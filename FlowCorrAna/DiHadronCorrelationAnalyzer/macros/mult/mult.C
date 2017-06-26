void mult()
{
   TFile* f_mb = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/multana_mb_all_v1.root");
   TFile* f_hm60 = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/multana_hm60_all_v1.root");
   TFile* f_hm85 = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/multana_hm85_all_v1.root");
   TFile* f_hm110 = new TFile("/net/hisrv0001/home/davidlw/scratch2/DiHadronCorrelations/outputs_312/PPData_Minbias_13TeV/merged/multana_hm110_all_v1.root");

   TH1D* h_mb = ((TH2D*)f_mb->Get("mult_ana/multrawvsgen"))->ProjectionY("mb",-1,-1,"e");
   TH1D* h_hm60 = ((TH2D*)f_hm60->Get("mult_ana/multrawvsgen"))->ProjectionY("hm60",-1,-1,"e");
   TH1D* h_hm85 = ((TH2D*)f_hm85->Get("mult_ana/multrawvsgen"))->ProjectionY("hm85",-1,-1,"e");
   TH1D* h_hm110 = ((TH2D*)f_hm110->Get("mult_ana/multrawvsgen"))->ProjectionY("hm110",-1,-1,"e");
  
   Double_t mean_mb = h_mb->GetMean();

   h_mb->SetLineColor(2);
   h_hm60->SetLineColor(3);
   h_hm85->SetLineColor(4);
   h_hm110->SetLineColor(6);

   TCanvas* c = new TCanvas("c","c",500,500);
   c->SetLogy();
//   h_mb->SetAxisRange(0,400,"X");
   h_mb->Draw("hist");
   h_hm60->Draw("histsame");
   h_hm85->Draw("histsame");
   h_hm110->Draw("histsame");

   TH1D* heff_hm60 = (TH1D*)h_hm60->Clone("eff_hm60");
   TH1D* heff_hm85 = (TH1D*)h_hm85->Clone("eff_hm85");
   TH1D* heff_hm110 = (TH1D*)h_hm110->Clone("eff_hm110");

   heff_hm60->Scale(h_mb->Integral(106,10000)/h_hm60->Integral(106,10000));
//   heff_hm60->Divide(h_mb);

   heff_hm85->Scale(heff_hm60->Integral(131,10000)/h_hm85->Integral(131,10000));
//   heff_hm85->Divide(h_hm60);

   heff_hm110->Scale(heff_hm85->Integral(156,10000)/h_hm110->Integral(156,10000));

   TH1D* h = new TH1D("h",";N_{trk}^{offline}",500,0,500);
   for(int i=1;i<=105;i++)
   {
     h->SetBinContent(i,h_mb->GetBinContent(i));
     h->SetBinError(i,h_mb->GetBinError(i));
   }
   for(int i=106;i<=130;i++)
   {
     h->SetBinContent(i,heff_hm60->GetBinContent(i));
     h->SetBinError(i,heff_hm60->GetBinError(i));
   }
   for(int i=131;i<=155;i++)
   {
     h->SetBinContent(i,heff_hm85->GetBinContent(i));
     h->SetBinError(i,heff_hm85->GetBinError(i));
   }
   for(int i=156;i<=500;i++)
   {
     h->SetBinContent(i,heff_hm110->GetBinContent(i));
     h->SetBinError(i,heff_hm110->GetBinError(i));
   }
   h->Scale(1.0/h->Integral());

   TCanvas* c1 = new TCanvas("c1","c1",500,500);
   c1->SetLogy();
   h_mb->SetAxisRange(0,250,"X");
   h_mb->Draw("hist");   
   heff_hm60->Draw("histsame");
   heff_hm85->Draw("histsame");
   heff_hm110->Draw("histsame");

   TCanvas* c2 = new TCanvas("c2","c2",500,500);
   c2->SetLogy();
   h->SetAxisRange(0,250,"X");
   h->Draw("hist");

   TF1 * f1 = new TF1("f1","[0]*ROOT::Math::negative_binomial_pdf(x,[1],[2])",20,200);
   f1->SetParameter(0,0.1);// normalization constant
   f1->SetParameter(1,0.5); // k parameter
   f1->SetParameter(2,5); // mean multiplicity
   h->Fit(f1,"RNO");
   h->Fit(f1,"RNO");
   h->Fit(f1,"RNO");
   f1->Draw("Lsame");

   Double_t xbins[151] = {0};
   for(int i=0;i<101;i++) xbins[i] = i;
   for(int i=101;i<126;i++) xbins[i] = xbins[100] + (i-100)*2;
   for(int i=126;i<136;i++) xbins[i] = xbins[125] + (i-125)*4;
   for(int i=136;i<140;i++) xbins[i] = xbins[135] + (i-135)*10;
   for(int i=140;i<150;i++) xbins[i] = xbins[139] + (i-139)*20;
   for(int i=150;i<151;i++) xbins[i] = xbins[149] + (i-149)*70;

   TH1D* hnew = (TH1D*)h->Rebin(150,"hnew",xbins);
   for(int i=1;i<=hnew->GetNbinsX();i++)
   {
     hnew->SetBinContent(i,hnew->GetBinContent(i)/hnew->GetBinWidth(i));
     hnew->SetBinError(i,hnew->GetBinError(i)/hnew->GetBinWidth(i));
   }
   hnew->Scale(1.0/hnew->Integral("width"));

   Double_t xbins_kno[151] = {0};
   for(int i=0;i<101;i++) xbins_kno[i] = i/mean_mb;
   for(int i=101;i<126;i++) xbins_kno[i] = xbins_kno[100] + (i-100)*2/mean_mb;
   for(int i=126;i<136;i++) xbins_kno[i] = xbins_kno[125] + (i-125)*4/mean_mb;
   for(int i=136;i<140;i++) xbins_kno[i] = xbins_kno[135] + (i-135)*10/mean_mb;
   for(int i=140;i<150;i++) xbins_kno[i] = xbins_kno[139] + (i-139)*20/mean_mb;
   for(int i=150;i<151;i++) xbins_kno[i] = xbins_kno[149] + (i-149)*70/mean_mb;
   TH1D* hnew_kno = new TH1D("hnew_kno",";z=N_{trk}^{offline}/<N_{trk}^{offline}>",150,xbins_kno);
   for(int i=1;i<=hnew_kno->GetNbinsX();i++)
   {
     hnew_kno->SetBinContent(i,hnew->GetBinContent(i));
     hnew_kno->SetBinError(i,hnew->GetBinError(i));
   }

   TCanvas* c3 = new TCanvas("c3","c3",500,500);
   c3->SetLogy();
   hnew->SetAxisRange(0,270,"X");
   hnew->SetMarkerStyle(20);
   hnew->SetMarkerColor(2);
   hnew->Draw("pe");

   TF1 * f2 = new TF1("f2","[0]*ROOT::Math::negative_binomial_pdf(x,[1],[2])",5,250);
   f2->SetParameter(0,0.1);// normalization constant
   f2->SetParameter(1,0.5); // k parameter
   f2->SetParameter(2,5); // mean multiplicity
   hnew->Fit(f2,"RNO");
   hnew->Fit(f2,"RNO");
   hnew->Fit(f2,"RNO");
   f2->Draw("Lsame");

   TCanvas* c4 = new TCanvas("c4","c4",500,500);
   c4->SetLogy();
   hnew_kno->SetAxisRange(0,20,"X");
   hnew_kno->SetMarkerStyle(20);
   hnew_kno->SetMarkerColor(2);
   hnew_kno->Draw("pe");
}
