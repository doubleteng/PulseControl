# Real-Time Stepper Motor Control with Arduino and Grasshopper

## Project Overview
This project enables real-time control of three stepper motors using an Arduino microcontroller integrated with Grasshopper, a visual programming language within Rhino 3D. The setup allows for precise control of the motors’ rotational speed and direction, which can be dynamically adjusted through serial data transmitted from Grasshopper. The application is ideal for interactive and adaptive systems, where motor movements need to respond instantly to parameter changes.

## Project Components
### 1. **Arduino Setup**
   - **Hardware**: Arduino board connected to three stepper motors.
   - **Code**: The Arduino `.ino` file included in this project is responsible for reading serial data from Grasshopper, parsing motor commands, and adjusting the speed and direction of each motor accordingly.
   - **Pin Configuration**: Each motor has dedicated direction and step control pins, allowing independent operation.

### 2. **Grasshopper Integration**
   - Grasshopper is used to generate and send control data to the Arduino in real-time.
   - A custom component in Grasshopper sends a serial data string in the format `D1,S1,D2,S2,D3,S3`, where:
     - `D1`, `D2`, `D3` are direction values for motors 1, 2, and 3 (0 for counterclockwise, 1 for clockwise).
     - `S1`, `S2`, `S3` are speed values for each motor.

## Getting Started

### Prerequisites
- **Hardware**:
  - Arduino Uno (or compatible model)
  - Three stepper motors
  - Motor driver circuits for each stepper motor
- **Software**:
  - Arduino IDE
  - Rhino 3D with Grasshopper plugin

### Setup Instructions
1. **Upload Arduino Code**: Open the provided `.ino` file in the Arduino IDE and upload it to your Arduino board.
2. **Wiring**: Connect each stepper motor to its designated pins on the Arduino:
   - Motor 1: Direction pin 2, Step pin 3
   - Motor 2: Direction pin 4, Step pin 5
   - Motor 3: Direction pin 6, Step pin 7
3. **Grasshopper Configuration**:
   - In Grasshopper, set up the serial data transmission to match the Arduino's expected data format.
   - Use sliders, buttons, or any other Grasshopper component to control the motor directions and speeds dynamically.

### Running the Project
1. Start the serial connection from Grasshopper, ensuring it is configured to match the Arduino’s baud rate (9600).
2. Adjust parameters in Grasshopper to control each motor’s speed and direction in real-time.
3. Observe the stepper motors responding immediately to changes made within Grasshopper.

## Example Serial Data
The expected data format sent from Grasshopper to Arduino is:
```
D1,S1,D2,S2,D3,S3
```
For example:
- `1,300,0,200,1,100` instructs:
  - Motor 1 to rotate clockwise at a speed of 300
  - Motor 2 to rotate counterclockwise at a speed of 200
  - Motor 3 to rotate clockwise at a speed of 100

## Future Enhancements
- **Feedback Loop**: Integrate sensors for real-time feedback to Grasshopper, enabling closed-loop control.
- **Customizable Controls**: Add more control options within Grasshopper, such as ramping speed or reversing direction based on external triggers.

## License
This project is open-source and available under the MIT License.


