#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void GaussianBlur(float arr[480][640], float kernel[3][3], int height, int width);

int main() {
    cout << "Algoritm for blurring an image" << endl;

    ifstream myImage("saturn.ascii.pgm");
    

    string sType = "", sWidth = "", sHeight = "", sIntensity = "";
    string sPixel = "";
    int height, width;
    int pixel;
    float array[480][640];
    
    // float ker[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}; // sharpening
    // float ker[3][3] = {{1/9, 1/9, 1/9}, {1/9, 1/9, 1/9}, {1/9, 1/9, 1/9}}; // box blur
    float ker[3][3] = {{0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}}; // blur

    // int ker[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}; 

    
    

    if (!myImage.is_open()) {
        cout << "ERROR: Failed to open the image" << endl;
        return 0;
    }
        

    myImage >> sType;
    myImage >> sWidth;
    myImage >> sHeight;
    myImage >> sIntensity;

    cout << "type: " << sType << endl;
    cout << "width: " << sWidth << endl;
    cout << "height: " << sHeight << endl;
    cout << "sIntensity: " << sIntensity << endl;

    height = stoi(sHeight);
    width = stoi(sWidth);

    for (int i = 0; i < 480; i++) {
        for (int j = 0; j < 640; j++) {
            myImage >> sPixel;
            pixel = stoi(sPixel);
            array[i][j] = pixel;
        }
    }

    GaussianBlur(array, ker, height, width);
    

    myImage.close();

    return 0;
}

void GaussianBlur(float arr[480][640], float kernel[3][3], int height, int width) {
    

    ofstream blurredImage("blurredImage.pgm");

    if(!blurredImage.is_open()) {
        cout << "Failed to open the new image" << endl;
    }

    blurredImage << "P2" << endl;
    blurredImage << "640 480" << endl;
    blurredImage << "255" << endl;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            float sum = 0;
            float sumKernel = 0;
            float newPixel = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if ((row + i) >= 0 && (row + i) < height && (col + j) >= 0 && (col + j) < width) {
                        sum = arr[row+i][col+j] * kernel[i+1][j+1];
                        sumKernel = sumKernel + sum;
                    }
                }
            }
            // newPixel = sumKernel;
            blurredImage << sumKernel << " ";
        }
        blurredImage << endl;
    }

    blurredImage.close();
}