#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TF2.h"
#include "TCanvas.h"

double PCA(double *x, double *par){
  
  int ietabin = (int)((x[0]+2.4)/0.6);
  int jetabin = (int)((x[1]+2.4)/0.6);

  if(fabs(ietabin-jetabin)<2) return 0;

  int parity_x = 1;
  int parity_y = 1;
  if(ietabin>=4 && ietabin<8) { ietabin = 7 - ietabin; parity_x = -1;}
  if(jetabin>=4 && jetabin<8) { jetabin = 7 - jetabin; parity_y = -1;}

  double result = par[ietabin] * par[jetabin] + parity_x * parity_y * par[ietabin+4] * par[jetabin+4] + par[ietabin+8] * par[jetabin+8];
  return result;
}


double PCA_full(double *x, double *par){

  int ietabin = (int)((x[0]+2.4)/0.6);
  int jetabin = (int)((x[1]+2.4)/0.6);

  int parity_x = 1;
  int parity_y = 1;
  if(ietabin>=4 && ietabin<8) { ietabin = 7 - ietabin; parity_x = -1;}
  if(jetabin>=4 && jetabin<8) { jetabin = 7 - jetabin; parity_y = -1;}

  double result = par[ietabin] * par[jetabin] + parity_x * parity_y * par[ietabin+4] * par[jetabin+4] + par[ietabin+8] * par[jetabin+8];
  return result;
}

void matrix()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/epetadecomatrix_ucc_pttrg033_ptass033_eff1_etabin02_golden_v5.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_7_5_5_patch3/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/epetadecomatrix.root");

//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadecomatrix_cent5060_pttrg033_ptass033_eff1_v2.root");

  const int ntrgbins = 24;
  TH2D* hsignal[ntrgbins][ntrgbins];
  TH2D* hbackground[ntrgbins][ntrgbins];

  TH2D* hMatrix = new TH2D("matrix",";#eta_{1};#eta_{2}",24,-2.4,2.4,24,-2.4,2.4);
  TH2D* hMatrix_fit = (TH2D*)hMatrix->Clone("matrix_fit");
  TH1D* hp1 = (TH1D*)hMatrix->ProjectionX("hp1",-1,-1,"e");
  TH1D* hp2 = (TH1D*)hMatrix->ProjectionX("hp2",-1,-1,"e");
  TH1D* hp3 = (TH1D*)hMatrix->ProjectionX("hp3",-1,-1,"e");
  
  for(int i=0;i<ntrgbins;i++)
  {
    for(int j=i;j<ntrgbins;j++)
    {
//      hsignal[i][j] = (TH2D*)f->Get(Form("epetadecomatrix_ana_HI_gen/signalcosn_trg%d_ass%d",i,j));      
      hsignal[i][j] = (TH2D*)f->Get(Form("epetadecomatrix_ana_HI/signalcosn_trg%d_ass%d",i,j));      
      hbackground[i][j] = (TH2D*)f->Get(Form("epetadecomatrix_ana_HI/backgroundcosn_trg%d_ass%d",i,j));

      TH1D* hsignal_1D = (TH1D*)hsignal[i][j]->ProjectionX("signal_1D",2,2,"i");
      TH1D* hbackground_1D = (TH1D*)hbackground[i][j]->ProjectionX("background_1D",2,2,"i");

      hMatrix->SetBinContent(i+1,j+1,hsignal_1D->GetMean()-hbackground_1D->GetMean());
      hMatrix->SetBinError(i+1,j+1,sqrt(hsignal_1D->GetMeanError()*hsignal_1D->GetMeanError()+hbackground_1D->GetMeanError()*hbackground_1D->GetMeanError()));
      hMatrix->SetBinContent(j+1,i+1,hsignal_1D->GetMean()-hbackground_1D->GetMean());
      hMatrix->SetBinError(j+1,i+1,sqrt(hsignal_1D->GetMeanError()*hsignal_1D->GetMeanError()+hbackground_1D->GetMeanError()*hbackground_1D->GetMeanError()));

      if(fabs(i-j)<2)
      {
        hMatrix->SetBinContent(i+1,j+1,0);
        hMatrix->SetBinError(i+1,j+1,hsignal_1D->GetMeanError());
        hMatrix->SetBinContent(j+1,i+1,0);
        hMatrix->SetBinError(j+1,i+1,hsignal_1D->GetMeanError());
      }

    }
  }

  TCanvas* c = new TCanvas("c","",500,500);
  hMatrix->Draw("lego2");

  double params[12] = {0.1,0.1,0.1,0.1,0.03,0.03,0.03,0.03,0.01,0.01,0.01,0.01};
  TF2* fitfunc = new TF2("fitfunc",PCA,-2.4,2.4,-2.4,2.4,12);
  fitfunc->SetParameters(params);

  fitfunc->FixParameter(8,0);
  fitfunc->FixParameter(9,0);
  fitfunc->FixParameter(10,0);
  fitfunc->FixParameter(11,0);

  hMatrix->Fit(fitfunc,"RNO");
  hMatrix->Fit(fitfunc,"RNO");
  hMatrix->Fit(fitfunc,"RNO");

  TF2* fitfunc_full = new TF2("fitfunc_full",PCA_full,-2.4,2.4,-2.4,2.4,12);
  fitfunc_full->SetParameters(fitfunc->GetParameters());
  fitfunc_full->SetMinimum(0);
//  TH2D* hMatrix_tmp = (TH2D*)fitfunc_full->CreateHistogram();
  hMatrix_fit->Add(fitfunc_full);

  TH2D* hMatrix_diff = (TH2D*)hMatrix->Clone("matrix_diff");
  hMatrix_diff->Add(hMatrix_fit,-1);

  for(int i=0;i<4;i++)
  {
    hp1->SetBinContent(i+1,fitfunc->GetParameter(i));
    hp1->SetBinError(i+1,fitfunc->GetParError(i));
    hp1->SetBinContent(8-i,fitfunc->GetParameter(i));
    hp1->SetBinError(8-i,fitfunc->GetParError(i));

    hp2->SetBinContent(i+1,fitfunc->GetParameter(i+4));
    hp2->SetBinError(i+1,fitfunc->GetParError(i+4));
    hp2->SetBinContent(8-i,-fitfunc->GetParameter(i+4));
    hp2->SetBinError(8-i,fitfunc->GetParError(i+4));

    hp3->SetBinContent(i+1,fitfunc->GetParameter(i+8));
    hp3->SetBinError(i+1,fitfunc->GetParError(i+8));
    hp3->SetBinContent(8-i,fitfunc->GetParameter(i+8));
    hp3->SetBinError(8-i,fitfunc->GetParError(i+8));
  }

  TCanvas* c1 = new TCanvas("c1","",500,500);
  hMatrix_fit->Draw("lego2");

  TCanvas* c2 = new TCanvas("c2","",500,500);
  hMatrix_diff->Draw("lego2");

  TCanvas* c3 = new TCanvas("c3","",500,500);
  hp1->SetMarkerColor(1);
  hp2->SetMarkerColor(2);
  hp3->SetMarkerColor(4);
  hp1->SetMarkerStyle(20);
  hp2->SetMarkerStyle(20);
  hp3->SetMarkerStyle(20);
  hp1->SetMaximum(0.15);
  hp1->SetMinimum(-0.05);
  hp1->Draw("PE");
  hp2->Draw("PESAME");
  hp3->Draw("PESAME");
}
