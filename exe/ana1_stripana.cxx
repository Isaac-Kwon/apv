#include "iostream"

#include "APVAnaTaskRun.hpp"
#include "TString.h"
#include "TCanvas.h"
#include "TTree.h"

int main(){
    // APVAnaTaskRun * bb = new APVAnaTaskRun("../data/kriss_data/apv_2022120803.txt"); //10% sheiding neutron 5669
    APVAnaTaskRun * bb = new APVAnaTaskRun("../data/kriss_data/apv_2022120725.txt"); //gamma 28439

    // for(int i=0; i<20; i++){
    //     // bb->GraphOne(i, TString::Format("c1_%d.pdf", i).Data());
    // }

    bb->SetThreshold(100);
    bb->SetEndEntry(1000);
    bb->Analysis();
    bb->GetTree()->SaveAs("../apv_2022120725.root");

    // bb->deadData();
    // bb->SaveTree("../testtree.root");
    return 0;
}