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
bool shouldMove = false;  
bool reverseMode = false;  // NEW flag for reverse

void commandCallback(const std_msgs::String &msg) {
  command = msg.data;
  if (command == "F") {
    shouldMove = true;
    reverseMode = false;
    digitalWrite(LDIR, HIGH);  // Forward
    digitalWrite(RDIR, HIGH);
  } else if (command == "R") {
    shouldMove = true;
    reverseMode = true;
    digitalWrite(LDIR, LOW);   // Reverse
    digitalWrite(RDIR, LOW);
  } else if (command == "S") {
    shouldMove = false;
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

  digitalWrite(LENA, LOW);  // Enable motors
  digitalWrite(RENA, LOW);
  digitalWrite(LDIR, HIGH); // Default Forward
  digitalWrite(RDIR, HIGH);
}

void loop() {
  nh.spinOnce();

  if (shouldMove) {
    digitalWrite(LPUL, HIGH);
    digitalWrite(RPUL, HIGH);
    delayMicroseconds(10);
    digitalWrite(LPUL, LOW);
    digitalWrite(RPUL, LOW);
    delayMicroseconds(10);
  }
}
