#include "APVAnaRun.hpp"

#include "string"
#include "APVStrips.hpp"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TTree.h"
#include "TPaveText.h"

APVAnaRun::APVAnaRun():APVAnaBase(){;}

APVAnaRun::APVAnaRun(std::string filename, std::string name, short Nx, short Ny):
APVAnaBase(filename, name, Nx, Ny){;}

void APVAnaRun::GraphOne(int i, std::string name){
    ReadData();

    TTree * rt = GetRawTree();
    unsigned int * ii = GetIp();
    short * x = GetX();
    short * y = GetY();
    short nx = GetNX();
    short ny = GetNY();
    unsigned int n = GetN();

    rt->GetEntry(i);
    
    APVStrips * sx = new APVStrips(nx, x, "APVStripX");
    APVStrips * sy = new APVStrips(ny, y, "APVStripY");
    sx->FindBaseline();
    sy->FindBaseline();
    sx->Compensate();
    sy->Compensate();
    StripResult resx = sx->Analysis();
    StripResult resy = sy->Analysis();

    TCanvas * c1 = new TCanvas("c1","c1", 1200, 1200);
    c1->Divide(2,2);
    c1->cd(1);
    // std::cout<<"Plot1"<<std::endl;
    sx->GetGraph()->Draw();
    sx->GetF1()->Draw("SAME");
    sx->GetF2()->Draw("SAME");
    c1->cd(2);
    // std::cout<<"Plot2"<<std::endl;
    sy->GetGraph()->Draw();
    sy->GetF1()->Draw("SAME");
    sy->GetF2()->Draw("SAME");
    c1->cd(3);
    // std::cout<<"Plot3"<<std::endl;
    sx->GetGraphCompensated()->Draw();
    sx->GetGraphCompensated()->GetYaxis()->SetRangeUser(-400, 5000);
    sx->GetGraphCompensated()->GetYaxis()->SetLimits(-400, 5000);
    TPaveText * pave_x = new TPaveText(0.6, 0.75, 0.95, 0.95, "NB NDC");
    pave_x->AddText(TString::Format("Mean: %.2f", resx.mean));
    pave_x->AddText(TString::Format("Stdev: %.2f", resx.stdev));
    pave_x->AddText(TString::Format("Skewness: %.2f", resx.skewness));
    pave_x->AddText(TString::Format("[%.1f,%.1f,%.1f]", resx.sum0,resx.sum1,resx.sum2));
    pave_x->Draw();
    c1->cd(4);
    // std::cout<<"Plot4"<<std::endl;
    sy->GetGraphCompensated()->Draw();
    sy->GetGraphCompensated()->GetYaxis()->SetRangeUser(-400, 5000);
    sy->GetGraphCompensated()->GetYaxis()->SetLimits(-400, 5000);
    TPaveText * pave_y = new TPaveText(0.6, 0.75, 0.95, 0.95, "NB NDC");
    pave_y->AddText(TString::Format("Mean: %.2f", resy.mean));
    pave_y->AddText(TString::Format("Stdev: %.2f", resy.stdev));
    pave_y->AddText(TString::Format("Skewness: %.2f", resy.skewness));
    pave_y->AddText(TString::Format("[%.1f,%.1f,%.1f]", resy.sum0,resy.sum1,resy.sum2));
    pave_y->Draw();
    // std::cout<<"Save"<<std::endl;

    c1->SaveAs(name.c_str());

    delete sx;
    delete sy;

    return;
}

void APVAnaRun::Analysis(){

}


// ProfileResult AnalyzeOne(short* val){
//     // 0 to 0.5, 0.5 to 1 fit pol1 Linear Robust 0.7
//     // Get Signal (Integral within linear pol1)
//     // Get Strip Multiplicity within 2sigma of pol1.
//     // Fit("pol1", "ROB=0.68")

//     //make profile graph
//     if(g==nullptr) g = new TGraph();
//     g->Clear();

//     size_t sz = size();
//     for(int i=0; i<sz; i++){
//         g->SetPoint(i, i, at(i));
//     }

//     //make baseline

//     int half = sz/2;
//     f1 = new TF1("", "pol1", 0, half-0.5);
//     f2 = new TF1("", "pol1", half-0.5, sz);

//     g->Fit(f1, "R ROB=0.68 0 Q");
//     g->Fit(f2, "R ROB=0.68 0 Q");

//     //make signal distribution over baseline
//     if(h==nullptr) h = new TH1I("", "signal dist", 100, -500, 500);
//     h->Clear();
//     for(int i=0; i<sz; i++){
//         TF1 * f;
//         if(i<half){f=f1;}else{f=f2;}
//         h->Fill(at(i)-(f->Eval(i)));
//     }
//     fg1 = new TF1("", "gaus", -500, 500);
//     h->Fit(fg1, "0 Q");

//     //detect outlier channel : 2.5 sigma outlier, from gaus distribution
//     float cm = fg1->GetParameter("Mean");
//     float cs = fg1->GetParameter("Sigma");

//     int overlier  = 0;
//     int underlier = 0;
//     int oversum   = 0;
//     int undersum  = 0;

//     for(int i=0; i<sz; i++){
//         TF1 * f;
//         if(i<half){f=f1;}else{f=f2;}
//         if(((at(i)-(f->Eval(i)))-cm) > (4*cs)){
//             //if over 2.5sigma
//             overlier ++;
//             oversum += (at(i)-(f->Eval(i)));

//         }else if(((at(i)-(f->Eval(i)))-cm) < (4*cs)){
//             //if under -2.5sigma
//             underlier ++;
//             undersum += (at(i)-(f->Eval(i)));
//         }else{
//             //otherwise
//         }
//     }

//     ProfileResult res = {
//         overlier, // Overlier
//         oversum, // OverSum
//         underlier, // Underlier
//         undersum, // UnderSum
//         f1->GetParameter("p0"),// F1a
//         f1->GetParameter("p1"),// F1b
//         f2->GetParameter("p0"),// F2a
//         f2->GetParameter("p1") // F2b
//     };

//     // h->Delete();
//     return res;
// }