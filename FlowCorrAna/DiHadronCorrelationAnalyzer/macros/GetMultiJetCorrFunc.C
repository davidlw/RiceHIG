#include "/net/hisrv0001/home/davidlw/useful_macros/doubleGaussian.C"

#define PI 3.141593

double ymin=-0.01;
double detamin=-3.9;
double detamax=3.9;

double detaprojmin=2; 
double detaprojmax=5;

TString outputdir = "/net/hisrv0001/home/davidlw/scratch/DiHadronCorrelations/outputs_312";
TString subdir = "";
//TString subdir = "ana/";
TFile* gInputfile;

TH1::SetDefaultSumw2();

void setupInputFile(TString dataset="PythiaGen_Minbias_10TeV", TString tag="Eff1", int nmin=-1, int nmax=-1, float etatrgmin=-2.0, float etatrgmax=2.0, float etaassmin=-2.5, float etaassmax=2.5, int centmin=-1, int centmax=-1)
{
	gInputfile = new TFile(Form("%s/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",outputdir.Data(),dataset.Data(),dataset.Data(),tag.Data(),nmin,nmax,etatrgmin,etatrgmax,etaassmin,etaassmax,centmin,centmax));
}

TH1D* GetMult()
{
                   TH1D* hmult = (TH1D*) gInputfile->Get(Form("%smult",subdir.Data()));
                   return hmult;
}

TH2D* GetMultTrg(int itrg)
{
                   TH2D* hmulttrg = (TH2D*) gInputfile->Get(Form("%smult_trg_%d",subdir.Data(),itrg));
                   return hmulttrg;
}

TProfile* GetMultTrgProfileX(int itrg)
{
                   TH2D* hmulttrg = (TH2D*) gInputfile->Get(Form("%smult_trg_%d",subdir.Data(),itrg));
                   hmulttrg->Rebin2D(8,1);
                   TProfile* hmulttrg_profx = (TProfile*)hmulttrg->ProfileX(Form("mult_trg_%d_profx",itrg),-1,-1);
                   return hmulttrg_profx;
}

double GetMultTrgMean(int itrg)
{
                   TH2D* hmulttrg = (TH2D*) gInputfile->Get(Form("%smult_trg_%d",subdir.Data(),itrg));
                   TH1D* hmulttrg_proj = (TH1D*)hmulttrg->ProjectionY(Form("mult_trg_proj_%d",itrg),-1,-1);
                   double  multtrg_mean = hmulttrg_proj->GetMean();
                   return multtrg_mean;
}

TH2D* GetMultAss(int jass)
{
                   TH2D* hmultass = (TH2D*) gInputfile->Get(Form("%smult_ass_%d",subdir.Data(),jass));
                   return hmultass;
}

TProfile* GetMultAssProfileX(int jass)
{
                   TH2D* hmultass = (TH2D*) gInputfile->Get(Form("%smult_ass_%d",subdir.Data(),jass));
                   hmultass->Rebin2D(8,1);
                   TProfile* hmultass_profx = (TProfile*)hmultass->ProfileX(Form("mult_ass_%d_profx",jass),-1,-1);
                   return hmultass_profx;
}

double GetMultAssMean(int jass)
{
                   TH2D* hmultass = (TH2D*) gInputfile->Get(Form("%smult_ass_%d",subdir.Data(),jass));
                   TH1D* hmultass_proj = (TH1D*)hmultass->ProjectionY(Form("mult_ass_proj_%d",jass),-1,-1);
                   double  multass_mean = hmultass_proj->GetMean();
                   return multass_mean;
}

double GetMeanpTtrg(int itrg)
{
		    TH1D* hpttrg = (TH1D*) gInputfile->Get(Form("%spt_trg_%d",subdir.Data(),itrg));
                    double pttrg = hpttrg->GetMean();
                    return pttrg;
}

double GetMeanpTass(int jass)
{
		    TH1D* hptass = (TH1D*) gInputfile->Get(Form("%spt_ass_%d",subdir.Data(),jass));
                    double ptass = hptass->GetMean();
                    return ptass;
}

int GetNumOfTrgSignal(int itrg, int jass)
{
                    TH1D* hnumoftrgsignal = (TH1D*)gInputfile->Get(Form("%spt_trg_%d",subdir.Data(),itrg));
cout<<hnumoftrgsignal->Integral()<<" "<<hnumoftrgsignal->GetEntries()<<endl;
                    return hnumoftrgsignal->Integral();
}

int GetNumOfTrgBackground(int itrg, int jass)
{
                    return GetNumOfTrgSignal(itrg,jass)*10;
}

TH1D* GetRawSignal1D(int itrg, int jass)
{
		    TH2D* hsignal = GetRawSignal2D(itrg,jass); 
		    TH1D* hsignalphi = (TH1D*)hsignal->ProjectionY(Form("signalphi_trg%d_ass%d",itrg,jass),hsignal->GetXaxis()->FindBin(detaprojmin),hsignal->GetXaxis()->FindBin(detaprojmax),"e");
		    hsignalphi->Scale(hsignal->GetXaxis()->GetBinWidth(1));
		    hsignalphi->GetXaxis()->CenterTitle();
		    hsignalphi->GetYaxis()->CenterTitle();  
	            hsignalphi->SetYTitle("S(#Delta#phi)");	    
                    hsignalphi->SetName(Form("signalphi_scale_trg%d_ass%d",itrg,jass));      
                    return hsignalphi;
}

double GetV2(int itrg, int jass)
{
                    TH2D* hsignal = (TH2D*) gInputfile->Get(Form("%ssignal_trg%d_ass%d",subdir.Data(),itrg,jass));
                    TH1D* hsignalphi = (TH1D*)hsignal->ProjectionY(Form("signalphi_trg%d_ass%d",itrg,jass),-1,hsignal->GetXaxis()->FindBin(-1.0),"e");
                    hsignalphi->Scale(1.0/hsignalphi->Integral());
                    TH2D* hmulttrg = (TH2D*) gInputfile->Get(Form("%smult_trg_%d",subdir.Data(),itrg));
                    TH1D* hmulttrg_proj = (TH1D*)hmulttrg->ProjectionY(Form("mult_trg_proj_%d",itrg),-1,-1);
                    float multtrg_mean = hmulttrg_proj->GetMean();
cout<<multtrg_mean<<endl;
                    TF1* fitfunc = new TF1("fitfunc","1+2*[0]*TMath::Cos(2*x)",-PI/2.,3.*PI/2.);
                    fitfunc->SetParameter(0,0.01);
                    fitfunc->SetParLimits(0,0.0,1.0);
                    hsignalphi->Fit(fitfunc,"RNO");
                    float V2=fitfunc->GetParameter(0)*(multtrg_mean-1);
//                    float V2 = 0;          
//                    for(int i=1;i<=hsignalphi->GetNbinsX();i++) 
//                      V2 = V2 + TMath::Cos(2*hsignalphi->GetBinCenter(i))*hsignalphi->GetBinContent(i); 
                    //V2 = V2 / hsignalphi->Integral(); //* (multtrg_mean-1);
                    return sqrt(V2);
}

TH2D* GetRawSignal2D(int itrg, int jass)
{
		    TH2D* hsignal = (TH2D*) gInputfile->Get(Form("%ssignal_trg%d_ass%d",subdir.Data(),itrg,jass));
                    int numoftrgsignal = GetNumOfTrgSignal(itrg,jass);
                    hsignal->Scale(1.0/numoftrgsignal);
		    hsignal->GetXaxis()->CenterTitle();
                    hsignal->GetYaxis()->CenterTitle();
                    hsignal->GetZaxis()->CenterTitle();	
	            hsignal->SetZTitle("S(#Delta#eta,#Delta#phi)");	   
		    hsignal->SetAxisRange(detamin,detamax,"X"); 
                    hsignal->SetName(Form("signal_scale_trg%d_ass%d",itrg,jass)); 
                    return hsignal;
}

TH1D* GetRawBackground1D(int itrg, int jass)
{
		    TH2D* hbackground = (TH2D*) GetRawBackground2D(itrg,jass);
		    TH1D* hbackphi = (TH1D*)hbackground->ProjectionY(Form("backphi_trg%d_ass%d",itrg,jass),hbackground->GetXaxis()->FindBin(detaprojmin),hbackground->GetXaxis()->FindBin(detaprojmax),"e");
		    hbackphi->Scale(hbackground->GetXaxis()->GetBinWidth(1));              
                    hbackphi->GetXaxis()->CenterTitle();
		    hbackphi->GetYaxis()->CenterTitle();
                    hbackphi->SetYTitle("B(#Delta#phi)");
                    hbackphi->SetName(Form("backphi_scale_trg%d_ass%d",itrg,jass));          
		    return hbackphi;
}

TH2D* GetRawBackground2D(int itrg, int jass)
{
		    TH2D* hbackground = (TH2D*) gInputfile->Get(Form("%sbackground_trg%d_ass%d",subdir.Data(),itrg,jass));
                    int numoftrgbackground = GetNumOfTrgBackground(itrg,jass);
                    hbackground->Scale(1.0/numoftrgbackground);
                    hbackground->GetXaxis()->CenterTitle();
                    hbackground->GetYaxis()->CenterTitle();
                    hbackground->GetZaxis()->CenterTitle();
                    hbackground->SetZTitle("B(#Delta#eta,#Delta#phi)");
		    hbackground->SetAxisRange(detamin,detamax,"X");
                    hbackground->SetName(Form("background_scale_trg%d_ass%d",itrg,jass));
		    return hbackground;
}

TH1D* GetRawCorrFunc1D_ratio(int itrg, int jass)
{
                    TH1D* hsignalphi = GetRawSignal1D(itrg,jass);
                    TH1D* hcorrphi = (TH1D*)hsignalphi->Clone(Form("corrphi_trg%d_ass%d",itrg,jass));
		    hcorrphi->SetYTitle("C(#Delta#phi)");  
		    TH1D* hbackphi = GetRawBackground1D(itrg,jass);
		    hcorrphi->Divide(hbackphi); 
                    float max = hcorrphi->GetBinContent(hcorrphi->GetMaximumBin());
//		    hcorrphi->SetAxisRange(ymin,max*1.3,"Y");
                    return hcorrphi;
}

TH2D* GetRawCorrFunc2D_ratio(int itrg, int jass)
{
                    TH2D* hsignal = GetRawSignal2D(itrg,jass);
		    TH2D* hbackground = GetRawBackground2D(itrg,jass);
		    hcorrelation = (TH2D*) hsignal->Clone(Form("correlation_trg%d_ass%d",itrg,jass));
                    hcorrelation->Divide(hbackground); 
                    hcorrelation->GetXaxis()->CenterTitle();
                    hcorrelation->GetYaxis()->CenterTitle();
                    hcorrelation->GetZaxis()->CenterTitle();
                    hcorrelation->SetZTitle("C(#Delta#eta,#Delta#phi)");
		    hcorrelation->SetAxisRange(detamin,detamax,"X");					
		    return hcorrelation;
}


TH1D* GetJetCorrFunc1D_doublegaussian(int itrg, int jass)
{
                    TH1D* hcorrphi = (TH1D*)GetRawCorrFunc1D_ratio(itrg,jass);
		    TF1* fitfunc = new TF1("fitfunc",doubleGaussian,-PI/2.,3.*PI/2.,5);		    
                    fitfunc->SetParameters(hcorrphi->GetMinimum(),hcorrphi->GetMaximum()-hcorrphi->GetMinimum(),0.3,hcorrphi->GetMaximum(hcorrphi->GetMaximum())-hcorrphi->GetMinimum(),0.5);  
                    fitfunc->SetParLimits(0,0,100000);
                    fitfunc->SetParLimits(1,0,100000);
                    fitfunc->SetParLimits(2,0,100000);
                    fitfunc->SetParLimits(3,0,100000);
                    fitfunc->SetParLimits(4,0,100000);		    
		    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit("fitfunc","RNO");                     
		    TH1D* hcorrphi_clone = (TH1D*)hcorrphi->Clone(Form("corrphi_clone_itrg%d_jass%d",itrg,jass));
		    float level = fitfunc->GetParameter(0);
		    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
                    float max = hcorrphi_clone->GetBinContent(hcorrphi_clone->GetMaximumBin());
                    hcorrphi_clone->SetAxisRange(ymin,max*1.3,"Y");
                    delete fitfunc;
                    return hcorrphi_clone;
}


TH1D* GetJetCorrFunc1D_ZYA1(int itrg, int jass)
{
                    TH1D* hcorrphi = (TH1D*)GetRawCorrFunc1D_ratio(itrg,jass);
                    TH1D* hcorrphi_clone = (TH1D*)hcorrphi->Clone(Form("corrphi_clone_itrg%d_jass%d",itrg,jass));
                    hcorrphi->SetAxisRange(0.5,2.0,"X");
                    double histminY = hcorrphi->GetMinimum();
		    TF1* fitfunc = new TF1("fitfunc","[0]+[1]*x",0.8,1.2);		    
                    fitfunc->SetParameters(histminY,0);
                    fitfunc->FixParameter(1,0);
		    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit("fitfunc","RNO");                     
		    float level = fitfunc->GetParameter(0);
		    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
                    float max = hcorrphi_clone->GetBinContent(hcorrphi_clone->GetMaximumBin());
                    hcorrphi_clone->SetAxisRange(ymin,max*1.3,"Y");
		    hcorrphi_clone->SetAxisRange(-PI/2.,3.*PI/2.,"X");
                    delete fitfunc;
                    return hcorrphi_clone;
}

TH1D* GetJetCorrFunc1D_ZYA1_pp(TH1D* h)
{
                    TH1D* hcorrphi_clone = (TH1D*)h->Clone(Form("%s_zyam",h->GetName()));
                    float level = hcorrphi_clone->GetBinContent(hcorrphi_clone->FindBin(2.0));
                    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
                    return hcorrphi_clone;
}

TH1D* GetJetCorrFunc1D_ZYAM_pp(TH1D* h)
{
                    TH1D* hcorrphi_clone = (TH1D*)h->Clone(Form("%s_zyam",h->GetName()));
                    TF1* fitfunc = GetFitFunc_ZYAM_pp(h);
                    float level = fitfunc->GetParameter(0);
                    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
                    delete fitfunc;
                    return hcorrphi_clone;
}

TH1D* GetJetCorrFunc1D_ZYAM(TH1D* h)
{
                    TH1D* hcorrphi_clone = (TH1D*)h->Clone(Form("%s_zyam",h->GetName()));
                    TF1* fitfunc = GetFitFunc_ZYAM(h);
		    float level = fitfunc->GetParameter(0);
		    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
//                    hcorrphi_clone->SetAxisRange(-0.05,2.95,"Y");
                    delete fitfunc;
                    return hcorrphi_clone;
}

TH1D* GetJetCorrFunc1D_ZYAM_poor(TH1D* h)
{
                    TH1D* hcorrphi_clone = (TH1D*)h->Clone(Form("%s_zyam",h->GetName()));
                    TF1* fitfunc = GetFitFunc_ZYAM_poor(h);
                    float level = fitfunc->GetParameter(0);
                    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
//                    hcorrphi_clone->SetAxisRange(-0.05,2.95,"Y");
                    delete fitfunc;
                    return hcorrphi_clone;
}

TH1D* GetJetCorrFunc1D_ZYAM_AllPhysics(TH1D* h)
{
                    TH1D* hcorrphi_clone = (TH1D*)h->Clone(Form("%s_zyam",h->GetName()));
                    TF1* fitfunc = GetFitFunc_ZYAM_AllPhysics(h);
                    float level = fitfunc->GetParameter(0);
                    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
//                    hcorrphi_clone->SetAxisRange(-0.05,2.95,"Y");
                    delete fitfunc;
                    return hcorrphi_clone;
}

TH1D* GetJetCorrFunc1D_ZYAM_MC(TH1D* h)
{                   
                    TH1D* hcorrphi_clone = (TH1D*)h->Clone(Form("%s_zyam",h->GetName()));
                    TF1* fitfunc = GetFitFunc_ZYAM_MC(h);
                    float level = fitfunc->GetParameter(0);
                    for(int ibin=1;ibin<=hcorrphi_clone->GetNbinsX();ibin++) hcorrphi_clone->SetBinContent(ibin,hcorrphi_clone->GetBinContent(ibin)-level);
//                    hcorrphi_clone->SetAxisRange(-0.05,2.95,"Y");
                    delete fitfunc;
                    return hcorrphi_clone;
}                   

TF1* GetFitFunc_ZYAM(TH1D* h)
{
                    TH1D* hcorrphi = (TH1D*)h->Clone(h->GetName());
                    double histminY = hcorrphi->GetBinContent(10);
                    double histminX = 1.0;

                    //hcorrphi->SetAxisRange(-0.01,1.2,"X"); 
                    TF1* fitfunc = new TF1(Form("fitfunc_%s",h->GetName()),"[0]+[1]*(x-[2])*(x-[2])",1.0,2.4); //std 0.6 1.55 vs pT ; 0.6 1.8 vs eta
                    fitfunc->SetParameters(histminY,0.0002,histminX);
                    fitfunc->SetParLimits(1,0,1000);
                    fitfunc->SetParLimits(2,1.0,2.4);
                   
/*
//                    hcorrphi->SetAxisRange(-0.01,1.2,"X"); 
                    TF1* fitfunc = new TF1(Form("fitfunc_%s",h->GetName()),"[0]+[1]*(x-[2])*(x-[2])",0.65,1.3); 
                    fitfunc->SetParameters(histminY,0.0002,histminX);
                    fitfunc->SetParLimits(1,0,1000);
                    fitfunc->SetParLimits(2,0.05,1000);
*/
                    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%s",h->GetName()),"RNO");
                    return fitfunc;
}

TF1* GetFitFunc_ZYAM_pp(TH1D* h)
{
                    TH1D* hcorrphi = (TH1D*)h->Clone(h->GetName());
//                    double histminY = hcorrphi->GetBinContent(hcorrphi->GetMinimumBin());
//                    double histminX = hcorrphi->GetBinCenter(hcorrphi->GetMinimumBin());
                    double histminY = hcorrphi->GetBinContent(hcorrphi->FindBin(1.2));
                    double histminX = hcorrphi->GetBinCenter(hcorrphi->FindBin(1.2));

                    //hcorrphi->SetAxisRange(-0.01,1.2,"X");
                    TF1* fitfunc = new TF1(Form("fitfunc_%s",h->GetName()),"[0]+[1]*(x-[2])*(x-[2])+[3]*abs((x-[2])*(x-[2])*(x-[2]))",0.5,2.5); //std 0.6 1.55 vs pT ; 0.6 1.8 vs eta
                    fitfunc->SetParameters(histminY,0.002,histminX,0.0);
                    fitfunc->SetParLimits(1,0,1000);
                    fitfunc->SetParLimits(2,0.2,2.0);
                   // fitfunc->SetParLimits(3,0,100);
                    fitfunc->FixParameter(3,0);

                    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%s",h->GetName()),"NO","",histminX-0.6,histminX+0.6);
                    fitfunc->SetName(Form("fitfunc_%s_%.3f",h->GetName(),fitfunc->GetParameter(0)));
                    return fitfunc;
}

TF1* GetFitFunc_ZYAM_poor(TH1D* h)
{                    TH1D* hcorrphi = (TH1D*)h->Clone(h->GetName());
                    double histminY = hcorrphi->GetBinContent(10);
                    double histminX = 1.0;

                    //hcorrphi->SetAxisRange(-0.01,1.2,"X");
                    TF1* fitfunc = new TF1(Form("fitfunc_%s",h->GetName()),"[0]+[1]*(x-[2])*(x-[2])+[3]*(x-[2])*(x-[2])*(x-[2])",0.5,1.5); //std 0.6 1.55 vs pT ; 0.6 1.8 vs eta
                    fitfunc->SetParameters(histminY,0.0002,histminX,0.0001);
                    fitfunc->SetParLimits(1,0,1000);
                    fitfunc->SetParLimits(2,0.5,1000);
                    fitfunc->FixParameter(3,0);

                    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%s",h->GetName()),"RNO");
                    return fitfunc;
}


TF1* GetFitFunc_ZYAM_AllPhysics(TH1D* h)
{
                    TH1D* hcorrphi = (TH1D*)h->Clone(h->GetName());
                    double histminY = hcorrphi->GetBinContent(10);
                    double histminX = 1.0;

                    hcorrphi->SetAxisRange(-0.01,1.5,"X");
                    TF1* fitfunc = new TF1(Form("fitfunc_%s",h->GetName()),"[0]+[1]*(x-[2])*(x-[2])+[3]*(x-[2])*(x-[2])*(x-[2])",0.5,1.65); //std 0.6 1.55 vs pT ; 0.6 1.8 vs eta
                    fitfunc->SetParameters(histminY,0.0002,histminX,0.0001);
                    fitfunc->SetParLimits(1,0,1000);
                    fitfunc->SetParLimits(2,0.5,1000);
                  //  fitfunc->SetParLimits(3,0,1000);

                    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%s",h->GetName()),"RNO");
                    return fitfunc;
}

TF1* GetFitFunc_ZYAM_MC(TH1D* h)
{
                    TH1D* hcorrphi = (TH1D*)h->Clone(h->GetName());
                    double histminY = hcorrphi->GetBinContent(10);
                    double histminX = 1.0;

                    //hcorrphi->SetAxisRange(-0.01,1.2,"X");
                    TF1* fitfunc = new TF1(Form("fitfunc_%s",h->GetName()),"[0]+[1]*(x-[2])*(x-[2])",0.8,2.8); //std 0.15-1.8
                    fitfunc->SetParameters(histminY,0.0002,histminX);
                    fitfunc->SetParLimits(1,0,1000);
                    fitfunc->SetParLimits(2,0.05,1000);

                    for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%s",h->GetName()),"RNO");
                    return fitfunc;
}

TH1D* GetFinalCorrFunc1D(int itrg, int jass)
{
                    TH1D* hbackground_phi = (TH1D*)GetRawBackground1D(itrg,jass);
		    TH1D* hcorrphi = (TH1D*)GetJetCorrFunc1D_ZYAM(itrg,jass);
                    hcorrphi->Multiply(hbackground_phi);
                    float max = hcorrphi->GetBinContent(hcorrphi->GetMaximumBin());
		    hcorrphi->SetAxisRange(ymin,max*1.5,"Y");
                    hcorrphi->SetYTitle("#frac{1}{N^{trg}}#frac{d^{2}N}{d#Delta#phi}");
                    return hcorrphi;
}

TH2D* GetJetCorrFunc2D_doublegaussian(int itrg, int jass)
{
                    TH2D* hcorr = (TH2D*)GetRawCorrFunc2D_ratio(itrg,jass);
                    TH2D* hcorr_clone = (TH2D*)hcorr->Clone(Form("corr_clone_itrg%d_jass%d",itrg,jass));
                    hcorr_clone->Reset();
		    for(int ietabin=1;ietabin<=hcorr->GetNbinsX();ietabin++)
		    {
                      TH1D* hcorrphi = (TH1D*)hcorr->ProjectionY(Form("corrphi_%d",ietabin),ietabin,ietabin,"e");  
                      float min = hcorrphi->GetMinimum();
                      hcorrphi->SetAxisRange(-1,1,"X");
                      float nearmax = hcorrphi->GetMaximum();
                      hcorrphi->SetAxisRange(PI-1,PI+1,"X");
                      float awaymax = hcorrphi->GetMaximum();

		      TF1* fitfunc = new TF1("fitfunc",doubleGaussian,-PI/2.,3.*PI/2.,5);		    
                      fitfunc->SetParameters(min,nearmax-min,0.3,awaymax-min,0.5);  
                      fitfunc->SetParLimits(0,0,100000);
                      fitfunc->SetParLimits(1,0,100000);
                      fitfunc->SetParLimits(2,0,100000);
                      fitfunc->SetParLimits(3,0,100000);
                      fitfunc->SetParLimits(4,0,100000);		    
		      for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%d",ietabin),"RNO");                     
		      float level = fitfunc->GetParameter(0);

		      for(int iphibin=1;iphibin<=hcorr->GetNbinsY();iphibin++) 
                        hcorr_clone->SetBinContent(ietabin,iphibin,hcorr->GetBinContent(ietabin,iphibin)-level);                      
                      delete fitfunc;
		    }

                    float max = hcorr_clone->GetBinContent(hcorr_clone->GetMaximumBin());
                    hcorr_clone->SetAxisRange(ymin,max*1.3,"Z");
                    return hcorr_clone;
}


TH2D* GetJetCorrFunc2D_ZYA1(int itrg, int jass)
{
                    TH2D* hcorr = (TH2D*)GetRawCorrFunc2D_ratio(itrg,jass);
                    TH2D* hcorr_clone = (TH2D*)hcorr->Clone(Form("corr_clone_itrg%d_jass%d",itrg,jass));
                    hcorr_clone->Reset();
		    for(int ietabin=1;ietabin<=hcorr->GetNbinsX();ietabin++)
		    {
                      TH1D* hcorrphi = (TH1D*)hcorr->ProjectionY(Form("corrphi_%d",ietabin),ietabin,ietabin,"e");  
                      hcorrphi->SetAxisRange(0.5,2.0,"X");
                      double histminY = hcorrphi->GetMinimum();
		      fitfunc = new TF1("fitfunc","[0]+[1]*x",0.8,1.2);		    
                      fitfunc->SetParameters(histminY,0);
                      fitfunc->FixParameter(1,0);
		      for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%d",ietabin),"RNO");                     
		      float level = fitfunc->GetParameter(0);
		      for(int iphibin=1;iphibin<=hcorrphi->GetNbinsY();iphibin++)
                        hcorr_clone->SetBinContent(ietabin,iphibin,hcorr->GetBinContent(ietabin,iphibin)-level);
                      delete fitfunc;
		    }

                    float max = hcorr_clone->GetBinContent(hcorr_clone->GetMaximumBin());
                    hcorr_clone->SetAxisRange(ymin,max*1.3,"Z");
                    return hcorr_clone;
}

TH2D* GetJetCorrFunc2D_ZYAM(int itrg, int jass)
{
                    TH2D* hcorr = (TH2D*)GetRawCorrFunc2D_ratio(itrg,jass);
                    TH2D* hcorr_clone = (TH2D*)hcorr->Clone(Form("corr_clone_itrg%d_jass%d",itrg,jass));
                    hcorr_clone->Reset();
		    for(int ietabin=1;ietabin<=hcorr->GetNbinsX();ietabin++)
		    {
                      TH1D* hcorrphi = (TH1D*)hcorr->ProjectionY(Form("corrphi_%d",ietabin),ietabin,ietabin,"e");  
                     // hcorrphi->SetAxisRange(0.35,1.57,"X");
                      double histminX = hcorrphi->GetBinCenter(hcorrphi->GetMinimumBin());
                      double histminY = hcorrphi->GetBinContent(hcorrphi->GetMinimumBin());
	   	      fitfunc = new TF1(Form("fitfunc_%d",ietabin),"[0]+[1]*(x-[2])*(x-[2])",0.6,1.2);		    
                      fitfunc->SetParameters(histminY,1,histminX);
                      fitfunc->SetParLimits(1,0,0.10000);
                  //    fitfunc->SetParLimits(2,0.35,1.57);
		      for(int ifit=0;ifit<3;ifit++) hcorrphi->Fit(Form("fitfunc_%d",ietabin),"RNO");                     		  
		      float level = fitfunc->GetParameter(0);
		      for(int iphibin=1;iphibin<=hcorr->GetNbinsY();iphibin++) 
                        hcorr_clone->SetBinContent(ietabin,iphibin,hcorr->GetBinContent(ietabin,iphibin)-level);
		    }
                    
                    float max = hcorr_clone->GetBinContent(hcorr_clone->GetMaximumBin());
                    hcorr_clone->SetAxisRange(ymin,max*1.3,"Z");		    
                    return hcorr_clone;
}

TH2D* GetFinalCorrFunc2D(int itrg, int jass)
{
                    TH2D* hbackground = (TH2D*)GetRawBackground2D(itrg,jass);
		    TH2D* hcorr = (TH2D*)GetJetCorrFunc2D_ZYAM(itrg,jass);
                    hcorr->Multiply(hbackground);
                    float max = hcorr->GetBinContent(hcorr->GetMaximumBin());
		    hcorr->SetAxisRange(ymin,max*1.3,"Z");
                    hcorr->SetAxisRange(detamin,detamax,"X");
                    hcorr->SetZTitle("#frac{1}{N^{trg}}#frac{d^{2}N}{d#Delta#eta#Delta#phi}");
		    return hcorr;
}

