void lam_gen()
{
//  TFile* f = new TFile("../../cfg/lampolgen.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/lampol_p100_b812_pttrg065_etaass35_v1.root");

  TH1D* hcos2p = (TH1D*)f->Get("lampolgen/cos2p_trg0");
  TH1D* hcos3p = (TH1D*)f->Get("lampolgen/cos3p_trg0");
  TH1D* hcos3p_rp = (TH1D*)f->Get("lampolgen/cos3p_rp_trg0");
  TH1D* hcos2p_ref = (TH1D*)f->Get("lampolgen/cos2p_ref");
  TH1D* hcos_ref_rp = (TH1D*)f->Get("lampolgen/cos_ref_rp");
/*
  TH1D* hcos1p_p_ref = (TH1D*)f->Get("lampolgen/cos1p_p_ref");
  TH1D* hcos1p_m_ref = (TH1D*)f->Get("lampolgen/cos1p_m_ref");
  TH1D* hsin1p_p_ref = (TH1D*)f->Get("lampolgen/sin1p_p_ref");
  TH1D* hsin1p_m_ref = (TH1D*)f->Get("lampolgen/sin1p_m_ref");
*/
  double cos2p = hcos2p->GetMean();
  double cos3p = hcos3p->GetMean();
  double cos3p_rp = hcos3p_rp->GetMean();
  double cos2p_ref = hcos2p_ref->GetMean();
  double cos_ref_rp = hcos_ref_rp->GetMean();

  double cos2p_err = hcos2p->GetMeanError();
  double cos3p_err = hcos3p->GetMeanError();
  double cos3p_rp_err = hcos3p_rp->GetMeanError();
  double cos2p_ref_err = hcos2p_ref->GetMeanError();
  double cos_ref_rp_err = hcos_ref_rp->GetMeanError();

  double epres = cos_ref_rp/sqrt(cos2p_ref); 
/*
  double cos1p_p_ref = hcos1p_p_ref->GetMean();
  double cos1p_m_ref = hcos1p_m_ref->GetMean();
  double sin1p_p_ref = hsin1p_p_ref->GetMean();
  double sin1p_m_ref = hsin1p_m_ref->GetMean();
*/

  double P3p = sqrt((cos2p-cos3p/sqrt(cos2p_ref))/2.)*8/0.642/3.1415926;
  double P3pNorm = (cos2p-cos3p/sqrt(cos2p_ref));
  double P3p_err = sqrt((cos2p_ref_err*cos3p/sqrt(cos2p_ref)/cos2p_ref/P3pNorm/4.0)*(cos2p_ref_err*cos3p/sqrt(cos2p_ref)/cos2p_ref/P3pNorm/4.0)+(cos2p_err/P3pNorm/2.)*(cos2p_err/P3pNorm/2.)+(cos3p_err/sqrt(cos2p_ref)/P3pNorm/2.)*(cos3p_err/sqrt(cos2p_ref)/P3pNorm/2.))*P3p;

  double P3p_epres = sqrt((cos2p-cos3p/sqrt(cos2p_ref)/epres)/2.)*8/0.642/3.1415926;
  P3pNorm = (cos2p-cos3p/sqrt(cos2p_ref)/epres);
  double P3p_epres_err = sqrt((cos2p_ref_err*cos3p/sqrt(cos2p_ref)/cos2p_ref/P3pNorm/4.0)*(cos2p_ref_err*cos3p/sqrt(cos2p_ref)/cos2p_ref/P3pNorm/4.0)+(cos2p_err/P3pNorm/2.)*(cos2p_err/P3pNorm/2.)+(cos3p_err/sqrt(cos2p_ref)/P3pNorm/2.)*(cos3p_err/sqrt(cos2p_ref)/P3pNorm/2.))*P3p_epres; 

  double P3p_rp = sqrt((cos2p-cos3p_rp)/2.)*8/0.642/3.1415926;
  double P3p_rp_err = sqrt((cos2p_err/(cos2p-cos3p_rp)/2.)*(cos2p_err/(cos2p-cos3p_rp)/2.)+(cos3p_rp_err/(cos2p-cos3p_rp)/2.)*(cos3p_rp_err/(cos2p-cos3p_rp)/2.))*P3p_rp;

cout<<"cos(phi1-phi2)="<<hcos2p->GetMean()<<" "<<hcos2p->GetMeanError()<<endl;
cout<<"cos(phi1+phi2-2Psi2)="<<hcos3p->GetMean()<<" "<<hcos3p->GetMeanError()<<endl;
cout<<"RP cos(phi1+phi2-2Psi2)="<<hcos3p_rp->GetMean()<<" "<<hcos3p_rp->GetMeanError()<<endl;
cout<<"V2_ref="<<hcos2p_ref->GetMean()<<" "<<hcos2p_ref->GetMeanError()<<endl;
cout<<"v2_ref="<<sqrt(hcos2p_ref->GetMean())<<" "<<hcos2p_ref->GetMeanError()<<endl;
cout<<"RP v2_ref="<<hcos_ref_rp->GetMean()<<" "<<hcos_ref_rp->GetMeanError()<<endl;
cout<<"cos(phi1+phi2-2Psi2)/v2_ref="<<hcos3p->GetMean()/sqrt(hcos2p_ref->GetMean())<<endl;

cout<<"EP resolution:"<<cos_ref_rp/sqrt(cos2p_ref)<<endl;
//cout<<"V2_ref background="<<cos1p_p_ref*cos1p_m_ref+sin1p_p_ref*sin1p_m_ref<<endl;
//cout<<"v2_ref="<<sqrt(hcos2p_ref->GetMean()-cos1p_p_ref*cos1p_m_ref+sin1p_p_ref*sin1p_m_ref)<<" "<<hcos2p_ref->GetMeanError()<<endl;
//cout<<"cos(phi1+phi2-2Psi2)/v2_ref="<<hcos3p->GetMean()/sqrt(hcos2p_ref->GetMean()-cos1p_p_ref*cos1p_m_ref+sin1p_p_ref*sin1p_m_ref)<<endl;

  cout<<endl;
  cout<<"P_3p = "<<P3p<<", P_3p_err = "<<P3p_err<<endl;
  cout<<endl;
  cout<<"P_3p (ep reso) = "<<P3p_epres<<", P_3p_err = "<<P3p_epres_err<<endl;
  cout<<endl;
  cout<<"P_3p_rp = "<<P3p_rp<<", P_3p_rp_err = "<<P3p_rp_err<<endl;
}
 
void lam_gen_all()
{} 
