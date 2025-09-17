#include <ros.h>
#include <std_msgs/String.h>

const int LPUL = 2;  // Left Pulse
const int LDIR = 3;  // Left Direction
const int LENA = 4;  // Left Enable

const int RPUL = 5;  // Right Pulse
const int RDIR = 6;  // Right Direction
const int RENA = 7;  // Right Enable

// --- Step timing & ramp control ---
unsigned long lastStepTime = 0;
unsigned long currentDelay = 2000;      // start delay between steps (us) -> slower = easier start
const unsigned long minDelay = 300;     // target fastest delay (us) -> lower = faster
const unsigned long accelStep = 20;     // how much to reduce delay each step
const unsigned long pulseWidth = 10;    // step pulse width (us)


ros::NodeHandle nh;
String command = "";  
bool shouldMove = false;  
bool reverseMode = false;  // NEW flag for reverse

void commandCallback(const std_msgs::String &msg) {
  command = msg.data;
  if (command == "F") {
    shouldMove = true;
    digitalWrite(LDIR, HIGH); // Forward
    digitalWrite(RDIR, HIGH);
  } else if (command == "R") {
    shouldMove = true;
    digitalWrite(LDIR, LOW);  // Reverse
    digitalWrite(RDIR, LOW);
  } else if (command == "S") {
    shouldMove = false;  // Stop movement
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
    reverseMode = false;
    digitalWrite(LDIR, HIGH);  // Forward
    digitalWrite(RDIR, HIGH);
  pinMode(RDIR, OUTPUT);
  pinMode(RENA, OUTPUT);

  digitalWrite(LENA, LOW);  // Enable motors
  digitalWrite(RENA, LOW);
  digitalWrite(LDIR, HIGH); // Default Forward
  digitalWrite(RDIR, HIGH);
}

void loop() {
  nh.spinOnce();  // Check for new commands

  unsigned long now = micros();

  if (shouldMove) {

    // gradually ramp down currentDelay toward minDelay
    if (currentDelay > minDelay) {
      // reduce delay by accelStep but avoid going below minDelay
      if (currentDelay - accelStep > minDelay) currentDelay -= accelStep;
      else currentDelay = minDelay;
    }

    // stepper timing (non-blocking except for short pulseWidth)
    if (now - lastStepTime >= currentDelay) {
      // generate pulse
      digitalWrite(LPUL, HIGH);
      digitalWrite(RPUL, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(LPUL, LOW);
      digitalWrite(RPUL, LOW);

      lastStepTime = micros(); // reset after pulse
    }

  } else {
    // We're stopped: reset ramp so next start is soft
    if (currentDelay < 2000) currentDelay = 2000; // initial slow start value; tune as needed
  }
}

