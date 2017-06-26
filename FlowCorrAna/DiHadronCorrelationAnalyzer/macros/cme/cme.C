void cme(TString filename, TH1D* h[8], TString type = "HI")
{
//  TH1D* h[8];

  TFile* f = new TFile(filename.Data());

  TH2D* hsame_bak = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos_same_bak",type.Data()));
  TH2D* hdiff_bak = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos_diff_bak",type.Data()));
  TH2D* hsame_for = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos_same_for",type.Data()));
  TH2D* hdiff_for = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos_diff_for",type.Data()));

  TH2D* hsame_2pcorrp = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos2pcorrp_same",type.Data()));
  TH2D* hsame_2pcorrm = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos2pcorrm_same",type.Data()));
  TH2D* hdiff_2pcorrp = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos2pcorrp_diff",type.Data()));
  TH2D* hdiff_2pcorrm = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalcos2pcorrm_diff",type.Data()));

  TH2D* hsame_npairs = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalnpairs_same",type.Data()));
  TH2D* hdiff_npairs = (TH2D*)f->Get(Form("chargedepcorr_ana_%s/signalnpairs_diff",type.Data()));

  TH2D* hsame = (TH2D*)hsame_bak->Clone("hsame");
  hsame->Add(hsame_for);
  TH2D* hdiff = (TH2D*)hdiff_bak->Clone("hsame");
  hdiff->Add(hdiff_for);

  TH1D* hq2 = (TH1D*)f->Get(Form("chargedepcorr_ana_%s/q2asscos",type.Data()));

  TH1D* hsame_2pcorrp_prof = (TH1D*)hsame_2pcorrp->ProfileY("hsame_2pcorrp_prof",-1,-1,"e");
  TH1D* hsame_2pcorrm_prof = (TH1D*)hsame_2pcorrm->ProfileY("hsame_2pcorrm_prof",-1,-1,"e");
  TH1D* hdiff_2pcorrp_prof = (TH1D*)hdiff_2pcorrp->ProfileY("hdiff_2pcorrp_prof",-1,-1,"e");
  TH1D* hdiff_2pcorrm_prof = (TH1D*)hdiff_2pcorrm->ProfileY("hdiff_2pcorrm_prof",-1,-1,"e");

  TH1D* hsame_proj_for = (TH1D*)hsame_for->ProjectionY("hsame_proj_for",-1,-1,"e");
  TH1D* hdiff_proj_for = (TH1D*)hdiff_for->ProjectionY("hdiff_proj_for",-1,-1,"e");
  hsame_proj_for->Reset();
  hdiff_proj_for->Reset();

  TH1D* hsame_proj_bak = (TH1D*)hsame_bak->ProjectionY("hsame_proj_bak",-1,-1,"e");
  TH1D* hdiff_proj_bak = (TH1D*)hdiff_bak->ProjectionY("hdiff_proj_bak",-1,-1,"e");
  hsame_proj_bak->Reset();
  hdiff_proj_bak->Reset();
 
  TH1D* hsame_proj = (TH1D*)hsame->ProjectionY("hsame_proj",-1,-1,"e");
  TH1D* hdiff_proj = (TH1D*)hdiff->ProjectionY("hdiff_proj",-1,-1,"e");
  hsame_proj->Reset();
  hdiff_proj->Reset();

  TH1D* hsame_npairs_proj = (TH1D*)hsame_npairs->ProjectionY("hsame_npairs_proj",-1,-1,"e");
  TH1D* hdiff_npairs_proj = (TH1D*)hdiff_npairs->ProjectionY("hdiff_npairs_proj",-1,-1,"e");

  TH1D* hsame_2pcorrp_proj = (TH1D*)hsame_2pcorrp->ProjectionY("hsame_2pcorrp_proj",-1,-1,"e");
  TH1D* hsame_2pcorrm_proj = (TH1D*)hsame_2pcorrm->ProjectionY("hsame_2pcorrm_proj",-1,-1,"e");
  TH1D* hdiff_2pcorrp_proj = (TH1D*)hdiff_2pcorrp->ProjectionY("hdiff_2pcorrp_proj",-1,-1,"e");
  TH1D* hdiff_2pcorrm_proj = (TH1D*)hdiff_2pcorrm->ProjectionY("hdiff_2pcorrm_proj",-1,-1,"e");
  hsame_2pcorrp_proj->Reset();
  hsame_2pcorrm_proj->Reset();
  hdiff_2pcorrp_proj->Reset();
  hdiff_2pcorrm_proj->Reset();
  
  for(int i=1;i<=hsame_proj_for->GetNbinsX();i++)
  {
    TH1D* hsame_proj_2pcorrp_tmp = (TH1D*)hsame_2pcorrp->ProjectionX("hsame_2pcorrp_tmp",i,i,"e");
    TH1D* hdiff_proj_2pcorrp_tmp = (TH1D*)hdiff_2pcorrp->ProjectionX("hdiff_2pcorrp_tmp",i,i,"e");
    TH1D* hsame_proj_2pcorrm_tmp = (TH1D*)hsame_2pcorrm->ProjectionX("hsame_2pcorrm_tmp",i,i,"e");
    TH1D* hdiff_proj_2pcorrm_tmp = (TH1D*)hdiff_2pcorrm->ProjectionX("hdiff_2pcorrm_tmp",i,i,"e");
    hsame_2pcorrp_proj->SetBinContent(i,hsame_proj_2pcorrp_tmp->GetMean());
    hsame_2pcorrm_proj->SetBinContent(i,hsame_proj_2pcorrm_tmp->GetMean());
    hdiff_2pcorrp_proj->SetBinContent(i,hdiff_proj_2pcorrp_tmp->GetMean());
    hdiff_2pcorrm_proj->SetBinContent(i,hdiff_proj_2pcorrm_tmp->GetMean());
    hsame_2pcorrp_proj->SetBinError(i,hsame_proj_2pcorrp_tmp->GetMeanError());
    hsame_2pcorrm_proj->SetBinError(i,hsame_proj_2pcorrp_tmp->GetMeanError());
    hdiff_2pcorrp_proj->SetBinError(i,hsame_proj_2pcorrp_tmp->GetMeanError());
    hdiff_2pcorrm_proj->SetBinError(i,hsame_proj_2pcorrp_tmp->GetMeanError());
//cout<<hsame_proj_2pcorrm_tmp->GetMean()<<endl;

    TH1D* hsame_proj_for_tmp = (TH1D*)hsame_for->ProjectionX("hsame_proj_for_tmp",i,i,"e");
    TH1D* hdiff_proj_for_tmp = (TH1D*)hdiff_for->ProjectionX("hdiff_proj_for_tmp",i,i,"e");

    double value = hsame_proj_for_tmp->GetMean()/sqrt(hq2->GetMean());
    double value_err = hsame_proj_for_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hsame_proj_for->SetBinContent(i,value);
    hsame_proj_for->SetBinError(i,value_err);

    value = hdiff_proj_for_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hdiff_proj_for_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hdiff_proj_for->SetBinContent(i,value);
    hdiff_proj_for->SetBinError(i,value_err);

    TH1D* hsame_proj_bak_tmp = (TH1D*)hsame_bak->ProjectionX("hsame_proj_bak_tmp",i,i,"e");
    TH1D* hdiff_proj_bak_tmp = (TH1D*)hdiff_bak->ProjectionX("hdiff_proj_bak_tmp",i,i,"e");

    value = hsame_proj_bak_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hsame_proj_bak_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hsame_proj_bak->SetBinContent(i,value);
    hsame_proj_bak->SetBinError(i,value_err);

    value = hdiff_proj_bak_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hdiff_proj_bak_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hdiff_proj_bak->SetBinContent(i,value);
    hdiff_proj_bak->SetBinError(i,value_err);

    TH1D* hsame_proj_tmp = (TH1D*)hsame->ProjectionX("hsame_proj_tmp",i,i,"e");
    TH1D* hdiff_proj_tmp = (TH1D*)hdiff->ProjectionX("hdiff_proj_tmp",i,i,"e");

    value = hsame_proj_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hsame_proj_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hsame_proj->SetBinContent(i,value);
    hsame_proj->SetBinError(i,value_err);

    value = hdiff_proj_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hdiff_proj_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hdiff_proj->SetBinContent(i,value);
    hdiff_proj->SetBinError(i,value_err);
  }
 
  h[0] = hsame_proj;
  h[1] = hdiff_proj;
  h[2] = hsame_2pcorrp_proj;
  h[3] = hsame_2pcorrm_proj;
  h[4] = hdiff_2pcorrp_proj;
  h[5] = hdiff_2pcorrm_proj;
  h[6] = hsame_npairs_proj;
  h[7] = hdiff_npairs_proj;

  delete hsame_bak;
  delete hdiff_bak;
  delete hsame_for;
  delete hdiff_for;
  delete hsame;
  delete hdiff;
  delete hsame_npairs;
  delete hdiff_npairs;
  delete hsame_2pcorrp;
  delete hsame_2pcorrm;
  delete hdiff_2pcorrp;
  delete hdiff_2pcorrm;
}

void compare_centrality()
{
  TString filename[10];
  filename[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent002_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[1] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent05_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[2] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent510_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[3] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent1020_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[4] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent2030_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[5] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent3040_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[6] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[7] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent5060_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[8] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent6070_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";
  filename[9] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent7080_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v45.root";

  TH1D* h[10][8];
  double cos_same[10];
  double cos_diff[10];
  double pcorrp_same[10];
  double pcorrm_same[10];
  double pcorrp_diff[10];
  double pcorrm_diff[10];
  double cos_same_err[10];
  double cos_diff_err[10];
  double pcorrp_same_err[10];
  double pcorrm_same_err[10];
  double pcorrp_diff_err[10];
  double pcorrm_diff_err[10];
  double cent[10] = {0.01,2.5,7.5,15,25,35,45,55,65,75};
  double cent_err[10] = {0};

  for(int i=0;i<10;i++)
  {
    cme(filename[i],h[i]);

    h[i][0]->Multiply(h[i][6]);
    h[i][2]->Multiply(h[i][6]);
    h[i][3]->Multiply(h[i][6]);
    h[i][1]->Multiply(h[i][7]);
    h[i][4]->Multiply(h[i][7]);
    h[i][5]->Multiply(h[i][7]);
    
    double xmin = h[i][0]->FindBin(0.1);
    double xmax = h[i][0]->FindBin(1.6);
    cos_same[i] = h[i][0]->IntegralAndError(xmin,xmax,cos_same_err[i])/h[i][6]->Integral(xmin,xmax);
    cos_diff[i] = h[i][1]->IntegralAndError(xmin,xmax,cos_diff_err[i])/h[i][7]->Integral(xmin,xmax);
    pcorrp_same[i] = h[i][2]->IntegralAndError(xmin,xmax,pcorrp_same_err[i])/h[i][6]->Integral(xmin,xmax);
    pcorrp_diff[i] = h[i][4]->IntegralAndError(xmin,xmax,pcorrp_diff_err[i])/h[i][7]->Integral(xmin,xmax);
    pcorrm_same[i] = h[i][3]->IntegralAndError(xmin,xmax,pcorrm_same_err[i])/h[i][6]->Integral(xmin,xmax);
    pcorrm_diff[i] = h[i][5]->IntegralAndError(xmin,xmax,pcorrm_diff_err[i])/h[i][7]->Integral(xmin,xmax);
//cout<<pcorrm_same[i]<<endl;
    cos_same_err[i] /= h[i][6]->Integral(xmin,xmax); 
    cos_diff_err[i] /= h[i][7]->Integral(xmin,xmax);
    pcorrp_same_err[i] /= h[i][6]->Integral(xmin,xmax);
    pcorrp_diff_err[i] /= h[i][7]->Integral(xmin,xmax);
    pcorrm_same_err[i] /= h[i][6]->Integral(xmin,xmax);
    pcorrm_diff_err[i] /= h[i][7]->Integral(xmin,xmax);
  }

  TGraphErrors* gr_cos_same = new TGraphErrors(10,cent,cos_same,cent_err,cos_same_err); 
  TGraphErrors* gr_cos_diff = new TGraphErrors(10,cent,cos_diff,cent_err,cos_diff_err); 
  TGraphErrors* gr_2pcorrp_same = new TGraphErrors(10,cent,pcorrp_same,cent_err,pcorrp_same_err); 
  TGraphErrors* gr_2pcorrm_same = new TGraphErrors(10,cent,pcorrm_same,cent_err,pcorrm_same_err);
  TGraphErrors* gr_2pcorrp_diff = new TGraphErrors(10,cent,pcorrp_diff,cent_err,pcorrp_diff_err);
  TGraphErrors* gr_2pcorrm_diff = new TGraphErrors(10,cent,pcorrm_diff,cent_err,pcorrm_diff_err);

  double cent_alice[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double cent_alice_err[9] = {0};
  double q3diff_alice[9] = {0.0,-1.0E-6,-1.4E-5,-2.5E-5,-6.4E-5,-2.6E-5,1.08E-4,3.15E-4,9.89E-4};
  double q3diff_alice_err[9] = {+4.0E-6,+6.0E-6,+9.0E-6,+1.4E-5,+2.3E-5,+4.1E-5,+8.0E-5,+1.22E-4,+2.17E-4};
  double q3same_alice[9] = {0.0,-1.0E-5,-4.6E-5,-9.8E-5,-1.47E-4,-2.48E-4,-3.66E-4,-3.7E-4,-3.93E-4};
  double q3same_alice_err[9] = {+4.0E-6,+6.0E-6,+9.0E-6,+1.4E-5,+2.4E-5,+4.1E-5,+8.1E-5,+1.77E-4,+3.77E-4};
  TGraphErrors* gr_same_alice = new TGraphErrors(9,cent_alice,q3same_alice,cent_alice_err,q3same_alice_err);
  TGraphErrors* gr_diff_alice = new TGraphErrors(9,cent_alice,q3diff_alice,cent_alice_err,q3diff_alice_err);
  gr_same_alice->SetMarkerStyle(34);
  gr_diff_alice->SetMarkerStyle(28);

  TH2D* htmp = new TH2D("tmp","",1000,0.0,100,1000,-0.001,0.0005);
  TH2D* htmp1 = new TH2D("tmp1","",1000,0.0,100,1000,-0.0005,0.0002);
  TH2D* htmp2 = new TH2D("tmp2","",1000,0.0,100,1000,-0.0015,0.005);

  TCanvas* c = new TCanvas("c","c",1200,400);
  c->Divide(3,1);
  c->cd(1);
  htmp->Draw();
  gr_cos_same->SetMarkerStyle(20);
  gr_cos_diff->SetMarkerStyle(24);
  gr_cos_same->Draw("PESAME");
  gr_cos_diff->Draw("PESAME");
  gr_same_alice->Draw("PESAME");
  gr_diff_alice->Draw("PESAME");
  c->cd(2);
  htmp1->Draw();
  gr_2pcorrp_same->SetMarkerStyle(20);
  gr_2pcorrp_diff->SetMarkerStyle(24);
  gr_2pcorrp_same->Draw("PESAME");
  gr_2pcorrp_diff->Draw("PESAME");
  c->cd(3);
  htmp2->Draw();
  gr_2pcorrm_same->SetMarkerStyle(20);
  gr_2pcorrm_diff->SetMarkerStyle(24);
  gr_2pcorrm_same->Draw("PESAME");
  gr_2pcorrm_diff->Draw("PESAME");
}

void compare()
{
  TString filename("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent3040_pttrg033_ptassallweight_etaass445_eff1_zvtx1_bin01_v45.root");
//    TString filename("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_n150185_pttrg033_ptassallweight_etaass445_all_eff1_zvtx1_bin01_v13.root");

  TH1D* h[10];
  cme(filename,h,"HI");

  TH2D* htmp = new TH2D("tmp","",1000,0.1,4.8,1000,-0.001*3,0.0005*3);
  TH2D* htmp1 = new TH2D("tmp1","",1000,0.1,4.8,1000,-0.0005*3,0.0002*3);
  TH2D* htmp2 = new TH2D("tmp2","",1000,0.1,4.8,1000,-0.0015*3,0.005*3);

  TCanvas* c = new TCanvas("c","c",1200,400);
  c->Divide(3,1);
  c->cd(1);
  htmp->Draw();
  h[0]->SetMarkerStyle(20);
  h[0]->Draw("PESAME");
  h[1]->SetMarkerStyle(24);
  h[1]->Draw("PESAME");
  c->cd(2);
  htmp1->Draw();
  h[2]->SetMarkerStyle(20);
  h[2]->Draw("PESAME");
  h[4]->SetMarkerStyle(24);
  h[4]->Draw("PESAME");
  c->cd(3);
  htmp2->Draw();
  h[3]->SetMarkerStyle(20);
  h[3]->Draw("PESAME");
  h[5]->SetMarkerStyle(24);
  h[5]->Draw("PESAME");
}
