void setup() {
  Serial2.begin(19200);
  Serial.begin(115200);
  delay(500);
}
char valChar[15];

void loop() {
  readLaser();
}

void readLaser() {
  Serial2.print("D");
  while (!Serial2.available());
  String val = Serial2.readString();
  val.toCharArray(valChar,val.length());

  if (val.length() > 8){
     val.remove(0,2);
   }

  for (int i = 0 ; i < val.length() ;i++ ){
    if (valChar[i]=='m' ){
      val.remove(i-2,val.length());
      Serial2.println();
      Serial2.print("val :");
      Serial2.println(val);
      Serial.println("1,"+val);
      break ;
      }
    }
}


