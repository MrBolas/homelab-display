package main

import (
	"machine"

	"image/color"

	"tinygo.org/x/drivers"
	"tinygo.org/x/drivers/st7789"
	"tinygo.org/x/tinyfont"
	"tinygo.org/x/tinyfont/freemono"
	"tinygo.org/x/tinyfont/freesans"
	"tinygo.org/x/tinyfont/freeserif"
)

func main() {
	// Example configuration for Adafruit Clue
	// machine.SPI1.Configure(machine.SPIConfig{
	//	Frequency: 8000000,
	//	SCK:       machine.TFT_SCK,
	//	SDO:       machine.TFT_SDO,
	//	SDI:       machine.TFT_SDO,
	//	Mode:      0,
	// })
	// display := st7789.New(machine.SPI1,
	//	machine.TFT_RESET,
	//	machine.TFT_DC,
	//	machine.TFT_CS,
	//	machine.TFT_LITE)

	d := initDisplay()
	//_, _ := d.Size()

	white := color.RGBA{255, 255, 255, 255}
	//red := color.RGBA{255, 0, 0, 255}
	blue := color.RGBA{0, 0, 255, 255}
	// green := color.RGBA{0, 255, 0, 255}
	//black := color.RGBA{0, 0, 0, 255}

	df := drivers.Displayer(d)

	//tinyfont.WriteLine(d, &tinyfont.Org01, 10, 35, "HELLO", white)
	//d.FillRectangle((10), (10), (10), (10), red)
	//d.SetPixel((1), (1), white)
	//d.SetPixel((10), (10), white)
	//d.SetPixel((100), (100), white)
	//d.SetPixel((250), (250), white)
	d.FillScreen(blue)
	tinyfont.WriteLineColors(d, &freesans.Bold18pt7b, 10, 35, "HELLO", []color.RGBA{white})
	tinyfont.WriteLineColorsRotated(d, &freemono.Bold18pt7b, 240, 150, "Gophers", []color.RGBA{white}, tinyfont.NO_ROTATION)
	tinyfont.WriteLineColorsRotated(d, &freeserif.Bold9pt7b, 200, 90, "TinyGo1", []color.RGBA{white}, tinyfont.NO_ROTATION)
	tinyfont.WriteLineColorsRotated(d, &tinyfont.Org01, 50, 70, "TinyGo2", []color.RGBA{white}, tinyfont.NO_ROTATION)

	// tinyfont.WriteLine(d, &freemono.BoldOblique24pt7b, 150, 100, "random string", green)
	// tinyfont.DrawChar(d, &freemono.Bold18pt7b, 50, 50, 'm', white)

	df.Display()
}

func initDisplay() *st7789.Device {

	machine.SPI1.Configure(machine.SPIConfig{
		Frequency: 6000000,
		Mode:      0,
		SCK:       machine.SPI1_SCK_PIN,
		SDO:       machine.SPI1_SDO_PIN,
		SDI:       machine.SPI1_SDI_PIN,
		LSBFirst:  false,
		DataBits:  16,
	})
	display := st7789.New(machine.SPI1,
		machine.GP15, // TFT_RESET
		machine.GP8,  // TFT_DC
		machine.GP9,  // TFT_CS
		machine.GP13) // TFT_LITE

	display.Configure(st7789.Config{
		Rotation: st7789.NO_ROTATION,
		Width:    480,
		Height:   320,
	})
	display.IsBGR(true)
	display.Command(st7789.MADCTL)
	display.Data(st7789.MADCTL_MV)

	machine.Serial.Configure(machine.UARTConfig{
		BaudRate: 9600,
		TX:       machine.UART0_TX_PIN,
		RX:       machine.UART0_RX_PIN},
	)
	machine.InitSerial()

	return &display
}
