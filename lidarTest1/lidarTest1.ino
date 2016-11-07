#include <LIDARLite.h>

//global vars
#define SPKR 6 //piezo buzzer

int loud = 0; //loudness of tone
long dist = 0;

LIDARLite myLidarLite;
void setup() 
{
  Serial.begin(115200); 

  //default addr for lidar 0x62
  myLidarLite.begin(0, true); //default config, I2C 400kHz
  myLidarLite.configure(0); //balanced performance 
}

void loop() 
{
  dist = myLidarLite.distance(); //collect distance from module
  Serial.println(dist);
  //loud = map(dist,0,200,400,1500); //map distance to volume for buzzer
  tone(SPKR,200,50); //write distance to spkr pin.
  delay(dist);
}
