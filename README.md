# 🔐 IoT-Based Multimodal Home Automation & Secure Door Lock System

A **final year engineering project** that combines **embedded systems**, **IoT communication**, and **security integration** to remotely manage home appliances (lights, fans, pumps) and secure door access using **RFID + password authentication**. The system leverages **GSM communication** to offer control from up to any distance.

---

## 📌 Key Features

- ✅ **Remote appliance control** via GSM (lights, fans, pump motors)
- ✅ **Door lock system** with **dual authentication** (RFID + password)
- ✅ Real-time SMS-based control and feedback
- ✅ Unauthorized access alerts via GSM
- ✅ Local & remote control coexistence
- ✅ Over-voltage & under-voltage protection logic
- ✅ Power-efficient design using microcontroller sleep modes

---

## 🔧 Technologies Used

| Technology | Purpose |
|-----------|---------|
| **C++ (Embedded C)** | Programming Arduino & microcontroller logic |
| **IoT (GSM Module)** | Wireless remote communication (SIM800/SIM900) |
| **RFID Module (RC522)** | Tag-based user authentication |
| **Keypad (4x4)** | Password entry for door lock |
| **Relay Module** | Control AC appliances safely |
| **LCD (16x2)** | Status display |
| **Buzzer & LED** | Intrusion alerts and status signals |
| **Solenoid Lock** | Electronic door locking/unlocking |
| **Arduino UNO / ATmega328** | Main microcontroller |

---

## ⚙️ Hardware Components

- Arduino UNO 
- GSM module (SIM900A)
- RFID Reader (RC522) + RFID Tags
- 4x4 Keypad for PIN entry
- 16x2 LCD Display (I2C or parallel)
- Solenoid door lock
- Relays (for fans, lights, motor pump)
- Power supply module (regulated 5V/12V)

---


---

## 🚀 How It Works

1. **Remote Commands via SMS**  
   User sends a command (e.g., `LIGHT ON`, `FAN OFF`,`MOTOR PUMP`) from any mobile phone. GSM module reads it and triggers the corresponding relay.

2. **Smart Door Lock Access**  
   - The user taps an RFID tag.  
   - If the tag is valid, the system asks for a password via keypad.  
   - If both are valid → Door opens  
   - If invalid → + message sent to owner

3. **Display & Feedback**  
   - LCD shows current status (e.g., `Access Granted`, `Fan ON`)
   - Unauthorized attempts are logged and reported

---

## 🛠️ Setup Instructions

1. Wire the hardware according to the `circuit_diagram.pdf`
2. Flash the code inside `code/main.ino` to Arduino using Arduino IDE
3. Insert a SIM card into the GSM module
4. Power the circuit with a stable power source
5. Test:
   - Send SMS from your phone to control devices
   - Use RFID tag + keypad to test the door lock

---

## 📷 Demo Screenshots

![Uploading image.png…]()



---

## 📚 Skills Demonstrated

- Embedded C++ programming
- GSM & IoT integration
- Security system design (2FA authentication)
- Power and signal circuit design
- Real-time automation with feedback

---

## 👨‍🎓 Developed By

**Kumar Chidanandam** 
**Mahesh Sahoo**
**Sahikant Nayak**
** Vikash Kumar**
Final Year – B.E/B.Tech  
Specialization: Embedded Systems & IoT

---

## 📌 Future Improvements

- Integrate mobile app (React Native)
- Add camera module for real-time image capture
- Connect to cloud for remote data logging
- Use fingerprint scanner as third-layer authentication

---

## 📄 License

This project is open for educational and academic use. You may modify it for personal learning and college demonstration purposes.



