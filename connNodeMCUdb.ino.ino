#include <ESP8266WiFi.h>
#include <WifiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Wi-Fi setting connect to your smartphone Wi-Fi hotspot */
const char *ssid = "name_of_hotspot_here";
const char *password = "passwrod_hotspot_here";

/* Variable for taking out LM35 value */
String tempValue;
int analogValue;
int tempPin = A0;
float milliVolts;
float celcius;

/* Variable for sending data to server */
String postData;
int httpCode;
String payload;
void setup(){
delay(1000);
Serial.begin(115200);
WiFi.begin(ssid,password);
Serial.println("");
Serial.println("Connecting");

/* If Wi-Fi hotspot is not found, show ..... in serial monitor */
while(WiFi.status()!=WL_CONNECTED){
delay(500);
Serial.println(".");
}

/* If Wi-Fi hotspot is found, show IP address in serial monitor */
Serial.println("");
Serial.println("Connected to ");
Serial.println(ssid);
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void loop(){

/* Getting value from LM35 */
delay(5000);
analogValue = analogRead(tempPin);
milliVolts = (analogValue/1024.0)*3300;
celcius = milliVolts/10;
tempValue = String(celcius);
Serial.println(tempValue);

/* Sending LM35 value to server */
HTTPClient http;
postData = "tempValue=" + tempValue;
http.begin("http://172.20.10.5/dbInsert.php");
http.addHeader("Content-Type","application/x-www-form-urlencoded");
httpCode = http.POST(postData);
payload = http.getString();
Serial.println(httpCode); //Print HTTP return code
Serial.println(payload); //Print request response payload
http.end();
}
