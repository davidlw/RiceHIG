void check()
{
  TFile* f = new TFile("dihadroncorrelation_HM60.root");
  TFile* f1 = new TFile("dihadroncorrelation_HM85.root");
  TFile* f2 = new TFile("dihadroncorrelation_HM110.root");

  TH1D* h = (TH1D*)f->Get("corr_ana/multrawall");
  TH1D* h1 = (TH1D*)f1->Get("corr_ana/multrawall");
  TH1D* h2 = (TH1D*)f2->Get("corr_ana/multrawall");

  h->Scale(1.0/h->Integral());
  h1->Scale(1.0/h1->Integral());
  h2->Scale(1.0/h2->Integral());

  h->SetMarkerColor(2);
  h1->SetMarkerColor(4);
  h2->SetMarkerColor(3);

  h->Divide(h1);

  TCanvas* c = new TCanvas("c","",500,500);
  h->SetAxisRange(0,250,"X");
  h->Draw("PE");
  h1->Draw("PESAME");
  h2->Draw("PESAME");
}
