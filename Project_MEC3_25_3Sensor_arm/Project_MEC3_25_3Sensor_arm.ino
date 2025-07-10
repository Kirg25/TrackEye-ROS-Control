#include <ros.h>
#include <std_msgs/String.h>

// --- Stepper Motor Pins ---
const int STEP_LINEAR = 10;
const int DIR_LINEAR = 11;

// --- Drive Motor Pins  ---
const int LPUL = 2;
const int LDIR = 3;
const int LENA = 4;

const int RPUL = 5;
const int RDIR = 6;
const int RENA = 7;

ros::NodeHandle nh;

// Linear actuator control
volatile bool linearMoving = false;
volatile bool linearDirection = true;  // true = extend, false = retract

// Timing variables
unsigned long moveStartMillis = 0;
const unsigned long moveDuration = 5000;  // 5 seconds duration

unsigned long lastStepMicros = 0;
const unsigned int stepInterval = 200;  // Speed control (lower = faster)

void commandCallback(const std_msgs::String &msg) {
  String cmd = msg.data;

  if (cmd == "EXTEND") {
    digitalWrite(DIR_LINEAR, HIGH);
    linearDirection = true;
    linearMoving = true;
    moveStartMillis = millis();
  } else if (cmd == "RETRACT") {
    digitalWrite(DIR_LINEAR, LOW);
    linearDirection = false;
    linearMoving = true;
    moveStartMillis = millis();
  } else if (cmd == "STOP_LINEAR") {
    linearMoving = false;
    digitalWrite(STEP_LINEAR, LOW);
  } else if (cmd == "F") {
    digitalWrite(LPUL, HIGH); digitalWrite(RPUL, HIGH);
    delayMicroseconds(10);
    digitalWrite(LPUL, LOW); digitalWrite(RPUL, LOW);
  } else if (cmd == "S") {
    digitalWrite(LPUL, LOW); digitalWrite(RPUL, LOW);
  }
}

ros::Subscriber<std_msgs::String> sub("motor_command", &commandCallback);

void setup() {
  nh.initNode();
  nh.subscribe(sub);

  // Stepper motor setup
  pinMode(STEP_LINEAR, OUTPUT);
  pinMode(DIR_LINEAR, OUTPUT);
  digitalWrite(STEP_LINEAR, LOW);
  digitalWrite(DIR_LINEAR, LOW);

  // Drive motor setup
  pinMode(LPUL, OUTPUT); pinMode(LDIR, OUTPUT); pinMode(LENA, OUTPUT);
  pinMode(RPUL, OUTPUT); pinMode(RDIR, OUTPUT); pinMode(RENA, OUTPUT);
  digitalWrite(LENA, LOW); digitalWrite(RENA, LOW);
  digitalWrite(LDIR, HIGH); digitalWrite(RDIR, HIGH);
}

void loop() {
  unsigned long nowMicros = micros();
  unsigned long nowMillis = millis();

  if (linearMoving && (nowMillis - moveStartMillis < moveDuration)) {
    if (nowMicros - lastStepMicros >= stepInterval) {
      digitalWrite(STEP_LINEAR, HIGH);
      delayMicroseconds(10);
      digitalWrite(STEP_LINEAR, LOW);
      lastStepMicros = nowMicros;
    }
  } else if (linearMoving) {
    // Stop after 5 seconds
    linearMoving = false;
    digitalWrite(STEP_LINEAR, LOW);
  }

  nh.spinOnce();
  delay(1);
}
