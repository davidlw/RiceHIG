void lam_data(bool isacc=0)
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/lampol_PbPb_sig_official_v2.root");

  TH1D* hcos2p = (TH1D*)f->Get("corr_ana/cos2p_trg0");
cout<<hcos2p->GetMean()<<endl;
  TH1D* hcos3p = (TH1D*)f->Get("corr_ana/cos3p_p_trg0");
  TH1D* hcos2p_ref = (TH1D*)f->Get("corr_ana/cos2p_ref");

//acceptance correction
  double q3pterm1=0;
  double q3pterm2=0;
  double q3pterm3=0;
  double q2pterm1=0;
  if(isacc)
  {
    TH1D* hcos1p_p_ref = (TH1D*)f->Get("corr_ana/cos1p_p_ref");
    TH1D* hsin1p_p_ref = (TH1D*)f->Get("corr_ana/sin1p_p_ref");
    TH1D* hcos1p = (TH1D*)f->Get("corr_ana/cos1p_trg0");
    TH1D* hsin1p = (TH1D*)f->Get("corr_ana/sin1p_trg0");
    TH1D* hcosuu = (TH1D*)f->Get("corr_ana/cosuu_trg0");
    TH1D* hsinuu = (TH1D*)f->Get("corr_ana/sinuu_trg0");
    TH1D* hcosu2v_p = (TH1D*)f->Get("corr_ana/cosu2v_p_trg0");
    TH1D* hsinu2v_p = (TH1D*)f->Get("corr_ana/sinu2v_p_trg0");
    double cos1p_p_ref = hcos1p_p_ref->GetMean();
    double sin1p_p_ref = hsin1p_p_ref->GetMean();
    double cos1p = hcos1p->GetMean();
    double sin1p = hsin1p->GetMean();
    double cosuu = hcosuu->GetMean();
    double sinuu = hsinuu->GetMean();
    double cosu2v = hcosu2v_p->GetMean();
    double sinu2v = hsinu2v_p->GetMean();
    TComplex q1p_p_ref(cos1p_p_ref,sin1p_p_ref);
    TComplex q1p(cos1p,sin1p);
    TComplex quu(cosuu,sinuu);
    TComplex qu2v(cosu2v,sinu2v);
    q3pterm1 = (quu*TComplex::Conjugate(q1p_p_ref)).Re();
    q3pterm2 = 2*(qu2v*q1p).Re();
    q3pterm3 = 2*(q1p*q1p*TComplex::Conjugate(q1p_p_ref)).Re();
    q2pterm1 = cos1p*cos1p+sin1p*sin1p;
cout<<"q2pterm1: "<<q2pterm1<<endl;
cout<<"q3pterm1: "<<q3pterm1<<endl;
cout<<"q3pterm2: "<<q3pterm2<<endl;
cout<<"q3pterm3: "<<q3pterm3<<endl;
  }

  double cos2p = hcos2p->GetMean()-q2pterm1;
  double cos3p = hcos3p->GetMean()+q3pterm1+q3pterm2-q3pterm3;
  double cos2p_ref = hcos2p_ref->GetMean();

  double cos2p_err = hcos2p->GetMeanError();
  double cos3p_err = hcos3p->GetMeanError();
  double cos2p_ref_err = hcos2p_ref->GetMeanError();

  double P3p = sqrt((cos2p-cos3p/sqrt(cos2p_ref))/2.)*8/0.642/3.1415926;
  double P3pNorm = (cos2p-cos3p/sqrt(cos2p_ref));
  double P3p_err = sqrt((cos2p_ref_err*cos3p/sqrt(cos2p_ref)/cos2p_ref/P3pNorm/4.0)*(cos2p_ref_err*cos3p/sqrt(cos2p_ref)/cos2p_ref/P3pNorm/4.0)+(cos2p_err/P3pNorm/2.)*(cos2p_err/P3pNorm/2.)+(cos3p_err/sqrt(cos2p_ref)/P3pNorm/2.)*(cos3p_err/sqrt(cos2p_ref)/P3pNorm/2.))*P3p;

cout<<"cos(phi1-phi2)="<<cos2p<<" "<<cos2p_err<<endl;
cout<<"cos(phi1+phi2-2Psi2)="<<cos3p<<" "<<cos3p_err<<endl;
cout<<"V2_ref="<<cos2p_ref<<" "<<cos2p_ref_err<<endl;
cout<<"v2_ref="<<sqrt(cos2p_ref)<<" "<<cos2p_ref_err<<endl;
cout<<"cos(phi1+phi2-2Psi2)/v2_ref="<<cos3p/sqrt(cos2p_ref)<<endl;

  cout<<endl;
  cout<<"P_3p = "<<P3p<<", P_3p_err = "<<P3p_err<<endl;
  cout<<endl;

}
 
