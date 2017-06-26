void centrality2()
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/test_centrality_express263233_v2.root");
  TH1D* h1 = (TH1D*)f->Get("corr_ana_HI_1/centrality");
  TH1D* h1nosel = (TH1D*)f->Get("corr_ana_HI_nosel1/centrality");

  TFile* f2 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/test_centrality_express263233_v2.root");
  TH1D* h2 = (TH1D*)f2->Get("corr_ana_HI_1/centrality");
  TH1D* h2nosel = (TH1D*)f2->Get("corr_ana_HI_nosel1/centrality");

  TFile* f3 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/test_centrality_express262811_v2.root");
  TH1D* h3 = (TH1D*)f3->Get("corr_ana_HI_1/centrality");
  TH1D* h3nosel = (TH1D*)f3->Get("corr_ana_HI_nosel1/centrality");

  h1->Rebin(10);
  h2->Rebin(10);
  h3->Rebin(10);
  h1nosel->Rebin(10);
  h2nosel->Rebin(10);
  h3nosel->Rebin(10);

  h1->Scale(1.0/h1->Integral());
  h2->Scale(1.0/h2->Integral());
  h3->Scale(1.0/h3->Integral());

  h1->Divide(h3);
  h2->Divide(h3);
  
  h1->SetMarkerColor(2);
  h2->SetMarkerColor(4);
  h1->SetMarkerStyle(20);
  h2->SetMarkerStyle(20);

  TH2D* htmp = new TH2D("htmp","Run 263233 / Run 262811; Centrality bin",200,0,200,100,0,1.5);
  TCanvas* c = new TCanvas("c","c",500,500);
  htmp->Draw("");
  h1->Draw("PESAME");
//  h2->Draw("PESAME");

  TLegend* legend = new TLegend(0.15,0.25,0.6,0.4);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->AddEntry(h1,"run 262620","P");
  legend->AddEntry(h2,"run 262656","P");
//  legend->Draw();
}
