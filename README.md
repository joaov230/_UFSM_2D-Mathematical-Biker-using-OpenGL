# 2D Mathematical Biker using OpenGL
 Interactive animation of a biker using OpenGL.
 This project was developed during my studies in Computer Science aout CGI.  

## Features
 * You can change the velocity of the bike and it's gear (faster and slower)
 * Scenery moves with the bike and has a parallax simulation (far objects moves slower then the close ones)
 * Some curves where created using **Cubic Bezier Curves** (manually calculated)
 * The knees where calculated using the intersection between circles with 60 pixel radius (with center in the pedals and in the bike seat)

## Compiling
 * Since it was developed using all libraries in code blocks, you must:
 1. Download code::blocks
 2. Open [mainProject](/mainProject/)
 3. Open the project 'canvas' with code::blocks
 4. Build and run

## Instructions
|------------|--------------------------------|
| ArrowRight | Increase the bike velocity     |
| ArrowLeft  | Decrease the bike velocity     |
| [          | Increase the bike gear         |
| ]          | Decrease the bike gear         |
| D          | Turn on the "visualizing" mode |
|------------|--------------------------------|

**IMPORTANT INFORMATION:**
Since the keymapping was mapped in my particular keyboard, maybe you'll have to change the mapping of the keys to your keyboard in the _main.cpp -> void keyboard (int key)_
To discover the id of your desired key, uncomment the _printf_ line in the function above, build and run, press the key, and it's id will appear in the cmd, then just change the mapping of the key in _void keyboard (int key)_