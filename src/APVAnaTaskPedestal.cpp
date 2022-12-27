#include "APVAnaTaskPedestal.hpp"

#include "string"

APVAnaTaskPedestal::APVAnaTaskPedestal():APVAnaTaskBase(){;}

APVAnaTaskPedestal::APVAnaTaskPedestal(std::string filename, std::string name, short Nx, short Ny):
APVAnaTaskBase(filename, name, Nx, Ny){;}

void APVAnaTaskPedestal::Analysis(){;}