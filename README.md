# Event-Driven Infrared Remote Controlled Servo System (Pure STM32-HAL)

A high-rigor, non-blocking firmware application designed for the WeAct Studio STM32F411CEU6 (Black Pill V2.0) microcontroller architecture. This project implements a hardware interrupt-driven NEC Infrared decoding state machine that coordinates with hardware timers to mechanically control a variable-angle louver system via an RC Servo Motor. 

Developed entirely in STM32CubeIDE utilizing the low-level STM32-HAL Library to enforce strict hardware abstraction layers and deterministic execution boundaries.

---

## 🛠️ Architecture & Core System Features

*   **Asynchronous Interrupt-Driven Protocol Parsing:** Bypasses CPU-intensive polling loops. The infrared capture engine uses an external hardware interrupt (EXTI0 line on PA0) configured for falling edge detection, calculating pulse widths dynamically via system tick differentials.
*   **Encapsulated State Machine Implementation:** Decoded bits are progressively pushed into a private file-scoped 32-bit register array (ir_decoder.c). Validated data frames are safely passed to the orchestration layer via pointer-driven mailbox exchanges.
*   **Deterministic Hardware PWM Generation:** Configures the internal TIM2 peripheral (Channel 1, mapped via Alternate Function to PA5) to drive a clean 50Hz (20ms period) square wave. The prescaler (PSC) scales clock resolution down to 1 microsecond intervals, allowing granular Capture/Compare Register updates (CCR1) between 500µs (0°) and 2500µs (180°).

---

## 📂 Engineering Directory Layout

*   Core/Inc/ir_decoder.h   # Enumerators & public declarations for the NEC state-machine
*   Core/Inc/servo_driver.h # Prototyped hardware timer manipulation interfaces
*   Core/Src/ir_decoder.c   # High-resolution interrupt capture math & signal decoding
*   Core/Src/servo_driver.c # Capture/Compare register scaling structures for 50Hz PWM
*   Core/Src/main.c         # System clock tree initializations & main loop consumption logic

---

## 🔌 Prototyping Interconnect Schematic Rules

To ensure laptop port immunity and electrical stability, a strict Power Isolation Architecture must be maintained on the prototyping matrix:

*   **IR Receiver:** OUT (Signal) wired to pin PA0, VCC wired to 3.3V on the board, GND wired to GND on the board.
*   **Servo Motor:** PWM (Orange/Yellow) wire connected directly to pin PA5.
*   **Servo Motor Power:** VCC (Red wire) connected EXCLUSIVELY to an external battery pack or 5V power module rail. Do not connect it to the board's 5V pin!
*   **Unified Common Ground:** Run a physical jumper line from the negative (-) terminal of your external battery pack straight into a GND pin on the Black Pill so all modules share a unified reference base.

---

## 🚀 Execution & Deployment WorGkflow

### 1. Build Verification
Open the workspace directory inside STM32CubeIDE. Click the Hammer Icon (Build All) or use the execution shortcut Ctrl + B. The toolchain cross-compiler validates with a clean 0 errors, 0 warnings profile.

### 2. Hardware Bootloader Latch Sequence
1. Bridge your laptop to the Black Pill via a high-quality data-sync USB-C cable.
2. Press and HOLD down the physical BOOT0 button on the PCB layout.
3. While continuing to hold BOOT0, click the physical NRST (Reset) button once.
4. Release BOOT0. The chip suspends flash runtime memory and opens the internal USB boot gates.

---

## 🇳🇬 Engineering Infrastructure Context
This project workspace was designed and successfully brought to full compiler completion locally in Lagos, Nigeria. Special logistical thanks to local embedded component providers like Micro-scale Engineering Nigeria for hardware support options.
