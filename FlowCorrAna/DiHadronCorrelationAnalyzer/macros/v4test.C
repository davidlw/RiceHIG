#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
// #include "CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/DrawTick.C"
#include "TStyle.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "/net/hisrv0001/home/davidlw/useful_macros/Histograms.C"
// #include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvasNew.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"
// #include "makeMultiPanelCanvasNew.C"
#include <fstream>
#include <iostream>
#include <vector>
#include "/net/hisrv0001/home/dav2105/flow_pp/FourierDecomposition.C"
#include "/net/hisrv0001/home/dav2105/flow_pp/v23cent.C"
#include "/net/hisrv0001/home/dav2105/flow_pp/all_fourier.C"
#include "/net/hisrv0001/home/dav2105/flow_pp/outecc.C"

using namespace std;

// #include "TH1Function.C"

/*
static const int ptbinmax=3;
double ptmin[ptbinmax] = {0.1,1.0,3.0};
double ptmax[ptbinmax] = {1.0,3.0,100.0};
double pthistbin[ptbinmax+1] = {0.1,1.0,3.0,100.0};
TString pttitle[ptbinmax]={"0.1GeV/c<p_{T}<1.0GeV/c","1.0GeV/c<p_{T}<3.0GeV/c","p_{T}>3.0GeV/c"};
static const int nhistmax=4;
int nmin[nhistmax] = {2,35,90,110};
int nmax[nhistmax] = {35,90,110,1000};
double nhistbin[nhistmax+1] = {2,35,90,110,1000};
TString ntitle[nhistmax]={"N<35","35<N<90","90<N<110","N>110"};
TString eventtype[nhistmax]={"PPData_Minbias_7TeV","PPData_Minbias_7TeV","PPData_Minbias_7TeV","PPData_Minbias_7TeV"};
TString tag[nhistmax]={"MINBIAS_ALL_INCLNEWv2EFF1TRG1","MINBIAS_ALL_INCLNEWv2EFF1TRG1","TRIGGER70_Run2010A_INCLNEWv2EFF1TRG1","TRIGGER85_Run2010A_INCLNEWv2EFF1TRG1"};
TString eventtype_mc[nhistmax]={"PythiaReco_Minbias_7TeV","PythiaReco_Minbias_7TeV","PythiaReco_Minbias_7TeV","PythiaReco_Minbias_7TeV"};
TString tag_mc[nhistmax]={"PYTHIA8_MINBIAS_INCLNEWv2GENNSD","PYTHIA8_MINBIAS_INCLNEWv2GENNSD","PYTHIA8_HIGHMULT_INCLNEWv2GENNSD","PYTHIA8_HIGHMULT115_INCLNEWv2GENNSD"};
*/

static const int ptbinmax=5;
double ptmin[ptbinmax] = {0.1,1.0,2.0,3.0,3.0};
double ptmax[ptbinmax] = {1.0,2.0,3.0,100.0,4.0};
double pthistbin[ptbinmax+1] = {0.1,1.0,2.0,3.0,4.0,100.0};
TString pttitle[ptbinmax]={"0.1GeV/c<p_{T}<1.0GeV/c","1.0GeV/c<p_{T}<2.0GeV/c","2.0GeV/c<p_{T}<3.0GeV/c","3.0GeV/c<p_{T}<100.0GeV/c","3.0GeV/c<p_{T}<4.0GeV/c"};
static const int nhistmax=4;
int nmin[nhistmax] = {2,35,90,110};
int nmax[nhistmax] = {35,90,110,1000};
double nhistbin[nhistmax+1] = {2,35,90,110,1000};
TString ntitle[nhistmax]={"N<35","35 #leq N<90","90 #leq N<110","N #geq 110"};
TString eventtype[nhistmax]={"PPData_Minbias_7TeV","PPData_Minbias_7TeV","PPData_Minbias_7TeV","PPData_Minbias_7TeV"};
TString tag[nhistmax]={"MINBIAS_ALL_INCLNEWv3EFF1TRG1","MINBIAS_ALL_INCLNEWv3EFF1TRG1","TRIGGER70_ALL_INCLNEWv3EFF1TRG1","TRIGGER85_ALL_INCLNEWv3EFF1TRG1"}; 
TString eventtype_mc[nhistmax]={"PythiaReco_Minbias_7TeV","PythiaReco_Minbias_7TeV","PythiaReco_Minbias_7TeV","PythiaReco_Minbias_7TeV"};
TString tag_mc[nhistmax]={"PYTHIA8_MINBIAS_INCLNEWv3GENNSD","PYTHIA8_MINBIAS_INCLNEWv3GENNSD","PYTHIA8_HIGHMULT_INCLNEWv3GENNSD","PYTHIA8_HIGHMULTALL_INCLNEWv3GENNSD"};

double dphimin = 0;
double dphimax = PI/2;

// my global
TCanvas* c3;
TLine * zero = new TLine( 0.0, 0.0, 10.0, 0.0 );
int const num_cent = 14;
int min_cents[num_cent] = {0,2,4,6,8,10,12,14,16,20,24,28,32,36};
int max_cents[num_cent] = {2,4,6,8,10,12,14,16,20,24,28,32,36,40};
zero->SetLineStyle(9);
AllFourier * alf = new AllFourier();
EccTable * ect = new EccTable();

void compare_flow_pp_phi_multipad(double detamin, double detamax, bool IsSave=0)
{
  double zyamscale=16;
  TGraphErrors* gr_yield_pt[nhistmax];
  TGraphErrors* gr_yield_mult[ptbinmax];
  TGraphErrors* gr_yield_pt_mc[nhistmax];
  TGraphErrors* gr_yield_mult_mc[ptbinmax];

  TArrow* arrow[nhistmax][ptbinmax];
  TH1D* h[nhistmax][ptbinmax];
  TH1D* h_mc[nhistmax][ptbinmax];
  TH1D* h_signal[nhistmax][ptbinmax];
  TH1D* h_signal_mc[nhistmax][ptbinmax];
  TH1D* h_background[nhistmax][ptbinmax];
  TH1D* h_background_mc[nhistmax][ptbinmax];
  TH1D* h_zyam[nhistmax][ptbinmax];
  TH1D* h_zyam_mc[nhistmax][ptbinmax];
  TF1* fitfunc[nhistmax][ptbinmax];
  TF1* fitfunc_mc[nhistmax][ptbinmax];
  TLatex* xlatex[ptbinmax];
  TLatex* ylatex[nhistmax];

//  int xbindraw[4] = {1,3,5,7};
//  int ybindraw[4] = {1,6,7,8};
  int xbindraw[4] = {0,1,2,4};
  int ybindraw[4] = {0,1,2,3};

  TLegend* legend = new TLegend(0.25,0.8,0.9,0.9);
  legend->SetFillColor(0);

  TH1D* hdummy;

  TCanvas* c = new TCanvas("c","",700,700);
  makeMultiPanelCanvas(c,4,4,0.02,0.02,0.2,0.2,0.01);
  TCanvas* c1 = new TCanvas("c1","",700,700);
  makeMultiPanelCanvas(c1,4,4,0.02,0.02,0.2,0.2,0.01);
  TCanvas* c2 = new TCanvas("c2","",700,700);
  makeMultiPanelCanvas(c2,4,4,0.02,0.02,0.2,0.2,0.01);
  TCanvas* c3 = new TCanvas("c3","",700,700);
  makeMultiPanelCanvas(c3,4,4,0.02,0.02,0.2,0.2,0.01);
/*
  TCanvas* c = new TCanvas("c","",600,700);
  makeMultiPanelCanvas(c,3,4);
  TCanvas* c1 = new TCanvas("c1","",600,700);
  makeMultiPanelCanvas(c1,3,4);
*/
  for(int ihist=0;ihist<nhistmax;ihist++)
  {
    for(int iptbin=0;iptbin<ptbinmax;iptbin++)
    {
      TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",eventtype[ihist].Data(),eventtype[ihist].Data(),tag[ihist].Data(),nmin[ihist],nmax[ihist]);
      TString filename_mc = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",eventtype_mc[ihist].Data(),eventtype_mc[ihist].Data(),tag_mc[ihist].Data(),nmin[ihist],nmax[ihist]);
      h[ihist][iptbin] = (TH1D*)Get1DCFdPhi(filename.Data(),iptbin,iptbin,detamin,detamax);
      h[ihist][iptbin]->SetName(Form("corr_%d_%d",ihist,iptbin));
      h_mc[ihist][iptbin] = (TH1D*)Get1DCFdPhi(filename_mc.Data(),iptbin,iptbin,detamin,detamax);      
      h_mc[ihist][iptbin]->SetName(Form("corr_mc_%d_%d",ihist,iptbin));
      h[ihist][iptbin]->SetMarkerSize(h[ihist][iptbin]->GetMarkerSize()*0.7);
      h[ihist][iptbin]->SetMarkerColor(2);
      h_signal[ihist][iptbin] = (TH1D*)GetHist(filename.Data(),Form("signal_phi_long_trg%d_ass%d",iptbin,iptbin));
      h_signal[ihist][iptbin]->Scale(1.0/h_signal[ihist][iptbin]->Integral("width"));
      h_signal[ihist][iptbin]->SetMarkerSize(h_signal[ihist][iptbin]->GetMarkerSize()*0.7);
      h_signal[ihist][iptbin]->SetMarkerColor(kRed);
      h_signal_mc[ihist][iptbin] = (TH1D*)GetHist(filename_mc.Data(),Form("signal_phi_long_trg%d_ass%d",iptbin,iptbin));
      h_signal_mc[ihist][iptbin]->Scale(1.0/h_signal_mc[ihist][iptbin]->Integral("width"));
      h_signal_mc[ihist][iptbin]->SetMarkerSize(h_signal_mc[ihist][iptbin]->GetMarkerSize()*0.7);
      h_signal_mc[ihist][iptbin]->SetMarkerColor(kRed);
      h_background[ihist][iptbin] = (TH1D*)GetHist(filename.Data(),Form("background_phi_long_trg%d_ass%d",iptbin,iptbin));
      h_background[ihist][iptbin]->Scale(1.0/h_background[ihist][iptbin]->Integral("width"));
      h_background[ihist][iptbin]->SetMarkerSize(h_background[ihist][iptbin]->GetMarkerSize()*0.7);
      h_background[ihist][iptbin]->SetMarkerStyle(24);
      h_background_mc[ihist][iptbin] = (TH1D*)GetHist(filename_mc.Data(),Form("background_phi_long_trg%d_ass%d",iptbin,iptbin));
      h_background_mc[ihist][iptbin]->Scale(1.0/h_background_mc[ihist][iptbin]->Integral("width"));
      h_background_mc[ihist][iptbin]->SetMarkerSize(h_background_mc[ihist][iptbin]->GetMarkerSize()*0.7);
      h_background_mc[ihist][iptbin]->SetMarkerStyle(24);
      fitfunc[ihist][iptbin]=GetFitFunc_ZYAM(h[ihist][iptbin]);
      fitfunc[ihist][iptbin]->SetLineColor(kRed);
      fitfunc_mc[ihist][iptbin]=GetFitFunc_ZYAM_MC(h_mc[ihist][iptbin]);
      fitfunc_mc[ihist][iptbin]->SetLineColor(1);
      h_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM(h[ihist][iptbin]);
      h_zyam_mc[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_MC(h_mc[ihist][iptbin]);
    }
  }

/*
  const int nmultbin=4;
  const int nptbin=3;
*/
  const int nmultbin=4;
  const int nptbin=4;

  TLatex* latex_mult[nptbin];
  TLatex* latex_pt[nmultbin];
  TGraphErrors* gr_yield_pt_paper[nmultbin];
  TGraphErrors* gr_yield_mult_paper[nptbin];
  TGraphErrors* gr_yield_pt_mc_paper[nmultbin];
  TGraphErrors* gr_yield_mult_mc_paper[nptbin];
  int color_pt[nmultbin]={1,3,4,2};
  int color_n[nptbin]={1,2,4,3};
  for(int ihist=0;ihist<nmultbin;ihist++)
  {
    gr_yield_pt_paper[ihist] = new TGraphErrors(nptbin);
    gr_yield_pt_paper[ihist]->SetName(Form("gr_yield_pt_data_%d",ihist));
    gr_yield_pt_paper[ihist]->SetMarkerColor(color_pt[ihist]);
    gr_yield_pt_paper[ihist]->SetMarkerStyle(20);
    gr_yield_pt_paper[ihist]->SetMarkerSize(gr_yield_pt_paper[ihist]->GetMarkerSize());
    gr_yield_pt_mc_paper[ihist] = new TGraphErrors(nptbin);
    gr_yield_pt_mc_paper[ihist]->SetName(Form("gr_yield_pt_mc_%d",ihist));
    gr_yield_pt_mc_paper[ihist]->SetMarkerColor(color_pt[ihist]);
    gr_yield_pt_mc_paper[ihist]->SetMarkerStyle(25);
    gr_yield_pt_mc_paper[ihist]->SetMarkerSize(gr_yield_pt_mc_paper[ihist]->GetMarkerSize());
    latex_pt[ihist] = new TLatex();
  }
  for(int iptbin=0;iptbin<nptbin;iptbin++)
  {
    gr_yield_mult_paper[iptbin] = new TGraphErrors(nmultbin);
    gr_yield_mult_paper[iptbin]->SetName(Form("gr_yield_multbin_data_%d",iptbin));
    gr_yield_mult_paper[iptbin]->SetMarkerColor(color_n[iptbin]);
    gr_yield_mult_paper[iptbin]->SetMarkerStyle(20);
    gr_yield_mult_paper[iptbin]->SetMarkerSize(gr_yield_mult_paper[iptbin]->GetMarkerSize());
    gr_yield_mult_mc_paper[iptbin] = new TGraphErrors(nmultbin);
    gr_yield_mult_mc_paper[iptbin]->SetName(Form("gr_yield_multbin_mc_%d",iptbin));
    gr_yield_mult_mc_paper[iptbin]->SetMarkerColor(color_n[iptbin]);
    gr_yield_mult_mc_paper[iptbin]->SetMarkerStyle(25);
    gr_yield_mult_mc_paper[iptbin]->SetMarkerSize(gr_yield_mult_mc_paper[iptbin]->GetMarkerSize());
    latex_mult[iptbin] = new TLatex();
  }

  TCanvas* cc = new TCanvas("cc","",1300,500);
  makeMultiPanelCanvas(cc,4,1,0.02,0.02,0.2,0.2,0.01);
  TH1D* htmp_pt = new TH1D("tmp_pt",";p_{T}(GeV/c);Associated Yield",100,-0.2,5);
  htmp_pt->SetLineWidth(1);
  htmp_pt->GetXaxis()->CenterTitle();
  htmp_pt->GetYaxis()->CenterTitle();
  htmp_pt->SetMaximum(0.9/zyamscale);
  htmp_pt->SetMinimum(-0.1/zyamscale);
  cc->cd(1);
  TH1D* htmp_pt1 = (TH1D*)htmp_pt->Clone("tmp_pt1");
  htmp_pt1->GetXaxis()->SetTitleSize(htmp_pt1->GetXaxis()->GetTitleSize()*0.85);
  htmp_pt1->GetYaxis()->SetTitleSize(htmp_pt1->GetYaxis()->GetTitleSize()*0.85);
  htmp_pt1->GetXaxis()->SetTitleOffset(htmp_pt1->GetXaxis()->GetTitleOffset()*1.2);
  htmp_pt1->GetYaxis()->SetTitleOffset(htmp_pt1->GetYaxis()->GetTitleOffset()*1.2);
  htmp_pt1->Draw();
  cc->cd(2);
  TH1D* htmp_pt2 = (TH1D*)htmp_pt->Clone("tmp_pt2");
  htmp_pt2->Draw();
  cc->cd(3);
  TH1D* htmp_pt3 = (TH1D*)htmp_pt->Clone("tmp_pt3");
  htmp_pt3->Draw();
  cc->cd(4);
  TH1D* htmp_pt4 = (TH1D*)htmp_pt->Clone("tmp_pt4");
  htmp_pt4->Draw();

  TCanvas* cc1 = new TCanvas("cc1","",1200,500);
  makeMultiPanelCanvas(cc1,4,1,0.02,0.02,0.2,0.2,0.01); 
  TH1D* htmp_mult = new TH1D("tmp_mult",";N;Associated Yield",200,-1.9,130);
  htmp_mult->SetLineWidth(1);
  htmp_mult->GetXaxis()->CenterTitle();
  htmp_mult->GetYaxis()->CenterTitle();
  htmp_mult->SetMaximum(0.9/zyamscale);
  htmp_mult->SetMinimum(-0.1/zyamscale);
  htmp_mult->GetYaxis()->SetTitleOffset(htmp_mult->GetYaxis()->GetTitleOffset()*1.3);
  cc1->cd(1);
  TH1D* htmp_mult1 = (TH1D*)htmp_mult->Clone("tmp_mult1");
  htmp_mult1->GetXaxis()->SetTitleSize(htmp_mult1->GetXaxis()->GetTitleSize()*0.825);
  htmp_mult1->GetYaxis()->SetTitleSize(htmp_mult1->GetYaxis()->GetTitleSize()*0.85);
  htmp_mult1->GetXaxis()->SetTitleOffset(htmp_mult1->GetXaxis()->GetTitleOffset()*1.25);
  htmp_mult1->GetYaxis()->SetTitleOffset(htmp_mult1->GetYaxis()->GetTitleOffset()*1.2);
  htmp_mult1->GetXaxis()->SetLabelSize(htmp_mult1->GetXaxis()->GetLabelSize()*0.825);
  htmp_mult1->GetYaxis()->SetLabelSize(htmp_mult1->GetYaxis()->GetLabelSize()*0.85);
  htmp_mult1->GetXaxis()->SetLabelOffset(htmp_mult1->GetXaxis()->GetLabelOffset()*3.5);
  htmp_mult1->GetYaxis()->SetLabelOffset(htmp_mult1->GetYaxis()->GetLabelOffset()*3.5);
  htmp_mult1->Draw();
  cc1->cd(2);
  TH1D* htmp_mult2 = (TH1D*)htmp_mult->Clone("tmp_mult2");
  htmp_mult2->Draw();
  cc1->cd(3);
  TH1D* htmp_mult3 = (TH1D*)htmp_mult->Clone("tmp_mult3");
  htmp_mult3->Draw();
  cc1->cd(4);
  TH1D* htmp_mult4 = (TH1D*)htmp_mult->Clone("tmp_mult4");
  htmp_mult4->Draw();

  TFile* ftable = new TFile("./corr_phi_histograms.root","recreate");
  ofstream ff("Figure8.dat");
  ofstream ff1("Figure9_data.dat");
  ofstream ff2("Figure9_mc.dat");

  for(int iptbindraw=0;iptbindraw<nptbin;iptbindraw++)
  {
    int iptbin = xbindraw[iptbindraw];
    ff1<<"Data: "<<pttitle[iptbin]<<endl;
    ff1<<"<N> "<<"Yield "<<" stat. error"<<" syst. error"<<endl;
    ff2<<"PYTHIA8 MC: "<<pttitle[iptbin]<<endl;
    ff2<<"<N> "<<"Yield "<<" stat. error"<<" syst. error"<<endl;
    for(int ihistdraw=0;ihistdraw<nmultbin;ihistdraw++)
    {   
      int ihist = ybindraw[ihistdraw];
      TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",eventtype[ihist].Data(),eventtype[ihist].Data(),tag[ihist].Data(),nmin[ihist],nmax[ihist]);
      TString filename_mc = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",eventtype_mc[ihist].Data(),eventtype_mc[ihist].Data(),tag_mc[ihist].Data(),nmin[ihist],nmax[ihist]);
      if(ihistdraw!=(nmultbin-1) || iptbindraw!=0)
      {
        h[ihist][iptbin]->GetXaxis()->SetTitleSize(h[ihist][iptbin]->GetXaxis()->GetTitleSize()*1.1);
        h[ihist][iptbin]->GetYaxis()->SetTitleSize(h[ihist][iptbin]->GetYaxis()->GetTitleSize()*1.25);
        h[ihist][iptbin]->GetXaxis()->SetLabelSize(h[ihist][iptbin]->GetXaxis()->GetLabelSize()*1.05);
        h[ihist][iptbin]->GetYaxis()->SetLabelSize(h[ihist][iptbin]->GetYaxis()->GetLabelSize()*1.2);
        h[ihist][iptbin]->GetXaxis()->SetLabelOffset(h[ihist][iptbin]->GetXaxis()->GetLabelOffset()*0.8);
        h[ihist][iptbin]->GetYaxis()->SetLabelOffset(h[ihist][iptbin]->GetYaxis()->GetLabelOffset()*0.8);
        h[ihist][iptbin]->GetXaxis()->SetTitleOffset(h[ihist][iptbin]->GetXaxis()->GetTitleOffset()*0.9);
        h[ihist][iptbin]->GetYaxis()->SetTitleOffset(h[ihist][iptbin]->GetYaxis()->GetTitleOffset()*0.8);
     }
      c->cd(ihistdraw*nptbin+iptbindraw+1);
      hdummy = (TH1D*)h[ihist][iptbin]->Clone(Form("dummy_%d_%d",ihist,iptbin));
      hdummy->SetAxisRange(0,PI,"X");
      hdummy->SetLineWidth(1);
      hdummy->Reset();
      hdummy->Draw();
      h[ihist][iptbin]->SetName(Form("corr_phi_mult%d_pt%d",ihist,iptbin));
      h_mc[ihist][iptbin]->SetName(Form("corr_mc_phi_mult%d_pt%d",ihist,iptbin));
      if(iptbin==4) h[ihist][iptbin]->SetName(Form("corr_phi_mult%d_pt3",ihist));
      if(iptbin==4) h_mc[ihist][iptbin]->SetName(Form("corr_mc_phi_mult%d_pt3",ihist));
      h[ihist][iptbin]->Draw("PESAME");
//      fitfunc[ihist][iptbin]->Draw("LSAME");
      h_mc[ihist][iptbin]->Draw("HISTSAME");
//      fitfunc_mc[ihist][iptbin]->Draw("LSAME");
      double zyam = fitfunc[ihist][iptbin]->GetParameter(2);
      double offset = fitfunc[ihist][iptbin]->GetParameter(0);
      arrow[ihist][iptbin] = new TArrow();
      arrow[ihist][iptbin]->SetLineColor(kRed);
      arrow[ihist][iptbin]->SetLineWidth(3);
//      arrow[ihist][iptbin]->DrawArrow(zyam,offset-0.5,zyam,offset,0.015,"|>");
      // data yield
      TH1D* hpt = (TH1D*)GetHist(filename,Form("pt_trg_%d",iptbin));
      TH1D* hmult = (TH1D*)GetHist(filename,Form("multrawall"));
      hmult->SetAxisRange(2,10000,"X");
      TH2D* hbackground = (TH2D*)GetHist(filename,Form("background_trg%d_ass%d",iptbin,iptbin));
      double scale = 2*hbackground->Integral(hbackground->GetXaxis()->FindBin(detamin),hbackground->GetXaxis()->FindBin(detamax),-1,-1)/hbackground->Integral();
      double zyamminimum=fitfunc[ihist][iptbin]->GetParameter(2);
      double yielderror=0;
      double yield = h_zyam[ihist][iptbin]->IntegralAndError(h_zyam[ihist][iptbin]->FindBin(-zyamminimum),h_zyam[ihist][iptbin]->FindBin(zyamminimum),yielderror)/zyamscale;
//      double yield = h_zyam[ihist][iptbin]->Integral(h_zyam[ihist][iptbin]->FindBin(-1.0),h_zyam[ihist][iptbin]->FindBin(1.0));
      yielderror=yielderror*1.8/zyamscale;
      gr_yield_pt_paper[ihistdraw]->SetPoint(iptbindraw,hpt->GetMean(),yield*scale);
      gr_yield_pt_paper[ihistdraw]->SetPointError(iptbindraw,0,yielderror*scale);
      gr_yield_mult_paper[iptbindraw]->SetPoint(ihistdraw,hmult->GetMean(),yield*scale);
      gr_yield_mult_paper[iptbindraw]->SetPointError(ihistdraw,0,yielderror*scale);
      cc->cd(ihistdraw+1);
      double errorbar = sqrt(0.04*0.04/zyamscale/zyamscale+yield*scale*0.14*yield*scale*0.14);
      DrawTick(yield*scale,errorbar,errorbar,hpt->GetMean(),0.004/zyamscale,0.2,color_pt[ihistdraw]);
      cc1->cd(iptbindraw+1);
      DrawTick(yield*scale,errorbar,errorbar,hmult->GetMean(),0.004/zyamscale,4.8,color_n[iptbindraw]);
      ff1<<Form("%.4f",hmult->GetMean())<<" "<<Form("%.4f",yield*scale)<<" "<<Form("%.4f",yielderror*scale)<<" "<<Form("%.4f",errorbar)<<endl; 

      // mc yield
      TH1D* hpt_mc = (TH1D*)GetHist(filename_mc,Form("pt_trg_%d",iptbin));
      TH1D* hmult_mc = (TH1D*)GetHist(filename_mc,Form("multrawall"));
      hmult_mc->SetAxisRange(2,10000,"X");
      TH2D* hbackground_mc = (TH2D*)GetHist(filename_mc,Form("background_trg%d_ass%d",iptbin,iptbin));
      double scale_mc = 2*hbackground_mc->Integral(hbackground_mc->GetXaxis()->FindBin(detamin),hbackground_mc->GetXaxis()->FindBin(detamax),-1,-1)/hbackground_mc->Integral();
      double zyamminimum_mc=fitfunc_mc[ihist][iptbin]->GetParameter(2);
      double yielderror_mc=0;
      double yield_mc = h_zyam_mc[ihist][iptbin]->IntegralAndError(h_zyam_mc[ihist][iptbin]->FindBin(-zyamminimum_mc),h_zyam_mc[ihist][iptbin]->FindBin(zyamminimum_mc),yielderror_mc)/zyamscale;
      yielderror_mc=yielderror_mc*1.8/zyamscale;
//      double yield_mc = h_zyam_mc[ihist][iptbin]->Integral(h_zyam_mc[ihist][iptbin]->FindBin(-1.0),h_zyam_mc[ihist][iptbin]->FindBin(1.0));
      gr_yield_pt_mc_paper[ihistdraw]->SetPoint(iptbindraw,hpt_mc->GetMean(),yield_mc*scale_mc);
      gr_yield_pt_mc_paper[ihistdraw]->SetPointError(iptbindraw,0,yielderror_mc*scale_mc);
      gr_yield_mult_mc_paper[iptbindraw]->SetPoint(ihistdraw,hmult_mc->GetMean(),yield_mc*scale_mc);
      gr_yield_mult_mc_paper[iptbindraw]->SetPointError(ihistdraw,0,yielderror_mc*scale_mc);
      ff2<<Form("%.4f",hmult_mc->GetMean())<<" "<<Form("%.4f",yield_mc*scale_mc)<<" "<<Form("%.4f",yielderror_mc*scale_mc)<<" "<<Form("%.4f",0)<<endl;

      c1->cd(ihistdraw*nptbin+iptbindraw+1);
      hdummy_zyam = (TH1D*)h_zyam[0][0]->Clone("dummy_zyam");
      hdummy_zyam->SetAxisRange(0,PI,"X");
      hdummy_zyam->SetLineWidth(1);
      hdummy_zyam->Reset();
      hdummy_zyam->Draw();
      h_zyam[ihist][iptbin]->Draw("PESAME");
      h_zyam_mc[ihist][iptbin]->Draw("HISTSAME");

      c2->cd(ihistdraw*nptbin+iptbindraw+1);
//      h_signal[ihist][iptbin]->Scale(hmult->GetMean()-1);
      h_signal[ihist][iptbin]->SetAxisRange(h_signal[ihist][iptbin]->GetMinimum()-0.005,h_signal[ihist][iptbin]->GetMaximum()+0.005,"Y");
      h_signal[ihist][iptbin]->SetAxisRange(0,PI,"X");
      h_signal[ihist][iptbin]->Draw("PE");
//      h_background[ihist][iptbin]->Scale(hmult->GetMean()-1);
      h_background[ihist][iptbin]->Draw("PESAME");

      c3->cd(ihistdraw*nptbin+iptbindraw+1);
//      h_signal[ihist][iptbin]->Scale(hmult->GetMean()-1);
      h_signal_mc[ihist][iptbin]->SetAxisRange(h_signal_mc[ihist][iptbin]->GetMinimum()-0.005,h_signal_mc[ihist][iptbin]->GetMaximum()+0.005,"Y");
      h_signal_mc[ihist][iptbin]->SetAxisRange(0,PI,"X");
      h_signal_mc[ihist][iptbin]->Draw("PE");//      h_background[ihist][iptbin]->Scale(hmult->GetMean()-1);
      h_background_mc[ihist][iptbin]->Draw("PESAME");

      if(ihistdraw==0) 
      {
        xlatex[iptbin] = new TLatex();
        if(iptbindraw==0) xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*1.7);
        else xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*1.7);
        c->cd(ihistdraw*nptbin+iptbindraw+1);
        xlatex[iptbin]->DrawLatex(-1.0+1.1,1.5,pttitle[iptbin]);
        c1->cd(ihistdraw*nptbin+iptbindraw+1);
        xlatex[iptbin]->DrawLatex(-1.0+1.1,1.5,pttitle[iptbin]);
        c2->cd(ihistdraw*nptbin+iptbindraw+1);
        xlatex[iptbin]->DrawLatex(-1.0+1.1,h_signal[ihist][iptbin]->GetMaximum()-0.015,pttitle[iptbin]);
        c3->cd(ihistdraw*nptbin+iptbindraw+1);
        xlatex[iptbin]->DrawLatex(-1.0+1.1,h_signal_mc[ihist][iptbin]->GetMaximum()-0.02,pttitle[iptbin]);
      }
      if(iptbindraw==0) 
      {
        ylatex[ihist] = new TLatex();
        if(ihistdraw==(nmultbin-1)) ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*1.7);
        else ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*2);
        c->cd(ihistdraw*nptbin+iptbindraw+1);
        ylatex[ihist]->DrawLatex(-1.0+1.1,1.2,ntitle[ihist]);
        c1->cd(ihistdraw*nptbin+iptbindraw+1);
        ylatex[ihist]->DrawLatex(-1.0+1.1,1.2,ntitle[ihist]);
        c2->cd(ihistdraw*nptbin+iptbindraw+1);
        ylatex[ihist]->DrawLatex(-1.0+1.1,0.165,ntitle[ihist]);
        c3->cd(ihistdraw*nptbin+iptbindraw+1);
        ylatex[ihist]->DrawLatex(-1.0+1.1,0.165,ntitle[ihist]);
      } 
      ff<<"Data: "<<ntitle[ihist]<<" "<<pttitle[iptbin]<<endl;
      ff<<"Delta-phi "<<"R "<<"stat. error"<<endl;
      for(int aa = 1; aa<=h[ihist][iptbin]->GetNbinsX(); aa++)
        if(h[ihist][iptbin]->GetXaxis()->GetBinCenter(aa)>-0.0001 && h[ihist][iptbin]->GetXaxis()->GetBinCenter(aa)<3.1417) ff<<Form("%.4f",h[ihist][iptbin]->GetXaxis()->GetBinCenter(aa))<<" "<<Form("%.4f",h[ihist][iptbin]->GetBinContent(aa))<<" "<<Form("%.4f",h[ihist][iptbin]->GetBinError(aa))<<endl;
      ff<<endl;
      ff<<"PYTHIA8 MC: "<<ntitle[ihist]<<" "<<pttitle[iptbin]<<endl;
      ff<<"Delta-phi "<<"R "<<"stat. error"<<endl;
      for(int aa = 1; aa<=h[ihist][iptbin]->GetNbinsX(); aa++)
        if(h[ihist][iptbin]->GetXaxis()->GetBinCenter(aa)>-0.0001 && h[ihist][iptbin]->GetXaxis()->GetBinCenter(aa)<3.1417) ff<<Form("%.4f",h_mc[ihist][iptbin]->GetXaxis()->GetBinCenter(aa))<<" "<<Form("%.4f",h_mc[ihist][iptbin]->GetBinContent(aa))<<" "<<Form("%.4f",h_mc[ihist][iptbin]->GetBinError(aa))<<endl;
      ff<<endl;
      ff<<endl;

      ftable->cd();
      h[ihist][iptbin]->Write();
      h_mc[ihist][iptbin]->Write(); 
    }
    ff1<<endl;
    ff1<<endl;
    ff2<<endl;
    ff2<<endl;
  }

  TLatex* latexdeta = new TLatex();
  latexdeta->SetTextSize(latexdeta->GetTextSize()*2.5);
  c->cd(4);
  latexdeta->DrawLatex(-1.0+1.2,1.0,Form("%.1f<|#Delta#eta|<%.1f",detamin,detamax));
  c1->cd(4);
  latexdeta->DrawLatex(-1.0+1.2,1.5,Form("%.1f<|#Delta#eta|<%.1f",detamin,detamax));

  c->cd(1);
  TLegend* l = new TLegend(0.49,0.57,0.99,0.83);
  l->SetFillColor(0);
  l->AddEntry(h[0][0],"CMS pp","P"); 
  l->AddEntry(h_mc[0][0],"PYTHIA8","L");           
  l->Draw("same");

  c2->cd(1);
  TLegend* l2 = new TLegend(0.23,0.67,0.93,0.93);
  l2->SetFillColor(0);
  l2->AddEntry(h_signal[0][0],"Data Signal","P");
  l2->AddEntry(h_background[0][0],"Data Background","P");    
  l2->Draw("same");

  c3->cd(1);
  TLegend* l3 = new TLegend(0.20,0.68,0.96,0.96);
  l3->SetFillColor(0);
  l3->AddEntry(h_signal_mc[0][0],"PYTHIA8 Signal","P");
  l3->AddEntry(h_background_mc[0][0],"PYTHIA8 Background","P");
  l3->Draw("same");

  cc->cd(1);
  latex_pt[0]->DrawLatex(2.5,0.8/zyamscale,ntitle[ybindraw[0]]);
  gr_yield_pt_paper[0]->Draw("PESAME");
  gr_yield_pt_mc_paper[0]->Draw("PESAME");
  cc->cd(2);
  latex_pt[1]->SetTextSize(latex_pt[1]->GetTextSize()*1.3);
  latex_pt[1]->DrawLatex(2.5,0.8/zyamscale,ntitle[ybindraw[1]]);
  gr_yield_pt_paper[1]->Draw("PESAME");
  gr_yield_pt_mc_paper[1]->Draw("PESAME");
  cc->cd(3);
  latex_pt[2]->SetTextSize(latex_pt[2]->GetTextSize()*1.3);
  latex_pt[2]->DrawLatex(2.5,0.8/zyamscale,ntitle[ybindraw[2]]);
  gr_yield_pt_paper[2]->Draw("PESAME");
  gr_yield_pt_mc_paper[2]->Draw("PESAME");
  cc->cd(4);
  latex_pt[3]->SetTextSize(latex_pt[3]->GetTextSize()*1.3);
  latex_pt[3]->DrawLatex(2.5,0.8/zyamscale,ntitle[ybindraw[3]]);
  gr_yield_pt_paper[3]->Draw("PESAME");
  gr_yield_pt_mc_paper[3]->Draw("PESAME");
  cc->cd(1);
  TLegend* legend_yield_pt = new TLegend(0.27,0.70,0.85,0.85);
  legend_yield_pt->SetFillColor(0);
  legend_yield_pt->AddEntry(gr_yield_pt_paper[0],"CMS pp 7TeV","P");
  legend_yield_pt->AddEntry(gr_yield_pt_mc_paper[0],"PYTHIA8 7TeV","P");
  legend_yield_pt->Draw();

  cc1->cd(1);
  latex_mult[0]->DrawLatex(10,0.8/zyamscale,pttitle[xbindraw[0]]);
  gr_yield_mult_paper[0]->Draw("PESAME");
  gr_yield_mult_mc_paper[0]->Draw("PESAME");
  cc1->cd(2);
  latex_mult[1]->SetTextSize(latex_mult[1]->GetTextSize()*1.3);
  latex_mult[1]->DrawLatex(10,0.8/zyamscale,pttitle[xbindraw[1]]);
  gr_yield_mult_paper[1]->Draw("PESAME");
  gr_yield_mult_mc_paper[1]->Draw("PESAME");
  cc1->cd(3);
  latex_mult[2]->SetTextSize(latex_mult[2]->GetTextSize()*1.3);
  latex_mult[2]->DrawLatex(10,0.8/zyamscale,pttitle[xbindraw[2]]);
  gr_yield_mult_paper[2]->Draw("PESAME");
  gr_yield_mult_mc_paper[2]->Draw("PESAME");
  cc1->cd(4);
  latex_mult[3]->SetTextSize(latex_mult[3]->GetTextSize()*1.3);
  latex_mult[3]->DrawLatex(10,0.8/zyamscale,pttitle[xbindraw[3]]);
  gr_yield_mult_paper[3]->Draw("PESAME");
  gr_yield_mult_mc_paper[3]->Draw("PESAME");
  cc1->cd(1);
  TLegend* legend_yield_mult = new TLegend(0.27,0.70,0.85,0.85);
  legend_yield_mult->SetFillColor(0);
  legend_yield_mult->AddEntry(gr_yield_mult_paper[0],"CMS pp 7TeV","P");
  legend_yield_mult->AddEntry(gr_yield_mult_mc_paper[0],"PYTHIA8 7TeV","P");
  legend_yield_mult->Draw();
/*
  TFile* fout = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/final/gr_yield_std.root","recreate");
  cc1->Write();
  cc->Write();
  fout->Close();
*/

  TCanvas* ctmp = new TCanvas("ctmp","",500,500);
  hdummy->Draw();
  TH1D* h_clone = (TH1D*)h[3][1]->Clone("h_clone");
  h_clone->SetMarkerSize(h_clone->GetMarkerSize()*1.5);
  h_clone->Draw("PESAME");
  fitfunc[3][1]->Draw("LSAME");
  h_mc[3][1]->Draw("histsame");

  if(IsSave)
  {
    c->cd();
    c->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/compare_corr_phi_%s_dphi%.0f-%.0f_highmult_4by4.gif",eventtype[0].Data(),detamin,detamax));
    c->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/compare_corr_phi_%s_dphi%.0f-%.0f_highmult_4by4.eps",eventtype[0].Data(),detamin,detamax));
    c2->cd();
    c2->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/signalbackground_phi_%s_dphi%.0f-%.0f_highmult_4by4.gif",eventtype[0].Data(),detamin,detamax));
    c2->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/signalbackground_phi_%s_dphi%.0f-%.0f_highmult_4by4.eps",eventtype[0].Data(),detamin,detamax));
    c3->cd();
    c3->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/signalbackground_phi_%s_dphi%.0f-%.0f_highmult_4by4_mc.gif",eventtype[0].Data(),detamin,detamax));
    c3->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/signalbackground_phi_%s_dphi%.0f-%.0f_highmult_4by4_mc.eps",eventtype[0].Data(),detamin,detamax));
//    c1->cd();
//    c1->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/compare_corr_phi_%s_dphi%.0f-%.0f_highmult_zyam.gif",eventtype[0].Data(),detamin,detamax));
//    c1->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/compare_corr_phi_%s_dphi%.0f-%.0f_highmult_zyam.eps",eventtype[0].Data(),detamin,detamax));
    cc->cd();
    cc->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/yieldvspt_%s_dphi%.0f-%.0f_4by4.gif",eventtype[0].Data(),detamin,detamax));
    cc->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/yieldvspt_%s_dphi%.0f-%.0f_4by4.eps",eventtype[0].Data(),detamin,detamax));
    cc1->cd();
    cc1->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/yieldvsn_%s_dphi%.0f-%.0f_4by4.gif",eventtype[0].Data(),detamin,detamax));
    cc1->Print(Form("/net/hisrv0001/home/davidlw/pic/flow_pp/paper/yieldvsn_%s_dphi%.0f-%.0f_4by4.eps",eventtype[0].Data(),detamin,detamax));
  }
}

template <class T>
T* compare_flow_pp_phi_multipad_pt(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_ReTracking_INCLEFF1TRG1v5NEW", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, double detamin=2.0, double detamax=4.8,  bool IsDraw=1, bool IsSave=0, int ret=0)
{
  gStyle->SetTitleSize(0.12,"t");//  gStyle->SetTitleX(0.8);
  gStyle->SetTitleW(0.8);

/*
  double zyamscale=16;
  const int ntrgptbins = 11;
  const int nassptbins = 11;
  int trgptbin[ntrgptbins] = {0,1,2,3,4,5,6,7,8,9,10};
  int assptbin[nassptbins] = {0,1,2,3,4,5,6,7,8,9,10};
  double ptmin[12]={0.1,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,1.0};
  double ptmax[12]={1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,3.0};
*/

  const int ntrgptbins = 4;
  const int nassptbins = 4;
  int trgptbin[ntrgptbins] = {0,1,2,3};
  int assptbin[nassptbins] = {0,1,2,3};
  double ptmin[8]={0,1.0,2.0,4.0,6.0,8.0,10.0,20.0};
  double ptmax[8]={1.0,2.0,4.0,6.0,8.0,10.0,20.0,100.0};

  TH1D* h_zyam[ntrgptbins][nassptbins];
  TF1*  fitfunc[ntrgptbins][nassptbins];
  TH1D*** h;
  h=new TH1D**[nassptbins];
  for(int i=0;i<ntrgptbins;i++) {
     h[i]=new TH1D*[nassptbins];
  }

  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);

  TCanvas* c = 0;
  if(IsDraw)
  {
    c = new TCanvas("c","",1000,700);
    makeMultiPanelCanvas(c,ntrgptbins,nassptbins,0.02,0.02,0.2,0.2,0.01);
  }

  TGraphErrors* gr_yield_pt_paper = new TGraphErrors(ntrgptbins);
  TGraphErrors* gr_yield_pt_trgptbin[ntrgptbins];

  for(int itrg = 0; itrg<ntrgptbins; itrg++)
  {
    gr_yield_pt_trgptbin[itrg] = new TGraphErrors(itrg+1);
    for(int jass = 0; jass<nassptbins; jass++)
    {
      if(itrg<jass) continue;
      if(jass!=0) continue;
//      h[itrg][jass] = (TH1D*)Get1DSignaldPhi(filename.Data(),trgptbin[itrg],assptbin[jass],detamin,detamax);
      h[itrg][jass] = (TH1D*)Get1DCFdPhiv3(filename.Data(),trgptbin[itrg],assptbin[jass],detamin,detamax);
//      h[itrg][jass] = (TH1D*)Get1DCFdPhi(filename.Data(),trgptbin[itrg],assptbin[jass],detamin,detamax);
//      h[itrg][jass]->SetTitle(Form("%.1f<p^{trg}_{T}<%.1f,%.1f<p^{ass}_{T}<%.1f",ptmin[trgptbin[itrg]],ptmax[trgptbin[itrg]],ptmin[assptbin[jass]],ptmax[assptbin[jass]]));
//      h[itrg][jass]->GetZaxis()->SetTitleSize(0.8*h[ihist]->GetZaxis()->GetTitleSize());
//      h[itrg][jass]->SetAxisRange(zaxismin[ihist],zaxismax[ihist],"Z");
      h[itrg][jass]->SetMarkerColor(kRed);
//      h[itrg][jass]->SetAxisRange(-2.5,4,"Y");
//      h[itrg][jass]->SetAxisRange(-10,16,"Y");

      // PbPb ZYAM
       
      fitfunc[itrg][jass]=GetFitFunc_ZYAM(h[itrg][jass]);
      fitfunc[itrg][jass]->SetLineColor(kRed);
      h_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM(h[itrg][jass]);
      TH1D* hpt = (TH1D*)GetHist(filename,Form("ptcorr_trg_%d",trgptbin[itrg]));
      double zyamminimum=fitfunc[itrg][jass]->GetParameter(2);
      double yielderror=0;
      double yield = h_zyam[itrg][jass]->IntegralAndError(h_zyam[itrg][jass]->FindBin(-zyamminimum),h_zyam[itrg][jass]->FindBin(zyamminimum),yielderror,"width")/2./zyamminimum;
//      double yield = h_zyam[itrg][jass]->IntegralAndError(h_zyam[itrg][jass]->FindBin(-zyamminimum),h_zyam[itrg][jass]->FindBin(zyamminimum),yielderror,"width")/2./zyamminimum;
      yielderror=yielderror/2./zyamminimum;
      gr_yield_pt_trgptbin[jass]->SetPoint(itrg,hpt->GetMean(),yield);
      gr_yield_pt_trgptbin[jass]->SetPointError(itrg,0,yielderror);
      if(jass==0)
      {
        gr_yield_pt_paper->SetPoint(itrg,hpt->GetMean(),yield);
        gr_yield_pt_paper->SetPointError(itrg,0,yielderror);
      }

      // pp ZYAM
/*
      fitfunc[itrg][jass]=GetFitFunc_ZYAM(h[itrg][jass]);
      fitfunc[itrg][jass]->SetLineColor(kRed);
      h_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM(h[itrg][jass]);
      TH1D* hpt = (TH1D*)GetHist(filename,Form("ptcorr_ass_%d",assptbin[jass]));
      TH1D* hmult = (TH1D*)GetHist(filename,Form("multcorr_ass_%d",assptbin[jass]));
      TH2D* hbackground = (TH2D*)GetHist(filename,Form("background_trg%d_ass%d",trgptbin[itrg],assptbin[jass]));
      hmult->SetAxisRange(2,10000,"X");
      double mult = hmult->GetMean();
      double scale = 2*hbackground->Integral(hbackground->GetXaxis()->FindBin(detamin),hbackground->GetXaxis()->FindBin(detamax),-1,-1)/hbackground->Integral();
      double zyamminimum=fitfunc[itrg][jass]->GetParameter(2);
      double yielderror=0;
      double yield = h_zyam[itrg][jass]->IntegralAndError(h_zyam[itrg][jass]->FindBin(-zyamminimum),h_zyam[itrg][jass]->FindBin(zyamminimum),yielderror)/zyamscale;
      yielderror=yielderror*1.8/zyamscale;
      gr_yield_pt_trgptbin[itrg]->SetPoint(jass,hpt->GetMean(),yield*scale);
      gr_yield_pt_trgptbin[itrg]->SetPointError(jass,0,yielderror*scale);
      if(itrg==jass)
      {
        gr_yield_pt_paper->SetPoint(itrg,hpt->GetMean(),yield*scale);
        gr_yield_pt_paper->SetPointError(itrg,0,yielderror*scale);
      }
*/
      if(IsDraw)
      {
        c->cd(itrg*nassptbins+jass+1);
        h[itrg][jass]->Draw("PE");
        fitfunc[itrg][jass]->Draw("Lsame");
      }
    }
  }

  if(IsDraw) 
  {
    TCanvas* c_gr = new TCanvas("c_gr","",600,600);
    TH2D* htmp_pt = new TH2D("tmp_pt",";p_{T}(GeV/c);Associated Yield",100,-0.2,6,100,-0.05,0.2);
    htmp_pt->SetLineWidth(1);
    htmp_pt->GetXaxis()->CenterTitle();
    htmp_pt->GetYaxis()->CenterTitle();
    htmp_pt->Draw("");
    gr_yield_pt_paper->Draw("PESAME");

    TCanvas* c_gr1 = new TCanvas("c_gr1","",600,600);
    TH2D* htmp_pt1 = new TH2D("tmp_pt1",";p_{T}(GeV/c);Associated Yield",100,-0.2,6,100,-0.05,0.2);
    htmp_pt1->SetLineWidth(1);
    htmp_pt1->GetXaxis()->CenterTitle();
    htmp_pt1->GetYaxis()->CenterTitle();
    htmp_pt1->Draw("");
    gr_yield_pt_trgptbin[4]->SetMarkerColor(kRed);
    gr_yield_pt_trgptbin[5]->SetMarkerColor(kBlue);
    gr_yield_pt_trgptbin[6]->SetMarkerColor(kGreen);
    gr_yield_pt_trgptbin[7]->SetMarkerColor(1);
    gr_yield_pt_trgptbin[4]->Draw("PESAME");
    gr_yield_pt_trgptbin[5]->Draw("PESAME");
    gr_yield_pt_trgptbin[6]->Draw("PESAME");
    gr_yield_pt_trgptbin[7]->Draw("PESAME");
  }
  
  if(ret==0) return h;
  if(ret==1) return gr_yield_pt_paper;
}

void draw_signalbackground_2D(TString eventtype1="HIData_Minbias_2760GeV", TString tag1="All_INCLEFF1v5", int nmin=-1, int nmax=-1, int centmin=0, int centmax=1, int ptmin=3, int ptmax=2, bool IsSave=0)
{
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TH2D* hsignal = (TH2D*)Get2DSignal(filename.Data(),ptmin,ptmax);
  TH2D* hbackground = (TH2D*)Get2DBackground(filename.Data(),ptmin,ptmax);

  TCanvas* c = new TCanvas("c","",800,400);
  c->Divide(2,1);
  c->cd(1);
//  c->GetPad(1)->SetTheta(60.839);
//  c->GetPad(1)->SetPhi(38.0172);
  hsignal->SetAxisRange(0,5.5,"Z");
  hsignal->Draw("surf1 fb");
  c->cd(2);
//  c->GetPad(2)->SetTheta(60.839);
//  c->GetPad(2)->SetPhi(38.0172);
  hbackground->SetAxisRange(0,5,"Z");
  hbackground->Draw("surf1 fb");

  if(IsSave) SaveCanvas(c,"HI/corr","sigbkg_pttrg4-6_ptass2-4_cent0-2");
}

create_lookup_table()
{
  // int min_cents[14] = {0,2,4,6,8,10,12,14,16,20,24,28,32,36};
  // int max_cents[14] = {2,4,6,8,10,12,14,16,20,24,28,32,36,40};
  for(int i = 0 ; i < 14 ; ++i)
  {
    save_all(min_cents[i],max_cents[i],7,103,"AllPhysics_INCLEFF1v6",-4,4);
  }
}

void save_all(int centmin, int centmax, int npt = 7, int centfactor = 1 , string tag = "AllPhysics_INCLEFF1v6", string datatype = "HIData_Minbias_2760GeV", double etamin = 2.0, double etamax = 4.0)
{
  ofstream myijk;
  myijk.open ("ijk.txt", ios::app);
  for(int i = 0 ; i < npt ; ++i)
  {
    // for(int j = 0 ; j <= i ; ++j)
    for(int j = 0 ; j < npt ; ++j)
    {
      std::vector<double> tmp_corr = find_ij(i,j,centmin,centmax,tag,datatype,etamin,etamax);
      for(int k = 0 ; k < 6 ; ++k)
      {
        myijk <<i<<" "<<j<<" "<<k<<" "<<centmin*centfactor<<" "<<centmax*centfactor<<" "<<tmp_corr[k]<<endl;
      }
      cout<<"i j: "<<i<<" "<<j<<endl;
    }
  }
  myijk.close();
  
  ofstream myijk_err;
  myijk_err.open ("ijk_err.txt", ios::app);
  for(int i = 0 ; i < npt ; ++i)
  {
    // for(int j = 0 ; j <= i ; ++j)
    for(int j = 0 ; j < npt ; ++j)
    {
      std::vector<double> tmp_corr = find_ij_err(i,j,centmin,centmax,tag,datatype,etamin,etamax);
      for(int k = 0 ; k < 6 ; ++k)
      {
        myijk_err <<i<<" "<<j<<" "<<k<<" "<<centmin*centfactor<<" "<<centmax*centfactor<<" "<<tmp_corr[k]<<endl;
      }
      cout<<"i j: "<<i<<" "<<j<<endl;
    }
  }
  myijk_err.close();  
}

void save_fourier(int centmin, int centmax, int npt = 7)
{
  ofstream myfile;
  myfile.open ("ijk.txt", ios::app);
  for(int i = 0 ; i < npt ; ++i)
  {
    for(int j = 0 ; j < npt ; ++j)
    {
      std::vector<double> tmp_corr = find_ij(i,j,centmin,centmax);
      for(int k = 0 ; k < 6 ; ++k)
      {
        myfile <<i<<" "<<j<<" "<<k<<" "<<centmin<<" "<<centmax<<" "<<tmp_corr[k]<<endl;
      }
      cout<<"i j: "<<i<<" "<<j<<endl;
    }
  }
  myfile.close();
}

void save_err(int centmin, int centmax, int npt = 7)
{
  ofstream myfile;
  myfile.open ("ijk_err.txt", ios::app);
  for(int i = 0 ; i < npt ; ++i)
  {
    for(int j = 0 ; j < npt ; ++j)
    {
      std::vector<double> tmp_corr = find_ij_err(i,j,centmin,centmax);
      for(int k = 0 ; k < 6 ; ++k)
      {
        myfile <<i<<" "<<j<<" "<<k<<" "<<centmin<<" "<<centmax<<" "<<tmp_corr[k]<<endl;
      }
      cout<<"i j: "<<i<<" "<<j<<endl;
    }
  }
  myfile.close();
}

void surface_plot(int k, int centmin, int centmax, int div = 0, int save = 1)
{
  // TCanvas * c1 = new TCanvas();
  //get big Vn for each combination of trig and ass bins (4x4 or 6x6) and plot it 
  //in a 2D hist
  // TH2D * vn_mat = new TH2D("vn_mat"," ;p_{T};p_{T}",6,0.1,9.9,6,0.1,9.9);
  TH2D * vn_mat = new TH2D("vn_mat"," ;p_{T}^{trg} bin;p_{T}^{assoc} bin",6,0.5,6.5,6,0.5,6.5);
  
  // double pt_vector[6] = {1.349,2.342,3.354,4.597,6.757,8.830};
  double pt_vector[6] = {1,2,3,4,5,6};
  int pttrg = 0 , ptass = 0 ; 
  for(int i = 0 ; i < 6 ; ++i)
  {
    for(int j = 0 ; j < 6 ; ++j)
    {
      // if(i==5 && j==5) continue;
      if(j<i)
      {
        pttrg = i;
        ptass = j;
      }
      else
      {
        ptass = i;
        pttrg = j;
      }
      double scale = 1.0;
      if(centmin==-1 && centmax==-1)
        scale = find_ijk(pttrg,ptass,0,centmin,centmax)/find_ijk(pttrg,ptass,0,6,8);

      if(div==0)
        vn_mat->Fill(pt_vector[i],pt_vector[j],find_ijk(pttrg,ptass,k,centmin,centmax)*scale);
      else
        vn_mat->Fill(pt_vector[i],pt_vector[j],find_ijk(pttrg,ptass,k,centmin,centmax)/find_ijk(i,0,k,centmin,centmax)*scale);
      // cout<<i<<" "<<j<<" "<<vn_mat->FindBin(pt_vector[i],pt_vector[j])<<endl;
    }
  }
  // cout<<"centmin centmax: "<<centmin*2.5<<" "<<centmax*2.5;
  TLatex * ltitle;
  if(centmin==-1 && centmax==-1)
    ltitle = new TLatex(0.05,0.84,"V2 pp #sqrt{s}=2.76 TeV");
  else
    ltitle = new TLatex(0.05,0.84,Form("V2 PbPb #sqrt{s_{NN}}=2.76 TeV %2.1f-%2.1f %%",k,centmin*2.5,centmax*2.5));
  ltitle->SetNDC(1);
  vn_mat->Draw("lego2");
  ltitle->Draw();
  if(save==1 && div==0)
  {
    c1->SaveAs(Form("matrix_v%d_centmin%d_centmax%d.gif",k,centmin,centmax));
    c1->SaveAs(Form("matrix_v%d_centmin%d_centmax%d.C",k,centmin,centmax));
    c1->SaveAs(Form("matrix_v%d_centmin%d_centmax%d.pdf",k,centmin,centmax));
    c1->SaveAs(Form("matrix_v%d_centmin%d_centmax%d.eps",k,centmin,centmax));
  }
  if(save==1 && div==1)
  {
    c1->SaveAs(Form("matdiv_v%d_centmin%d_centmax%d.gif",k,centmin,centmax));
    c1->SaveAs(Form("matdiv_v%d_centmin%d_centmax%d.C",k,centmin,centmax));
    c1->SaveAs(Form("matdiv_v%d_centmin%d_centmax%d.pdf",k,centmin,centmax));
    c1->SaveAs(Form("matdiv_v%d_centmin%d_centmax%d.eps",k,centmin,centmax));
  }
} 

void vn_ecc(int centmin, int centmax)
{

  //! Diagonal method
  double corr_pt[4] = {1.349,2.342,3.354,4.597}; //,6.757,8.830
  double corr_v2[4] = {0,0,0,0};
  double corr_v2err[4] = {0,0,0,0};
  double corr_v3[4] = {0,0,0,0};
  double corr_v3err[4] = {0,0,0,0};
  double corr_x_err[4] = {0,0,0,0};
  std::vector<double> tmp_corr = find_ij(0,0,centmin,centmax)
  for(int i = 0 ; i < 4 ; ++i)
  {
    corr_v2[i] = sqrt(find_ijk(i,i,2,centmin,centmax));
    corr_v2err[i] = find_ijk_err(i,i,2,centmin,centmax)/(2*sqrt(find_ijk(i,i,2,centmin,centmax)));
    corr_v3[i] = sqrt(find_ijk(i,i,3,centmin,centmax));
    corr_v3err[i] = find_ijk_err(i,i,3,centmin,centmax)/(2*sqrt(find_ijk(i,i,3,centmin,centmax)));
  }
  
  //! Factorization method
  double corr2_pt[6] = {1.349,2.342,3.354,4.597,6.757,8.830}; //
  double corr2_v2[6] = {0,0,0,0,0,0};
  double corr2_v2err[6] = {0,0,0,0,0,0};
  double corr2_v3[6] = {0,0,0,0,0,0};
  double corr2_v3err[6] = {0,0,0,0,0,0};
  double corr2_x_err[6] = {0,0,0,0,0,0};
  for(int i = 0 ; i < 6 ; ++i)
  {
    double v0_2 = find_ijk(0,0,2,centmin,centmax);
    double dv0_2 = find_ijk_err(0,0,2,centmin,centmax);
    double vn_2 = find_ijk(i,0,2,centmin,centmax);
    double dvn_2 = find_ijk_err(i,0,2,centmin,centmax);
    double v0_3 = find_ijk(0,0,3,centmin,centmax);
    double dv0_3 = find_ijk_err(0,0,3,centmin,centmax);
    double vn_3 = find_ijk(i,0,3,centmin,centmax);
    double dvn_3 = find_ijk_err(i,0,3,centmin,centmax);
    
    corr2_v2[i] = vn_2/sqrt(v0_2);
    corr2_v2err[i] = sqrt( pow(dvn_2/sqrt(v0_2),2) + pow(vn_2/(2*pow(sqrt(v0_2),3))*dv0_2,2) );
    corr2_v3[i] = vn_3/sqrt(v0_3);
    corr2_v3err[i] = sqrt( pow(dvn_3/sqrt(v0_3),2) + pow(vn_3/(2*pow(sqrt(v0_3),3))*dv0_3,2) );
  }
  
}

double Getvn(int i , int j , int k, int centmin, int centmax)
{
  double v0_2 = find_ijk(j,j,k,centmin,centmax);
  double dv0_2 = find_ijk_err(j,j,k,centmin,centmax);
  double vn_2 = find_ijk(i,j,k,centmin,centmax);
  double dvn_2 = find_ijk_err(i,j,k,centmin,centmax);
  
  return vn_2/sqrt(v0_2);
}

double Getvnerr(int i , int j , int k, int centmin, int centmax)
{
  double v0_2 = find_ijk(j,j,k,centmin,centmax);
  double dv0_2 = find_ijk_err(j,j,k,centmin,centmax);
  double vn_2 = find_ijk(i,j,k,centmin,centmax);
  double dvn_2 = find_ijk_err(i,j,k,centmin,centmax);
  
  return sqrt( pow(dvn_2/sqrt(v0_2),2) + pow(vn_2/(2*pow(sqrt(v0_2),3))*dv0_2,2) );
}



void vn_npart(int divecc = 0 , int pttrg = 0 , int ptass = 0 , int save = 1 )
{

    c3 = new TCanvas("c3","",700,600);
  c3->SetFillStyle(4000);
  c3->SetFillColor(0);
  c3->SetFrameFillStyle(4000);
  // makeMultiPanelCanvas(c3, 1, 1, 0.03, 0.03, 0.22, 0.23, 0.34);
  
  const int ncent = 12;
  double x_npart[ncent], y_vn[ncent], y_vnerr[ncent];
  double y_vnecc[ncent], y_vneccerr[ncent];
  double x_errors[ncent];
  double shiftX = 400.0, shiftY = 0.3 , minY = 0.0 , maxY = 1.0;
  
  if(divecc==1) shiftY = 1.1;
  
  if(divecc==0)
    TH2D* dummy = new TH2D("dummy",Form(";N_{part};v_{n}^{f} [10^{-2}]"),100,0,ect->GetNpart(min_cents[0],max_cents[0])+20,100,minY*shiftY,shiftY);
  if(divecc==1)
    TH2D* dummy = new TH2D("dummy",Form(";N_{part};v_{n}^{f}/#epsilon_{n} [10^{-2}]"),100,0,ect->GetNpart(min_cents[0],max_cents[0])+20,100,minY*shiftY,maxY*shiftY);
  dummy->Draw();
  dummy->GetYaxis()->CenterTitle();
  dummy->GetXaxis()->CenterTitle();
  TLegend * leg = new TLegend(0.25,0.90,0.45,0.65);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  

    
      TLatex * lcms = new TLatex( .4*shiftX , .9*shiftY, "CMS Preliminary" );
      lcms->SetTextSize(lcms->GetTextSize()*0.8);
      lcms->Draw("same");
      
      TLatex * lint = new TLatex( .4*shiftX , .8*shiftY, "#int L dt = 3.1 #mub^{-1}" );
      lint->SetTextSize(lint->GetTextSize()*0.8);
      lint->Draw("same");
      
      TLatex * lass = new TLatex( .7*shiftX , 0.9*shiftY, "1<p_{T}^{assoc}<2 GeV/c" );
      lass->SetTextSize(lass->GetTextSize()*0.8);
      lass->Draw("same");
      
      TLatex * ltrg = new TLatex( .7*shiftX , 0.8*shiftY, "1<p_{T}^{trg}<2 GeV/c" );
      ltrg->SetTextSize(ltrg->GetTextSize()*0.8);
      ltrg->Draw("same");
      
      TLatex * ldeta = new TLatex( .7*shiftX ,0.7*shiftY, "2<|#Delta#eta|<4" );
      ldeta->SetTextSize(ldeta->GetTextSize()*0.8);
      ldeta->Draw("same");
  
  
  for(int vn = 2 ; vn <= 5 ; ++vn)
  {
    for(int cent = 0 ; cent < ncent ; ++cent)
    {
      double npart = ect->GetNpart(min_cents[cent],max_cents[cent]);
      double v = Getvn(pttrg,ptass,vn,min_cents[cent],max_cents[cent]);
      double dv = Getvnerr(pttrg,ptass,vn,min_cents[cent],max_cents[cent]);
      double e = ect->GetEcc(vn,min_cents[cent],max_cents[cent]);
      double de = e / 100.0 * ect->GetEccErr(vn,min_cents[cent],max_cents[cent]);
      
      x_npart[cent] = npart;
      cout<<npart<<endl;
      y_vn[cent] = v;
      y_vnerr[cent] = dv;
      y_vnecc[cent] = v/e;
      y_vneccerr[cent] = sqrt( ((dv/e)*(dv/e)) + ((de*v/e/e)*(de*v/e/e)) );
      
    }
    if(divecc==0)
    {
      TGraphErrors* g_vn = new TGraphErrors(ncent,x_npart,y_vn,x_errors,y_vnerr);
      g_vn->SetName("g_vn");
      g_vn->SetMarkerColor(vn-1);
      g_vn->Draw("PEsame");
      leg->AddEntry(g_vn, Form("v_{%d}^{f}",vn),"p");
    }
    if(divecc==1)
    {
      TGraphErrors* g_vn_ecc = new TGraphErrors(ncent,x_npart,y_vnecc,x_errors,y_vneccerr);
      g_vn_ecc->SetName("g_vn_ecc");
      g_vn_ecc->SetMarkerColor(vn-1);
      g_vn_ecc->Draw("PEsame");
      leg->AddEntry(g_vn_ecc, Form("v_{%d}^{f}/#epsilon_{%d}",vn,vn),"p");
    }
  }
  leg->Draw();
  // TLatex * ltrg = new TLatex(0.55,0.90,"1<p_{T}^{assoc}<2 GeV/c");
  // TLatex * lass = new TLatex(0.55,0.84,"1<p_{T}^{trg}<2 GeV/c");
  // ltrg->SetTextFont(42);
  // ltrg->Draw("same");
  // lass->SetTextFont(42);
  // lass->Draw("same");
  if(save==1)
  {
    if(divecc==0)
    {
      c3->SaveAs("vn_npart.gif");
      c3->SaveAs("vn_npart.pdf");
      c3->SaveAs("vn_npart.eps");
      c3->SaveAs("vn_npart.C");
    }
    if(divecc==1)
    {
      c3->SaveAs("vn_npartecc.gif");
      c3->SaveAs("vn_npartecc.pdf");
      c3->SaveAs("vn_npartecc.eps");
      c3->SaveAs("vn_npartecc.C");
    }
  }
}

void centrality(int v_n)
{

      // double v0 = vData[0][j+1];
      // double dv0 = vErrorData[0][j+1];
      // double vn = vData[i][j+1];
      // double dvn = vErrorData[i][j+1];
      // tempData[i] = vn/sqrt(fabs(v0))*10;
      // tempData1[i] = tempData[i]/getEcc(centmin/2,j+1)*0.1;
      // cout<<"td1, td2:  "<<tempData[i]<<" , "<<tempData1[i]<<endl;
      // tempErrorData[i] = sqrt( pow(dvn/sqrt(fabs(v0)),2) + pow(vn/(2*pow(sqrt(fabs(v0)),3))*dv0,2) )*10;
      // tempErrorData1[i] = tempErrorData[i]/getEcc(centmin/2,j+1)*0.1;

  // cout<<getV()<<endl;
  // return;
  const int num_points = 14;
  double x_cent[num_points], x_cent_err[num_points], cent_vn[num_points], cent_vn_err[num_points];
  double cent_vn_ecc[num_points], cent_vn_ecc_err[num_points];
  for(int i = 0 ; i < num_points ; ++i)
  {
    x_cent[i] = 2.5 + 5.0*i;
    x_cent_err[i] = 2.5;
    double v0 = find_ijk(0,0,v_n,2*i,2*(i+1));
    double dv0 = find_ijk_err(0,0,v_n,2*i,2*(i+1));
    double vn = v0;
    double dvn = dv0;
    cent_vn[i] = vn/sqrt(fabs(v0));
    cent_vn_ecc[i] = cent_vn[i]/getEcc(i,v_n);
    cent_vn_err[i] = sqrt( pow(dvn/sqrt(fabs(v0)),2) + pow(vn/(2*pow(sqrt(fabs(v0)),3))*dv0,2) );
    // cent_vn_ecc_err[i] = cent_vn[i]/getEcc(i,v_n);
    cent_vn_ecc_err[i] = cent_vn[i];
  }
  for(int i = 0 ; i < num_points ; ++i)
  {
    cout<<"i, vn, vn/ecc:  "<<i<<" , "<<cent_vn[i]<<" , "<<cent_vn_ecc[i]<<endl;
  }
  
  TH2D* dummy = new TH2D("dummy"," ;cent %;v_{n}",100,0.1,99.9,100,-0.5,1);
  dummy->GetXaxis()->CenterTitle();
  dummy->GetYaxis()->CenterTitle();
  dummy->GetYaxis()->SetTitleOffset(dummy->GetYaxis()->GetTitleOffset()*1.5);
  dummy->Draw();
  TGraphErrors* gcent_vn = new TGraphErrors(num_points,x_cent,cent_vn,x_cent_err,cent_vn_err);
  gcent_vn->SetName("gcent_vn");
  gcent_vn->SetMarkerColor(1);
  TGraphErrors* gcent_vn_ecc = new TGraphErrors(num_points,x_cent,cent_vn_ecc,x_cent_err,cent_vn_ecc_err);
  gcent_vn_ecc->SetName("gcent_vn_ecc");
  gcent_vn_ecc->SetMarkerColor(2);
  
  TString whichV = Form("v_{%d}{2}",v_n);
  TString whichVecc = Form("v_{%d}{2}/#epsilon_{%d}",v_n,v_n);
  TLegend * leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetFillColor(0);
  leg->AddEntry(gcent_vn, whichV.Data(),"p");
  leg->AddEntry(gcent_vn_ecc, whichVecc.Data(),"p");
  // leg->SetTextSize(0.05);
  gcent_vn->Draw("PEsame");
  gcent_vn_ecc->Draw("PEsame");
  leg->Draw();

  
}

void flow_compare(int centmin, int centmax)
{
  double pt_err_0[20] = {0.0};
  double pt22[20], pt24[20], pt32[20];
  double v22[20], v24[20], v32[20];
  double v22_error[20], v24_error[20], v32_error[20];
  //! v2{2}
  for(int k = 0 ; k < getPt22(centmin/2).size() ; ++k)
  {
    pt22[k]=getPt22(centmin/2)[k];
    v22[k]=getV22(centmin/2)[k];
    v22_error[k]=getV22_err(centmin/2)[k];
  }
  TGraphErrors* gv22 = new TGraphErrors(getPt22(centmin/2).size(),pt22,v22,pt_err_0,v22_error);
  gv22->SetName("gv22");
  
    // cout<<"HERE2"<<endl;
    // cout<<getPt24(centmin/2).size()<<endl;
    // cout<<"HERE2.5"<<endl;
  //! v2{4}
  for(int k = 0 ; k < getPt24(centmin/2).size() ; ++k)
  {
    // cout<<"HERE3"<<endl;
    pt24[k]=getPt24(centmin/2)[k];
    v24[k]=getV24(centmin/2)[k];
    v24_error[k]=getV24_err(centmin/2)[k];
  }
  TGraphErrors* gv24 = new TGraphErrors(getPt24(centmin/2).size(),pt24,v24,pt_err_0,v24_error);
  gv24->SetName("gv24");
  
  //! v3{2}
  for(int k = 0 ; k < getPt32(centmin/2).size() ; ++k)
  {
    pt32[k]=getPt32(centmin/2)[k];
    v32[k]=getV32(centmin/2)[k];
    v32_error[k]=getV32_err(centmin/2)[k];
  }
  TGraphErrors* gv32 = new TGraphErrors(getPt32(centmin/2).size(),pt32,v32,pt_err_0,v32_error);
  gv32->SetName("gv32");
  
  vector<TLatex*> latexvector;
  TString centrality = Form("cent %d-%d%%",centmin*5/2,centmax*5/2);
  latexvector.push_back(new TLatex( 6 , .45, centrality.Data() ));
  
  //! Diagonal method
  double corr_pt[4] = {1.349,2.342,3.354,4.597}; //,6.757,8.830
  double corr_v2[4] = {0,0,0,0};
  double corr_v2err[4] = {0,0,0,0};
  double corr_v3[4] = {0,0,0,0};
  double corr_v3err[4] = {0,0,0,0};
  double corr_x_err[4] = {0,0,0,0};
  for(int i = 0 ; i < 4 ; ++i)
  {
    corr_v2[i] = sqrt(find_ijk(i,i,2,centmin,centmax));
    corr_v2err[i] = find_ijk_err(i,i,2,centmin,centmax)/(2*sqrt(find_ijk(i,i,2,centmin,centmax)));
    corr_v3[i] = sqrt(find_ijk(i,i,3,centmin,centmax));
    corr_v3err[i] = find_ijk_err(i,i,3,centmin,centmax)/(2*sqrt(find_ijk(i,i,3,centmin,centmax)));
  }
  
  //! Factorization method
  double corr2_pt[6] = {1.349,2.342,3.354,4.597,6.757,8.830}; //
  double corr2_v2[6] = {0,0,0,0,0,0};
  double corr2_v2err[6] = {0,0,0,0,0,0};
  double corr2_v3[6] = {0,0,0,0,0,0};
  double corr2_v3err[6] = {0,0,0,0,0,0};
  double corr2_x_err[6] = {0,0,0,0,0,0};
  for(int i = 0 ; i < 6 ; ++i)
  {
    double v0_2 = find_ijk(0,0,2,centmin,centmax);
    double dv0_2 = find_ijk_err(0,0,2,centmin,centmax);
    double vn_2 = find_ijk(i,0,2,centmin,centmax);
    double dvn_2 = find_ijk_err(i,0,2,centmin,centmax);
    double v0_3 = find_ijk(0,0,3,centmin,centmax);
    double dv0_3 = find_ijk_err(0,0,3,centmin,centmax);
    double vn_3 = find_ijk(i,0,3,centmin,centmax);
    double dvn_3 = find_ijk_err(i,0,3,centmin,centmax);
    
    corr2_v2[i] = vn_2/sqrt(v0_2);
    corr2_v2err[i] = sqrt( pow(dvn_2/sqrt(v0_2),2) + pow(vn_2/(2*pow(sqrt(v0_2),3))*dv0_2,2) );
    corr2_v3[i] = vn_3/sqrt(v0_3);
    corr2_v3err[i] = sqrt( pow(dvn_3/sqrt(v0_3),2) + pow(vn_3/(2*pow(sqrt(v0_3),3))*dv0_3,2) );
    
  }
  
  

  
  
  
  double x_error[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  TH2D* dummy = new TH2D("dummy"," ;p_{T}^{trig} (GeV/c);v_{n}",100,0.1,9.9,100,-0.0,0.5);
  dummy->GetXaxis()->CenterTitle();
  dummy->GetYaxis()->CenterTitle();
  dummy->GetYaxis()->SetTitleOffset(dummy->GetYaxis()->GetTitleOffset()*1.5);


  
  dummy->Draw();
  TGraphErrors* gcorrv2 = new TGraphErrors(4,corr_pt,corr_v2,corr_x_err,corr_v2err);
  gcorrv2->SetName("gcorrv2");
  TGraphErrors* gcorrv3 = new TGraphErrors(4,corr_pt,corr_v3,corr_x_err,corr_v3err);
  gcorrv3->SetName("gcorrv3");
  // gcorrv2->SetMarkerStyle(21);
  // gcorrv3->SetMarkerStyle(25);
  TGraphErrors* gcorr2v2 = new TGraphErrors(6,corr2_pt,corr2_v2,corr2_x_err,corr2_v2err);
  gcorr2v2->SetName("gcorr2v2");
  TGraphErrors* gcorr2v3 = new TGraphErrors(6,corr2_pt,corr2_v3,corr2_x_err,corr2_v3err);
  gcorr2v3->SetName("gcorr2v3");
  
  gcorr2v2->SetMarkerColor(3);
  gcorr2v3->SetMarkerColor(3);
  
  gv22->SetMarkerColor(1);
  gv24->SetMarkerColor(2);
  gv32->SetMarkerColor(1);
  // gcorr2v2->SetMarkerStyle(20);
  // gcorr2v3->SetMarkerStyle(24);
  // gv2->SetMarkerColor(2);
  gv22->SetMarkerColor(4);
  // gv2->SetMarkerStyle(21);
  gv32->SetMarkerColor(2);
  // gv3->SetMarkerStyle(25);
  TLegend * leg = new TLegend(0.3,0.9,0.6,0.7);
  leg->SetFillColor(0);
  // gv22->Draw("PEsame");
  // gv24->Draw("PEsame");
  gv32->Draw("PEsame");
  // gcorrv2->Draw("PEsame");
  gcorrv3->Draw("PEsame");
  // gcorr2v2->Draw("PEsame");
  gcorr2v3->Draw("PEsame");
  // leg->AddEntry(gv22,"v_{2}{2}","p");
  // leg->AddEntry(gv24,"v_{2}{4}","p");
  leg->AddEntry(gv32,"v_{3}{2}","p");
  // leg->AddEntry(gcorrv2,"v_{2}^{2pcorr},diagonal","p");
  leg->AddEntry(gcorrv3,"v_{3}^{2pcorr},diagonal","p");
  // leg->AddEntry(gcorr2v2,"v_{2}^{2pcorr},p_{T}^{asso}:1-2","p");
  leg->AddEntry(gcorr2v3,"v_{3}^{2pcorr},p_{T}^{asso}:1-2","p");

  // leg->AddEntry(gv22,"v_{2}{2}","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  latexvector[0]->Draw("same");

  
}

void ratio_plot()
{
// TGraphErrors* gv1 = new TGraphErrors(4,x_vector,tempMC,x_error,tempErrorMC);
// gv1->SetName("gv1");
// double x_vector[4] = {2.4,4.6,6.7,8.8};
  int vn = 2;
  // double x_vector[4] = {2.4,4.6,6.7,8.8};
  double x_vector[4] = {1.5,2.5,3.5,5};
  double y0_vector[4] = {0,0,0,0};
  for(int i = 0 ; i < 4 ; ++i)
    y0_vector[i]=find_ijk(i,0,vn,0,2);
  double y1_vector[4] = {0,0,0,0};
  y1_vector[0]=y0_vector[1];
  for(int i = 1 ; i < 4 ; ++i)
    y1_vector[i]=find_ijk(i,1,vn,0,2);
  cout<<"fu"<<endl;
  // return;
  double y2_vector[4] = {0,0,0,0};
  y2_vector[0]=y0_vector[2];
  y2_vector[1]=y1_vector[2];
  for(int i = 2 ; i < 4 ; ++i)
    y2_vector[i]=find_ijk(i,2,vn,0,2);
  double y3_vector[4] = {0,0,0,0};
  y3_vector[0]=y0_vector[3];
  y3_vector[1]=y1_vector[3];
  y3_vector[2]=y2_vector[3];
  y3_vector[3]=find_ijk(3,3,vn,0,2);

  cout<<endl;
  cout<<endl;
  cout<<"before dividing"<<endl;
  cout<<"y0";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y0_vector[i];
  cout<<endl;
  cout<<"y1";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y1_vector[i];
  cout<<endl;
  cout<<"y2";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y2_vector[i];
  cout<<endl;
  cout<<"y3";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y3_vector[i];
  cout<<endl;
  
  
  // return;
  for(int i = 0 ; i < 4 ; ++i)
  {
    y3_vector[i] = y3_vector[i]/y0_vector[i];
    y2_vector[i] = y2_vector[i]/y0_vector[i];
    y1_vector[i] = y1_vector[i]/y0_vector[i];
    y0_vector[i] = y0_vector[i]/y0_vector[i];
  }
  cout<<endl;
  cout<<"after dividing"<<endl;
  cout<<"y0";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y0_vector[i];
  cout<<endl;
  cout<<"y1";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y1_vector[i];
  cout<<endl;
  cout<<"y2";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y2_vector[i];
  cout<<endl;
  cout<<"y3";
  for(int i = 0 ; i < 4 ; ++i)
    cout<<" "<<y3_vector[i];
  cout<<endl;
  
  TH2D* dummy = new TH2D("dummy"," ;p_{T}^{trig} (GeV/c);V_{n}^{assoc pT=1-2:4-6}/V_{n}^{assoc pT=1-2}",100,0.1,5.9,100,0.1,5.0);
  dummy->GetXaxis()->CenterTitle();
  dummy->GetYaxis()->CenterTitle();
  dummy->GetYaxis()->SetTitleOffset(dummy->GetYaxis()->GetTitleOffset()*1.5);

  TGraph* gv1 = new TGraph(4,x_vector,y0_vector);
  gv1->SetName("gv1");
  TGraph* gv2 = new TGraph(4,x_vector,y1_vector);
  gv2->SetName("gv2");
  TGraph* gv3 = new TGraph(4,x_vector,y2_vector);
  gv3->SetName("gv3");
  TGraph* gv4 = new TGraph(4,x_vector,y3_vector);
  gv4->SetName("gv4");
  gv1->SetMarkerColor(1);
  gv1->SetMarkerStyle(20);
  gv2->SetMarkerColor(2);
  gv2->SetMarkerStyle(21);
  gv3->SetMarkerColor(3);
  gv3->SetMarkerStyle(22);
  gv4->SetMarkerColor(4);
  gv4->SetMarkerStyle(29);
  // gv2->SetMarkerColor(2);
  // gv3->SetMarkerColor(6);
  // gv3->SetMarkerStyle(25);
  // gv4->SetMarkerStyle(24);
  // gv4->SetMarkerColor(4);
  
  dummy->Draw();
  gv1->Draw("Psame");
  gv2->Draw("Psame");
  gv3->Draw("Psame");
  gv4->Draw("Psame");
  // zero->Draw("same");
  // if(j==3)
  // {
    // latexvector[5]->Draw("same");
    // latexvector[7]->Draw("same");
  // }
  // if(j==4)
  // {
    // latexvector[6]->Draw("same");
  // } double x_vector[4] = {2.4,4.6,6.7,8.8};
  
  TLegend * leg = new TLegend(0.3,0.3,0.68,0.6);
  leg->SetFillColor(0);
  leg->AddEntry(gv1,"V_{2}^{2pcorr} (p_{T}^{asso}:1-2/p_{T}^{asso}:1-2)","p");
  leg->AddEntry(gv2,"V_{2}^{2pcorr} (p_{T}^{asso}:2-3/p_{T}^{asso}:1-2)","p");
  leg->AddEntry(gv3,"V_{2}^{2pcorr} (p_{T}^{asso}:3-4/p_{T}^{asso}:1-2)","p");
  leg->AddEntry(gv4,"V_{2}^{2pcorr} (p_{T}^{asso}:4-6/p_{T}^{asso}:1-2)","p");
  leg->SetTextSize(0.05);
  leg->Draw();

  
  
}

double find_ijk(int i , int j , int k, int centmin, int centmax)
{
  if(centmin == 0 && centmax == -22)
  {
    TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv8",-1,-1,-1,-1,i,j,2.0,4.0,0);
    TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
    f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
    h1d_data1->Fit("f1d_data1","RNO");
    return f1d_data1->GetParameter(k);  
  }
  else
    return alf->GetAPFourier(i,j,k,centmin,centmax);
  // TH1D* h1d = (TH1D*)draw_single_dPhi("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv5",-1,-1,-1,-1,i,j,2.0,4.0,0);
  // TH1D* h1d_data = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,0,2,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("AMPTReco_Minbias_2760GeV","GEN_INCLGENv5",5000,100000,-1,-1,i,j,2.0,4.0,0);

  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1v6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // h1d_data1->Fit("f1d_data1","RNO");
  // FourierDecomposition * tinstance = new FourierDecomposition(h1d_data1);
  // double result = f1d_data1->GetParameter(k);
  // delete f1d_data1;
  // delete h1d_data1;
  // return result;

  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6HF4100",-1,-1,0,2,i,j,2.0,4.0,0);
// TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5Eric",1200,10000,0,2,i,j,2.0,4.0,0);
  // TH1D* h1d_data2 = (TH1D*)draw_single_dPhi("HydjetReco_Minbias_2760GeV","393_INCLGENv5",-1,-1,0,2,i,j,2.0,4.0,0);
  // TF1 * f1d = new TF1("f1d","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // TF1 * f1d_data = new TF1("f1d_data","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // TF1 * f1d_data2 = new TF1("f1d_data2","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // f1d->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // f1d_data->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // f1d_data2->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // h1d->Fit("f1d","RNO");
  // h1d_data->Fit("f1d_data","RNO");
  // h1d_data2->Fit("f1d_data2","RNO");
 
  
  // double max = PI, min = 0.0;
  // set the max and min outside the range
  // std::vector<double> v0to5 = tinstance->GetCosCoefficients(16, min, max);
  // for(int t = 1 ; t < 6 ; ++t )
  // {
    // cout<<"Fourier vs Fit: "<<t<<" = "<<v0to5[t]/v0to5[0]/2.0<<" vs "<<f1d_data1->GetParameter(t)<<endl; 
  // }
  // double diff = result - GetAPFourier(i,j,k,centmin,centmax);
  // cout<<diff<<endl;
  // delete tinstance;
  // delete f1d;
  // delete f1d_data;
  // delete f1d_data2;
  // delete h1d;
  // delete h1d_data;
  // delete h1d_data2;
}

double find_ijk_err(int i , int j , int k, int centmin, int centmax)
{
  if(centmin == 0 && centmax == -22)
  {
    TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv8",-1,-1,-1,-1,i,j,2.0,4.0,0);
    TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
    f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
    h1d_data1->Fit("f1d_data1","RNO");
    return f1d_data1->GetParError(k);  
  }
  else
    return alf->GetAPFourierErr(i,j,k,centmin,centmax);
  // TH1D* h1d = (TH1D*)draw_single_dPhi("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv5",-1,-1,-1,-1,i,j,2.0,4.0,0);
  // TH1D* h1d_data = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,0,2,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("AMPTReco_Minbias_2760GeV","GEN_INCLGENv5",5000,100000,-1,-1,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
        // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6HF4100",-1,-1,0,2,i,j,2.0,4.0,0);

  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5Eric",1200,10000,0,2,i,j,2.0,4.0,0);
  // TH1D* h1d_data2 = (TH1D*)draw_single_dPhi("HydjetReco_Minbias_2760GeV","393_INCLGENv5",-1,-1,0,2,i,j,2.0,4.0,0);
  // TF1 * f1d = new TF1("f1d","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // TF1 * f1d_data = new TF1("f1d_data","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // TF1 * f1d_data2 = new TF1("f1d_data2","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // f1d->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // f1d_data->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // f1d_data2->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // h1d->Fit("f1d","RNO");
  // h1d_data->Fit("f1d_data","RNO");
  // h1d_data2->Fit("f1d_data2","RNO");
 
 /* old
  TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1v6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  h1d_data1->Fit("f1d_data1","RNO");
  double result = f1d_data1->GetParError(k);
  delete f1d_data1;
  delete h1d_data1;
  return result;
  */

  // double diff = result - GetAPFourierErr(i,j,k,centmin,centmax);
  // cout<<diff<<endl;

  // delete f1d;
  // delete f1d_data;
  // delete f1d_data2;
  // delete h1d;
  // delete h1d_data;
  // delete h1d_data2;
}

std::vector<double> find_ij(int i, int j, int centmin, int centmax, string tag = "AllPhysics_INCLEFF1v6", string datatype = "HIData_Minbias_2760GeV", double etamin = 2.0, double etamax = 4.0)
{
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLPHIBIN64v6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1CENT05v6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLv6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1v6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  TH1D* h1d_data1 = (TH1D*)draw_single_dPhi(datatype,tag,-1,-1,centmin,centmax,i,j,etamin,etamax,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLv8",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysicsSmall_INCLv8",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1v6Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
  // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("PPData_Minbias_2760GeV","MINBIAS_All_INCLEFF1TRG1v6",-1,-1,-1,-1,i,j,2.0,4.0,0);
  TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  h1d_data1->Fit("f1d_data1","RNO");
 
  // FourierDecomposition * tinstance = new FourierDecomposition(h1d_data1);
  // double max = PI, min = 0.0;
  // std::vector<double> v0to5 = tinstance->GetCosCoefficients(16, min, max);
  std::vector<double> result;
  for(int k = 0 ; k < 6 ; ++k)
  {
    result.push_back(f1d_data1->GetParameter(k));
  }
  // delete tinstance;
  delete f1d_data1;
  delete h1d_data1;
  return result;

}

std::vector<double> find_ij_err(int i, int j, int centmin, int centmax, string tag = "AllPhysics_INCLEFF1v6", string datatype = "HIData_Minbias_2760GeV", double etamin = 2.0, double etamax = 4.0)
{
  TH1D* h1d_data1 = (TH1D*)draw_single_dPhi(datatype,tag,-1,-1,centmin,centmax,i,j,etamin,etamax,0);
  TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  h1d_data1->Fit("f1d_data1","RNO");
 
  // FourierDecomposition * tinstance = new FourierDecomposition(h1d_data1);
  // double max = PI, min = 0.0;
  // std::vector<double> v0to5 = tinstance->GetCosCoefficients(16, min, max);
  std::vector<double> result;
  for(int k = 0 ; k < 6 ; ++k)
  {
    result.push_back(f1d_data1->GetParError(k));
  }
  // delete tinstance;
  delete f1d_data1;
  delete h1d_data1;
  return result;

}

void write_ratio()
{
  int centmin = 8, centmax = 10, j=5;
  for(int k = 1 ; k <= 5 ; ++k)
    for(int i = 0 ; i < 6 ; ++i)
      cout<<"HalfBin,k,i,"<<k<<","<<i<<","<<fabs(1-find_ijk(i,j,k,centmin,centmax)/find_ijk(i,j,k,10*centmin,10*centmax))<<","
      <<"TrckEff,k,i,"<<k<<","<<i<<","<<fabs(1-find_ijk(i,j,k,centmin,centmax)/find_ijk(i,j,k,100*centmin,100*centmax))<<","
      <<"ZeroEff,k,i,"<<k<<","<<i<<","<<fabs(1-find_ijk(i,j,k,centmin,centmax)/find_ijk(i,j,k,1000*centmin,1000*centmax))<<","
      <<endl;
  // for(int k = 1 ; k < 5 ; ++k)
    // for(int i = 0 ; i < 6 ; ++i)
      // cout<<endl;
  // for(int k = 1 ; k < 5 ; ++k)
    // for(int i = 0 ; i < 6 ; ++i)
      // cout<<"ZeroEff,k,i,"<<k<<","<<i<<",  "<<fabs(1-find_ijk(i,j,k,centmin,centmax)/find_ijk(i,j,k,1000*centmin,1000*centmax))<<endl;

}

void find_fourier(int centmin, int centmax, int whichplot=1, double errorfactor = 1.0)
{
  // c3 = new TCanvas("c3","",800,220);
  c3 = new TCanvas("c3","",1600,400);
  zero->SetLineStyle(2);
  // c3->Divide(4,1);
  makeMultiPanelCanvas(c3, 5, 1, 0.03, 0.03, 0.22, 0.17, 0.03);
  double v0vector[4];
  vector<vector<double> > vMC;
  vector<vector<double> > vData;
  vector<vector<double> > vData1;
  vector<vector<double> > vData2;
  vector<vector<double> > vErrorMC;
  vector<vector<double> > vErrorData;
  vector<vector<double> > vErrorData1;
  vector<vector<double> > vErrorData2;
  
  int nonconst_numPt;
  if(whichplot >= 5 && whichplot <= 10)  nonconst_numPt = 4;
  else if(whichplot == 11) nonconst_numPt = 5;
  else                              nonconst_numPt = 6;
  
  const int numPt = nonconst_numPt;
  if(whichplot >= 5 && whichplot <= 10)
  {
    double x_vector[numPt] = {2.4,4.6,6.7,8.8};
    double x_error[numPt] = {0,0,0,0};
  }
  else if(whichplot == 11)
  {
    double x_vector[numPt] = {2.4,4.6,6.7,8.8, 10.87};
    double x_error[numPt] = {0,0,0,0,0};
  }
  else
  {
    double x_vector[numPt] = {1.349,2.342,3.354,4.597,6.757,8.830};
    double x_error[numPt] = {0,0,0,0,0,0};
  }
  
  
  int numV = 6;
  
  for ( int i = 0; i < numPt; i++ ) {
    vMC.push_back ( vector<double>() );
    vErrorMC.push_back ( vector<double>() );
    vData.push_back ( vector<double>() );
    vData1.push_back ( vector<double>() );
    vData2.push_back ( vector<double>() );
    vErrorData.push_back ( vector<double>() );
    vErrorData1.push_back ( vector<double>() );
    vErrorData2.push_back ( vector<double>() );
  }
  double tempMC[numPt];
  double tempData[numPt];
  double tempData1[numPt];
  double tempData2[numPt];
  double tempErrorMC[numPt];
  double tempErrorData[numPt];
  double tempErrorData1[numPt];
  double tempErrorData2[numPt];
  
  // ="pt_assoc 8.8 GeV / pt_assoc 2.4 GeV"
  // double x_vector[4] = {1.38,2.40,3.42,4.3};
  

  int ptbins[4] = {6,3,4,5};
  
  
  for(int i = 0; i < numPt; ++i)
  {
    for(int j = 0; j == 0; ++j)
    {
      // TH1D* h1d = (TH1D*)draw_single_dPhi("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv5",-1,-1,-1,-1,i,j,2.0,4.0,0);
      
      // TH1D* h1d_data = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
        // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1v6",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
      
      // TH1D* h1d_data = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
      
      // TH1D* h1d_data = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5Eric",-1,-1,centmin,centmax,i,j,2.0,4.0,0);
      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v5Eric",1200,10000,0,2,i,j,2.0,4.0,0);
      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllEric_INCLEFF1v6HF4100",-1,-1,0,2,i,j,2.0,4.0,0);
      // HIData_Minbias_2760GeV_AllEric_INCLEFF1v6HF4100_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root
      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("AMPTReco_Minbias_2760GeV","GEN_INCLGENv5",5000,100000,-1,-1,i,j,2.0,4.0,0);
      // TH1D* h1d_data2 = (TH1D*)draw_single_dPhi("HydjetReco_Minbias_2760GeV","393_INCLGENv5",-1,-1,0,2,i,j,2.0,4.0,0);
      // TH1D* h1d = (TH1D*)draw_single_dPhi("PPData_Minbias_7TeV","TRIGGER100_All_firstdag",130,1000,-1,-1,i+1,j+1,2.0,4.0,0);
      // TH1D* h1d_data = (TH1D*)draw_single_dPhi("PPData_Minbias_7TeV","TRIGGER100_All_firstdag",150,1000,-1,-1,i+1,j+1,2.0,4.0,0);

      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("PPData_Minbias_7TeV","TRIGGER85_All_seconddag",110,1000,-1,-1,i,j,2.0,4.0,0);
      
      // TH1D* h1d_data2 = (TH1D*)draw_single_dPhi("PPData_Minbias_7TeV","TRIGGER70_All_thirddag",90,1000,-1,-1,i,j,2.0,4.0,0);
      
      // TH1D* h1d = (TH1D*)draw_single_dPhi("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLv5",-1,-1,-1,-1,i,j,2.0,4.0,0);
      // TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLv5",-1,-1,0,2,i,j,2.0,4.0,0);
      
      
      // return;
      
      // TF1 * f1d = new TF1("f1d","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
      // TF1 * vcos = new TF1("vcos","[0]+[1]*cos(2*x)",0,PI);
      // f1d->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
      // h1d->Fit("f1d","RNO");
      
      TF1 * f1d_data = new TF1("f1d_data","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
      TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
      TF1 * f1d_data2 = new TF1("f1d_data2","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
      f1d_data->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
      f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
      f1d_data2->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
      // h1d_data->Fit("f1d_data","RNO");
      // h1d_data1->Fit("f1d_data1","RNO");
      // h1d_data2->Fit("f1d_data2","RNO");
      
      // c3->cd(i);
      // h1d->SetTitle("PYTHIA8 2.76TeV Trig 2-4 GeV, Assoc 2-4 GeV 2<|#Delta#eta|<4");
      // TCanvas * c1 = new TCanvas();
      // h1d_data->SetTitle("PbPb 2.76TeV Trig 2-4 GeV, Assoc 4-6 GeV 2<|#Delta#eta|<4");
      // h1d->GetYaxis()->SetTitleOffset(h1d->GetYaxis()->GetTitleOffset()*1.5);
      // f1d_data->SetLineColor(2);
      // vector<TLatex*> latexvector;
      
      // double top = 0.0, scale = 0.0;
      // top += f1d_data->GetParameter(0);
        // cout<<top<<endl;
      // for( int k = 0 ; k < 5 ; ++k )
      // {
        // top += .10*f1d_data->GetParameter(k+1);
        // top += 80.0*f1d_data->GetParameter(k+1);
        // top += 100.0*f1d_data->GetParameter(k+1);
        // cout<<top<<endl;
      // }
      // scale = (top - abs(f1d_data->GetParameter(0)))/130.0;
      // scale = (top - abs(f1d_data->GetParameter(0)))/13.0;
      // latexvector.push_back(new TLatex( 1, top , "CMS Preliminary" ));
      // h1d_data->Draw("E");
      // f1d_data->Draw("same");
      // c1->SetLeftMargin(c1->GetLeftMargin()*1.5);
      // cout<<endl<<endl;
      // latexvector.push_back(new TLatex( 1, 40.58 , "CMS Preliminary" ));
      // TString tempstring;
      // tempstring = Form("V_{%d}: %f",0,f1d_data->GetParameter(0));
      // cout<<tempstring.Data()<<endl;
      // latexvector.push_back(new TLatex( 1, top - scale*1 , tempstring.Data() ));
      // tempstring = Form("V_{%d}: %f",1,f1d_data->GetParameter(1));
      // cout<<tempstring.Data()<<endl;
      // latexvector.push_back(new TLatex( 1, top - scale*2 , tempstring.Data() ));
      // tempstring = Form("V_{%d}: %f",2,f1d_data->GetParameter(2));
      // cout<<tempstring.Data()<<endl;
      // latexvector.push_back(new TLatex( 1, top - scale*3 , tempstring.Data() ));
      // tempstring = Form("V_{%d}: %f",3,f1d_data->GetParameter(3));
      // cout<<tempstring.Data()<<endl;
      // latexvector.push_back(new TLatex( 1, top - scale*4 , tempstring.Data() ));
      // tempstring = Form("V_{%d}: %f",4,f1d_data->GetParameter(4));
      // cout<<tempstring.Data()<<endl;
      // latexvector.push_back(new TLatex( 1, top - scale*5 , tempstring.Data() ));
      
      // for(int k = 0 ; k <=5 ; ++k)
      // {
        // cout<<"V"<<k<<": "<<f1d_data->GetParameter(k)<<endl;
        // cout<<latexvector.size()<<endl;
      // }
      // cout<<"chi^2/NDF: "<<f1d_data->GetChisquare()/f1d_data->GetNDF()<<endl;
      // tempstring = Form("#chi^{2}/NDF: %f",f1d_data->GetChisquare()/f1d_data->GetNDF());
      // latexvector.push_back(new TLatex( 1, top - scale*6 , tempstring.Data() ));
        // cout<<latexvector.size()<<endl;
      // for(int k = 0 ; k < 7; ++k)
        // latexvector[k]->Draw("same");
        // latexvector[1]->Draw("same");
      // return;
      
      // h1d->Fit
      // cout<<f1d->GetParameter(0)<<" === "<<f1d_data->GetParameter(0)<<endl;
      // cout<<f1d->GetParameter(1)<<" === "<<f1d_data->GetParameter(1)<<endl;
      // cout<<f1d->GetParameter(2)<<" === "<<f1d_data->GetParameter(2)<<endl;
      // cout<<f1d->GetParameter(3)<<" === "<<f1d_data->GetParameter(3)<<endl;
      // cout<<f1d->GetParameter(4)<<" === "<<f1d_data->GetParameter(4)<<endl;
      // cout<<"function fit"<<endl;
      // h1d->Draw();
      // f1d->Draw("same");
 
     // FourierDecomposition * tinstance = new FourierDecomposition(h1d_data1);
      
      // set the max and min outside the range
      // double max = PI, min = 0.0;
      // std::vector<double> v0to5 = tinstance->GetCosCoefficients(5, min, max);
      // for(int t = 1 ; t < 6 ; ++t )
      // {
        // cout<<"Fourier vs Fit: "<<t<<" = "<<100*v0to5[t]/v0to5[0]/2.0<<" vs "<<f1d_data1->GetParameter(t)<<endl; 
      // }
      
      for ( int k = 0; k < numV; k++ ) {
        // vMC[i].push_back ( f1d->GetParameter(k)*100*f1d->GetParameter(0)/f1d_data->GetParameter(0) );
        // vErrorMC[i].push_back ( f1d->GetParError(k)*100*f1d->GetParameter(0)/f1d_data->GetParameter(0) );
        // vMC[i].push_back ( f1d->GetParameter(k)*100 );
        // vErrorMC[i].push_back ( f1d->GetParError(k)*100 );
        // vData[i].push_back ( f1d_data->GetParameter(k) );
        // vData1[i].push_back ( f1d_data1->GetParameter(k) );
        // vData1[i].push_back ( v0to5[k]/v0to5[0]/2.0 );
        // vErrorData1[i].push_back ( f1d_data1->GetParError(k) );
        vData[i].push_back ( f1d_data->GetParameter(k) );
        vErrorData[i].push_back ( f1d_data->GetParError(k) );

        // if(whichplot==5)
        // {
          // vData1[i].push_back ( find_ijk(ptbins[i],6,k,centmin,centmax) );
          // vErrorData1[i].push_back ( find_ijk_err(ptbins[i],6,k,centmin,centmax) );
        // }
        if(whichplot==6 || whichplot==5) //! compare to AllPhysics_INCLv8, 0-3 pt bins, cent needs to be 0 2, 0 1, or 1 2
        {
          vData1[i].push_back ( find_ijk(i,j,k,100*centmin,-100*centmax) );
          vErrorData1[i].push_back ( find_ijk_err(i,j,k,100*centmin,-100*centmax) );
          // vData1[i].push_back ( find_ijk(i,j,k,100*0,-100*1) );
          // vErrorData1[i].push_back ( find_ijk_err(i,j,k,100*0,-100*1) );
        }
        else if(whichplot==7 || whichplot==8 || whichplot==9)  //! compare to AllPhysics_INCLEFF1v8Eric, 0-3 pt bins, cent needs to be 0 2, 0 1, or 1 2
        {
          vData1[i].push_back ( find_ijk(i,j,k,41*centmin,41*centmax) );
          vErrorData1[i].push_back ( find_ijk_err(i,j,k,41*centmin,41*centmax) );
        }
        else if(whichplot==10 || whichplot==11)
        {
          double N_PbPb = find_ijk(i,j,0,41*centmin,41*centmax);
          double N_PYTHIA = find_ijk(i,j,0,-11*centmin,-11*centmax);
          vData1[i].push_back ( find_ijk(i,j,k,-11*centmin,-11*centmax)*N_PYTHIA/N_PbPb );
          vErrorData1[i].push_back ( find_ijk_err(i,j,k,-11*centmin,-11*centmax)*N_PYTHIA/N_PbPb  );        
        }
        else
        {
          vData1[i].push_back ( find_ijk(i,j,k,centmin,centmax) );
          vErrorData1[i].push_back ( find_ijk_err(i,j,k,centmin,centmax) );
        }
        //! compare to corephys , cent needs to be 0 2
        if(whichplot==1)
        {
          vData2[i].push_back ( find_ijk(i,j,k,centmin,-centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,centmin,-centmax) );
        }
        //! compare to halfbin , cent needs to be 8 10
        if(whichplot==2)
        {
          vData2[i].push_back ( find_ijk(i,j,k,centmin*10,centmax*10) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,centmin*10,centmax*10) );
        }
    
        //! compare to trackeff , cent needs to be 8 10
        if(whichplot==3)
        {
          vData2[i].push_back ( find_ijk(i,j,k,centmin*100,centmax*100) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,centmin*100,centmax*100) );
        }
    
        //! compare to noeff , cent needs to be 8 10
        if(whichplot==4)
        {
          vData2[i].push_back ( find_ijk(i,j,k,centmin*1000,centmax*1000) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,centmin*1000,centmax*1000) );
        }
        //! compare to promptreco, 0-3 pt bins, cent needs to be 0 2
        if(whichplot==5)
        {
          vData2[i].push_back ( find_ijk(i,j,k,10*centmin,-10*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,10*centmin,-10*centmax) );
        }
        //! compare to AllPhysicsSmall_INCLv8, 0-3 pt bins, cent needs to be 0 2, 0 1, or 1 2
        if(whichplot==6)
        {
          vData2[i].push_back ( find_ijk(i,j,k,1000*centmin,-1000*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,1000*centmin,-1000*centmax) );
        }
        //! compare to AllPhysicsSmall_INCLEFF1v8Eric, 0-3 pt bins, cent needs to be 0 2, 0 1, or 1 2
        if(whichplot==7)
        {
          vData2[i].push_back ( find_ijk(i,j,k,43*centmin,43*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,43*centmin,43*centmax) );
        }
        //! compare to All_INCLEFF1v8Eric, 0-3 pt bins, cent needs to be 0 2, 0 1, or 1 2
0        if(whichplot==8)
        {
          vData2[i].push_back ( find_ijk(i,j,k,43*centmin,43*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,43*centmin,43*centmax) );
        }
        //! compare to AllPhysics_INCLEFF1v8EricHFHits, 0-3 pt bins, cent needs to be 0 2, 0 1, or 1 2
        if(whichplot==9)
        {
          vData2[i].push_back ( find_ijk(i,j,k,whichplot*centmin,whichplot*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,whichplot*centmin,whichplot*centmax) );
        }
        //! Fig 6 in the paper, cent needs to be 0 2, tag is AllPhysics_INCLEFF1v8Eric
        if(whichplot==10)
        {
          vData2[i].push_back ( find_ijk(i,j,k,41*centmin,41*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,41*centmin,41*centmax) );
        }
        if(whichplot==11)
        {
          vData2[i].push_back ( find_ijk(i,j,k,41*centmin,41*centmax) );
          vErrorData2[i].push_back ( find_ijk_err(i,j,k,41*centmin,41*centmax) );
        }
        
        
        // vData2[i].push_back ( f1d_data2->GetParameter(k) );
        // vErrorData[i].push_back ( f1d_data->GetParError(k) );
        // vErrorData2[i].push_back ( f1d_data2->GetParError(k) );
      }
      // delete tinstance;
      cout<<i<<" "<<j<<endl;
    }
    
    cout<<endl;
    cout<<endl;

  }
  double shiftYff = 1.0, shiftX = 1.0;
  double x_scale;
  if(whichplot==11) x_scale = 11.9;
  else              x_scale = 9.9;
  // TH2D* dummy = new TH2D("dummy",";p_{T}^{trig} (GeV/c);N_{ass}/N_{ass}^{PbPb} V_{n} [10^{-2}]",100,0.1,9.9,100,(-1)*shiftYff,shiftYff);
  TH2D* dummy = new TH2D("dummy",";p_{T}^{trig} (GeV/c);N_{ass}/N_{ass}^{PbPb} V_{n} [10^{-2}]",100,0.1,x_scale*shiftX,100,(-1)*shiftYff,shiftYff);
  // TH2D* dummy = new TH2D("dummy",";p_{T}^{trig} (GeV/c);V_{n}^{corr}/V_{n}^{uncorr}",100,0.1,9.9,100,0.0,2.0);
  dummy->GetXaxis()->CenterTitle();
  dummy->GetYaxis()->CenterTitle();
  dummy->GetYaxis()->SetTitleOffset(dummy->GetYaxis()->GetTitleOffset()*1.5);
  
  float xsize = 0.08;
  TH2D* dummy2 = (TH2D*) dummy->Clone("dummy2");
  // dummy2->SetYTitle("V_{0}/V_{0}^{PbPb} V_{2} [10^{-2}]");
  dummy2->GetXaxis()->CenterTitle();
  dummy2->GetXaxis()->SetTitleSize(xsize);
  TH2D* dummy3 = (TH2D*) dummy->Clone("dummy3");
  // dummy3->SetYTitle("V_{0}/V_{0}^{PbPb} V_{3} [10^{-2}]");
  dummy3->GetXaxis()->CenterTitle();
  dummy3->GetXaxis()->SetTitleSize(xsize);
  TH2D* dummy4 = (TH2D*) dummy->Clone("dummy4");
  // dummy4->SetYTitle("V_{0}/V_{0}^{PbPb} V_{4} [10^{-2}]");
  dummy4->GetXaxis()->CenterTitle();
  dummy4->GetXaxis()->SetTitleSize(xsize);
  TH2D* dummy5 = (TH2D*) dummy->Clone("dummy5");
  // dummy4->SetYTitle("V_{0}/V_{0}^{PbPb} V_{4} [10^{-2}]");
  dummy5->GetXaxis()->CenterTitle();
  dummy5->GetXaxis()->SetTitleSize(xsize);
    
  vector<TH2D*> dummyvector;
  dummyvector.push_back(dummy);
  dummyvector.push_back(dummy2);
  dummyvector.push_back(dummy3);
  dummyvector.push_back(dummy4);
  dummyvector.push_back(dummy5);
  
  vector<TLatex*> latexvector;
  latexvector.push_back(new TLatex( 2.0*shiftX , .8*shiftYff, "V_{1}" ));
  latexvector.push_back(new TLatex( 2.0*shiftX , .8*shiftYff, "V_{2}" ));
  latexvector.push_back(new TLatex( 2.0*shiftX , .8*shiftYff, "V_{3}" ));
  latexvector.push_back(new TLatex( 2.0*shiftX , .8*shiftYff, "V_{4}" ));
  latexvector.push_back(new TLatex( 2.0*shiftX , .8*shiftYff, "V_{5}" ));
  latexvector.push_back(new TLatex( 1.0*shiftX , -.8*shiftYff, "2<|#Delta#eta|<4" ));
  latexvector.push_back(new TLatex( 4.5*shiftX , .8*shiftYff, "CMS Preliminary" ));
  latexvector.push_back(new TLatex( 1.0*shiftX , -.6*shiftYff, "1<p_{T}^{assoc}<2 GeV/c" ));
  TString centrality = Form("cent %d-%d%%",centmin*5/2,centmax*5/2);
  latexvector.push_back(new TLatex( 1.0*shiftX , -.4*shiftYff, centrality.Data() ));
  // TLatex * title2 = new TLatex( 5.0 , 0.8, "V_2" );
  // TLatex * title3 = new TLatex( 5.0 , 0.8, "V_3" );
  // TLatex * title4 = new TLatex( 5.0 , 0.8, "V_4" );
  
  latexvector[0]->SetTextSize(0.07);
  latexvector[1]->SetTextSize(0.09);
  latexvector[2]->SetTextSize(0.09);
  latexvector[3]->SetTextSize(0.09);
  latexvector[4]->SetTextSize(0.09);
  latexvector[5]->SetTextSize(0.07);
  latexvector[6]->SetTextSize(0.07);
  latexvector[7]->SetTextSize(0.07);
  latexvector[8]->SetTextSize(0.07);
  
  // if(j==0);
      // title->SetTextSize(0.07);
  
  // TLine * zero = new TLine( 0.0, 0.0, 10.0, 0.0 );
  // zero->SetLineStyle(9);
  // cout<<"here"<<endl;
  for(int j = 0 ; j < 5 ; ++j)
  {
    c3->cd(j+1);
    cout<<"========================"<<endl;
    for(int i = 0 ; i < numPt ; ++i)
    {
      double v0 = vData[0][j+1];
      double dv0 = vErrorData[0][j+1];
      double vn = vData[i][j+1];
      double dvn = vErrorData[i][j+1];

      // tempMC[i] = vMC[i][j+1];
      tempData[i] = vData[i][j+1]*100;
      tempData1[i] = vData1[i][j+1]*100;
      // tempData[i] = vn/sqrt(fabs(v0))*10;
      // tempData1[i] = tempData[i]/getEcc(centmin/2,j+1)*0.1;
      tempData2[i] = vData2[i][j+1]*100;
      
      cout<<"td1, td2:  "<<tempData[i]<<" , "<<tempData1[i]<<endl;
      // tempErrorMC[i] = vErrorMC[i][j+1];
      tempErrorData[i] = vErrorData[i][j+1]*100;
      // tempErrorData[i] = sqrt( pow(dvn/sqrt(fabs(v0)),2) + pow(vn/(2*pow(sqrt(fabs(v0)),3))*dv0,2) )*10;
      // tempErrorData1[i] = tempErrorData[i]/getEcc(centmin/2,j+1)*0.1;
      tempErrorData1[i] = vErrorData1[i][j+1]*100*errorfactor;
      tempErrorData2[i] = vErrorData2[i][j+1]*100*errorfactor;
      // cout<<vMC[i][j+1]<<" , "<<vData[i][j+1]<<endl;
    }

    cout<<"numpt "<<numPt<<endl;
    // cout<<"============"<<endl;
    
    // TGraphErrors* gv1 = new TGraphErrors(numPt,x_vector,tempMC,x_error,tempErrorMC);
    // gv1->SetName("gv1");
    TGraphErrors* gv2 = new TGraphErrors(numPt,x_vector,tempData,x_error,tempErrorData);
    gv2->SetName("gv2");
    TGraphErrors* gv3 = new TGraphErrors(numPt,x_vector,tempData1,x_error,tempErrorData1);
    gv3->SetName("gv3");
    TGraphErrors* gv4 = new TGraphErrors(numPt,x_vector,tempData2,x_error,tempErrorData2);
    gv4->SetName("gv4");
    
    // cout<<"============"<<endl;
    // cout<<gv1->GetX()[0]<<",";
    // cout<<gv1->GetY()[0]<<endl;
    // cout<<gv1->GetX()[1]<<",";
    // cout<<gv1->GetY()[1]<<endl;
    // cout<<gv1->GetX()[2]<<",";
    // cout<<gv1->GetY()[2]<<endl;
    // cout<<gv1->GetX()[3]<<",";
    // cout<<gv1->GetY()[3]<<endl;
    
    
    // TGraph* gv3 = new TGraph(4,x_vector,v3vector);
    // gv3->SetName("gv3");
    // TGraph* gv4 = new TGraph(4,x_vector,v4vector);
    // gv4->SetName("gv4");
    // gv0->SetFillColor(1);
    // gv0->SetLineColor(4);
    // gv0->SetLineWidth(1);
    // gv0->SetMarkerStyle(1);
    // gv0->SetTitle("v0 over 4 trig pt bins");
    // gv0->GetXaxis()->SetTitle("trig pt bin");
    // gv0->GetYaxis()->SetTitle("fourier coefficient");
    // gv0->Draw("A*");
    
    // gv4->SetLineColor(kBlue);
    // gv4->SetLineStyle(3);
    gv3->SetLineWidth(3);
    // gv1->SetMarkerColor(2);
    // gv1->SetMarkerStyle(21);
    // gv1->SetLineColor(1);
    // gv1->SetLineWidth(2);
    gv2->SetMarkerColor(2);
    gv3->SetMarkerColor(2);
    // gv3->SetMarkerColor(6);
    // gv3->SetMarkerStyle(25);
    // gv3->SetMarkerStyle(24);
    if(whichplot==10 || whichplot==11)
      gv4->SetMarkerColor(2);
    else
    {
      gv4->SetMarkerStyle(25);
      gv4->SetMarkerColor(6);
    }
    // gv2->SetLineColor(2);
    // gv3->SetLineColor(6);
    // gv4->SetLineColor(4);
    // gv2->SetLineWidth(2);
    // gv3->SetLineWidth(2);
    // gv4->SetLineWidth(2);
    
    
    // gv2->SetMarkerStyle(23);
    // gv3->SetMarkerColor(4);
    // gv3->SetMarkerStyle(24);
    // gv4->SetMarkerColor(6);
    // gv4->SetMarkerStyle(26);
    // mg->Add(gv1);
    // mg->Add(gv2);
    // mg->Add(gv3);
    // mg->Add(gv4);
    dummyvector[j]->Draw();
    // gv1->Draw("LEsame");
    if((whichplot==10 || whichplot==11))
      gv3->Draw("LEsame");
    else
      gv3->Draw("PEsame");
    // gv3->Draw("Esame");
    if(whichplot>0 || whichplot<5) gv4->Draw("PEsame");
    // gv2->Draw("LEsame");
    // gv3->Draw("LEsame");
    // gv4->Draw("LEsame");
    // gv1->Draw("LEsame");
    zero->Draw("same");
    // latexvector[j]->SetTextSize(latexvector[j]->GetTextSize()*0.7);
    // latexvector[j]->Draw("same");
    if(j==3)
    {
      // latexvector[5]->Draw("same");
      // latexvector[7]->Draw("same");
      // latexvector[8]->Draw("same");
    }
    if(j==4)
    {
      // CMS Preliminary
      // latexvector[6]->Draw("same");
    }
    // TLatex * title = new TLatex( 5.0 , 0.8, Form("V_{%d}",j+1) );
    // if(j==0);
      // title->SetTextSize(0.07);
    // title->Draw("same");
    
    
    // delete gv1;
    // delete gv2;
    // delete leg;
    // TLatex * this_v = new TLatex( 1.0*shiftX , );
    if(j==0 && (whichplot < 10 || whichplot > 11) )
    {
      TLatex * lcent = new TLatex(1.0*shiftX , -0.8*shiftYff, Form("%d - %d %%",(int) (2.5*centmin),(int) (2.5*centmax)) );
      lcent->SetTextSize(lcent->GetTextSize()*0.7);
      lcent->Draw("same");
      TLatex * lcms = new TLatex( 1.0*shiftX , .7*shiftYff, "CMS Preliminary" );
      lcms->SetTextSize(lcms->GetTextSize()*0.7);
      lcms->Draw("same");
    
    }
    if(j==0 && (whichplot < 10 || whichplot > 11))
    {
      if(whichplot>=5 && whichplot<10)
        TLatex * lass = new TLatex( 1.0*shiftX , .45*shiftYff, "2<p_{T}^{assoc}<4 GeV/c" );
      else
        TLatex * lass = new TLatex( 1.0*shiftX , .45*shiftYff, "1<p_{T}^{assoc}<2 GeV/c" );
      lass->SetTextSize(lass->GetTextSize()*0.7);
      lass->Draw("same");
    }
    if(j==3 && (whichplot==10 || whichplot==11))
    {
      TLatex * lass = new TLatex( 1.0*shiftX , -.6*shiftYff, "2<p_{T}^{assoc}<4 GeV/c" );
      lass->SetTextSize(lass->GetTextSize()*0.7);
      lass->Draw("same");
      
      TLatex * ldeta = new TLatex( 1.0*shiftX , -.8*shiftYff, "2<|#Delta#eta|<4" );
      ldeta->SetTextSize(ldeta->GetTextSize()*0.7);
      ldeta->Draw("same");

    }
    if(j==4)
    {
      TLatex * lcms = new TLatex( 1.0*shiftX , -.40*shiftYff, "CMS   #int L dt = 0.4 #mub^{-1}" );
      lcms->SetTextSize(lcms->GetTextSize()*0.65);
      lcms->Draw("same");
    }
    if(j==0)
    {
      TLatex * lv1 = new TLatex( 2.0*shiftX , .8*shiftYff, Form("V_{%d}",j+1) );
      // lv1->SetTextSize(lv1->GetTextSize()*0.7);
      lv1->Draw("same");
    }
    if(j==1)
    {
      TLatex * lv2 = new TLatex( 2.0*shiftX , .8*shiftYff, Form("V_{%d}",j+1) );
      // lv2->SetTextSize(lv2->GetTextSize()*0.7);
      lv2->Draw("same");
    }
    if(j==2)
    {
      TLatex * lv3 = new TLatex( 2.0*shiftX , .8*shiftYff, Form("V_{%d}",j+1) );
      // lv3->SetTextSize(lv3->GetTextSize()*0.7);
      lv3->Draw("same");
    }
    if(j==3)
    {
      TLatex * lv4 = new TLatex( 2.0*shiftX , .8*shiftYff, Form("V_{%d}",j+1) );
      // lv4->SetTextSize(lv4->GetTextSize()*0.7);
      lv4->Draw("same");
    }
    if(j==4)
    {
      TLatex * lv5 = new TLatex( 2.0*shiftX , .8*shiftYff, Form("V_{%d}",j+1) );
      // lv5->SetTextSize(lv5->GetTextSize()*0.7);
      lv5->Draw("same");
    }
    
    // delete lvn;
    // 
    // if(j==3)
    // {
      // if(V_or_v==0)
        // TLegend * leg = new TLegend(0.05,0.74,0.58,0.94);
      // if(V_or_v==1)
        // TLegend * leg = new TLegend(0.05,0.24,0.58,0.48);
      // leg->SetFillColor(0);
      
      // if(V_or_v==0)
        // leg->AddEntry(gtemp,"PbPb 2.76TeV","p");
      // else
        // leg->AddEntry(gtemp,Form("v_{%d}^{corr}, dihadron correlation",vn),"p");
      // if(V_or_v==0)
        // leg->AddEntry(gpp,"N_{ass}/N_{ass}^{PbPb} pp 2.76TeV","l");
      // if(V_or_v==1 && vn==2)
      // {
        // leg->AddEntry(gv22,"v_{2}{2}","p");
        // leg->AddEntry(gv24,"v_{2}{4}","p");  
      // }
      // if(V_or_v==1 && vn==3)
        // leg->AddEntry(gv3,"v_{3}{2}","p");
      // if(V_or_v==1 && vn==4)
        // leg->AddEntry(gv4,"v_{4} LYZ","p");
      
      // leg->SetTextFont(42);
      // leg->SetTextSize(0.085);
      // leg->Draw();
    
    // if(j==0)
    // {
      // if(V_or_v==0)
        // TLatex * ltitle = new TLatex(0.8*shiftX , 0.7*shiftYff, Form("V_{%d}^{f}",vn) );
      // else
        // TLatex * ltitle = new TLatex(0.8*shiftX , 0.7*shiftYff, Form("v_{%d}^{corr}",vn) );
      // ltitle->SetTextSize(ltitle->GetTextSize()*0.7);
      // ltitle->Draw("same");
    // }
    
  }
  cout<<endl;
  
  
  TLegend * leg = new TLegend(0.02,0.17,0.92,0.35);
  // leg->SetHeader("Fourier progressions");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  // leg->SetTextSize(0.5);
  // leg->AddEntry(gv4,"HYDJET 2.76TeV, 0-5% ","p");
  // leg->AddEntry(gv3,"AMPT 2.76TeV ","p");
  // leg->AddEntry(gv3,"PbPb uncorrected 2.76TeV, 0-5% ","p");
  if(whichplot==5)      leg->AddEntry(gv3,"PbPb 2.76TeV Rereco","p");
  else if(whichplot==6) leg->AddEntry(gv3,"0-2.5% PbPb 2.76TeV AllPhysics_INCLv8","p");
  else if(whichplot==7 || whichplot==8 || whichplot==9) leg->AddEntry(gv3,"full rereco","p");
  else if(whichplot==10 || whichplot==11) leg->AddEntry(gv4,"PbPb #sqrt{s_{NN}}=2.76 TeV, 0-5%","p");
  else                  leg->AddEntry(gv3,"PbPb 2.76TeV AllPhysics","p");
  if(whichplot==1)      leg->AddEntry(gv4,"PbPb 2.76TeV CorePhysics","p");
  if(whichplot==2)      leg->AddEntry(gv4,"PbPb 2.76TeV Half Bin","p");
  if(whichplot==3)      leg->AddEntry(gv4,"PbPb 2.76TeV Track Eff","p");
  if(whichplot==4)      leg->AddEntry(gv4,"PbPb 2.76TeV No Eff","p");
  if(whichplot==5)      leg->AddEntry(gv4,"PbPb 2.76TeV Promptreco","p");
  if(whichplot==6)      leg->AddEntry(gv4,"PbPb 2.76TeV AllPhysicsSmall_INCLv8","p");
  if(whichplot==7)      leg->AddEntry(gv4,"1/10th rereco","p");
  if(whichplot==8)      leg->AddEntry(gv4,"prompt reco","p");
  if(whichplot==9)      leg->AddEntry(gv4,"rereco with HFHits centrality","p");
  if(whichplot==10 || whichplot==11)     leg->AddEntry(gv3,"PYTHIA8 pp #sqrt{s}=2.76TeV","l");
  // leg->AddEntry(gv22,"PbPb 2.76TeV mike","p");
  // leg->AddEntry(gv1,"PYTHIA8 pp 2.76TeV","l");
  // leg->AddEntry(gv4,"PP N> 90 7TeV ","l");
  // leg->AddEntry(gv3,"Most Central","p");
  // leg->AddEntry(gv3,"vn/ecc","p");
  // leg->AddEntry(gv3,"AllPhysics","p");
  // leg->AddEntry(gv3,"PP N>110 7TeV ","l");
  // leg->AddEntry(gv2,"PP N>130 7 TeV ","l");
  // leg->AddEntry(gv1,"PP N>150 7 TeV ","l");
  // leg->AddEntry(gv3,"v3","p");
  // leg->AddEntry(gv4,"v4","p");
  leg->SetTextSize(0.05);
  leg->Draw();
  cout<<"cent MIN/MAX : "<<centmin<<"/"<<centmax<<endl;

}

TF1 * draw_fit(int ipt, int jpt, int centmin, int centmax, string tag = "AllPhysics_INCLEFF1v6", int save = 1, int data_mc = 1 )
{
  if(data_mc ==1)
    TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV",tag,-1,-1,centmin,centmax,ipt,jpt,2.0,4.0,0);
  else
  {
    TFile * f = new TFile(Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/unmerged/hist2D_generate_%d.root",i));
    TH2D * h2d = (TH2D*)f->Get("h_clone");
  }
  // if(dataset==2) TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","AllPhysics_INCLEFF1v8Eric",-1,-1,centmin,centmax,ipt,jpt,2.0,4.0,0);
  // if(dataset==3) TH1D* h1d_data1 = (TH1D*)draw_single_dPhi("HIData_Minbias_2760GeV","All_INCLEFF1v8Eric",-1,-1,centmin,centmax,ipt,jpt,2.0,4.0,0);
  TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",0,PI);
  // TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(2*x))",0,PI);
  // TF1 * f1d_data1 = new TF1("f1d_data1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x)+2*[7]*cos(7*x)+2*[8]*cos(8*x)+2*[9]*cos(9*x)+2*[10]*cos(10*x))",0,PI);
  // cout<<"v"<<i<<" = "<<f1d_data1->GetParameter(i)<<" +="<<endl;

  
  // f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05,0.05,0.05,0.05,0.05,0.05);
  f1d_data1->SetParameters(0.015,-0.1,0.1,0.1,0.05,0.05);
  // f1d_data1->SetParameters(0.015,0.1);
  h1d_data1->Fit("f1d_data1","RNO");
  
  h1d_data1->SetTitle(Form("Fit ipt=%d jpt=%d %s",ipt,jpt,tag));
  // h1d_data1->Draw();
  f1d_data1->SetLineColor(2);
  // f1d_data1->Draw("same");
  // if(save==1)
    // c1->SaveAs(Form("fit_%s_%d_%d.png",tag,ipt,jpt));
  // delete f1d_data1;
  // delete h1d_data1;
  return f1d_data1;

}

void allPull()
{
  for(int i = 1 ; i <= 5 ; ++i)
  {
    for(int j = 0 ; j <= 3 ; ++j)
    {
      getPull(i,j,5,1);
    }
  }
  for(int i = 1 ; i <= 5 ; ++i)
  {
    getPull(i,-1,5,3);
  }
  for(int j = 0 ; j <= 3 ; ++j)
  {
    getPull(-1,j,5,4);
  }
  getPull(-1,-1,5,2);
}

TH1D * getPull(int vn = 2, int pttrg = 3, int range = 5, int which_pull = 1, int nbinsx = 10)
{
  // int nbinsx = 9;
  int pt_trg[5] = {2,4,6,8,10}; 
  int pt_ass[5] = {2,4,6,8,10}; 
  TF1 * myf;
  TH1D * pull;
  
  if(which_pull==1) //! default pull binning into seperate vn and pttrg bins
  {
    pull = new TH1D("pull",Form("Pull V%d",vn),nbinsx,-range,range);
    TF1 * myf = draw_fit(pttrg,0,0,2,Form("AllPhysicsAdd_INCLEFF1v8Eric"),0);
    double x0 = myf->GetParameter(vn);
    for(int i = 1 ; i <= 10 ; ++i)
    {
      myf = draw_fit(pttrg,0,0,2,Form("AllPhysics%d_INCLEFF1v8Eric",i),0);
      double sigma = myf->GetParError(vn);
      double x = myf->GetParameter(vn);
      pull->Fill((x-x0)/sigma);
    }
  }
  else if(which_pull==2) //! global pull: group all vn and pt bins together
  {
    pull = new TH1D("pull",Form("Global Pull"),nbinsx,-range,range);
    for(int v = 1 ; v <= 5 ; ++v)
    {
      for(int pt = 0 ; pt <= 3 ; ++pt)
      {
        myf = draw_fit(pt,0,0,2,Form("AllPhysicsAdd_INCLEFF1v8Eric"),0);
        double x0 = myf->GetParameter(v);
        for(int i = 1 ; i <= 10 ; ++i)
        {
          myf = draw_fit(pt,0,0,2,Form("AllPhysics%d_INCLEFF1v8Eric",i),0);
          double sigma = myf->GetParError(v);
          double x = myf->GetParameter(v);
          pull->Fill((x-x0)/sigma);
        }
      }
    }
  }
  else if(which_pull==3) //! pt pull: group all pt bins together, seperate vn
  {
    pull = new TH1D("pull",Form("Combined V_{%d} Pull",vn),nbinsx,-range,range);
    for(int pt = 0 ; pt <= 3 ; ++pt)
    {
      myf = draw_fit(pt,0,0,2,Form("AllPhysicsAdd_INCLEFF1v8Eric"),0);
      double x0 = myf->GetParameter(vn);
      for(int i = 1 ; i <= 10 ; ++i)
      {
        myf = draw_fit(pt,0,0,2,Form("AllPhysics%d_INCLEFF1v8Eric",i),0);
        double sigma = myf->GetParError(vn);
        double x = myf->GetParameter(vn);
        pull->Fill((x-x0)/sigma);
      }
    }
  }
  else if(which_pull==4) //! vn pull: group all vn bins together, seperate pt
  {
    pull = new TH1D("pull",Form("Combined p_{T}^{trg} Pull",),nbinsx,-range,range);
    for(int v = 1 ; v <= 5 ; ++v)
    {
      myf = draw_fit(pttrg,0,0,2,Form("AllPhysicsAdd_INCLEFF1v8Eric"),0);
      double x0 = myf->GetParameter(v);
      for(int i = 1 ; i <= 10 ; ++i)
      {
        myf = draw_fit(pttrg,0,0,2,Form("AllPhysics%d_INCLEFF1v8Eric",i),0);
        double sigma = myf->GetParError(v);
        double x = myf->GetParameter(v);
        pull->Fill((x-x0)/sigma);
      }
    }
  }
  delete myf;
  TF1 *fgaus = new TF1("fgaus","gaus(0)",-range,range);
  fgaus->SetParameters(pull->GetMaximum(),pull->GetMean(),pull->GetRMS());
  pull->Fit("fgaus","RNO");
  fgaus->SetLineStyle(2);
  float myrms = pull->GetRMS(), mymean = pull->GetMean();
  float chi2ndf = fgaus->GetChisquare() / fgaus->GetNDF();
  TLatex * lrms = new TLatex( -4.5 , pull->GetMaximum()*4.5/5.0, Form("RMS = %6.4f",myrms));
  TLatex * lmean = new TLatex( -4.5 , pull->GetMaximum()*4.0/5.0, Form("Mean = %6.4f",mymean));
  TLatex * lchi2 = new TLatex( -4.5 , pull->GetMaximum()*3.5/5.0, Form("#chi^{2}/NDF = %6.4f",chi2ndf));
  TLatex * lass = new TLatex( -4.5 , pull->GetMaximum()*3.0/5.0, Form("%d<p_{T}^{ass}<%d GeV",pt_ass[0],pt_ass[1]));
  TLatex * ltrg = new TLatex( -4.5 , pull->GetMaximum()*2.5/5.0, Form("%d<p_{T}^{trg}<%d GeV",pt_trg[pttrg],pt_trg[pttrg+1]));
  // pull->SetAxisRange(0,5,"Y");
  pull->GetYaxis()->SetTitle("Number of entries");
  if(which_pull==1 || which_pull==4)
    pull->GetXaxis()->SetTitle(Form("(avg V_{%d} - V_{%d}^{sample})/#sigma^{sample}",vn,vn));
  else
    pull->GetXaxis()->SetTitle(Form("(avg V_{n} - V_{n}^{sample})/#sigma^{sample}"));
  pull->GetYaxis()->CenterTitle();
  pull->GetXaxis()->CenterTitle();
  pull->Draw();
  lmean->Draw();
  lrms->Draw();
  lchi2->Draw();
  fgaus->Draw("same");
  if(which_pull==1 || which_pull==4)
  {
    ltrg->Draw();
    lass->Draw();
  }
  if(which_pull==1)   c1->SaveAs(Form("pull_v%d_pttrg_%d.png",vn,pttrg));
  if(which_pull==2)   c1->SaveAs(Form("pull_global.png"));
  if(which_pull==3)   c1->SaveAs(Form("pull_combined_v%d.png",vn));
  if(which_pull==4)   c1->SaveAs(Form("pull_combined_pttrg%d.png",pttrg));
  cout<<Form("pttrg%d = ",pttrg)<<pull->GetRMS()<<endl;
  // delete lrms;
  // delete lchi2;
  // delete lmean;
  // delete ltrg;
  // delete lass;
  // delete fgaus;
  return pull;
}

void draw_fourier(int centmin, int centmax, int save = 1, int ptass = 3)
{
  c3 = new TCanvas("c3","",1600,400);
  makeMultiPanelCanvas(c3, 5, 1, 0.03, 0.03, 0.22, 0.17, 0.03);
  const int numPt = 6;
  
  double x_vector[numPt] = {1.349,2.342,3.354,4.597,6.757,8.830};
  double x_error[numPt] = {0,0,0,0,0,0};
  double tempData[numPt], flipData[numPt];
  double tempErr[numPt], flipErr[numPt];
  for(int vn = 1 ; vn <= 5 ; ++k)
  {
    for(int i = 0 ; i < numPt ; ++i)
    {
      tempData[i] = find_ijk(i,ptass,vn,centmin,centmax)*100;
      tempErr[i] = find_ijk_err(i,ptass,vn,centmin,centmax)*100;    
      flipData[i] = find_ijk(ptass,i,vn,centmin,centmax)*100;
      flipErr[i] = find_ijk_err(ptass,i,vn,centmin,centmax)*100;    
    }
    
    
    
    
    
    
    
  }
  
}


void four_three_plot(int vn, int V_or_v, int ptass = 0, int etacut = 0, int legendpanel = 1)
{
  int minpt[7] = {1,2,3,4,6,8,2};
  int maxpt[7] = {2,3,4,6,8,10,4};
  zero->SetLineStyle(2);
  TH2D* dummy;
  if(V_or_v==0)
  {
    double shiftX = 1.0, shiftY = 1.0, minY = -1.0 , maxY = 1.0;
    if(vn==1) { shiftY = 5.0; minY = -1.0; maxY = 1.0; }
    if(vn==2) { shiftY = 5.0; }
    if(vn==3) { shiftY = 1.2; }
    if(vn==4) { shiftY = 0.5; }
    if(vn==5) { shiftY = 0.25; }
      
    dummy = new TH2D("dummy",Form(";p_{T}^{trig} (GeV/c);V_{%d}^{f} [10^{-2}]",vn),100,0.1,9.9*shiftX,100,minY*shiftY,maxY*shiftY);
  }
  if(V_or_v==1 || V_or_v==2)
  {
    double shiftX = 1.0, shiftY = 0.2, minY = -1.0 , maxY = 1.0;
    if(vn==2) { shiftY = 0.4; }
    if(vn==3) { shiftY = 0.3; }
    
    dummy = new TH2D("dummy",Form(";p_{T}^{trig} (GeV/c);v_{%d}^{f} ",vn),100,0.1,9.9*shiftX,100,minY*shiftY,maxY*shiftY);
  }
  fixedFontHist(dummy, 2.1);
  
  
  dummy->GetXaxis()->CenterTitle();
  dummy->GetYaxis()->CenterTitle();
  dummy->GetYaxis()->SetTitleOffset(dummy->GetYaxis()->GetTitleOffset()*1.5);

  c3 = new TCanvas("c3","",800,600);
  
  dummy->GetXaxis()->SetTitleSize(dummy->GetXaxis()->GetTitleSize()*0.8);
  dummy->GetXaxis()->SetTitleOffset(dummy->GetXaxis()->GetTitleOffset()*1.5);
  c3->SetFillStyle(4000);
  c3->SetFillColor(0);
  c3->SetFrameFillStyle(4000);
  
  makeMultiPanelCanvas(c3, 4, 3, 0.03, 0.03, 0.22, 0.23, 0.34);
  
  // int min_cents[14] = {0,2,4,6,8,10,12,14,16,20,24,28,32,36};
  // int max_cents[14] = {2,4,6,8,10,12,14,16,20,24,28,32,36,40};

  
  const int numPt = 6;
  double x_vector[numPt] = {1.349,2.342,3.354,4.597,6.757,8.830};
  double x_error[numPt] = {0,0,0,0,0,0};
  double tempData[numPt], ppData[numPt]; //, assoc1[numPt];
  double tempErrorData[numPt], ppErrorData[numPt]; //, assoc1Error[numPt];

  double cx_vector[21], cpt_v3[21], cpt_v22[21], cpt_v24[21];
  double cx_error[21];
  double ctempData[21], cv_v3[21], cv_v22[21], cv_v24[21];
  double ctempErrorData[21], cerr_v3[21], cerr_v22[21], cerr_v24[21];
  
  double temp24Gev[numPt];
  double tempError24Gev[numPt];
  
  
  for(int cent = 0 ; cent < 12 ; ++cent)
  {
    c3->cd(cent+1);
    for(int i = 0 ; i < numPt ; ++i)
    {
      
      if(V_or_v==0)
      {
         if(etacut == 0)
         {
           tempData[i] = find_ijk(i,ptass,vn,min_cents[cent],max_cents[cent])*100;
           tempErrorData[i] = find_ijk_err(i,ptass,vn,min_cents[cent],max_cents[cent])*100;
           ppData[i] = find_ijk(i,ptass,vn,-1,-1)*100*find_ijk(i,ptass,0,-1,-1)/find_ijk(i,ptass,0,min_cents[cent],max_cents[cent]);
           ppErrorData[i] = find_ijk_err(i,ptass,vn,-1,-1)*100*find_ijk(i,ptass,0,-1,-1)/find_ijk(i,ptass,0,min_cents[cent],max_cents[cent]);
           // cout<<"0: "<<tempData[i]<<endl;
         }
         else if(etacut == 1)
         {
           tempData[i] = find_ijk(i,ptass,vn,101*min_cents[cent],101*max_cents[cent])*100;
           tempErrorData[i] = find_ijk_err(i,ptass,101*vn,min_cents[cent],101*max_cents[cent])*100;
           ppData[i] = find_ijk(i,ptass,vn,-103,-103)*100*find_ijk(i,ptass,0,-103,-103)/find_ijk(i,ptass,0,101*min_cents[cent],101*max_cents[cent]);
           ppErrorData[i] = find_ijk_err(i,ptass,vn,-103,-103)*100*find_ijk(i,ptass,0,-103,-103)/find_ijk(i,ptass,0,101*min_cents[cent],101*max_cents[cent]);
           cout<<"1: "<<tempData[i]<<endl;
         }
        cout<<tempData[i]<<endl;
      }
      else
      {
        double v0_2 = find_ijk(0,ptass,vn,min_cents[cent],max_cents[cent]);
        double dv0_2 = find_ijk_err(0,ptass,vn,min_cents[cent],max_cents[cent]);
        double vn_2 = find_ijk(i,ptass,vn,min_cents[cent],max_cents[cent]);
        double dvn_2 = find_ijk_err(i,ptass,vn,min_cents[cent],max_cents[cent]);
        
        tempData[i] = vn_2/sqrt(v0_2);
        tempErrorData[i] = sqrt( pow(dvn_2/sqrt(v0_2),2) + pow(vn_2/(2*pow(sqrt(v0_2),3))*dv0_2,2) );
        
        if(V_or_v==2)
        {
          v0_2 = find_ijk(0,0,vn,min_cents[cent],max_cents[cent]);
          dv0_2 = find_ijk_err(0,0,vn,min_cents[cent],max_cents[cent]);
          vn_2 = find_ijk(i,0,vn,min_cents[cent],max_cents[cent]);
          dvn_2 = find_ijk_err(i,0,vn,min_cents[cent],max_cents[cent]);
          
          temp24Gev[i] = vn_2/sqrt(v0_2);
          tempError24Gev[i] = sqrt( pow(dvn_2/sqrt(v0_2),2) + pow(vn_2/(2*pow(sqrt(v0_2),3))*dv0_2,2) );
        }
        
        
        cout<<tempData[i]<<endl;
      }
    }
    TGraphErrors * gtemp = new TGraphErrors(numPt,x_vector,tempData,x_error,tempErrorData);
    gtemp->SetName("gtemp");
    gtemp->SetMarkerColor(2);
    if(V_or_v==0)
    {
      TGraphErrors * gpp = new TGraphErrors(numPt,x_vector,ppData,x_error,ppErrorData);
      gpp->SetName("gpp");
    }
    if(V_or_v==2)
    {
      TGraphErrors * g24gev = new TGraphErrors(numPt,x_vector,temp24Gev,x_error,tempError24Gev);
      g24gev->SetName("g24gev");
      g24gev->SetMarkerColor(4);
      g24gev->SetMarkerStyle(25);
    }

    dummy->Draw();
    if(vn==4 && cent>9) continue;
    if(vn==5 && cent>8) continue;
    
    gtemp->Draw("PEsame");
    if(V_or_v==0) gpp->Draw("LEsame");
    if(V_or_v==2) g24gev->Draw("PEsame");
    
    if(vn==4 && V_or_v==1)
    {
      if(cent > 0 && cent < 8)
      {
        vector<double> flowv4pt = getPtv4ptlyz(cent-1);
        vector<double> flowv4V = getVv4ptlyz(cent-1);
        vector<double> flowv4err = getVv4ptlyz_err(cent-1);
        
          cout<<"flowv4pt.size() "<<flowv4pt.size()<<endl;
        for(int i = 0 ; i < flowv4pt.size() ; ++i )
        {
          cx_vector[i] = flowv4pt[i];
          ctempData[i] = flowv4V[i];
          ctempErrorData[i] = flowv4err[i];
          // cout<<"ctemp "<<ctempData[i]<<endl;
        }
        TGraphErrors * gv4 = new TGraphErrors(flowv4pt.size(),cx_vector,ctempData,cx_error,ctempErrorData);
        gv4->SetName("gv4");
        gv4->SetMarkerColor(4);
        gv4->SetMarkerStyle(25);
        gv4->Draw("PEsame");
      }
    }
    
    if(vn==3 && V_or_v==1)
    {
      vector<double> flowv3pt = getPt32(cent);
      vector<double> flowv3V = getV32(cent);
      vector<double> flowv3err = getV32_err(cent);
      
        cout<<"flowv3pt.size() "<<flowv3pt.size()<<endl;
      for(int i = 0 ; i < flowv3pt.size() ; ++i )
      {
        cpt_v3[i] = flowv3pt[i];
        cv_v3[i] = flowv3V[i];
        cerr_v3[i] = flowv3err[i];
        // cout<<"ctemp "<<ctempData[i]<<endl;
      }
      TGraphErrors * gv3 = new TGraphErrors(flowv3pt.size(),cpt_v3,cv_v3,cx_error,cerr_v3);
      gv3->SetName("gv3");
      gv3->SetMarkerColor(4);
      gv3->SetMarkerStyle(25);
      gv3->Draw("PEsame");
    }
    
    
    if(vn==2 && V_or_v==1)
    {
      vector<double> flowv22pt = getPt22(cent);
      vector<double> flowv22V = getV22(cent);
      vector<double> flowv22err = getV22_err(cent);
      vector<double> flowv24pt = getPt24(cent);
      vector<double> flowv24V = getV24(cent);
      vector<double> flowv24err = getV24_err(cent);
      
        cout<<"flowv2pt.size() "<<flowv22pt.size()<<endl;
      for(int i = 0 ; i < flowv22pt.size() ; ++i )
      {
        cpt_v22[i] = flowv22pt[i];
        cv_v22[i] = flowv22V[i];
        cerr_v22[i] = flowv22err[i];
        // cout<<"ctemp "<<ctempData[i]<<endl;
      }
      for(int i = 0 ; i < flowv24pt.size() ; ++i )
      {
        cpt_v24[i] = flowv24pt[i];
        cv_v24[i] = flowv24V[i];
        cerr_v24[i] = flowv24err[i];
        // cout<<"ctemp "<<ctempData[i]<<endl;
      }
      
      TGraphErrors * gv22 = new TGraphErrors(flowv24pt.size(),cpt_v22,cv_v22,cx_error,cerr_v22);
      gv22->SetName("gv22");
      gv22->SetMarkerColor(4);
      gv22->SetMarkerStyle(25);
      gv22->Draw("PEsame");
      
      TGraphErrors * gv24 = new TGraphErrors(flowv24pt.size(),cpt_v24,cv_v24,cx_error,cerr_v24);
      gv24->SetName("gv24");
      gv24->SetMarkerColor(1);
      gv24->SetMarkerStyle(22);
      if(cent!=0)
        gv24->Draw("PEsame");
      
      
    }
    
    
    
    
    
    
    TLatex * lcent = new TLatex(0.8*shiftX , -0.8*shiftY, Form("%d - %d %%",(int) (2.5*min_cents[cent]),(int) (2.5*max_cents[cent])) );
    if(cent==0)
    {
       if(etacut==0)
         TLatex * ldeta = new TLatex( 1.0*shiftX ,1.10*shiftY, "2<|#Delta#eta|<4" );
       else
         TLatex * ldeta = new TLatex( 1.0*shiftX ,1.10*shiftY, "-4<#Delta#eta<4" );
      ldeta->SetTextSize(ldeta->GetTextSize()*0.7);
      ldeta->Draw("same");
    
      TLatex * lcms = new TLatex( 3.0*shiftX , .7*shiftY, "CMS Preliminary" );
      lcms->SetTextSize(lcms->GetTextSize()*0.7);
      lcms->Draw("same");
      

       
       TLatex * lint = new TLatex( 1.0*shiftX , 1.60*shiftY, "#int L dt = 3.1 #mub^{-1}" );
       lint->SetTextSize(lint->GetTextSize()*0.65);
       lint->Draw("same");
    }
    if(cent==0 && V_or_v!=2)
    {
      TLatex * lass = new TLatex( 1.0*shiftX , 1.35*shiftY, "1<p_{T}^{assoc}<2 GeV/c" );
      lass->SetTextSize(lass->GetTextSize()*0.7);
      lass->Draw("same");
    }
    if(cent==legendpanel)
    {
      if(V_or_v==0)
        TLegend * leg = new TLegend(0.25,0.14,0.85,0.28);
      if(V_or_v==1 || V_or_v==2)
        TLegend * leg = new TLegend(0.25,0.14,0.85,0.28);
      leg->SetFillColor(0);
      leg->SetTextSize(0.055);
      leg->SetFillStyle(0);
      if(V_or_v==0)
        leg->AddEntry(gtemp,"PbPb 2.76TeV","p");
      else if(V_or_v==1)
        leg->AddEntry(gtemp,Form("v_{%d}^{f}, dihadron correlation",vn),"p");
      else if(V_or_v==2)
      {
        leg->AddEntry(gtemp,Form("v_{%d}^{f}, %d<p_{T}^{assoc}<%d GeV/c",vn,minpt[ptass],maxpt[ptass]),"p");
        leg->AddEntry(g24gev,Form("v_{%d}^{f}, 1<p_{T}^{assoc}<2 GeV/c",vn),"p");      
      }
      if(V_or_v==0)
        leg->AddEntry(gpp,"N_{ass}/N_{ass}^{PbPb} pp 2.76TeV","l");
      if(V_or_v==1 && vn==2)
      {
        leg->AddEntry(gv22,"v_{2}{2}","p");
        leg->AddEntry(gv24,"v_{2}{4}","p");  
      }
      if(V_or_v==1 && vn==3)
        leg->AddEntry(gv3,"v_{3}{2}","p");
      if(V_or_v==1 && vn==4)
        leg->AddEntry(gv4,"v_{4} LYZ","p");
      
      leg->SetTextFont(42);
      leg->SetTextSize(0.085);
      leg->Draw();
    }
    
    lcent->SetTextSize(lcent->GetTextSize()*0.7);
    lcent->Draw("same");
    if(cent==0)
    {
      if(V_or_v==0)
        TLatex * ltitle = new TLatex(0.8*shiftX , 0.7*shiftY, Form("V_{%d}^{f}",vn) );
      else
        TLatex * ltitle = new TLatex(0.8*shiftX , 0.7*shiftY, Form("v_{%d}^{f}",vn) );
      ltitle->SetTextSize(ltitle->GetTextSize()*0.7);
      ltitle->Draw("same");
    }
    zero->Draw("same");
    
    
    
  }
  
  // TGraphErrors* gv2 = new TGraphErrors(numPt,x_vector,tempData,x_error,tempErrorData);
  // gv2->SetName("gv2");
  // vector<TLatex*> latexvector;
  // latexvector.push_back(new TLatex( 2.0*shiftX , .8*shiftY, "V_{1}" ));
  // latexvector.push_back(new TLatex( 1.0*shiftX , -.8*shiftY, "2<|#Delta#eta|<4" ));
  // latexvector.push_back(new TLatex( 4.5*shiftX , .8*shiftY, "CMS Preliminary" ));
  // latexvector.push_back(new TLatex( 1.0*shiftX , -.6*shiftY, "1<p_{T}^{assoc}<2 GeV/c" ));
    
}

// 
TH2D* draw_single_2D(TString eventtype1="HIData_Minbias_2760GeV", TString tag1="All_INCLEFF1v5", int nmin=-1, int nmax=-1, int centmin=0, int centmax=1, int ptmin=1, int ptmax=0, bool IsSave=0)
{
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  // TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_All_INCLv5_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax1.root");
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),ptmin,ptmax);
  
  // TCanvas* c = new TCanvas("c","",500,500);
  // c->SetTheta(60.839);
  // c->SetPhi(38.0172);
  h->SetAxisRange(-4.3,4.3,"X");
//  h->SetAxisRange(3.78,4.35,"Z");
//  h->SetAxisRange(3.75,4.15,"Z");
//  h->SetAxisRange(5.68,6.55,"Z");// bin 1-0
//  h->SetAxisRange(5.68,7.2,"Z");// bin 1-0 peak
//  h->SetAxisRange(0.033,0.5,"Z"); // pythia
  // h->SetAxisRange(0.033,1.4,"Z"); // pythia peak
  // c3->cd(1);
  // h->Draw("surf1 fb");
  return h;


  double min = h->GetMinimum();
  TH2D* hzyam = (TH2D*)h->Clone("corr_zyam");
  for(int i=1;i<=hzyam->GetNbinsX();i++)
    for(int j=1;j<=hzyam->GetNbinsY();j++)
      hzyam->SetBinContent(i,j,h->GetBinContent(i,j)-min);
  // TCanvas* c1 = new TCanvas("c1","",500,500);
  // c1->SetTheta(60.839);
  // c1->SetPhi(38.0172);
  // hzyam->SetAxisRange(0,4.5-3.95,"Z");
  hzyam->SetZTitle("C'(#Delta#eta,#Delta#phi)");
  // return hzyam;
  // c3->cd(2);
  // hzyam->DrawCopy("surf1 fb");

  if(IsSave)
  {
//    SaveCanvas(c,"HI/corr",Form("corr2Dpeak_pttrg4-6_ptass2-4_cent%d-%d",centmin,centmax));
//   SaveCanvas(c1,"HI/corr",Form("corr2Dzyampeak_pttrg4-6_ptass2-4_cent%d-%d",centmin,centmax));
    // SaveCanvas(c,"HI/corr",Form("corr2Dpythia8peak_pttrg4-6_ptass2-4_cent%d-%d",centmin,centmax));
    // SaveCanvas(c1,"HI/corr",Form("corr2Dpythia8zyampeak_pttrg4-6_ptass2-4_cent%d-%d",centmin,centmax));
  }
}

void draw_compare_dEta(TString eventtype1="HIData_Minbias_2760GeV", TString tag1="All_INCLEFF1v5", int nmin=-1, int nmax=-1, int centmin=0, int centmax=1, int ptmin=3, int ptmax=2, bool IsSave=0)
{ 
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  // TString filename = Form("/net/hidsk0001/d00/scratch/dav2105/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/unmerged/4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TH1D* h = (TH1D*)Get1DCFdEtav3(filename.Data(),ptmin,ptmax,-1,1);
  TH1D* h1 = (TH1D*)Get1DCFdEtav3(filename.Data(),ptmin,ptmax,PI-0.7,PI+0.7);
  
  TCanvas* c = new TCanvas("c","",500,500);
  h->SetAxisRange(3.78,4.25,"Y");
  h->SetMarkerColor(kRed);
  h->Draw("PE");
//  h1->SetMarkerColor(1);
//  h1->Draw("PESAME");
}

void draw_compare_dPhi(TString eventtype1="HIData_Minbias_2760GeV", TString tag1="All_INCLEFF1v5", int nmin=-1, int nmax=-1, int centmin=0, int centmax=2, int ptmin=1, int ptmax=0, bool IsSave=0)
{
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TH1D* h = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptmin,ptmax,0,1.9);
  TH1D* h1 = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptmin,ptmax,1.9,4.2);

  TCanvas* c = new TCanvas("c","",500,500);
  h->SetAxisRange(3.75,4.4,"Y");
  h->SetMarkerColor(kRed);
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.65);
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*0.8);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.6);
//  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*0.8);
  h->Draw("PE");
  h1->SetMarkerColor(1);
  h1->Draw("PESAME");

  TF1* fit = new TF1("fit","[0]*(1+2*[1]*[1]*cos(2*x))",-PI/2.,3.*PI/2.);
  fit->SetParameters(3.85,0.05);
  fit->SetLineColor(kBlue);
  fit->Draw("Lsame");

  TF1* fit1 = new TF1("fit1","[0]*(1+2*[1]*[1]*cos(2*x))",-PI/2.,3.*PI/2.);
  fit1->SetParameters(3.85,0.03);
  fit1->SetLineColor(kGreen);
  fit1->Draw("Lsame");

  TLegend* legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h,"0<|#Delta#eta|<2","P");
  legend->AddEntry(h1,"2<|#Delta#eta|<4","P");
  legend->AddEntry(fit,"v2=5%","L");
  legend->AddEntry(fit1,"v2=3%","L");
  legend->Draw("same");

  TH1D* hzyam = GetJetCorrFunc1D_ZYAM(h);
  TH1D* hzyam1 = GetJetCorrFunc1D_ZYAM(h1);
  TCanvas* c1 = new TCanvas("c1","",500,500);
  hzyam->SetAxisRange(-0.05,10.6-9.6,"Y");
  hzyam->SetMarkerColor(kRed);
  hzyam->SetYTitle("C'(#Delta#phi)");
  hzyam->Draw("PE");
  hzyam1->SetMarkerColor(1);
  hzyam1->Draw("PESAME");

  TLegend* legend1 = new TLegend(0.6,0.75,0.9,0.9);
  legend1->SetFillColor(0);
  legend1->AddEntry(hzyam,"0<|#Delta#eta|<2","P");
  legend1->AddEntry(hzyam1,"2<|#Delta#eta|<4","P");
  legend1->Draw("same");

  TFile* fout = new TFile("corr1Ddphi_pttrg4-6_ptass2-4_cent0-2.root","recreate");
  h->SetName("corr_phi_eta0-2");
  h1->SetName("corr_phi_eta2-4");
  h->Write();
  h1->Write();
  fout->Close();

  if(IsSave)
  {
    SaveCanvas(c,"HI/corr","corr1Ddphi_pttrg4-6_ptass2-4_cent0-1");
    SaveCanvas(c1,"HI/corr","corr1Ddphizyam_pttrg4-6_ptass2-4_cent0-1");
  }
}

void draw_multicompare_dPhi(int ptmin=3, int ptmax=2, bool IsSave=0)
{
//  TString hidata = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_All_INCL_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
//  TString ppdata = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PPData_Minbias_7TeV/merged/PPData_Minbias_7TeV_MINBIAS_All_INCLEFF1TRG1HICOMPARE_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TString pppythia8 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_7TeV/merged/PythiaReco_Minbias_7TeV_PYTHIA8_MINBIAS_INCLGENHICOMPARE_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TString ppd6t = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_7TeV/merged/PythiaReco_Minbias_7TeV_D6T_INCLGENHICOMPARE_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
/*
  TString hiampt = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTReco_Minbias_2760GeV/merged/AMPTReco_Minbias_2760GeV_393_INCLv4_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  TString hiampteff1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTReco_Minbias_2760GeV/merged/AMPTReco_Minbias_2760GeV_393_INCLEFF1v4_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  TString hiamptgen = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTReco_Minbias_2760GeV/merged/AMPTReco_Minbias_2760GeV_393_INCLGENv4_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
*/
/*
  TString hiampt = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_393_INCLv4_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  TString hiampteff1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_393_INCLEFF1v4_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  TString hiamptgen = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_393_INCLGENv4_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
*/

  TString hidata = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_All_INCLv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  TString hidataeff1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_All_INCLEFF1v5_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");

  TH1D* h = (TH1D*)Get1DCFdPhiv3(hidata.Data(),2,1,0,4.4);
  TH1D* h1 = (TH1D*)Get1DCFdPhiv3(hidataeff1.Data(),ptmin,ptmax,0,4.4);

  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.8);

  TCanvas* c = new TCanvas("c","",500,500);
  h->SetAxisRange(0,8.5,"Y");
  h->SetMarkerColor(1);
  h->Draw("PE");
  h1->SetMarkerColor(kRed);
  h1->Draw("PESAME");
  TLegend* legend = new TLegend(0.4,0.8,0.9,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h,"PbPb data, Uncorrected","P");
  legend->AddEntry(h1,"PbPb data, corrected","P");
  legend->Draw("same");

  TCanvas* c1 = new TCanvas("c1","",500,500);
  TH1D* h1_clone = (TH1D*)h->Clone("ratio");
  h1_clone->SetYTitle("Ratio");
  h1_clone->Divide(h1);
  h1_clone->SetAxisRange(0.55,1.0,"Y");
  h1_clone->Draw();

  if(IsSave)
  {
    SaveCanvas(c,"HI/corr","corr1Ddphi_datacorrection_pttrg4-6_ptass2-4_cent0-2");
    SaveCanvas(c1,"HI/corr","corr1Ddphiratio_datacorrection_pttrg4-6_ptass2-4_cent0-2");
  }

return;
  TH1D* h = (TH1D*)Get1DCFdPhiv3(hiampt.Data(),ptmin,ptmax,0,4.4);
  TH1D* h1 = (TH1D*)Get1DCFdPhiv3(hiampteff1.Data(),ptmin,ptmax,0,4.4);
  TH1D* h2 = (TH1D*)Get1DCFdPhiv3(hiamptgen.Data(),ptmin,ptmax,0,4.4);

  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.8);

  TCanvas* c = new TCanvas("c","",500,500);
  h->SetAxisRange(0,8,"Y");
  h->SetMarkerColor(1);
  h->Draw("PE");
  h1->SetMarkerColor(kRed);
  h1->Draw("PESAME");
  h2->SetMarkerStyle(24);
  h2->Draw("PESAME");
  TLegend* legend = new TLegend(0.4,0.7,0.9,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h,"HYDJET RECO, Uncorrected","P");
  legend->AddEntry(h1,"HYDJET RECO, corrected","P");
  legend->AddEntry(h2,"HYDJET GEN","P");
  legend->Draw("same");

  TCanvas* c1 = new TCanvas("c1","",500,500);
  TH1D* h1_clone = (TH1D*)h1->Clone("ratio");
  h1_clone->SetYTitle("Ratio");
  h1_clone->Divide(h2);
  h1_clone->SetAxisRange(0.9,1.1,"Y");
  h1_clone->Draw();
  TF1* fit = new TF1("fit","[0]+[1]*x",0,PI);
  fit->SetParameters(1,0);
  fit->FixParameter(1,0);
  h1_clone->Fit("fit");
  fit->Draw("Lsame");

  if(IsSave)
  {
    SaveCanvas(c,"HI/corr","corr1Ddphi_closure_pttrg4-6_ptass2-4_cent0-2");
    SaveCanvas(c1,"HI/corr","corr1Ddphiratio_closure_pttrg4-6_ptass2-4_cent0-2");
  }

return;
  TF1* fit = new TF1("fit","[0]*(1+2*[1]*[1]*cos(2*x))",-PI/2.,3.*PI/2.);
  fit->SetParameters(10,0.05);
  fit->SetLineColor(kBlue);
  fit->Draw("Lsame");

  TF1* fit1 = new TF1("fit1","[0]*(1+2*[1]*[1]*cos(2*x))",-PI/2.,3.*PI/2.);
  fit1->SetParameters(10,0.02);
  fit1->SetLineColor(kGreen);
  fit1->Draw("Lsame");

  TLegend* legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(h,"PbPb 2.76TeV","P");
  legend->AddEntry(h1,"pp 7TeV","P");
//  legend->AddEntry(h2,"pythia8 7TeV","P");
  legend->AddEntry(fit,"v2=5%","L");
  legend->AddEntry(fit1,"v2=2%","L");
  legend->Draw("same");

  TH1D* hzyam = GetJetCorrFunc1D_ZYAM(h);
  TH1D* hzyam1 = GetJetCorrFunc1D_ZYAM(h1);
  TH1D* hzyam2 = GetJetCorrFunc1D_ZYAM(h2);
  TCanvas* c1 = new TCanvas("c1","",500,500);
  hzyam->SetAxisRange(-0.05,10.6-9.6,"Y");
  hzyam->SetMarkerColor(kRed);
  hzyam->SetYTitle("C'(#Delta#phi)");
  hzyam->Draw("PE");
  hzyam1->SetMarkerColor(1);
  hzyam1->Draw("PESAME");
//  hzyam2->SetMarkerStyle(24);
//  hzyam2->Draw("PESAME");

  TLegend* legend1 = new TLegend(0.6,0.75,0.9,0.9);
  legend1->SetFillColor(0);
  legend1->AddEntry(hzyam,"PbPb 2.76TeV","P");
  legend1->AddEntry(hzyam1,"pp 7TeV","P");
//  legend1->AddEntry(hzyam2,"pythia8 7TeV","P");
  legend1->Draw("same");

  if(IsSave)
  {
    SaveCanvas(c,"HI/corr","corr1Ddphi_multicompare_pttrg4-6_ptass2-4_cent0-2_short");
    SaveCanvas(c1,"HI/corr","corr1Ddphizyam_multicompare_pttrg4-6_ptass2-4_cent0-2_short");
  }
}

TH1D* draw_single_dPhi(TString eventtype1="HIData_Minbias_2760GeV", TString tag1="All_INCLEFF1v5", int nmin=-1, int nmax=-1, int centmin=0, int centmax=1, int ptmin=3, int ptmax=2, double detamin=0.0, double detamax=4.8, bool IsSave=0)
{
  // TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TString filename = Form("/net/hisrv0001/home/dav2105/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TH1D* h = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptmin,ptmax,detamin,detamax);
  // TF1* fitfunc=GetFitFunc_ZYAM(h);
  // h_zyam=GetJetCorrFunc1D_ZYAM(h);

  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.7);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.4);
  // h->SetMarkerColor(kRed);
  // h->SetAxisRange(5.68,6.25,"Y");
  
  // TCanvas* c = new TCanvas("c","",500,500);
//  h->GetYaxis()->UnZoom();
  // h->Draw("PE");
  // fitfunc->Draw("Lsame");
  // if(IsSave) SaveCanvas(c,"HI/corr",Form("corr1Ddphi_zyamexample"));

  // TCanvas* c1 = new TCanvas("c1","",500,500);  
  // h_zyam->Draw("PE");
  return h;

/*
  TF1* fit = new TF1("fit","[0]*(1+2*[1]*[1]*cos(2*x))",-PI/2.,3.*PI/2.);
  fit->SetParameters(h->Integral()/h->GetNbinsX(),0.02);
  fit->SetLineColor(kRed);
  fit->Draw("Lsame");
*/

/*
  TF1* fit = FitVnFunc(h,-PI/2.,3.*PI/2.);
  fit->SetLineColor(kRed);
  fit->Draw("Lsame");
*/
  // if(IsSave) SaveCanvas(c,"HI/corr",Form("corr1Ddphi_pttrg4-6_ptass2-4_cent%d-%d_fourier",centmin,centmax));
}

TH1D* jeremy_dPhi(TString eventtype1="HIData_Minbias_2760GeV", TString tag1="All_INCLEFF1v5", int nmin=-1, int nmax=-1, int centmin=0, int centmax=1, int ptmin=3, int ptmax=2, double detamin=0.0, double detamax=4.8, bool IsSave=0)
{
  TString filename = Form("/net/hisrv0001/home/dav2105/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TH1D* h = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptmin,ptmax,detamin,detamax);
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.7);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.4);
  return h;

}

void draw_one(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_ReTracking_INCLEFF1TRG1v5NEW", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, double detamin=2.0, double detamax=4.8, bool IsSave=0)
{
  TGraphErrors* gr_90 = compare_flow_pp_phi_multipad_pt<TGraph>(eventtype1,tag1,nmin,nmax,centmin,centmax,detamin,detamax,1,IsSave,1);
}

void draw_mult(double detamin=2.0, double detamax=4.8)
{
  TH1D ***hidata = compare_flow_pp_phi_multipad_pt<TH1D**>("HIData_Minbias_2760GeV","All_INCL",-1,-1,0,2,detamin,detamax,0,0,0);
  TH1D ***hidata_long = compare_flow_pp_phi_multipad_pt<TH1D**>("HIData_Minbias_2760GeV","All_INCL",-1,-1,0,2,2,4.2,0,0,0);
//  TH1D ***hiampt = compare_flow_pp_phi_multipad_pt<TH1D**>("AMPTReco_Minbias_2760GeV","393_INCL",-1,-1,0,1,detamin,detamax,0,0,0);
//  TH1D ***hihydjet = compare_flow_pp_phi_multipad_pt<TH1D**>("HydjetReco_Minbias_2760GeV","393_INCL",-1,-1,0,1,detamin,detamax,0,0,0);
//  TH1D ***ppdata = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1HICOMPARE",-1,-1,-1,-1,detamin,detamax,0,0,0);
//  TH1D ***pppythia8 = compare_flow_pp_phi_multipad_pt<TH1D**>("PythiaReco_Minbias_7TeV","PYTHIA8_MINBIAS_INCLGENHICOMPARE",-1,-1,-1,-1,detamin,detamax,0,0,0);
//  TH1D ***ppd6t = compare_flow_pp_phi_multipad_pt<TH1D**>("PythiaReco_Minbias_7TeV","D6T_INCLGENHICOMPARE",-1,-1,-1,-1,detamin,detamax,0,0,0);

  int ntrgptbins=3;
  int nassptbins=2;
  TCanvas* c = new TCanvas("c","",1000,700);
  makeMultiPanelCanvas(c,ntrgptbins,nassptbins,0.02,0.02,0.2,0.2,0.01);

  for(int itrg = 0; itrg<ntrgptbins; itrg++)
  {
    for(int jass = 0; jass<nassptbins; jass++)
    {
      if(itrg<jass) continue;
      hidata[itrg][jass]->SetMarkerColor(kRed);
      hidata_long[itrg][jass]->SetMarkerColor(1);
//      ppdata[itrg][jass]->SetMarkerColor(kRed);
//      ppd6t[itrg][jass]->SetMarkerColor(1);
 //     pppythia8[itrg][jass]->SetMarkerColor(1);
//      hiampt[itrg][jass]->SetMarkerColor(kRed);
//      hihydjet[itrg][jass]->SetMarkerColor(kBlue);
      c->cd(itrg*nassptbins+jass+1);
//      hidata[itrg][jass]->SetAxisRange(0,hidata[itrg][jass]->GetMaximum(),"Y");
      hidata[itrg][jass]->GetYaxis()->UnZoom();
      hidata[itrg][jass]->SetAxisRange(hidata[itrg][jass]->GetMinimum()*0.8,hidata[itrg][jass]->GetMaximum()*1.5,"Y");
      hidata[itrg][jass]->Draw("PE");
      hidata_long[itrg][jass]->Draw("PESAME");
//      ppd6t[itrg][jass]->Draw("PE");
//      pppythia8[itrg][jass]->Draw("PE");
//      ppdata[itrg][jass]->Draw("PESAME");
//      hiampt[itrg][jass]->Draw("PESAME");
//      hihydjet[itrg][jass]->Draw("PESAME");
    }
  }
}

void draw_mult_special()
{
  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,0,2,-1,1.0,0,0,0);
  TH1D ***hidata_long = compare_flow_pp_phi_multipad_pt<TH1D**>("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,0,2,1.0,1.9,0,0,0);
  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("HIData_Minbias_2760GeV","All_INCLEFF1v5",-1,-1,0,2,1.9,4.2,0,0,0);
  TH1D ***pppythia8_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv5",-1,-1,-1,-1,0,1.0,0,0,0);
  TH1D ***pppythia8_long = compare_flow_pp_phi_multipad_pt<TH1D**>("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv5",-1,-1,-1,-1,1.0,1.9,0,0,0);
  TH1D ***pppythia8_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PythiaReco_Minbias_2760GeV","PYTHIA8_GEN_INCLGENv5",-1,-1,-1,-1,1.9,4.2,0,0,0);

  int ntrgptbins=4;
  int nassptbins=2;
  TCanvas* c = new TCanvas("c","",900,450);
  makeMultiPanelCanvas(c,ntrgptbins,nassptbins,0.02,0.02,0.25,0.2,0.01);
  TCanvas* c1 = new TCanvas("c1","",350,700);
  makeMultiPanelCanvas(c1,2,4,0.02,0.02,0.25,0.2,0.01);

  for(int itrg = 0; itrg<4; itrg++)
  {
    for(int jass = 0; jass<4; jass++)
    {
      if(jass<itrg) continue;
      hidata_short[jass][itrg]->SetMarkerColor(kRed);
      hidata_long[jass][itrg]->SetMarkerColor(kRed);
      hidata_mid[jass][itrg]->SetMarkerColor(kRed);
      if(itrg==0)
      {
        hidata_short[jass][itrg]->SetAxisRange(5.59,6.99,"Y");
        hidata_long[jass][itrg]->SetAxisRange(5.59,6.99,"Y");
        hidata_mid[jass][itrg]->SetAxisRange(5.59,6.99,"Y");
      }
      else if(itrg==1)
      {
        hidata_short[jass][itrg]->SetAxisRange(0,0.195,"Y");
        hidata_long[jass][itrg]->SetAxisRange(0,0.195,"Y");
        hidata_mid[jass][itrg]->SetAxisRange(0,0.195,"Y");
      }
      else if(itrg==2)
      {
        hidata_short[jass][itrg]->SetAxisRange(0,0.069,"Y");
        hidata_long[jass][itrg]->SetAxisRange(0,0.069,"Y");
        hidata_mid[jass][itrg]->SetAxisRange(0,0.069,"Y");
      }
      else if(itrg==3)
      {
        hidata_short[jass][itrg]->SetAxisRange(0,0.059,"Y");
        hidata_long[jass][itrg]->SetAxisRange(0,0.059,"Y");
        hidata_mid[jass][itrg]->SetAxisRange(0,0.059,"Y");
      }
      else
      {
        hidata_short[jass][itrg]->GetYaxis()->UnZoom();
        hidata_long[jass][itrg]->GetYaxis()->UnZoom();
        hidata_mid[jass][itrg]->GetYaxis()->UnZoom();
      }
      SimpleShift1D(pppythia8_short[jass][itrg],hidata_short[jass][itrg]->GetMinimum());
      SimpleShift1D(pppythia8_long[jass][itrg],hidata_long[jass][itrg]->GetMinimum());
      SimpleShift1D(pppythia8_mid[jass][itrg],hidata_mid[jass][itrg]->GetMinimum());
//      pppythia8_short[jass][itrg]->SetLineStyle(9);
//      pppythia8_long[jass][itrg]->SetLineStyle(9);
//      pppythia8_mid[jass][itrg]->SetLineStyle(9);
//      pppythia8_short[jass][itrg]->SetAxisRange(5.7,6.69,"Y");
//      pppythia8_long[jass][itrg]->SetAxisRange(5.7,6.69,"Y");
//      pppythia8_mid[jass][itrg]->SetAxisRange(5.7,6.69,"Y");
    }
  }

  TLatex* latex_short = new TLatex(0.9,6.55,"0<|#Delta#eta|<1");
  TLatex* latex_long = new TLatex(0.9,6.5,"1<|#Delta#eta|<2");
  TLatex* latex_mid = new TLatex(0.9,6.55,"2<|#Delta#eta|<4");
/*
  TLatex* latex_trg1 = new TLatex(0.4,6.9,"2GeV/c<p^{trig}_{T}<4GeV/c");
  TLatex* latex_trg2 = new TLatex(0.4,6.9,"4GeV/c<p^{trig}_{T}<6GeV/c");
  TLatex* latex_trg3 = new TLatex(0.4,6.9,"6GeV/c<p^{trig}_{T}<8GeV/c");
  TLatex* latex_trg4 = new TLatex(0.4,6.9,"8GeV/c<p^{trig}_{T}<10GeV/c");
  TLatex* latex_ass = new TLatex(0.4,6.3,"2GeV/c<p^{assoc}_{T}<4GeV/c");
*/
  TLatex* latex_trg1 = new TLatex(0.4,6.8,"2<p^{trig}_{T}<4 GeV/c");
  TLatex* latex_trg2 = new TLatex(0.4,6.8,"4<p^{trig}_{T}<6 GeV/c");
  TLatex* latex_trg3 = new TLatex(0.4,6.8,"6<p^{trig}_{T}<8 GeV/c");
  TLatex* latex_trg4 = new TLatex(0.4,6.8,"8<p^{trig}_{T}<10 GeV/c");
  TLatex* latex_ass = new TLatex(0.4,6.5,"2<p^{assoc}_{T}<4 GeV/c");
  latex_short->SetTextSize(latex_short->GetTextSize()*2.2); 
  latex_long->SetTextSize(latex_long->GetTextSize()*1.7);
  latex_mid->SetTextSize(latex_mid->GetTextSize()*2.0);
  latex_trg1->SetTextSize(latex_trg1->GetTextSize()*1.7);
  latex_trg2->SetTextSize(latex_trg2->GetTextSize()*1.7);
  latex_trg3->SetTextSize(latex_trg3->GetTextSize()*1.7);
  latex_trg4->SetTextSize(latex_trg4->GetTextSize()*1.7);
  latex_ass->SetTextSize(latex_ass->GetTextSize()*1.35);

  TLegend* l = new TLegend(0.3,0.52,0.99,0.75);
  l->SetFillColor(0);
  l->AddEntry(hidata_short[0][0],"PbPb 2.76TeV, 0-5%","P"); 
  l->AddEntry(pppythia8_short[0][0],"PYTHIA8 2.76TeV","L");          
  l->Draw("same"); 

  hidata_mid[0][0]->GetXaxis()->SetTitleSize(hidata_mid[0][0]->GetXaxis()->GetTitleSize()*0.9);
  hidata_mid[0][0]->GetYaxis()->SetTitleSize(hidata_mid[0][0]->GetYaxis()->GetTitleSize()*0.8);
  hidata_mid[0][0]->GetXaxis()->SetTitleOffset(hidata_mid[0][0]->GetXaxis()->GetTitleOffset()*1.1);
  hidata_mid[0][0]->GetYaxis()->SetTitleOffset(hidata_mid[0][0]->GetYaxis()->GetTitleOffset()*1.3);
  hidata_mid[0][0]->GetXaxis()->SetLabelSize(hidata_mid[0][0]->GetXaxis()->GetLabelSize()*0.9);
  hidata_mid[0][0]->GetYaxis()->SetLabelSize(hidata_mid[0][0]->GetYaxis()->GetLabelSize()*0.9);
  hidata_mid[0][0]->GetXaxis()->SetLabelOffset(hidata_mid[0][0]->GetXaxis()->GetLabelOffset()*1.9);
  hidata_mid[0][0]->GetYaxis()->SetLabelOffset(hidata_mid[0][0]->GetYaxis()->GetLabelOffset()*1.3);

  c->cd(1);
  hidata_short[0][0]->Draw("PE");
  c->cd(2);
  hidata_short[1][0]->Draw("PE");
  c->cd(3);
  hidata_short[2][0]->Draw("PE");
  c->cd(4);
  hidata_short[3][0]->Draw("PE");
  c->cd(5);
  hidata_mid[0][0]->Draw("PE");
  c->cd(6);
  hidata_mid[1][0]->Draw("PE");
  c->cd(7);
  hidata_mid[2][0]->Draw("PE");
  c->cd(8);
  hidata_mid[3][0]->Draw("PE");

  c->cd(1);
  SimpleShift1D(pppythia8_short[0][0],0.07);
  pppythia8_short[0][0]->Draw("histSAME");
  c->cd(2);
  SimpleShift1D(pppythia8_short[1][0],0.12);
  pppythia8_short[1][0]->Draw("histSAME");
  c->cd(3);
  SimpleShift1D(pppythia8_short[2][0],0.2);
  pppythia8_short[2][0]->Draw("histSAME");
  c->cd(4);
  SimpleShift1D(pppythia8_short[3][0],0.27);
  pppythia8_short[3][0]->Draw("histSAME");
  c->cd(5);
  SimpleShift1D(pppythia8_mid[0][0],0.07);
  pppythia8_mid[0][0]->Draw("histSAME");
  c->cd(6);
  SimpleShift1D(pppythia8_mid[1][0],0.12);
  pppythia8_mid[1][0]->Draw("histSAME");
  c->cd(7);
  SimpleShift1D(pppythia8_mid[2][0],0.2);
  pppythia8_mid[2][0]->Draw("histSAME");
  c->cd(8);
  SimpleShift1D(pppythia8_mid[3][0],0.27);
  pppythia8_mid[3][0]->Draw("histSAME");

  c->cd(1);
  latex_trg1->Draw("same");
  l->Draw("same");
  c->cd(2);
  latex_trg2->Draw("same");
  c->cd(3);
  latex_trg3->Draw("same");
  c->cd(4);
  latex_trg4->Draw("same");
  latex_short->Draw("same");
  c->cd(5);
  latex_ass->Draw("same");
  c->cd(8);
  latex_mid->Draw("same");

  SaveCanvas(c,"HI/corr","corr1Ddphi_all_final");
}

double draw_vn_covariance(int v1 = 2, int v2 = 3)
{
  TH2D * cov = new TH2D("cov",Form(";(V_{%d}-<V_{%d}>)/#sigma_{V_{%d}};(V_{%d}-<V_{%d}>)/#sigma_{V_{%d}}",v1,v1,v1,v2,v2,v2),100,-4.0,4.0,100,-4.0,4.0);

  double r = 0.0, sigma1 = 0.0, sigma2 = 0.0, x1sum = 0.0 , x2sum = 0.0;
  for(int trg_pt = 0 ; trg_pt < 4 ; ++trg_pt)
  {
    for(int ass_pt = 0 ; ass_pt < 4 ; ++ass_pt)
    {
    
      TF1 * myf = draw_fit(trg_pt,ass_pt,0,2,Form("AllPhysicsAdd_INCLEFF1v8Eric"),0);
      double x1_0 = myf->GetParameter(v1);
      double x2_0 = myf->GetParameter(v2);
      
      for(int i = 1 ; i <= 10 ; ++i)
      {
        myf = draw_fit(trg_pt,ass_pt,0,2,Form("AllPhysics%d_INCLEFF1v8Eric",i),0);
        double x1 = myf->GetParameter(v1);
        double x2 = myf->GetParameter(v2);
        double dx1 = myf->GetParError(v1);
        double dx2 = myf->GetParError(v2);
        
        double delta_x1 = (x1 - x1_0)/dx1;
        double delta_x2 = (x2 - x2_0)/dx2;
        
        cov->Fill(delta_x1,delta_x2);
        
        // x1sum += 
        
      }
    }
  }
  
  cov->Draw("colz");
  c1->SaveAs(Form("cov_v%d_v%d.gif",v1,v2));
  // cout<<"Cov V"<<v1<<" and V"<<v2<<": "<<cov->GetCovariance()<<endl;
  return cov->GetCovariance();

}

TH1D * draw_scatterplot()
{
  int pt_trg[5] = {2,4,6,8,10};
  TH2D * dummy = new TH2D("dummy",";n;V_{n} [10^{-2}]",100,0,6,100,-1,1);
  dummy->Draw();
  int ass_pt = 0, trg_pt = 3, ass_pt = 0;
  const int numV = 5;
  TF1 * fcore = draw_fit(trg_pt,ass_pt,0,2,Form("All_INCLEFF1v8Eric"),0);
  
  TLegend * leg = new TLegend(0.25,0.20,0.78,0.34);
  
  

  double tempData1[numV];
  double tempData2[numV];
  double tempErrorData1[numV];
  double tempErrorData2[numV];
  double x_vector[numV] = {1,2,3,4,5};
  double x_error[numV] = {0,0,0,0,0};
  for(int i = 0 ; i < numV ; ++i)
  {
    tempData1[i] = fcore->GetParameter(i+1)*100;
    tempErrorData1[i] = fcore->GetParError(i+1)*100;
  }
  TGraphErrors* gcore = new TGraphErrors(numV,x_vector,tempData1,x_error,tempErrorData1);
  gcore->SetName("gcore");
  gcore->SetMarkerColor(2);
  gcore->Draw("PEsame");
  leg->AddEntry(gcore, Form("CorePhysics"),"p");
  
  
  for(int i = 1 ; i <= 10 ; ++i)
  {
    myf = draw_fit(trg_pt,ass_pt,0,2,Form("AllPhysics%d_INCLEFF1v8Eric",i),0);
    for(int j = 0 ; j < numV ; ++j)
    {
      tempData2[j] = myf->GetParameter(j+1)*100;
      tempErrorData2[j] = myf->GetParError(j+1)*100;
    }
    TGraphErrors* gsample = new TGraphErrors(numV,x_vector,tempData2,x_error,tempErrorData2);
    gsample->SetName("gsample");
    gsample->SetMarkerColor(1);
    gsample->SetMarkerStyle(4);
    gsample->Draw("PEsame");
    
  }
  leg->AddEntry(gsample, Form("AllPhysics Subsample"),"p");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.065);
  leg->Draw();
  // TLatex * lass = new TLatex( -4.5 , pull->GetMaximum()*3.0/5.0, Form("%d<p_{T}^{ass}<%d GeV",pt_ass[0],pt_ass[1]));
  // TLatex * ltrg = new TLatex( -4.5 , pull->GetMaximum()*2.5/5.0, Form("%d<p_{T}^{trg}<%d GeV",pt_trg[pttrg],pt_trg[pttrg+1]));
  c1->SaveAs("fluctuation_scatterplot.gif");

}

void all_covariance()
{
  ofstream covlist;
  covlist.open ("covlist.txt", ios::app);
  
  for(int i = 1 ; i <= 5 ; ++i) 
  {
    for(int j = 1 ; j <= 5 ; ++j) 
    {
      covlist<<"Cov V"<<i<<" and V"<<j<<": "<<draw_vn_covariance(i,j)<<endl;
    }
  }
  
  covlist.close();
}


