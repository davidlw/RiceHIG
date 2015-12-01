void scalarprod_centrality()
{
  gStyle->SetOptStat(0);

  TFile* f[10];
  f[0] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_cent010_v4.root");
  f[1] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_cent1020_v4.root");
  f[2] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_cent2030_v4.root");
  f[3] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_cent3040_v4.root");
  f[4] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_cent4050_v4.root");
  f[5] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_cent5060_v4.root");

  TFile* f_hf[10];
  f_hf[0] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_hf_cent010_v4.root");
  f_hf[1] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_hf_cent1020_v4.root");
  f_hf[2] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_hf_cent2030_v4.root");
  f_hf[3] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_hf_cent3040_v4.root");
  f_hf[4] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_hf_cent4050_v4.root");
  f_hf[5] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/FlowVn2015_1M_hf_cent5060_v4.root");

  TGraphErrors* gr_v2[10];
  TGraphErrors* gr_v3[10];
  TGraphErrors* gr_v4[10];
  for(int j=0;j<6;j++)
  {
    TH2D* hsignal_hf = (TH2D*)f_hf[j]->Get("scalarprod_ana_HI_hf/signalcosnsame_pm_trg0_ass0");
    TH2D* hbackground_hf = (TH2D*)f_hf[j]->Get("scalarprod_ana_HI_hf/backgroundcosnsame_pm_trg0_ass0");

    TH1D* hsignal_hf_1D = (TH1D*)hsignal_hf->ProfileY(Form("signal_hf_1D_%d",j),-1,-1,"i");
    TH1D* hbackground_hf_1D = (TH1D*)hbackground_hf->ProfileY(Form("background_hf_1D_%d",j),-1,-1,"i");

    double V2_ref = hsignal_hf_1D->GetBinContent(1);
    double V3_ref = hsignal_hf_1D->GetBinContent(2);
    double V4_ref = hsignal_hf_1D->GetBinContent(3);
    double V2_ref_err = hsignal_hf_1D->GetBinError(1);
    double V3_ref_err = hsignal_hf_1D->GetBinError(2);
    double V4_ref_err = hsignal_hf_1D->GetBinError(3);

    double v2_ref = sqrt(V2_ref);
    double v3_ref = sqrt(V3_ref);
    double v4_ref = sqrt(V4_ref);

    double v2_ref_err = 0.5*v2_ref*V2_ref_err/V2_ref;
    double v3_ref_err = 0.5*v3_ref*V3_ref_err/V3_ref;
    double v4_ref_err = 0.5*v4_ref*V4_ref_err/V4_ref;
/*
    TH2D* hpt[30];
    TH2D* hsignal[30];
    TH2D* hbackground[30];
    TH1D* hsignal_1D[30];
    TH1D* hbackground_1D[30];
*/
    double pt[30]={0};
    double pt_err[30]={0};
    double V2[30]={0};
    double V3[30]={0};
    double V4[30]={0};
    double V2_err[30]={0};
    double V3_err[30]={0};
    double V4_err[30]={0};
    double v2[30]={0};
    double v3[30]={0};
    double v4[30]={0};
    double v2_err[30]={0};
    double v3_err[30]={0};
    double v4_err[30]={0};

    for(int i=0;i<16;i++)
    {
      TH1D* hpt = (TH1D*)f[j]->Get(Form("scalarprod_ana_HI/pt_signal_trg_%d",i));

      TH2D* hsignal = (TH2D*)f[j]->Get(Form("scalarprod_ana_HI/signalcosnsame_pm_trg%d_ass0",i));
//      TH2D* hbackground = (TH2D*)f[j]->Get(Form("scalarprod_ana_HI/backgroundcosnsame_mp_trg%d_ass0",i));
      TH1D* hsignal_1D = (TH1D*)hsignal->ProfileY(Form("signal_1D_%d_%d",i,j),-1,-1,"i");
//      TH1D* hbackground_1D = (TH1D*)hbackground->ProfileY(Form("background_1D_%d",i),-1,-1,"i");    

      pt[i] = hpt->GetMean();
      V2[i] = hsignal_1D->GetBinContent(1);
      V3[i] = hsignal_1D->GetBinContent(2);
      V4[i] = hsignal_1D->GetBinContent(3);

      V2_err[i] = hsignal_1D->GetBinError(1);
      V3_err[i] = hsignal_1D->GetBinError(2);
      V4_err[i] = hsignal_1D->GetBinError(3);

      v2[i] =  V2[i]/v2_ref;
      v3[i] =  V3[i]/v3_ref;
      v4[i] =  V4[i]/v4_ref;
      v2_err[i] = fabs(v2[i]) * sqrt(v2_ref_err*v2_ref_err/v2_ref/v2_ref+V2_err[i]*V2_err[i]/V2[i]/V2[i]);
      v3_err[i] = fabs(v3[i]) * sqrt(v3_ref_err*v3_ref_err/v3_ref/v3_ref+V3_err[i]*V3_err[i]/V3[i]/V3[i]);
      v4_err[i] = fabs(v4[i]) * sqrt(v4_ref_err*v4_ref_err/v4_ref/v4_ref+V4_err[i]*V4_err[i]/V4[i]/V4[i]);   
    }

    gr_v2[j] = new TGraphErrors(16,pt,v2,pt_err,v2_err);
    gr_v3[j] = new TGraphErrors(16,pt,v3,pt_err,v3_err);
    gr_v4[j] = new TGraphErrors(16,pt,v4,pt_err,v4_err);

    gr_v2[j]->SetMarkerStyle(20);
    gr_v3[j]->SetMarkerStyle(20);
    gr_v4[j]->SetMarkerStyle(20);
    gr_v2[j]->SetMarkerColor(2);
    gr_v3[j]->SetMarkerColor(4);
    gr_v4[j]->SetMarkerColor(3);
  }

  TH2D* htmp = new TH2D("htmp",";p_{T} (GeV/c); v_{n}", 1000, 0, 15, 1000, -0.02, 0.25);

  TCanvas* c = new TCanvas("c","c",900,600);
  c->Divide(3,2);
  c->cd(1);
  htmp->Draw();
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  gr_v2[0]->Draw("PESAME");
  gr_v3[0]->Draw("PESAME");
  gr_v4[0]->Draw("PESAME");
  c->cd(2);
  htmp->Draw();
  gr_v2[1]->Draw("PESAME");
  gr_v3[1]->Draw("PESAME");
  gr_v4[1]->Draw("PESAME");
  c->cd(3);
  htmp->Draw();
  gr_v2[2]->Draw("PESAME");
  gr_v3[2]->Draw("PESAME");
  gr_v4[2]->Draw("PESAME");
  c->cd(4);
  htmp->Draw();
  gr_v2[3]->Draw("PESAME");
  gr_v3[3]->Draw("PESAME");
  gr_v4[3]->Draw("PESAME");
  c->cd(5);
  htmp->Draw();
  gr_v2[4]->Draw("PESAME");
  gr_v3[4]->Draw("PESAME");
  gr_v4[4]->Draw("PESAME");
  c->cd(6);
  htmp->Draw();
  gr_v2[5]->Draw("PESAME");
  gr_v3[5]->Draw("PESAME");
  gr_v4[5]->Draw("PESAME");
}
