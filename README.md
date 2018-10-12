# IOTwaterpump
Arduino (ESP8266) controlled water pump

## Overview
This code controls a small 12V water pump via an Arduino based ESP8266.  

The ESP8266 will register itself on a wireless network and then the pump can be interfaced via  simple URL of
http://pump.local/ by any device also on the same network.

## Network Configuration  
Currently to use this someone will have to supply their own SSID and key then upload the code onto their Arduino.

## WebServer Configuration
Using the ESP8266WebServer library, the web server is very easily configured using callback functions.  

First define a server.
```C++
ESP8266WebServer server(80);
```
Then define routes that the server should respond to and their callbacks.
```C++
  server.on("/", handleRoot);
  server.on("/pump", handlePump);
  server.onNotFound(handleNotFound);
```
The callbacks just need to be accessible when compiling.


## Arduino libraries
This uses the following Arduino Libraries.
* ESP8266WiFi - ESP8266 Core WiFi Library
* ESP8266mDNS - Simple ESP8266 Multicast DNS for .local urls
* ESP8266WebServer - Local WebServer used to serve the configuration portal
* [WiFiManager](https://github.com/tzapu/WiFiManager) - WiFi Configuration Magic
* DNSServer - Local DNS Server used for redirecting all requests to the configuration portal

## Hardware BOM
The POC of this was built with the following BOM
* [SparkFun ESP32 Thing](https://www.sparkfun.com/products/13907)
* [Small Water Pump (12V)](https://www.amazon.com/gp/product/B06WW1W7W2)
* [SparkFun Beefcake Relay Control Kit](https://www.sparkfun.com/products/13815)


## Usefull Links
* [A beginners guide to the ESP8266](https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html)
* [Esp8266 Advanced Webserver Example](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/examples/AdvancedWebServer/AdvancedWebServer.ino)
