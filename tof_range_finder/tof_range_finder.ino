#include <ros.h>
#include <std_msgs/UInt8.h>

#include <Wire.h>

#include <SFE_VL6180X.h>

/*const float GAIN_1    = 1.01;  // Actual ALS Gain of 1.01
const float GAIN_1_25 = 1.28;  // Actual ALS Gain of 1.28
const float GAIN_1_67 = 1.72;  // Actual ALS Gain of 1.72
const float GAIN_2_5  = 2.6;   // Actual ALS Gain of 2.60
const float GAIN_5    = 5.21;  // Actual ALS Gain of 5.21
const float GAIN_10   = 10.32; // Actual ALS Gain of 10.32
const float GAIN_20   = 20;    // Actual ALS Gain of 20
const float GAIN_40   = 40;    // Actual ALS Gain of 40
*/
#define VL6180X_ADDRESS 0x29

VL6180xIdentification identification;
VL6180x sensor(VL6180X_ADDRESS);

ros::NodeHandle  nh;
std_msgs::UInt8 distance_msg;
ros::Publisher distance_publisher("tof_range_finder", &distance_msg);

void setup()
{
  //: ros initialization:
  nh.initNode();
  nh.advertise(distance_publisher);

  //: sensor initialization:
  Wire.begin(); //Start I2C library
  delay(100); // delay .1s
  sensor.getIdentification(&identification); // Retrieve manufacture info from device memory
  //fixme?
  //? printIdentification(&identification); // Helper function to print all the Module information

  if(sensor.VL6180xInit() != 0){
    //fixme: use ros to report an error? 
    //Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
  }

  sensor.VL6180xDefautSettings(); //Load default settings to get started.
  delay(1000); // delay 1s
}

void loop() {
  //: get sensor reading and broadcast:
  distance_msg.data = sensor.getDistance();
  distance_publisher.publish( &distance_msg);
  nh.spinOnce();
  delay(1000);
}

