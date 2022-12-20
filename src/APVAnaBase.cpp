#include "APVAnaBase.hpp"

#include "TTree.h"
#include "TString.h"
#include "cstdlib"
#include "iostream"

APVAnaBase::APVAnaBase(): fFileName(), fName("APVAna0"){;}

APVAnaBase::APVAnaBase(std::string filename, std::string name, short Nx, short Ny): fFileName(filename), fName(name), fNx(Nx), fNy(Ny){
    fX = (short*)std::malloc(sizeof(short)*fNx);
    fY = (short*)std::malloc(sizeof(short)*fNy);
}

APVAnaBase::APVAnaBase(const APVAnaBase& other):
    fFileName(other.fFileName),
    fName(other.fName),
    fNx(other.fNx),
    fNy(other.fNy),
    fN(other.fN),
    fI(other.fI){
    fX = (short*)std::malloc(sizeof(short)*fNx);
    fY = (short*)std::malloc(sizeof(short)*fNy);
}

APVAnaBase::~APVAnaBase(){
    std::free(fX);
    std::free(fY);
    if(fTree != nullptr) fTree->Delete();
}

void APVAnaBase::BuildTree(){
    fTree = new TTree(TString::Format("tree_%s",fName.c_str()), fName.c_str());
    fTree->Branch("i", &fI, "i/i");
    fTree->Branch("x", fX, TString::Format("x[%d]/S",fNx));
    fTree->Branch("y", fY, TString::Format("y[%d]/S",fNy));
}

void APVAnaBase::ReadData(){
    if(IsDataRead()) return;
    std::string tempstr;
    fIfs.open(fFileName);
    fIfs>>tempstr;
    fN = std::stoi(tempstr);
    
    std::cout<<"APVAnaBase::ReadData - " << fN <<" Event will be read"<<std::endl;

    if(fTree == nullptr){
        std::cout<<"APVAnaBase::ReadData - Tree is built automatically."<<std::endl;
        BuildTree();
    }

    for(int i=0; i<fN; i++){
        fI = i;
        for(int j=0; j<fNx; j++){
            fIfs>>tempstr;
            fX[j] = std::stoi(tempstr);
        }
        for(int j=0; j<fNy; j++){
            fIfs>>tempstr;
            fY[j] = std::stoi(tempstr);
        }
        fTree->Fill();
    }
    fIsDataRead=true;
}

void APVAnaBase::SaveRawTree(std::string filename){
    fTree->SaveAs(filename.c_str());
}

void APVAnaBase::Analysis(){std::cout<<"APVAnaBase::Analysis - virtual function is not overrided"<<std::endl;}