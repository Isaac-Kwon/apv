#ifndef __APVANARUN__
#define __APVANARUN__

#include "APVAnaBase.hpp"

class APVAnaRun: public APVAnaBase{
    public:
    APVAnaRun();
    APVAnaRun(std::string filename, std::string name="APVAna0", short Nx=256, short Ny=256);
    void Analysis() override;
    void GraphOne(int i, std::string name="c1.pdf");
    protected:
    private:
};

#endif
