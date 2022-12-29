#include "APVAnaTaskRun.hpp"

#include "string"
#include "TTree.h"
#include "iostream"

#include "APVStrip.hpp"

APVAnaTaskRun::APVAnaTaskRun():APVAnaTaskBase(){;}

APVAnaTaskRun::APVAnaTaskRun(std::string filename, std::string name, short Nx, short Ny):
APVAnaTaskBase(filename, name, Nx, Ny){;}

TTree* APVAnaTaskRun::MakeTree(){
    fTree = new TTree(TString::Format("Ana%s",GetName().c_str()), TString::Format("Analysis about %s",GetName().c_str()));
    fTree->Branch("I", &fbI, "I/I");
    fTree->Branch("X", &fbX, "mean/F:mean_f/F:peakstrip/S:peakvalue/S:sum0/F:sum0_f/F:sum1/F:sum1_f/F:nfired/S");
    fTree->Branch("Y", &fbY, "mean/F:mean_f/F:peakstrip/S:peakvalue/S:sum0/F:sum0_f/F:sum1/F:sum1_f/F:nfired/S");
    return fTree;
}

void APVAnaTaskRun::Analysis(){
    ReadData();
    if(fTree == nullptr) MakeTree();

    TTree * rt = GetRawTree();
    unsigned int * ii = GetIp();
    short *     x  = GetX();
    short *     y  = GetY();
    short       nx = GetNX();
    short       ny = GetNY();
    unsigned int n = GetN();

    for(int i=fStartEntry; i<n ; i++){
        if(fEndEntry > 0 && i>fEndEntry) break;
        std::cout<<"APVAnaTaskRun::Analysis - i="<<i<<std::endl;
        rt->GetEntry(i);
        APVStrip * sx = new APVStrip(nx, x, "APVStripX");
        APVStrip * sy = new APVStrip(ny, y, "APVStripY");

        StripResult rx = sx->Analysis(fThreshold);
        StripResult ry = sy->Analysis(fThreshold);
        fbI = i;
        fbX = rx;
        fbY = ry;
        
        fTree->Fill();

        delete sx;
        delete sy;
    }
}