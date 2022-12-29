#ifndef __APVANARUN__
#define __APVANARUN__

#include "APVAnaTaskBase.hpp"
#include "APVStrip.hpp"

class TCanvas;
class TH1D;
class TH2D;

class APVAnaTaskRun: public APVAnaTaskBase{
    public:
    APVAnaTaskRun();
    APVAnaTaskRun(std::string filename, std::string name="APVAna0", short Nx=256, short Ny=256);
    // static void AnalysisOne(APVStrip* sx, APVStrip* sy) ;
    void Analysis() override;
    void SetThreshold(short val=100){fThreshold = val;}
    void SetStartEntry(int val=0){fStartEntry = val;}
    void SetEndEntry(int val=-1){fEndEntry = val;}
    TTree * GetTree(){return fTree;}
    protected:
    TTree * MakeTree();
    private:
    // TH2D * fhHitmapMean = nullptr; //hitmap [Mean]
    // TH2D * fhHitmapPeak = nullptr; //hitmap [Peak]
    // TH1D * fhAmpl       = nullptr; //Amplitudes (peak top)
    // TH1D * fh3=nullptr;            //Fired Strips
    TTree * fTree = nullptr;
    int         fStartEntry = 0;
    int         fEndEntry = -1;
    int         fbI;
    StripResult fbX;
    StripResult fbY;

    short fThreshold = 100;
};

#endif
