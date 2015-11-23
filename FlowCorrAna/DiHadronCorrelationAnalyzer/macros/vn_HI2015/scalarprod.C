void scalarprod()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_5TeV/merged/scalarprod_v9.root");
  TFile* f_hf = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_5TeV/merged/scalarprod_v9_hf.root");

  TH2D* hsignal_hf = (TH2D*)f_hf->Get("scalarprod_ana_HI_hf/signalcosnsame_pm_trg0_ass0");
  TH2D* hbackground_hf = (TH2D*)f_hf->Get("scalarprod_ana_HI_hf/backgroundcosnsame_pm_trg0_ass0");

  TH1D* hsignal_hf_1D = (TH1D*)hsignal_hf->ProfileY("signal_hf_1D",-1,-1,"i");
  TH1D* hbackground_hf_1D = (TH1D*)hbackground_hf->ProfileY("background_hf_1D",-1,-1,"i");

cout<<hsignal_hf_1D->GetBinContent(1)<<" "<<hbackground_hf_1D->GetBinContent(1)<<endl;
  double V2_ref = hsignal_hf_1D->GetBinContent(1)-hbackground_hf_1D->GetBinContent(1);
  double V3_ref = hsignal_hf_1D->GetBinContent(2)-hbackground_hf_1D->GetBinContent(2);
  double V4_ref = hsignal_hf_1D->GetBinContent(3)-hbackground_hf_1D->GetBinContent(3);
  double V2_ref_err = sqrt(hsignal_hf_1D->GetBinError(1)*hsignal_hf_1D->GetBinError(1)+hbackground_hf_1D->GetBinError(1)*hbackground_hf_1D->GetBinError(1));
  double V3_ref_err = sqrt(hsignal_hf_1D->GetBinError(2)*hsignal_hf_1D->GetBinError(2)+hbackground_hf_1D->GetBinError(2)*hbackground_hf_1D->GetBinError(2));
  double V4_ref_err = sqrt(hsignal_hf_1D->GetBinError(3)*hsignal_hf_1D->GetBinError(3)+hbackground_hf_1D->GetBinError(3)*hbackground_hf_1D->GetBinError(3));

  double v2_ref = sqrt(V2_ref);
  double v3_ref = sqrt(V3_ref);
  double v4_ref = sqrt(V4_ref);

  double v2_ref_err = 0.5*v2_ref*V2_ref_err/V2_ref;
  double v3_ref_err = 0.5*v3_ref*V3_ref_err/V3_ref;
  double v4_ref_err = 0.5*v4_ref*V4_ref_err/V4_ref;

cout<<V2_ref<<" "<<V2_ref_err<<" "<<v2_ref<<" "<<v2_ref_err<<endl;

  TH2D* hpt[30];
  TH2D* hsignal[30];
  TH2D* hbackground[30];
  TH1D* hsignal_1D[30];
  TH1D* hbackground_1D[30];

  double pt[30];
  double pt_err[30]={0};
  double V2[30];
  double V3[30];
  double V4[30];
  double V2_err[30];
  double V3_err[30];
  double V4_err[30];
  double v2[30];
  double v3[30];
  double v4[30];
  double v2_err[30];
  double v3_err[30];
  double v4_err[30];

  for(int i=0;i<13;i++)
  {
    hpt[i] = (TH2D*)f->Get(Form("scalarprod_ana_HI/pt_signal_trg_%d",i));

    hsignal[i] = (TH2D*)f->Get(Form("scalarprod_ana_HI/signalcosnsame_mp_trg%d_ass0",i));
    hbackground[i] = (TH2D*)f->Get(Form("scalarprod_ana_HI/backgroundcosnsame_mp_trg%d_ass0",i));

    hsignal_1D[i] = (TH1D*)hsignal[i]->ProfileY(Form("signal_1D_%d",i),-1,-1,"i");
    hbackground_1D[i] = (TH1D*)hbackground[i]->ProfileY(Form("background_1D_%d",i),-1,-1,"i");    

    pt[i] = hpt[i]->GetMean();
    V2[i] = hsignal_1D[i]->GetBinContent(1)-hbackground_1D[i]->GetBinContent(1);
    V3[i] = hsignal_1D[i]->GetBinContent(2)-hbackground_1D[i]->GetBinContent(2);
    V4[i] = hsignal_1D[i]->GetBinContent(3)-hbackground_1D[i]->GetBinContent(3);
    V2_err[i] = sqrt(hsignal_1D[i]->GetBinError(1)*hsignal_1D[i]->GetBinError(1)+hbackground_1D[i]->GetBinError(1)*hbackground_1D[i]->GetBinError(1));
    V3_err[i] = sqrt(hsignal_1D[i]->GetBinError(2)*hsignal_1D[i]->GetBinError(2)+hbackground_1D[i]->GetBinError(2)*hbackground_1D[i]->GetBinError(2));
    V4_err[i] = sqrt(hsignal_1D[i]->GetBinError(3)*hsignal_1D[i]->GetBinError(3)+hbackground_1D[i]->GetBinError(3)*hbackground_1D[i]->GetBinError(3));

    v2[i] =  V2[i]/v2_ref;
    v3[i] =  V3[i]/v3_ref;
    v4[i] =  V4[i]/v4_ref;
    v2_err[i] = v2[i] * sqrt(v2_ref_err*v2_ref_err/v2_ref/v2_ref+V2_err[i]*V2_err[i]/V2[i]/V2[i]);
    v3_err[i] = v3[i] * sqrt(v3_ref_err*v3_ref_err/v3_ref/v3_ref+V3_err[i]*V3_err[i]/V3[i]/V3[i]);
    v4_err[i] = v4[i] * sqrt(v4_ref_err*v4_ref_err/v4_ref/v4_ref+V4_err[i]*V4_err[i]/V4[i]/V4[i]);   
  }

  TGraphErrors* gr_v2 = new TGraphErrors(13,pt,v2,pt_err,v2_err);
  TGraphErrors* gr_v3 = new TGraphErrors(13,pt,v3,pt_err,v3_err);
  TGraphErrors* gr_v4 = new TGraphErrors(13,pt,v4,pt_err,v4_err);
  gr_v2->SetMarkerStyle(20);
  gr_v3->SetMarkerStyle(20);
  gr_v4->SetMarkerStyle(20);
  gr_v2->SetMarkerColor(2);
  gr_v3->SetMarkerColor(2);
  gr_v4->SetMarkerColor(2);

  TH2D* htmp = new TH2D("htmp",";p_{T} (GeV/c); v_{2}", 1000, 0, 30, 1000, -0.02, 1.0);

  TCanvas* c = new TCanvas("c","c",600,600);
  htmp->Draw();
  gr_v2->Draw("PESAME");

  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  htmp->Draw();
  gr_v3->Draw("PESAME");

  TCanvas* c2 = new TCanvas("c2","c2",600,600);
  htmp->Draw();
  gr_v4->Draw("PESAME");
}
