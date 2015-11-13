void vertex()
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/mult_pythia8_purej_dz01_debug.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_mb_purej_dz01_debug.root");

  TH1D* hvz = (TH1D*)f->Get("corr_ana/zvtx");
  TH1D* hvz1 = (TH1D*)f1->Get("corr_ana/zvtx");
  TH2D* hvxy = (TH2D*)f->Get("corr_ana/xyvtx");
  TH2D* hvxy1 = (TH2D*)f1->Get("corr_ana/xyvtx");

  hvz->Scale(1.0/hvz->Integral("width"));
  hvz1->Scale(1.0/hvz1->Integral("width"));
  hvxy->Scale(1.0/hvxy->Integral("width"));
  hvxy1->Scale(1.0/hvxy1->Integral("width"));
  
  hvz->SetMarkerStyle(20);
  hvz1->SetMarkerStyle(24);

  TCanvas* c = new TCanvas("c","c",500,500);
//  c->SetLogy();
  c->SetRightMargin(0.02);
  hvz->SetMaximum(0.13);
  hvz->Draw("PE");
  hvz1->Draw("PESAME");
  TLegend* legend = new TLegend(0.22,0.73,0.64,0.85);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
  legend->AddEntry(hvz,"CMS Data","P");
  legend->AddEntry(hvz1,"PYTHIA8 TuneCUETP8M1","P");
  legend->Draw();

  c->Print("~/pic/flow_pp/pp13TeV/vz_compare_vtx1.gif");
  c->Print("~/pic/flow_pp/pp13TeV/vz_compare_vtx1.C");
  c->Print("~/pic/flow_pp/pp13TeV/vz_compare_vtx1.pdf");
  c->Print("~/pic/flow_pp/pp13TeV/vz_compare_vtx1.eps");

  TCanvas* c1 = new TCanvas("c1","c1",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  c1->GetPad(1)->SetRightMargin(0.18);
  hvxy->SetTitle("CMS Data");
  hvxy->Draw("colz");
  c1->cd(2);
  c1->GetPad(2)->SetRightMargin(0.18);
  hvxy1->SetTitle("PYTHIA8 TuneCUETP8M1");
  hvxy1->Draw("colz");

  c1->Print("~/pic/flow_pp/pp13TeV/vxy_compare_dz01.gif");
  c1->Print("~/pic/flow_pp/pp13TeV/vxy_compare_dz01.C");
  c1->Print("~/pic/flow_pp/pp13TeV/vxy_compare_dz01.pdf");
  c1->Print("~/pic/flow_pp/pp13TeV/vxy_compare_dz01.eps");
}
