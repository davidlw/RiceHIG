#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void pPbFB()
{
  double ptmin=5;
  double ptmax=4;

  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_mb_forward_pPb_Golden_dz01.root");
  TH1D* h_ff = (TH1D*)Get1DCFdPhiv3(filename.Data(),"corr_ana_pPb_FF",ptmin,ptmax,-100,100);
  TH1D* h_fc = (TH1D*)Get1DCFdPhiv3(filename.Data(),"corr_ana_pPb_FC",ptmin,ptmax,-100,100);
  TH1D* h_fb = (TH1D*)Get1DCFdPhiv3(filename.Data(),"corr_ana_pPb_FB",ptmin,ptmax,-100,100);

  TCanvas* c = new TCanvas("c","c",900,300);
  c->Divide(3,1);
  c->cd(1);
  h_ff->Draw("PESAME");
  c->cd(2);
  h_fc->Draw("PESAME");
  c->cd(3);
  h_fb->Draw("PESAME");
}
