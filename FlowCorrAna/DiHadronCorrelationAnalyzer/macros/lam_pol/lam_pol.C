void lam_pol()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/lampolgen_pol070_n5001500.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/lampol_n1851000.root");
  
  TH1D* hcos1p = (TH1D*)f->Get("corr_ana/cos1p_trg2");
  TH1D* hcos2p_signal = (TH1D*)f->Get("corr_ana/cos2p_signal_trg2");
  TH1D* hcos2p_background = (TH1D*)f->Get("corr_ana/cos2p_background_trg2");
  TH1D* hcos3p = (TH1D*)f->Get("corr_ana/cos3p_trg2");
  TH1D* hcos2p_ref = (TH1D*)f->Get("corr_ana/cos2p_ref");

cout<<hcos1p->GetMean()<<" "<<hcos1p->GetMeanError()<<endl;
cout<<hcos2p_signal->GetMean()<<" "<<hcos2p_signal->GetMeanError()<<endl;
cout<<hcos2p_background->GetMean()<<" "<<hcos2p_background->GetMeanError()<<endl;
cout<<hcos3p->GetMean()<<" "<<hcos3p->GetMeanError()<<endl;
cout<<hcos2p_ref->GetMean()<<" "<<hcos2p_ref->GetMeanError()<<endl;

//cout<<hcos2p->GetMean()<<" "<<hcos3p_rp->GetMean()<<" "<<hcos3p->GetMean()<<" "<<hcos2p_ref->GetMean()<<endl;
//cout<<hcos2p->GetMeanError()<<" "<<hcos3p_rp->GetMeanError()<<" "<<hcos3p->GetMeanError()<<" "<<hcos2p_ref->GetMeanError()<<endl;

//  cout<<"P_3p = "<<sqrt((hcos2p->GetMean()-hcos3p_rp->GetMean())/2.)*8/0.642/3.1415926<<endl;
//  cout<<"P_rp = "<<sqrt((hcos2p->GetMean()-hcos3p->GetMean()/sqrt(hcos2p_ref->GetMean()))/2.)*8/0.642/3.1415926<<endl;
}
