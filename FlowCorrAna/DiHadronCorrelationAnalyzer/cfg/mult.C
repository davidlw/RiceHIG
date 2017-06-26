void mult()
{
  TFile* f = new TFile("~/scratch2/DiHadronCorrelations/outputs_312/EPOS_Minbias_5TeV/merged/multana_epos_gen_v1.root");
  TFile* f1 = new TFile("~/scratch2/DiHadronCorrelations/outputs_312/Hydjet_Minbias_5TeV/merged/multana_hydjet_gen_v1.root");

  TH1D* h = (TH1D*)f->Get("corr_ana/multrawall");
  TH1D* h1 = (TH1D*)f1->Get("corr_ana/multrawall");

  h->Rebin(10);
  h1->Rebin(10);

  h->Scale(1.0/h->Integral());
  h1->Scale(1.0/h1->Integral());

  h->SetLineColor(2);
  h1->SetLineColor(4);

  TCanvas* c = new TCanvas("c","",500,500);
  c->SetLogy();
  h->Draw("L");
  h1->Draw("Lsame");
}
