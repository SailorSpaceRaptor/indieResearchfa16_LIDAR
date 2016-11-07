//#include <Servo.h>
//
//class Sweeper
//{
//  Servo servo; //the servo
//  int pos; //current servo position
//  int increment; // increment to move
//  int updateInterval; //interval between updates
//  unsigned long lastUpdate; //last updated position
//
//public:
// Sweeper(int interval)
// {
//  updateInterval = interval;
//  increment = 1;
// } //end constructor
//
// void Attach(int pin)
// {
//  servo.attach(pin);
// } //end attach
//
// void Detach()
// {
//  servo.detach();
// } //end detach
//
// void Update()
// {
//  if((millis()-lastUpdate) > updateInterval) // time to update
//  {
//    lastUpdate = millis();
//    pos += increment;
//    servo.write(pos);
//    Serial.println(pos);
//    if((pos >= 180) || ( pos<=0 )) //end of sweep
//    {
//      //reverse direction
//      increment = -increment;
//    }
//  }
// }//end update
// 
// }; //end class Sweeper

