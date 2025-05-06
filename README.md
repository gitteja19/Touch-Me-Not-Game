# 🎮 Touch Me Not – Embedded Obstacle Avoidance Game on ARM7

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

**Touch Me Not** is a real-time obstacle avoidance game developed on the **LPC2148 ARM7 microcontroller**. It uses an analog joystick (via ADC) for player control, an LCD for graphics display with custom characters, and dynamic track generation to create a fast-paced embedded gaming experience.

---

## 🚀 Features

- **🕹 Analog Joystick Control**  
  - Player movement driven via ADC input from a joystick  
  - Smooth and responsive navigation logic with dead zone filtering

- **📺 LCD Display with Animations**  
  - Uses 16x2 character LCD with CGRAM for animated characters  
  - Frame-based sprite updates for running player animation

- **⚠️ Real-Time Obstacle Generation**  
  - Dynamic and randomized track with scrolling obstacles  
  - Collision detection and game reset logic included

- **🎯 Score Tracking**  
  - Tracks and displays score based on survival time  
  - Difficulty increases over time by reducing frame delay

- **🔄 Game Loop Management**  
  - Uses interrupts and tight polling for precise frame timing  
  - Supports full restart upon collision (soft reset)

---

## 🛠️ Tech Stack

- **MCU**: LPC2148 (ARM7TDMI-S)  
- **Input**: Analog Joystick via ADC (A0.1 and A0.2)  
- **Output**: 16x2 Character LCD (custom CGRAM sprites)  
- **Language**: Embedded C  
- **Tools**: Keil uVision / GCC ARM Toolchain

---

## 📦 How It Works

1. Game starts with a countdown and clears the LCD.
2. Player moves left/right and switches rows using joystick input.
3. Obstacles scroll in from the right. If the player collides, the game ends.
4. Score is displayed dynamically. Game resets on button press (P1.27).

---

## 📸 Demo Preview

> Add your LCD screenshots or gameplay GIFs here:

```
🏃‍♂️          ★
           ★
```

---

## 📁 Project Structure

```bash
.
├── main.c            # Core game logic and main loop
├── lcdLib.h/.c       # LCD control and CGRAM sprite handling
├── adcLib48.h/.c     # Joystick ADC interface
├── gpioLib.h/.c      # GPIO read/write macros
├── delayLib.h/.c     # Delay utilities
├── types.h           # Basic type definitions
└── Makefile          # (If applicable for build)
```

---

## 🔧 Setup & Flashing

1. Connect the joystick and LCD to LPC2148 (ensure proper ADC/GPIO pins).  
2. Compile and flash using Keil uVision or any ARM GCC toolchain.  
3. Power the board, and the game will launch with a countdown.  

> 🧪 Optional: Customize joystick sensitivity, frame rate, or sprite design in code.

---

## 🎮 Controls

- **Horizontal Move**: Left/Right via Joystick X  
- **Row Switch**: Up/Down via Joystick Y  
- **Restart Game**: Press button connected to `P1.27`

---

## 🧠 Learning Highlights

- Real-time game loop design on microcontrollers  
- ADC integration for analog input handling  
- Custom LCD graphics with CGRAM characters  
- Embedded system optimization and interrupt-safe programming

---

## 👨‍💻 Author

**Your Name**  
📧 your.email@example.com  
🔗 [LinkedIn](https://linkedin.com/in/yourname)

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).




