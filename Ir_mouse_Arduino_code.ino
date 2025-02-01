#include <IRremote.hpp>

#define IR_LED_PIN 3  // Change this to the pin your IR LED is connected to

IRsend irEmitter(IR_LED_PIN);  // Initialize IR emitter on pin 3 (renamed from irsend)

void setup() {
    Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
    irEmitter.begin(IR_LED_PIN);  // Initialize IR emitter (renamed from IrSender)
}

void loop() {
    if (Serial.available()) {
        String message = Serial.readStringUntil('\n');  // Read the incoming message until newline
        int separatorIndex = message.indexOf(',');  // Find the separator between address and command

        if (separatorIndex != -1) {
            String addressString = message.substring(0, separatorIndex);  // Get address part
            String commandString = message.substring(separatorIndex + 1);  // Get command part

            // Convert the address and command from hexadecimal string to integers
            uint16_t address = strtol(addressString.c_str(), NULL, 16);
            uint16_t command = strtol(commandString.c_str(), NULL, 16);

            // Send the IR signal using the renamed variable
            irEmitter.sendNEC(address, command, 0);

            delay(5000);  // Wait 5 seconds before sending again
        }
    }
}
