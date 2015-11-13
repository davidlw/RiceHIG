void lam_pol()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/lampolgen_pol070_n5001500.root");
  
  TH1D* hcos2p = (TH1D*)f->Get("corr_ana/cos2p_trg0_ass0");
  TH1D* hcos3p = (TH1D*)f->Get("corr_ana/cos3p_trg0_ass0");
  TH1D* hcos3p_rp = (TH1D*)f->Get("corr_ana/cos3p_rp_trg0_ass0");
  TH1D* hcos2p_ref = (TH1D*)f->Get("corr_ana/cos2p_ref_ass0");

cout<<hcos2p->GetMean()<<" "<<hcos3p_rp->GetMean()<<" "<<hcos3p->GetMean()<<" "<<hcos2p_ref->GetMean()<<endl;
cout<<hcos2p->GetMeanError()<<" "<<hcos3p_rp->GetMeanError()<<" "<<hcos3p->GetMeanError()<<" "<<hcos2p_ref->GetMeanError()<<endl;

  cout<<"P_3p = "<<sqrt((hcos2p->GetMean()-hcos3p_rp->GetMean())/2.)*8/0.642/3.1415926<<endl;
  cout<<"P_rp = "<<sqrt((hcos2p->GetMean()-hcos3p->GetMean()/sqrt(hcos2p_ref->GetMean()))/2.)*8/0.642/3.1415926<<endl;
}
