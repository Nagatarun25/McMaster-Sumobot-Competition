#define IR_SENSOR 6
#define TRIG 3
#define ECHO 2

#define INT1 8  
#define INT2 9  
#define INT3 10 
#define INT4 11 

float distance = 0;
bool gameStarted = false;

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  delay(5000);
  gameStarted = true;
}

float readUltrasonicDistance() {
  long duration;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  return (duration * 0.0343) / 2;
}

bool isOnEdge() {
  int sensor_val = digitalRead(IR_SENSOR);
  return (sensor_val == LOW);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

void turnLeft() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

void loop() {
  if (!gameStarted) {
    return;
  }

  distance = readUltrasonicDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (isOnEdge()) {
    moveBackward();
    delay(500);
    turnRight();
    delay(500);
    stopMotors();
    return;
  }

  if (distance > 0 && distance <= 15) {
    moveBackward();
    delay(300);
    turnRight();
    delay(400);
    return;
  }

  if (distance > 15 && distance <= 30) {
    moveForward();
    delay(600);
    return;
  }

  if (distance > 30 && distance <= 60) {
    turnLeft();
    delay(500);
    return;
  }

  turnRight();
  delay(300);
}

