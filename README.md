# Embedded-System---Multimedia-Center

**Overview**
The Media Center Project is an embedded systems application developed for the COE 718: Embedded Systems Design course at Ryerson University. It was implemented on the Keil MCB1700 Evaluation Board, leveraging the NXP LPC1700 ARM Cortex™-M3 microcontroller. The system features a real-time multimedia center with the following components:

**Menu Interface**: A navigable menu displayed on the onboard LCD, controlled using the joystick.
**Photo Gallery**: A viewer for bitmap images, navigable using the joystick, with support for selecting and exiting pictures.
**Audio Player**: A USB DAC-based MP3 player that streams audio from a connected PC. Volume control is managed via an onboard potentiometer.
**Snake Game**: A dynamic, joystick-controlled game with features including collision detection, score tracking, and random food generation.

**Features**
  **Menu Interface**:
  - Multi-directional navigation to select options.
  - Real-time visual feedback with a selector for improved user interaction.
  - Seamless transition between features.
  
  **Photo Gallery**:
  - Displays bitmap images resized for the LCD.
  - Allows forward and backward navigation through images.
  - Option to exit the gallery via the joystick.
    
  **Audio Player**:
  - Streams MP3 audio through USB to the onboard speaker.
  - Volume control using the potentiometer: clockwise decreases, counter-clockwise increases.
  - Displays a splash screen with instructions during playback.
  - Automatically disconnects USB upon exiting the player.
  
  **Snake Game**:
  - Implements core mechanics of a snake game, including dynamic growth and random food placement.
  - Collision detection to signal game over.
  - Score tracking to engage users.
  - Simplified mechanics for enhanced usability, such as no border collision.

**Technical Details**
Hardware: Keil MCB1700 Board with an ARM Cortex™-M3 microcontroller, LCD, joystick, potentiometer, and onboard speaker.
Software Tools: Keil µVision, GIMP (for image processing), and the LPC17xx library for device control.
Programming Language: C.

**Design Methodology:**
Modular implementation for each component.
Bitmap resizing and conversion for gallery images.
Integration of USB-based audio streaming and DAC control.
Event-driven programming for game mechanics and user interaction.

**Documentation**
Comprehensive IEEE-format reports were created to document the project phases, including design, development, testing, and implementation. The reports also outline challenges encountered and the steps taken to resolve them.

**Usage**
The project demonstrates key principles of embedded systems design, including real-time scheduling, device interfacing, and user-centered design. It serves as an engaging and functional multimedia application for learning and experimentation.
