void compareHF()
{
  TFile* fda = new TFile("HF_2013.root");
  TFile* f1da = new TFile("HF_2016.root");
  TFile* f = new TFile("HF_MC_2013.root");
  TFile* f1 = new TFile("HF_MC_2016.root");

  TH1D* hda = (TH1D*)fda->Get("corr_ana_pPb/ptall_trg");
  TH1D* h1da = (TH1D*)f1da->Get("corr_ana/ptall_trg");
  TH1D* h = (TH1D*)f->Get("corr_ana_pPb/ptall_trg");
  TH1D* h1 = (TH1D*)f1->Get("corr_ana/ptall_trg");
  TH1D* hNTda = (TH1D*)fda->Get("corr_ana_pPb/mult_trg_0");
  TH1D* h1NTda = (TH1D*)f1da->Get("corr_ana/mult_trg_0");
  TH1D* hNT = (TH1D*)f->Get("corr_ana_pPb/mult_trg_0");
  TH1D* h1NT = (TH1D*)f1->Get("corr_ana/mult_trg_0");

  hda->Scale(1.0/hda->Integral());
  h1da->Scale(1.0/h1da->Integral());
  hNTda->Scale(1.0/hNTda->Integral());
  h1NTda->Scale(1.0/h1NTda->Integral());
  h->Scale(1.0/h->Integral());
  h1->Scale(1.0/h1->Integral());
  hNT->Scale(1.0/hNT->Integral());
  h1NT->Scale(1.0/h1NT->Integral());

  hda->SetMarkerStyle(20);
  h1da->SetMarkerStyle(20);
  hda->SetMarkerColor(1);
  h1da->SetMarkerColor(2);
  h->SetMarkerStyle(25);
  h1->SetMarkerStyle(25);
  h->SetMarkerColor(1);
  h1->SetMarkerColor(2);

  hNTda->SetMarkerStyle(20);
  h1NTda->SetMarkerStyle(20);
  hNTda->SetMarkerColor(1);
  h1NTda->SetMarkerColor(2);
  hNT->SetMarkerStyle(25);
  h1NT->SetMarkerStyle(25);
  hNT->SetMarkerColor(1);
  h1NT->SetMarkerColor(2);

  TCanvas* c = new TCanvas("c","c",500,500);
  c->SetLogy();
  h->Draw("PE");
  h1->Draw("PESAME");
  TH1D* h_ratio = (TH1D*)h1->Clone("ratio");
  h_ratio->Divide(h);
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  h_ratio->Draw();

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  hNT->Draw("PE");
  h1NT->Draw("PESAME");
  TH1D* hNT_ratio = (TH1D*)h1NT->Clone("ratioNT");
  hNT_ratio->Divide(hNT);
  TCanvas* c3 = new TCanvas("c3","c3",500,500);
  hNT_ratio->Draw();

  TCanvas* cda = new TCanvas("cda","cda",500,500);
  cda->SetLogy();
  hda->Draw("PE");
  h1da->Draw("PESAME");
  TH1D* hda_ratio = (TH1D*)h1da->Clone("ratioda");
  hda_ratio->Divide(hda);
  TCanvas* c1da = new TCanvas("c1da","c1da",500,500);
  hda_ratio->Draw();
  h_ratio->Draw("PESAME");

  TCanvas* c2da = new TCanvas("c2da","c2da",500,500);
  hNTda->Draw("PE");
  h1NTda->Draw("PESAME");
  TH1D* hNTda_ratio = (TH1D*)h1NTda->Clone("ratioNTda");
  hNTda_ratio->Divide(hNTda);
  TCanvas* c3da = new TCanvas("c3da","c3da",500,500);
  hNTda_ratio->Draw();
  hNT_ratio->Draw("PESAME");
}
