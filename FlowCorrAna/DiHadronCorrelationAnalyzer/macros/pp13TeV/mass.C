void mass()
{
  using namespace RooFit;

  TFile* f_ks;
  TFile* f_lam;
  f_ks = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/dihadroncorrelation_pp2015D_n1051000_ks.root");
  f_lam = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/dihadroncorrelation_pp2015D_n1051000_lam.root");

/*
  double ptbins[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.4,1.8,2.2,2.8,3.6,4.6,6.0};
  double ptbinwidth[] = {0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.6,0.8,1.0,1.4};
*/
/*
  double ptbins[] = {0.0,0.2,0.6,1.0,1.4,1.8,2.4,3.2,4.4,6.0};
  double ptbinwidth[] = {0.2,0.4,0.4,0.4,0.4,0.6,0.8,1.2,1.6};
*/
/*
  double ptbins[] = {0.0,0.2,0.7,1.2,1.6,2.0,2.6,3.2,4.4,6.0};
  double ptbinwidth[] = {0.2,0.5,0.5,0.4,0.4,0.6,0.6,1.2,1.6};
*/
//v28
/*
  double ptbins[] = {0.0,0.2,0.7,1.2,1.8,2.4,3.2,4.4,6.0};
  double ptbinwidth[] = {0.2,0.5,0.5,0.6,0.6,0.8,1.2,1.6};
*/
//v29
/*
  double ptbins[] = {0.0,0.5,1.0,1.5,2.0,2.6,3.4,4.6,6.0};
  double ptbinwidth[] = {0.5,0.5,0.5,0.5,0.6,0.8,1.2,1.4};
*/
//v30
//  double ptbins[] = {0.0,0.4,0.8,1.2,1.8,2.4,3.2,4.4,6.0};
//  double ptbinwidth[] = {0.4,0.4,0.4,0.6,0.6,0.8,1.2,1.6};
//v35
//  double ptbins[] = {0.0,0.4,0.9,1.3,1.6,2.0,2.6,3.2,4.2,6.0};
//  double ptbinwidth[] = {0.4,0.5,0.4,0.3,0.4,0.6,0.6,1.0,1.8};
//v36
//  double ptbins[] = {0.0,0.2,0.7,1.1,1.6,2.2,3.0,4.2,6.0};
//  double ptbinwidth[] = {0.2,0.5,0.4,0.5,0.6,0.8,1.2,1.8};
//v38
//  double ptbins[] = {0.0, 0.4, 0.7, 1.1, 1.7, 2.5, 3.2, 4.4, 6.0};
//  double ptbinwidth[] = {0.4,0.3,0.4,0.6,0.8,0.7,1.2,1.6};
//  v40
  double ptbins[] = {0.0, 0.4, 0.7, 1.1, 1.7, 2.7, 4.0, 5.6, 9.0};
  double ptbinwidth[] = {0.4,0.3,0.4,0.6,1.0,1.3,1.6,3.4};

  TH1D* ksmassall[30];
  TH1D* lamassall[30];

  TH2D* ksmassptall = (TH2D*)f_ks->Get("corr_ana/v0invmassvspt");
  ksmassptall->SetAxisRange(0.44,0.57,"Y");

  TH2D* lamassptall = (TH2D*)f_lam->Get("corr_ana/v0invmassvspt");
  lamassptall->SetAxisRange(1.08,1.15,"Y");

  RooRealVar *x_la[30],*x_ks[30];
  RooDataHist *data_la[30],*data_ks[30];
  RooPlot *xframe_la[30],*xframe_ks[30];
  RooRealVar *mean_la[30],*mean_ks[30];
  RooRealVar *sigma1_la[30],*sigma1_ks[30];
  RooRealVar *sigma2_la[30],*sigma2_ks[30];
  RooRealVar *sig1_la[30],*sig1_ks[30];
  RooRealVar *sig2_la[30],*sig2_ks[30];
  RooRealVar *a_la[30],*a_ks[30];
  RooRealVar *b_la[30],*b_ks[30];
  RooRealVar *cp_la[30],*cp_ks[30];
  RooRealVar *d_la[30],*d_ks[30];
  RooGaussian *gaus1_la[30],*gaus1_ks[30];
  RooGaussian *gaus2_la[30],*gaus2_ks[30];
  RooPolynomial *poly_la[30],*poly_ks[30];
  RooRealVar *polysig_la[30],*polysig_ks[30];
  RooAddPdf *sum_la[30],*sum_ks[30];

  TLine* l1_la[30];
  TLine* l2_la[30];
  TLine* l1_ks[30];
  TLine* l2_ks[30];

  double ptmean_ks[30];
  double ptmean_la[30];
  double ptmean_err_ks[30];
  double ptmean_err_la[30];
  TH1D*  ksptall = ksmassptall->ProjectionX("ksPtAll",-1,-1,"e");
  TH1D*  laptall = lamassptall->ProjectionX("lamPtAll",-1,-1,"e");
  for(int i=0;i<8;i++)
  {
    ksptall->SetAxisRange(ptbins[i],ptbins[i+1],"X");
    laptall->SetAxisRange(ptbins[i],ptbins[i+1],"X");
    ptmean_ks[i] = ksptall->GetMean();
    ptmean_la[i] = laptall->GetMean();
    ptmean_err_ks[i] = 0;
    ptmean_err_la[i] = 0;
  }

  double sigmean_ks[30]={0};
  double sigmean_la[30]={0};
  double sigmean_err_ks[30]={0};
  double sigmean_err_la[30]={0};
  double sigwidth_ks[30]={0};
  double sigwidth_la[30]={0};
  double sigwidth_err_ks[30]={0};
  double sigwidth_err_la[30]={0};
  double sigfrac_ks[30]={0};
  double sigfrac_la[30]={0};
  double sigsig_ks[30]={0};
  double sigsig_la[30]={0};

  for(int i=0;i<8;i++)
  {
    int nminpt = ksmassptall->GetXaxis()->FindBin(ptbins[i]+0.0001);
    int nmaxpt = ksmassptall->GetXaxis()->FindBin(ptbins[i+1]-0.0001);
   
    ksmassall[i] = ksmassptall->ProjectionY(Form("ksMassAll_%d",i),nminpt,nmaxpt,"e");
    lamassall[i] = lamassptall->ProjectionY(Form("lamMassAll_%d",i),nminpt,nmaxpt,"e");

    x_la[i] = new RooRealVar(Form("x_la_%d",i),"mass",1.,1.2);
    data_la[i] = new RooDataHist(Form("data_la_%d",i),"dataset",*x_la[i],lamassall[i]);
    xframe_la[i] = x_la[i]->frame(80);
    data_la[i]->plotOn(xframe_la[i],Name(Form("data_la_%d",i)));
    mean_la[i] = new RooRealVar(Form("mean_la_%d",i),"mean",1.115,1.11,1.12);
    sigma1_la[i] = new RooRealVar(Form("sigma1_la_%d",i),"sigma1",0.002,0.001,0.012);
    sigma2_la[i] = new RooRealVar(Form("sigma2_la_%d",i),"sigma2",0.01,0.002,0.03);
    sig1_la[i] = new RooRealVar(Form("sig1_la_%d",i),"signal1",10,0,10000000);
    sig2_la[i] = new RooRealVar(Form("sig2_la_%d",i),"signal2",10,0,10000000);
    a_la[i] = new RooRealVar(Form("a_la_%d",i),"a",0,-100000,100000);
    b_la[i] = new RooRealVar(Form("b_la_%d",i),"b",0,-100000,100000);
    cp_la[i] = new RooRealVar(Form("cp_la_%d",i),"cp",0,-100000,100000);
    d_la[i] = new RooRealVar(Form("d_la_%d",i),"d",0,-100000,100000);
    gaus1_la[i] = new RooGaussian(Form("gaus1_la_%d",i),"gaus1",*x_la[i],*mean_la[i],*sigma1_la[i]);
    gaus2_la[i] = new RooGaussian(Form("gaus2_la_%d",i),"gaus2",*x_la[i],*mean_la[i],*sigma2_la[i]);
    poly_la[i] = new RooPolynomial(Form("poly_la_%d",i),"poly",*x_la[i],RooArgList(*a_la[i],*b_la[i]));//,*cp_la[i],*d_la[i]));
    polysig_la[i] = new RooRealVar(Form("polysig_la_%d",i),"polysig",500,0,10000000);
    sum_la[i] = new RooAddPdf(Form("sum_la_%d",i),"sum",RooArgList(*gaus1_la[i],*gaus2_la[i],*poly_la[i]),RooArgList(*sig1_la[i],*sig2_la[i],*polysig_la[i]));

    x_la[i]->setRange("cut",1.095,1.14);
    sum_la[i]->fitTo(*data_la[i],Range("cut"));
//    sum_la[i]->fitTo(*data_la[i],Range("cut"));
//    sum_la[i]->fitTo(*data_la[i],Range("cut"));
    sum_la[i]->plotOn(xframe_la[i],Name(Form("sum_la_%d",i)));
    sum_la[i]->plotOn(xframe_la[i],Components(*poly_la[i]),LineStyle(kDashed));

    double meanf  = mean_la[i]->getVal();
    double meanfe  = mean_la[i]->getError();
    double sigmaf1  = sigma1_la[i]->getVal();
    double sigmaf2  = sigma2_la[i]->getVal();
    double sigmaf1e  = sigma1_la[i]->getError();
    double sigmaf2e  = sigma2_la[i]->getError();
    double bkgf  = polysig_la[i]->getVal();
    double sigf1  = sig1_la[i]->getVal();
    double sigf2  = sig2_la[i]->getVal();
    double sigwf1  = sigf1 /(sigf1 +sigf2 );
    double sigwf2  = sigf2 /(sigf1 +sigf2 );
    double sigmaf  = sqrt(sigmaf1*sigmaf1*sigwf1  + sigmaf2*sigmaf2*sigwf2 );
    double sigmafe  = sqrt(sigmaf1e*sigmaf1e*sigwf1  + sigmaf2e*sigmaf2e*sigwf2 );

    double massmin  = meanf  - 2.0*sigmaf ;
    double massmax  = meanf  + 2.0*sigmaf ;

    double mean_pdg = 1.1159;
//    double massmin  = mean_pdg - 0.01 ;
//    double massmax  = mean_pdg + 0.01 ;
    
    int nmin = lamassall[i]->GetXaxis()->FindBin(massmin);
    int nmax = lamassall[i]->GetXaxis()->FindBin(massmax);
    double totyhe = 0;
    double totyh  = lamassall[i]->IntegralAndError(nmin,nmax,totyhe);
//    double totyh  = lamassall[i]->Integral(nmin,nmax);
    l1_la[i] = new TLine(massmin ,0,massmin ,5000);
    l2_la[i] = new TLine(massmax ,0,massmax ,5000);
    x_la[i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_la[i]->createIntegral(*x_la[i],NormSet(*x_la[i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_la[i]->createIntegral(*x_la[i],NormSet(*x_la[i]));//,Range("cut"));
    RooAbsReal* isig2  = gaus2_la[i]->createIntegral(*x_la[i],NormSet(*x_la[i]));//,Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_la[i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf;
    double bkgye = ibkgf*bkgfe;
    double sigyh  = totyh - bkgy;
//    double sigyh  = sigf1+sigf2;

    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye); 
    double sigy1  = isig1f *sigf1 ;
    double sigy2  = isig2f *sigf2 ;
    double sigy  = sigy1  + sigy2 ;

    if(totyh) sigfrac_la[i] = sigyh / totyh;
    if(totyh) sigsig_la[i] = sigyh / sqrt(totyh);
    sigmean_la[i] = meanf;
    sigmean_err_la[i] = meanfe;
    sigwidth_la[i] = sigmaf;
    sigwidth_err_la[i] = sigmafe;

    x_ks[i] = new RooRealVar(Form("x_ks_%d",i),"mass",0.44-0.02,0.56+0.02);
    data_ks[i] = new RooDataHist(Form("data_ks_%d",i),"dataset",*x_ks[i],ksmassall[i]);
    xframe_ks[i] = x_ks[i]->frame(80);
    data_ks[i]->plotOn(xframe_ks[i],Name(Form("data_ks_%d",i)));
    mean_ks[i] = new RooRealVar(Form("mean_ks_%d",i),"mean",0.50,0.49,0.51);
    sigma1_ks[i] = new RooRealVar(Form("sigma1_ks_%d",i),"sigma1",0.005,0.001,0.02);
    sigma2_ks[i] = new RooRealVar(Form("sigma2_ks_%d",i),"sigma2",0.015,0.001,0.05);
    sig1_ks[i] = new RooRealVar(Form("sig1_ks_%d",i),"signal1",10000,0,1000000);
    sig2_ks[i] = new RooRealVar(Form("sig2_ks_%d",i),"signal2",10000,0,1000000);
    a_ks[i] = new RooRealVar(Form("a_ks_%d",i),"a",0,-1000000,1000000);
    b_ks[i] = new RooRealVar(Form("b_ks_%d",i),"b",0,-1000000,1000000);
    cp_ks[i] = new RooRealVar(Form("cp_ks_%d",i),"cp",0,-1000000,1000000);
    d_ks[i] = new RooRealVar(Form("d_ks_%d",i),"d",0,-1000000,1000000);
    gaus1_ks[i] = new RooGaussian(Form("gaus1_ks_%d",i),"gaus1",*x_ks[i],*mean_ks[i],*sigma1_ks[i]);
    gaus2_ks[i] = new RooGaussian(Form("gaus2_ks_%d",i),"gaus2",*x_ks[i],*mean_ks[i],*sigma2_ks[i]);
    poly_ks[i] = new RooPolynomial(Form("poly_ks_%d",i),"poly",*x_ks[i],RooArgList(*a_ks[i],*b_ks[i],*cp_ks[i],*d_ks[i]));
    polysig_ks[i] = new RooRealVar(Form("polysig_ks_%d",i),"polysig",10,0,10000);
    sum_ks[i] = new RooAddPdf(Form("sum_ks_%d",i),"sum",RooArgList(*gaus1_ks[i],*gaus2_ks[i],*poly_ks[i]),RooArgList(*sig1_ks[i],*sig2_ks[i],*polysig_ks[i]));

    x_ks[i].setRange("cut",0.44+0.01,0.56-0.01);
    sum_ks[i]->fitTo(*data_ks[i],Range("cut"));
//    sum_ks[i]->fitTo(*data_ks[i],Range("cut"));
//    sum_ks[i]->fitTo(*data_ks[i],Range("cut"));
//    sum_ks[i]->fitTo(*data_ks[i],Range("cut"));
//    sum_ks[i]->fitTo(*data_ks[i],Range("cut"));
//    sum_ks[i]->fitTo(*data_ks[i],Range("cut"));
    sum_ks[i]->plotOn(xframe_ks[i],Name(Form("sum_ks_%d",i)));
    sum_ks[i]->plotOn(xframe_ks[i],Components(*poly_ks[i]),LineStyle(kDashed));

    double meanf  = mean_ks[i]->getVal();
    double meanfe  = mean_ks[i]->getError();
    double sigmaf1  = sigma1_ks[i]->getVal();
    double sigmaf2  = sigma2_ks[i]->getVal();
    double sigmaf1e  = sigma1_ks[i]->getError();
    double sigmaf2e  = sigma2_ks[i]->getError();
    double bkgf  = polysig_ks[i]->getVal();
    double sigf1  = sig1_ks[i]->getVal();
    double sigf2  = sig2_ks[i]->getVal();
    double sigwf1  = sigf1 /(sigf1 +sigf2 );
    double sigwf2  = sigf2 /(sigf1 +sigf2 );
    double sigmaf  = sqrt(sigmaf1*sigmaf1*sigwf1  + sigmaf2*sigmaf2*sigwf2 );
    double sigmafe  = sqrt(sigmaf1e*sigmaf1e*sigwf1  + sigmaf2e*sigmaf2e*sigwf2 );

    double massmin  = meanf  - 2.0*sigmaf ;
    double massmax  = meanf  + 2.0*sigmaf ;

    double mean_pdg = 0.4976;
//    double massmin  = mean_pdg - 0.02 ;
//    double massmax  = mean_pdg + 0.02 ;

    int nmin = ksmassall[i]->GetXaxis()->FindBin(massmin);
    int nmax = ksmassall[i]->GetXaxis()->FindBin(massmax);
    double totyhe = 0;
    double totyh  = ksmassall[i]->IntegralAndError(nmin,nmax,totyhe);
    l1_ks[i] = new TLine(massmin ,0,massmin ,5000);
    l2_ks[i] = new TLine(massmax ,0,massmax ,5000);
    x_ks[i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_ks[i]->createIntegral(*x_ks[i],NormSet(*x_ks[i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_ks[i]->createIntegral(*x_ks[i],NormSet(*x_ks[i]));//,Range("cut"));
    RooAbsReal* isig2  = gaus2_ks[i]->createIntegral(*x_ks[i],NormSet(*x_ks[i]));//,Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_ks[i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf ;
    double bkgye = ibkgf*bkgfe ;
    double sigyh  = totyh - bkgy;

    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye);
    double sigy1  = isig1f *sigf1 ;
    double sigy2  = isig2f *sigf2 ;
    double sigy  = sigy1  + sigy2 ;

    if(totyh) sigfrac_ks[i] = sigyh / totyh;
    if(totyh) sigsig_ks[i] = sigyh / sqrt(totyh);
    sigmean_ks[i] = meanf;
    sigmean_err_ks[i] = meanfe;
    sigwidth_ks[i] = sigmaf;
    sigwidth_err_ks[i] = sigmafe;
  }

  TGraphErrors* gr_sigmean_ks = new TGraphErrors(8,ptmean_ks,sigmean_ks,ptmean_err_ks,sigmean_err_ks);
  TGraphErrors* gr_sigwidth_ks = new TGraphErrors(8,ptmean_ks,sigwidth_ks,ptmean_err_ks,sigwidth_err_ks);
  TGraphErrors* gr_sigmean_la = new TGraphErrors(8,ptmean_la,sigmean_la,ptmean_err_la,sigmean_err_la);
  TGraphErrors* gr_sigwidth_la = new TGraphErrors(8,ptmean_la,sigwidth_la,ptmean_err_la,sigwidth_err_la);
  TGraph* gr_sigfrac_ks = new TGraph(8,ptmean_ks,sigfrac_ks);
  TGraph* gr_sigfrac_la = new TGraph(8,ptmean_la,sigfrac_la);
  TGraph* gr_sigsig_ks = new TGraph(8,ptmean_ks,sigsig_ks);
  TGraph* gr_sigsig_la = new TGraph(8,ptmean_la,sigsig_la);

  cout<<"Kshort mean:"<<endl;
  for(int i=0;i<8;i++)
    cout<<sigmean_ks[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Kshort width:"<<endl;
  for(int i=0;i<8;i++)
    cout<<sigwidth_ks[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Lambda mean:"<<endl;
  for(int i=0;i<8;i++)
    cout<<sigmean_la[i]<<" ";
  cout<<endl;
  cout<<endl;

  cout<<"Lambda width:"<<endl;
  for(int i=0;i<8;i++)
    cout<<sigwidth_la[i]<<" ";
  cout<<endl;
  cout<<endl;

  TCanvas* c1 = new TCanvas("c1","c1",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  ksptall->Draw();
  c1->cd(2);
  laptall->Draw();

  TLine* l_ks = new TLine(0,0.4976,6,0.4976);
  TLine* l_la = new TLine(0,1.1159,6,1.1159);
  TCanvas* c3 = new TCanvas("c3","c3",800,400);
  c3->Divide(2,1);
  c3->cd(1);
  gr_sigmean_ks->Draw("AP");
  l_ks->Draw("Lsame");
  c3->cd(2);
  gr_sigwidth_ks->Draw("AP");
  TCanvas* c4 = new TCanvas("c4","c4",800,400);
  c4->Divide(2,1);
  c4->cd(1);
  gr_sigmean_la->Draw("AP");
  l_la->Draw("Lsame");
  c4->cd(2);
  gr_sigwidth_la->Draw("AP");

  TCanvas* c6 = new TCanvas("c6","c6",800,400);
  c6->Divide(2,1);
  c6->cd(1);
  gr_sigfrac_ks->Draw("AP");
  c6->cd(2);
  gr_sigfrac_la->Draw("AP");

  TCanvas* c7 = new TCanvas("c7","c7",800,400);
  c7->Divide(2,1);
  c7->cd(1);
  gr_sigsig_ks->Draw("AP");
  c7->cd(2);
  gr_sigsig_la->Draw("AP");

  TCanvas* c2 = new TCanvas("c2","c2",1200,900);
  c2->Divide(4,3);
  for(int i=0;i<8;i++)
  {
    c2->cd(i+1);
    ksmassall[i]->Draw("PE");
    xframe_ks[i]->Draw("SAME");
    l1_ks[i]->Draw("LSAME");
    l2_ks[i]->Draw("LSAME");
  }

  TCanvas* c5 = new TCanvas("c5","c5",1200,900);
  c5->Divide(4,3);
  for(int i=0;i<8;i++)
  {
    c5->cd(i+1);
    lamassall[i]->Draw("PE");
    xframe_la[i]->Draw("SAME");
    l1_la[i]->Draw("LSAME");
    l2_la[i]->Draw("LSAME");
  }

  TFile* fout = new TFile("V0signal_frac_pp2015D_n1051000_std.root","recreate");
  gr_sigfrac_ks->Write("gr_sigfrac_ks");
  gr_sigfrac_la->Write("gr_sigfrac_la");
  fout->Close();
}
