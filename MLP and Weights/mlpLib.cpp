#include "mlpLib.h"

using namespace cv;

void imgToTxt(std::string digit, std::string filename, int *frame) {
    float temp;
    Mat image;
    std::string filepath = "/home/crexiz/Desktop/4090/MLP/mnist_png/mnist_png/testing/2/38.png";
    image = imread(filepath, CV_LOAD_IMAGE_UNCHANGED);
    if(!image.data) {
        std::cout << "No image data!\n";
    }

    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            temp = (int)image.at<uchar>(i,j);
            frame[image.rows*i + j] = temp;
        }   
    }
}

void fullyConnected(int *digit, int **weights, int *biases, int *output, int row, int col) {
    int sum = 0;
    for(int i = 0; i < 1; i++) {
        for(int j = 0; j < row; j++) {
            sum = 0;
            for(int k = 0; k < col; k++) {
                 sum += digit[k] * weights[k][j];
            }
            sum += biases[j];
            if(sum < 0) {
                sum = 0;
            }
            if(sum > 15) {
                sum = 15;
            }
            output[j] = sum;
        }
    }
}

void transpose(int** original, int** transpose, int row, int col) {
 
    for(int i = 0; i < col; i++) {
        transpose[i] = new int[row];
    }
  
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            transpose[j][i] = original[i][j];
        }
    }
}

void txtToArray(int *array, int size, std::string filename) {
    float temp;
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()){
        std::cout << filename << " could not open!\n";
    }
    for(int i = 0; i < size; i++) {
        file >> temp;
        array[i] = (int)temp;
    }
    file.close();
}

void txtToMatrix(int **matrix, int row, int col, std::string filename) {
    float temp;
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()){
        std::cout << filename << " could not open!\n";
    }

    for(int i = 0; i < row; i++) {
        matrix[i] = new int[col];
    }

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            file >> temp;
            matrix[i][j] = (int)temp;
        }
    }
    file.close();
}