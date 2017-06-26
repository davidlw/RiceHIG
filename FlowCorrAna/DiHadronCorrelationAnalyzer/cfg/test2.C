void test2()
{
  TFile* f = new TFile("dihadroncorrelation_pp.root");
  TFile* f1 = new TFile("dihadroncorrelation_hi.root");

  TH1D* hpt_pp = (TH1D*)f->Get("corr_ana_pp/pt_signal_trg_0");
  TH1D* hpt_hi = (TH1D*)f1->Get("corr_ana_HI/pt_signal_trg_0");

  hpt_pp->SetMarkerStyle(20);
  hpt_pp->SetMarkerColor(2);

  TCanvas* c = new TCanvas("c","c",550,500);
  hpt_pp->Draw("PE");
  hpt_hi->Draw("histESAME");
}
