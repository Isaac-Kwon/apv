#ifndef __APVANATASKGRAPHONE__
#define __APVANATASKGRAPHONE__

#include "APVAnaTaskBase.hpp"

class TCanvas;

class APVAnaTaskGraphSet1: public APVAnaTaskBase{
    public:
    APVAnaTaskGraphSet1();
    APVAnaTaskGraphSet1(std::string filename, std::string name="APVAna0", short Nx=256, short Ny=256);
    void SetSelection();
    void GraphOne(int i, std::string name="c1.pdf");
    void Analysis() override;
    // void GraphOne(int i, TCanvas* c);
    protected:
    private:
    // TTree * fTreeRaw = nullptr;
};

#endif
