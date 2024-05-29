<h6>
Copyright © 2024, Danylo Galytskyy
ALL RIGHTS RESERVED
</h6>

Libraries used:

* OLED: https://github.com/nhatuan84/esp32-sh1106-oled/tree/master

* Matrix: https://github.com/adafruit/Adafruit_NeoMatrix

* Graphics: https://github.com/adafruit/Adafruit-GFX-Library

* Buttons: https://github.com/GyverLibs/EncButton

* Encoder: https://github.com/madhephaestus/ESP32Encoder

* IO: https://github.com/GyverLibs/GyverIO

* https://github.com/adafruit/Adafruit_BusIO

Schematic:

<img width="839" alt="Screenshot 2024-05-29 at 12 45 10" src="https://github.com/danylog/comunicador_esp32/assets/36711786/cbbce6a4-33f0-452b-bf99-8c7a9f282911">

Instructions:
* upload "mac_adress_visualizer" sketch on one device
* open Serial port on 9600 baud
* copy the mac address
* put it in the other device’s "_codigo-nuevo.ino" line 17 using the format provided: for example **E0:5A:1B:D2:D7:D8** becomes **uint8_t broadcastAddress[] = { 0xE0, 0x5A, 0x1B, 0xD2, 0xD7, 0xD8 };**
* repeat the same process with the other device

