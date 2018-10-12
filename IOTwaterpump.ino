#include <ESP8266WiFi.h> //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <ESP8266mDNS.h>
#include <DNSServer.h> //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = 5; // Thing's onboard, green LED
const int PUMP_PIN = 13; //Digital pin to keep on for pump;

///////////////////
///app constants///
///////////////////
const int PUMP_ON = 1;
const int PUMP_OFF = 0;

int state=PUMP_OFF;


ESP8266WebServer server(80);

void setup() 
{
  initHardware();
  
  setupWiFi();
  //start a local web server and define how it responds to requests  
  server.on("/", handleRoot); 
  server.on("/pump", handlePump);
  server.onNotFound(handleNotFound);
  server.begin();
  
  setupMDNS();
}
void handlePump() {
  if (state == PUMP_ON) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(PUMP_PIN, HIGH);
  }
  if (state == PUMP_OFF) {
    digitalWrite(PUMP_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    
  }
  state = !state;

  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleRoot() {


  char* current_status = "OFF";
  if(state == PUMP_ON) {
   current_status = "ON";
  }
  char temp[400];
  
  snprintf(temp, 400,
          "<html>  <head>   <meta http-equiv='refresh' content='5'/>   <title>IOT Pump</title>   <style> \
     body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
   </style> \
 </head> \
 <body> \
   <h1>Welcome to the IOT Pump</h1> \
   <h2>Pump is currently %s </h2> \
   <form action=\"/pump\" method=\"POST\"><input type=\"submit\" value=\"Toggle Pump\"></form>\
 </body>\
</html>",
  current_status
         );

  server.send(200, "text/html", temp);   // Send HTTP status 200 (Ok) and send some html to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}


void setupMDNS()
{
  // Call MDNS.begin(<domain>) to set up mDNS to point to

  if (!MDNS.begin("pump")) 
  {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();

  //Use the WiFIManager to prompt for SSID and creds
  WiFiManager wifiManager;
  String AP_NAME = "Pump Thing "+macID;
  char* buf;
  AP_NAME.toCharArray(buf, AP_NAME.length());
//first parameter is name of access point, second is the password (if present)
  wifiManager.autoConnect(buf);
}


void initHardware()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(LED_PIN, HIGH);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
}

void loop() 
{
  server.handleClient(); 

}



