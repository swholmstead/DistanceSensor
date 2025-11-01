<h2>Assembly Instructions</h2>

<b>WORK IN PROGRESS</b>

<h3>LED strip</h3>

Cut 40 LEDs from the spool of WS2812B lights at the copper pads between LEDs.  Remove any waterproofing from over the pad on the side with the arror pointing AWAY from the copper pad.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3783.JPEG" alt="WS2812B" width=600>

Cut about 100 cm (40 inches) of the 22 AWG 3 wire cable. Remove 2 cm of the outer cable from each end.  Strip off
about 3mm from each wire and solder the wires to the exposed pad.

* +5V - RED
* Din - YELLOW
* GND - BLACK

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3784.JPEG" alt="WS2812B" width=600>

Crimp JST XH connectors to other end of cable and insert into FEMALE 3-pin JST-XH connector in the same order as shown.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3785.JPEG" alt="WS2812B" width=600>

Add shrink tubing to both ends (optional).

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3786.JPEG" alt="WS2812B" width=600>

<h3>Electronics assembly</h3>

Solder the following components onto the front side of the PCB.

* R1 - 2K 1206 SMD resistor
* R2 - 3K 1206 SMD resistor
* CONFIG - Tact button switch
* TTL-BUFFER - SN74AHCT125N Quad Bus Buffer chip.
    * ENSURE Pin 1 is aligned with dot on PCB.

Trim off pins on back side of PCB to be flush with board (doesn't need to be perfectly flush).

Solder the following components onto the back side of the PCB.

* 8 pin headers on boths sides of where the ESP8266 processor will go
* LED-STRIP - 3 pin right angle JST-XH connector
* POWER - DC Power barrel female jack 2.1mm

Trim off pins on front side of PCB to be flush with board.

Cover the area under where the HC-SR04 ultrasonic sensor and SSD1306 OLED display will go with electrical tape
to ensure the back of these components will not short with the PCB.

Solder a 3 pin header onto the SSD1306 OLED display with the pins behind the display.

Solder the OLED display to the PCB.

Bend the 4 pins on the HC-SR04 to be straight out.

Solder the HC-SR04 onto the PCB.

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

Cut 40 lights from the spool of WS1812b LED lights.  Solder on JST-XH 3 pin connector on side with DIN label and
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