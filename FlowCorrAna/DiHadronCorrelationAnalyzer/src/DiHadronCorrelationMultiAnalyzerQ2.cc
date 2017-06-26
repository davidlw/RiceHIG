#include "../interface/DiHadronCorrelationMultiAnalyzerQ2.h"
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

DiHadronCorrelationMultiAnalyzerQ2::DiHadronCorrelationMultiAnalyzerQ2(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig),
  signalTrgEffWeight(0),
  bkgTrgEffWeight(0),
  bkgAssEffWeight(0)
{
  cutPara.IsSymmetrize=1;
  q2min = iConfig.getParameter< std::vector<double> >("q2min");
  q2max = iConfig.getParameter< std::vector<double> >("q2max");
  bkgFactor = 100; 
}

DiHadronCorrelationMultiAnalyzerQ2::~DiHadronCorrelationMultiAnalyzerQ2()
{}

void DiHadronCorrelationMultiAnalyzerQ2::beginJob()
{
  double etabinwidth = (cutPara.etatrgmax-cutPara.etaassmin-cutPara.etatrgmin+cutPara.etaassmax)/NEtaBins;
  double phibinwidth = 2*PI/NPhiBins;

  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  hSignal_pt1pt2 = theOutputs->make<TH2D>("signal_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
  hBackground_pt1pt2 = theOutputs->make<TH2D>("background_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);
  hCorrelation_pt1pt2 = theOutputs->make<TH2D>("correlation_pt1pt2",";p_{T,1};p_{T,2}", 50, 0, 5.0, 50, 0, 5.0);

  for(int iq2=0;iq2<(int)(q2min.size());iq2++)
  {
    hSignal[iq2] = theOutputs->make<TH2D>(Form("signal_q2%d",iq2),";#Delta#eta;#Delta#phi",
                                   NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,                                            NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

    hBackground[iq2] = theOutputs->make<TH2D>(Form("background_q2%d",iq2),";#Delta#eta;#Delta#phi",
                                   NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,
                                   NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);

    hCorrelation[iq2] = theOutputs->make<TH2D>(Form("correlation_q2%d",iq2),";#Delta#eta;#Delta#phi",
                                   NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,
                                   NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);
  }
  DiHadronCorrelationMultiBase::beginJob();
}

void DiHadronCorrelationMultiAnalyzerQ2::endJob()
{
  DiHadronCorrelationMultiBase::endJob();

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

void DiHadronCorrelationMultiAnalyzerQ2::NormalizeHists()
{
  for(int iq2=0;iq2<(int)(q2min.size());iq2++)
  {
      if(hSignal[iq2]->Integral()==0) continue;
      if(hBackground[iq2]->Integral()==0) continue;

      double  etabinwidth = hSignal[iq2]->GetXaxis()->GetBinWidth(1);
      double  phibinwidth = hSignal[iq2]->GetYaxis()->GetBinWidth(1);
 
      hSignal[iq2]->Scale(1.0/etabinwidth/phibinwidth);
      hBackground[iq2]->Scale(1.0/etabinwidth/phibinwidth);

      hCorrelation[iq2]->Add(hSignal[iq2]);
      hCorrelation[iq2]->Divide(hBackground[iq2]);
      hCorrelation[iq2]->Scale(hBackground[iq2]->GetBinContent(hBackground[iq2]->FindBin(0,0)));
  }

  if(hBackground_pt1pt2)
  {
    hCorrelation_pt1pt2->Add(hSignal_pt1pt2);
    hCorrelation_pt1pt2->Divide(hBackground_pt1pt2);
  }
}

//--------------- Calculate signal distributions ----------------------
void DiHadronCorrelationMultiAnalyzerQ2::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  for(unsigned int iq2=0;iq2<q2min.size();iq2++)
    {
      if(eventcorr.q2<q2min[iq2] || eventcorr.q2>q2max[iq2]) continue;

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
            hSignal[iq2]->Fill(deltaEta,deltaPhi,1.0/effweight/nMultCorr_trg);
          }
          else
          {
            hSignal[iq2]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[iq2]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[iq2]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[iq2]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[iq2]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
            hSignal[iq2]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg);
          }
          hSignal_pt1pt2->Fill(pt_trg,pt_ass,1.0/effweight);
        }
      }
    } 
}

void DiHadronCorrelationMultiAnalyzerQ2::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int iq2=0;iq2<q2min.size();iq2++)
    {
      if(eventcorr_trg.q2<q2min[iq2] || eventcorr_trg.q2>q2max[iq2] || eventcorr_ass.q2<q2min[iq2] || eventcorr_ass.q2>q2max[iq2]) continue;

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
            hBackground[iq2]->Fill(deltaEta,deltaPhi,1.0/effweight);
          }
          else
          {
            hBackground[iq2]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[iq2]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[iq2]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[iq2]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[iq2]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[iq2]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
          }
          hBackground_pt1pt2->Fill(pt_trg,pt_ass,1.0/effweight);
        }
      }
    } 
}
