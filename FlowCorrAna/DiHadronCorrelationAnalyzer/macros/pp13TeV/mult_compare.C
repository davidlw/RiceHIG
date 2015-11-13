void mult_compare()
{
  gStyle->SetOptStat(0);

  TFile* f_110 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_7TeV/merged/PPData_Minbias_7TeV_MINBIAS_All_Apr21ReReco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TFile* f_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_mb.root");

  TH1D* h_mb = (TH1D*)f_mb->Get("corr_ana/multrawall");
  TH1D* h_110 = (TH1D*)f_110->Get("multrawall");

  h_mb->Rebin(2);
  h_110->Rebin(2);

  h_mb->Scale(1.0/h_mb->Integral("width"));
  h_110->Scale(1.0/h_110->Integral("width"));

  h_mb->SetMarkerColor(1);
  h_110->SetMarkerColor(1);
  h_mb->SetMarkerStyle(20);
  h_110->SetMarkerStyle(24);
  h_mb->SetMarkerSize(1.3);
  h_110->SetMarkerSize(1.3);

  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogy();
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.08);
  c->SetRightMargin(0.05);
  h_mb->SetAxisRange(0,170,"X");
  h_mb->SetAxisRange(0.00000002,0.4,"Y");
  h_mb->SetTitle(";N_{trk}^{offline};P(N)");
  h_mb->GetXaxis()->CenterTitle();
  h_mb->GetYaxis()->CenterTitle();
  h_mb->GetXaxis()->SetTitleOffset(1.05);
  h_mb->GetYaxis()->SetTitleOffset(1.5);
  h_mb->GetXaxis()->SetTitleSize(h_mb->GetXaxis()->GetTitleSize()*1.2);
  h_mb->GetYaxis()->SetTitleSize(h_mb->GetYaxis()->GetTitleSize()*1.3);
  h_mb->Draw("PE");
  h_110->Draw("PESAME");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.8*latex->GetTextSize());
  latex->DrawLatex(0.65,0.94,"CMS Preliminary");

  TLegend* legend = new TLegend(0.6,0.78,0.8,0.9);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
  legend->AddEntry(h_mb,"pp #sqrt{s} = 13 TeV","P");
  legend->AddEntry(h_110,"pp #sqrt{s} = 7 TeV","P");
  legend->Draw();

  c->Print("~/pic/flow_pp/pp13TeV/mult_compare.gif");
  c->Print("~/pic/flow_pp/pp13TeV/mult_compare.C");
  c->Print("~/pic/flow_pp/pp13TeV/mult_compare.pdf");
  c->Print("~/pic/flow_pp/pp13TeV/mult_compare.eps");
}
