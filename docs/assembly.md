<h2>Assembly Instructions</h2>

<b>WORK IN PROGRESS</b>

<h3>Electronics assembly</h3>

Solder all socket components on the PCB.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_xxxx.JPEG" alt="Solder" width=400>

Add the following components to the PCB:

* ESP8266 D1 Mini
* HC-SR04 Ultrasonic sensor
* SSD1306 OLED display
* SN74AHCT125N Quad Buffer

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3527.JPEG" alt="All Components" width=400>

<h3>Controller Case</h3>

Insert circuit board into 3D printed case.  Secure with screws.

Attach case back with screws.

<h3>Strip of LED lights</h3>

Cut 36 lights from the spool of WS1812b LED lights.  Solder on JST-XH 3 pin connector on side with DIN label and
arrows pointing AWAY.

Plug LED strip into case.

<h3>Operation</h3>

Attach case at vehicle bumper height and route LED strip to about eye height while sitting in vehicle.

Plug in 5V power supply.  Circuit will start immediately.

Place vehicle in ideal parking spot and press Config button through case exterior hole.  This will save the 
vehicle current position distance in the EEPROM.

Back out vehicle and pull in to verify operation.

LED strip will glow faint BLUE when it recognized a vehicle within about 8 feet.  As you get closer, the GREEN
lights will gradually close in towards the center.  When vehicle is in ideal parking spot, LEDs will turn RED.

System will automatically timeout at turn off after 5 seconds of nothing moving.