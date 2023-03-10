#ifndef __APVANATASKBASE__
#define __APVANATASKBASE__

#include "string"
#include "fstream"

class TTree;

class APVAnaTaskBase{
    public:
    APVAnaTaskBase();
    APVAnaTaskBase(std::string filename, std::string name="APVAna0", short Nx=256, short Ny=256);
    APVAnaTaskBase(const APVAnaTaskBase& other);
    ~APVAnaTaskBase();

    void    BuildTree();
    void    ReadData();
    void    SaveRawTree(std::string filename);
    TTree * GetRawTree()   {return fTree;}

    unsigned int   GetI()  {return fI;}
    unsigned int * GetIp() {return &fI;}
    short *        GetX()  {return fX;}
    short *        GetY()  {return fY;}
    short          GetNX() {return fNx;}
    short          GetNY() {return fNy;}
    unsigned int   GetN()  {return fN;}

    std::string    GetFileName() {return fFileName;}
    std::string    GetName()     {return fName;}

    virtual void   Analysis();
    bool           IsDataRead()  {return fIsDataRead;}

    protected:
    private:
    std::ifstream fIfs;
    std::string   fFileName;
    std::string   fName;
    TTree       * fTree;

    //number of strip
    short fNx = 256;
    short fNy = 256;

    //number of event (hit)
    unsigned int fN;

    //tree elements
    unsigned int fI; // TTree variable i/i
    short      * fX; // TTree variable x/s
    short      * fY; // TTree variable y/s

    bool fIsDataRead = false;

};

#endif