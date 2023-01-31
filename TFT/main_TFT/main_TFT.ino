/*  
Homelab display
 */

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <string.h>
#include <hardware/adc.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

#define BACKGROUND_COLOR TFT_WHITE
#define MAX_WIDTH 480
#define MAX_HEIGHT 320
#define MAX_SERVICES 12

char next_label[]="next";
char prev_label[]="prev";

#ifndef STASSID
#define STASSID "The Internet"
#define STAPSK "Papaya0721"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
WiFiMulti multi;

class LandingScreen {
  public:
  LandingScreen(){}
  void display_landing_screen() {
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setCursor(MAX_WIDTH / 3 + 36, MAX_HEIGHT / 2, 2);
    tft.setTextColor(TFT_BLACK);
    tft.setTextFont(4);
    tft.println("HomeLab");
    tft.setCursor((MAX_WIDTH / 3) + 48, (MAX_HEIGHT / 2) + 24, 2);
    tft.setTextFont(4);
    tft.println("MrBalls");
    delay(1000);
  }
  void connect_to_wifi(){
    tft.setCursor(MAX_WIDTH / 3+6 , MAX_HEIGHT / 4, 2);
    tft.setTextColor(TFT_BLACK);
    tft.setTextFont(2);
    char wifib[50];
    sprintf (wifib, "Connecting to: %s",ssid);
    tft.println(wifib);

    multi.addAP(ssid, password);
    if (multi.run() != WL_CONNECTED) {
      Serial.println("Unable to connect to network, rebooting in 10 seconds...");
      delay(10000);
      rp2040.reboot();
    }

    tft.setCursor(MAX_WIDTH / 3-2 , MAX_HEIGHT / 4+16, 2);
    arduino::IPAddress ip = WiFi.localIP();
    char ipb[50];
    sprintf (ipb, "Connected on %s",ip.toString().c_str());
    Serial.println(ipb);
    tft.println(ipb);
    delay(10000);
  }
  private:
};

class Service {
public:
  Service(String name, String id,
          String url, int reqPerMinute,
          int success, int userFail, int internalError) {
    _name = name;
    _id = id;
    _url = url;
    _req_per_minute = reqPerMinute;
    _success = success;
    _userFail = userFail;
    _internalError = internalError;
  };
  String _name;
  String _id;
  String _url;
  int _req_per_minute;
  int _success;
  int _userFail;
  int _internalError;
private:
};

class DetailsScreen {
  public:
  DetailsScreen(Service *service){
    _service = service;
    _nextButton =  new TFT_eSPI_Button(); 
    _previousButton =  new TFT_eSPI_Button(); 
    _nextButton->initButtonUL(&tft, uint16_t(MAX_WIDTH-150), uint16_t(250), uint16_t(150), uint16_t(70), uint16_t(5), uint16_t(0), TFT_WHITE, next_label , 2);
    _previousButton->initButtonUL(&tft, uint16_t(0), uint16_t(250), uint16_t(150), uint16_t(70), uint16_t(5), uint16_t(1), TFT_WHITE, prev_label, 2);
  }
  void printNewLine(int x, int y, String label, String value, bool normal) {
    uint16_t txtColor = TFT_BLACK;
    if (!normal) {
      txtColor = TFT_BLUE;
    }
    tft.setCursor(y, x, 1);
    tft.setTextColor(TFT_BLACK);
    tft.println(label);
    tft.setTextColor(txtColor);
    tft.setCursor(MAX_WIDTH / 2, x, 1);
    tft.println(value);
  }
  void printDetailScreen() {
    int line_spacing = 20;
    int offset = -2;
    tft.fillScreen(BACKGROUND_COLOR);
    for (int i = 1; i<9; i++) {
      tft.drawLine(0, i*line_spacing+offset, MAX_WIDTH, i*line_spacing+offset, TFT_BLACK);
    }
    printNewLine(0, 0, "IP Address", WiFi.localIP().toString().c_str(), true);
    printNewLine(20, 0, "Name", _service->_name, true);
    printNewLine(40, 0, "ID", _service->_id, true);
    printNewLine(60, 0, "URL",  _service->_url, true);
    printNewLine(80, 0, "ReqPerMin", String(int(_service->_req_per_minute)).c_str(), true);
    printNewLine(100, 0, "200s", String(int(_service->_success)).c_str(), true);
    printNewLine(120, 0, "400s", String(int(_service->_userFail)).c_str(), _service->_userFail == 0);
    printNewLine(140, 0, "500s", String(int(_service->_internalError)).c_str(), _service->_internalError == 0);
    getNextButton()->drawButton();
    getPrevButton()->drawButton();
  }
  Service* getService(){
    return _service;
  }
  TFT_eSPI_Button* getNextButton(){
    return _nextButton;
  }
  TFT_eSPI_Button* getPrevButton(){
    return _previousButton;
  }
  private:
  Service *_service;
  TFT_eSPI_Button *_nextButton;
  TFT_eSPI_Button *_previousButton;
};

class MenuScreen {
  public:
  MenuScreen(DetailsScreen *detailedScreens){
    this->_detailedScreens = detailedScreens;

    for (int i = 0; i<sizeof(detailedScreens)-1; i++){
      String service_name = this->_detailedScreens[i].getService()->_name;
      char service_label[service_name.length() + 1];
      service_name.toCharArray(service_label, service_name.length() + 1);

      TFT_eSPI_Button* newButton =  new TFT_eSPI_Button(); 
      newButton->initButtonUL(&tft, uint16_t(20*i), uint16_t(0), uint16_t(MAX_WIDTH),uint16_t(20), uint16_t(5), uint16_t(1), TFT_WHITE, service_label, 2);
      this->_buttons[i]= newButton;
    }
  }
  void displayMenu(){
      for(int i = 0; i<sizeof(this->_buttons); i++){
        _buttons[i]->drawButton();
      }
  }
  private:
  DetailsScreen *_detailedScreens;
  TFT_eSPI_Button *_buttons[MAX_SERVICES];
};

TFT_eSPI_Button *buttons[MAX_SERVICES] = {NULL};
Service *services[MAX_SERVICES] = {NULL};
DetailsScreen *detailedScreens[MAX_SERVICES] = {NULL};

void load_from_server() {
  // fetch from server
  auto service1 = new Service("service 1", "1", "url1", 200, 8, 8, 8);
  auto service2 = new Service("service 2", "2", "url2", 200, 8, 8, 8);
  auto service3 = new Service("service 3", "3", "url3", 200, 8, 8, 8);

  services[0] = service1;
  services[1] = service2;
  services[2] = service3;

  detailedScreens[0] = new DetailsScreen(service1); 
  detailedScreens[1] = new DetailsScreen(service2);
  detailedScreens[2] = new DetailsScreen(service3);

  delay(1000);
}

uint16_t x = 0;
uint16_t y = 0;
uint16_t data[5];
int i = 0;
auto nextButton = new TFT_eSPI_Button();
auto previousButton = new TFT_eSPI_Button();
DetailsScreen* currentScreen = NULL;

void setup(void) {
  Serial.begin(9600);

  //  Start TFT
  tft.init();
  tft.setRotation(1);
  auto landingPage = new LandingScreen();
  landingPage->display_landing_screen();

  //  Connect to Wifi
  landingPage->connect_to_wifi();

setup_t tft_settings={};
tft.getSetup(tft_settings);

      char buffer[50];
    sprintf (buffer, "mosi: %d, miso: %d, clk: %d, cs: %d,",tft_settings.pin_tft_mosi,tft_settings.pin_tft_miso,tft_settings.pin_tft_clk,tft_settings.pin_tft_cs);

      char buffer2[50];
    sprintf (buffer2, "serial: %d, port: %d, dc: %d, rd: %d, wr: %d,",tft_settings.serial ,tft_settings.port,tft_settings.pin_tft_dc,tft_settings.pin_tft_rd,tft_settings.pin_tft_wr);

      char buffer3[50];
    sprintf (buffer3, "spi_freq: %d, rd_freq: %d",tft_settings.tft_spi_freq,tft_settings.tft_rd_freq);

    Serial.println("buffer");
    Serial.println(buffer);
        Serial.println(buffer2);
        Serial.println(buffer3);

  load_from_server();
  tft.fillScreen(BACKGROUND_COLOR);

/*
  auto menu = MenuScreen(detailedScreens);
  menu->displayMenu();
  /*
    currentScreen = detailedScreens[i];
    currentScreen->printDetailScreen();
  */
}

void loop() {
  //  scan for touch events
  if (tft.getTouch(&x, &y)) {
    char buffer[50];
    sprintf (buffer, "touch coordinates: x: %d y: %d",uint16_t(x),uint16_t(y));
    Serial.println(buffer);

    if(currentScreen->getNextButton()->contains(uint16_t(x),uint16_t(y)) 
    && detailedScreens[i+1] != NULL){
      i++;  
      sprintf (buffer, "next button pressed: %d",i);
      Serial.println(buffer);
      currentScreen = detailedScreens[i];
      currentScreen->printDetailScreen();
    }

    if(currentScreen->getPrevButton()->contains(uint16_t(x),uint16_t(y))
        && detailedScreens[i-1] != NULL && i>0){
      i--;  
      sprintf (buffer, "previous button pressed: %d",i);
      Serial.println(buffer);
      currentScreen = detailedScreens[i];
      currentScreen->printDetailScreen();
    }
  };
}
