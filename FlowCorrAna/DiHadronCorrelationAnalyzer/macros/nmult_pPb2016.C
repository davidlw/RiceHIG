void nmult_pPb2016()
{
  TFile* f[10];
  f[0] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_mb_pPb_Golden_dz01_v1.root");
  f[1] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_mb_pPb5TeV_Golden_dz01_v1.root");

  TH1D* hmult[10];
  hmult[0] = (TH1D*)f[0]->Get("corr_ana/multrawall");
  hmult[1] = (TH1D*)f[1]->Get("corr_ana/multrawall");

  hmult[0]->Scale(1.0/hmult[0]->Integral("width"));
  hmult[1]->Scale(1.0/hmult[1]->Integral("width"));

  hmult[0]->SetMarkerStyle(20);
  hmult[1]->SetMarkerStyle(24);
  hmult[0]->SetMarkerColor(2);
  hmult[1]->SetMarkerColor(1);

  TH1D* htmp = (TH1D*)hmult[0]->Clone("htmp");
  htmp->Reset();

  TH1D* hratio = (TH1D*)hmult[0]->Clone("hratio");
  hratio->Divide(hmult[1]);
 
  TCanvas* c = new TCanvas("c","",550,500);
  c->SetLogy();
  htmp->SetAxisRange(0,450,"X");
  htmp->SetAxisRange(0.000000000001,0.1,"Y");
  htmp->Draw();
  hmult[0]->Draw("PESAME");
  hmult[1]->Draw("PESAME");

  TCanvas* c1 = new TCanvas("c1","",550,500);
  hratio->Draw("PE");
}
