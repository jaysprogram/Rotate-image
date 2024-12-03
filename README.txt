Install python dependencies:
pip install -r requirements.txt

To run:

python rotate_image.py <input_image> <rotation_angle>
python3 if on linux

<input_image> = specify a image to input including the file extension Ex: image.ppm
<rotation_angle> = specify the rotation you want in degrees clockwise 

To run without python:

./rotate_image <input_image> <rotation_angle> <output_image>
<output_image> = The name of the output

The program supports reading PPM files in 'P6' format (binary).

The Python script:

Converts the input image to the PPM format using Pillow.
Compiles and runs the C program (rotate_image.c), passing the converted image and rotation angle as arguments.
Visualizes the original and rotated images side-by-side using matplotlib.

The C program:

Reads the PPM image.
Rotates it based on the given angle.
Saves the rotated image in the PPM format.


FIXES NEEDED
Anti-aliasing
fix the color shift
