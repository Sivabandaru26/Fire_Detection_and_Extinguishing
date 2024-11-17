#define enA 10 // Enable1 L298 Pin enA
#define in1 9  // Motor1 L298 Pin in1
#define in2 8  // Motor1 L298 Pin in2
#define in3 7  // Motor2 L298 Pin in3
#define in4 6  // Motor2 L298 Pin in4
#define enB 5  // Enable2 L298 Pin enB
#define ir_R A0 // Right sensor
#define ir_F A1 // Front sensor
#define ir_L A2 // Left sensor
#define servo A4
#define pump A5

int Speed = 160; // Motor speed (0 to 255)
int s1, s2, s3;

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(ir_R, INPUT); // Declare fire sensor pin as input
  pinMode(ir_F, INPUT);
  pinMode(ir_L, INPUT);
  pinMode(enA, OUTPUT); // Motor control pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(servo, OUTPUT);
  pinMode(pump, OUTPUT);

  // Servo calibration to initial position
  for (int angle = 90; angle <= 140; angle += 5) {
    servoPulse(servo, angle);
  }
  for (int angle = 140; angle >= 40; angle -= 5) {
    servoPulse(servo, angle);
  }
  for (int angle = 40; angle <= 95; angle += 5) {
    servoPulse(servo, angle);
  }

  analogWrite(enA, Speed); // Motor speed
  analogWrite(enB, Speed);
  delay(500);
}

void loop() {
  s1 = analogRead(ir_R); // Read sensor values
  s2 = analogRead(ir_F);
  s3 = analogRead(ir_L);

  // Serial output for debugging
  Serial.print(s1);
  Serial.print("\t");
  Serial.print(s2);
  Serial.print("\t");
  Serial.println(s3);
  delay(50);

  // Check for fire detection and control actions
  if (s1 < 500) { // Fire detected on right sensor
    Stop();
    digitalWrite(pump, HIGH); // Turn on pump
    moveToFireRight(); // Move towards the fire detected by the right sensor
  }
  else if (s2 < 500) { // Fire detected on front sensor
    Stop();
    digitalWrite(pump, HIGH); // Turn on pump
    moveToFireFront(); // Move towards the fire detected by the front sensor
  }
  else if (s3 < 500) { // Fire detected on left sensor
    Stop();
    digitalWrite(pump, HIGH); // Turn on pump
    moveToFireLeft(); // Move towards the fire detected by the left sensor
  }
  else { // No fire detected
    digitalWrite(pump, LOW); // Turn off pump
    Stop(); // Stop the robot
  }

  delay(10); // Short delay for stability
}

void servoPulse(int pin, int angle) {
  int pwm = (angle * 11) + 500; // Convert angle to microseconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50); // Refresh cycle of servo
}

void moveToFireRight() {


  // Move robot right
  forward();
}

void moveToFireFront() {


  // Move robot forward
  forward();
}

void moveToFireLeft() {


  // Move robot left
  turnLeft();
}

void forward() {
  // Move motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  // Turn robot right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnLeft() {
  // Turn robot left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop() {
  // Stop motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
