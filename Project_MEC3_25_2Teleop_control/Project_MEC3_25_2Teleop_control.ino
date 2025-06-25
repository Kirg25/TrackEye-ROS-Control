#include <ros.h>
#include <std_msgs/String.h>

const int LPUL = 2;  // Left Pulse
const int LDIR = 3;  // Left Direction
const int LENA = 4;  // Left Enable

const int RPUL = 5;  // Right Pulse
const int RDIR = 6;  // Right Direction
const int RENA = 7;  // Right Enable

ros::NodeHandle nh;
String command = "";  
bool shouldMove = false;  // Flag to control continuous movement

void commandCallback(const std_msgs::String &msg) {
  command = msg.data;
  if (command == "F") {
    shouldMove = true;  // Enable continuous movement
    //digitalWrite(LENA, LOW);  // Enable motors
    //digitalWrite(RENA, LOW);
  } else if (command == "S") {
    shouldMove = false;  // Stop movement
    //digitalWrite(LENA, HIGH);  // Disable motors (optional, can also just stop pulses)
    //digitalWrite(RENA, HIGH);
  }
}

ros::Subscriber<std_msgs::String> sub("motor_command", &commandCallback);

void setup() {
  nh.initNode();
  nh.subscribe(sub);

  pinMode(LPUL, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(LENA, OUTPUT);
  pinMode(RPUL, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RENA, OUTPUT);

  digitalWrite(LENA, LOW);  // Enable by default
  digitalWrite(RENA, LOW);
  digitalWrite(LDIR, HIGH);  // Set direction (HIGH = Forward)
  digitalWrite(RDIR, HIGH);
}

void loop() {
  nh.spinOnce();  // Check for new commands

  if (shouldMove) {
    // Generate continuous pulses while shouldMove is true
    digitalWrite(LPUL, HIGH);
    digitalWrite(RPUL, HIGH);
    delayMicroseconds(10);  // Controls speed (lower = faster)
    digitalWrite(LPUL, LOW);
    digitalWrite(RPUL, LOW);
    delayMicroseconds(10);
  }
}
