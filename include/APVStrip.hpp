#ifndef __APVSTRIP__
#define __APVSTRIP__

#include "string"

class TF1;
class TH1I;
class TGraph;

struct StripResult{
    float mean;   // mean without thres
    float mean_f; // mean with thres
    short peakstrip;
    short peakvalue;
    float sum0;   // sum0 without thres
    float sum0_f; // sum0 with thres
    float sum1;   // sum1 with thres
    float sum1_f; // sum1 with thres
    short nfired; // Nstrip over thres

    StripResult(): mean(0),mean_f(0),peakstrip(0),peakvalue(0),sum0(0),sum0_f(0),sum1(0),sum1_f(0),nfired(0){;}

    StripResult(const StripResult& oth){
        mean = oth.mean;
        mean_f = oth.mean_f;
        peakstrip = oth.peakstrip;
        peakvalue = oth.peakvalue;
        sum0 = oth.sum0;
        sum0_f = oth.sum0_f;
        sum1 = oth.sum1;
        sum1_f = oth.sum1_f;
        nfired = oth.nfired;
    }
};


class APVStrip{
    public:
    APVStrip(int n, short* val, std::string name="APVStrip0");
    ~APVStrip();
    void FindBaseline();
    void Adjust();
    StripResult Analysis(short thres=100, bool ignoreCompensate=false);

    const int     GetN()  {return fN;}
    short*  GetV()  {return fV;}
    TF1    * GetF1()      {return fF1;}
    TF1    * GetF2()      {return fF2;}
    TGraph * GetGraph()           {return fG0;}
    TGraph * GetGraphAdjusted()   {return fG1;}
    TH1I   * GetSigHist()         {return fH0;}
    TH1I   * GetSigHistAdjusted() {return fH1;}

    int  Integrate();
    float GetMean(short thres=-1);
    short GetFired(short thres=150, bool overcount=true);

    bool IsBaselined(){return fBaselined;}
    bool IsAdjusted(){return fAdjusted;}

    protected:
    private:
    std::string fName;

    const int   fN;
    short *     fV;

    TF1    * fF1 = nullptr;
    TF1    * fF2 = nullptr;

    TGraph * fG0 = nullptr; // Signal - RAW
    TGraph * fG1 = nullptr; // Signal - Compensated

    TH1I   * fH0 = nullptr; // SignalHistogram - RAW
    TH1I   * fH1 = nullptr; // SignalHistogram - Compensated

    bool fBaselined = false;
    bool fAdjusted  = false;
};

#endif