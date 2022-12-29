#include "iostream"

#include "APVAnaTaskRun.hpp"
#include "TTree.h"
// #include "TFile.h"

#include "stdlib.h"
#include "getopt.h"

int Analysis(std::string infilename, std::string outfilename, int startn=0, int endn=-1, short threshold=100){

    // APVAnaTaskRun * bb = new APVAnaTaskRun("../data/kriss_data/apv_2022120725.txt"); //gamma
    // APVAnaTaskRun * bb = new APVAnaTaskRun("../data/kriss_data/apv_2022120803.txt"); //10% sheiding neutron
    APVAnaTaskRun * bb = new APVAnaTaskRun(infilename); //neutron

    bb->SetThreshold(threshold);
    bb->SetStartEntry(startn);
    bb->SetEndEntry(endn);
    bb->Analysis();
    bb->GetTree()->SaveAs(outfilename.c_str());

    return 0;
}

struct Arguments{
    std::string ifilename = "";
    std::string ofilename = "";
    int startn            = 0;
    int endn              = -1;
    short threshold       = 0;


    bool        b_ifilename = false;
    bool        b_ofilename = false;
    bool        b_startn    = false;
    bool        b_endn      = false;
    bool        b_threshold = false;

    Arguments(): ifilename(""),ofilename(""),startn(0), endn(-1), threshold(100),
                 b_ifilename(false), b_ofilename(false), b_startn(false), b_endn(false), b_threshold(false){;}

};

int main(int argc, char** argv){
  char c; // option
  Arguments args;

  static struct option long_options[] =
    {
      {"in"    , required_argument, 0, 'i'},
      {"out"   , required_argument, 0, 'o'},
      {"start" , required_argument, 0, 's'},
      {"end"   , required_argument, 0, 'e'},
      {"threshold" , required_argument, 0, 't'},
      {"help"  , no_argument,       0, 'h'},
      {0, 0, 0, 0}
    };

    int option_index = 0;
    while( (c = getopt_long(argc, argv, "i:o:s:e:t:h", long_options, &option_index)) != -1){
        switch(c){
            case 'i':
                args.ifilename  = std::string(optarg);
                args.b_ifilename = true;
                break;
            case 'o':
                args.ofilename   = std::string(optarg);
                args.b_ofilename = true;
                break;
            case 's':
                args.startn   = std::stoi(optarg);
                args.b_startn = true;
                break;
            case 'e':
                args.endn   = std::stoi(optarg);
                args.b_endn = true;
                break;
            case 't':
                args.threshold   = std::stoi(optarg);
                args.b_threshold = true;
                break;
            case 'h':
            std::cout<<"Single Run with Stert/End Entry"<<std::endl;
            std::cout<<"Available Options" <<std::endl;
            std::cout<<"-i, --in   \t input file(txt)    \t [REQUIRED]" <<std::endl;
            std::cout<<"-o, --out  \t output file(root)  \t [REQUIRED]" <<std::endl;
            std::cout<<"-s, --start\t start entry number \t [default=0]" <<std::endl;
            std::cout<<"-s, --end  \t end entry number   \t [default=all]" <<std::endl;
            std::cout<<"-t, --threshold\t threshold      \t [default=100]" <<std::endl;
            std::cout<<"-h, --help     \t this message" <<std::endl;
                return 0;
            case '?':
                printf("Unknown flag : %c", optopt);
                return 1;
        }
    }

    if (!(args.b_ifilename && args.b_ofilename)){
        std::cout<<"Input file name and output file name are necessary!"<<std::endl;
        return 1;
    }

    
    return Analysis(args.ifilename, args.ofilename, args.startn, args.endn, args.threshold);;
}