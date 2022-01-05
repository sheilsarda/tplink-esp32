/*
 * MEAM510 HTML510 example w/LED
 * March 2021
 * 
 * Mark Yim
 * University of Pennsylvania
 * copyright (c) 2021 All Rights Reserved
 */
 
#include <WiFi.h> 
#include "html510.h"

#define LEDPIN 21

const char* ssid     = "TP-Link_05AF";
const char* password = "47543454";
//const char* ssid     = "yourhomeSSID";
//const char* password = "yourhomesasword";

HTML510Server h(80);              

const char body[] PROGMEM = R"===(
<!DOCTYPE html>
<html><body>
<H1>
<a href="/H">Turn ON</a> LED.<br>
<a href="/L">Turn OFF</a> LED.<br>
<span id="somelabel">  </span> <br>

</H1>
<button type="button" onclick="hit()"> mybutton </button>
</body>
<script>
function hit() {
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "hit", true);
  xhttp.send();
}  

setInterval(updateLabel,2000);

function updateLabel() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("somelabel").innerHTML =   
             this.responseText;
    }
  };
  xhttp.open("GET", "LEDstate", true);
  xhttp.send();
}

</script>

</html>
)===";

/*****************/
/* web handler   */
void handleRoot(){
  h.sendhtml(body);
}

void handleH(){
  digitalWrite(LEDPIN, HIGH);  // LED ON  
  h.sendhtml(body);
}                    
                     
void handleL(){
  digitalWrite(LEDPIN, LOW);  // LED ON  
  h.sendhtml(body);
}

void handleHit(){
  static int toggle;
  if (++toggle%2)  digitalWrite(LEDPIN,HIGH);
  else digitalWrite(LEDPIN,LOW);
  h.sendplain(""); // acknowledge         
}

void handleLEDstate(){
  String s = "LED state is "+String(digitalRead(LEDPIN));
  h.sendplain(s);
}


void setup() {
  Serial.begin(115200);                                             
  pinMode(LEDPIN, OUTPUT);
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, password);
  WiFi.config(IPAddress(192, 168, 1, 6),
              IPAddress(192, 168, 1, 1),
              IPAddress(255, 255, 255, 0));
              
  while(WiFi.status()!= WL_CONNECTED ) { 
    delay(500);
    Serial.print("."); 
  }
  Serial.println("WiFi connected"); 
  h.begin();
  
  h.attachHandler("/H",handleH);
  h.attachHandler("/L",handleL);
  h.attachHandler("/ ",handleRoot);
  h.attachHandler("/hit",handleHit);
  h.attachHandler("/LEDstate",handleLEDstate);

}

void loop(){
  h.serve();
  delay(1);
}
