#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void vnpt_PbPb()
{
  TString filename[100];
  TString dirname[100];

  filename[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_hireco_cent5060_v1.root";
  dirname[0] = "corr_ana_HI";

  TH1D* hdphi[100];
  TH1D* hpt[100];
  TF1*  fitfunc[100];

  double detamin=2.0;
  double detamax=1000; 

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

//  double factor[]={1,1.0,1.01,1.,0.997,1.0,1.002,1.016,1.016,1.03,1.045,1.04,1.03,1.04,1.02,0.97,0.93,0.97}; //20-30%
//  double factor[]={1,1.0,1.0070,1.003,0.997,0.997,1.002,1.016,1.016,1.03,1.045,1.037,1.03,1.04,1.02,0.97,0.955,1.015}; //30-50%
  double factor[]={1,1.04,0.988,0.985,1.018,1.02,1.027,1.021,1.021,1.062,1.072,1.035,1.005,1.035,1.07,0.939,1.16,1.44}; //50-60%
//  double factor[18]={1.0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

  double v1err[100]={0};
  double v2err[100]={0};
  double v3err[100]={0};
  double v4err[100]={0};
  double v5err[100]={0};
  double v6err[100]={0};

  double v4_milan[] = {0,0.00324273,0.00528383,0.00830817,0.0127294,0.019824,0.02699,0.0358164,0.0461142,0.0584547,0.0650077,0.0644619,0.0611876,0.053306,0.0466994,0.047166,0.0459417,0.0392819}; //50-60%
  double v4err_milan[] = {0,0.000243533,0.000226065,0.000224949,0.000169739,0.000194471,0.000210642,0.000267085,0.000256204,0.000439093,0.000699032,0.00103848,0.00149301,0.00166137,0.00283724,0.00440172,0.00627881,0.00681012}; //50-60%
//  double v4_milan[] = {0,0.003554,0.0057791,0.00839311,0.0128269,0.0196126,0.0271964,0.0357815,0.0471324,0.0625146,0.0726572,0.0767031,0.0750238,0.0654631,0.0499494,0.0362287,0.031624,0.0265319}; //30-50%
//  double v4err_milan[] = {0,6.07481e-05,5.61622e-05,5.55401e-05,4.15041e-05,4.69676e-05,5.04324e-05,6.3337e-05,6.06986e-05,0.000103892,0.000167009,0.000252605,0.000371536,0.000425767,0.000749573,0.00116826,0.00167556,0.00181511}; //30-50%
//  double v4_milan[] = {0,0.00342448,0.00511806,0.00736033 ,0.0113032,0.0171354 ,0.0241684,0.0319507,0.0426139,0.0584379,0.0712356,0.0777991,0.0780295,0.069245,0.0501373,0.038857,0.0311799,0.0246278}; // 20-30%
//  double v4err_milan[] = {0,6.0672e-05,5.65409e-05,5.58919e-05,4.15978e-05,4.68139e-05,4.99226e-05,6.24131e-05,5.95981e-05,0.000102725,0.000166782,0.000256339,0.000384486,0.00045238,0.000819445,0.00129668,0.00186359,0.00199894}; //20-30%

  double v4_ratio[100]={0};
  double v4err_ratio[100]={0};

  for(int i=0;i<18;i++)
  {
    hpt[i] = (TH1D*)GetHist(filename[0],dirname[0],Form("ptcorr_signal_trg_%d",i));
    hdphi[i] = (TH1D*)Get1DCFdPhiv3(filename[0].Data(),dirname[0],i,0,detamin,detamax);
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

    if(i==0)
    {
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
    else
    {
      if(v2[0]) v2[i]=V2[i]/v2[0];
      if(v3[0]) v3[i]=V3[i]/v3[0];
      if(v4[0]) 
      { 
        v4[i]=V4[i]/v4[0]*factor[i];;
        v4_ratio[i]=v4[i]/v4_milan[i];
      }
      if(v5[0]) v5[i]=V5[i]/v5[0];
      if(v6[0]) v6[i]=V6[i]/v6[0];
      if(v2[0]) v2err[i]=v2[i]*sqrt(V2err[i]*V2err[i]/V2[i]/V2[i]+v2err[0]*v2err[0]/v2[0]/v2[0]);
      if(v3[0]) v3err[i]=v3[i]*sqrt(V3err[i]*V3err[i]/V3[i]/V3[i]+v3err[0]*v3err[0]/v3[0]/v3[0]);
      if(v4[0])
      {
        v4err[i]=v4[i]*sqrt(V4err[i]*V4err[i]/V4[i]/V4[i]+v4err[0]*v4err[0]/v4[0]/v4[0]);
        v4err_ratio[i]=v4_ratio[i]*v4err[i]/v4[i];
      }
      if(v5[0]) v5err[i]=v5[i]*sqrt(V5err[i]*V5err[i]/V5[i]/V5[i]+v5err[0]*v5err[0]/v5[0]/v5[0]);
      if(v6[0]) v6err[i]=v6[i]*sqrt(V6err[i]*V6err[i]/V6[i]/V6[i]+v6err[0]*v6err[0]/v6[0]/v6[0]);
    }   
  }
/*
  TCanvas* c = new TCanvas("c","c",1200,1200);
  c->Divide(4,4);
  for(int i=10;i<23;i++)
  {
    c->cd(i-9);
    hdphi[i]->Draw("PE");
    fitfunc[i]->Draw("LSAME");
  }  
*/
  int n=18;
  TGraphErrors* gr_V1 = new TGraphErrors(n,pt,V1,pterr,V1err); 
  TGraphErrors* gr_V2 = new TGraphErrors(n,pt,V2,pterr,V2err);
  TGraphErrors* gr_V3 = new TGraphErrors(n,pt,V3,pterr,V3err);
  TGraphErrors* gr_V4 = new TGraphErrors(n,pt,V4,pterr,V4err);
  TGraphErrors* gr_V5 = new TGraphErrors(n,pt,V5,pterr,V5err);
  TGraphErrors* gr_V6 = new TGraphErrors(n,pt,V6,pterr,V6err);

  TGraphErrors* gr_v2 = new TGraphErrors(n,pt,v2,pterr,v2err);
  TGraphErrors* gr_v3 = new TGraphErrors(n,pt,v3,pterr,v3err);
  TGraphErrors* gr_v4 = new TGraphErrors(n,pt,v4,pterr,v4err);
  TGraphErrors* gr_v5 = new TGraphErrors(n,pt,v5,pterr,v5err);
  TGraphErrors* gr_v6 = new TGraphErrors(n,pt,v6,pterr,v6err);

  TGraphErrors* gr_v4_milan = new TGraphErrors(n,pt,v4_milan,pterr,v4err_milan);
  TGraphErrors* gr_v4_ratio = new TGraphErrors(n,pt,v4_ratio,pterr,v4err_ratio);

  gr_V1->RemovePoint(0);
  gr_V2->RemovePoint(0);
  gr_V3->RemovePoint(0);
  gr_V4->RemovePoint(0);
  gr_V5->RemovePoint(0);
  gr_V6->RemovePoint(0);
  gr_v2->RemovePoint(0);
  gr_v3->RemovePoint(0);
  gr_v4->RemovePoint(0);
  gr_v4_milan->RemovePoint(0);
  gr_v4_ratio->RemovePoint(0);
  gr_v5->RemovePoint(0);
  gr_v6->RemovePoint(0);

  gr_V1->SetMarkerSize(1.8);
  gr_V2->SetMarkerSize(1.8);
  gr_V3->SetMarkerSize(2.0);
  gr_V4->SetMarkerSize(1.8);
  gr_V5->SetMarkerSize(2.4);
  gr_V6->SetMarkerSize(2.);

  gr_v2->SetMarkerSize(1.8);
  gr_v3->SetMarkerSize(2.0);
  gr_v4->SetMarkerSize(1.8);
  gr_v4_milan->SetMarkerSize(1.8);
  gr_v4_ratio->SetMarkerSize(1.8);
  gr_v5->SetMarkerSize(2.4);
  gr_v6->SetMarkerSize(2.);

  gr_V1->SetMarkerStyle(24);
  gr_V2->SetMarkerStyle(20);
  gr_V3->SetMarkerStyle(22);
  gr_V4->SetMarkerStyle(21);
  gr_V5->SetMarkerStyle(29);
  gr_V6->SetMarkerStyle(28);

  gr_v2->SetMarkerStyle(20);
  gr_v3->SetMarkerStyle(22);
  gr_v4->SetMarkerStyle(21);
  gr_v4_milan->SetMarkerStyle(25);
  gr_v4_ratio->SetMarkerStyle(21);
  gr_v5->SetMarkerStyle(29);
  gr_v6->SetMarkerStyle(28);

  gr_V1->SetMarkerColor(1);
  gr_V2->SetMarkerColor(2);
  gr_V3->SetMarkerColor(kGreen+2);
  gr_V4->SetMarkerColor(4);
  gr_V5->SetMarkerColor(6);
  gr_V6->SetMarkerColor(1);

  gr_v2->SetMarkerColor(2);
  gr_v3->SetMarkerColor(kGreen+2);
  gr_v4->SetMarkerColor(4);
  gr_v4_milan->SetMarkerColor(4);
  gr_v4_ratio->SetMarkerColor(4);
  gr_v5->SetMarkerColor(6);
  gr_v6->SetMarkerColor(1);

  TH2D* htmp = new TH2D("htmp",";p_{T} (GeV/c);V_{n}(2, |#Delta#eta|>2)",1000,0,10,1000,-0.01,0.01);
  TH2D* htmp1 = new TH2D("htmp1",";p_{T} (GeV/c);v_{n}(2, |#Delta#eta|>2)",1000,0,10,1000,0.0,0.122);
  TH2D* htmp2 = new TH2D("htmp2",";p_{T} (GeV/c);Ratio",1000,0,10,1000,0.9,1.1);
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
  htmp2->GetXaxis()->CenterTitle();
  htmp2->GetYaxis()->CenterTitle();
  htmp2->GetXaxis()->SetTitleOffset(1.2);
  htmp2->GetYaxis()->SetTitleOffset(1.2);
  htmp2->GetXaxis()->SetTitleSize(0.05);
  htmp2->GetYaxis()->SetTitleSize(0.05);

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
//  gr_v2->Draw("PESAME");
//  gr_v3->Draw("PESAME");
  gr_v4->Draw("PESAME");
  gr_v4_milan->Draw("PESAME");
//  gr_v5->Draw("PESAME");
//  gr_v6->Draw("PESAME");
  
  TLegend* ll = new TLegend(0.2,0.35,0.37,0.55);
  ll->SetNColumns(2);
  ll->SetBorderSize(0);
  ll->AddEntry(gr_v2,"v_{2}","P");
  ll->AddEntry(gr_v5,"v_{5}","P");
  ll->AddEntry(gr_v3,"v_{3}","P");
  ll->AddEntry(gr_v6,"v_{6}","P");
  ll->AddEntry(gr_v4,"v_{4}","P");
//  ll->Draw("P");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->DrawLatex(0.15,0.92,"CMS PbPb #sqrt{s_{NN}} = 5.02 TeV");
//  latex->DrawLatex(0.67,0.85,"0.3 < p_{T} < 3 GeV/c");

  TCanvas* c3 = new TCanvas("c3","c3",800,600);
  c3->SetLeftMargin(0.15);
  c3->SetBottomMargin(0.15);
  htmp2->Draw();
  gr_v4_ratio->Draw("PE");
  TLine* line = new TLine(0,1,10,1);
  line->Draw("PESAME");
//
//  c2->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_PbPb2015_Golden_v1.gif");
//  c2->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_PbPb2015_Golden_v1.pdf");
}
