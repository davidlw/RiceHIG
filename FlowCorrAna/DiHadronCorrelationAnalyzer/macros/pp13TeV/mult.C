void mult()
{

  gStyle->SetOptStat(0);

  TFile* f_60 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_hlt60.root");
  TFile* f_85 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_hlt85.root");
  TFile* f_110 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_hlt110.root");
  TFile* f_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_mb.root");

  TH1D* h_mb = (TH1D*)f_mb->Get("corr_ana/multrawall");
  TH1D* h_60 = (TH1D*)f_60->Get("corr_ana/multrawall");
  TH1D* h_85 = (TH1D*)f_85->Get("corr_ana/multrawall");
  TH1D* h_110 = (TH1D*)f_110->Get("corr_ana/multrawall");

  h_mb->Rebin(2);
  h_60->Rebin(2);
  h_85->Rebin(2);
  h_110->Rebin(2);

  h_mb->Scale(1.0/h_mb->Integral("width"));
  h_60->Scale(1.0/h_60->Integral("width"));
  h_85->Scale(1.0/h_85->Integral("width"));
  h_110->Scale(1.0/h_110->Integral("width"));

  h_mb->SetMarkerColor(1);
  h_110->SetMarkerColor(kGreen+2);
  h_60->SetMarkerColor(2);
  h_85->SetMarkerColor(4);
  h_mb->SetMarkerStyle(20);
  h_60->SetMarkerStyle(20);
  h_110->SetMarkerStyle(20);
  h_85->SetMarkerStyle(20);
  h_mb->SetMarkerSize(1.3);
  h_60->SetMarkerSize(1.3);
  h_110->SetMarkerSize(1.3);
  h_85->SetMarkerSize(1.3);

  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogy();
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.08);
  c->SetRightMargin(0.05);
  h_mb->SetAxisRange(0,220,"X");
  h_mb->SetAxisRange(0.0000007,1,"Y");
  h_mb->SetTitle(";N_{trk}^{offline};P(N)");
  h_mb->GetXaxis()->CenterTitle();
  h_mb->GetYaxis()->CenterTitle();
  h_mb->GetXaxis()->SetTitleOffset(1.05);
  h_mb->GetYaxis()->SetTitleOffset(1.5);
  h_mb->GetXaxis()->SetTitleSize(h_mb->GetXaxis()->GetTitleSize()*1.2);
  h_mb->GetYaxis()->SetTitleSize(h_mb->GetYaxis()->GetTitleSize()*1.3);
  h_mb->Draw("PE");
  h_60->Draw("PESAME"); 
  h_85->Draw("PESAME");
  h_110->Draw("PESAME");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.8*latex->GetTextSize());
  latex->DrawLatex(0.65,0.94,"CMS Preliminary");
  latex->DrawLatex(0.15,0.94,"pp #sqrt{s} = 13 TeV");

  TLegend* legend = new TLegend(0.2,0.78,0.4,0.9);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.035);
  legend->AddEntry(h_mb,"MinBias","P");
  legend->AddEntry(h_60,"HLT N_{trk}^{online}>60","P");
  legend->Draw();

  TLegend* legend1 = new TLegend(0.5,0.78,0.7,0.9);
  legend1->SetFillStyle(0);
  legend1->SetBorderSize(0);
  legend1->SetTextSize(0.035);
  legend1->AddEntry(h_85,"HLT N_{trk}^{online}>85","P");
  legend1->AddEntry(h_110,"HLT N_{trk}^{online}>110","P");
  legend1->Draw();

  c->Print("~/pic/flow_pp/pp13TeV/mult_all.gif");
  c->Print("~/pic/flow_pp/pp13TeV/mult_all.C");
  c->Print("~/pic/flow_pp/pp13TeV/mult_all.pdf");
  c->Print("~/pic/flow_pp/pp13TeV/mult_all.eps");
}
