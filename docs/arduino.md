<h2>Arduino IDE</h2>

Download IDE from https://www.arduino.cc/en/software

Under File > Preferences, set Additional boards manager URLs to http://arduino.esp8266.com/stable/package_esp8266com_index.json

Add libraries:
 * Adafruit GFX by Adafruit
 * Adafruit NeoPixel by Adafruit
 * Adafruit SSD1306 by Adafruit

Under Tools > Board > Board Manager, add these boards
* esp8266 by ESP8266 Community

Under Tools > Board, select esp8266 > LOLIN (WEMOS) D1 R2 & mini

Connect ESP32 Development Kit with USB cable
Under Tools > Port, select COM port used

Open DistanceSensor.ino file and click right arrow on top tool bar to download code to ESP8266

