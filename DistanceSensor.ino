#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// config for Ultrasonic distance sensor
#define triggerPin    D6
#define echoPin       D5

// config for LED strip
#define ledPin        D7
#define numLEDs       36  // number of LEDs used in strip, needs to be an even number
#define maxBright     255 // 0-255 max brightness
#define IDLE_COLOR    pixels.Color(0, 0, 0)   // BLACK or OFF
#define STOP_COLOR    pixels.Color(255, 0, 0) // RED
#define GO_COLOR      pixels.Color(0, 255, 0) // GREEN
#define BACK_COLOR    pixels.Color(0, 0, 128)  // faint BLUE
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numLEDs, ledPin, NEO_GRB + NEO_KHZ800);
float pixelSize = 1.0;    // the physical distance that each LED represents in cm

// config for configuration button
#define configPin     D3

// config for OLED display
#define sdaPin        D2
#define sclPin        D1
#define screenWidth   128
#define screenHeight  32
#define oledReset     -1  // pin to use to reset OLED or -1 to just use ESP reset pin
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);

// general config
#define detectRange   250 // distance where we start displaying distance in cm (approx 8 feet)
#define detectOffset  20  // Offset from detectRange in cm to start displaying GO_COLOR (approx 8 in)
#define idleTimeout   50  // in 0.1 sec increments
#define idleRange     5   // idle when distance doesn't deviate more than this range in cm (approx 1 in)
#define CMtoFT(x)     (x / 2.54 / 12.0)

int targetDistance = 1;   // stored in EEPROM
int lastDistance = -1;    // previous distance to detect idle mode
int idleCount = 0;        // count of distance samples at the same distance

// Arduino setup function. Runs in CPU 1
void setup()
{
  Serial.begin(74880);  // default baud rate for bootloader
  Serial.printf("\n\nESP8266 D1 mini startup...\n");

  // set up OLED display
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);

  // set up Config button
  pinMode(configPin, INPUT_PULLUP);

  // set up LED strip
  pixels.begin();
  pixels.setBrightness(maxBright);  // to prevent overcurrent situation, start low
  pixels.show();

  // initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.printf("SSD1306 allocation failed.\n");
    while (1);  // halt
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();

  // fetch stored target distance value
  EEPROM.begin(sizeof(targetDistance));
  EEPROM.get(0, targetDistance);
  calcPixelSize();
  Serial.printf("EEPROM target distance: %d cm\nPixel Size: %0.1f cm\n", targetDistance, pixelSize);
}

// Arduino loop function. Runs in CPU 1.
void loop()
{
  int distance = processDistance();
  processDisplay(distance);
  processPixels(distance);
  processConfig(distance);
  delay(100);
}

int processDistance()
{
  // send 10 microsecond pulse to trigger of HC-SR04
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // calculate distance from echo duration
  return pulseIn(echoPin, HIGH) * .034 / 2;
}

void processDisplay(int distance)
{
  display.clearDisplay();
  // check if out of range or idle mode
  if (distance <= detectRange + detectOffset && !isIdle(distance))
  {
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.printf("%.1f ft\n", CMtoFT(distance));
    display.printf("Goal: %.1f", CMtoFT(targetDistance));
  }
  display.display();
}

void processPixels(int distance) {
  // check if out of range or idle mode
  if (distance > detectRange + detectOffset || isIdle(distance))
  {
    pixels.fill(IDLE_COLOR, 0, numLEDs);
  }
  // check if beyond target distance
  else if (distance > targetDistance)
  {
    pixels.fill(BACK_COLOR, 0, numLEDs);
    int closeness = (detectRange - distance) / pixelSize;
    if (closeness > 0)
    {
      pixels.fill(GO_COLOR, 0, closeness);
      pixels.fill(GO_COLOR, numLEDs - closeness, closeness);
    }
    if (abs(distance - lastDistance) < idleRange)
    {
      idleCount++;
    }
    else
    {
      idleCount = 0;
      lastDistance = distance;
    }
  }
  // at target distance
  else
  {
    pixels.fill(STOP_COLOR, 0, numLEDs);
    if (idleCount >= idleTimeout) {
      pixels.fill(IDLE_COLOR, 0, numLEDs);
      lastDistance = distance;
    }
    else
    {
      idleCount++;
    }
  }
  pixels.show();
}

void processConfig(int distance)
{
  if (digitalRead(configPin) == LOW)
  {
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
    Serial.printf("EEPROM target distance: %d cm\nPixel Size: %0.1f cm\n", targetDistance, pixelSize);
    delay(2000);
  }
}

bool isIdle(int distance)
{
  // returns true if has stayed at the same distance too long
  return (abs(distance - lastDistance) < idleRange) && (idleCount >= idleTimeout);
}

void calcPixelSize()
{
  // calculates how much physical distance each LED pixel represents
  pixelSize = (detectRange - targetDistance) * 2.0 / (numLEDs + 2);
}
