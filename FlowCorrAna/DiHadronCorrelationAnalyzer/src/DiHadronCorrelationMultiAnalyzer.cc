#include "../interface/DiHadronCorrelationMultiAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TVector3.h>
#include <vector> 
#include <iostream>
#include "Math/Vector3D.h"

using namespace std;

DiHadronCorrelationMultiAnalyzer::DiHadronCorrelationMultiAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig),
  signalTrgEffWeight(0),
  bkgTrgEffWeight(0),
  bkgAssEffWeight(0)
{
  cutPara.IsSymmetrize=1;
  cutPara.IsHarmonics = iConfig.getParameter<bool>("IsHarmonics");
  cutPara.IsHarmonicsEta1Eta2 = iConfig.getParameter<bool>("IsHarmonicsEta1Eta2");
  bkgFactor = 10; 
}

DiHadronCorrelationMultiAnalyzer::~DiHadronCorrelationMultiAnalyzer()
{}

void DiHadronCorrelationMultiAnalyzer::beginJob()
{
  double etabinwidth = (cutPara.etatrgmax-cutPara.etaassmin-cutPara.etatrgmin+cutPara.etaassmax)/NEtaBins;
  double phibinwidth = 2*PI/NPhiBins;

  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  if(cutPara.IsHarmonicsEta1Eta2)
  {
    for(int ieta1=0; ieta1<16; ieta1++)
      for(int ieta2=0; ieta2<16; ieta2++)
      {
        hSignalCosn_eta1eta2[ieta1][ieta2] = theOutputs->make<TH2D>(Form("signalcosn_eta1eta2_eta%d_eta%d",ieta1,ieta2),";cos(n#Delta#phi);n",500,-1.0,1.0,5,0.5,5.5);
        hBackgroundCosn_eta1eta2[ieta1][ieta2] = theOutputs->make<TH2D>(Form("backgroundcosn_eta1eta2_eta%d_eta%d",ieta1,ieta2),";cos(n#Delta#phi);n",500,-1.0,1.0,5,0.5,5.5);
      }
  }

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;
      hSignal[itrg][jass] = theOutputs->make<TH2D>(Form("signal_trg%d_ass%d",itrg,jass),";#Delta#eta;#Delta#phi",
                                     NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,                    
	                             NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

      hBackground[itrg][jass] = theOutputs->make<TH2D>(Form("background_trg%d_ass%d",itrg,jass),";#Delta#eta;#Delta#phi",
                                     NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,
                                     NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

      hCorrelation[itrg][jass] = theOutputs->make<TH2D>(Form("correlation_trg%d_ass%d",itrg,jass),";#Delta#eta;#Delta#phi",
                                     NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,
                                     NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

      if(cutPara.IsHarmonics)
      {
        hSignalCosn[itrg][jass] = theOutputs->make<TH2D>(Form("signalcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",20000,-1.0,1.0,3,1.5,4.5);
        hBackgroundCosn[itrg][jass] = theOutputs->make<TH2D>(Form("backgroundcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",20000,-1.0,1.0,3,1.5,4.5);
/*
        hSignalSinn[itrg][jass] = theOutputs->make<TH2D>(Form("signalsinn_trg%d_ass%d",itrg,jass),";sin(n#Delta#phi);n",50000,-1.0,1.0,3,1.5,4.5);
        hBackgroundSinn[itrg][jass] = theOutputs->make<TH2D>(Form("backgroundsinn_trg%d_ass%d",itrg,jass),";sin(n#Delta#phi);n",50000,-1.0,1.0,3,1.5,4.5);
        hSignalRhon[itrg][jass] = theOutputs->make<TH2D>(Form("signalrhon_trg%d_ass%d",itrg,jass),";#rho;n",50000,-1.0,1.0,3,1.5,4.5);
        hBackgroundRhon[itrg][jass] = theOutputs->make<TH2D>(Form("backgroundrhon_trg%d_ass%d",itrg,jass),";#rho;n",50000,-1.0,1.0,3,1.5,4.5);
*/
      }

      hSignal2PEPCorrelator[itrg][jass] = theOutputs->make<TH1D>(Form("signal2pepcorrelator_trg%d_ass%d",itrg,jass),";cos(#phi_{#alpha}-3#phi_{#beta}+2#Psi_{2})",600,-0.6,0.6);
      hBackground2PEPCorrelator[itrg][jass] = theOutputs->make<TH1D>(Form("background2pepcorrelator_trg%d_ass%d",itrg,jass),";cos(#phi_{#alpha}-3#phi_{#beta}+2#Psi_{2})",600,-0.6,0.6);
/*
      hSignal_pt1pt2 = theOutputs->make<TH2D>("signal_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
      hBackground_pt1pt2 = theOutputs->make<TH2D>("background_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
      hCorrelation_pt1pt2 = theOutputs->make<TH2D>("correlation_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
*/
      hSignal_eta1eta2[itrg][jass] = theOutputs->make<TH2D>(Form("signal_eta1eta2_trg%d_ass%d",itrg,jass),";#eta_{1};#eta_{2}",
                                     NEtaBins*2+1,cutPara.etatrgmin-etabinwidth/2.,cutPara.etatrgmax+etabinwidth/2.,
                                     NEtaBins*2+1,cutPara.etaassmin-etabinwidth/2.,cutPara.etaassmax+etabinwidth/2.);
      hBackground_eta1eta2[itrg][jass] = theOutputs->make<TH2D>(Form("background_eta1eta2_trg%d_ass%d",itrg,jass),";#eta_{1};#eta_{2}",
                                     NEtaBins*2+1,cutPara.etatrgmin-etabinwidth/2.,cutPara.etatrgmax+etabinwidth/2.,
                                     NEtaBins*2+1,cutPara.etaassmin-etabinwidth/2.,cutPara.etaassmax+etabinwidth/2.);
      hCorrelation_eta1eta2[itrg][jass] = theOutputs->make<TH2D>(Form("correlation_eta1eta2_trg%d_ass%d",itrg,jass),";#eta_{1};#eta_{2}",
                                     NEtaBins*2+1,cutPara.etatrgmin-etabinwidth/2.,cutPara.etatrgmax+etabinwidth/2.,
                                     NEtaBins*2+1,cutPara.etaassmin-etabinwidth/2.,cutPara.etaassmax+etabinwidth/2.);

      hSignal_phi1phi2[itrg][jass] = theOutputs->make<TH2D>(Form("signal_phi1phi2_trg%d_ass%d",itrg,jass),";#phi_{1};#phi_{2}",
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.,
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.);
      hBackground_phi1phi2[itrg][jass] = theOutputs->make<TH2D>(Form("background_phi1phi2_trg%d_ass%d",itrg,jass),";#phi_{1};#phi_{2}",
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.,
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.);
      hCorrelation_phi1phi2[itrg][jass] = theOutputs->make<TH2D>(Form("correlation_phi1phi2_trg%d_ass%d",itrg,jass),";#phi_{1};#phi_{2}",
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.,
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.);
    }
  }
  DiHadronCorrelationMultiBase::beginJob();
}

void DiHadronCorrelationMultiAnalyzer::endJob()
{
  DiHadronCorrelationMultiBase::endJob();

  if(!cutPara.IsCorr) return;
  
  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;
  cout<< "Total of " << eventcorrArray.size() << " events are selected!" << endl;   
  cout<< "Start running correlation analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);

    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;

    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
//      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) break;
      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      hDeltaZvtx->Fill(deltazvtx);

      if(fabs(deltazvtx)>0.3) continue;

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void DiHadronCorrelationMultiAnalyzer::NormalizeHists()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;

      if(hSignal[itrg][jass]->Integral()==0) continue;
      if(hBackground[itrg][jass]->Integral()==0) continue;

      double  etabinwidth = hSignal[itrg][jass]->GetXaxis()->GetBinWidth(1);
      double  phibinwidth = hSignal[itrg][jass]->GetYaxis()->GetBinWidth(1);
 
      hSignal[itrg][jass]->Scale(1.0/etabinwidth/phibinwidth);
      hSignal_eta1eta2[itrg][jass]->Scale(1.0/etabinwidth/etabinwidth);
      hSignal_phi1phi2[itrg][jass]->Scale(1.0/phibinwidth/phibinwidth);

      hBackground[itrg][jass]->Scale(1.0/etabinwidth/phibinwidth);
      hBackground_eta1eta2[itrg][jass]->Scale(1.0/etabinwidth/etabinwidth);
      hBackground_phi1phi2[itrg][jass]->Scale(1.0/phibinwidth/phibinwidth);

      hCorrelation[itrg][jass]->Add(hSignal[itrg][jass]);
      hCorrelation[itrg][jass]->Divide(hBackground[itrg][jass]);
      hCorrelation[itrg][jass]->Scale(hBackground[itrg][jass]->GetBinContent(hBackground[itrg][jass]->FindBin(0,0)));  

     if(hBackground_eta1eta2[itrg][jass]) hCorrelation_eta1eta2[itrg][jass]->Divide(hBackground_eta1eta2[itrg][jass]);
     if(hBackground_phi1phi2[itrg][jass]) hCorrelation_phi1phi2[itrg][jass]->Divide(hBackground_phi1phi2[itrg][jass]);
    }
  }
/*
  if(hBackground_pt1pt2)
  {
    hCorrelation_pt1pt2->Add(hSignal_pt1pt2);
    hCorrelation_pt1pt2->Divide(hBackground_pt1pt2);
  }
*/
}

void DiHadronCorrelationMultiAnalyzer::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;

      unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr.pVect_ass[jass].size();
      double nMultCorr_trg = eventcorr.nMultCorrVect_trg[itrg];

      double sumcosn[15]={0};
      double npairs[15]={0};
      double sumcosn_eta1eta2[16][16][5] = {{{0.0}}};
      double npairs_eta1eta2[16][16][5] = {{{0.0}}};
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr.pVect_trg[itrg])[ntrg];	  
        double effweight_trg = (eventcorr.effVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta();
        double phi_trg = pvector_trg.Phi();
        double pt_trg = pvector_trg.Pt();
        double eta_trg_dau1 = -999.9;
        double phi_trg_dau1 = -999.9;
//        double pt_trg_dau1 = -999.9;
        double eta_trg_dau2 = -999.9;
        double phi_trg_dau2 = -999.9;
//        double pt_trg_dau2 = -999.9;
        if(cutPara.IsCheckTrgV0Dau)
        {
          TLorentzVector pvector_trg_dau1 = (eventcorr.pVect_trg_dau1[itrg])[ntrg];
          eta_trg_dau1 = pvector_trg_dau1.Eta();
          phi_trg_dau1 = pvector_trg_dau1.Phi();
//          pt_trg_dau1 = pvector_trg_dau1.Pt();

          TLorentzVector pvector_trg_dau2 = (eventcorr.pVect_trg_dau2[itrg])[ntrg];
          eta_trg_dau2 = pvector_trg_dau2.Eta();
          phi_trg_dau2 = pvector_trg_dau2.Phi();
//          pt_trg_dau2 = pvector_trg_dau2.Pt();
        }

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr.pVect_ass[jass])[nass];   
          double effweight_ass = (eventcorr.effVect_ass[jass])[nass];
          double eta_ass = pvector_ass.Eta();
          double phi_ass = pvector_ass.Phi();
          double pt_ass = pvector_ass.Pt();
          double eta_ass_dau1 = -999.9;
          double phi_ass_dau1 = -999.9;
//          double pt_ass_dau1 = -999.9;
          double eta_ass_dau2 = -999.9;
          double phi_ass_dau2 = -999.9;
//          double pt_ass_dau2 = -999.9;
          if(cutPara.IsCheckAssV0Dau)
          {
            TLorentzVector pvector_ass_dau1 = (eventcorr.pVect_ass_dau1[jass])[nass];
            eta_ass_dau1 = pvector_ass_dau1.Eta();
            phi_ass_dau1 = pvector_ass_dau1.Phi();
//            pt_ass_dau1 = pvector_ass_dau1.Pt();

            TLorentzVector pvector_ass_dau2 = (eventcorr.pVect_ass_dau2[jass])[nass];
            eta_ass_dau2 = pvector_ass_dau2.Eta();
            phi_ass_dau2 = pvector_ass_dau2.Phi();
//            pt_ass_dau2 = pvector_ass_dau2.Pt();
          }

          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

          if(deltaEta==0.0 && deltaPhi==0.0 && pt_trg==pt_ass) continue; 

          if(cutPara.IsCheckTrgV0Dau)
          {
            double deltaPhi1_dau=GetDeltaPhi(phi_ass,phi_trg_dau1);
            double deltaEta1_dau=GetDeltaEta(eta_ass,eta_trg_dau1);
            double deltaPhi2_dau=GetDeltaPhi(phi_ass,phi_trg_dau2);
            double deltaEta2_dau=GetDeltaEta(eta_ass,eta_trg_dau2);

            if(fabs(deltaEta1_dau)<0.03 && fabs(deltaPhi1_dau)<0.03) {cout<<deltaPhi1_dau<<" "<<deltaEta1_dau<<" ; rejected!"<<endl; continue;}
            if(fabs(deltaEta2_dau)<0.03 && fabs(deltaPhi2_dau)<0.03) {cout<<deltaPhi2_dau<<" "<<deltaEta2_dau<<" ; rejected!"<<endl; continue;}
          }
          if(cutPara.IsCheckAssV0Dau)
          {
            double deltaPhi1_dau=GetDeltaPhi(phi_trg,phi_ass_dau1);
            double deltaEta1_dau=GetDeltaEta(eta_trg,eta_ass_dau1);
            double deltaPhi2_dau=GetDeltaPhi(phi_trg,phi_ass_dau2);
            double deltaEta2_dau=GetDeltaEta(eta_trg,eta_ass_dau2);

            if(fabs(deltaEta1_dau)<0.03 && fabs(deltaPhi1_dau)<0.03) {cout<<deltaPhi1_dau<<" "<<deltaEta1_dau<<" ; rejected!"<<endl; continue;}
            if(fabs(deltaEta2_dau)<0.03 && fabs(deltaPhi2_dau)<0.03) {cout<<deltaPhi2_dau<<" "<<deltaEta2_dau<<" ; rejected!"<<endl; continue;}
          }

          double effweight = effweight_trg * effweight_ass;

          if(cutPara.IsHarmonics && fabs(deltaEta)>2) 
          {
            for(int nn = 1; nn<4; nn++)
            {
              sumcosn[nn] = sumcosn[nn] + cos((nn+1)*fabs(deltaPhi))/effweight;
              npairs[nn] += 1.0/effweight;
            }
          }

          if(cutPara.IsHarmonicsEta1Eta2 && itrg==0 && jass==0)
          {
            int ieta1 = (int)(eta_trg/0.3)+8;
            int ieta2 = (int)(eta_ass/0.3)+8;
            if(eta_trg<0) ieta1--;
            if(eta_ass<0) ieta2--;
            for(int nn = 1; nn<4; nn++)
            {
              sumcosn_eta1eta2[ieta1][ieta2][nn] = sumcosn_eta1eta2[ieta1][ieta2][nn] + cos((nn+1)*fabs(deltaPhi))/effweight;                             
              npairs_eta1eta2[ieta1][ieta2][nn] += 1.0/effweight;
            }
          }

          if(!cutPara.IsSymmetrize)
          {
            hSignal[itrg][jass]->Fill(deltaEta,deltaPhi,1.0/effweight/nMultCorr_trg);
            hSignal_eta1eta2[itrg][jass]->Fill(eta_trg,eta_ass,1.0/effweight/nMultCorr_trg);
            hSignal_phi1phi2[itrg][jass]->Fill(phi_trg,phi_ass,1.0/effweight/nMultCorr_trg);
          }
          else
          {
            hSignal[itrg][jass]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[itrg][jass]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[itrg][jass]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[itrg][jass]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[itrg][jass]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[itrg][jass]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal_eta1eta2[itrg][jass]->Fill(eta_trg,eta_ass,1.0/effweight/nMultCorr_trg);
            hSignal_phi1phi2[itrg][jass]->Fill(phi_trg,phi_ass,1.0/effweight/nMultCorr_trg);
            hSignal_eta1eta2[itrg][jass]->Fill(eta_ass,eta_trg,1.0/effweight/nMultCorr_trg);
            hSignal_phi1phi2[itrg][jass]->Fill(phi_ass,phi_trg,1.0/effweight/nMultCorr_trg);
          }
        }
      }

      if(cutPara.IsHarmonics) 
      { 
        for(int nn = 1; nn<4; nn++) 
        {
          if(!npairs[nn]) continue;
          sumcosn[nn]=sumcosn[nn]/npairs[nn];
          hSignalCosn[itrg][jass]->Fill(sumcosn[nn],nn+1);
        }
      }

      if(cutPara.IsHarmonicsEta1Eta2 && itrg==0 && jass==0)
      {
        for(int ieta1=0; ieta1<16; ieta1++)
          for(int ieta2=0; ieta2<16; ieta2++)
            for(int nn = 1; nn<4; nn++)
            {
              if(!npairs_eta1eta2[ieta1][ieta2][nn]) continue;
              sumcosn_eta1eta2[ieta1][ieta2][nn]=sumcosn_eta1eta2[ieta1][ieta2][nn]/npairs_eta1eta2[ieta1][ieta2][nn];
              hSignalCosn_eta1eta2[ieta1][ieta2]->Fill(sumcosn_eta1eta2[ieta1][ieta2][nn],nn+1);
            }
      }
    } 
}

void DiHadronCorrelationMultiAnalyzer::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;

      unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr_ass.pVect_ass[jass].size();
      double nMultCorr_trg = eventcorr_trg.nMultCorrVect_trg[itrg];

      double sumcosn[15]={0};
      double npairs[15]={0};
      double sumcosn_eta1eta2[16][16][5] = {{{0.0}}};
      double npairs_eta1eta2[16][16][5] = {{{0.0}}};
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[itrg])[ntrg];	  
        double effweight_trg = (eventcorr_trg.effVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta();
        double phi_trg = pvector_trg.Phi();
        double pt_trg = pvector_trg.Pt();
        double eta_trg_dau1 = -999.9;
        double phi_trg_dau1 = -999.9;
//        double pt_trg_dau1 = -999.9;
        double eta_trg_dau2 = -999.9;
        double phi_trg_dau2 = -999.9;
//        double pt_trg_dau2 = -999.9;
        if(cutPara.IsCheckTrgV0Dau)
        {
          TLorentzVector pvector_trg_dau1 = (eventcorr_trg.pVect_trg_dau1[itrg])[ntrg];
          eta_trg_dau1 = pvector_trg_dau1.Eta();
          phi_trg_dau1 = pvector_trg_dau1.Phi();
//          pt_trg_dau1 = pvector_trg_dau1.Pt();

          TLorentzVector pvector_trg_dau2 = (eventcorr_trg.pVect_trg_dau2[itrg])[ntrg];
          eta_trg_dau2 = pvector_trg_dau2.Eta();
          phi_trg_dau2 = pvector_trg_dau2.Phi();
//          pt_trg_dau2 = pvector_trg_dau2.Pt();
        }

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[jass])[nass];   
          double effweight_ass = (eventcorr_ass.effVect_ass[jass])[nass];
          double eta_ass = pvector_ass.Eta();
          double phi_ass = pvector_ass.Phi();
          double pt_ass = pvector_ass.Pt();
          double eta_ass_dau1 = -999.9;
          double phi_ass_dau1 = -999.9;
//          double pt_ass_dau1 = -999.9;
          double eta_ass_dau2 = -999.9;
          double phi_ass_dau2 = -999.9;
//          double pt_ass_dau2 = -999.9;
          if(cutPara.IsCheckAssV0Dau)
          {
            TLorentzVector pvector_ass_dau1 = (eventcorr_ass.pVect_ass_dau1[jass])[nass];
            eta_ass_dau1 = pvector_ass_dau1.Eta();
            phi_ass_dau1 = pvector_ass_dau1.Phi();
//            pt_ass_dau1 = pvector_ass_dau1.Pt();

            TLorentzVector pvector_ass_dau2 = (eventcorr_ass.pVect_ass_dau2[jass])[nass];
            eta_ass_dau2 = pvector_ass_dau2.Eta();
            phi_ass_dau2 = pvector_ass_dau2.Phi();
//            pt_ass_dau2 = pvector_ass_dau2.Pt();
          }

          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

          if(deltaEta==0.0 && deltaPhi==0.0 && pt_trg==pt_ass) continue; // two particles are identical

          if(cutPara.IsCheckTrgV0Dau)
          {
            double deltaPhi1_dau=GetDeltaPhi(phi_ass,phi_trg_dau1);
            double deltaEta1_dau=GetDeltaEta(eta_ass,eta_trg_dau1);
            double deltaPhi2_dau=GetDeltaPhi(phi_ass,phi_trg_dau2);
            double deltaEta2_dau=GetDeltaEta(eta_ass,eta_trg_dau2);

            if(fabs(deltaEta1_dau)<0.03 && fabs(deltaPhi1_dau)<0.03) {cout<<deltaPhi1_dau<<" "<<deltaEta1_dau<<" ; rejected!"<<endl; continue;}
            if(fabs(deltaEta2_dau)<0.03 && fabs(deltaPhi2_dau)<0.03) {cout<<deltaPhi2_dau<<" "<<deltaEta2_dau<<" ; rejected!"<<endl; continue;}
          }
          if(cutPara.IsCheckAssV0Dau)
          {
            double deltaPhi1_dau=GetDeltaPhi(phi_trg,phi_ass_dau1);
            double deltaEta1_dau=GetDeltaEta(eta_trg,eta_ass_dau1);
            double deltaPhi2_dau=GetDeltaPhi(phi_trg,phi_ass_dau2);
            double deltaEta2_dau=GetDeltaEta(eta_trg,eta_ass_dau2);

            if(fabs(deltaEta1_dau)<0.03 && fabs(deltaPhi1_dau)<0.03) {cout<<deltaPhi1_dau<<" "<<deltaEta1_dau<<" ; rejected!"<<endl; continue;}
            if(fabs(deltaEta2_dau)<0.03 && fabs(deltaPhi2_dau)<0.03) {cout<<deltaPhi2_dau<<" "<<deltaEta2_dau<<" ; rejected!"<<endl; continue;}
          }

          double effweight = effweight_trg * effweight_ass * nMultCorr_trg;

          if(cutPara.IsHarmonics && fabs(deltaEta)>2) 
          {
            for(int nn = 1; nn<4; nn++)
            {
              sumcosn[nn] = sumcosn[nn] + cos((nn+1)*fabs(deltaPhi))/effweight;
              npairs[nn] += 1.0/effweight;
            }
          }

          if(cutPara.IsHarmonicsEta1Eta2 && itrg==0 && jass==0)
          {
            int ieta1 = (int)(eta_trg/0.3)+8;
            int ieta2 = (int)(eta_ass/0.3)+8;
            if(eta_trg<0) ieta1--;
            if(eta_ass<0) ieta2--;
            for(int nn = 1; nn<4; nn++)
            {
              sumcosn_eta1eta2[ieta1][ieta2][nn] = sumcosn_eta1eta2[ieta1][ieta2][nn] + cos((nn+1)*fabs(deltaPhi))/effweight;
              npairs_eta1eta2[ieta1][ieta2][nn] += 1.0/effweight;
            }
          }

          if(!cutPara.IsSymmetrize)
          {
            hBackground[itrg][jass]->Fill(deltaEta,deltaPhi,1.0/effweight);
            hBackground_eta1eta2[itrg][jass]->Fill(eta_trg,eta_ass,1.0/effweight);
            hBackground_phi1phi2[itrg][jass]->Fill(phi_trg,phi_ass,1.0/effweight);
          }
          else
          {
            hBackground[itrg][jass]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground_eta1eta2[itrg][jass]->Fill(eta_trg,eta_ass,1.0/effweight);
            hBackground_phi1phi2[itrg][jass]->Fill(phi_trg,phi_ass,1.0/effweight);
            hBackground_eta1eta2[itrg][jass]->Fill(eta_ass,eta_trg,1.0/effweight);
            hBackground_phi1phi2[itrg][jass]->Fill(phi_ass,phi_trg,1.0/effweight);
          }
        }
      }

      if(cutPara.IsHarmonics)
      {
        for(int nn = 1; nn<4; nn++)
        {
          if(!npairs[nn]) continue;
          sumcosn[nn]=sumcosn[nn]/npairs[nn];
          hBackgroundCosn[itrg][jass]->Fill(sumcosn[nn],nn+1);
        }
      }

      if(cutPara.IsHarmonicsEta1Eta2 && itrg==0 && jass==0)
      {
        for(int ieta1=0; ieta1<16; ieta1++)
          for(int ieta2=0; ieta2<16; ieta2++)
            for(int nn = 1; nn<4; nn++)
            {
                if(!npairs_eta1eta2[ieta1][ieta2][nn]) continue;
                sumcosn_eta1eta2[ieta1][ieta2][nn]=sumcosn_eta1eta2[ieta1][ieta2][nn]/npairs_eta1eta2[ieta1][ieta2][nn];
                hBackgroundCosn_eta1eta2[ieta1][ieta2]->Fill(sumcosn_eta1eta2[ieta1][ieta2][nn],nn+1);
            }
      }
    } 
}
