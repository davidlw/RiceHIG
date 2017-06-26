void example_rootuple()
{
  gStyle->SetOptStat(1);

  TFile* f = TFile::Open("/net/hisrv0001/home/davidlw/scratch/data/7TeV/ROOTuple_HighPurity_37_1.root");
  TTree* tr = f->Get("rootpleProducer/AnalysisTree");

  TClonesArray    *Track=0;
  TBranch         *b_Track=0;  
  tr->SetBranchAddress("Track", &Track, &b_Track);
 
  TH2D* hetapt = new TH2D("etapt","",30,-3,3,40,0,2);

  for(int i=0;i<tr->GetEntries();i++)
  {
    tr->GetEntry(i);
    TLorentzVector* track=0;
    TIterator *trackIter = trackIter = Track->MakeIterator();
    while((track = dynamic_cast<TLorentzVector*>(trackIter->Next())))
    {
      double eta = track->Eta();
      double phi = track->Phi();
      double pt  = track->Pt();
      hetapt->Fill(eta,pt);
    }  
  }

  TCanvas* c = new TCanvas("c","",600,600);
  hetapt->Draw("colz");

  TCanvas* c1 = new TCanvas("c1","",600,600);
  TH1D* heta = (TH1D*)hetapt->ProjectionX("eta",-1,-1,"e");
  heta->Draw("colz");

  TCanvas* c2 = new TCanvas("c2","",600,600);
  TH1D* hpt = (TH1D*)hetapt->ProjectionY("pt",-1,-1,"e");
  hpt->Draw("colz");
}
