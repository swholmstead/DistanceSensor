
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// pins for Ultrasonic distance sensor
#define triggerPin D6
#define echoPin D5

// pins for LED strip
#define ledPin D7
#define numLEDs 36

// pin for configuration button
#define configPin D3

// pins for OLED display
#define sdaPin D2
#define sclPin D1
#define screenWidth 128
#define screenHeight 32
#define oledReset -1

// #define powerOnDistance 250  // 250 cm is approx 8 feet
#define powerOnDistance 100  // 250 cm is approx 8 feet
#define detectionRange  20   // start detecting 20 cm (8 inches) beyond powerOnDistance
#define idleTimeout     50   // 5 seconds
#define idleRange       5    // 5 cm or approx 2 inches
#define IDLE_COLOR pixels.Color(0, 0, 0)
#define STOP_COLOR pixels.Color(255, 0, 0)
#define GO_COLOR pixels.Color(0, 255, 0)
#define BACK_COLOR pixels.Color(0, 0, 64)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numLEDs, ledPin, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);
int targetDistance = 1;
float pixelSize = 1.0;
int idleCount = 0;
int idleDistance = -1;

// Arduino setup function. Runs in CPU 1
void setup() {
  Serial.begin(19200);

  // set up OLED display
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);

  // set up Config button
  pinMode(configPin, INPUT_PULLUP);

  // set up LED strip
  pixels.begin();
  pixels.setBrightness(50);  // to prevent overcurrent situation, start low
  pixels.show();

  // initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.printf("SSD1306 allocation failed.\n");
    while (1)
      ;  // halt
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();

  // fetch stored target distance value
  EEPROM.begin(sizeof(targetDistance));
  EEPROM.get(0, targetDistance);
  calcPixelSize();
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
  return pulseIn(echoPin, HIGH) * .034 / 2;
}

void processDisplay(int distance) {
  display.clearDisplay();
  if (distance <= powerOnDistance + detectionRange && !isIdle(distance)) {
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.printf("%.1f ft\n", distance / 2.54 / 12.0);
    display.printf("Goal: %.1f", targetDistance / 2.54 / 12.0);
  }
  display.display();
}

void processPixels(int distance) {
  if (distance > powerOnDistance + detectionRange || isIdle(distance)) {
    pixels.fill(IDLE_COLOR, 0, numLEDs);
  } else if (distance > targetDistance) {
    pixels.fill(BACK_COLOR, 0, numLEDs);
    int closeness = (powerOnDistance - distance) / pixelSize;
    if (closeness > 0) {
      pixels.fill(GO_COLOR, 0, closeness);
      pixels.fill(GO_COLOR, numLEDs - closeness, closeness);
    }
    if (abs(distance - idleDistance) < idleRange) {
      idleCount++;
    } else {
      idleCount = 0;
      idleDistance = distance;
    }
  } else {
    pixels.fill(STOP_COLOR, 0, numLEDs);
    if (idleCount >= idleTimeout) {
      pixels.fill(IDLE_COLOR, 0, numLEDs);
      idleDistance = distance;
    } else {
      idleCount++;
    }
  }
  pixels.show();
}

void processConfig(int distance) {
  if (digitalRead(configPin) == LOW) {
    // store current distance as target distance in EEPROM
    targetDistance = distance;
    EEPROM.put(0, targetDistance);
    EEPROM.commit();
    calcPixelSize();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(3);
    display.print("SAVED");
    display.display();
    pixels.fill(GO_COLOR, 0, numLEDs);
    pixels.show();
    delay(2000);
  }
}

bool isIdle(int distance) {
  return (abs(distance - idleDistance) < idleRange) && (idleCount >= idleTimeout);
}

void calcPixelSize() {
  pixelSize = (powerOnDistance - targetDistance) * 2.0 / (numLEDs + 2);
}
