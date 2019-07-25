
#include "readmatrix.h"

using namespace std;
// int main(){
//     createvector("l0_w.out", "testout.out");
//     return 0;
// }
vector<vector<long double>> createvector(string inputfile){
    vector<vector<long double>> v;
    vector<long double> tempv;
    double temp;
    string tempstr;
    ifstream input(inputfile);
    long double i;
    char delimiter;
    if(input.is_open()){
        while(getline(input,tempstr)){
            istringstream iss(tempstr);
            vector<long double> tempv;
            while(iss >> i){
                tempv.push_back(i);
                iss >> delimiter;
            }
            v.push_back(tempv);
        }
    }
    input.close();
    return v;
}