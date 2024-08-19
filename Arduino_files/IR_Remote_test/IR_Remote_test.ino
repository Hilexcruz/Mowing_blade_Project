#include <IRremote.hpp> // include the library

// Define the pin where your IR receiver is connected
#define IR_RECEIVE_PIN 11

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Initialize the IR receiver
    Serial.println("IR Receiver is ready to receive signals");
}

void loop() {
    if (IrReceiver.decode()) {
        unsigned long value = IrReceiver.decodedIRData.decodedRawData; // Get the raw IR code
        
        Serial.print("Received IR Code: 0x");
        Serial.println(value, HEX);  // Print the received code in hexadecimal

        IrReceiver.resume(); // Receive the next value
    }
}
