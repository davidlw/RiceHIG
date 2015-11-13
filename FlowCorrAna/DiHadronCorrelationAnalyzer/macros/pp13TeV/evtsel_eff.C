void evtsel_eff()
{
  gStyle->SetOptStat(0);

  TFile* f_110 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/mult_pythia8_evtsel.root");
  TFile* f_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/mult_pythia8_dsgen.root");

  TFile* f1_110 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/EPOSReco_Minbias_13TeV/merged/mult_epos_evtsel.root");
  TFile* f1_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/EPOSReco_Minbias_13TeV/merged/mult_epos_dsgen.root");

  TFile* f_data = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_mb_vtx1.root");

  TH1D* h_mb = (TH1D*)f_mb->Get("corr_ana/multrawall");
  TH1D* h_110 = (TH1D*)f_110->Get("corr_ana/multrawall");

  TH1D* h1_mb = (TH1D*)f1_mb->Get("corr_ana/multrawall");
  TH1D* h1_110 = (TH1D*)f1_110->Get("corr_ana/multrawall");

  TH1D* h_data = (TH1D*)f_data->Get("corr_ana/multrawall");

/*
  h_mb->Rebin(2);
  h_110->Rebin(2);
*/
  h_mb->SetMarkerColor(1);
  h_110->SetMarkerColor(1);
  h_mb->SetMarkerStyle(20);
  h_110->SetMarkerStyle(24);
  h_mb->SetMarkerSize(1.3);
  h_110->SetMarkerSize(1.3);

  h1_mb->SetMarkerColor(1);
  h1_110->SetMarkerColor(1);
  h1_mb->SetMarkerStyle(20);
  h1_110->SetMarkerStyle(24);
  h1_mb->SetMarkerSize(1.3);
  h1_110->SetMarkerSize(1.3);

  h_data->SetMarkerColor(2);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(1.3);

  TCanvas* c = new TCanvas("c","",600,600);
  c->SetLogy();
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.08);
  c->SetRightMargin(0.05);
  h_mb->SetAxisRange(0,20,"X");
//  h_mb->SetAxisRange(0.00000002,0.4,"Y");
  h_mb->SetTitle(";N_{trk}^{offline};P(N)");
  h_mb->GetXaxis()->CenterTitle();
  h_mb->GetYaxis()->CenterTitle();
  h_mb->GetXaxis()->SetTitleOffset(1.05);
  h_mb->GetYaxis()->SetTitleOffset(1.3);
  h_mb->GetXaxis()->SetTitleSize(h_mb->GetXaxis()->GetTitleSize()*1.2);
  h_mb->GetYaxis()->SetTitleSize(h_mb->GetYaxis()->GetTitleSize()*1.1);
  h_mb->Draw("PE");
  h_110->Draw("PESAME");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.8*latex->GetTextSize());
  latex->DrawLatex(0.65,0.94,"CMS Preliminary");

cout<<"Overall efficiency:"<<endl;
cout<<"PYTHIA8: "<<h_110->Integral(1,10000)/h_mb->Integral(1,10000)<<endl;
cout<<"EPOS LHC: "<<h1_110->Integral(1,10000)/h1_mb->Integral(1,10000)<<endl;

  TH1D* heff = (TH1D*)h_mb->Clone("heff");
  heff->Reset();
  heff->Add(h_110);
  heff->Divide(h_mb);
  TH1D* heff1 = (TH1D*)h1_mb->Clone("heff");
  heff1->Reset();
  heff1->Add(h1_110);
  heff1->Divide(h1_mb);
  heff1->SetMarkerStyle(24);

  TCanvas* c1 = new TCanvas("c1","",600,600);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.08);
  c1->SetRightMargin(0.05);  
  heff->SetYTitle("Selection Efficiency for DS MinBias");
  heff->Draw("PE");
  heff1->Draw("PESAME");
  latex->DrawLatex(0.65,0.94,"CMS Preliminary");
  latex->DrawLatex(0.48,0.325,"pp MC #sqrt{s} = 13 TeV");

  TLegend* legend = new TLegend(0.42,0.18,0.64,0.3);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
  legend->AddEntry(heff,"PYTHIA8 TuneCUETP8M1","P");
  legend->AddEntry(heff1,"EPOS LHC","P");
  legend->Draw();

  c1->Print("~/pic/flow_pp/pp13TeV/evtseleff_compare.gif");
  c1->Print("~/pic/flow_pp/pp13TeV/evtseleff_compare.C");
  c1->Print("~/pic/flow_pp/pp13TeV/evtseleff_compare.pdf");
  c1->Print("~/pic/flow_pp/pp13TeV/evtseleff_compare.eps");

  h_mb->Scale(1.0/h_mb->Integral("width"));
  h_110->Scale(1.0/h_110->Integral("width"));
  h1_mb->Scale(1.0/h1_mb->Integral("width"));
  h1_110->Scale(1.0/h1_110->Integral("width"));
  h_data->Scale(1.0/h_data->Integral("width"));

  TCanvas* c2 = new TCanvas("c2","",600,600);
  c2->SetLeftMargin(0.15);
  c2->SetBottomMargin(0.12);
  c2->SetTopMargin(0.08);
  c2->SetRightMargin(0.05);
  h1_mb->SetMarkerStyle(24);
  h_mb->SetAxisRange(0,100,"X");
  h_mb->Draw("PE");
  h1_mb->Draw("PESAME");
  h_data->Draw("PESAME");
}
