void test()
{
  TFile* f = new TFile("dihadroncorrelation.root");
  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_7TeV/merged/PPData_Minbias_7TeV_MINBIAS_All_Apr21ReReco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");

  TH1D* h = (TH1D*)f->Get("corr_ana/multrawall");
  TH1D* h1 = (TH1D*)f1->Get("multrawall");

  h->Scale(1./h->Integral());
  h1->Scale(1./h1->Integral());
 
  h->SetMarkerStyle(20);
  h->SetMarkerColor(2);
  h1->SetMarkerColor(1);

  TCanvas* c = new TCanvas("c","",600,550);
  c->SetLogy();
  h1->SetAxisRange(0,200,"X");
  h1->Draw("PE");
  h->Draw("PESAME");
}
