// Original https://github.com/WacKEDmaN/STM32-LCD-demo-mandelbrot-raytrace
// Altered for the ESP32 ESP-WROFER-KIT by Martin Michael
//


#include "Variablen.h"
#include "mandelbrot.h"
#define RGBTO565(_r, _g, _b) ((((_r) & B11111000)<<8) | (((_g) & B11111100)<<3) | ((_b) >>3))
#include "raytracer.h"
#include "FreeMonoBold.cpp"

//WROVER_KIT_LCD tft;


////// CPC bootscreen end //////

///////////////// Setup ///////////////////////////////////
void setup() {
  Serial.begin(115200);
 
  tft.begin();

  uint8_t x = 0;
  uint32_t id = tft.readId();
  if (id) {
	  Serial.println("======= WROVER ST7789V Display Test ========");
  }
  else {
	  Serial.println("======= WROVER ILI9341 Display Test ========");
  }
  Serial.println("============================================");
  Serial.printf("Display ID:      0x%06X\n", id);

  pinMode(5, OUTPUT);

  x = tft.readcommand8(WROVER_RDDST);
  Serial.print("Status:          0x"); Serial.println(x, HEX);
  x = tft.readcommand8(WROVER_RDDPM);
  Serial.print("Power Mode:      0x"); Serial.println(x, HEX);
  x = tft.readcommand8(WROVER_RDDMADCTL);
  Serial.print("MADCTL Mode:     0x"); Serial.println(x, HEX);
  x = tft.readcommand8(WROVER_RDDCOLMOD);
  Serial.print("Pixel Format:    0x"); Serial.println(x, HEX);
  x = tft.readcommand8(WROVER_RDDIM);
  Serial.print("Image Format:    0x"); Serial.println(x, HEX);
  x = tft.readcommand8(WROVER_RDDSDR);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);


  tft.setFont(&_FreeMonoBold_);
   tft.fillScreen(ILI9341_NAVY);
  
  tft.setRotation(3);

}
/// end setup ////


////////////////// Loop //////////////////////////////////
void loop() {
  // mandelbrot
  tft.fillScreen(ILI9341_NAVY);
  uint32_t t = millis();
  uint32_t mandeltime = t;
  drawMandelbrot();
  Serial.println(F("Done!"));
  Serial.print(F("Mandelbrot Time = "));
  mandeltime = (millis() - t)/1000;
  Serial.print(mandeltime);
  Serial.println(F(" seconds"));
  delay(2000);  
  tft.fillScreen(ILI9341_NAVY);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_NAVY);
  tft.setTextSize(1);
  tft.setCursor(32,32);
  tft.println("Mandelbrot Time");
  tft.setCursor(64,64);
  tft.print(mandeltime);
  tft.print(" Seconds");
  delay(5000);  
  // mandelbrot end

  // raytracer 
  tft.fillScreen(ILI9341_NAVY);
  t = millis();
  uint32_t raytime = t;
//    doRaytrace(1,320,240,4); // fast preview
//    doRaytrace(1,320,240,2); // slower preview
    doRaytrace(1,320,240,1); // full 320x240 1 sample
//  doRaytrace(1,160,120,2); // quarter of the screen
  doRaytrace(2);  // very high quality 320x240 antialiased, 8 samples
  Serial.println(F("Done!"));
  Serial.print(F("Raytrace Time = "));
  raytime = (millis() - t)/1000;
  Serial.print(raytime);
  Serial.println(F(" seconds"));
  delay(2000);  
  tft.fillScreen(ILI9341_NAVY);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_NAVY);
  tft.setTextSize(1);
  tft.setCursor(32,32);
  tft.println("RayTrace Time");
  tft.setCursor(64,64);
  tft.print(raytime);
  tft.print(" Seconds");
  delay(5000);  
  
}
/// (never)end loop ////

