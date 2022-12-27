#ifndef __APVANAPEDESTAL__
#define __APVANAPEDESTAL__

#include "APVAnaTaskBase.hpp"
#include "string"

class APVAnaTaskPedestal: public APVAnaTaskBase{
    public:
    APVAnaTaskPedestal();
    APVAnaTaskPedestal(std::string filename, std::string name="APVAna0ped", short Nx=256, short Ny=256);
    void Analysis();
    protected:
    private:
};

#endif
