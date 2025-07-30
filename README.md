
### Hardware Block Diagram

*(Insert circuit diagram image here if hosted on GitHub, e.g. ![Circuit](./your_circuit_image.png))*

---

## ⚙️ Key Components

| Component             | Role                                                   |
|----------------------|--------------------------------------------------------|
| Arduino Uno          | Central control unit                                   |
| IR Receiver          | Wireless remote interface                              |
| H-Bridge (Transistors)| Controls motor direction and braking                   |
| DC Motor             | Simulated load/motion device (e.g., mowing blade)      |
| LM35 Sensors         | Measures temperature of board and motor                |
| ACS712 Sensor        | Measures current flowing through the motor             |
| Remote Controller    | Sends IR commands to Arduino                           |
| Emergency Switch + Fuse | Added safety and protection for motor circuit      |

---

## 📦 Codebase Structure

### `Basic_Motor_Control.ino`
Initial testing code to control motor direction and speed using serial commands.

### `Motor_Control_With_Sensors.ino`
Full implementation with:
- IR remote control
- Real-time temperature & current sensing
- Fault detection and automatic shutdown

### `Final_working_code.ino`
Stable version with final tuning and optimized logic. Recommended for deployment or demos.

---

## 📺 Demo

🎥 **Video**: _Controlling the mowing blade_  
*(Upload and link the video on GitHub or YouTube, or embed it if applicable)*

---

## 🧪 How It Works

1. Power is supplied via a battery through a safety fuse and emergency switch.
2. The H-Bridge controls the flow of current through the DC motor for direction switching.
3. Arduino modulates PWM signals to control speed and direction.
4. Two LM35 sensors measure temperature; an ACS712 sensor monitors current.
5. If temperature exceeds 70°C or current exceeds 18A, the motor shuts down automatically.
6. IR remote or serial commands can start/stop or control direction and speed of the motor.

---

## 🔐 Safety Features

- **Automatic shutdown** if:
  - Board temperature > 70°C
  - Motor temperature > 70°C
  - Current > 18A
- **Emergency kill switch** in power supply line
- **Fuse** for electrical protection
- **Serial feedback** for real-time fault alerts

---

## 📚 What I Learned

- Designing and implementing an **H-Bridge motor driver**
- Reading and processing analog sensor data in real time
- Programming with **IR remote protocols** (NEC, Sony, etc.)
- Building a safe and reliable **embedded control system**
- Debugging and structuring **robust Arduino code**
- System integration of sensors, actuators, and logic control

---

## 🧩 Future Improvements

- Add an OLED or LCD display for local feedback  
- Implement PID control for closed-loop motor speed regulation  
- Integrate Bluetooth/Wi-Fi for remote control via mobile app  
- Build a custom PCB for compactness and durability  
- Improve enclosure and mount sensors for better thermal contact  

---

## ✅ Status

✔️ Working prototype tested with IR remote and serial commands  
✔️ Fully functional safety monitoring for temperature and current  
✔️ Demo video available  
✔️ Code documented and modular for extension

---

## 🧠 Bonus

This project showcases my capability to:
- Work with real-world sensors and actuators
- Translate theory into a working embedded system
- Prioritize safety and modularity in design
- Build systems that are ready for real-world deployment

---

