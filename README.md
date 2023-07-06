# Convolution-based-Edge-Detection
This code implements image edge detection using convolution and gradient techniques. It utilizes OpenCV library in C++. The program applies convolution, converts the image to grayscale, calculates gradients, and identifies edges based on a threshold. It offers a simple and efficient method for detecting edges in images.

The program includes the following functions:

convolución(Mat imagen, Mat kernel): This function applies convolution on the input image using the specified kernel. It returns the resulting image after convolution.

gris(Mat imagen): This function converts the input image to grayscale. It returns the grayscale image.

puntos(Mat fuerza, Mat angulo, float umbral): This function identifies edge points in the image based on the gradient magnitude and direction. It takes the gradient magnitude, gradient angle, and a threshold value as inputs, and returns an image with the identified edge points.

The main function performs the following steps:

Reads an image from the specified file path.
Defines a kernel matrix for convolution.
Applies convolution on the image using the defined kernel.
Converts the convolved image to grayscale.
Calculates the gradient in the x and y directions using the Sobel operator.
Calculates the magnitude and direction of the gradient.
Identifies edge points based on the gradient information and a threshold.
Displays the original image, gradient magnitude, gradient direction, and the identified edges.
Waits for a key press before exiting the program.
Dependencies
The code requires the following dependencies:

OpenCV 2 library
Usage
To use this code, follow these steps:

Install OpenCV 2 library on your system.
Clone this repository to your local machine or download the code files.
Update the file path in the main function to the location of the image you want to process.
Compile and run the code using a C++ compiler with OpenCV 2 library linked.
View the displayed images to observe the original image, gradient magnitude, gradient direction, and the identified edges.
Feel free to modify the code according to your requirements and experiment with different images and parameters to achieve desired edge detection results.
