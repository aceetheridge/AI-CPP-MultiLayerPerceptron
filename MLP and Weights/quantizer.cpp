#include "readmatrix.h"
#include <iostream>
using namespace std;

void quantize(string in, string out);
int main(){
    string fileout;
    string filein;
    for(int i =0; i<=3; i++){
        if(i == 0){
            fileout = "l0_bout.out";
            filein = "l0_b.out";
            quantize(filein,fileout);
        }
        else if(i == 1){
            fileout ="l0_wout.out";
            filein = "l0_w.out";
            quantize(filein,fileout);
        }
        else if(i == 2){
            fileout ="l2_wout.out";
            filein = "l2_w.out";
            quantize(filein,fileout);
        }
        else if(i == 3){
            fileout ="l2_bout.out";
            filein = "l2_b.out";
            quantize(filein,fileout);
        }
        
    }
    return 0;
}

void quantize(string in, string out){
    vector<vector<long double>> poop;
    vector<vector<long double>> outvec;
    ofstream outfile(out);
    poop = createvector(in);
    vector<vector<long double>>::iterator row;
    vector<long double>::iterator col;
    for(row = poop.begin(); row !=poop.end(); row++){
        vector<long double> tempv;
        for(col = row->begin(); col != row->end();col++){
            tempv.push_back(int((*col*16)));
        }
        outvec.push_back(tempv);
    }
    for (auto rows : outvec){
        for(auto el : rows){
            outfile << el << ' ';
        }
        outfile << endl;
    }
    outfile.close();
    return;


}