#include <SoftwareSerial.h>

SoftwareSerial sim900(7, 8);  // RX, TX (Connect TX of SIM900A to 7, RX to 8)

// Define relay pins
#define RELAY1 4  
#define RELAY2 5  
#define RELAY3 6  
#define RELAY4 9  

// Define push button pins
#define BUTTON1 10  
#define BUTTON2 11  
#define BUTTON3 12  
#define BUTTON4 13  

void setup() {
    // Set relay pins as output
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(RELAY4, OUTPUT);

    // Initially turn off all relays
    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, HIGH);
    digitalWrite(RELAY3, HIGH);
    digitalWrite(RELAY4, HIGH);

    // Set button pins as input with pull-up resistors
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
    pinMode(BUTTON4, INPUT_PULLUP);

    Serial.begin(9600);  // Serial monitor
    sim900.begin(9600);  // GSM module baud rate

    Serial.println("Initializing SIM900A...");
    delay(1000);
    
    sim900.println("AT");  // Check SIM900A response
    delay(1000);
    showResponse();
    
    sim900.println("AT+CMGF=1");  // Set SMS mode to TEXT
    delay(1000);
    showResponse();

    sim900.println("AT+CNMI=2,2,0,0,0");  // New SMS notification
    delay(1000);
    showResponse();

    Serial.println("SIM900A Initialized. Waiting for SMS...");
}

void loop() {
    checkButtons();  // Check push button status
    checkSMS();      // Check for SMS commands
}

void checkButtons() {
    if (digitalRead(BUTTON1) == LOW) {
        toggleRelay(RELAY1, "RELAY1");
        delay(300);  // Debounce delay
    }
    if (digitalRead(BUTTON2) == LOW) {
        toggleRelay(RELAY2, "RELAY2");
        delay(300);
    }
    if (digitalRead(BUTTON3) == LOW) {
        toggleRelay(RELAY3, "RELAY3");
        delay(300);
    }
    if (digitalRead(BUTTON4) == LOW) {
        toggleRelay(RELAY4, "RELAY4");
        delay(300);
    }
}

void toggleRelay(int relayPin, String relayName) {
    int state = digitalRead(relayPin);
    digitalWrite(relayPin, state == HIGH ? LOW : HIGH);
    Serial.println(relayName + (state == HIGH ? " TURNED ON" : " TURNED OFF"));
}

void checkSMS() {
    if (sim900.available()) {
        String sms = sim900.readString();
        Serial.println("SMS Received: " + sms);

        processSMS(sms, "RELAY1", RELAY1);
        processSMS(sms, "RELAY2", RELAY2);
        processSMS(sms, "RELAY3", RELAY3);
        processSMS(sms, "RELAY4", RELAY4);
    }
}

void processSMS(String sms, String relayName, int relayPin) {
    if (sms.indexOf(relayName + " ON") != -1) {
        digitalWrite(relayPin, LOW);
        Serial.println(relayName + " TURNED ON");
        sendSMS(relayName + " is now ON");
    } 
    else if (sms.indexOf(relayName + " OFF") != -1) {
        digitalWrite(relayPin, HIGH);
        Serial.println(relayName + " TURNED OFF");
        sendSMS(relayName + " is now OFF");
    }
}

void sendSMS(String message) {
    sim900.println("AT+CMGS=\"+918763983406\"");  // Replace with the recipient's phone number
    delay(1000);
    sim900.println(message);
    delay(1000);
    sim900.write(26);  // End message with CTRL+Z
    delay(3000);
    Serial.println("Acknowledgment SMS Sent: " + message);
}

void showResponse() {
    while (sim900.available()) {
        Serial.write(sim900.read());
    }
}