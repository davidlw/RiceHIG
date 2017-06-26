void lam_genv2(bool isacc=0)
{
//  TFile* f = new TFile("../../cfg/lampolgen_noacc.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/lampol_p000_s000_b812_pttrg065_etaass35_pteff2_v6.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/EPOS_Minbias_5TeV/merged/lampol_gen_pol000_v1.root");

  TH1D* hcos2p = (TH1D*)f->Get("lampolgen/cos2p_trg0");
  TH1D* hcos3p = (TH1D*)f->Get("lampolgen/cos3p_p_trg0");
  TH1D* hcos3p_rp = (TH1D*)f->Get("lampolgen/cos3p_rp_trg0");
  TH1D* hcos2p_ref = (TH1D*)f->Get("lampolgen/cos2p_ref");
  TH1D* hcos_ref_rp = (TH1D*)f->Get("lampolgen/cos_ref_rp");

//acceptance correction
  double q3pterm1=0;
  double q3pterm2=0;
  double q3pterm3=0;
  double q2pterm1=0;
  if(isacc)
  {
    TH1D* hcos1p_p_ref = (TH1D*)f->Get("lampolgen/cos1p_p_ref");
    TH1D* hsin1p_p_ref = (TH1D*)f->Get("lampolgen/sin1p_p_ref");
    TH1D* hcos1p = (TH1D*)f->Get("lampolgen/cos1p_trg0");
    TH1D* hsin1p = (TH1D*)f->Get("lampolgen/sin1p_trg0");
    TH1D* hcosuu = (TH1D*)f->Get("lampolgen/cosuu_trg0");
    TH1D* hsinuu = (TH1D*)f->Get("lampolgen/sinuu_trg0");
    TH1D* hcosu2v_p = (TH1D*)f->Get("lampolgen/cosu2v_p_trg0");
    TH1D* hsinu2v_p = (TH1D*)f->Get("lampolgen/sinu2v_p_trg0");
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

cout<<"cos(phi1-phi2)="<<cos2p<<" "<<cos2p_err<<endl;
cout<<"cos(phi1+phi2-2Psi2)="<<cos3p<<" "<<cos3p_err<<endl;
cout<<"RP cos(phi1+phi2-2Psi2)="<<cos3p_rp<<" "<<cos3p_rp_err<<endl;
cout<<"V2_ref="<<cos2p_ref<<" "<<cos2p_ref_err<<endl;
cout<<"v2_ref="<<sqrt(cos2p_ref)<<" "<<cos2p_ref_err<<endl;
cout<<"RP v2_ref="<<cos_ref_rp<<" "<<cos_ref_rp_err<<endl;
cout<<"cos(phi1+phi2-2Psi2)/v2_ref="<<cos3p/sqrt(cos2p_ref)<<endl;

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

  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/scalarprod_b812_etatrg1_etaass35_v4.root");
  TH2D* htrkhfp = (TH2D*)f1->Get("scalarprod_ana_gen_trkhfp/signalcosn_trg0_ass0");
  TH2D* htrkhfm = (TH2D*)f1->Get("scalarprod_ana_gen_trkhfm/signalcosn_trg0_ass0");
  TH2D* hhfphfm = (TH2D*)f1->Get("scalarprod_ana_gen_hfphfm/signalcosn_trg0_ass0");
  double trkhfp = htrkhfp->GetMean();
  double trkhfm = htrkhfm->GetMean();
  double hfphfm = hhfphfm->GetMean();
  double trkhfp_err = htrkhfp->GetMeanError();
  double trkhfm_err = htrkhfm->GetMeanError();
  double hfphfm_err = hhfphfm->GetMeanError();
cout<<"trkhfp="<<trkhfp<<" trkhfp_err="<<trkhfp_err<<endl;
cout<<"trkhfm="<<trkhfm<<" trkhfm_err="<<trkhfm_err<<endl;
cout<<"hfphfm="<<hfphfm<<" hfphfm_err="<<hfphfm_err<<endl;

//  double v2_trk = sqrt(trkhfp*trkhfm/hfphfm);
  double v2_trk = sqrt(trkhfp/trkhfm*hfphfm);

cout<<"v2_trk = "<<v2_trk<<endl;

  P3p = sqrt((cos2p-cos3p/v2_trk/epres)/2.)*8/0.642/3.1415926;
  P3pNorm = (cos2p-cos3p/v2_trk/epres);

cout<<"P3 = "<<P3p<<endl;


}
 
