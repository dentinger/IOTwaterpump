# IOTwaterpump
Arduino (ESP8266) controlled waterpump

## Overview
This code controls a small 12V waterpump via arduino based ESP8266.  The ESP8266 will register itself on the provided wireless network and then it is referenceable via http://pump.local/pump by any device also on the same network.

Currently to use this someone will have to supply their own SSID and key then upload the code onto their arduino.

The POC of this was built with the following BOM
* [SparkFun ESP32 Thing](https://www.sparkfun.com/products/13907) 
* [Small Water Pump (12V)](https://www.amazon.com/gp/product/B06WW1W7W2)
* [SparkFun Beefcake Relay Control Kit](https://www.sparkfun.com/products/13815)
