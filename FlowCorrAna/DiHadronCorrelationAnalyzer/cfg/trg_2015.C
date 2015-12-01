void trg_2015()
{
  TFile* f = new TFile("dihadroncorrelation_pt005.root");

//  TFile* f = new TFile("dihadroncorrelation_eta08_nhit12.root");
//  TFile* f = new TFile("dihadroncorrelation_nhit12.root");
//  TFile* f = new TFile("dihadroncorrelation_eta08.root");

  TH1D* h_mb = (TH1D*)f->Get("corr_ana_HI/pt_signal_trg_0");
  TH1D* h_trk12 = (TH1D*)f->Get("corr_ana_HI_trk12/pt_signal_trg_0");
  TH1D* h_trk18 = (TH1D*)f->Get("corr_ana_HI_trk18/pt_signal_trg_0");
  TH1D* h_trk24 = (TH1D*)f->Get("corr_ana_HI_trk24/pt_signal_trg_0");
  TH1D* h_trk34 = (TH1D*)f->Get("corr_ana_HI_trk34/pt_signal_trg_0");
  TH1D* h_trk45 = (TH1D*)f->Get("corr_ana_HI_trk45/pt_signal_trg_0");

  TH1D* h_l1trk12 = (TH1D*)f->Get("corr_ana_HI_l1trk12/pt_signal_trg_0");
  TH1D* h_l1trk16 = (TH1D*)f->Get("corr_ana_HI_l1trk16/pt_signal_trg_0");
  TH1D* h_l1trk20 = (TH1D*)f->Get("corr_ana_HI_l1trk20/pt_signal_trg_0");
  TH1D* h_l1trk24 = (TH1D*)f->Get("corr_ana_HI_l1trk24/pt_signal_trg_0");
  TH1D* h_l1trk28 = (TH1D*)f->Get("corr_ana_HI_l1trk28/pt_signal_trg_0");

  h_mb->Rebin(40);
  h_trk12->Rebin(40);
  h_trk18->Rebin(40);
  h_trk24->Rebin(40);
  h_trk34->Rebin(40);
  h_trk45->Rebin(40);
  h_l1trk12->Rebin(40);
  h_l1trk16->Rebin(40);
  h_l1trk20->Rebin(40);
  h_l1trk24->Rebin(40);
  h_l1trk28->Rebin(40);

  h_mb->SetMarkerStyle(20);
  h_trk12->SetMarkerStyle(20);
  h_trk18->SetMarkerStyle(20);
  h_trk24->SetMarkerStyle(20);
  h_trk34->SetMarkerStyle(20);
  h_trk45->SetMarkerStyle(20);
  h_l1trk12->SetMarkerStyle(20);
  h_l1trk16->SetMarkerStyle(20);
  h_l1trk20->SetMarkerStyle(20);
  h_l1trk24->SetMarkerStyle(20);
  h_l1trk28->SetMarkerStyle(20);

  h_mb->SetMarkerColor(1);
  h_trk12->SetMarkerColor(2);
  h_trk18->SetMarkerColor(3);
  h_trk24->SetMarkerColor(4);
  h_trk34->SetMarkerColor(6);
  h_trk45->SetMarkerColor(7);
  h_l1trk12->SetMarkerColor(2);
  h_l1trk16->SetMarkerColor(3);
  h_l1trk20->SetMarkerColor(4);
  h_l1trk24->SetMarkerColor(6);
  h_l1trk28->SetMarkerColor(7);

  TH1D* h_trk12_ratio = (TH1D*)h_trk12->Clone("h_trk12_ratio");
  TH1D* h_trk18_ratio = (TH1D*)h_trk18->Clone("h_trk18_ratio");
  TH1D* h_trk24_ratio = (TH1D*)h_trk24->Clone("h_trk24_ratio");
  TH1D* h_trk34_ratio = (TH1D*)h_trk34->Clone("h_trk34_ratio");
  TH1D* h_trk45_ratio = (TH1D*)h_trk45->Clone("h_trk45_ratio");
  h_trk12_ratio->Divide(h_mb);
  h_trk18_ratio->Divide(h_mb);
  h_trk24_ratio->Divide(h_mb);
  h_trk34_ratio->Divide(h_mb);
  h_trk45_ratio->Divide(h_mb);

  TH1D* h_l1trk12_ratio = (TH1D*)h_l1trk12->Clone("h_l1trk12_ratio");
  TH1D* h_l1trk16_ratio = (TH1D*)h_l1trk16->Clone("h_l1trk16_ratio");
  TH1D* h_l1trk20_ratio = (TH1D*)h_l1trk20->Clone("h_l1trk20_ratio");
  TH1D* h_l1trk24_ratio = (TH1D*)h_l1trk24->Clone("h_l1trk24_ratio");
  TH1D* h_l1trk28_ratio = (TH1D*)h_l1trk28->Clone("h_l1trk28_ratio");
  h_l1trk12_ratio->Divide(h_mb);
  h_l1trk16_ratio->Divide(h_mb);
  h_l1trk20_ratio->Divide(h_mb);
  h_l1trk24_ratio->Divide(h_mb);
  h_l1trk28_ratio->Divide(h_mb);

  TCanvas* c = new TCanvas("c","c",550,500);
  c->SetLogy();
  h_mb->Draw("PE");
  h_trk12->Draw("PESAME");
  h_trk18->Draw("PESAME");
  h_trk24->Draw("PESAME");
  h_trk34->Draw("PESAME");
  h_trk45->Draw("PESAME");

  TCanvas* c1 = new TCanvas("c1","c1",550,500);
//  c1->SetLogy();
  h_trk12_ratio->SetAxisRange(0,100,"X"); 
  h_trk12_ratio->Draw("PE");
  h_trk18_ratio->Draw("PESAME");
  h_trk24_ratio->Draw("PESAME");
  h_trk34_ratio->Draw("PESAME");
  h_trk45_ratio->Draw("PESAME");

  TCanvas* c2 = new TCanvas("c2","c2",550,500);
  h_l1trk12_ratio->SetAxisRange(0,100,"X");
  h_l1trk12_ratio->Draw("PE");
  h_l1trk16_ratio->Draw("PESAME");
  h_l1trk20_ratio->Draw("PESAME");
  h_l1trk24_ratio->Draw("PESAME");
  h_l1trk28_ratio->Draw("PESAME");
}
