// Line Following Robot with 3 IR Sensors, 2 Motors, and L298N Motor Driver

// Motor A
int motor1A = 2; // L298N module input 1
int motor1B = 3; // L298N module input 2

// Motor B
int motor2A = 4; // L298N module input 3
int motor2B = 5; // L298N module input 4

// IR Sensor Pins
int sensorLeft = 8;
int sensorCenter = 9;
int sensorRight = 10;

void setup() {
  // Motor Pins Setup
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // IR Sensor Pins Setup
  pinMode(sensorLeft, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight, INPUT);
}

long previous_time = 0;
long duration = 1000;
int done = 0;

void loop() {
  int leftValue = digitalRead(sensorLeft);
  int centerValue = digitalRead(sensorCenter);
  int rightValue = digitalRead(sensorRight);

  // ALL CASES FOR THE ROBOT

  // CASE 1 --> HAVE 3 PATHS (ALL SENSORS ARE ON BLACK LINE) :

  if (leftValue == LOW && centerValue == LOW && rightValue == LOW) {
    moveForward();
  }

  // CASE 2 --> HAVE 2 PATHS (LEFT BLACK , CENTRE BLACK AND RIGHT WHITE):
  else if (leftValue == LOW && centerValue == LOW && rightValue == HIGH) {
    moveForward();
  }

  // CASE 3 --> HAVE 2 PATHS (LEFT WHITE , CENTRE BLACK AND RIGHT BLACK):
  else if (leftValue == HIGH && centerValue == LOW && rightValue == LOW) {
    moveForward();
  }


  // CASE 4 --> HAVE 2 PATHS (LEFT BLACK , CENTRE BLACK AND RIGHT WHITE):
  else if (leftValue == LOW && centerValue == HIGH && rightValue == LOW) {
    moveRandomLeftRight();
  }

  // CASE 5 --> HAVE 1 PATHS (LEFT WHITE , CENTRE WHITE AND RIGHT BLACK):
  else if (leftValue == HIGH && centerValue == HIGH && rightValue == LOW) {
    turnRight();
  }

  // CASE 6 --> HAVE 1 PATHS (LEFT BLACK , CENTRE WHITE AND RIGHT WHITE):
  else if (leftValue == LOW && centerValue == HIGH && rightValue == HIGH) {
    turnLeft();
  }

  // CASE 7 --> HAVE 1 PATHS (LEFT BLACK , CENTRE WHITE AND RIGHT WHITE):
  else if (leftValue == HIGH && centerValue == LOW && rightValue == HIGH) {
    moveForward();
  }

  // CASE 8 --> HAVE 1 PATHS (LEFT BLACK , CENTRE WHITE AND RIGHT WHITE):
  else if (leftValue == HIGH && centerValue == HIGH && rightValue == HIGH) {

    if (done == 0){
      long cur_time = millis();
      previous_time = cur_time;
      done = 1;
      continue;
    }
    if (done == 1){
      long cur_time = millis();
      if ((cur_time - previous_time) > duration){
        stopMotors();
      }
      else {
        continue;
      }
    }
    
  }

  if (done == 1){
    done == 0;
  }

  else {
    stopMotors();
  }
}



void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void moveBackward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void turnLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void turnRight() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void stopMotors() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}
