### Arduino Battleship Game with LED Matrix Display

This project implements the Battleship game using an Arduino microcontroller and a large bicolor LED matrix display. Players use directional buttons or a joystick to select positions for firing, aiming to sink each other's ships displayed on the LED matrix.

#### Project Overview
The game will be split into two equal regions on the LED matrix, one for each player. Ships will be randomly generated and displayed on the matrix for each player. The game interface includes directional buttons for navigation and a confirmation button for firing.

#### Features
- **Game Setup**:
  - Randomly generate and display ships for each player on the LED matrix.
  - Initialize game components and set up the LED matrix display.

- **Player Interaction**:
  - Use directional buttons (or a joystick) to move a cursor for targeting on the LED matrix.
  - Press a button to confirm the firing position and check for hits on opponent's ships.

- **Game Logic**:
  - Detect hits on opponent's ships and update the display accordingly.
  - Display different colors on the LED matrix to represent hits and misses.

- **Game End**:
  - Display a winning message and the final score when a player sinks all opponent ships.

#### Components Used
- Arduino Uno microcontroller
- Bicolor LED Matrix (multiple matrices may be used for larger displays)
- Keypad for player input
- Pushbutton for confirmation
- Breadboard for prototyping and wiring

#### Wiring and Connections
The code provided includes specific pin assignments and connection details for the LED matrix, keypad, pushbutton, and other components. Ensure all connections are correctly made according to the specified pin mappings.

#### Game Logic Overview
The Arduino sketch contains functions for ship generation, hit detection, player movement, and LED matrix control. The game continues until one player sinks all opponent ships, triggering a game-over state.

#### Instructions for Running the Game
1. Upload the provided Arduino sketch to your Arduino Uno board.
2. Ensure all components are correctly connected as per the wiring instructions.
3. Power on the system and interact with the game using the keypad and pushbutton to play Battleship.

#### Contributors
- **Author**: Anca Lazar
- **Editor**: Wokwi

Feel free to modify and expand upon this project to add more features, improve gameplay, or enhance the user interface based on your requirements. Happy coding!
