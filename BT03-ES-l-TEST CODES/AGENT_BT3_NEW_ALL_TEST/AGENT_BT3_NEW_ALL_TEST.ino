/***************************************************
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        25 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels



#include <SPI.h>
#include "Adafruit_MAX31855.h"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   19
#define MAXCS_1   26
#define MAXCS_2   27
#define MAXCLK  18

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple_1(MAXCLK, MAXCS_1, MAXDO);
Adafruit_MAX31855 thermocouple_2(MAXCLK, MAXCS_2, MAXDO);


void setup() {
  Serial.begin(115200);

  pinMode(32, INPUT);
  pinMode(22, INPUT);
  pinMode(21, INPUT);
   //pinMode(35, INPUT);


  pinMode(13, OUTPUT);
  pinMode(33, OUTPUT);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensor...");
  if (!thermocouple_1.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }

  Serial.print("Initializing sensor...");
  if (!thermocouple_2.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }


  // OPTIONAL: Can configure fault checks as desired (default is ALL)
  // Multiple checks can be logically OR'd together.
  // thermocouple.setFaultChecks(MAX31855_FAULT_OPEN | MAX31855_FAULT_SHORT_VCC);  // short to GND fault is ignored

  Serial.println("DONE.");


    pixels.clear(); // Set all pixel colors to 'off'\


  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(1000);
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(1000);
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(1000);


}

void loop() {
  // basic readout test, just print the current temp
  //  Serial.print("Internal Temp = ");
  //  Serial.println(thermocouple_1.readInternal());
  //  Serial.println(thermocouple_2.readInternal());


  double c1 = thermocouple_1.readCelsius();
  double c2 = thermocouple_2.readCelsius();

  if (isnan(c1)) {
    Serial.println("Thermocouple fault(s) detected!");
    uint8_t e = thermocouple_1.readError();
    if (e & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple is open - no connections.");
    //    if (e & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple is short-circuited to GND.");
    //    if (e & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple is short-circuited to VCC.");
  } else {
    Serial.print("C1 = ");
    Serial.println(c1);
  }

  if (isnan(c2)) {
    Serial.println("Thermocouple fault(s) detected!");
    uint8_t e = thermocouple_2.readError();
    if (e & MAX31855_FAULT_OPEN) Serial.println("FAULT: Thermocouple is open - no connections.");
    //    if (e & MAX31855_FAULT_SHORT_GND) Serial.println("FAULT: Thermocouple is short-circuited to GND.");
    //    if (e & MAX31855_FAULT_SHORT_VCC) Serial.println("FAULT: Thermocouple is short-circuited to VCC.");
  } else {
    Serial.print("C2 = ");
    Serial.println(c2);
  }



  delay(200);
  digitalWrite(13, HIGH);
  digitalWrite(23, LOW);
  delay(1000);
  digitalWrite(23, HIGH);
  digitalWrite(13, LOW);
  delay(1000);


  Serial.println("");


  Serial.println("--------------------------------------------------");
  Serial.print(digitalRead(32)); Serial.print(digitalRead(22)); Serial.print(digitalRead(21));//Serial.print(digitalRead(35));
    Serial.println("");
  Serial.println("--------------------------------------------------");

  //Serial.print("F = ");
  //Serial.println(thermocouple.readFahrenheit());

  delay(1000);
}
