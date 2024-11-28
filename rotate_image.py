## Program to rotate an image given a degree using Matrix multiplication
## Please read README file first.
from PIL import Image
import sys
import os
import subprocess
import matplotlib.pyplot as plt



## handle command line arguments
if len(sys.argv) < 3:
    print("Usage: python rotate_image.py <input_image> <rotation_angle>")
    sys.exit(1)
    
## assign arg
inputImage = sys.argv[1]
degreesToRotate = sys.argv[2]
outPutImage = "rotated_" + inputImage # the rotated file name
convertedImage = "converted_image.ppm" ## temp file

#convert jpg to PPM
try:
    image = Image.open(inputImage)
    image.save(convertedImage, format = 'PPM') ## convert any file to PPM
except Exception as e:
    print(f"Error converting image:{e}")
    sys.exit(1)
    
# call the c program

try:
    ## compile
    subprocess.run(["gcc","rotate.c","-o","rotate_image","-lm"], check= True)
    
    ## run
    subprocess.run(["./rotate_image", convertedImage, degreesToRotate,outPutImage], check= True)
    
except subprocess.CalledProcessError as e:
    print(f"An error occured when compiling or running the C file: {e}")
    sys.exit(1)
    
## clean up temp file
os.remove(convertedImage)
    
## load images
originalImage = Image.open(inputImage)
rotatedImage = Image.open(outPutImage)

## display image using Matplotlib

fig, axs = plt.subplots(1,2,figsize=(10, 5))

# Display original image
axs[0].imshow(originalImage)
axs[0].set_title("Original Image")
axs[0].axis("off")

# Display rotated image
axs[1].imshow(rotatedImage)
axs[1].set_title(f"Rotated Image ({degreesToRotate}°)")
axs[1].axis("off")

# Show the before and after comparison
plt.tight_layout()
plt.show()

