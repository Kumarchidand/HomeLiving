#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10       // RFID SS pin
#define RST_PIN 9       // RFID RST pin
#define SOLENOID_PIN 6  // Solenoid lock control pin (Connected to Relay Module)

MFRC522 mfrc522(SS_PIN, RST_PIN);  
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// Keypad Configuration
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Keypad Pins: Avoiding Conflict with RFID
byte rowPins[ROWS] = {2, 3, 4, 5};  // Rows connected to Arduino
byte colPins[COLS] = {7, 8, A0, A1}; // Columns connected to Arduino
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String correctPassword = "2580";  // Define correct password
String enteredPassword = "";      // Store user input

// List of Authorized RFID Tags (3 UIDs)
byte authorizedTags[3][4] = {
  {0xCD, 0x88, 0x30, 0x03},
  {0x23, 0xB6, 0xF0, 0xE3},
  {0xD7, 0xBE, 0x76, 0x65}
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  
  pinMode(SOLENOID_PIN, OUTPUT);
  lockDoor();  // Ensure the solenoid is locked at startup

  lcd.setCursor(0, 0);
  lcd.print("Scan RFID or");
  lcd.setCursor(0, 1);
  lcd.print("Enter Password:");
}

void loop() {
  checkRFID();
  checkKeypad();
}

// RFID Tag Checking Function
void checkRFID() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (int i = 0; i < 3; i++) {
      bool match = true;
      for (byte j = 0; j < 4; j++) {
        if (mfrc522.uid.uidByte[j] != authorizedTags[i][j]) {
          match = false;
          break;
        }
      }
      if (match) {
        lcd.clear();
        lcd.print("RFID Granted");
        unlockDoor();  // Unlock door (Relay OFF)
        delay(6000);   // *Keep the door unlocked for 6 seconds*
        lockDoor();    // Lock door (Relay ON)
        mfrc522.PICC_HaltA();
        return;
      }
    }
    lcd.clear();
    lcd.print("Access Denied");
    delay(2000);
    mfrc522.PICC_HaltA();
  }
}

// Keypad Password Checking Function
void checkKeypad() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {  // Confirm password
      if (enteredPassword == correctPassword) {
        lcd.clear();
        lcd.print("Pass Granted");
        unlockDoor();  // Unlock door (Relay OFF)
        delay(6000);   // *Keep the door unlocked for 6 seconds*
        lockDoor();    // Lock door (Relay ON)
      } else {
        lcd.clear();
        lcd.print("Wrong Password");
        delay(2000);
      }
      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    } else if (key == '*') {  // Reset password entry
      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    } else {
      enteredPassword += key;
      lcd.setCursor(enteredPassword.length() - 1, 1);
      lcd.print('');  // Display '' for security
    }
  }
}

// Unlock Door Function (Deactivates Relay, Opens Lock)
void unlockDoor() {
  digitalWrite(SOLENOID_PIN, LOW);  // Relay OFF (Door Unlocked)
  lcd.clear();
  lcd.print("Door Unlocked");
}

// Lock Door Function (Activates Relay, Locks)
void lockDoor() {
  digitalWrite(SOLENOID_PIN, HIGH);  // Relay ON (Door Locked)
  lcd.clear();
  lcd.print("Door Locked");
}