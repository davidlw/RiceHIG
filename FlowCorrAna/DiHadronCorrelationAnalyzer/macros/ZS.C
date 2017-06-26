void ZS()
{
  TFile* f = new TFile("ZeroSupTracks_18ev_Dist10.root");
  TFile* f1 = new TFile("ZeroSupTracks_18ev_Dist15.root");
  TFile* f2 = new TFile("ZeroSupTracks_18ev_Nominal.root");
  TFile* f3 = new TFile("ZeroSupTracks_18ev_Dist25.root");
  TFile* f4 = new TFile("ZeroSupTracks_18ev_Dist30.root");
  TFile* f5 = new TFile("ZeroSupTracks_18ev_Dist50.root");

  TNtuple* nt = (TNtuple*)f->Get("ana_PbPb/TrackParOffline");
  TNtuple* nt1 = (TNtuple*)f1->Get("ana_PbPb/TrackParOffline");
  TNtuple* nt2 = (TNtuple*)f2->Get("ana_PbPb/TrackParOffline");
  TNtuple* nt3 = (TNtuple*)f3->Get("ana_PbPb/TrackParOffline");
  TNtuple* nt4 = (TNtuple*)f4->Get("ana_PbPb/TrackParOffline");
  TNtuple* nt5 = (TNtuple*)f5->Get("ana_PbPb/TrackParOffline");

  TH1D* hpt = new TH1D("hpt",";p_{T} (GeV)",400,0,40);
  TH1D* hpt1 = new TH1D("hpt1",";p_{T} (GeV)",400,0,40);
  TH1D* hpt2 = new TH1D("hpt2",";p_{T} (GeV)",400,0,40);
  TH1D* hpt3 = new TH1D("hpt3",";p_{T} (GeV)",400,0,40);
  TH1D* hpt4 = new TH1D("hpt4",";p_{T} (GeV)",400,0,40);
  TH1D* hpt5 = new TH1D("hpt5",";p_{T} (GeV)",400,0,40);
/*
  nt->Draw("pt>>hpt","highPurity","GOFF");
  nt->Draw("pt>>hpt1","highPurity","GOFF");
  nt->Draw("pt>>hpt2","highPurity","GOFF");
*/
  nt->Draw("pt>>hpt","highPurity","GOFF");
  nt1->Draw("pt>>hpt1","highPurity","GOFF");
  nt2->Draw("pt>>hpt2","highPurity","GOFF");
  nt3->Draw("pt>>hpt3","highPurity","GOFF");
  nt4->Draw("pt>>hpt4","highPurity","GOFF");
  nt5->Draw("pt>>hpt5","highPurity","GOFF");

  hpt->Divide(hpt2);
  hpt1->Divide(hpt2);
  hpt3->Divide(hpt2);
  hpt4->Divide(hpt2);
  hpt5->Divide(hpt2);

  TH2D* htmp = new TH2D("htmp",";p_{T} (GeV);Ratio",400,0,40,100,0.,10);
  TCanvas* c = new TCanvas("c","",500,500);
  htmp->Draw();
  hpt->Draw("PE");
  hpt1->Draw("PESAME");
  hpt3->Draw("PESAME");
  hpt4->Draw("PESAME");
  hpt5->Draw("PESAME");
}
