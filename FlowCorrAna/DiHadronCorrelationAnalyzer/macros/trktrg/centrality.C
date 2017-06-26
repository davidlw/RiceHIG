void centrality()
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/test_centrality_express262834_v2.root");
  TH1D* h1 = (TH1D*)f->Get("corr_ana_HI_1/centrality");
  TH1D* h1nosel = (TH1D*)f->Get("corr_ana_HI_nosel1/centrality");
  TH1D* h2 = (TH1D*)f->Get("corr_ana_HI_2/centrality");
  TH1D* h2nosel = (TH1D*)f->Get("corr_ana_HI_nosel2/centrality");
  TH1D* h3 = (TH1D*)f->Get("corr_ana_HI_3/centrality");
  TH1D* h3nosel = (TH1D*)f->Get("corr_ana_HI_nosel3/centrality");

  h1->Rebin(3);
  h2->Rebin(3);
  h3->Rebin(3);
  h1nosel->Rebin(3);
  h2nosel->Rebin(3);
  h3nosel->Rebin(3);


  TGraphAsymmErrors * gr1 = new TGraphAsymmErrors();
  gr1->Divide(h1, h1nosel, "cp" );

  TGraphAsymmErrors * gr2 = new TGraphAsymmErrors();
  gr2->Divide(h2, h2nosel, "cp" );

  TGraphAsymmErrors * gr3 = new TGraphAsymmErrors();
  gr3->Divide(h3, h3nosel, "cp" );

  
/*
  h1->Divide(h1nosel);
  h2->Divide(h2nosel);
  h3->Divide(h3nosel);
*/
  gr1->SetMarkerColor(2);
  gr2->SetMarkerColor(4);
  gr3->SetMarkerColor(3);
  gr1->SetMarkerStyle(20);
  gr2->SetMarkerStyle(20);
  gr3->SetMarkerStyle(20);

  TH1D* htmp = new TH1D("htmp","Event selection efficiency, run 262834; Centrality bin",200,0,200);
  TCanvas* c = new TCanvas("c","c",500,500);
  htmp->Draw("");
  gr1->Draw("PESAME");
  gr2->Draw("PESAME");
  gr3->Draw("PESAME");

  TLegend* legend = new TLegend(0.15,0.25,0.8,0.5);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->AddEntry(gr1,"HLT_HIL1MinimumBiasHF1ANDExpress_v1","P");
  legend->AddEntry(gr2,"HLT_HIL1MinimumBiasHF2ANDExpress_v1","P");
  legend->AddEntry(gr3,"HLT_HIL1HFplusANDminusTH0Express_v1","P");
  legend->Draw();
}
