#include <vector>
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TTree.h"
#include "TMath.h"
#include "TFile.h"

#define PI 3.141593

void ExpandError(TH1D* h, double factor)
{
  for(int i=1;i<=h->GetNbinsX();i++)
   h->SetBinError(i,h->GetBinError(i)*factor);
}

TTree* GetTree(TString filename,TString treename)
{
  TFile* f = new TFile(filename.Data());
  TTree* h = (TTree*)f->Get(treename);
  return h;
}

TH2D* GetHist(TString filename, TString dir, TString histname)
{
  TFile* f = new TFile(filename.Data());  
  TH2D* h = (TH2D*)f->Get(Form("%s/%s",dir.Data(),histname.Data()));

//  h->SetDirectory(0);
//  f->Close();
  return h;
}

TH2D* GetHist_Old(TString filename, TString histname)
{
  TFile* f = new TFile(filename.Data());
  TH2D* h = (TH2D*)f->Get(Form("%s",histname.Data()));

  return h;
}

TH1D* HistStatErr(TH1D* h[], TH1D* haverage, int size)
{
  cout<<h[0]->GetEntries()<<endl;
  for(int j=1;j<=h[0]->GetNbinsX();j++)
  {
    double sigma=0;
    for(int i=0;i<size;i++)
      sigma += (h[i]->GetBinContent(j)-haverage->GetBinContent(j))*(h[i]->GetBinContent(j)-haverage->GetBinContent(j));
    haverage->SetBinError(j,sqrt(sigma/size));
  }
  return haverage;
}

TH2D* Get2DSignal(TString filename, TString dir, int iptbin, int jptbin)
{
  TFile* f = new TFile(filename.Data());

  TH2D* hsignal = (TH2D*)f->Get(Form("%s/signal_trg%d_ass%d",dir.Data(),iptbin,jptbin));
  TH1D* hmult = (TH1D*)f->Get(Form("%s/multcorr_trg_%d",dir.Data(),iptbin));
  TH1D* hpt_trg = (TH1D*)f->Get(Form("%s/ptcorr_signal_trg_%d",dir.Data(),iptbin));
  TH1D* hpt_ass = (TH1D*)f->Get(Form("%s/ptcorr_signal_ass_%d",dir.Data(),jptbin));  
  if(!hpt_trg) hpt_trg = (TH1D*)f->Get(Form("%s/ptcorr_trg_%d",dir.Data(),iptbin));
  if(!hpt_ass) hpt_ass = (TH1D*)f->Get(Form("%s/ptcorr_ass_%d",dir.Data(),jptbin));

//  int ntrgs = hpt_trg->Integral();

  int ntrgs = hmult->Integral(2,10000,"X");
  if(fabs(hpt_trg->GetMean()-hpt_ass->GetMean())<0.0005) ntrgs = hmult->Integral(3,10000,"X");

  double mean=0;
/*
  if(iptbin==jptbin)
  { 
    hmult->SetAxisRange(2,10000,"X");
    mean=hmult->GetMean();
    hsignal->Scale(mean/(mean-1));
  }
*/
  hsignal->Scale(1.0/ntrgs);
  hsignal->GetXaxis()->CenterTitle();
  hsignal->GetYaxis()->CenterTitle();
  hsignal->GetZaxis()->CenterTitle();
  hsignal->SetZTitle("S(#Delta#eta,#Delta#phi)");

  hsignal->SetDirectory(0);
  f->Close();
  return hsignal;
}

TH2D* Get2DBackground(TString filename, TString dir, int iptbin, int jptbin)
{
  TFile* f = new TFile(filename.Data());

  TH2D* hbackground = (TH2D*)f->Get(Form("%s/background_trg%d_ass%d",dir.Data(),iptbin,jptbin));
  TH1D* hmult = (TH1D*)f->Get(Form("%s/multcorr_ass_%d",dir.Data(),jptbin));
  TH1D* hpt_trg= (TH1D*)f->Get(Form("%s/ptcorr_signal_trg_%d",dir.Data(),iptbin));
  TH1D* hpt_ass = (TH1D*)f->Get(Form("%s/ptcorr_signal_ass_%d",dir.Data(),jptbin));
  if(!hpt_trg) hpt_trg = (TH1D*)f->Get(Form("%s/ptcorr_trg_%d",dir.Data(),iptbin));
  if(!hpt_ass) hpt_ass = (TH1D*)f->Get(Form("%s/ptcorr_ass_%d",dir.Data(),jptbin));

  int ntrg = hpt_trg->Integral();
/*
  int nasss = hmult->Integral(2,10000,"X");
  if(fabs(hpt_trg->GetMean()-hpt_ass->GetMean())<0.01) nasss = hmult->Integral(3,10000,"X");
*/
  double mean=0;
/*
  if(iptbin==jptbin) 
  { 
    hmult->SetAxisRange(2,10000,"X");
    mean=hmult->GetMean();
    hbackground->Scale(mean/(mean-1));
  }
*/
  hbackground->Scale(1.0/ntrg);
  hbackground->GetXaxis()->CenterTitle();
  hbackground->GetYaxis()->CenterTitle();
  hbackground->GetZaxis()->CenterTitle();
  hbackground->SetZTitle("B(#Delta#eta,#Delta#phi)");

  hbackground->SetDirectory(0);
  f->Close();
  return hbackground;
}

TH1D* Get1DSignaldPhi(TString filename, int iptbin, int jptbin, double detamin, double detamax)
{
  TFile* f = new TFile(filename.Data());
  
  TH2D* hsignal = (TH2D*)f->Get(Form("signal_trg%d_ass%d",iptbin,jptbin));
  
  int xmin = hsignal->GetXaxis()->FindBin(detamin);
  int xmax = hsignal->GetXaxis()->FindBin(detamax);

  TH1D* hsignal_phi = (TH1D*)hsignal->ProjectionY("signal_phi",xmin,xmax,"e");
  TH1D* hmult = (TH1D*)f->Get(Form("multcorr_trg_%d",iptbin));

  double xbinwidth = hsignal->GetXaxis()->GetBinWidth(1);
  int ntrgs=0;
//  if(iptbin==jptbin) ntrgs = hmult->Integral(3,10000,"X");
//  else ntrgs = hmult->Integral(2,10000,"X");
  ntrgs = hmult->Integral(2,10000,"X");

  hsignal_phi->Scale(xbinwidth/ntrgs);

  hsignal->SetDirectory(0);
  f->Close();
  return hsignal_phi;
}

TH1D* Get1DCFdPhi(TString filename, int iptbin, int jptbin, double detamin, double detamax)
{
  TFile* f = new TFile(filename.Data());

  TH2D* hsignal = (TH2D*)f->Get(Form("signal_trg%d_ass%d",iptbin,jptbin));
  TH2D* hbackground = (TH2D*)f->Get(Form("background_trg%d_ass%d",iptbin,jptbin));

  int xmin = hsignal->GetXaxis()->FindBin(detamin);
  int xmax = hsignal->GetXaxis()->FindBin(detamax);

  TH1D* hsignal_phi = (TH1D*)hsignal->ProjectionY("signal_phi",xmin,xmax,"e");
  if(hsignal_phi->Integral()) hsignal_phi->Scale(1.0/hsignal_phi->Integral());
  TH1D* hbackground_phi = (TH1D*)hbackground->ProjectionY("background_phi",xmin,xmax,"e");
  if(hbackground_phi->Integral()) hbackground_phi->Scale(1.0/hbackground_phi->Integral());
cout<<hbackground_phi->Integral()<<" "<<hsignal_phi->Integral()<<endl;
  TH1D* hcorr_phi = (TH1D*)hsignal_phi->Clone("correlation_phi");
  hcorr_phi->Add(hbackground_phi,-1);
  hcorr_phi->Divide(hbackground_phi);

//  TH1D* hmult = (TH1D*)f->Get(Form("multcorr_ass_%d",jptbin));
  TH1D* hmult = (TH1D*)f->Get(Form("multcorr_trg_%d",jptbin));

/*
  int nEvents = 0;
  if(iptbin==jptbin) 
    nEvents = hmult->Integral(3,10000);
  else
    nEvents = hmult->Integral(2,10000);
*/
  double mean = 0;
  if(iptbin==jptbin)
  {
    hmult->SetAxisRange(2,10000,"X");
    mean = hmult->GetMean()-1;
  }
  else
  {
    hmult->SetAxisRange(1,10000,"X");
    mean = hmult->GetMean();
  }

  hcorr_phi->Scale(mean);
//  hcorr_phi->Scale(scale/nEvents);

//  hcorr_phi->SetAxisRange(-1.98,3.35,"Y"); //3X4
//  hcorr_phi->SetAxisRange(-1.18,1.85,"Y"); //$X4
  hcorr_phi->SetAxisRange(-1.2,1.8.,"Y"); 
  hcorr_phi->SetAxisRange(0,PI,"X");
  hcorr_phi->GetXaxis()->CenterTitle();
  hcorr_phi->GetYaxis()->CenterTitle();
  hcorr_phi->SetYTitle("R(#Delta#phi)");
  hcorr_phi->GetXaxis()->SetTitleSize(hcorr_phi->GetXaxis()->GetTitleSize()*1.5);
  hcorr_phi->GetYaxis()->SetTitleSize(hcorr_phi->GetYaxis()->GetTitleSize()*1.5);
  hcorr_phi->GetXaxis()->SetTitleOffset(hcorr_phi->GetXaxis()->GetTitleOffset()*0.7);
  hcorr_phi->GetYaxis()->SetTitleOffset(hcorr_phi->GetYaxis()->GetTitleOffset()*0.7);
  hcorr_phi->SetLineWidth(1);

  hcorr_phi->SetDirectory(0);
  f->Close();
  return hcorr_phi;
}

TH1D* Get1DCFdPhiv2(TString filename, int iptbin, int jptbin, double detamin, double detamax)
{
  TFile* f = new TFile(filename.Data());
  
  TH2D* hsignal = (TH2D*)f->Get(Form("signal_trg%d_ass%d",iptbin,jptbin));
  TH2D* hbackground = (TH2D*)f->Get(Form("background_trg%d_ass%d",iptbin,jptbin));
  
  int xmin = hsignal->GetXaxis()->FindBin(detamin);
  int xmax = hsignal->GetXaxis()->FindBin(detamax);

  TH1D* hsignal_phi = (TH1D*)hsignal->ProjectionY("signal_phi",xmin,xmax,"e");
  TH1D* hbackground_phi = (TH1D*)hbackground->ProjectionY("background_phi",xmin,xmax,"e");
  TH1D* hmult = (TH1D*)f->Get(Form("multcorr_trg_%d",iptbin));

  double xbinwidth = hsignal->GetXaxis()->GetBinWidth(1);
  int ntrgs=0;
//  if(iptbin==jptbin) ntrgs = hmult->Integral(3,10000,"X");
//  else ntrgs = hmult->Integral(2,10000,"X");
  ntrgs = hmult->Integral(2,10000,"X");

  hsignal_phi->Scale(xbinwidth/ntrgs);
  hbackground_phi->Scale(1.0/hbackground_phi->Integral("width"));
  TH1D* hcorr_phi = (TH1D*)hsignal_phi->Clone("correlation_phi");
  hcorr_phi->Add(hbackground_phi,-hsignal_phi->Integral("width"));
  hcorr_phi->Divide(hbackground_phi);

//  hcorr_phi->SetAxisRange(-1.98,3.35,"Y"); //3X4
  hcorr_phi->SetAxisRange(-1.18,1.85,"Y"); //$X4
//  hcorr_phi->SetAxisRange(-2.98,5.35,"Y"); 
  hcorr_phi->SetAxisRange(0,PI,"X");
  hcorr_phi->GetXaxis()->CenterTitle();
  hcorr_phi->GetYaxis()->CenterTitle();
  hcorr_phi->SetYTitle("R(#Delta#phi)");
  hcorr_phi->GetXaxis()->SetTitleSize(hcorr_phi->GetXaxis()->GetTitleSize()*1.5);
  hcorr_phi->GetYaxis()->SetTitleSize(hcorr_phi->GetYaxis()->GetTitleSize()*1.5);
  hcorr_phi->GetXaxis()->SetTitleOffset(hcorr_phi->GetXaxis()->GetTitleOffset()*0.7);
  hcorr_phi->GetYaxis()->SetTitleOffset(hcorr_phi->GetYaxis()->GetTitleOffset()*0.7);
  hcorr_phi->SetLineWidth(1);

  hcorr_phi->SetDirectory(0);
  f->Close();
  return hcorr_phi;
}

TH1D* Get1DCFdPhiv3(TString filename, TString dir, int iptbin, int jptbin, double detamin, double detamax)
{
  TH2D* hsignal = Get2DSignal(filename,dir,iptbin,jptbin);
  TH2D* hbackground = Get2DBackground(filename,dir,iptbin,jptbin);
  hbackground->Scale(1.0/hbackground->GetBinContent(hbackground->FindBin(0,0)));

  int xmin = hsignal->GetXaxis()->FindBin(detamin);
  int xmax = hsignal->GetXaxis()->FindBin(detamax);
  
  TH1D* hsignal_phi = (TH1D*)hsignal->ProjectionY(Form("corr1D_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  hsignal_phi->Scale(1.0/(xmax-xmin+1));
  TH1D* hbackground_phi = (TH1D*)hbackground->ProjectionY(Form("background1D_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  hbackground_phi->Scale(1.0/(xmax-xmin+1));
  hsignal_phi->Divide(hbackground_phi);
  TH1D* hcorr_phi_weighted = hsignal_phi->Clone(Form("corr1D_clone_trg%d_ass%d",iptbin,jptbin));

//  hcorr_phi_weighted->SetAxisRange(-PI/2,3*PI/2,"X");
  hcorr_phi_weighted->SetAxisRange(-1.2,2*PI-1.2,"X");
  hcorr_phi_weighted->GetXaxis()->CenterTitle();
  hcorr_phi_weighted->GetYaxis()->CenterTitle();
  hcorr_phi_weighted->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi}");
  hcorr_phi_weighted->SetXTitle("#Delta#phi (radians)");
  hcorr_phi_weighted->GetXaxis()->SetTitleSize(hcorr_phi_weighted->GetXaxis()->GetTitleSize()*1.5);
  hcorr_phi_weighted->GetYaxis()->SetTitleSize(hcorr_phi_weighted->GetYaxis()->GetTitleSize()*1.5);
  hcorr_phi_weighted->GetXaxis()->SetTitleOffset(hcorr_phi_weighted->GetXaxis()->GetTitleOffset()*0.7);
  hcorr_phi_weighted->GetYaxis()->SetTitleOffset(hcorr_phi_weighted->GetYaxis()->GetTitleOffset()*1.0);
  hcorr_phi_weighted->GetXaxis()->SetLabelSize(hcorr_phi_weighted->GetXaxis()->GetLabelSize()*1.3);
  hcorr_phi_weighted->GetYaxis()->SetLabelSize(hcorr_phi_weighted->GetYaxis()->GetLabelSize()*1.3);
  hcorr_phi_weighted->SetLineWidth(1);
  hcorr_phi_weighted->SetName(Form("%s_trg%d_ass%d_detamin%d_detamax%d",hcorr_phi_weighted->GetName(),iptbin,jptbin,detamin,detamax));

  return hcorr_phi_weighted;
}

TH1D* Get1DCFdPhiv4(TString filename, TString dir, int iptbin, int jptbin, double detamin, double detamax)
{
  TH2D* hsignal = Get2DSignal(filename,dir,iptbin,jptbin);
  TH2D* hbackground = Get2DBackground(filename,dir,iptbin,jptbin);

  int xmin = hsignal->GetXaxis()->FindBin(detamin);
  int xmax = hsignal->GetXaxis()->FindBin(detamax);

  TH1D* hsignal_phi = (TH1D*)hsignal->ProjectionY(Form("corr1D_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  hsignal_phi->Scale(1.0/(xmax-xmin+1));
  TH1D* hbackground_phi = (TH1D*)hbackground->ProjectionY(Form("background_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  hbackground_phi->Scale(1.0/(xmax-xmin+1));
  hbackground_phi->Scale(hbackground_phi->GetNbinsX()/hbackground_phi->Integral());
  hsignal_phi->Divide(hbackground_phi);

  hsignal_phi->SetAxisRange(0,PI,"X");
  hsignal_phi->GetXaxis()->CenterTitle();
  hsignal_phi->GetYaxis()->CenterTitle();
  hsignal_phi->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi}");
  hsignal_phi->SetXTitle("|#Delta#phi|");
  hsignal_phi->GetXaxis()->SetTitleSize(hsignal_phi->GetXaxis()->GetTitleSize()*1.5);
  hsignal_phi->GetYaxis()->SetTitleSize(hsignal_phi->GetYaxis()->GetTitleSize()*1.5);
  hsignal_phi->GetXaxis()->SetTitleOffset(hsignal_phi->GetXaxis()->GetTitleOffset()*0.7);
  hsignal_phi->GetYaxis()->SetTitleOffset(hsignal_phi->GetYaxis()->GetTitleOffset()*1.0);
  hsignal_phi->GetXaxis()->SetLabelSize(hsignal_phi->GetXaxis()->GetLabelSize()*1.3);
  hsignal_phi->GetYaxis()->SetLabelSize(hsignal_phi->GetYaxis()->GetLabelSize()*1.3);
  hsignal_phi->SetLineWidth(1);
  hsignal_phi->SetName(Form("%s_trg%d_ass%d_detamin%d_detamax%d",hsignal_phi->GetName(),iptbin,jptbin,detamin,detamax));

  return hsignal_phi;
}

TH1D* Get1DCFdPhiv5(TString filename, int iptbin, int jptbin, double detamin, double detamax)
{
  TH2D* hcorr = Get2DCFv3(filename,iptbin,jptbin);
  
  int xmin = hcorr->GetXaxis()->FindBin(detamin);
  int xmax = hcorr->GetXaxis()->FindBin(detamax);
  
  TH1D* hcorr_phi = (TH1D*)hcorr->ProjectionY(Form("corr1D_v5_trg%d_ass%d",iptbin,jptbin),xmin,xmax,"e");
  hcorr_phi->Scale(1.0/(xmax-xmin+1));
    
  hcorr_phi->SetAxisRange(0,PI,"X");
  hcorr_phi->GetXaxis()->CenterTitle();
  hcorr_phi->GetYaxis()->CenterTitle(); 
  hcorr_phi->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi}");
  hcorr_phi->SetXTitle("#Delta#phi (radians)");
  hcorr_phi->GetXaxis()->SetTitleSize(hcorr_phi->GetXaxis()->GetTitleSize()*1.5);
  hcorr_phi->GetYaxis()->SetTitleSize(hcorr_phi->GetYaxis()->GetTitleSize()*1.5);
  hcorr_phi->GetXaxis()->SetTitleOffset(hcorr_phi->GetXaxis()->GetTitleOffset()*0.7);
  hcorr_phi->GetYaxis()->SetTitleOffset(hcorr_phi->GetYaxis()->GetTitleOffset()*1.0);
  hcorr_phi->GetXaxis()->SetLabelSize(hcorr_phi->GetXaxis()->GetLabelSize()*1.3);
  hcorr_phi->GetYaxis()->SetLabelSize(hcorr_phi->GetYaxis()->GetLabelSize()*1.3);
  hcorr_phi->SetLineWidth(1);
  hcorr_phi->SetName(Form("%s_trg%d_ass%d_detamin%d_detamax%d",hcorr_phi->GetName(),iptbin,jptbin,detamin,detamax));
  
  return hcorr_phi;
} 

TH1D* Get1DCFdEtav3(TString filename, int iptbin, int jptbin, double dphimin, double dphimax)
{
  TH2D* hcorr = Get2DCFv3(filename,iptbin,jptbin);
  
  int ymin = hcorr->GetYaxis()->FindBin(dphimin);
  int ymax = hcorr->GetYaxis()->FindBin(dphimax);
  
  TH1D* hcorr_eta = (TH1D*)hcorr->ProjectionX("corr_eta",ymin,ymax,"e");
  hcorr_eta->Scale(1.0/(ymax-ymin+1));

//  hcorr_phi->SetAxisRange(0,PI,"X");
  hcorr_eta->GetXaxis()->CenterTitle();
  hcorr_eta->GetYaxis()->CenterTitle();
  hcorr_eta->SetYTitle("#frac{1}{N_{trg}}#frac{dN^{pair}}{d#Delta#phi}");
  hcorr_eta->GetXaxis()->SetTitleSize(hcorr_eta->GetXaxis()->GetTitleSize()*1.5);
  hcorr_eta->GetYaxis()->SetTitleSize(hcorr_eta->GetYaxis()->GetTitleSize()*0.8);
  hcorr_eta->GetXaxis()->SetTitleOffset(hcorr_eta->GetXaxis()->GetTitleOffset()*0.7);
  hcorr_eta->GetYaxis()->SetTitleOffset(hcorr_eta->GetYaxis()->GetTitleOffset()*1.5);
  hcorr_eta->SetLineWidth(1);

  return hcorr_eta;
}
TH2D* Get2DCF(TString filename, int iptbin, int jptbin)
{
  TFile* f = new TFile(filename.Data());
//  TH1D* hmult = (TH1D*)f->Get(Form("multcorr_trg_%d",iptbin));
  TH1D* hmult = (TH1D*)f->Get(Form("ptcorr_signal_trg_%d",iptbin));
/*
  if(iptbin==jptbin)
    hmult->SetAxisRange(2,10000,"X");//    hmult->SetAxisRange(1,10000,"X");
  else
    hmult->SetAxisRange(1,10000,"X");  
*/
  double nEvents = hmult->Integral();

  TH2D* hcorr = (TH2D*)f->Get(Form("correlation_trg%d_ass%d",iptbin,jptbin));
  hcorr->Scale(1./nEvents);

  hcorr->SetAxisRange(-4.0,4.0,"X");
  hcorr->SetAxisRange(hcorr->GetMinimum()*1.2,hcorr->GetMaximum()/20,"Z");
  hcorr->GetXaxis()->CenterTitle();
  hcorr->GetYaxis()->CenterTitle();
  hcorr->GetZaxis()->CenterTitle();
  hcorr->SetZTitle("R(#Delta#eta,#Delta#phi)");

  hcorr->SetDirectory(0);
  f->Close();
  return hcorr;
}

TH2D* Get2DCFv2(TString filename, TString dir, int iptbin, int jptbin)
{
  TH2D* hsignal = Get2DSignal(filename,dir,iptbin,jptbin);
  TH2D* hbackground = Get2DBackground(filename,dir,iptbin,jptbin);
  TH2D* hcorr = (TH2D*)hsignal->Clone("corr");
  hcorr->Divide(hbackground); 
  hcorr->SetAxisRange(-4.4,4.4,"X");
  hcorr->GetXaxis()->CenterTitle();
  hcorr->GetYaxis()->CenterTitle();
  hcorr->GetZaxis()->CenterTitle();
  hcorr->SetZTitle("S(#Delta#eta,#Delta#phi)/B(#Delta#eta,#Delta#phi)");
//  hcorr->SetAxisRange(hcorr->GetMinimum()*0.95,hcorr->GetMaximum()/1.05,"Z");
  return hcorr;
}

TH2D* Get2DCFv3(TString filename, TString dir, int iptbin, int jptbin)
{
  TH2D* hsignal = Get2DSignal(filename,dir,iptbin,jptbin);
  TH2D* hbackground = Get2DBackground(filename,dir,iptbin,jptbin);
  TH2D* hcorr = (TH2D*)hsignal->Clone(Form("corr_trg%d_ass%d",iptbin,jptbin));

/*
  double b0=0;
  for(int i=hbackground->GetYaxis()->FindBin(0);i<=hbackground->GetYaxis()->FindBin(PI);i++)
  {
    b0 = b0 + hbackground->GetBinContent(hbackground->GetXaxis()->FindBin(0),i);
  }
  b0=b0/(hbackground->GetYaxis()->FindBin(PI)-hbackground->GetYaxis()->FindBin(0)+1);
*/
//cout<<"average b0="<<b0<<endl;

//  double b0 = hbackground->Integral(hbackground->GetXaxis()->FindBin(0.0),hbackground->GetXaxis()->FindBin(0.0),1,hbackground->GetNbinsY()+1)/hbackground->GetNbinsY();
  double b0 = hbackground->GetBinContent(hbackground->FindBin(0,0));  
  if(b0==0.0) b0=1.0;
  hbackground->Scale(1.0/b0);
  
  hcorr->Divide(hbackground);
  hcorr->SetAxisRange(-4.2,4.2,"X");
  hcorr->GetXaxis()->CenterTitle();
  hcorr->GetYaxis()->CenterTitle();
  hcorr->GetZaxis()->CenterTitle();
  hcorr->SetYTitle("#Delta#phi (radians)");
  hcorr->SetZTitle("#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#eta d#Delta#phi}");
//  hcorr->GetZaxis()->SetTitleSize(hcorr->GetZaxis()->GetTitleSize()*0.67);
//  hcorr->GetZaxis()->SetTitleOffset(hcorr->GetZaxis()->GetTitleOffset()*1.3);
//  hcorr->SetAxisRange(hcorr->GetMinimum()*0.95,hcorr->GetMaximum()/1.05,"Z");
  return hcorr;
}

TH2D* GetCF(TString filename, TString histname)
{
  TFile* f = new TFile(filename.Data());
  TH1D* hmult = (TH1D*)f->Get("mult");
  hmult->SetAxisRange(2,10000,"X");
  double nEvents = hmult->Integral();
  
  TH2D* hcorr = (TH2D*)f->Get(histname.Data());
  hcorr->Scale(1./nEvents);
  
  hcorr->SetAxisRange(-4.0,4.0,"X");
  hcorr->SetAxisRange(hcorr->GetMinimum()*1.12,hcorr->GetMaximum()/35,"Z");
  hcorr->GetXaxis()->CenterTitle();
  hcorr->GetYaxis()->CenterTitle();
  hcorr->GetZaxis()->CenterTitle();
  hcorr->SetZTitle("R(#Delta#eta,#Delta#phi)");

  hcorr->SetDirectory(0);
  f->Close();
  return hcorr;
}


double GetVn(TH1D* hcorr_phi, int n, double nmult)
{
/*
  TF1* func = new TF1("func","2*[0]*TMath::Cos(2*x)",-PI/2.,3*PI/2);
  func->SetParameter(0,0.11);
  hcorr_phi->Fit("func","RNO"); 
  double V2 = TMath::Sqrt(func->GetParameter(0));
//  double V2 = func->GetParameter(0);
*/

  double V2=0;
  int xbinmin = 1;
  int xbinmax = hcorr_phi->GetNbinsX();
//  int xbinmin = hcorr_phi->FindBin(0);
//  int xbinmax = hcorr_phi->FindBin(PI/2);

  for(int i=xbinmin;i<=xbinmax;i++)
    {V2 = V2 + hcorr_phi->GetBinContent(i)*TMath::Cos(n*hcorr_phi->GetBinCenter(i))*hcorr_phi->GetBinWidth(i)/nmult; }
  V2 = V2/PI/2.;
//  V2 = sqrt(V2);

  return V2;
}

double FitVn(TH1D* hcorr_phi, int n, double nmult, double dphimin = -PI/2, double dphimax = 3*PI/2)
{
  TF1* func = new TF1("func","[0]+2*[1]*TMath::Cos(x)+2*[2]*TMath::Cos(2*x)+2*[3]*TMath::Cos(3*x)",dphimin,dphimax);
  func->SetParameters(hcorr_phi->GetBinContent(hcorr_phi->FindBin(1.5)),-(hcorr_phi->GetMaximum()-hcorr_phi->GetMinimum())/4.0,(hcorr_phi->GetMaximum()-hcorr_phi->GetMinimum())/4.0,0);
  hcorr_phi->Fit("func","RNO");
  double V2 = func->GetParameter(n)/nmult;

  return V2;
}

TF1* FitVnFunc(TH1D* hcorr_phi,double dphimin = 0, double dphimax = PI)
{
//  TF1* func = new TF1("func","[0]*(1+2*[1]*TMath::Cos(x)+2*[2]*TMath::Cos(2*x)+2*[3]*TMath::Cos(3*x)+2*[4]*TMath::Cos(4*x)+2*[5]*TMath::Cos(5*x))",dphimin,dphimax);
  TF1* func = new TF1("func","[0]*(1+2*[1]*TMath::Cos(x)+2*[2]*TMath::Cos(2*x)+2*[3]*TMath::Cos(3*x)+2*[4]*TMath::Cos(4*x)+2*[5]*TMath::Cos(5*x)+2*[6]*TMath::Cos(6*x)+2*[7]*TMath::Cos(7*x)+2*[8]*TMath::Cos(8*x)+2*[9]*TMath::Cos(9*x)+2*[10]*TMath::Cos(10*x))",-PI/2,3*PI/2);
  func->SetParameters(hcorr_phi->GetBinContent(hcorr_phi->FindBin(1.5)),-(hcorr_phi->GetMaximum()-hcorr_phi->GetMinimum())/4.0,(hcorr_phi->GetMaximum()-hcorr_phi->GetMinimum())/4.0,0,0,0,0,0,0,0,0);
//  func->FixParameter(2,0);
//  func->FixParameter(3,0);
//  func->FixParameter(4,0);
  func->FixParameter(5,0);
  func->FixParameter(6,0);
  func->FixParameter(7,0);
  func->FixParameter(8,0);
  func->FixParameter(9,0);
  func->FixParameter(10,0);
  hcorr_phi->Fit("func","NO","",dphimin,dphimax);

  return func;
}

TH1D* GetV2dEta(TString filename)
{
  TFile* f = new TFile(filename.Data());
  TH2D* hsignal = (TH2D*)f->Get("signal_trg0_ass0");
  TH2D* hbackground = (TH2D*)f->Get("background_trg0_ass0");
  TH1D* hV2 = (TH1D*)hsignal->ProjectionX("V2",-1,-1,"e");
  hV2->Reset();

  for(int i=1;i<=hsignal->GetNbinsX();i++)
  {
    TH1D* hsignal_phi = (TH1D*)hsignal->ProjectionY("signal_phi_trg0_ass0",i,i,"e");
    TH1D* hbackground_phi = (TH1D*)hbackground->ProjectionY("background_phi_trg0_ass0",i,i,"e");

    hsignal_phi->Scale(1.0/hsignal_phi->Integral());
    hbackground_phi->Scale(1.0/hbackground_phi->Integral());

    TH1D* hcorrelation_phi = (TH1D*) hsignal_phi->Clone("correlation_phi_trg0_ass0");
    hcorrelation_phi->Divide(hbackground_phi);

    TH1D* hmult = (TH1D*)f->Get("mult");

    TF1* func = new TF1("func","[0]*(1.+2.*[1]*TMath::Cos(2*x))",-PI/2.,3.*PI/2.);
    func->SetParameters(1.0,0.05);
    hcorrelation_phi->Fit("func","RNO");

    double V2=func->GetParameter(1);
    double V2error=func->GetParError(1);
/*
    for(int j=1;j<=hcorrelation_phi->GetNbinsX();j++)
    { 
      V2 = V2 + hcorrelation_phi->GetBinContent(j)*TMath::Cos(2*hcorrelation_phi->GetBinCenter(j));
      V2error = V2error + (hcorrelation_phi->GetBinError(j)*TMath::Cos(2*hcorrelation_phi->GetBinCenter(j)))*(hcorrelation_phi->GetBinError(j)*TMath::Cos(2*hcorrelation_phi->GetBinCenter(j))); 
    }
//cout<<V2<<" "<<hcorrelation_phi->Integral()<<" "<<hmult->GetMean()<<endl;
    V2 = V2/hcorrelation_phi->GetNbinsX();
    V2 = TMath::Sqrt(V2);    
//    V2error = TMath::Sqrt(TMath::Sqrt(V2error/hcorrelation_phi->GetNbinsX()));
    V2error = TMath::Sqrt(V2error/hcorrelation_phi->GetNbinsX());
*/
//cout<<func->GetParameter(1)<<" "<<V2<<endl;

//    hV2->SetBinContent(i,TMath::Abs(V2)*sqrt(hmult->GetMean()));
    hV2->SetBinContent(i,TMath::Abs(V2));
    hV2->SetBinError(i,V2error);
  }

  hV2->SetDirectory(0);
  f->Close();
  return hV2;
}

TH2D* SimpleZYAM2D(TH2D* h)
{
  double min = h->GetMinimum();
  TH2D* hzyam = (TH2D*)h->Clone("corr_zyam");
  for(int i=1;i<=hzyam->GetNbinsX();i++)
    for(int j=1;j<=hzyam->GetNbinsY();j++)
      hzyam->SetBinContent(i,j,h->GetBinContent(i,j)-min);

  return hzyam;
}

TH1D* SimpleZYAM1D(TH1D* h, double level=1.4)
{
//  double min = h->GetMinimum();
  double min = h->GetBinContent(h->FindBin(level));

  TH1D* hzyam = (TH1D*)h->Clone("corr_zyam");
  for(int i=1;i<=hzyam->GetNbinsX();i++)
      hzyam->SetBinContent(i,h->GetBinContent(i)-min);

  return hzyam;
}

void SimpleShift1D(TH1D* h, double c)
{
  for(int i=1;i<=h->GetNbinsX();i++)
      h->SetBinContent(i,h->GetBinContent(i)+c);
}

TH1D* DoZYAM(TH1D* h, TF1* func)
{
  TH1D* h_clone = (TH1D*)h->Clone("h_clone");
/*
  for(int i=1;i<=h_clone->GetNbinsX();i++)
  {
    h_clone->SetBinContent(i,h->GetBinContent(i)/func->Eval(h->GetBinCenter(i)));
    h_clone->SetBinError(i,h->GetBinError(i)/func->Eval(h->GetBinCenter(i)));
  }
*/
/*
  double histminY = h_clone->GetMinimum();
  double histminX = h_clone->GetBinCenter(h_clone->GetMinimumBin());
*/
  double histminY = h_clone->GetBinContent(h_clone->FindBin(1.0));
  double histminX = 1;

  TF1* fitpara2 = new TF1("fitpara2","[0]+[1]*(x-[2])*(x-[2])",histminX-0.6,histminX+0.6);
  fitpara2->SetParameters(histminY,0.01,histminX,0.001);
  fitpara2->SetParLimits(1,0,1);
  fitpara2->SetParLimits(2,histminX-0.6,histminX+0.6);
//  fitpara2->FixParameter(1,0);
  fitpara2->FixParameter(2,1);
  h_clone->Fit("fitpara2","RNO");

  TH1D* h1_clone = (TH1D*)h->Clone("h1_clone");
  func->SetParameter(0,fitpara2->GetParameter(0));
  for(int i=1;i<=h1_clone->GetNbinsX();i++)
  {
    h1_clone->SetBinContent(i,h->GetBinContent(i)-func->Eval(h->GetBinCenter(i)));
  }

  return h1_clone;
}

double DoZYAMLevel(TH1D* h, TF1* func)
{
  TH1D* h_clone = (TH1D*)h->Clone("h_clone");

  for(int i=1;i<=h_clone->GetNbinsX();i++)
  {
    h_clone->SetBinContent(i,h->GetBinContent(i)/func->Eval(h->GetBinCenter(i)));
    h_clone->SetBinError(i,h->GetBinError(i)/func->Eval(h->GetBinCenter(i)));
  }

  double histminY = h_clone->GetMinimum();
  double histminX = h_clone->GetBinCenter(h_clone->GetMinimumBin());

  TF1* fitpara2 = new TF1("fitpara2","[0]+[1]*(x-[2])*(x-[2])+[3]*(x-[2])*(x-[2])",histminX-1,histminX+1);
  fitpara2->SetParameters(histminY,0.01,histminX,0.001);
  fitpara2->SetParLimits(1,0,1000);
  fitpara2->SetParLimits(2,0,1000);
  fitpara2->SetParLimits(3,0,1000);
  h_clone->Fit("fitpara2","R");

  TH1D* h1_clone = (TH1D*)h->Clone("h1_clone");
  func->SetParameter(0,fitpara2->GetParameter(0));
  for(int i=1;i<=h1_clone->GetNbinsX();i++)
  {
    h1_clone->SetBinContent(i,h->GetBinContent(i)-func->Eval(h->GetBinCenter(i)));
  }

cout<<fitpara2->GetParameter(0)<<endl;
  return fitpara2->GetParameter(0);
}

template <class T>
T* compare_flow_pp_phi_multipad_pt(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_ReTracking_INCLEFF1TRG1v5NEW", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, double detamin=2.0, double detamax=4.8, const int ntrgptbins, const int nassptbins, double etatrgmin=-2.4, double etatrgmax=2.4, double etaassmin=-2.4, double etaassmax=2.4)
{

  TH1D*** h;
  h=new TH1D**[nassptbins];
  for(int i=0;i<ntrgptbins;i++) {
     h[i]=new TH1D*[nassptbins];
  }

  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,etatrgmin,etatrgmax,etaassmin,etaassmax,centmin,centmax);

  for(int itrg = 0; itrg<ntrgptbins; itrg++)
  {
    for(int jass = 0; jass<nassptbins; jass++)
    {
      h[itrg][jass] = (TH1D*)Get1DCFdPhiv3(filename.Data(),itrg,jass,detamin,detamax);
      if(!h[itrg][jass]) continue;
      h[itrg][jass]->SetMarkerColor(kRed);
    }
  }

  return h;
}
