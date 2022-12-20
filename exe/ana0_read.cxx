#include "iostream"
// #include "APVAnaBase.hpp"
#include "APVAnaRun.hpp"
#include "TString.h"

int main(){
    APVAnaRun * bb = new APVAnaRun("../data/kriss_data/apv_2022120720.txt");
    // bb->Analysis();
    for(int i=0; i<100; i++){
        bb->GraphOne(i, TString::Format("c1_%d.pdf", i).Data());
    }

    // bb->ReadData();
    // bb->SaveTree("../testtree.root");
    return 0;
}