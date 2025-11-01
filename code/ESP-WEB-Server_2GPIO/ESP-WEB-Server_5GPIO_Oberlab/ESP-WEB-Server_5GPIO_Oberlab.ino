/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
  Funktion: ESP32 WEB Server 5 GPOI 5 Slider //A00
  Angepasst an die Oberlab Header Platine
  
**************************************************************************************************
  Version: 18.12.2022
---------------------------------------------------------------      
*************************************************************************************************
  Board: ESP32vn IoT UNO
**************************************************************************************************
  C++ Arduino IDE V1.8.19
**************************************************************************************************
  Einstellungen:
  https://dl.espressif.com/dl/package_esp32_index.json
  http://dan.drown.org/stm32duino/package_STM32duino_index.json
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json

 **************************************************************************************************/

#include <WiFi.h>

// WLAN-Daten
const char* ssid = "Oberlab2G";
const char* password = "UrlaubinBALREBO#!1";

WiFiServer server(80);
String header;

// GPIO-Status
String output2State =  "off";
String output4State =  "off";
String output35State = "off";
String output34State = "off";
String output36State = "off";
String output39State = "off";

// GPIO-Pins
const int output2   = 2; // interne LED
const int output4   = 4; 
const int output35 = 35; 
const int output34 = 34; 
const int output36 = 36;   
const int output39 = 39;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
   pinMode(output2,  OUTPUT);
   pinMode(output4, OUTPUT);
   pinMode(output35, OUTPUT);
   pinMode(output34, OUTPUT);
   pinMode(output36, OUTPUT);
   pinMode(output39, OUTPUT);

  digitalWrite(output2,  LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output35, LOW);
  digitalWrite(output34, LOW);
  digitalWrite(output36, LOW);
  digitalWrite(output39, LOW);

  Serial.print("Verbinde mit WLAN: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWLAN verbunden!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("GPIO schalten: ");
    String currentLine = "";
    header = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // ---- HTTP-Antwort ----
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // ---- Steuerlogik ----

            //GPIO2  
            if (header.indexOf("GET /2/on") >= 0) {
              output2State = "on"; digitalWrite(output2, HIGH);
              Serial.println("GPIO 2 an");
            } else if (header.indexOf("GET /2/off") >= 0) {
              output2State = "off"; digitalWrite(output2, LOW);
              Serial.println("GPIO 2 aus");

            //GPIO14  
            } else if (header.indexOf("GET /4/on") >= 0) {
              output4State = "on"; digitalWrite(output4, HIGH);
              Serial.println("GPIO 4 an");
            } else if (header.indexOf("GET /4/off") >= 0) {
              output4State = "off"; digitalWrite(output4, LOW);
              Serial.println("GPIO 4 aus");

            //GPIO35 
            } else if (header.indexOf("GET /35/on") >= 0) {
              output35State = "on"; digitalWrite(output35, HIGH);
              Serial.println("GPIO 35 an");
            } else if (header.indexOf("GET /35/off") >= 0) {
              output35State = "off"; digitalWrite(output35, LOW);
              Serial.println("GPIO 35 aus"); 

            //GPIO34  
            } else if (header.indexOf("GET /34/on") >= 0) {
              output34State = "on"; digitalWrite(output34, HIGH);
              Serial.println("GPIO 34 an");
            } else if (header.indexOf("GET /34/off") >= 0) {
              output34State = "off"; digitalWrite(output34, LOW);
              Serial.println("GPIO 34 aus"); 

            //GPIO36
            } else if (header.indexOf("GET /36/on") >= 0) {
              output36State = "on"; digitalWrite(output36, HIGH);
              Serial.println("GPIO 36 an");
            } else if (header.indexOf("GET /36/off") >= 0) {
              output36State = "off"; digitalWrite(output36, LOW);
              Serial.println("GPIO 36 aus");

            //GPIO39  
            } else if (header.indexOf("GET /39/on") >= 0) {
              output39State = "on"; digitalWrite(output39, HIGH);
              Serial.println("GPIO 39 an");
            } else if (header.indexOf("GET /39/off") >= 0) {
              output39State = "off"; digitalWrite(output39, LOW);
              Serial.println("GPIO 39 aus");                                        
              
         }

            // ---- HTML-Seite ----
            client.println("<!DOCTYPE html><html><head>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>");
            client.println("html{font-family:Helvetica;text-align:center;}");
            client.println(".switch{position:relative;display:inline-block;width:80px;height:44px;}");
            client.println(".switch input{display:none;}");
            client.println(".slider{position:absolute;cursor:pointer;top:0;left:0;right:0;bottom:0;"
                           "background-color:#00cc0c;transition:.4s;border-radius:34px;}");
            client.println(".slider:before{position:absolute;content:'';height:36px;width:36px;"
                           "left:4px;bottom:4px;background:white;transition:.4s;border-radius:50%;}");
            client.println("input:checked + .slider{background-color:#fb0052;}"); 
            client.println("input:checked + .slider:before{transform:translateX(36px);}");
            client.println("</style></head><body>");
            client.println("<h1>KHF Webserver</h1>");

            // GPIO 2
            client.println("<p>GPIO 2 int.LED"  "</p>");
            client.println("<label class=\"switch\">");
            client.print("<input type=\"checkbox\" id=\"gpio2\" ");
            if (output2State == "on") client.print("checked");
            client.println(" onchange=\"toggle(this,2)\">");
            client.println("<span class=\"slider\"></span></label>"); 

            // GPIO 4
            client.println("<p>GPIO 4"  "</p>");
            client.println("<label class=\"switch\">");
            client.print("<input type=\"checkbox\" id=\"gpio4\" ");
            if (output4State == "on") client.print("checked");
            client.println(" onchange=\"toggle(this,4)\">");
            client.println("<span class=\"slider\"></span></label>");   

            // GPIO 35
            client.println("<p>GPIO 35"  "</p>");
            client.println("<label class=\"switch\">");
            client.print("<input type=\"checkbox\" id=\"gpio35\" ");
            if (output35State == "on") client.print("checked");
            client.println(" onchange=\"toggle(this,35)\">");
            client.println("<span class=\"slider\"></span></label>"); 

            // GPIO 34
            client.println("<p>GPIO 34"  "</p>");
            client.println("<label class=\"switch\">");
            client.print("<input type=\"checkbox\" id=\"gpio34\" ");
            if (output34State == "on") client.print("checked");
            client.println(" onchange=\"toggle(this,34)\">");
            client.println("<span class=\"slider\"></span></label>");       

            // GPIO 36
            client.println("<p>GPIO 36"  "</p>");
            client.println("<label class=\"switch\">");
            client.print("<input type=\"checkbox\" id=\"gpio36\" ");
            if (output36State == "on") client.print("checked");
            client.println(" onchange=\"toggle(this,36)\">");
            client.println("<span class=\"slider\"></span></label><br><br>");

            // GPIO 39
            client.println("<p>GPIO 39"  "</p>");
            client.println("<label class=\"switch\">");
            client.print("<input type=\"checkbox\" id=\"gpio39\" ");
            if (output39State == "on") client.print("checked");
            client.println(" onchange=\"toggle(this,39)\">");
            client.println("<span class=\"slider\"></span></label>");                                                

            // ---- JavaScript ----
            client.println("<script>");
            client.println("function toggle(el,pin){");
            client.println("var state = el.checked ? 'on' : 'off';");
            client.println("fetch('/'+pin+'/'+state);");
            client.println("}");
            client.println("</script>");
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

  }
}
