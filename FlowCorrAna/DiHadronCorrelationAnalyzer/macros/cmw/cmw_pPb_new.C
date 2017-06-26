#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"

void cmw_pPb_new()
{ 
  TString filename[12];
//  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chasymdihadroncorrelation_pPb_n185220_all_eff_v5.root");
//  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/chasymdihadroncorrelation_n185220_pprereco_eff_v4.root");
  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/chasymdihadroncorrelation_cent3040_pprereco_eff_v4.root");

  TH2D* h_pos[20];
  TH2D* hback_pos[20];
  TH1D* h1D_pos[20];
  TH1D* h1Dback_pos[20];
  TF1*  fit_pos[20];
  double v2_pos[20];
  double v3_pos[20];
  double v4_pos[20];
  double v2err_pos[20];
  double v3err_pos[20];
  double v4err_pos[20];

  TH2D* h_neg[20];
  TH2D* hback_neg[20];
  TH1D* h1D_neg[20];
  TH1D* h1Dback_neg[20];
  TF1*  fit_neg[20];
  double v2_neg[20];
  double v3_neg[20];
  double v4_neg[20];
  double v2err_neg[20];
  double v3err_neg[20];
  double v4err_neg[20];

  double v2diff[20];
  double v3diff[20];
  double v2diff_err[20];
  double v3diff_err[20];

  double chasymbin[]={-1.,-0.09,-0.055,-0.03,-0.01,0.01,0.03,0.055,0.09,1.};
  double chasym[20];
  double chasymerr[20]={0};
//  TH1D* hchasym = (TH1D*)GetHist(filename[0].Data(),"corr_ana_pPb_pos","multchargeasym");
  TH1D* hchasym = (TH1D*)GetHist(filename[0].Data(),"corr_ana_PbPb_pos","multchargeasym");

  for(int i=0;i<9;i++)
  {
    hchasym->SetAxisRange(chasymbin[i],chasymbin[i+1],"X");
    chasym[i] = hchasym->GetMean();
  }

  for(int i=0;i<9;i++)
  {
    h_pos[i] = (TH2D*)GetHist(filename[0].Data(),"corr_ana_PbPb_pos",Form("signal_chasym%d",i));
    int xmin = h_pos[i]->GetXaxis()->FindBin(1.9);
    int xmax = h_pos[i]->GetXaxis()->FindBin(6.0);
    h1D_pos[i] = h_pos[i]->ProjectionY(Form("signal_1D_chasym%d",i),xmin,xmax,"e");

    hback_pos[i] = (TH2D*)GetHist(filename[0].Data(),"corr_ana_PbPb_pos",Form("background_chasym%d",i));
    h1Dback_pos[i] = hback_pos[i]->ProjectionY(Form("background_1D_chasym%d",i),xmin,xmax,"e");

    h1D_pos[i]->Divide(h1Dback_pos[i]);

    fit_pos[i] = new TF1(Form("fit_pos_%d",i),"[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x))",-PI/2,3*PI/2);
    h1D_pos[i]->Fit(Form("fit_pos_%d",i),"RNO");
    v2_pos[i] = sqrt(fit_pos[i]->GetParameter(2)); 
    v3_pos[i] = sqrt(fit_pos[i]->GetParameter(3));
    v4_pos[i] = sqrt(fit_pos[i]->GetParameter(4));
    v2err_pos[i] = 0.5*fit_pos[i]->GetParError(2)/fit_pos[i]->GetParameter(2)*v2_pos[i];
    v3err_pos[i] = 0.5*fit_pos[i]->GetParError(3)/fit_pos[i]->GetParameter(3)*v3_pos[i];
    v4err_pos[i] = 0.5*fit_pos[i]->GetParError(4)/fit_pos[i]->GetParameter(4)*v4_pos[i];


    h_neg[i] = (TH2D*)GetHist(filename[0].Data(),"corr_ana_PbPb_neg",Form("signal_chasym%d",i));
    int xmin = h_neg[i]->GetXaxis()->FindBin(1.9);
    int xmax = h_neg[i]->GetXaxis()->FindBin(6.0);
    h1D_neg[i] = h_neg[i]->ProjectionY(Form("signal_1D_chasym%d",i),xmin,xmax,"e");

    hback_neg[i] = (TH2D*)GetHist(filename[0].Data(),"corr_ana_PbPb_neg",Form("background_chasym%d",i));
    h1Dback_neg[i] = hback_neg[i]->ProjectionY(Form("background_1D_chasym%d",i),xmin,xmax,"e");

    h1D_neg[i]->Divide(h1Dback_neg[i]);

    fit_neg[i] = new TF1(Form("fit_neg_%d",i),"[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x))",-PI/2,3*PI/2);
    h1D_neg[i]->Fit(Form("fit_neg_%d",i),"RNO");
    v2_neg[i] = sqrt(fit_neg[i]->GetParameter(2));
    v3_neg[i] = sqrt(fit_neg[i]->GetParameter(3));
    v4_neg[i] = sqrt(fit_neg[i]->GetParameter(4));
    v2err_neg[i] = 0.5*fit_neg[i]->GetParError(2)/fit_neg[i]->GetParameter(2)*v2_neg[i];
    v3err_neg[i] = 0.5*fit_neg[i]->GetParError(3)/fit_neg[i]->GetParameter(3)*v3_neg[i];
    v4err_neg[i] = 0.5*fit_neg[i]->GetParError(4)/fit_neg[i]->GetParameter(4)*v4_neg[i];

    v2diff_err[i] = 2*v2_pos[i]/v2_neg[i]*sqrt((v2err_neg[i]/v2_neg[i])*(v2err_neg[i]/v2_neg[i])+(v2err_pos[i]/v2_pos[i])*(v2err_pos[i]/v2_pos[i]))/(1+v2_pos[i]/v2_neg[i])/(1+v2_pos[i]/v2_neg[i]);
    v3diff_err[i] = 2*v3_pos[i]/v3_neg[i]*sqrt((v3err_neg[i]/v3_neg[i])*(v3err_neg[i]/v3_neg[i])+(v3err_pos[i]/v3_pos[i])*(v3err_pos[i]/v3_pos[i]))/(1+v3_pos[i]/v3_neg[i])/(1+v3_pos[i]/v3_neg[i]);
    v2diff[i] = (v2_neg[i] - v2_pos[i])/(v2_neg[i] + v2_pos[i]);
    v3diff[i] = (v3_neg[i] - v3_pos[i])/(v3_neg[i] + v3_pos[i]);    
  }
 
  TGraphErrors* gr_v2vschasym_pos = new TGraphErrors(9,chasym,v2_pos,chasymerr,v2err_pos);
  TGraphErrors* gr_v3vschasym_pos = new TGraphErrors(9,chasym,v3_pos,chasymerr,v3err_pos);

  TGraphErrors* gr_v2vschasym_neg = new TGraphErrors(9,chasym,v2_neg,chasymerr,v2err_neg);
  TGraphErrors* gr_v3vschasym_neg = new TGraphErrors(9,chasym,v3_neg,chasymerr,v3err_neg);

  gr_v2vschasym_neg->SetMarkerStyle(24);
  gr_v3vschasym_neg->SetMarkerStyle(24);

  TGraphErrors* gr_v2vschasym_diff = new TGraphErrors(9,chasym,v2diff,chasymerr,v2diff_err);
  TGraphErrors* gr_v3vschasym_diff = new TGraphErrors(9,chasym,v3diff,chasymerr,v3diff_err);

  TH2D* htmp = new TH2D("tmp",";A_{ch};v_{2}",100,-0.2,0.2,100,0.065,0.072);
  TH2D* htmp1 = new TH2D("tmp1",";A_{ch};v_{3}",100,-0.2,0.2,100,0.019,0.024);
  TH2D* htmp2 = new TH2D("tmp2",";A_{ch};(v^{-}_{2}-v^{+}_{2})/(v^{-}_{2}+v^{+}_{2})",100,-0.15,0.15,100,-0.03,0.03);
  TH2D* htmp3 = new TH2D("tmp3",";A_{ch};(v^{-}_{3}-v^{+}_{3})/(v^{-}_{3}+v^{+}_{3})",100,-0.15,0.15,100,-0.045,0.045);

  TCanvas* c = new TCanvas("c","",800,400); 
  c->Divide(2,1);
  c->cd(1);
  htmp->Draw();
  gr_v2vschasym_pos->Draw("PESAME");
  gr_v2vschasym_neg->Draw("PESAME");
  c->cd(2);
  htmp2->Draw();
  gr_v2vschasym_diff->Draw("PESAME");

  TF1* func = new TF1("func","[0]+[1]*x",-0.12,0.12);
  func->SetParameters(0.0,-0.15);
  gr_v2vschasym_diff->Fit("func","RNO");
  gr_v2vschasym_diff->Fit("func","RNO");
  gr_v2vschasym_diff->Fit("func","RNO");
  func->SetLineColor(2);
  func->Draw("Lsame");

  TCanvas* c1 = new TCanvas("c1","",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  htmp1->Draw();
  gr_v3vschasym_pos->Draw("PESAME");
  gr_v3vschasym_neg->Draw("PESAME");
  c1->cd(2);
  htmp3->Draw();
  gr_v3vschasym_diff->Draw("PESAME");

  TF1* func1 = new TF1("func1","[0]+[1]*x",-0.12,0.12);
  func1->SetParameters(0.0,-0.15);
  gr_v3vschasym_diff->Fit("func1","RNO");
  gr_v3vschasym_diff->Fit("func1","RNO");
  gr_v3vschasym_diff->Fit("func1","RNO");
  func1->SetLineColor(2);
  func1->Draw("Lsame");
}
