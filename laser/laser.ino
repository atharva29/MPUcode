#include <ESP8266WiFi.h>
int count = 0 ;
int counter = 0 ;
String ssid = "hot" ; // wifi ssid
String password = "123123123"; // wifi password
String ip = "192.168.43.100" ; // ip address of server
int port = 5000 ; // port of server
String val = "" ;
WiFiClient client1; //client object
byte temp = 1; 
char valChar[25];

char* string2char(String command) {
  if (command.length() != 0)
  {
    char*p = const_cast<char*>(command.c_str());
    return p;
  }
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  clientMode();
}


String readLaser() {
  Serial.print("D");
  while (!Serial.available());
  val = Serial.readString();
  delay(200);
//  val.toCharArray(valChar,val.length());
//
//  if (val.length() > 8){
//     val.remove(0,1);
//   } else {
//    return "";
//    }
//
//  for (int i = 0 ; i < val.length() ;i++ ){
//    if (valChar[i]=='m'){
//      val.remove(i-1,val.length()-2);
//      break ;
//    }
//  }
  return val ;
 }


void clientMode() {
  if (count == 0 ) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(string2char(ssid), string2char(password) );
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(250);
    }
    delay(100);
    while (!client1.connect(string2char(ip), port))
    {
      Serial.println("Connecting to server");
      delay(500);
    }
    count = 2 ; // go to count = 1
  }

  else if (count == 2 ) { // connection to server is successful
    if (client1.connected()) {
      if (client1.available() > 0 ) { // server is sending some data
        String Command = client1.readStringUntil('\n'); // read data
        if (Command == "D") {
           String val = readLaser();
           if (val != ""){
            client1.println(val);
           }
        }
      }
    } else { // if connection is lost then go to count = 0
      count = 0 ;
     }
  }
}
