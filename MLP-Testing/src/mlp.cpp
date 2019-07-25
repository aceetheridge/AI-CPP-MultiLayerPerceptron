#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "mlpLib.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Constants
    const int ROWS = 28;
    const int COLUMNS = 28;
    const int imageSize = ROWS*COLUMNS;
    const int CHANNEL = 1;
    
    // Weights, biases
    int l1_b[100];
    int l2_b[10];
    int **l1_w = new int*[100];
    int **l2_w = new int*[10];

    // Transpose weights
    int **l1_wt = new int*[784];
    int **l2_wt = new int*[100];

    // Input image
    int digit[imageSize];

    // Output layers
    int layer_one_output[100];
    int layer_two_output[10];
    
    // Read in 28 by 28 mnist digit
    imgToTxt(argv[1], argv[2], digit);

    // Read in layer 1 biases, 100 by 1
    txtToArray(l1_b, 100, "l0_b.txt");
   
    // Read in layer 2 biases, 10 by 1
    txtToArray(l2_b, 10, "l2_b.txt");
   
    // Read in layer 1 weights, 100 by 784
    txtToMatrix(l1_w, 100, 784, "l0_w.txt");
   
    // For matrix multiplication to work
    // Transpose layer 1 weights, 784 by 100
    transpose(l1_w, l1_wt, 100, 784);
   
    // Read in layer 2 weights, 10 by 100
    txtToMatrix(l2_w, 10, 100, "l2_w.txt");
   
    // For matrix multiplication to work
    // Transpose layer 1 weights, 784 by 100
    transpose(l2_w, l2_wt, 10, 100);

    // MLP Architecture
    // 1 input layer
    // 2 "hidden" layers
    // 1 output layer

    // Hidden layer 1
    fullyConnected(digit, l1_wt, l1_b, layer_one_output, 100, 784);

    // Hidden layer 2
    fullyConnected(layer_one_output, l2_wt, l2_b, layer_two_output, 10, 100);

    int highest = 0;
    int guess = 0;
    cout << "Ranking (highest number is the prediction.\n";
    for(int i = 0; i < 10; i++) {
        cout << i << ": " << layer_two_output[i] << endl;
        if(layer_two_output[i] > highest) {
            highest = layer_two_output[i];
            guess = i;
        }
    }
    
    cout << "Actual number: " << argv[1] << " Guessed: " << guess << endl;
    if(guess == stoi(argv[1])){
        cout << "Correct!\n";
    }
    else {
        cout << "Incorrect!\n";
    }
    
    return 0;
}