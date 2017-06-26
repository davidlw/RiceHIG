#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void vnn()
{
  TString filename_ref = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_run285479_285549_v6.root";
  TString filename_diff = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pt_run285479_285549_v6.root";

  TH1D* hdphi[100];
  TH1D* hpt[100];
  TF1*  fitfunc[100];

  double detamin=1.9;
  double detamax=4.8; 

  double pt[100]={0};
  double pterr[100]={0};

  double V1[100]={0};
  double V2[100]={0};
  double V3[100]={0};
  double V4[100]={0};
  double V5[100]={0};
  double V6[100]={0};

  double V1err[100]={0};
  double V2err[100]={0};
  double V3err[100]={0};
  double V4err[100]={0};
  double V5err[100]={0};
  double V6err[100]={0};

  double v1[100]={0};
  double v2[100]={0};
  double v3[100]={0};
  double v4[100]={0};
  double v5[100]={0};
  double v6[100]={0};

  double v1err[100]={0};
  double v2err[100]={0};
  double v3err[100]={0};
  double v4err[100]={0};
  double v5err[100]={0};
  double v6err[100]={0};

  for(int i=0;i<23;i++)
  {
//    cout<<filename[i].Data()<<endl;
    hpt[i] = (TH1D*)GetHist(filename[i],"corr_ana_N1851000","ptcorr_trg_0");
    hdphi[i] = (TH1D*)Get1DCFdPhiv3(filename_diff,"corr_ana_N1851000",i,0,detamin,detamax);
    hdphi[i]->SetMarkerStyle(20);
    fitfunc[i] = new TF1(Form("fitfunc_%d",i),"[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x))",0,PI);
    fitfunc[i]->SetLineColor(2);
//    fitfunc[i]->SetParameters(hdphi[i]->GetBinContent(3),0.0,0.06*0.06,0.01*0.01,0.01*0.01);
    hdphi[i]->Fit(Form("fitfunc_%d",i),"RNO");
    hdphi[i]->Fit(Form("fitfunc_%d",i),"RNO");
    hdphi[i]->Fit(Form("fitfunc_%d",i),"RNO");
  
    pt[i]=hpt[i]->GetMean();
    V1[i]=fitfunc[i]->GetParameter(1);
    V2[i]=fitfunc[i]->GetParameter(2);
    V3[i]=fitfunc[i]->GetParameter(3);
    V4[i]=fitfunc[i]->GetParameter(4);
    V5[i]=fitfunc[i]->GetParameter(5);
    V6[i]=fitfunc[i]->GetParameter(6);
    V1err[i]=fitfunc[i]->GetParError(1);
    V2err[i]=fitfunc[i]->GetParError(2);
    V3err[i]=fitfunc[i]->GetParError(3);
    V4err[i]=fitfunc[i]->GetParError(4);
    V5err[i]=fitfunc[i]->GetParError(5);
    V6err[i]=fitfunc[i]->GetParError(6);
    if(V2[i]) v2[i]=sqrt(V2[i]);
    if(V3[i]) v3[i]=sqrt(V3[i]);
    if(V4[i]) v4[i]=sqrt(V4[i]);
    if(V5[i]) v5[i]=sqrt(V5[i]);
    if(V6[i]) v6[i]=sqrt(V6[i]);
    if(V2[i]) v2err[i]=0.5*v2[i]*V2err[i]/V2[i];
    if(V3[i]) v3err[i]=0.5*v3[i]*V3err[i]/V3[i];
    if(V4[i]) v4err[i]=0.5*v4[i]*V4err[i]/V4[i];
    if(V5[i]) v5err[i]=0.5*v5[i]*V5err[i]/V5[i];
    if(V6[i]) v6err[i]=0.5*v6[i]*V6err[i]/V6[i];
  }

  TCanvas* c = new TCanvas("c","c",1200,1200);
  c->Divide(4,4);
  for(int i=10;i<23;i++)
  {
    c->cd(i-9);
    hdphi[i]->Draw("PE");
    fitfunc[i]->Draw("LSAME");
  }  

  int n=23;
  TGraphErrors* gr_V1 = new TGraphErrors(n,nmult,V1,nmulterr,V1err); 
  TGraphErrors* gr_V2 = new TGraphErrors(n,nmult,V2,nmulterr,V2err);
  TGraphErrors* gr_V3 = new TGraphErrors(n,nmult,V3,nmulterr,V3err);
  TGraphErrors* gr_V4 = new TGraphErrors(n,nmult,V4,nmulterr,V4err);
  TGraphErrors* gr_V5 = new TGraphErrors(n,nmult,V5,nmulterr,V5err);
  TGraphErrors* gr_V6 = new TGraphErrors(n,nmult,V6,nmulterr,V6err);

  TGraphErrors* gr_v2 = new TGraphErrors(n,nmult,v2,nmulterr,v2err);
  TGraphErrors* gr_v3 = new TGraphErrors(n,nmult,v3,nmulterr,v3err);
  TGraphErrors* gr_v4 = new TGraphErrors(n,nmult,v4,nmulterr,v4err);
  TGraphErrors* gr_v5 = new TGraphErrors(n,nmult,v5,nmulterr,v5err);
  TGraphErrors* gr_v6 = new TGraphErrors(n,nmult,v6,nmulterr,v6err);

  gr_V1->SetMarkerSize(1.8);
  gr_V2->SetMarkerSize(1.8);
  gr_V3->SetMarkerSize(2.0);
  gr_V4->SetMarkerSize(1.8);
  gr_V5->SetMarkerSize(2.2);
  gr_V6->SetMarkerSize(2.2);

  gr_v2->SetMarkerSize(1.8);
  gr_v3->SetMarkerSize(2.0);
  gr_v4->SetMarkerSize(1.8);
  gr_v5->SetMarkerSize(2.2);
  gr_v6->SetMarkerSize(2.2);

  gr_V1->SetMarkerStyle(24);
  gr_V2->SetMarkerStyle(20);
  gr_V3->SetMarkerStyle(22);
  gr_V4->SetMarkerStyle(21);
  gr_V5->SetMarkerStyle(29);
  gr_V6->SetMarkerStyle(3);

  gr_v2->SetMarkerStyle(20);
  gr_v3->SetMarkerStyle(22);
  gr_v4->SetMarkerStyle(21);
  gr_v5->SetMarkerStyle(29);
  gr_v6->SetMarkerStyle(3);

  gr_V1->SetMarkerColor(1);
  gr_V2->SetMarkerColor(2);
  gr_V3->SetMarkerColor(kGreen+2);
  gr_V4->SetMarkerColor(4);
  gr_V5->SetMarkerColor(6);
  gr_V6->SetMarkerColor(1);

  gr_v2->SetMarkerColor(2);
  gr_v3->SetMarkerColor(kGreen+2);
  gr_v4->SetMarkerColor(4);
  gr_v5->SetMarkerColor(6);
  gr_v6->SetMarkerColor(1);

  TH2D* htmp = new TH2D("htmp",";N_{trk}^{offline};V_{n}(2, |#Delta#eta|>2)",1000,0,500,1000,-0.01,0.01);
  TH2D* htmp1 = new TH2D("htmp1",";N_{trk}^{offline};v_{n}(2, |#Delta#eta|>2)",1000,0,500,1000,0.0,0.082);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetXaxis()->SetTitleOffset(1.2); 
  htmp->GetYaxis()->SetTitleOffset(1.2);
  htmp->GetXaxis()->SetTitleSize(0.05);
  htmp->GetYaxis()->SetTitleSize(0.05);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetXaxis()->SetTitleOffset(1.2);
  htmp1->GetYaxis()->SetTitleOffset(1.2);
  htmp1->GetXaxis()->SetTitleSize(0.05);
  htmp1->GetYaxis()->SetTitleSize(0.05);

  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.1);
  htmp->Draw();
  gr_V1->Draw("PESAME");
  gr_V2->Draw("PESAME");
  gr_V3->Draw("PESAME");
  gr_V4->Draw("PESAME");
  gr_V5->Draw("PESAME");
  gr_V6->Draw("PESAME");

  TCanvas* c2 = new TCanvas("c2","c2",800,600);
  c2->SetLeftMargin(0.15);
  c2->SetBottomMargin(0.15);
  htmp1->Draw();
  gr_v2->Draw("PESAME");
  gr_v3->Draw("PESAME");
  gr_v4->Draw("PESAME");
  gr_v5->Draw("PESAME");
  gr_v6->Draw("PESAME");
  
  TLegend* ll = new TLegend(0.2,0.35,0.37,0.55);
  ll->SetNColumns(2);
  ll->SetBorderSize(0);
  ll->AddEntry(gr_v2,"v_{2}","P");
  ll->AddEntry(gr_v5,"v_{5}","P");
  ll->AddEntry(gr_v3,"v_{3}","P");
  ll->AddEntry(gr_v6,"v_{6}","P");
  ll->AddEntry(gr_v4,"v_{4}","P");
  ll->Draw("P");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->DrawLatex(0.15,0.92,"CMS pPb #sqrt{s_{NN}} = 8.16 TeV, L_{int} = 37.6 nb^{-1}");
  latex->DrawLatex(0.67,0.85,"0.3 < p_{T} < 3 GeV/c");

  c2->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_run285479_285549.gif");
  c2->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_run285479_285549.pdf");
}
