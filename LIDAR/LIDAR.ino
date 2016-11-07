#include <Wire.h>
#include <LIDARLite.h>
#include <Servo.h>
#include <Stepper.h>
/*------------------------------------------------------------------------------

  LIDARLite Arduino Library
  GetDistanceI2c

  This example shows how to initialize, configure, and read distance from a
  LIDAR-Lite connected over the I2C interface.

  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND
  
  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

------------------------------------------------------------------------------*/


class Sweeper
{
  Servo servo; //the servo
  int pos; //current servo position
  int increment; // increment to move
  int updateInterval; //interval between updates
  unsigned long lastUpdate; //last updated position

public:
 Sweeper(int interval)
 {
  updateInterval = interval;
  increment = 1;
 } //end constructor

 void Attach(int pin)
 {
  servo.attach(pin);
 } //end attach

 void Detach()
 {
  servo.detach();
 } //end detach

 void Update()
 {
  if((millis()-lastUpdate) > updateInterval) // time to update
  {
    lastUpdate = millis();
    pos += increment;
    servo.write(pos);
    Serial.println(pos);
    if((pos >= 180) || ( pos<=0 )) //end of sweep
    {
      //reverse direction
      increment = -increment;
    }
  }
 }//end update
 
 }; //end class Sweeper

//global var
#define SERVO 9
#define pin0 2
#define pin1 3
#define pin2 4
#define pin3 5
#define NUMSTEPS 200
#define RPM 60

LIDARLite myLidarLite;
Sweeper sweeper1(90);
Stepper stepper(NUMSTEPS, pin0,pin1,pin2,pin3);
  
void setup()
{
  Serial.begin(115200); // Initialize serial connection to display distance readings
  sweeper1.Attach(SERVO);
  stepper.setSpeed(RPM);
  /*
    begin(int configuration, bool fasti2c, char lidarliteAddress)

    Starts the sensor and I2C.

    Parameters
    ----------------------------------------------------------------------------
    configuration: Default 0. Selects one of several preset configurations.
    fasti2c: Default 100 kHz. I2C base frequency.
      If true I2C frequency is set to 400kHz.
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  /*
    configure(int configuration, char lidarliteAddress)

    Selects one of several preset configurations.

    Parameters
    ----------------------------------------------------------------------------
    configuration:  Default 0.
      0: Default mode, balanced performance.
      1: Short range, high speed. Uses 0x1d maximum acquisition count.
      2: Default range, higher speed short range. Turns on quick termination
          detection for faster measurements at short range (with decreased
          accuracy)
      3: Maximum range. Uses 0xff maximum acquisition count.
      4: High sensitivity detection. Overrides default valid measurement detection
          algorithm, and uses a threshold value for high sensitivity and noise.
      5: Low sensitivity detection. Overrides default valid measurement detection
          algorithm, and uses a threshold value for low sensitivity and noise.
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */
  myLidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop()
{
  sweeper1.Update();
  stepper.step(NUMSTEPS);
  /*
    distance(bool biasCorrection, char lidarliteAddress)

    Take a distance measurement and read the result.

    Parameters
    ----------------------------------------------------------------------------
    biasCorrection: Default true. Take aquisition with receiver bias
      correction. If set to false measurements will be faster. Receiver bias
      correction must be performed periodically. (e.g. 1 out of every 100
      readings).
    lidarliteAddress: Default 0x62. Fill in new address here if changed. See
      operating manual for instructions.
  */

  // Take a measurement with receiver bias correction and print to serial terminal
  Serial.println(myLidarLite.distance());
  
  // Take 99 measurements without receiver bias correction and print to serial terminal
  for(int i = 0; i < 99; i++)
  {
    Serial.println(myLidarLite.distance(false));
  }
}
