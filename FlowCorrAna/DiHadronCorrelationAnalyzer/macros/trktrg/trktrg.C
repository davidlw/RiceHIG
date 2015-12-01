void trktrg()
{
  gStyle->SetOptStat(0);
  TFile* f_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_5TeV/merged/dihadroncorrelation_pp2015_highPtTrk_mult_run262273.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_5TeV/merged/dihadroncorrelation_pp2015_MB_mult_run262273.root");

  TH1D* hpt = (TH1D*)f->Get("corr_ana/pt_signal_trg_0");
  TH1D* hpt_mb = (TH1D*)f_mb->Get("corr_ana/pt_signal_trg_0");
  hpt_mb->Scale(20);

  hpt->Rebin(5);
  hpt_mb->Rebin(5);
  hpt->SetLineWidth(2);
  hpt_mb->SetLineWidth(2);

  TCanvas* c = new TCanvas("c","c",550,500);
  c->SetLogy();
  hpt->SetAxisRange(9,80,"X");
  hpt->SetAxisRange(2,20000,"Y");
  hpt->SetTitle(";p_{T} (GeV/c);N_{trk}");
  hpt->GetYaxis()->SetTitleSize(0.05);  
  hpt->GetXaxis()->CenterTitle();
  hpt->GetYaxis()->CenterTitle();
  hpt->SetMarkerStyle(20);
  hpt->SetLineColor(2);
  hpt->Draw("hist");
  hpt_mb->Draw("histsame");

  TLegend* legend = new TLegend(0.4,0.67,0.85,0.8);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
//  legend->AddEntry(hpt_mb,"HLT_HIL1MinimumBiasHF1AND","L");
//  legend->AddEntry(hpt,"HLT_HIFullTrackXXX","L");
  legend->AddEntry(hpt_mb,"Minimum Bias trigger","L");
  legend->AddEntry(hpt,"High-p_{T} track trigger","L");
  legend->Draw();

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->DrawLatex(0.12,0.92,"CMS Preliminary");
  latex->DrawLatex(0.15,0.85,"pp #sqrt{s} = 5.02 TeV, run 262273");
  
}

