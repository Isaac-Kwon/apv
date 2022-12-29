#include "APVAnaTaskGraphSet1.hpp"

#include "string"
#include "APVStrip.hpp"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TTree.h"
#include "TPaveText.h"

APVAnaTaskGraphSet1::APVAnaTaskGraphSet1():APVAnaTaskBase(){;}

APVAnaTaskGraphSet1::APVAnaTaskGraphSet1(std::string filename, std::string name, short Nx, short Ny):
APVAnaTaskBase(filename, name, Nx, Ny){;}

void APVAnaTaskGraphSet1::GraphOne(int i, std::string name){
    ReadData();

    TTree * rt = GetRawTree();
    unsigned int * ii = GetIp();
    short *     x  = GetX();
    short *     y  = GetY();
    short       nx = GetNX();
    short       ny = GetNY();
    unsigned int n = GetN();

    rt->GetEntry(i);
    
    APVStrip * sx = new APVStrip(nx, x, "APVStripX");
    APVStrip * sy = new APVStrip(ny, y, "APVStripY");
    sx->FindBaseline();
    sy->FindBaseline();
    sx->Adjust();
    sy->Adjust();
    StripResult resx = sx->Analysis();
    StripResult resy = sy->Analysis();

    TCanvas * c1 = new TCanvas("c1","c1", 1200, 1200);
    c1->Divide(2,2);
    c1->cd(1);
    sx->GetGraph()->Draw();
    sx->GetF1()->Draw("SAME");
    sx->GetF2()->Draw("SAME");
    c1->cd(2);
    sy->GetGraph()->Draw();
    sy->GetF1()->Draw("SAME");
    sy->GetF2()->Draw("SAME");
    c1->cd(3);
    sx->GetGraphAdjusted()->Draw();
    sx->GetGraphAdjusted()->GetYaxis()->SetRangeUser(-400, 5000);
    sx->GetGraphAdjusted()->GetYaxis()->SetLimits(-400, 5000);
    TPaveText * pave_x = new TPaveText(0.6, 0.75, 0.95, 0.95, "NB NDC");
    pave_x->AddText(TString::Format("Mean: %.2f", resx.mean));
    pave_x->AddText(TString::Format("Stdev: %.2f", resx.stdev));
    pave_x->AddText(TString::Format("Skewness: %.2f", resx.skewness));
    pave_x->AddText(TString::Format("[%.1f,%.1f,%.1f]", resx.sum0,resx.sum1,resx.sum2));
    pave_x->Draw();
    c1->cd(4);
    sy->GetGraphAdjusted()->Draw();
    sy->GetGraphAdjusted()->GetYaxis()->SetRangeUser(-400, 5000);
    sy->GetGraphAdjusted()->GetYaxis()->SetLimits(-400, 5000);
    TPaveText * pave_y = new TPaveText(0.6, 0.75, 0.95, 0.95, "NB NDC");
    pave_y->AddText(TString::Format("Mean: %.2f", resy.mean));
    pave_y->AddText(TString::Format("Stdev: %.2f", resy.stdev));
    pave_y->AddText(TString::Format("Skewness: %.2f", resy.skewness));
    pave_y->AddText(TString::Format("[%.1f,%.1f,%.1f]", resy.sum0,resy.sum1,resy.sum2));
    pave_y->Draw();

    c1->SaveAs(name.c_str());

    delete sx;
    delete sy;

    return;
}

void APVAnaTaskGraphSet1::Analysis(){


}