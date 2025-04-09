#include <ros.h>
#include <std_msgs/String.h>

// Define motor pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 9
#define ENB 10

ros::NodeHandle nh;

// Callback function for the ROS topic
void commandCallback(const std_msgs::String& msg) {
  // Print the raw message data
  Serial.print("Raw message: ");
  Serial.println(msg.data);

  // Print the length of the message
  Serial.print("Message length: ");
  Serial.println(strlen(msg.data)); // Use strlen() for C-style strings

  // Process the command
  if (strcmp(msg.data, "forward") == 0) { // Use strcmp() for string comparison
    Serial.println("Executing: forward");
    // Move forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255); // Set speed
    analogWrite(ENB, 255);
  } else if (strcmp(msg.data, "stop") == 0) { // Use strcmp() for string comparison
    Serial.println("Executing: stop");
    // Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  } else {
    Serial.println("Unknown command");
  }
}

// Create a ROS subscriber
ros::Subscriber<std_msgs::String> sub("robot_command", &commandCallback);

void setup() {
  // Initialize motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(57600);

  // Initialize ROS node
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10); // Small delay to avoid buffer overflow
}