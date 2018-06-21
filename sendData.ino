#include <ESP8266WiFi.h>

const char* ssid     = "Vodafone-34656602";
const char* password = "juventus";
String host="demiledge.com";
String page="/espTutorial.php";
String myIP;
WiFiClient myclient;

void setup() {
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

   //ESTABLISH CONNECTION WITH THE SERVER
   int serverPort=80;
   
   Serial.print("Establing connect to the server");
   while(!myclient.connect(host, serverPort)){
     Serial.print(".");
     delay(300);
   }
   Serial.println("");
   Serial.println("Connected successfully to "+host);
}

void loop(){
  //SEND DATA (IP, RANDOM NUMBER) TO THE SERVER EVERY 3 SECONDS
  int numb=random(1000);
  
  Serial.println("Sending information to the server..");
  String data="clientIP="+ myIP+"&number="+numb;

  String postRequest=
  "POST " + page + " HTTP/1.1\r\n" + 
  "Host: " + host + "\r\n" + 
  "Content-Length: " + data.length() + "\r\n"+
  "Content-Type: application/x-www-form-urlencoded\r\n" + 
  "\r\n" + 
  data;
  
  myclient.print(postRequest);

  delay(3000);
}

