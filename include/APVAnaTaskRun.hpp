#ifndef __APVANARUN__
#define __APVANARUN__

#include "APVAnaTaskBase.hpp"

class TCanvas;

class APVAnaTaskRun: public APVAnaTaskBase{
    public:
    APVAnaTaskRun();
    APVAnaTaskRun(std::string filename, std::string name="APVAna0", short Nx=256, short Ny=256);
    void Analysis() override;
    void GraphOne(int i, std::string name="c1.pdf");
    protected:
    private:
};

#endif
