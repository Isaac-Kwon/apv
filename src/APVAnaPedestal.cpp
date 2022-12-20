#include "APVAnaPedestal.hpp"

#include "string"

APVAnaPedestal::APVAnaPedestal():APVAnaBase(){;}

APVAnaPedestal::APVAnaPedestal(std::string filename, std::string name, short Nx, short Ny):
APVAnaBase(filename, name, Nx, Ny){;}

void APVAnaPedestal::Analysis(){;}