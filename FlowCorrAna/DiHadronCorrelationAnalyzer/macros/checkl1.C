void checkl1()
{
  TFile* f = new TFile("/net/hidsk0001/d00/scratch/frankma/data/HCRaw/hcraw-rerunl1hlt-masterv2-tower/merge/all.root");
  TNtuple* nt = (TNtuple*)f->Get("hltbitnew/HltTree");
  TH1D* h = new TH1D("h",";L1_ETT (GeV)",4402,-1,2200);
  h->Sumw2();
//  nt->Draw("L1EtTot>>h","L1EtTot>=100 || (L1EtTot<=140 && (L1JetCenEt>=16 || L1TauEt>=16)) || (L1CenJetEt>=36 || L1TauEt>=36 || L1ForJetEt>=36)","GOFF");
//  nt->Draw("L1EtTot>>h","(L1CenJetEt>=36 || L1TauEt>=36 || L1ForJetEt>=36)","GOFF");
  nt->Draw("L1EtTot>>h");
//  cout<<h->GetEntries()<<endl;  

//  TCanvas* c = new TCanvas("c","",500,500);
//  h->Draw();
}
