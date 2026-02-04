Project Description: Smart Industrial Feedback & Safety Controller
This project demonstrates an Intermediate-Level Embedded System designed to simulate industrial automation logic. The system acts as a "Brain" for a production line, focusing on three core engineering pillars: Precision Monitoring, Asynchronous Event Counting, and Fail-Safe Safety Protocols.

Core Functionality
Closed-Loop Feedback: The system utilizes dual analog inputs (Potentiometers) to compare a user-defined "Target" speed against an "Actual" feedback signal. It calculates the System Error in real-time to determine if the machinery is in equilibrium.

High-Priority Safety: Leveraging Hardware Interrupts on Pin 2, the controller features a sub-millisecond response to an Emergency Stop (E-Stop). This instantly hijacks the processor to enter a "Safe State," halting all data processing and locking the UI to prevent accidental operation.

Asynchronous Pulse Counting: A secondary interrupt on Pin 3 simulates an IR beam or proximity sensor. By using a hardware interrupt, the system ensures that "products" are never missed during counting, even while the main CPU is busy updating the LCD or sending Serial telemetry.

Operator Dashboard: A 16x2 I2C LCD provides a live "HMI" (Human Machine Interface) displaying the Target, Actual, Error, and Product Count, while the Serial Monitor acts as a data logger for engineering diagnostics.

Technical Skills Demonstrated
Interrupt Handling: Implementing attachInterrupt() for time-critical safety and event logging.

Analog Sensing: Calibrating and processing 10-bit ADC signals into meaningful system variables.

State Machine Logic: Managing transitions between Initialize, Active, and Emergency states.

I2C Communication: Interfacing with peripherals using the 2-wire protocol to save GPIO pins.

Fail-Safe Programming: Designing code that prioritizes safety flags over standard loop execution.
