#include "../interface/DiHadronCorrelationMultiAnalyzerChAsym.h"
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

DiHadronCorrelationMultiAnalyzerChAsym::DiHadronCorrelationMultiAnalyzerChAsym(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig),
  signalTrgEffWeight(0),
  bkgTrgEffWeight(0),
  bkgAssEffWeight(0)
{
  cutPara.IsSymmetrize=1;
  chasymmin = iConfig.getParameter< std::vector<double> >("chasymmin");
  chasymmax = iConfig.getParameter< std::vector<double> >("chasymmax");
  bkgFactor = 100; 
}

DiHadronCorrelationMultiAnalyzerChAsym::~DiHadronCorrelationMultiAnalyzerChAsym()
{}

void DiHadronCorrelationMultiAnalyzerChAsym::beginJob()
{
  double etabinwidth = (cutPara.etatrgmax-cutPara.etaassmin-cutPara.etatrgmin+cutPara.etaassmax)/NEtaBins;
  double phibinwidth = 2*PI/NPhiBins;

  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  hSignal_pt1pt2 = theOutputs->make<TH2D>("signal_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
  hBackground_pt1pt2 = theOutputs->make<TH2D>("background_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
  hCorrelation_pt1pt2 = theOutputs->make<TH2D>("correlation_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);

  for(int ichasym=0;ichasym<(int)(chasymmin.size());ichasym++)
  {
    hSignal[ichasym] = theOutputs->make<TH2D>(Form("signal_chasym%d",ichasym),";#Delta#eta;#Delta#phi",
                                   NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,                                            NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

    hBackground[ichasym] = theOutputs->make<TH2D>(Form("background_chasym%d",ichasym),";#Delta#eta;#Delta#phi",
                                   NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,
                                   NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

    hCorrelation[ichasym] = theOutputs->make<TH2D>(Form("correlation_chasym%d",ichasym),";#Delta#eta;#Delta#phi",
                                   NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,
                                   NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);
  }
  DiHadronCorrelationMultiBase::beginJob();
}

void DiHadronCorrelationMultiAnalyzerChAsym::endJob()
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

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void DiHadronCorrelationMultiAnalyzerChAsym::NormalizeHists()
{
  for(int ichasym=0;ichasym<(int)(chasymmin.size());ichasym++)
  {
      if(hSignal[ichasym]->Integral()==0) continue;
      if(hBackground[ichasym]->Integral()==0) continue;

      double  etabinwidth = hSignal[ichasym]->GetXaxis()->GetBinWidth(1);
      double  phibinwidth = hSignal[ichasym]->GetYaxis()->GetBinWidth(1);
 
      hSignal[ichasym]->Scale(1.0/etabinwidth/phibinwidth);
      hBackground[ichasym]->Scale(1.0/etabinwidth/phibinwidth);

      hCorrelation[ichasym]->Add(hSignal[ichasym]);
      hCorrelation[ichasym]->Divide(hBackground[ichasym]);
      hCorrelation[ichasym]->Scale(hBackground[ichasym]->GetBinContent(hBackground[ichasym]->FindBin(0,0)));
  }

  if(hBackground_pt1pt2)
  {
    hCorrelation_pt1pt2->Add(hSignal_pt1pt2);
    hCorrelation_pt1pt2->Divide(hBackground_pt1pt2);
  }
}

//--------------- Calculate signal distributions ----------------------
void DiHadronCorrelationMultiAnalyzerChAsym::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  for(unsigned int ichasym=0;ichasym<chasymmin.size();ichasym++)
    {
      if(eventcorr.chasym<chasymmin[ichasym] || eventcorr.chasym>chasymmax[ichasym]) continue;

      unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
      unsigned int nasssize = eventcorr.pVect_ass[0].size();
      double nMultCorr_trg = eventcorr.nMultCorrVect_trg[0];

      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];	  
        double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
        double eta_trg = pvector_trg.Eta();
        double phi_trg = pvector_trg.Phi();
        double pt_trg = pvector_trg.Pt();

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];   
          double effweight_ass = (eventcorr.effVect_ass[0])[nass];
          double eta_ass = pvector_ass.Eta();
          double phi_ass = pvector_ass.Phi();
          double pt_ass = pvector_ass.Pt();

          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

          if(deltaEta==0.0 && deltaPhi==0.0 && pt_trg==pt_ass) continue; // two particles are identical

          // total weight
          double effweight = effweight_trg * effweight_ass;

          if(!cutPara.IsSymmetrize)
          {
            hSignal[ichasym]->Fill(deltaEta,deltaPhi,1.0/effweight/nMultCorr_trg);
          }
          else
          {
            hSignal[ichasym]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[ichasym]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[ichasym]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[ichasym]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[ichasym]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[ichasym]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
          }
          hSignal_pt1pt2->Fill(pt_trg,pt_ass,1.0/effweight);
        }
      }
    } 
}

void DiHadronCorrelationMultiAnalyzerChAsym::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int ichasym=0;ichasym<chasymmin.size();ichasym++)
    {
      if(eventcorr_trg.chasym<chasymmin[ichasym] || eventcorr_trg.chasym>chasymmax[ichasym] || eventcorr_ass.chasym<chasymmin[ichasym] || eventcorr_ass.chasym>chasymmax[ichasym]) continue;

      unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
      unsigned int nasssize = eventcorr_ass.pVect_ass[0].size();
      double nMultCorr_trg = eventcorr_trg.nMultCorrVect_trg[0];

      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];	  
        double effweight_trg = (eventcorr_trg.effVect_trg[0])[ntrg];
        double eta_trg = pvector_trg.Eta();
        double phi_trg = pvector_trg.Phi();
        double pt_trg = pvector_trg.Pt();

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[0])[nass];   
          double effweight_ass = (eventcorr_ass.effVect_ass[0])[nass];
          double eta_ass = pvector_ass.Eta();
          double phi_ass = pvector_ass.Phi();
          double pt_ass = pvector_ass.Pt();

          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

          if(deltaEta==0.0 && deltaPhi==0.0 && pt_trg==pt_ass) continue; // two particles are identical

          // total weight
          double effweight = effweight_trg * effweight_ass * nMultCorr_trg;

          // Fill dihadron correlation functions
          if(!cutPara.IsSymmetrize)
          {
            hBackground[ichasym]->Fill(deltaEta,deltaPhi,1.0/effweight);
          }
          else
          {
            hBackground[ichasym]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[ichasym]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[ichasym]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[ichasym]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[ichasym]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[ichasym]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
          }
          hBackground_pt1pt2->Fill(pt_trg,pt_ass,1.0/effweight);
        }
      }
    } 
}
