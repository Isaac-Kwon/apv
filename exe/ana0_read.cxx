#include "iostream"

#include "APVAnaTaskRun.hpp"
#include "TString.h"
#include "TCanvas.h"

int main(){
    // APVAnaRun * bb = new APVAnaRun("../data/kriss_data/apv_2022120725.txt"); //gamma
    // APVAnaRun * bb = new APVAnaRun("../data/kriss_data/apv_2022120803.txt"); //10% sheiding neutron
    APVAnaTaskRun * bb = new APVAnaTaskRun("../data/kriss_data/apv_2022120725.txt"); //neutron

    for(int i=0; i<20; i++){
        bb->GraphOne(i, TString::Format("c1_%d.pdf", i).Data());
    }

    // bb->ReadData();
    // bb->SaveTree("../testtree.root");
    return 0;
}