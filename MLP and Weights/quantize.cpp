#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <sstream>


using namespace std;

int main(){
    ifstream input;
    ofstream output;
    string currentfile = "";
    string currentfileo = "";
    stringstream line;
    vector<vector<int>> data;
    for(int i=0; i<=3; i++){
        if(i == 0){
            currentfile = "l0_b";
            currentfileo = "l0_bq";
            
        }
        else if(i == 1){
            currentfile = "l2_b";
            currentfileo = "l2_bq";
        }
        else if(i == 2){
            currentfile = "l0_w";
            currentfileo = "l0_wq";
        }
        else if (i == 3){
            currentfile = "l2_w";
            currentfileo = "l2_wq";
        }
        else {
            break;
        }
        input.open(currentfile);
        output.open(currentfileo);
        if(input.is_open() && output.is_open()){
            while(!input.eof()){
                int j=0;
                while(getline(input, line)){
                   
               } 
            }
        }


    }

}