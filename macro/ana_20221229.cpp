
#include "TChain.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"

void ana_20221229(){

    TChain * ch = new TChain("AnaAPVAna0");
    ch->Add("./data/processed/apv_2022120725_*.root"); //Cd plate 100% 28439
    float tti = 28439.*0.4;
    int setnum = 1;
    // ch->Add("./data/processed/apv_2022120803_*.root");    //Cd plate 10% 5669
    // float tti = 5669.;
    // int setnum = 2;


    TH2D* h1 = new TH2D("h1", "hitmap [fired mean]", 256, 0, 256, 256, 0, 256);
    ch->Draw("X.mean_f:Y.mean_f >> h1", "", "goff");
    h1->Scale(3600./tti);

    TH1D* h2x = new TH1D("h2x", "ADC[X] Sum [fired]", 100, 0, 25000);
    TH1D* h2y = new TH1D("h2y", "ADC[Y] Sum [fired]", 100, 0, 25000);
    TH2D* h2xy = new TH2D("h2xy", "ADC[XY] Sum [fired]", 100, 0, 25000, 100, 0, 25000);
    TH1D* h2sum = new TH1D("h2sum", "ADC[X+Y] Sum [fired]", 200, 0, 50000);
    ch->Draw("X.sum0_f >> h2x", "", "goff");
    ch->Draw("Y.sum0_f >> h2y", "", "goff");
    ch->Draw("X.sum0_f:Y.sum0_f >> h2xy", "", "goff");
    ch->Draw("X.sum0_f + Y.sum0_f >> h2sum", "", "goff");
    h2x->Scale(3600./tti);
    h2y->Scale(3600./tti);
    h2xy->Scale(3600./tti);
    h2sum->Scale(3600./tti);

    TH1D* h3x = new TH1D("h3x", "FiredStrip[X] [fired]", 50, 0, 50);
    TH1D* h3y = new TH1D("h3y", "FiredStrip[Y] [fired]", 50, 0, 50);
    TH2D* h3xy = new TH2D("h3xy", "FiredStrip[XY] [fired]", 50, 0, 50, 50, 0, 50);
    TH1D* h3sum = new TH1D("h3sum", "FiredStrip[X+Y] [fired]", 100, 0, 100);
    ch->Draw("X.nfired >> h3x", "", "goff");
    ch->Draw("Y.nfired >> h3y", "", "goff");
    ch->Draw("X.nfired:Y.nfired >> h3xy", "", "goff");
    ch->Draw("X.nfired + Y.nfired >> h3sum", "", "goff");
    h3x->Scale(3600./tti);
    h3y->Scale(3600./tti);
    h3xy->Scale(3600./tti);
    h3sum->Scale(3600./tti);


    TH2D* h4x = new TH2D("h4x", "ADC[X+Y]:FiredStrip[X+Y]", 100, 0, 25000, 50, 0, 50);
    TH2D* h4y = new TH2D("h4y", "ADC[X+Y]:FiredStrip[X+Y]", 100, 0, 25000, 50, 0, 50);
    TH2D* h4sum = new TH2D("h4sum", "ADC[X+Y]:FiredStrip[X+Y]", 200, 0, 50000, 100, 0, 100);
    ch->Draw("X.nfired:X.sum0_f >> h4x", "", "goff");
    ch->Draw("Y.nfired:Y.sum0_f >> h4y", "", "goff");
    ch->Draw("(X.nfired+Y.nfired):(X.sum0_f+Y.sum0_f) >> h4sum", "", "goff");
    h4x->Scale(3600./tti);
    h4y->Scale(3600./tti);
    h4sum->Scale(3600./tti);

    TCanvas * c1 = new TCanvas("c1", "c1", 1500, 1500);
    h1->Draw("COLZ");

    TCanvas * c2 = new TCanvas("c2", "c2", 3000, 3000);
    c2->Divide(2,2);
    c2->cd(1);
    h2x->Draw("COLZ");
    c2->cd(2);
    h2y->Draw("COLZ");
    c2->cd(3);
    h2xy->Draw("COLZ");
    c2->cd(4);
    h2sum->Draw("COLZ");

    TCanvas * c3 = new TCanvas("c3", "c3", 3000, 3000);
    c3->Divide(2,2);
    c3->cd(1);
    h3x->Draw("COLZ");
    c3->cd(2);
    h3y->Draw("COLZ");
    c3->cd(3);
    h3xy->Draw("COLZ");
    c3->cd(4);
    h3sum->Draw("COLZ"); 

    TCanvas * c4 = new TCanvas("c4", "c4", 3000, 3000);
    c4->Divide(2,2);
    c4->cd(1);
    h4x->Draw("COLZ");
    c4->cd(2);
    h4y->Draw("COLZ");
    c4->cd(3);
    h4sum->Draw("COLZ");

    c1->SaveAs(TString::Format("c1_%d.png",setnum));
    c2->SaveAs(TString::Format("c2_%d.png",setnum));
    c3->SaveAs(TString::Format("c3_%d.png",setnum));
    c4->SaveAs(TString::Format("c4_%d.png",setnum));

}