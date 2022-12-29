#include "APVStrip.hpp"
#include "TF1.h"
#include "TGraph.h"
#include "TH1I.h"
#include "TMath.h"

APVStrip::APVStrip(int n, short* val, std::string name):fName(name), fN(n), fV(val) {;}

APVStrip::~APVStrip(){
    if(fF1!=nullptr) fF1->Delete();
    if(fF2!=nullptr) fF2->Delete();
    if(fG0!=nullptr) fG0->Delete();
    if(fG1!=nullptr) fG1->Delete();
    if(fH0!=nullptr) fH0->Delete();
    if(fH1!=nullptr) fH1->Delete();
}

void APVStrip::FindBaseline(){
    fG0 = new TGraph();
    fH0 = new TH1I(TString::Format("%sh0",fName.c_str()), fName.c_str(),
                                  410, -100, 4000);

    for(int i=0; i<fN; i++){
        fG0->SetPoint(i,i,fV[i]);
        fH0->Fill(fV[i]);
    }

    fF1 = new TF1("fx1", "pol1", 0, (fN/2)+0.5);
    fF2 = new TF1("fx2", "pol1", (fN/2)+0.5, fN);

    fG0->Fit(fF1, "R ROB=0.68 0 Q");
    fG0->Fit(fF2, "R ROB=0.68 0 Q");
    
    fBaselined = true;
}

void APVStrip::Adjust(){
    if(!fBaselined) FindBaseline();
    

    fG1 = new TGraph();
    fH1 = new TH1I(TString::Format("%sh1",fName.c_str()), fName.c_str(),
                                  410, -100, 4000);
    for(int i=0; i<fG0->GetN(); i++){
        double x,y;
        fG0->GetPoint(i,x,y);
        
        if(x < (fN/2)+0.5){
            fG1->SetPoint(i, x, y-(fF1->Eval(x)));
            fV[i] -= fF1->Eval(x);
            fH1->Fill(fV[i]);
        }else{
            fG1->SetPoint(i, x, y-(fF2->Eval(x)));
            fV[i] -= fF2->Eval(x);
            fH1->Fill(fV[i]);
        }
    }

    fAdjusted = true;
}

StripResult APVStrip::Analysis(short thres, bool ignoreCompensate){
    if(!fAdjusted && !ignoreCompensate) Adjust();

    float sum0=0, sum1=0, sum2=0, sum0_f=0, sum1_f=0;
    short nfired=0, peakstrip=-1, peakvalue=-1 ;
    for(int i=0; i<fN; i++){
        sum0 += fV[i];
        sum1 += fV[i] * i;
        if(fV[i]>thres){
            sum0_f += fV[i];
            sum1_f += fV[i] * i;
            nfired++;
        }
        
        if(peakvalue < fV[i]){
            peakvalue = fV[i];
            peakstrip = i;
        }
    }

    StripResult ans;

    ans.mean   = sum1/sum0;
    ans.mean_f = sum1_f/sum0_f;
    ans.sum0   = sum0;
    ans.sum0_f = sum0_f;
    ans.sum1   = sum1;
    ans.sum1_f = sum1_f;
    ans.nfired = nfired;
    ans.peakstrip = peakstrip;
    ans.peakvalue = peakvalue;

    return ans;
}

int APVStrip::Integrate(){
    if(!IsAdjusted()) Adjust();

    //simple sum of values
    int ans = 0.;
    for(int i=0; i<GetN(); i++){
        ans+=fV[i];
    }

    return ans;
}

float APVStrip::GetMean(short thres){
    if(!IsAdjusted()) Adjust();
    float sum0 = 0;
    int   n    = 0;
    for(int i=0; i<fN; i++){
        if(fV[i]>thres){
            sum0 += fV[i];
            n++;
        }
    }
    return sum0/n;
}

short APVStrip::GetFired(short thres, bool overcount){
    if(!IsAdjusted()) Adjust();
    short ans = 0;
    for(int i=0; i<fN; i++){
        if(overcount && fV[i] >= thres) ans++;
        if((!overcount) && fV[i] < thres) ans++;
    }
    return ans;
}


