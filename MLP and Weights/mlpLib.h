#ifndef MLPLIB_H_
#define MLPLIB_H_

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv_modules.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

void fullyConnected(int *digit, int **weights, int *biases, int *output, int row, int col);
void imgToTxt(std::string digit, std::string filename, int *frame);
void transpose(int** original, int** transpose, int row, int col);
void txtToArray(int *array, int size, std::string filename);
void txtToMatrix(int **matrix, int row, int col, std::string filename);

#endif
