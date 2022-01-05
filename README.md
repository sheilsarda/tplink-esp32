## TP-Link Plug Load Sensor and ESP32 Integration

In this repository is a collection of `.ino` scripts built for the ESP32 to interface with the KS115 plug load sensor by TP-Link.

*Note* it is possible to run any of these scripts on other ESP or Arduino based platforms with minimal tweaks.

Some of these scripts have been modified from Prof. Mark Yim's MEAM510 examples.

#### `espAirPennNetDevice`

This connects the ESP32 to the AirPennNet-Device network to try to test if we can use P2P communication to interface with the plug load sensor, which is also on that network.

#### `macAddress`

This simply prints the MAC address of the ESP32. It is also possible to change the MAC on an ESP32.

#### `softAPTest`

This script creates an access point from the ESP32 which other devices (e.g. the plug load sensor) can join.

#### `stationMode`

This script joins a WiFi network (e.g. AirPennNet-Device) and then broadcasts a webpage at a local IP Address, visible to other devices on that network.
