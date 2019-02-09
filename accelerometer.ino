#include "I2Cdev.h"
#include "MPU6050.h"
#include "dht.h"
#include "Wire.h"

#define dht_apin A0 // Analog Pin sensor is connected to
int accelaration =  0 ;
int count = 0 ;
int state = 0 ;
char valChar[15];
unsigned long t1 , t2 = 0 ;
int RstPin = 7 ;


dht DHT;


#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#endif
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;

void setup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE 
  Fastwire::setup(400, true);
#endif
  Serial2.begin(19200); ///// Laser
  Serial.begin(115200); ////////Esp

  Serial1.begin(19200); //////////// Accelerometer
  accelgyro.initialize();
  pinMode(RstPin,OUTPUT);
}

void loop() {
  while (1) {
    switch (state) {
      case 0: {
          for (int i = 0 ; i < 5 ; i++) {
            accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

#ifdef OUTPUT_READABLE_ACCELGYRO
 
            Serial.println("ACC," + String((az * 0.061) / 1000));
           // delay(3000);
#endif

#ifdef OUTPUT_BINARY_ACCELGYRO
            Serial1.write((uint8_t)(az >> 8)); Serial1.write((uint8_t)(az & 0xFF));
            Serial1.write((uint8_t)(gz >> 8)); Serial1.write((uint8_t)(gz & 0xFF));
//            delay(10);
#endif

          }
         state = 1 ;
          delay(2000);
        }
      case 1 : {
          readLaser();
          state = 2 ;
        }
      case 2 : {
          DHT.read11(dht_apin);
          Serial.println("HUMIDITY," + String(DHT.humidity));
          Serial.println("TEMP," + String(DHT.temperature));
          state = 0 ;
          delay(4000);
        }
    }
  }
} 
  Serial2.flush();


//void readLaser() {
//
//
//  Serial2.print("D");
//  delay(2000);
//  while (!Serial2.available());
//  delay(10);
//  String val = Serial2.readString();
//  val.toCharArray(valChar, val.length());
//
//  if (val.length() > 8) {
//    val.remove(0,2);
//  }
//  delay(50);
//  for (int i = 0 ; i < val.length() ; i++ ) {
//    if (valChar[i] == 'm' ) {
//      val.remove(i - 2, val.length());
//      val.remove(val.indexOf(' '),1);
//      val.remove(val.indexOf(':'),1);
//      
//      Serial.println("LASER," + val);
////      
//      delay(2000);
//      break ; 
//    } 
//  }
//  Serial2.flush();
//}
//

