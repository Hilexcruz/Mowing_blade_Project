const int RPWM_Output = 5; // Arduino PWM output pin 5
const int LPWM_Output = 6; // Arduino PWM output pin 6

int motorSpeed = 0; // Motor speed (0-255)
bool motorRunning = false;
bool motorDirection = true; // true for forward, false for reverse

void setup() {
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  
  // Initialize motor
  analogWrite(RPWM_Output, 0);
  analogWrite(LPWM_Output, 0);
  
  Serial.begin(9600); // Start serial communication for debugging
  Serial.println("Setup complete. Waiting for commands.");
}

void loop() {
  // Example: Checking for serial input to change speed or direction
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.print("Command received: ");
    Serial.println(command);
    
    if (command == 'f') {
      startMotor(true); // Start motor in forward direction
    } else if (command == 'r') {
      startMotor(false); // Start motor in reverse direction
    } else if (command == 's') {
      stopMotor(); // Stop the motor
    } else if (command == '+') {
      if (motorRunning) {
        increaseSpeed(); // Increase speed only if the motor is running
      }
    } else if (command == '-') {
      if (motorRunning) {
        decreaseSpeed(); // Decrease speed only if the motor is running
      }
    }
  }
}

void startMotor(bool forward) {
  motorRunning = true;
  motorDirection = forward;
  
  if (forward) {
    analogWrite(RPWM_Output, motorSpeed);
    analogWrite(LPWM_Output, 0);
    Serial.println("Motor started in forward direction.");
  } else {
    analogWrite(RPWM_Output, 0);
    analogWrite(LPWM_Output, motorSpeed);
    Serial.println("Motor started in reverse direction.");
  }
}

void stopMotor() {
  motorRunning = false;
  analogWrite(RPWM_Output, 0);
  analogWrite(LPWM_Output, 0);
  Serial.println("Motor stopped.");
}

void increaseSpeed() {
  if (motorSpeed < 255) {
    if (motorSpeed == 0) {
      motorSpeed = 64; // 25% of 255
    } else if (motorSpeed == 64) {
      motorSpeed = 128; // 50% of 255
    } else if (motorSpeed == 128) {
      motorSpeed = 191; // 75% of 255
    } else if (motorSpeed == 191) {
      motorSpeed = 255; // 100% of 255
    }
  }
  Serial.print("Motor speed increased to ");
  Serial.println(motorSpeed);
  if (motorDirection) {
    analogWrite(RPWM_Output, motorSpeed);
    analogWrite(LPWM_Output, 0);
  } else {
    analogWrite(RPWM_Output, 0);
    analogWrite(LPWM_Output, motorSpeed);
  }
}

void decreaseSpeed() {
  if (motorSpeed > 0) {
    if (motorSpeed == 255) {
      motorSpeed = 191; // 75% of 255
    } else if (motorSpeed == 191) {
      motorSpeed = 128; // 50% of 255
    } else if (motorSpeed == 128) {
      motorSpeed = 64; // 25% of 255
    } else if (motorSpeed == 64) {
      motorSpeed = 0; // 0% of 255
    }
  }
  Serial.print("Motor speed decreased to ");
  Serial.println(motorSpeed);
  if (motorDirection) {
    analogWrite(RPWM_Output, motorSpeed);
    analogWrite(LPWM_Output, 0);
  } else {
    analogWrite(RPWM_Output, 0);
    analogWrite(LPWM_Output, motorSpeed);
  }
}
