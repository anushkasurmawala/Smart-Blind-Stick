#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Ultrasonic Sensor Pin Assignments
#define TRIG_FRONT 2
#define ECHO_FRONT 7
#define TRIG_BACK 3
#define ECHO_BACK 8
#define TRIG_LEFT 4
#define ECHO_LEFT 9
#define TRIG_RIGHT 5
#define ECHO_RIGHT 10
#define TRIG_DOWN 6
#define ECHO_DOWN 11

// Vibration Motor Pin Assignments
#define VIBRATION_MOTOR_FRONT 12
#define VIBRATION_MOTOR_BACK A2
#define VIBRATION_MOTOR_LEFT A0
#define VIBRATION_MOTOR_RIGHT A1
#define BUZZER 13

// DFPlayer setup
SoftwareSerial mySerial(14, 15); // RX, TX (change if needed)
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  // Ultrasonic Sensor Pins
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_BACK, OUTPUT);
  pinMode(ECHO_BACK, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_DOWN, OUTPUT);
  pinMode(ECHO_DOWN, INPUT);

  // Motor Pins
  pinMode(VIBRATION_MOTOR_FRONT, OUTPUT);
  pinMode(VIBRATION_MOTOR_BACK, OUTPUT);
  pinMode(VIBRATION_MOTOR_LEFT, OUTPUT);
  pinMode(VIBRATION_MOTOR_RIGHT, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Serial and DFPlayer
  Serial.begin(9600);
  mySerial.begin(9600);
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer not found");
    while (true);
  }
  myDFPlayer.volume(20); // Set volume (0-30)
}

// Function to get distance from ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // cm
  return distance;
}

// Function to determine steps (1 to 5) based on distance
int getSteps(long distance) {
  if (distance < 10) return 1;
  else if (distance < 20) return 2;
  else if (distance < 30) return 3;
  else if (distance < 40) return 4;
  else return 5;
}

// Function to play footsteps and direction
void speakDirection(int steps, int directionFileNumber) {
  if (steps >= 1 && steps <= 5) {
    myDFPlayer.play(steps); // Play step count: 001–005.mp3
    delay(1500);            // Wait for number to play
    myDFPlayer.play(directionFileNumber); // Play direction: 010–012
    delay(2000);
  }
}

void loop() {
  long distanceFront = getDistance(TRIG_FRONT, ECHO_FRONT);
  long distanceBack = getDistance(TRIG_BACK, ECHO_BACK);
  long distanceLeft = getDistance(TRIG_LEFT, ECHO_LEFT);
  long distanceRight = getDistance(TRIG_RIGHT, ECHO_RIGHT);
  long distanceDown = getDistance(TRIG_DOWN, ECHO_DOWN);

  int threshold = 50; // cm

  // FRONT
  if (distanceFront < threshold) {
    digitalWrite(VIBRATION_MOTOR_FRONT, HIGH);
    int steps = getSteps(distanceFront);
    speakDirection(steps, 012); // 012 = "back"
  } else {
    digitalWrite(VIBRATION_MOTOR_FRONT, LOW);
  }

  // BACK
  if (distanceBack < threshold) {
    digitalWrite(VIBRATION_MOTOR_BACK, HIGH);
    int steps = getSteps(distanceBack);
    speakDirection(steps, 010); // 010 = "to the left" (example)
  } else {
    digitalWrite(VIBRATION_MOTOR_BACK, LOW);
  }

  // LEFT
  if (distanceLeft < threshold) {
    digitalWrite(VIBRATION_MOTOR_LEFT, HIGH);
    int steps = getSteps(distanceLeft);
    speakDirection(steps, 011); // 011 = "to the right"
  } else {
    digitalWrite(VIBRATION_MOTOR_LEFT, LOW);
  }

  // RIGHT
  if (distanceRight < threshold) {
    digitalWrite(VIBRATION_MOTOR_RIGHT, HIGH);
    int steps = getSteps(distanceRight);
    speakDirection(steps, 010); // 010 = "to the left"
  } else {
    digitalWrite(VIBRATION_MOTOR_RIGHT, LOW);
  }

  // DOWN
  if (distanceDown > 50) {
    digitalWrite(BUZZER, HIGH);
    myDFPlayer.play(013); // 013 = "pothole ahead"
    delay(2000);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  delay(500);
}