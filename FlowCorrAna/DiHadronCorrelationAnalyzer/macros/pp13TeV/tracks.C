void tracks()
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

//  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/trackntuple_pythia8.root"); 
  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/mult_pythia8_evtsel_purej_dz01_debug.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/mult_mb_purej_vtx1_debug.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_13TeV/merged/mult_pythia8_evtsel_purej_dz01_dataxy_debug.root");

//  TNtuple* nt1 = (TNtuple*)f1->Get("HITrackCorrections/recTree");
  TNtuple* nt1 = (TNtuple*)f1->Get("corr_ana/trackntuple");
  TNtuple* nt = (TNtuple*)f->Get("corr_ana/trackntuple");

  TH1D* hpt = new TH1D("hpt",";p_{T} (GeV/c)",40,0,20);
  TH1D* heta = new TH1D("heta",";#eta",60,-3.0,3.0);
  TH1D* hphi = new TH1D("hphi",";#phi",64,-3.2,3.2);
  TH1D* hpterr = new TH1D("hpterr",";#sigma(p_{T})/p_{T}",40,0.0,0.2);
  TH1D* hnhits = new TH1D("hnhits",";N_{hits}",50,0,50);
  TH1D* hchi2 = new TH1D("hchi2",";#chi^{2}/ndof",100,0,100);
  TH1D* hdz = new TH1D("hdz",";dz/#sigma(dz)",40,-10,10);
  TH1D* hdxy = new TH1D("hdxy",";dxy/#sigma(dxy)",40,-10,10);

  TH1D* hpt1 = new TH1D("hpt1",";p_{T} (GeV/c)",40,0,20);
  TH1D* heta1 = new TH1D("heta1",";#eta",60,-3.0,3.0);
  TH1D* hphi1 = new TH1D("hphi1",";#phi",64,-3.2,3.2);
  TH1D* hpterr1 = new TH1D("hpterr1",";#sigma(p_{T})/p_{T}",40,0.0,0.2);
  TH1D* hnhits1 = new TH1D("hnhits1",";N_{hits}",50,0,50);
  TH1D* hchi21 = new TH1D("hchi21",";#chi^{2}/ndof",100,0,100);
  TH1D* hdz1 = new TH1D("hdz1",";dz/#sigma(dz)",40,-10,10);
  TH1D* hdxy1 = new TH1D("hdxy1",";dxy/#sigma(dxy)",40,-10,10);

  hnhits->Sumw2();
  hnhits1->Sumw2();
/*
  nt1->Draw("recValues.ptr>>hpt1","recValues.highPurityr","GOFF");
  nt1->Draw("recValues.etar>>heta1","recValues.highPurityr","GOFF");
  nt1->Draw("recValues.phir>>hphi1","recValues.highPurityr","GOFF");
  nt1->Draw("(recValues.pterr/recValues.ptr)>>hpterr1","recValues.highPurityr","GOFF");
  nt1->Draw("recValues.hitr>>hnhits1","recValues.highPurityr","GOFF");
  nt1->Draw("recValues.chi2r>>hchi21","recValues.highPurityr","GOFF");
  nt1->Draw("recValues.dzerr>>hdz1","recValues.highPurityr","GOFF");
  nt1->Draw("recValues.d0err>>hdxy1","recValues.highPurityr","GOFF");
*/
  nt1->Draw("pt>>hpt1","highPurity","GOFF");
  nt1->Draw("eta>>heta1","highPurity","GOFF");
  nt1->Draw("phi>>hphi1","highPurity","GOFF");
  nt1->Draw("(pterr/pt)>>hpterr1","highPurity","GOFF");
  nt1->Draw("hit>>hnhits1","highPurity","GOFF");
  nt1->Draw("chi2>>hchi21","highPurity","GOFF");
  nt1->Draw("dzerr>>hdz1","highPurity","GOFF");
  nt1->Draw("d0err>>hdxy1","highPurity","GOFF");

  nt->Draw("pt>>hpt","highPurity","GOFF");
  nt->Draw("eta>>heta","highPurity","GOFF");
  nt->Draw("phi>>hphi","highPurity","GOFF");
  nt->Draw("(pterr/pt)>>hpterr","highPurity","GOFF");
  nt->Draw("hit>>hnhits","highPurity","GOFF");
  nt->Draw("chi2>>hchi2","highPurity","GOFF");
  nt->Draw("dzerr>>hdz","highPurity","GOFF");
  nt->Draw("d0err>>hdxy","highPurity","GOFF");

  hpt->Scale(1.0/hpt->Integral("width"));
  heta->Scale(1.0/heta->Integral("width"));
  hphi->Scale(1.0/hphi->Integral("width"));
  hpterr->Scale(1.0/hpterr->Integral("width"));
  hnhits->Scale(1.0/hnhits->Integral("width"));
  hchi2->Scale(1.0/hchi2->Integral("width"));
  hdz->Scale(1.0/hdz->Integral("width"));
  hdxy->Scale(1.0/hdxy->Integral("width"));

  hpt1->Scale(1.0/hpt1->Integral("width"));
  heta1->Scale(1.0/heta1->Integral("width"));
  hphi1->Scale(1.0/hphi1->Integral("width"));
  hpterr1->Scale(1.0/hpterr1->Integral("width"));
  hnhits1->Scale(1.0/hnhits1->Integral("width"));
  hchi21->Scale(1.0/hchi21->Integral("width"));
  hdz1->Scale(1.0/hdz1->Integral("width"));
  hdxy1->Scale(1.0/hdxy1->Integral("width"));

  hpt->SetMarkerStyle(20);
  heta->SetMarkerStyle(20);
  hphi->SetMarkerStyle(20);
  hpterr->SetMarkerStyle(20);
  hnhits->SetMarkerStyle(20);
  hchi2->SetMarkerStyle(20);
  hdz->SetMarkerStyle(20);
  hdxy->SetMarkerStyle(20);

  hpt->SetMarkerColor(2);
  heta->SetMarkerColor(2);
  hphi->SetMarkerColor(2);
  hpterr->SetMarkerColor(2);
  hnhits->SetMarkerColor(2);
  hchi2->SetMarkerColor(2);
  hdz->SetMarkerColor(2);
  hdxy->SetMarkerColor(2);

  hpt1->SetMarkerStyle(25);
  heta1->SetMarkerStyle(25);
  hphi1->SetMarkerStyle(25);
  hpterr1->SetMarkerStyle(25);
  hnhits1->SetMarkerStyle(25);
  hchi21->SetMarkerStyle(25);
  hdz1->SetMarkerStyle(25);
  hdxy1->SetMarkerStyle(25);

  hpt1->SetMarkerColor(4);
  heta1->SetMarkerColor(4);
  hphi1->SetMarkerColor(4);
  hpterr1->SetMarkerColor(4);
  hnhits1->SetMarkerColor(4);
  hchi21->SetMarkerColor(4);
  hdz1->SetMarkerColor(4);
  hdxy1->SetMarkerColor(4);

  TCanvas* c = new TCanvas("c","c",1000,400);
  c->Divide(3,1);
  c->cd(1);
  c->GetPad(1)->SetLogy();
  c->GetPad(1)->SetRightMargin(0.02);
  hpt->SetAxisRange(0,10,"X");
  hpt->Draw("PE");
  hpt1->Draw("PESAME");
  TLegend* legend = new TLegend(0.32,0.73,0.74,0.85);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
  legend->AddEntry(hpt,"CMS Data","P");
  legend->AddEntry(hpt1,"PYTHIA8 TuneCUETP8M1","P");
  legend->Draw();
  c->cd(2);
  c->GetPad(2)->SetRightMargin(0.02);
  heta->Draw("PE");
  heta1->Draw("PESAME");
  c->cd(3);
  c->GetPad(3)->SetRightMargin(0.02);
  hphi->SetAxisRange(-3.2,3.2,"X");
  hphi->SetAxisRange(0.1,0.2,"Y");
  hphi->Draw("PE");
  hphi1->Draw("PESAME");

  c->Print("~/pic/flow_pp/pp13TeV/tracks_ptetaphi_dz01.gif");
  c->Print("~/pic/flow_pp/pp13TeV/tracks_ptetaphi_dz01.C");
  c->Print("~/pic/flow_pp/pp13TeV/tracks_ptetaphi_dz01.pdf");
  c->Print("~/pic/flow_pp/pp13TeV/tracks_ptetaphi_dz01.eps");

  TCanvas* c1 = new TCanvas("c1","c1",1000,400);
  c1->Divide(3,1);
  c1->cd(1);
  c1->GetPad(1)->SetLogy();
  c1->GetPad(1)->SetRightMargin(0.02);
  hpterr1->Draw("PE");
  hpterr->Draw("PESAME");
  legend->Draw();
  c1->cd(2);
  c1->GetPad(2)->SetLogy();
  c1->GetPad(2)->SetRightMargin(0.02);
  hnhits1->SetAxisRange(0,40,"X");
  hnhits1->Draw("PE");
  hnhits->Draw("PESAME");
  c1->cd(3);
  c1->GetPad(3)->SetLogy();
  c1->GetPad(3)->SetRightMargin(0.02);
  hchi21->SetAxisRange(0,30,"X");
  hchi21->Draw("PE");
  hchi2->Draw("PESAME");
/*
  c1->Print("~/pic/flow_pp/pp13TeV/tracks_pterrnhitchi2_evtsel_vtz1.gif");
  c1->Print("~/pic/flow_pp/pp13TeV/tracks_pterrnhitchi2_evtsel_vtz1.C");
  c1->Print("~/pic/flow_pp/pp13TeV/tracks_pterrnhitchi2_evtsel_vtz1.pdf");
  c1->Print("~/pic/flow_pp/pp13TeV/tracks_pterrnhitchi2_evtsel_vtz1.eps");
*/
  TCanvas* c2 = new TCanvas("c2","c2",800,400);
  c2->Divide(2,1);
  c2->cd(1);
  c2->GetPad(1)->SetLogy();
  c2->GetPad(1)->SetRightMargin(0.02);
  hdz->SetMaximum(7.0);
  hdz->Draw("PE");
  hdz1->Draw("PESAME");
  legend->Draw();
  c2->cd(2);
  c2->GetPad(2)->SetLogy();
  c2->GetPad(2)->SetRightMargin(0.02);
  hdxy->SetMaximum(7.0);
  hdxy->Draw("PE");
  hdxy1->Draw("PESAME");
/*
  c2->Print("~/pic/flow_pp/pp13TeV/tracks_dca_evtsel_vtx1.gif");
  c2->Print("~/pic/flow_pp/pp13TeV/tracks_dca_evtsel_vtx1.C");
  c2->Print("~/pic/flow_pp/pp13TeV/tracks_dca_evtsel_vtx1.pdf");
  c2->Print("~/pic/flow_pp/pp13TeV/tracks_dca_evtsel_vtx1.eps");
*/
}
