#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
//#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"

void drawCorr_2D()
{
  int ptmin=0;
  int ptmax=0;
  double zmin=0.98;
  double zmax=0.94;
  int nmin=330;
  int nmax=360;

//  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/dihadron_2016_N300inf.root");
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt13_N330HM7_run285479_285549_v6.root");
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),"corr_ana_N330360",ptmin,ptmax);

  h->SetAxisRange(h->GetMinimum()*zmin,h->GetMaximum()*zmax,"Z");

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetBottomMargin(0.05);
  c->SetRightMargin(0.02);
  c->SetLeftMargin(0.18);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.3,4.3,"X");
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*1.4);
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*1.4);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*1.3);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.3);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.3);
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.35);
  h->Draw("surf1 fb");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.8*latex->GetTextSize());
  latex->DrawLatex(0.045,0.95,Form("CMS pPb #sqrt{s_{NN}} = 8.16 TeV, %d #leq N < %d",nmin,nmax));
//  latex->DrawLatex(0.045,0.95,Form("CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV, %d #leq N < %d",nmin,nmax));
  latex->DrawLatex(0.045,0.86,"1 < p_{T}^{trig} < 3 GeV/c");
  latex->DrawLatex(0.045,0.8,"1 < p_{T}^{assoc} < 3 GeV/c");

  SaveCanvas(c,"pPb/8TeV",Form("corr2D_pPb8TeV_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));

//  SaveCanvas(c,"pPb/corr",Form("corr2D_pPbNew_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));
//  SaveCanvas(c,"pPb/corr",Form("corr2D_PbPb_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));

return;
  TFile* fout = new TFile(Form("results/results_2D_N%d%d_eff.root",nmin,nmax),"recreate");
//  TFile* fout = new TFile(Form("results/results_2D_HF170_noeff.root",nmin,nmax),"recreate");
  h->Write();
  fout->Close();
}

void drawCorr_dphi()
{ 
  int ptmin=0;
  int ptmax=0;
  double detamin=1.9;
  double detamax=4.8;
  double ymin=0.992;
  double ymax=1.012;
  int nmin=330;
  int nmax=360;

  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt13_N330HM7_run285479_285549_v6.root");
  TH1D* h = (TH1D*)Get1DCFdPhiv3(filename.Data(),"corr_ana_N330360",ptmin,ptmax,detamin,detamax);
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.8);
  h->GetYaxis()->SetLabelSize(h->GetYaxis()->GetLabelSize()*0.8);
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*0.8);
  h->GetXaxis()->SetLabelSize(h->GetXaxis()->GetLabelSize()*0.8);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
  h->SetMarkerColor(kRed);
  h->SetMarkerStyle(20);
  h->SetAxisRange(h->GetMinimum()*ymin,h->GetMaximum()*ymax,"Y");
  h->SetAxisRange(-3.1416/2+0.1,3*3.1416/2-0.1,"X");
  h->SetMarkerSize(1.5);

  TCanvas* c = new TCanvas("c","",600,500);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.1);
  c->SetTopMargin(0.08);
  c->SetRightMargin(0.05);
  h->Draw("PE");

  TF1* fit = new TF1("fit","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x))",-PI/2+0.1,3*PI/2-0.1);
  h->Fit("fit","RNO");
  h->Fit("fit","RNO");
  h->Fit("fit","RNO");
  fit->SetLineWidth(2);
  fit->Draw("LSAME");

  TF1* fit1 = new TF1("fit1","[0]*(1+2*[1]*cos(x))",-PI/2+0.1,3*PI/2-0.1);
  TF1* fit2 = new TF1("fit2","[0]*(1+2*[1]*cos(2*x))",-PI/2+0.1,3*PI/2-0.1);
  TF1* fit3 = new TF1("fit3","[0]*(1+2*[1]*cos(3*x))",-PI/2+0.1,3*PI/2-0.1);
  TF1* fit4 = new TF1("fit4","[0]*(1+2*[1]*cos(4*x))",-PI/2+0.1,3*PI/2-0.1);
  TF1* fit5 = new TF1("fit5","[0]*(1+2*[1]*cos(5*x))",-PI/2+0.1,3*PI/2-0.1);
  TF1* fit6 = new TF1("fit6","[0]*(1+2*[1]*cos(6*x))",-PI/2+0.1,3*PI/2-0.1);
  fit1->SetParameters(fit->GetParameter(0),fit->GetParameter(1));
  fit2->SetParameters(fit->GetParameter(0),fit->GetParameter(2));
  fit3->SetParameters(fit->GetParameter(0),fit->GetParameter(3));
  fit4->SetParameters(fit->GetParameter(0),fit->GetParameter(4));
  fit5->SetParameters(fit->GetParameter(0),fit->GetParameter(5));
  fit6->SetParameters(fit->GetParameter(0),fit->GetParameter(6));
  fit1->SetLineStyle(2);
  fit2->SetLineStyle(9);
  fit3->SetLineStyle(5);
  fit4->SetLineStyle(8);
  fit5->SetLineStyle(6);
  fit6->SetLineStyle(3);
  fit1->SetLineColor(1);
  fit2->SetLineColor(2);
  fit3->SetLineColor(kGreen+3);
  fit4->SetLineColor(4);
  fit5->SetLineColor(6);
  fit6->SetLineColor(7);
  fit1->SetLineWidth(2);
  fit2->SetLineWidth(2);
  fit3->SetLineWidth(2);
  fit4->SetLineWidth(2);
  fit5->SetLineWidth(2);
  fit6->SetLineWidth(2);
  fit1->Draw("LSAME");
  fit2->Draw("LSAME");
  fit3->Draw("LSAME");
  fit4->Draw("LSAME");
//  fit5->Draw("LSAME");
//  fit6->Draw("LSAME"); 
  h->Draw("PESAME");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.8*latex->GetTextSize());
  latex->DrawLatex(0.16,0.95,Form("CMS pPb #sqrt{s_{NN}} = 8.16 TeV, %d #leq N < %d",nmin,nmax));
  latex->DrawLatex(0.18,0.855,"1 < p_{T}^{trig} < 3 GeV/c");
  latex->DrawLatex(0.18,0.79,"1 < p_{T}^{assoc} < 3 GeV/c");

  SaveCanvas(c,"pPb/8TeV",Form("corr1D_pPb8TeV_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));
}
/*
void compareCorr_dphi(double ymin=0.95, double ymax=1.05)
{
//  TString eventtype1="PythiaReco_Minbias_7TeV";
  TString eventtype1="PPData_Minbias_7TeV";
//  TString tag1="TuneZ2_MinBias_42x_INCLHFPHFPPtWeight00Inf";
  TString tag1="TRIGGER_All_Apr21ReReco_INCLHFPHFMPtWeight032";
//  TString tag1="MINBIAS_All_Apr21ReReco_INCLHFPHFMPtWeight035";
//  TString tag1="MINBIAS_All_Apr21ReReco_INCLTrackPHFMPtWeight0310";
  int nmin1=150;
  int nmax1=1000;
  int centmin1=-1;
  int centmax1=-1;
  double etatrgmin1=-5.0;
  double etatrgmax1=-3.0;
  double etaassmin1=3.0;
  double etaassmax1=5.0;

//  TString eventtype2="PythiaReco_Minbias_7TeV";
  TString eventtype2="PPData_Minbias_7TeV";
//  TString tag2="TuneZ2_MinBias_42x_INCLHFPHFPPtWeight00Inf";
//  TString tag2="MINBIAS_All_Apr21ReReco_INCLHFPHFMPtWeight03Inf";
  TString tag2="TRIGGER_All_Apr21ReReco_INCLHFPHFMPtWeight032";
//  TString tag2="MINBIAS_All_Apr21ReReco_INCLHFPHFM033";
  int nmin2=150;
  int nmax2=1000;
  int centmin2=-1; 
  int centmax2=-1;
  double etatrgmin2=-5.0;
  double etatrgmax2=-3.0;
  double etaassmin2=3.0;
  double etaassmax2=5.0;

  TString filename1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin1,nmax1,etatrgmin1,etatrgmax1,etaassmin1,etaassmax1,centmin1,centmax1);
  TString filename2 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype2.Data(),eventtype2.Data(),tag2.Data(),nmin2,nmax2,etatrgmin2,etatrgmax2,etaassmin2,etaassmax2,centmin2,centmax2);

  int ptmin1=0;
  int ptmax1=0;
  double detamin1=-15;
  double detamax1=15;

  int ptmin2=0;
  int ptmax2=0;
  double detamin2=-15;
  double detamax2=15;

  TH1D* h1 = (TH1D*)Get1DCFdPhiv3(filename1.Data(),ptmin1,ptmax1,detamin1,detamax1);
  TH1D* h1_zyam=GetJetCorrFunc1D_ZYAM_pp(h1);
  h1_zyam->SetAxisRange(h1_zyam->GetMinimum()*ymin,h1_zyam->GetMaximum()*ymax,"Y");

  TH1D* h2 = (TH1D*)Get1DCFdPhiv3(filename2.Data(),ptmin2,ptmax2,detamin2,detamax2);
  TH1D* h2_zyam=GetJetCorrFunc1D_ZYAM_pp(h2);
  h2_zyam->SetAxisRange(h2_zyam->GetMinimum()*ymin,h2_zyam->GetMaximum()*ymax,"Y");

//  TF1* fit1 = new TF1("fit1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x)+2*[7]*cos(7*x)+2*[8]*cos(8*x)+2*[9]*cos(9*x)+2*[10]*cos(10*x)+2*[11]*cos(11*x)+2*[12]*cos(12*x))",-PI/2,3*PI/2);
//  TF1* fit2 = new TF1("fit2","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x)+2*[7]*cos(7*x)+2*[8]*cos(8*x)+2*[9]*cos(9*x)+2*[10]*cos(10*x)+2*[11]*cos(11*x)+2*[12]*cos(12*x))",-PI/2,3*PI/2);
  TF1* fit1 = new TF1("fit1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x))",-PI/2,3*PI/2);
  TF1* fit2 = new TF1("fit2","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x))",-PI/2,3*PI/2);
  

  h1->Fit("fit1","RNO");
  h2->Fit("fit2","RNO");

//cout<<"v2="<<sqrt(fit2->GetParameter(2)-3*fit1->GetParameter(2)*fit1->GetParameter(0)/fit2->GetParameter(0))<<endl;
//  cout<<"v2="<<sqrt(fit2->GetParameter(2))<<endl;

  TCanvas* c1 = new TCanvas("c1","",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  h1->Draw("PE");
  fit1->Draw("Lsame");
  c1->cd(2);
  h2->Draw("PE");
  fit2->Draw("Lsame");

  TCanvas* c = new TCanvas("c","",550,500);
  h2_zyam->Draw("PE");
  h1_zyam->SetMarkerStyle(24);
  h1_zyam->Scale(1.);
  h1_zyam->Draw("PESAME");

}
*/
