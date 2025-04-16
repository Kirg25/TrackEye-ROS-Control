#include <ros.h>
#include <geometry_msgs/Twist.h>

// Motor A (left)
const int ENA = 3;
const int IN1 = 5;
const int IN2 = 6;

// Motor B (right)
const int ENB = 11;
const int IN3 = 9;
const int IN4 = 10;

// ROS node
ros::NodeHandle nh;

// Twist message callback
void cmdVelCallback(const geometry_msgs::Twist &cmd_msg) {
  if (cmd_msg.linear.x > 0) {
    // Move forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);  // Speed (0–255)
    analogWrite(ENB, 255);
  } else {
    // Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", cmdVelCallback);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10);
}
