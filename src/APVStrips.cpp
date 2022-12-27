#include "APVStrips.hpp"
#include "TF1.h"
#include "TGraph.h"
#include "TH1I.h"
#include "TMath.h"

APVStrips::APVStrips(int n, short* val, std::string name):fName(name), fN(n), fV(val) {;}

APVStrips::~APVStrips(){
    if(fF1!=nullptr) fF1->Delete();
    if(fF2!=nullptr) fF2->Delete();
    if(fG0!=nullptr) fG0->Delete();
    if(fG1!=nullptr) fG1->Delete();
    if(fH0!=nullptr) fH0->Delete();
    if(fH1!=nullptr) fH1->Delete();
}

void APVStrips::FindBaseline(){
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

void APVStrips::Adjust(){
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

StripResult APVStrips::Analysis(bool ignoreCompensate){
    if(!fAdjusted && !ignoreCompensate) Adjust();

    float sum0=0, sum1=0, sum2=0;
    for(int i=0; i<fN; i++){
        sum0 += fV[i];
        sum1 += fV[i] * i;
        sum2 += fV[i] * i * i;
    }

    StripResult ans;
    ans.mean = sum1/sum0;
    ans.variance = (sum2/sum0)-((ans.mean)*(ans.mean));
    ans.stdev = TMath::Sqrt(ans.variance);

    double temp;

    for(int i=0; i<fN; i++){
        double x = (i-ans.mean)/(ans.stdev);
        temp += x*x*x*3;
    }

    ans.skewness = temp/sum0;

    ans.sum0 = sum0;
    ans.sum1 = sum1;
    ans.sum2 = sum2;

    return ans;
}

int APVStrips::Integrate(){
    if(!IsAdjusted()) Adjust();

    //simple sum of values
    int ans = 0.;
    for(int i=0; i<GetN(); i++){
        ans+=fV[i];
    }

    return ans;
}

float APVStrips::GetMean(){
    if(!IsAdjusted()) Adjust();
    float sum0 = 0;
    for(int i=0; i<fN; i++){
        sum0 += fV[i];
    }
    return sum0/fN;
}

short APVStrips::GetFired(short thres, bool overcount){
    if(!IsAdjusted()) Adjust();
    short ans = 0;
    for(int i=0; i<fN; i++){
        if(overcount && fV[i] >= thres) ans++;
        if((!overcount) && fV[i] < thres) ans++;
    }
    return ans;
}


