const int RPWM_Output = 5; // Arduino PWM output pin 5
const int LPWM_Output = 6; // Arduino PWM output pin 6
const int temperature_pin1 = A2; // Temperature sensor pin
const int temperature_pin2 = A3; // Temperature sensor pin
const int current_pin = A0; // Current sensor pin
const int Receiver_pin = 11; // Pin connected to the IR receiver

int motor_speed = 0; // Motor speed (0-255)
bool motor_running = false;
bool motor_direction = true; // true for forward, false for reverse
const int temperature_threshold = 70; // Temperature threshold in degrees Celsius
const float current_threshold = 18.0; // Current threshold in Amps
unsigned long previous_time = 0; // will store last time sensors were updated
const long interval = 5000; // interval at which to update sensors (milliseconds)


void setup() {
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  pinMode(temperature_pin1, INPUT);
  pinMode(temperature_pin2, INPUT);
  //pinMode(temperature_pin3, INPUT);
  pinMode(current_pin, INPUT);

  // Initialize motor to stop
  analogWrite(RPWM_Output, 0);
  analogWrite(LPWM_Output, 0);

  Serial.begin(9600); // Start serial communication for debugging
  Serial.println("Setup complete. Waiting for commands.");
}

void loop() {

  if (motor_running) {
    unsigned long current_time = millis();
    if (current_time - previous_time >= interval) {
      previous_time = current_time;

      float temperature1 = read_temperature(temperature_pin1);
      float temperature2 = read_temperature(temperature_pin2);
      //float temperature3 = read_temperature(temperature_pin3);
      float current = read_current();

      // Print sensor readings for debugging
      Serial.print("Temperature 1: ");
      Serial.print(temperature1);
      Serial.print(" °C, Temperature 2: ");
      Serial.print(temperature2);
      Serial.print(" °C, Current: ");
      Serial.print(current);
      Serial.println(" A");

      // Check for over temperature and over current conditions
      if (temperature1 > temperature_threshold || temperature2 > temperature_threshold) {
        stop_motor();
        Serial.println("Motor stopped due to high temperature!");
      }
      if (current > current_threshold) {
        stop_motor();
        Serial.println("Motor stopped due to high current!");
      }
    }
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.print("Command received: ");
    Serial.println(command);

    if (command == 'f') {
      start_motor(true); // Start motor in forward direction
    } else if (command == 'r') {
      start_motor(false); // Start motor in reverse direction
    } else if (command == 's') {
      stop_motor(); // Stop the motor
    } else if (command == '+') {
      if (motor_running) {
        increase_speed(); // Increase speed only if the motor is running
      }
    } else if (command == '-') {
      if (motor_running) {
        decrease_speed(); // Decrease speed only if the motor is running
      }
    }
  }
}

void start_motor(bool forward) {
  motor_running = true;
  motor_direction = forward;

  if (motor_speed == 0) {
    motor_speed = 64; // Start motor at a safe speed
  }

  update_motor_speed();

  if (forward) {
    Serial.println("Motor started in forward direction.");
  } else {
    Serial.println("Motor started in reverse direction.");
  }
}

void stop_motor() {
  motor_running = false;
  motor_speed = 0;
  analogWrite(RPWM_Output, 0);
  analogWrite(LPWM_Output, 0);
  Serial.println("Motor stopped.");
}

void increase_speed() {
  if (motor_speed < 255) {
    motor_speed = min(motor_speed + 64, 255); // Increase speed by 64, cap at 255
  }
  Serial.print("Motor speed increased to ");
  Serial.println(motor_speed);
  update_motor_speed();
}

void decrease_speed() {
  if (motor_speed > 0) {
    motor_speed = max(motor_speed - 64, 0); // Decrease speed by 64, bottom at 0
  }
  Serial.print("Motor speed decreased to ");
  Serial.println(motor_speed);
  update_motor_speed();
}

void update_motor_speed() {
  if (motor_direction) {
    analogWrite(RPWM_Output, motor_speed);
    analogWrite(LPWM_Output, 0);
  } else {
    analogWrite(RPWM_Output, 0);
    analogWrite(LPWM_Output, motor_speed);
  }
}

float read_temperature(int pin) {
  int sensor_value = analogRead(pin);
  float voltage = sensor_value * (5.0 / 1023.0); // Convert analog reading to voltage
  float temperature = voltage * 100.0; // LM35 outputs 10mV per degree Celsius

  if (temperature > 150.0) {
    temperature = -1; // Invalid reading
  }
  return temperature;
}

float read_current() {
  int sensor_value = analogRead(current_pin);
  float voltage = sensor_value * (5.0 / 1023.0); // Convert analog reading to voltage
  float current = (voltage - 2.5) / 0.066; // ACS712 30A sensor sensitivity is 66mV/A

  if (current < 0.1 && current > -0.1) {
    current = 0.0;
  }
  return current;
}
