void matrix()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/Hydjet_Minbias_5TeV/merged/multana_hydjet_v2.root");

  TH2D* h = (TH2D*)f->Get("mult_ana/multrawvsgen");

  TCanvas* c = new TCanvas("c","",500,500);
  h->Draw("colz");
}
