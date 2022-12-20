#ifndef __APVANABASE__
#define __APVANABASE__

#include "string"
#include "fstream"

class TTree;

class APVAnaBase{
    public:
    APVAnaBase();
    APVAnaBase(std::string filename, std::string name="APVAna0", short Nx=256, short Ny=256);
    APVAnaBase(const APVAnaBase& other);
    ~APVAnaBase();

    void BuildTree();
    void ReadData();
    void SaveRawTree(std::string filename);
    TTree * GetRawTree(){return fTree;}

    unsigned int GetI(){return fI;}
    unsigned int * GetIp(){return &fI;}
    short * GetX(){return fX;}
    short * GetY(){return fY;}
    short   GetNX(){return fNx;}
    short   GetNY(){return fNy;}
    unsigned int GetN(){return fN;}

    std::string GetFileName(){return fFileName;}
    std::string GetName(){return fName;}

    virtual void Analysis();
    bool IsDataRead(){return fIsDataRead;}

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
    unsigned int fI;
    short * fX;
    short * fY;

    //
    bool fIsDataRead = false;

};

#endif