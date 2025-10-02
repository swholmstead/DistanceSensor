
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// pins for Ultrasonic distance sensor
#define triggerPin    12
#define echoPin       13

// pins for LED strip
#define ledPin        14
#define numLEDs       30

// pin for configuration button
#define configPin     16

// pins for OLED display
#define sdaPin        4
#define sclPin        5
#define screenWidth   128
#define screenHeight  64
#define oledReset     -1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numLEDs, ledPin, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);
int targetDistance = -1;

// Arduino setup function. Runs in CPU 1
void setup() {
  Serial.begin(115200);

  // set up OLED display
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);

  // set up Config button
  pinMode(configPin, INPUT_PULLUP);

  // set up LED strip
  pixels.begin();
  pixels.setBrightness(50); // to prevent overcurrent situation, start low
  pixels.show();

  // initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.printf("SSD1306 allocation failed.\n");
    while (1); // halt
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();

  // fetch stored target distance value
  EEPROM.begin(4);
  EEPROM.get(0, targetDistance);
  Serial.printf("Target Distance: %d\n", targetDistance);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
  int distance = processDistance();
  processDisplay(distance);
  processPixels(distance);
  processConfig(distance);

  delay(100);
}

int processDistance() {
  // send 10 microsecond pulse to trigger of HC-SR04
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // calculate distance from echo duration
  int distance = pulseIn(echoPin, HIGH) * .034 / 2;
  Serial.printf("Ultrasonic distance: %d\n", distance);
  return distance;
}

void processDisplay(int distance) {
  Serial.printf("Distance: %d\n", distance);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.setTextSize(2);
  display.printf("%d cm\n", distance);
  display.setTextSize(1);
  display.printf("Target distance: %d", targetDistance);
  display.display();
}

void processPixels(int distance) {
  static uint16_t hue = 0;
  pixels.rainbow(hue, 20);
  pixels.show();
  hue += 256;
  if (hue >= 65535) {
    hue = 0;
  }
}

void processConfig(int distance) {
  if (digitalRead(configPin) == LOW) {
    // store current distance as target distance in EEPROM
    targetDistance = distance;
    EEPROM.put(0, targetDistance);
    Serial.printf("Stored target distance: %d\n", targetDistance);
    display.setCursor(0,24);
    display.setTextSize(1);
    display.print("Target Distance SAVED.")
    display.display();
    delay(1000);
  }
}
