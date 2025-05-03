# 🔍 Smart Blind Stick with Ultrasonic Sensors, Vibration Feedback & Audio Guidance

An Arduino-powered smart blind stick designed to assist visually impaired individuals by detecting obstacles in multiple directions and giving real-time feedback using vibration motors and a DFPlayer Mini audio module.

## 🧠 Features

- 🔄 **360° Obstacle Detection** (Front, Back, Left, Right, Down)
- 🎧 **Dynamic Audio Feedback** via DFPlayer Mini (e.g., “Move 3 steps right”)
- 🌡️ **Pothole Detection** using downward-facing sensor
- 💥 **Vibration Alerts** to indicate proximity of obstacles
- 🔔 **Buzzer Alert** for pothole/speed breaker detection

## ⚙️ Hardware Components

| Component              | Quantity |
|------------------------|----------|
| Arduino Uno / Nano     | 1        |
| Ultrasonic Sensors (HC-SR04) | 5        |
| Vibration Motors       | 4        |
| DFPlayer Mini MP3 Module | 1        |
| Micro SD Card (with pre-recorded audio) | 1        |
| Buzzer                 | 1        |
| Jumper Wires & Breadboard | As required |
| Power Supply           | 1        |

## 🧩 Sensor Orientation

| Sensor Position | Pins |
|------------------|------|
| Front            | TRIG: 2, ECHO: 7 |
| Back             | TRIG: 3, ECHO: 8 |
| Left             | TRIG: 4, ECHO: 9 |
| Right            | TRIG: 5, ECHO: 10 |
| Down             | TRIG: 6, ECHO: 11 |

## 🔉 Audio Logic (DFPlayer Mini)

Pre-recorded audio clips are triggered dynamically based on distance:

- “Move 5 steps to the right”
- “Move 3 steps to the left”
- “Step back 2 steps”

Audio filenames are indexed (e.g., `0001.mp3`, `0002.mp3`) and mapped to step-based instructions.

## 🧠 How It Works

1. **Ultrasonic sensors** measure distance in all directions.
2. If an obstacle is within a **threshold (e.g., < 50cm)**:
   - The **corresponding vibration motor activates**.
   - The **DFPlayer Mini** plays a voice instruction suggesting how many steps to move in a clear direction.
3. If the **downward sensor detects a large drop (> 50cm)**:
   - The **buzzer sounds** to alert about potholes or open drains.

## 📂 File Structure
SmartBlindStick_/
├── SmartBlindStick_.ino         # Main Arduino code
├── audio/
│   ├── 0001.mp3  # “Move 1 step right”
│   ├── 0002.mp3  # “Move 2 steps right”
│   ├── …
│   └── 0015.mp3  # “Pothole ahead”

> 💾 **Ensure the audio files are copied to a FAT32-formatted microSD card and inserted into DFPlayer Mini.**

## 📦 Setup

1. Connect all components to the Arduino according to the pin assignments in the code.
2. Upload `SmartBlindStick_.ino` using Arduino IDE.
3. Insert microSD card with audio files into DFPlayer Mini.
4. Power the stick using a 9V battery or portable power bank.

## 🛡️ Future Improvements

- GPS tracking and emergency SMS alerts
- Voice command support
- Battery level monitoring
- Mobile app integration

## 👩‍💻 Developed By

**Anushka Surmawala**  
3rd Year CSE (IoT Specialization)  
GCET, Gujarat, India  
GitHub: [@anushkasurmawala](https://github.com/anushkasurmawala)

---

