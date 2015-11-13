void highPurity()
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/mult_pythia8_purej_dz01_debug.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_mb_noevtsel_debug.root");

  TH1D* hfrac = (TH1D*)f->Get("corr_ana/hHighPurityFrac");
  TH1D* hfrac1 = (TH1D*)f1->Get("corr_ana/hHighPurityFrac");

  hfrac->Rebin(2);
  hfrac1->Rebin(2);

  hfrac->Scale(1.0/hfrac->Integral("width"));
  hfrac1->Scale(1.0/hfrac1->Integral("width"));
  
  hfrac->SetMarkerStyle(20);
  hfrac1->SetMarkerStyle(24);

  TCanvas* c = new TCanvas("c","c",500,500);
  c->SetLogy();
  c->SetRightMargin(0.02);
  hfrac->Draw("PE");
  hfrac1->Draw("PESAME");
  TLegend* legend = new TLegend(0.22,0.73,0.64,0.85);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
  legend->AddEntry(hfrac,"CMS Data","P");
  legend->AddEntry(hfrac1,"PYTHIA8 TuneCUETP8M1","P");
  legend->Draw();

  c->Print("~/pic/flow_pp/pp13TeV/highPurity_frac_noevtsel.gif");
  c->Print("~/pic/flow_pp/pp13TeV/highPurity_frac_noevtsel.C");
  c->Print("~/pic/flow_pp/pp13TeV/highPurity_frac_noevtsel.pdf");
  c->Print("~/pic/flow_pp/pp13TeV/highPurity_frac_noevtsel.eps");
}
