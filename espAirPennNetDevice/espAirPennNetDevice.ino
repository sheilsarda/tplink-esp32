#include <WiFi.h>
#include "sliderJS.h"  // contains string "body" html code
#include "html510.h"


HTML510Server h(80);

const char* ssid = "AirPennNet-Device";
const char* password = "penn1740wifi";
volatile int dutyCycle = 0;
const int freq = 5; // sets frequency to 5 Hz
const int channel = 0; // sets pin channel to 0
const int res = 8; // sets max resolution of 13 for 5kHz

// const char *customNetworkName = "ESP32 Network";

void setup() {
  Serial.begin(115200);                                                  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(IPAddress(192, 168, 1, 177), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0)); 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");  Serial.println(myIP);      

  Serial.println("WiFi Connected"); 
  Serial.print("Use this URL to connect: http://");  
  Serial.print(WiFi.localIP()); Serial.println("/");
  
  h.begin();
}

void loop(){
  h.serve();
  
  delay(100);
}
