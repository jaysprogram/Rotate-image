// Program to rotate a ppm image
// ppm stands for Portable Pixmap format, which is my simple to work with]

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.1415926

typedef struct Image{
    int height;
    int width;
    int maxVal;
    unsigned char * data;
}Image;

// convert degree to radians
double radians(int degrees){
    return degrees * (PI / 180.0);
}

Image * rotateImage(char * originalImage, double radians){
    Image * newImage = malloc(sizeof(Image));
    // open image if not found quit
    FILE * imageFile = fopen(originalImage, "rb");
    if (imageFile == NULL){
        printf("Error opening %s\n",originalImage);
        return NULL;
    }

    // read image header
    char format[3];
    int width, height, maxVal;
    fscanf(imageFile, "%s %d %d %d", format, &width, &height, &maxVal);

    newImage->width = width;
    newImage->height = height;
    newImage->maxVal = maxVal;

    // allocate memory for the image
    unsigned char * image = calloc(3,  width * height); // 3 because of RGB
    unsigned char * rotatedImage = malloc(3 * width * height);
 
  

    // read the image 
    fread(image, 3, width * height, imageFile);
    fclose(imageFile);

    // math variables
    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    // the center for the image
    int cx = width/2;
    int cy = height/2;

    // perform the rotation

    // loop through each pixel
    for(int y = 0; y < height;y++){
        for (int x = 0; x < width; x++){
            // remember we rotate from center
            int x_rel = x - cx;
            int y_rel = y - cy;

            // matrix multiplication

            int new_x = (int) (cosTheta * x_rel - sinTheta * y_rel + .5) + cx;
            int new_y = (int) (sinTheta * x_rel + cosTheta * y_rel + .5 ) + cy;
            
            //checks if the new cords are in bounds
            if(new_x >= 0 && new_x < width && new_y >= 0 && new_y < height){
                // we are multipying with width sense this is stil considerd a 1D array
                int srcIdx = (y * width + x) * 3;
                int dstIdx = (new_y * width + new_x) * 3;

                //copy over the red green and blue pixels
                rotatedImage[dstIdx] = image[srcIdx]; // Red
                rotatedImage[dstIdx + 1] = image[srcIdx + 1]; // Green
                rotatedImage[dstIdx + 2] = image[srcIdx + 2]; // Blue
            }
        }  
    }
    free(image);
    newImage->data = rotatedImage;
    return newImage;
}

int main(int argc, char *argv[]){
    // check if inputed correctly
    if(argc < 4 ){
        printf("Usage: ./rotate_image <input_image> <rotation_angle> <output_image>\n");
        return 1;
    }

    // assign arguments
    char * originalImage = argv[1];
    double degrees = radians(atoi(argv[2]));
    char * newImageName = argv[3];

    Image * rotatedImage = rotateImage(originalImage,degrees);
    if (rotatedImage == NULL) return 1;
    
    // save the image 
    FILE * rotatedFile = fopen(newImageName, "wb");
    if(rotatedFile == NULL){
        printf("Error creating file: %s\n",newImageName);
        return 1;
    }

    fprintf(rotatedFile, "P6\n%d %d\n%d\n", rotatedImage->width,rotatedImage->height,rotatedImage->maxVal);
    fwrite(rotatedImage->data, 3, rotatedImage->height * rotatedImage->width, rotatedFile);
    fclose(rotatedFile);

    free(rotatedImage->data);
    free(rotatedImage);

    printf("Rotation completed and save as %s\n", newImageName);

    return 0;
}