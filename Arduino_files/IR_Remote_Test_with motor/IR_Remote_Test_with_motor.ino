#include <IRremote.hpp> // include the library
// Define IR codes
const unsigned long forward_code = 0xE718FF00;
const unsigned long reverse_code = 0xAD52FF00;
const unsigned long stop_code = 0xE619FF00;
const unsigned long speed_up_code = 0xA55AFF00;
const unsigned long speed_down_code = 0xF708FF00;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(11, ENABLE_LED_FEEDBACK);  // Initialize the IR receiver on pin 11
    // Initialize motor pins and other settings
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    Serial.println("System ready");
}

void loop() {
    handleIRRemote();
}

void handleIRRemote() {
    if (IrReceiver.decode()) {
        unsigned long value = IrReceiver.decodedIRData.decodedRawData;

        Serial.print("Received IR Code: 0x");
        Serial.println(value, HEX);

        if (value == forward_code) {
            Serial.println("Forward command received");
            start_motor(true);
        } else if (value == reverse_code) {
            Serial.println("Reverse command received");
            start_motor(false);
        } else if (value == stop_code) {
            Serial.println("Stop command received");
            stop_motor();
        } else if (value == speed_up_code) {
            Serial.println("Speed up command received");
            increase_speed();
        } else if (value == speed_down_code) {
            Serial.println("Speed down command received");
            decrease_speed();
        } else {
            Serial.println("Unknown command received");
        }

        IrReceiver.resume();  // Prepare for the next value
    }
}

// Dummy functions for motor control
void start_motor(bool forward) {
    if (forward) {
        Serial.println("Motor started in forward direction");
        // Code to start motor in forward direction
    } else {
        Serial.println("Motor started in reverse direction");
        // Code to start motor in reverse direction
    }
}

void stop_motor() {
    Serial.println("Motor stopped");
    // Code to stop motor
}

void increase_speed() {
    Serial.println("Increasing motor speed");
    // Code to increase motor speed
}

void decrease_speed() {
    Serial.println("Decreasing motor speed");
    // Code to decrease motor speed
}
