#include "../interface/EPEtaPtDecoAnalyzerSPMatrix.h"
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

EPEtaPtDecoAnalyzerSPMatrix::EPEtaPtDecoAnalyzerSPMatrix(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

EPEtaPtDecoAnalyzerSPMatrix::~EPEtaPtDecoAnalyzerSPMatrix() 
{}

void EPEtaPtDecoAnalyzerSPMatrix::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;
    
      for(int n=0;n<4;n++)
      {
        hSignalCosn[n][itrg][jass] = theOutputs->make<TH3D>(Form("signalcos%d_trg%d_ass%d",n,itrg,jass),";cos(n#Delta#phi)",108,-5.4,5.4,108,-5.4,5.4,2,-1.0,1.0);
        hBackgroundCosn[n][itrg][jass] = theOutputs->make<TH3D>(Form("backgroundcos%d_trg%d_ass%d",n,itrg,jass),";cos(n#Delta#phi)",108,-5.4,5.4,108,-5.4,5.4,2,-1.0,1.0);
/*
        hSignalSinn[n][itrg][jass] = theOutputs->make<TH3D>(Form("signalsin%d_trg%d_ass%d",n+1,itrg,jass),";sin(n#Delta#phi)",108,-5.4,5.4,108,-5.4,5.4,2,-1.0,1.0);
        hBackgroundSinn[n][itrg][jass] = theOutputs->make<TH3D>(Form("backgroundsin%d_trg%d_ass%d",n+1,itrg,jass),";sin(n#Delta#phi)",108,-5.4,5.4,108,-5.4,5.4,2,-1.0,1.0);

*/
      }
    }
  }

  DiHadronCorrelationMultiBase::beginJob();
}

void EPEtaPtDecoAnalyzerSPMatrix::endJob()
{
  DiHadronCorrelationMultiBase::endJob();
  
  if(!cutPara.IsCorr) return;

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running correlation analysis!" << endl;

  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsBackground(eventcorrArray[i],eventcorrArray[i]);

    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;

    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
//      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) break;
//      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) continue;

      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      hDeltaZvtx->Fill(deltazvtx);

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void EPEtaPtDecoAnalyzerSPMatrix::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
void EPEtaPtDecoAnalyzerSPMatrix::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;

      unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr_ass.pVect_trg[jass].size();

      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[itrg])[ntrg];
        double effweight_trg = (eventcorr_trg.effVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta()-cutPara.etacms;
        double phi_trg = pvector_trg.Phi();

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr_ass.pVect_trg[jass])[nass];
          double effweight_ass = (eventcorr_ass.effVect_trg[jass])[nass];
          double eta_ass = pvector_ass.Eta()-cutPara.etacms;
          double phi_ass = pvector_ass.Phi();

          for(int nn = 0; nn<4; nn++)
          {
            if(eventcorr_trg.run==eventcorr_ass.run && eventcorr_trg.event==eventcorr_ass.event)
            {
              hSignalCosn[nn][itrg][jass]->Fill(eta_trg,eta_ass,cos(nn*(phi_trg-phi_ass)),1./effweight_trg/effweight_ass);
//            hSignalSinn[nn][itrg][jass]->Fill(eta_trg,eta_ass,sin((nn+1)*(phi_trg-phi_ass)),1./effweight_trg/effweight_ass);
            }
            else
            {
              hBackgroundCosn[nn][itrg][jass]->Fill(eta_trg,eta_ass,cos(nn*(phi_trg-phi_ass)),1./effweight_trg/effweight_ass);
//            hBackgroundSinn[nn][itrg][jass]->Fill(eta_trg,eta_ass,sin((nn+1)*(phi_trg-phi_ass)),1./effweight_trg/effweight_ass);
            }
          }
        }
      }
    }
}
