/*  
Homelab display
 */

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <string.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

#define BACKGROUND_COLOR TFT_WHITE
#define MAX_WIDTH 480
#define MAX_HEIGHT 320
#define MAX_SERVICES 12

void printNewLine(int x, int y, String label, String value, bool normal) {
  uint16_t txtColor = TFT_BLACK;
  if (!normal) {
    txtColor = TFT_CYAN;
  }
  tft.drawLine(y, x, MAX_WIDTH, x, TFT_BLACK);
  tft.setCursor(y, x, 1);
  tft.setTextColor(TFT_BLACK);
  tft.println(label);
  tft.setTextColor(txtColor);
  tft.setCursor(MAX_WIDTH / 2, x, 1);
  tft.println(value);
}

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
  void printDetailScreen(int time) {
    tft.fillScreen(BACKGROUND_COLOR);
    printNewLine(20, 0, "Name", _name, true);
    printNewLine(40, 0, "ID", _id, true);
    printNewLine(60, 0, "URL", _url, true);
    printNewLine(80, 0, "ReqPerMin", std::to_string(int(_req_per_minute)).c_str(), true);
    printNewLine(100, 0, "200s", std::to_string(int(_success)).c_str(), true);
    if (_userFail > 0) {
      printNewLine(120, 0, "400s", std::to_string(int(_userFail)).c_str(), false);
    }
    if (_internalError > 0) {
      printNewLine(140, 0, "500s", std::to_string(int(_internalError)).c_str(), false);
    }
    delay(time);
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
    _nextButton->initButtonUL(&tft, uint16_t(MAX_WIDTH-150), uint16_t(250), uint16_t(150), uint16_t(70), uint16_t(5), uint16_t(0), TFT_WHITE, "next", uint16_t(2));
    _previousButton->initButtonUL(&tft, uint16_t(0), uint16_t(250), uint16_t(150), uint16_t(70), uint16_t(5), uint16_t(1), TFT_WHITE, "prev", uint16_t(2));
  }
  void printDetailScreen() {
    tft.fillScreen(BACKGROUND_COLOR);
    tft.setTextFont(4);
    printNewLine(20, 0, "Name", _service->_name, true);
    printNewLine(40, 0, "ID", _service->_id, true);
    printNewLine(60, 0, "URL",  _service->_url, true);
    printNewLine(80, 0, "ReqPerMin", std::to_string(int(_service->_req_per_minute)).c_str(), true);
    printNewLine(100, 0, "200s", std::to_string(int(_service->_success)).c_str(), true);
    if (_service->_userFail > 0) {
      printNewLine(120, 0, "400s", std::to_string(int(_service->_userFail)).c_str(), false);
    }
    if (_service->_internalError > 0) {
      printNewLine(140, 0, "500s", std::to_string(int(_service->_internalError)).c_str(), false);
    }
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

DetailsScreen *detailedScreens[MAX_SERVICES];

void display_landing_screen() {
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setCursor(MAX_WIDTH / 3 + 24, MAX_HEIGHT / 2, 2);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(4);
  tft.println("HomeLab");
  tft.setCursor((MAX_WIDTH / 3) + 32, (MAX_HEIGHT / 2) + 24, 2);
  tft.setTextFont(4);
  tft.println("MrBalls");
  delay(1000);
}

void load_from_server() {
  tft.setCursor(MAX_WIDTH / 3 + 24, MAX_HEIGHT / 4, 2);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(4);
  tft.println("Loading ...");

  // fetch from server
  auto service1 = new Service("service 1", "1", "url1", 200, 8, 8, 8);
  detailedScreens[0] = new DetailsScreen(service1); 
  auto service2 = new Service("service 2", "2", "url2", 200, 8, 8, 8);
  detailedScreens[1] = new DetailsScreen(service2);
  auto service3 = new Service("service 3", "3", "url3", 200, 8, 8, 8);
  detailedScreens[2] = new DetailsScreen(service3);
  delay(1000);
}

uint16_t x = 0;
uint16_t y = 0;
uint16_t data[5];
int i = 0;
auto nextButton = new TFT_eSPI_Button();
auto previousButton = new TFT_eSPI_Button();
Service* currentService = NULL;
DetailsScreen* currentScreen = NULL;

void setup(void) {
  tft.init();
  tft.setRotation(1);
  display_landing_screen();
  load_from_server();
  tft.fillScreen(BACKGROUND_COLOR);

  Serial.begin(9600);
}

void loop() {
  // refresh screen
  if (detailedScreens[i] != NULL 
  && detailedScreens[i]!=currentScreen) {
    currentScreen = detailedScreens[i];
    currentScreen->printDetailScreen();

    tft.setTextFont(uint16_t(2));
    currentScreen->getNextButton()->drawButton();
    currentScreen->getPrevButton()->drawButton();
  };

  //  scan for touch events
  if (tft.getTouch(&x, &y)) {
    Serial.print(uint16_t(x));
    Serial.print(" ");
    Serial.println(uint16_t(y));

    if(currentScreen->getNextButton()->contains(uint16_t(x),uint16_t(y))){
      Serial.println("next button pressed");
      if(detailedScreens[i+1]!=NULL){
        i++;  
      }
    }

    if(currentScreen->getPrevButton()->contains(uint16_t(x),uint16_t(y))){
      Serial.println("previous button pressed");
      if(detailedScreens[i-1]!=NULL){
        i--;  
      }
    }
  };
}
