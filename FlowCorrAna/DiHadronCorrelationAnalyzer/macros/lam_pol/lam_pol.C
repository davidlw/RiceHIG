void lam_pol()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/lampolgen_pol005_cent3050_pt1-5_ptassall.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/lampol_n1851000.root");
  
  TH1D* hcos1p = (TH1D*)f->Get("lampolgen/cos1p_trg0");
  TH1D* hcos2p = (TH1D*)f->Get("lampolgen/cos2p_trg0_ass0");
  TH1D* hcos3p = (TH1D*)f->Get("lampolgen/cos3p_trg0_ass0");
  TH1D* hcos2p_ref = (TH1D*)f->Get("lampolgen/cos2p_ref_ass0");
  TH1D* hcos_true = (TH1D*)f->Get("lampolgen/sin1p_rp_trg0");

  TH1D* hsin2p_rp = (TH1D*)f->Get("lampolgen/sin1p_rp_trg0");
  TH1D* hcos2p_rp = (TH1D*)f->Get("lampolgen/cos1p_rp_trg0");

  TH1D* hcos_ref_rp = (TH1D*)f->Get("lampolgen/cos_ref_rp_ass0");

  double cos1p = hcos1p->GetMean();
  double cos2p = hcos2p->GetMean();
  double cos3p = hcos3p->GetMean(); 
  double cos2p_ref = hcos2p_ref->GetMean();
  double cos1p_err = hcos1p->GetMeanError();
  double cos2p_err = hcos2p->GetMeanError();
  double cos3p_err = hcos3p->GetMeanError();
  double cos2p_ref_err = hcos2p_ref->GetMeanError();

  double sin2p_rp = hsin2p_rp->GetMean();
  double cos2p_rp = hcos2p_rp->GetMean();
  double sin2p_rp_err = hsin2p_rp->GetMeanError();
  double cos2p_rp_err = hcos2p_rp->GetMeanError();

  double cos_ref_rp = hcos_ref_rp->GetMean();
  double cos_ref_rp_err = hcos_ref_rp->GetMeanError();

  double P3p = sqrt((hcos2p->GetMean()-hcos3p->GetMean()/sqrt(hcos2p_ref->GetMean()))/2.)*8/0.642/3.1415926;
  double Prp = sqrt((hcos2p->GetMean()-hcos3p->GetMean()/hcos_ref_rp->GetMean())/2.)*8/0.642/3.1415926;
  double Ptrue = hcos_true->GetMean();
  double P3p_err = sqrt((cos2p_ref_err/cos2p_ref/4.0)*(cos2p_ref_err/cos2p_ref/4.0)+(cos2p_err/cos2p/2.)*(cos2p_err/cos2p/2.)+(cos3p_err/cos3p/2.)*(cos3p_err/cos3p/2.))*P3p;
  double Prp_err = sqrt((cos_ref_rp_err/cos_ref_rp/2.0)*(cos_ref_rp_err/cos_ref_rp/2.0)+(cos2p_err/cos2p/2.)*(cos2p_err/cos2p/2.)+(cos3p_err/cos3p/2.)*(cos3p_err/cos3p/2.))*Prp;
  double Ptrue_err = hcos_true->GetMeanError();

cout<<hcos1p->GetMean()<<" "<<hcos1p->GetMeanError()<<endl;
cout<<hcos2p->GetMean()<<" "<<hcos2p->GetMeanError()<<endl;
cout<<hcos3p->GetMean()<<" "<<hcos3p->GetMeanError()<<endl;
cout<<hcos2p_ref->GetMean()<<" "<<hcos2p_ref->GetMeanError()<<endl;

cout<<endl;
cout<<hsin2p_rp->GetMean()<<" "<<hsin2p_rp->GetMeanError()<<endl;
cout<<hcos2p_rp->GetMean()<<" "<<hcos2p_rp->GetMeanError()<<endl;

cout<<endl;
cout<<hcos_ref_rp->GetMean()<<" "<<hcos_ref_rp->GetMeanError()<<endl;

cout<<endl;

//cout<<hcos2p->GetMean()<<" "<<hcos3p_rp->GetMean()<<" "<<hcos3p->GetMean()<<" "<<hcos2p_ref->GetMean()<<endl;
//cout<<hcos2p->GetMeanError()<<" "<<hcos3p_rp->GetMeanError()<<" "<<hcos3p->GetMeanError()<<" "<<hcos2p_ref->GetMeanError()<<endl;

//  cout<<"P_rp = "<<sqrt((hcos2p->GetMean()-hcos3p_rp->GetMean())/2.)*8/0.642/3.1415926<<endl;
  cout<<"P_3p = "<<P3p<<", P_3p_err = "<<P3p_err<<endl;
  cout<<"P_rp = "<<Prp<<", P_rp_err = "<<Prp_err<<endl;
  cout<<"P_true = "<<Ptrue<<", P_true_err = "<<Ptrue_err<<endl;


}
