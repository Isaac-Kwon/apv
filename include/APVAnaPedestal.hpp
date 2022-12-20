#ifndef __APVANAPEDESTAL__
#define __APVANAPEDESTAL__

#include "APVAnaBase.hpp"
#include "string"

class APVAnaPedestal: public APVAnaBase{
    public:
    APVAnaPedestal();
    APVAnaPedestal(std::string filename, std::string name="APVAna0ped", short Nx=256, short Ny=256);
    void Analysis();
    protected:
    private:
};

#endif
