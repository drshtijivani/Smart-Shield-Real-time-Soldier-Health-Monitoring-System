
/*  PulseSensor Starter Project and Signal Tester
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=RbB8NSRa5X4
 *
 *
-------------------------------------------------------------
1) This shows a live human Heartbeat Pulse.
2) Live visualization in Arduino's Cool "Serial Plotter".
3) Blink an LED on each Heartbeat.
4) This is the direct Pulse Sensor's Signal.
5) A great first-step in troubleshooting your circuit and connections.
6) "Human-readable" code that is newbie friendly."

*/


//  Variables
#include <DHT.h>  
#include <ESP8266WiFi.h>
String apiKey = "NLS2PI9FG4VA9YCD";     //  Enter your Write API key here
const char *ssid =  "Visha";     // Enter your WiFi Name
const char *pass =  "vishhh321"; // Enter your WiFi Password
const char* server = "api.thingspeak.com";
#define DHTPIN 4          // GPIO Pin where the dht11 is connected
 DHT dht(DHTPIN, DHT11);
WiFiClient client;
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED = LED_BUILTIN;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 580;
void setup() 
{
       Serial.begin(115200); 
       delay(10);
       dht.begin();
       Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
       while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 }
void loop() 
{
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      Signal = analogRead(PulseSensorPurplePin);
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
                         if (client.connect(server,80))   
                      {  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(Signal);
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("Signal " + String(Signal));
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
           Serial.println("Waiting...");
    delay(1000);
}




