#include <ros.h>
#include <std_msgs/String.h>

// Define Arduino pins connected to Hb808c
const int LPUL = 2;  // Pulse pin
const int LDIR = 3;  // Direction pin
const int LENA = 4;  // Enable pin

const int RPUL = 5;  // Pulse pin
const int RDIR = 6;  // Direction pin
const int RENA = 7;  // Enable pin

ros::NodeHandle nh;
String command = "";  // Variable to store received command

// Callback function for ROS subscriber
void commandCallback(const std_msgs::String &msg) {
  command = msg.data;
}

ros::Subscriber<std_msgs::String> sub("motor_command", &commandCallback);

void setup() {
  nh.initNode();
  nh.subscribe(sub);

  // Set pin modes
  pinMode(LPUL, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(LENA, OUTPUT);
  pinMode(RPUL, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RENA, OUTPUT);

  // Enable the driver initially
  digitalWrite(LENA, LOW);  // LOW to enable, HIGH to disable
  digitalWrite(RENA, LOW);  // LOW to enable, HIGH to disable
}

void loop() {
  nh.spinOnce();  // Process incoming ROS messages

  if (command == "F") {
    // Re-enable motors when moving forward
    digitalWrite(LENA, LOW);
    digitalWrite(RENA, LOW);
    moveForward();
    command = "";  // Clear command after execution
  } else if (command == "S") {
    stopMotors();
    command = "";  // Clear command after execution
  }
}

void moveForward() {
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);

  for (int i = 0; i < 4000; i++) {  // Adjust steps for distance/speed
    digitalWrite(LPUL, HIGH);
    delayMicroseconds(10); // Adjust pulse width for speed
    digitalWrite(LPUL, LOW);
    delayMicroseconds(10);
    digitalWrite(RPUL, HIGH);
    delayMicroseconds(10);
    digitalWrite(RPUL, LOW);
    delayMicroseconds(10);
  }
}

void stopMotors() {
  // Disable motor driver to stop completely
  digitalWrite(LENA, HIGH);  // HIGH to disable
  digitalWrite(RENA, HIGH);  // HIGH to disable
}
