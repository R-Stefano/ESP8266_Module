#include <ESP8266WiFi.h>

const char* ssid     = "wifiName";
const char* password = "wifiPassword";
String myIP;
WiFiClient myclientServer;
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
   //CONNECT TO WIFI
   Serial.begin(9600);
   WiFi.begin(ssid, password);

   Serial.print("Coonnecting");
   while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
   }
   Serial.println("");
   Serial.print("Connected, the ESP Module IP is ");
   myIP=WiFi.localIP().toString();
   Serial.println(myIP);

   server.begin();
}

String searchValue(String key, String str){
    int idx=str.indexOf(key);
    int idxStartValue=idx + key.length() + 1;
    int idxEndValue=str.indexOf("&", idxStartValue);
    String result=str.substring(idxStartValue, idxEndValue);
    
    //If the key is for the last value
    if(result.indexOf("HTTP")>0){
      idx=result.indexOf("HTTP");
      result=result.substring(0, idx-1);
    }
    //return just the value of the key passed as parameter
    return result;
}

void loop() {
  WiFiClient myclientServer=server.available();

  //If some device sended data to the ESP module
  if(myclientServer.available()){
    String req=myclientServer.readStringUntil('\r');
    Serial.println("\nThis is the complete request:");
    Serial.println(req);

    Serial.println("\nThis is the value of the data key required:");
    String value=searchValue("data3", req);
    Serial.println(value);

    String myResponse="ALL RIGHT BABY!";
    
    myclientServer.print("HTTP/1.1 200 OK\r\n");
    myclientServer.print("Access-Control-Allow-Origin: *\r\n"); 
    myclientServer.print("\r\n");
    myclientServer.print(myResponse);
    
  }
  delay(1000);
}
