#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define triggerPin    12
#define echoPin       13

long duration;
int distance;

#define ledPin        14
#define numLEDs       30

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numLEDs, ledPin, NEO_GRB + NEO_KHZ800);

#define sdaPin        4
#define sclPin        5
#define screenWidth   128
#define screenHeight  64
#define oledReset     -1

Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);



// Arduino setup function. Runs in CPU 1
void setup() {
  Serial.begin(115200);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);

  pixels.begin();
  pixels.setBrightness(50); // to prevent overcurrent situation, start low
  pixels.show();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.printf("SSD1306 allocation failed.\n");
    while (1); // halt
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.println("SSD1306 OLED");
  display.drawRect(0, 20, 50, 30, WHITE);
  display.display();

  delay(2000);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
  static uint16_t hue = 0;

  // send 10 microsecond pulse to trigger of HC-SR04
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * .034 / 2;
  Serial.printf("Distance: %d\n", distance);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Parking Assistant");
  display.print("Distance: ");
  display.setTextSize(2);
  display.printf("%d cm", distance);
  display.display();

  pixels.rainbow(hue, 20);
  pixels.show();
  hue += 256;
  if (hue >= 65535) {
    hue = 0;
  }

  delay(100);
}
