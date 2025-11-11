<h2>Assembly Instructions</h2>

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

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3787.JPEG" alt="WS2812B" width=600>

<h3>Electronics assembly</h3>

Solder the following components onto the front side of the PCB.

* R1 - 2K 1206 SMD resistor
* R2 - 3K 1206 SMD resistor
* CONFIG - Tact button switch
* TTL-BUFFER - SN74AHCT125N Quad Bus Buffer chip.
    * ENSURE Pin 1 is aligned with dot on PCB.

Trim off pins on back side of PCB to be flush with board (doesn't need to be perfectly flush).

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/Solder1.png" alt="PCB" width=600>
<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3795.JPEG" alt="PCB" width=600>


Solder the following components onto the back side of the PCB.

* 8 pin headers on boths sides of where the ESP8266 processor will go
* LED-STRIP - 3 pin right angle JST-XH connector
* POWER - DC Power barrel female jack 2.1mm

Trim off pins on front side of PCB to be flush with board.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3796.JPEG" alt="PCB" width=600>

Cover the area under where the SSD-1306 OLED display will go with electrical tape
to ensure this component will not short with the PCB.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3798.JPEG" alt="PCB" width=600>

Bend the pins on the HC-SR04 ultrasonic sensor so they are straight.  Then cover the back
with electrical tape to ensure this component will not short with the PCB.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3799.JPEG" alt="PCB" width=600>

Solder a 4 pin header onto the SSD1306 OLED display with the pins behind the display.
Solder the OLED display to the PCB.  Insert Display Offset 3D printed part behind the right side of the display
to stablize it.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3800.JPEG" alt="PCB" width=600>

Solder the HC-SR04 onto the PCB.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3801.JPEG" alt="PCB" width=600>


Add the following components to the PCB:

* ESP8266 D1 Mini

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3804.JPEG" alt="PCB" width=600>

Insert the power supply to ensure PCB powers on.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3802.JPEG" alt="PCB" width=400>

<h3>Controller Case</h3>

Insert Save Button into back of 3D printed case.  Insert circuit board into case.  Secure with 2 M1.7 x 5mm screws.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3805.JPEG" alt="Case" width=400>

Attach case back with 4 M1.7 x 5mm screws.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3806.JPEG" alt="Case" width=400>


<h3>Operation</h3>

Attach case at vehicle bumper height and route LED strip to about eye height while sitting in vehicle.
Plug LED strip into case.  Secure cable and LEDs with clips.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3807.JPEG" alt="Clips" width=600>

Plug in 5V power supply.  Circuit will start immediately.

<img src="https://github.com/swholmstead/DistanceSensor/blob/main/pictures/IMG_3809.JPEG" alt="Clips" width=600>

Place vehicle in ideal parking spot and press Save Button.  This will save the vehicle current position
distance in the EEPROM.

Back out vehicle and pull in to verify operation.

LED strip will glow faint BLUE when it recognized a vehicle within about 8 feet.  As you get closer, the GREEN
lights will gradually close in towards the center.  When vehicle is in ideal parking spot, LEDs will turn RED.

System will automatically timeout at turn off after 5 seconds of nothing moving.