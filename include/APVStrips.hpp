#ifndef __APVSTRIPS__
#define __APVSTRIPS__

#include "string"

class TF1;
class TH1I;
class TGraph;

struct StripResult{
    float mean;
    float stdev;
    float variance;
    float skewness;
    float sum0;
    float sum1;
    float sum2;
};


class APVStrips{
    public:
    APVStrips(int n, short* val, std::string name="APVStrip0");
    ~APVStrips();
    void FindBaseline();
    void Compensate();
    StripResult Analysis(bool ignoreCompensate=false);

    const int     GetN()  {return fN;}
    short*  GetV()  {return fV;}
    TF1    * GetF1()      {return fF1;}
    TF1    * GetF2()      {return fF2;}
    TGraph * GetGraph()              {return fG0;}
    TGraph * GetGraphCompensated()   {return fG1;}
    TH1I   * GetSigHist()            {return fH0;}
    TH1I   * GetSigHistCompensated() {return fH1;}

    bool IsBaselined(){return fBaselined;}
    bool IsCompensated(){return fCompensated;}

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

    bool fBaselined   = false;
    bool fCompensated = false;
};

#endif