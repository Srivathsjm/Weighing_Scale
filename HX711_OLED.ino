
#include "HX711.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;

void setup() {
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  
  display.display();
  delay(2000);
   scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
   display.println("HX711 Demo");
   display.println("Initializing the scale");
   display.println("Before setting up the scale:");
   display.display();
   display.clearDisplay();
   display.setCursor(0,0);
   display.setTextSize(1);      
   display.setTextColor(SSD1306_WHITE);
   display.print("read: \t\t");
   display.println(scale.read());

   display.display();
   delay(500);
   display.clearDisplay();
   display.setCursor(0,0);
   display.setTextSize(1);      
   display.setTextColor(SSD1306_WHITE);
   display.print("read average: \t\t");
   display.println(scale.read_average(20));    // print the average of 20 readings from the ADC

   display.print("get value: \t\t");
   display.println(scale.get_value(5));  

   display.display();
   delay(500);
   display.clearDisplay();
   display.display();
   scale.set_scale(228.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
   scale.tare();  

}
void loop() {
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  
  display.println("Weight in grams:");
  display.println(scale.get_units(),1);
  display.display();
  
  delay(200);
  if(digitalRead(2)== LOW)
  scale.tare();
  
}
