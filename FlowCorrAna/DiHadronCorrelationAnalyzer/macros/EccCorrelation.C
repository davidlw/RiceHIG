#include "TF2.h"
#include "TRandom3.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"

void EccCorrelation()
{
  TF2* func = new TF2("func","[0]*x+[1]*y+[2]",-1,1,-1,1);
  func->SetParameters(0,0,1);

  int Nevents = 1000000;
  int Ns=18;
  int nterms=6;

  TH2D* h2D = new TH2D("h2D","Theory;#epsilon_{2};#epsilon_{3}",50,0,1,50,0,1);
  TH2D* hh2D = new TH2D("hh2D","Simulation;#epsilon_{2};#epsilon_{3}",50,0,1,50,0,1);
  TH2D* hhh2D = new TH2D("hhh2D","Simulation;#epsilon^{2}_{2};#epsilon^{2}_{3}",50,0,1,50,0,1);

  for(int j=0;j<Nevents;j++)
  {
    double meanX=0;
    double meanY=0;
    double meanX2=0;
    double meanY2=0;
    double meanXY=0;

    double XPart[1000]={0};
    double YPart[1000]={0};

    double avgrsqcosphi[10]={0};
    double avgrsqsinphi[10]={0};
    double avgrsquared[10]={0};
    double eccPART[10]={0};
    double psiPART[10]={0};

    double rsquared = 0;
    double phipart = 0;

    for(int i=0;i<Ns;i++)
    {
      double xx=0;
      double yy=0;
      func->GetRandom2(xx,yy);
      XPart[i] = xx;
      YPart[i] = yy;
      if(sqrt(xx*xx+yy*yy)>1) {i--; continue;}

      meanX  += XPart[i];
      meanY  += YPart[i];
      meanX2 += XPart[i] * XPart[i];
      meanY2 += YPart[i] * YPart[i];
      meanXY += XPart[i] * YPart[i];
    }  

    meanX /= Ns;
    meanY /= Ns;
    meanX2 /= Ns;
    meanY2 /= Ns;
    meanXY /= Ns;

    for(int i=0;i<Ns;i++)
    {
      double xAshift = XPart[i]-meanX;
      double yAshift = YPart[i]-meanY;
      rsquared = xAshift*xAshift + yAshift*yAshift;
      phipart = TMath::ATan2(yAshift,xAshift);

      for(int iterm=0;iterm<nterms;iterm++)
      {
        avgrsqcosphi[iterm] += TMath::Power(sqrt(rsquared),iterm+1)*TMath::Cos((iterm+1)*phipart);
        avgrsqsinphi[iterm] += TMath::Power(sqrt(rsquared),iterm+1)*TMath::Sin((iterm+1)*phipart);
        avgrsquared[iterm] += TMath::Power(sqrt(rsquared),iterm+1);
      }
    }    

    for(int iterm=0;iterm<nterms;iterm++)
    {
      avgrsqcosphi[iterm] /= Ns;
      avgrsqsinphi[iterm] /= Ns;
      avgrsquared[iterm] /= Ns;

      eccPART[iterm]=TMath::Sqrt(avgrsqcosphi[iterm]*avgrsqcosphi[iterm]+avgrsqsinphi[iterm]*avgrsqsinphi[iterm])/avgrsquared[iterm];
      psiPART[iterm]=(TMath::ATan2(avgrsqsinphi[iterm],avgrsqcosphi[iterm])+TMath::Pi())/(iterm+1);
    }
    hh2D->Fill(eccPART[1],eccPART[2]);
    hhh2D->Fill(eccPART[1]*eccPART[1],eccPART[2]*eccPART[2]);
  }

  hh2D->Scale(1.0/hh2D->Integral("width"));

  TH1D* hecc2 = (TH1D*)hh2D->ProjectionX("ecc2",-1,-1,"e");
  TH1D* hecc3 = (TH1D*)hh2D->ProjectionY("ecc3",-1,-1,"e");
  hecc2->Scale(1.0/hecc2->Integral("width"));
  hecc3->Scale(1.0/hecc3->Integral("width"));

  TF1* func_e2 = new TF1("func_e2","([0]-1)*x*(1-x*x)**(0.5*[0]-1.5)",0,1);
  func_e2->SetParameter(0,Ns);
  TF1* func_e3 = new TF1("func_e3","([0]-1)*x*(1-x*x)**(0.5*[0]-1.5)",0,1);
  func_e3->SetParameter(0,Ns);

  hecc2->Fit("func_e2","RNO");
  hecc3->Fit("func_e3","RNO");

  TCanvas* c = new TCanvas("c","c",850,400);
  c->Divide(2,1);
  c->cd(1);
  hecc2->Draw("hist");
  func_e2->Draw("Lsame");
  c->cd(2);
  hecc3->Draw("hist");
  func_e3->Draw("Lsame");

   TF2* func2 = new TF2("func2","([0]-1)*[1]*([0]-1)*x*y*(2-x*x-y*y+[2]*([0]-1)*([0]-1)*x*x*y*y)**(0.5*[0]-1.5)",0,1,0,1);

//   TF2* func2 = new TF2("func2","([0]-1)*([0]-1)*x*y*(1-x*x-y*y+x*x*y*y)**(0.5*[0]-1.5)",0,1,0,1);
//   TF2* func2 = new TF2("func2","([0]-1)*([0]-1)*x*y*(1-2*x*y+x*x*y*y)**(0.5*[0]-1.5)",0,1,0,1);

   func2->SetParameter(0,Ns);
   func2->SetParameter(1,1000);
   func2->SetParameter(2,-0.005);
   hh2D->Fit("func2","RNO");
   hh2D->Fit("func2","RNO");
   hh2D->Fit("func2","RNO");

   for(int i=0;i<1000000;i++)
   {
     double xx=0;
     double yy=0;
     func2->GetRandom2(xx,yy);
     h2D->Fill(xx,yy);
   }

  h2D->Scale(1.0/h2D->Integral("width"));

   TCanvas* c3 = new TCanvas("c3","c3",850,400);
   c3->Divide(2,1);
   c3->cd(1);
   hh2D->Draw("surf1");
   c3->cd(2);
   h2D->Draw("surf1");
cout<<h2D->GetCorrelationFactor()<<" "<<hh2D->GetCorrelationFactor()<<endl;
cout<<hhh2D->GetCorrelationFactor()<<endl;
}
