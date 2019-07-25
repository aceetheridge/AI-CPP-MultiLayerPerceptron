#include <iostream>
#include "readmatrix.h"


using namespace std;
void vecToArray(int **matrix, vector<vector<long double>> vec2d );
int main(){
    vector<vector<long double>> l0b,l2b,l0w,l2w,img;
    // l0b = createvector("l0_b.out");
    // l2b = createvector("l2_b.out");
    // l0w = createvector("l0_w.out");
    // l2w = createvector("l2_w.out");
    img = createvector("23.png");
    int **l0wa = new int*[2000]; 
    vecToArray(l0wa, img);
    for(int i = 0; i < l0w.size();i++){
        for(int j = 0; j < l0w[1].size();j++){
            cout << l0wa[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
void vecToArray( int **matrix, vector<vector<long double>> vec2d ){
    vector<vector<long double>> o;
    int i = 0;
    int row = vec2d.size();
    int col = vec2d[i].size();
    for(int x = 0; x < row; x++){
        matrix[x] = new int[col];
    }
    // vector<vector<long double>>::iterator r;
    // vector<long double>::iterator c;
    // int s = 0;
    // for(r = vec2d.begin(); r !=vec2d.end(); r++){
    //     int q = 0;
    //     for(c = r->begin(); c != r->end(); c++){
    //         matrix[s][q] = 
    //     }
    // }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = vec2d[i][j];
        }
    }
    return;
}