# Multilayer Perceptron
## Using pre-trained weights quantized to 5-bits
### You will need the mnist 28x28 hand written digit dataset

To compile
```
g++ -std=c++11 mlp.cpp mlpLib.cpp mlpLib.h -l `pkg-config --cflags --libs opencv` -o mlp
```

To run
```
./mlp arg1 arg2
```
* Where arg1 is the digit (i.e. 1, 2, 3, etc...)
* Where arg2 is the filename (i.e. 1.png, 2.png, etc...)

example
```
./mlp 1 3.png
```
This will have the network guess the 3rd image of the digit '1'
