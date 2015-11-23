void eff_count()
{
  using namespace RooFit;

  TFile* f;
  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation/v0validation_V0EffCountAna_25M_v1.root");
//  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation/v0validation_V0EffCountAna_PbPbPeri_v3.root");
//  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_EPOSall_v14.root");
//  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_v12.root");
/*
  double ptbins[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.4,3.8,4.2,4.6,5.0,5.6,6.6,9.0,12.0};
  int nptbins[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,34,38,42,46,50,56,66,90,120};
  double ptbinwidth[] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.4,0.4,0.6,1.0,2.4,3.0};
*/
  double ptbins[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.6,3.2,4.2,6.0,9.0};
  double ptbinwidth[] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.6,0.6,1.0,1.8,3.0};

  TH2D* ksmassptall[7];
  TH2D* lamassptall[7];
  TH1D* ksmassall[7][30];
  TH1D* lamassall[7][30];
  TH2D* hYieldReco_la;
  TH2D* hYieldReco_ks;
  TH2D* hYieldGen_la;
  TH2D* hYieldGen_ks;
  TH1D* hYieldRecoPt_la[7];
  TH1D* hYieldRecoPt_ks[7];
  TH1D* hYieldGenPt_la[7];
  TH1D* hYieldGenPt_ks[7];

  hYieldGen_la = (TH2D*)f->Get("v0Validator/LamGenVsEtaPt");
  hYieldGen_ks = (TH2D*)f->Get("v0Validator/K0sGenVsEtaPt");
  hYieldReco_la = (TH2D*)hYieldGen_la->Clone("LamRecoVsEtaPt");
  hYieldReco_ks = (TH2D*)hYieldGen_ks->Clone("K0sRecoVsEtaPt");
  hYieldReco_la->Reset();
  hYieldReco_ks->Reset();

  for(int i=0;i<6;i++) 
  {
    ksmassptall[i] = (TH2D*)f->Get(Form("v0Validator/ksMassPtAllEta%d",i+1));
    ksmassptall[i]->SetAxisRange(0.44,0.56,"Y");
  }
  ksmassptall[6] = (TH2D*)f->Get("v0Validator/ksMassPtAll");
  ksmassptall[6]->SetAxisRange(0.45,0.55,"Y");

  for(int i=0;i<6;i++) 
  {
    lamassptall[i] = (TH2D*)f->Get(Form("v0Validator/lamMassPtAllEta%d",i+1));
    lamassptall[i]->SetAxisRange(1.09,1.145,"Y");
  }
  lamassptall[6] = (TH2D*)f->Get("v0Validator/lamMassPtAll");
  lamassptall[6]->SetAxisRange(1.095,1.14,"Y");

  RooRealVar *x_la[7][30],*x_ks[7][30];
  RooDataHist *data_la[7][30],*data_ks[7][30];
  RooPlot *xframe_la[7][30],*xframe_ks[7][30];
  RooRealVar *mean_la[7][30],*mean_ks[7][30];
  RooRealVar *sigma1_la[7][30],*sigma1_ks[7][30];
  RooRealVar *sigma2_la[7][30],*sigma2_ks[7][30];
  RooRealVar *sig1_la[7][30],*sig1_ks[7][30];
  RooRealVar *sig2_la[7][30],*sig2_ks[7][30];
  RooRealVar *a_la[7][30],*a_ks[7][30];
  RooRealVar *b_la[7][30],*b_ks[7][30];
  RooRealVar *cp_la[7][30],*cp_ks[7][30];
  RooRealVar *d_la[7][30],*d_ks[7][30];
  RooGaussian *gaus1_la[7][30],*gaus1_ks[7][30];
  RooGaussian *gaus2_la[7][30],*gaus2_ks[7][30];
  RooPolynomial *poly_la[7][30],*poly_ks[7][30];
  RooRealVar *polysig_la[7][30],*polysig_ks[7][30];
  RooAddPdf *sum_la[7][30],*sum_ks[7][30];

  TLine* l1_la[7][30];
  TLine* l2_la[7][30];
  TLine* l1_ks[7][30];
  TLine* l2_ks[7][30];

  for(int i=0;i<15;i++)
  {
   for(int j=0;j<7;j++)
   {
    int nminpt = ksmassptall[j]->GetXaxis()->FindBin(ptbins[i]+0.0001);
    int nmaxpt = ksmassptall[j]->GetXaxis()->FindBin(ptbins[i+1]-0.0001);
   
    ksmassall[j][i] = ksmassptall[j]->ProjectionY(Form("ksMassAllEta%d_%d",j+1,i),nminpt,nmaxpt,"e");
    lamassall[j][i] = lamassptall[j]->ProjectionY(Form("lamMassAllEta%d_%d",j+1,i),nminpt,nmaxpt,"e");

//    ksmassall[j][i] = ksmassptall[j]->ProjectionY(Form("ksMassAllEta%d_%d",j+1,i),nptbins[i]+1,nptbins[i+1],"e");
//    lamassall[j][i] = lamassptall[j]->ProjectionY(Form("lamMassAllEta%d_%d",j+1,i),nptbins[i]+1,nptbins[i+1],"e");

    x_la[j][i] = new RooRealVar(Form("x_la_eta%d_%d",j+1,i),"mass",1.,1.2);
    data_la[j][i] = new RooDataHist(Form("data_la_eta%d_%d",j+1,i),"dataset",*x_la[j][i],lamassall[j][i]);
    xframe_la[j][i] = x_la[j][i]->frame(80);
    data_la[j][i]->plotOn(xframe_la[j][i],Name(Form("data_la_eta%d_%d",j+1,i)));
    mean_la[j][i] = new RooRealVar(Form("mean_la_eta%d_%d",j+1,i),"mean",1.115,1.11,1.12);
    sigma1_la[j][i] = new RooRealVar(Form("sigma1_la_eta%d_%d",j+1,i),"sigma1",0.003,0.001,0.01);
    sigma2_la[j][i] = new RooRealVar(Form("sigma2_la_eta%d_%d",j+1,i),"sigma2",0.003,0.001,0.01);
    sig1_la[j][i] = new RooRealVar(Form("sig1_la_eta%d_%d",j+1,i),"signal1",10,0,10000000);
    sig2_la[j][i] = new RooRealVar(Form("sig2_la_eta%d_%d",j+1,i),"signal2",10,0,10000000);
    a_la[j][i] = new RooRealVar(Form("a_la_eta%d_%d",j+1,i),"a",0,-100000,100000);
    b_la[j][i] = new RooRealVar(Form("b_la_eta%d_%d",j+1,i),"b",0,-100000,100000);
    cp_la[j][i] = new RooRealVar(Form("cp_la_eta%d_%d",j+1,i),"cp",0,-100000,100000);
    d_la[j][i] = new RooRealVar(Form("d_la_eta%d_%d",j+1,i),"d",0,-100000,100000);
    gaus1_la[j][i] = new RooGaussian(Form("gaus1_la_eta%d_%d",j+1,i),"gaus1",*x_la[j][i],*mean_la[j][i],*sigma1_la[j][i]);
    gaus2_la[j][i] = new RooGaussian(Form("gaus2_la_eta%d_%d",j+1,i),"gaus2",*x_la[j][i],*mean_la[j][i],*sigma2_la[j][i]);
    poly_la[j][i] = new RooPolynomial(Form("poly_la_eta%d_%d",j+1,i),"poly",*x_la[j][i],RooArgList(*a_la[j][i],*b_la[j][i],*cp_la[j][i],*d_la[j][i]));
    polysig_la[j][i] = new RooRealVar(Form("polysig_la_eta%d_%d",j+1,i),"polysig",10,0,10000000);
    sum_la[j][i] = new RooAddPdf(Form("sum_la_eta%d_%d",j+1,i),"sum",RooArgList(*gaus1_la[j][i],*gaus2_la[j][i],*poly_la[j][i]),RooArgList(*sig1_la[j][i],*sig2_la[j][i],*polysig_la[j][i]));


    x_la[j][i]->setRange("cut",1.10,1.14);
    sum_la[j][i]->fitTo(*data_la[j][i],Range("cut"));
    sum_la[j][i]->fitTo(*data_la[j][i],Range("cut"));
    sum_la[j][i]->fitTo(*data_la[j][i],Range("cut"));
    sum_la[j][i]->plotOn(xframe_la[j][i],Name(Form("sum_la_eta%d_%d",j+1,i)));
    sum_la[j][i]->plotOn(xframe_la[j][i],Components(*poly_la[j][i]),LineStyle(kDashed));

    double meanf  = mean_la[j][i]->getVal();
    double meanfe  = mean_la[j][i]->getError();
    double sigmaf1  = sigma1_la[j][i]->getVal();
    double sigmaf2  = sigma2_la[j][i]->getVal();
    double bkgf  = polysig_la[j][i]->getVal();
    double sigf1  = sig1_la[j][i]->getVal();
    double sigf2  = sig2_la[j][i]->getVal();
    double sigwf1  = sigf1 /(sigf1 +sigf2 );
    double sigwf2  = sigf2 /(sigf1 +sigf2 );
    double sigmaf  = sqrt(sigmaf1 **2*sigwf1  + sigmaf2 **2*sigwf2 );
    double massmin  = meanf  - 5*sigmaf ;
    double massmax  = meanf  + 5*sigmaf ;
    int nmin = lamassall[j][i]->GetXaxis()->FindBin(massmin);
    int nmax = lamassall[j][i]->GetXaxis()->FindBin(massmax);
    double totyhe = 0;
    double totyh  = lamassall[j][i]->IntegralAndError(nmin,nmax,totyhe);
//    double totyh  = lamassall[j][i]->Integral(nmin,nmax);
    l1_la[j][i] = new TLine(massmin ,0,massmin ,500);
    l2_la[j][i] = new TLine(massmax ,0,massmax ,500);
    x_la[j][i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]));//,Range("cut"));
    RooAbsReal* isig2  = gaus2_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]));//,Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_la[j][i]->getError();
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

    hYieldReco_la->SetBinContent(j+1,i+1,sigyh);
    hYieldReco_la->SetBinError(j+1,i+1,sigyhe);

    x_ks[j][i] = new RooRealVar(Form("x_ks_eta%d_%d",j+1,i),"mass",0.44,0.56);
    data_ks[j][i] = new RooDataHist(Form("data_ks_eta%d_%d",j+1,i),"dataset",*x_ks[j][i],ksmassall[j][i]);
    xframe_ks[j][i] = x_ks[j][i]->frame(80);
    data_ks[j][i]->plotOn(xframe_ks[j][i],Name(Form("data_ks_eta%d_%d",j+1,i)));
    mean_ks[j][i] = new RooRealVar(Form("mean_ks_eta%d_%d",j+1,i),"mean",0.50,0.49,0.51);
    sigma1_ks[j][i] = new RooRealVar(Form("sigma1_ks_eta%d_%d",j+1,i),"sigma1",0.003,0.001,0.01);
    sigma2_ks[j][i] = new RooRealVar(Form("sigma2_ks_eta%d_%d",j+1,i),"sigma2",0.003,0.001,0.01);
    sig1_ks[j][i] = new RooRealVar(Form("sig1_ks_eta%d_%d",j+1,i),"signal1",10,0,10000000);
    sig2_ks[j][i] = new RooRealVar(Form("sig2_ks_eta%d_%d",j+1,i),"signal2",10,0,10000000);
    a_ks[j][i] = new RooRealVar(Form("a_ks_eta%d_%d",j+1,i),"a",0,-100000,100000);
    b_ks[j][i] = new RooRealVar(Form("b_ks_eta%d_%d",j+1,i),"b",0,-100000,100000);
    cp_ks[j][i] = new RooRealVar(Form("cp_ks_eta%d_%d",j+1,i),"cp",0,-100000,100000);
    d_ks[j][i] = new RooRealVar(Form("d_ks_eta%d_%d",j+1,i),"d",0,-100000,100000);
    gaus1_ks[j][i] = new RooGaussian(Form("gaus1_ks_eta%d_%d",j+1,i),"gaus1",*x_ks[j][i],*mean_ks[j][i],*sigma1_ks[j][i]);
    gaus2_ks[j][i] = new RooGaussian(Form("gaus2_ks_eta%d_%d",j+1,i),"gaus2",*x_ks[j][i],*mean_ks[j][i],*sigma2_ks[j][i]);
    poly_ks[j][i] = new RooPolynomial(Form("poly_ks_eta%d_%d",j+1,i),"poly",*x_ks[j][i],RooArgList(*a_ks[j][i],*b_ks[j][i],*cp_ks[j][i],*d_ks[j][i]));
    polysig_ks[j][i] = new RooRealVar(Form("polysig_ks_eta%d_%d",j+1,i),"polysig",10,0,10000000);
    sum_ks[j][i] = new RooAddPdf(Form("sum_ks_eta%d_%d",j+1,i),"sum",RooArgList(*gaus1_ks[j][i],*gaus2_ks[j][i],*poly_ks[j][i]),RooArgList(*sig1_ks[j][i],*sig2_ks[j][i],*polysig_ks[j][i]));

    x_ks[j][i].setRange("cut",0.45,0.54);
    sum_ks[j][i]->fitTo(*data_ks[j][i],Range("cut"));
    sum_ks[j][i]->fitTo(*data_ks[j][i],Range("cut"));
    sum_ks[j][i]->fitTo(*data_ks[j][i],Range("cut"));
    sum_ks[j][i]->fitTo(*data_ks[j][i],Range("cut"));
    sum_ks[j][i]->fitTo(*data_ks[j][i],Range("cut"));
    sum_ks[j][i]->fitTo(*data_ks[j][i],Range("cut"));
    sum_ks[j][i]->plotOn(xframe_ks[j][i],Name(Form("sum_ks_eta%d_%d",j+1,i)));
    sum_ks[j][i]->plotOn(xframe_ks[j][i],Components(*poly_ks[j][i]),LineStyle(kDashed));

    double meanf  = mean_ks[j][i]->getVal();
    double meanfe  = mean_ks[j][i]->getError();
    double sigmaf1  = sigma1_ks[j][i]->getVal();
    double sigmaf2  = sigma2_ks[j][i]->getVal();
    double bkgf  = polysig_ks[j][i]->getVal();
    double sigf1  = sig1_ks[j][i]->getVal();
    double sigf2  = sig2_ks[j][i]->getVal();
    double sigwf1  = sigf1 /(sigf1 +sigf2 );
    double sigwf2  = sigf2 /(sigf1 +sigf2 );
    double sigmaf  = sqrt(sigmaf1 **2*sigwf1  + sigmaf2 **2*sigwf2 );
    double massmin  = meanf  - 5*sigmaf ;
    double massmax  = meanf  + 5*sigmaf ;
    int nmin = ksmassall[j][i]->GetXaxis()->FindBin(massmin);
    int nmax = ksmassall[j][i]->GetXaxis()->FindBin(massmax);
    double totyhe = 0;
    double totyh  = ksmassall[j][i]->IntegralAndError(nmin,nmax,totyhe);
//    double totyh  = ksmassall[j][i]->Integral(nmin,nmax);
    l1_ks[j][i] = new TLine(massmin ,0,massmin ,500);
    l2_ks[j][i] = new TLine(massmax ,0,massmax ,500);
    x_ks[j][i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]));//,Range("cut"));
    RooAbsReal* isig2  = gaus2_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]));//,Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_ks[j][i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf ;
    double bkgye = ibkgf*bkgfe ;
    double sigyh  = totyh - bkgy;
//    double sigyh  = sigf1+sigf2;

    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye);
    double sigy1  = isig1f *sigf1 ;
    double sigy2  = isig2f *sigf2 ;
    double sigy  = sigy1  + sigy2 ;
    
    hYieldReco_ks->SetBinContent(j+1,i+1,sigyh);
    hYieldReco_ks->SetBinError(j+1,i+1,sigyhe);
  }
}
  for(int i=0;i<6;i++)
  {
    hYieldRecoPt_ks[i] = hYieldReco_ks->ProjectionY(Form("ks_%d",i),i+1,i+1,"e");
    hYieldRecoPt_la[i] = hYieldReco_la->ProjectionY(Form("la_%d",i),i+1,i+1,"e");
  }
  hYieldRecoPt_ks[6] = hYieldReco_ks->ProjectionY(Form("ks_%d",7),1,6,"e");
  hYieldRecoPt_la[6] = hYieldReco_la->ProjectionY(Form("la_%d",7),1,6,"e");
  hYieldRecoPt_ks[6]->Divide(hYieldGen_ks->ProjectionY("gen_ks",1,6,"e"));
  hYieldRecoPt_la[6]->Divide(hYieldGen_la->ProjectionY("gen_la",1,6,"e"));
  TH1D* hYieldRecoEta_ks_ratio = hYieldReco_ks->ProjectionX("EffCountEta_ks",-1,-1,"e");
  TH1D* hYieldRecoEta_la_ratio = hYieldReco_la->ProjectionX("EffCountEta_la",-1,-1,"e");
  hYieldRecoEta_ks_ratio->Divide(hYieldGen_ks->ProjectionX("eta_ks",-1,-1,"e"));  
  hYieldRecoEta_la_ratio->Divide(hYieldGen_la->ProjectionX("eta_la",-1,-1,"e")); 

  TH2D* hYieldReco_la_ratio = (TH2D*)hYieldReco_la->Clone("EffCountEtaPt_la");
  hYieldReco_la_ratio->Divide(hYieldGen_la);
  TCanvas* cc4 = new TCanvas("cc4","cc4",550,500);
  hYieldReco_la_ratio->SetAxisRange(0,1.0,"Z");
  hYieldReco_la_ratio->SetAxisRange(0.2,10.0,"Y");
  hYieldReco_la_ratio->Draw("lego2");  

  TH2D* hYieldReco_ks_ratio = (TH2D*)hYieldReco_ks->Clone("EffCountEtaPt_ks");
  hYieldReco_ks_ratio->Divide(hYieldGen_ks);
  TCanvas* cc5 = new TCanvas("cc5","cc5",550,500);
  hYieldReco_ks_ratio->SetAxisRange(0,1.0,"Z");
  hYieldReco_ks_ratio->SetAxisRange(0.2,10.0,"Y");
  hYieldReco_ks_ratio->Draw("lego2");

  TH1D* hEffvsPt_ks[7];
  TH1D* hEffvsPt_la[7];
  for(int i=0;i<6;i++)
  {
    hEffvsPt_ks[i] = hYieldReco_ks_ratio->ProjectionY(Form("EffCountPt_ks_%d",i+1),i+1,i+1,"e");
    hEffvsPt_la[i] = hYieldReco_la_ratio->ProjectionY(Form("EffCountPt_la_%d",i+1),i+1,i+1,"e");
  }
  hEffvsPt_ks[6] = hYieldRecoPt_ks[6];
  hEffvsPt_la[6] = hYieldRecoPt_la[6];
  hEffvsPt_ks[6]->SetName("EffCountPt_ks_7");
  hEffvsPt_la[6]->SetName("EffCountPt_la_7");


  TCanvas* c1 = new TCanvas("c1","c1",900,450);
  c1->Divide(2,1);
  c1->cd(1);
  hEffvsPt_ks[0]->Draw("PE");
  c1->cd(2);
  hEffvsPt_la[0]->Draw("PE");

  TCanvas* c2 = new TCanvas("c2","c2",900,450);
  c2->Divide(2,1);
  c2->cd(1);
  hEffvsPt_ks[1]->Draw("PE");
  c2->cd(2);
  hEffvsPt_la[1]->Draw("PE");

  TCanvas* c3 = new TCanvas("c3","c3",900,450);
  c3->Divide(2,1);
  c3->cd(1);
  hEffvsPt_ks[2]->Draw("PE");
  c3->cd(2);
  hEffvsPt_la[2]->Draw("PE");

  TCanvas* c4 = new TCanvas("c4","c4",900,450);
  c4->Divide(2,1);
  c4->cd(1);
  hEffvsPt_ks[3]->Draw("PE");
  c4->cd(2);
  hEffvsPt_la[3]->Draw("PE");

  TCanvas* c5 = new TCanvas("c5","c5",900,450);
  c5->Divide(2,1);
  c5->cd(1);
  hEffvsPt_ks[4]->Draw("PE");
  c5->cd(2);
  hEffvsPt_la[4]->Draw("PE");

  TCanvas* c6 = new TCanvas("c6","c6",900,450);
  c6->Divide(2,1);
  c6->cd(1);
  hEffvsPt_ks[5]->Draw("PE");
  c6->cd(2);
  hEffvsPt_la[5]->Draw("PE");

  TFile* fout = new TFile("V0Eff_counting_PbPbPeri.root","recreate");
//  TFile* fout = new TFile("V0Eff_counting_10M.root","recreate");
  hYieldReco_la_ratio->Write();
  hYieldReco_ks_ratio->Write();
  for(int i=0;i<7;i++)
  {
    hEffvsPt_ks[i]->Write();
    hEffvsPt_la[i]->Write();
  }
  hYieldRecoEta_ks_ratio->Write();
  hYieldRecoEta_la_ratio->Write();
  fout->Close();

//  SaveCanvas(c,"HI/V0","ksmassfake");
//  SaveCanvas(c1,"HI/V0","lammassfake");
//  SaveCanvas(c2,"HI/V0","ksmassgood");
//  SaveCanvas(c3,"HI/V0","lammassgood");
}
