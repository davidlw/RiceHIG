#include "../interface/EPEtaPtDecoAnalyzerSPMatrix.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile2D.h>
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
#include <TComplex.h>
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
 
  for(int n=0;n<5;n++)
  {
    if(n==0) {
      hSignalCosn[n] = theOutputs->make<TProfile2D>(Form("signalcos%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hBackgroundCosn[n] = theOutputs->make<TProfile2D>(Form("backgroundcos%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hSignalSinn[n] = theOutputs->make<TProfile2D>(Form("signalsin%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hBackgroundSinn[n] = theOutputs->make<TProfile2D>(Form("backgroundsin%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);    
    }
    else {
      hSignalCosn[n] = theOutputs->make<TProfile2D>(Form("signalcos%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hBackgroundCosn[n] = theOutputs->make<TProfile2D>(Form("backgroundcos%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hSignalSinn[n] = theOutputs->make<TProfile2D>(Form("signalsin%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hBackgroundSinn[n] = theOutputs->make<TProfile2D>(Form("backgroundsin%d",n),"",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX); 
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
      unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
      TComplex qsum_trg[5][NETABINS];
      TComplex q2sum_trg[5][NETABINS];      
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];
        double effweight_trg = (eventcorr_trg.effVect_trg[0])[ntrg];
        double eta_trg = pvector_trg.Eta()-cutPara.etacms;
        double phi_trg = pvector_trg.Phi();
        int ieta = getEtaBin(eta_trg,ETAMIN,ETAMAX,ETABINWIDTH);

        for(int nn = 0; nn<5; nn++)
        {
        	TComplex q_tmp(effweight_trg*cos(nn*phi_trg),effweight_trg*sin(nn*phi_trg)); 
                TComplex q2_tmp(effweight_trg*effweight_trg*cos(2*nn*phi_trg),effweight_trg*effweight_trg*sin(2*nn*phi_trg));
  	        qsum_trg[nn][ieta] += q_tmp; 	
                q2sum_trg[nn][ieta] += q2_tmp;  
	}
      }

      unsigned int nasssize = eventcorr_ass.pVect_ass[0].size();      
      TComplex qsum_ass[5][NETABINS];
      TComplex q2sum_ass[5][NETABINS];      
      for(unsigned int nass=0;nass<nasssize;nass++)
      {
        TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[0])[nass];
        double effweight_ass = (eventcorr_ass.effVect_ass[0])[nass];
        double eta_ass = pvector_ass.Eta()-cutPara.etacms;
        double phi_ass = pvector_ass.Phi();
        int ieta = getEtaBin(eta_ass,ETAMIN,ETAMAX,ETABINWIDTH);

        for(int nn = 0; nn<5; nn++)
        {
                TComplex q_tmp(effweight_ass*cos(nn*phi_ass),effweight_ass*sin(nn*phi_ass));
                TComplex q2_tmp(effweight_ass*effweight_ass*cos(2*nn*phi_ass),effweight_ass*effweight_ass*sin(2*nn*phi_ass));
                qsum_ass[nn][ieta] += q_tmp;
                q2sum_ass[nn][ieta] += q2_tmp;
        }
      }
      
      for(int ieta=0; ieta<NETABINS; ieta++)
      {
        double ietacenter = ETAMIN + (ieta + 0.5) * ETABINWIDTH;
	
        for(int jeta=0; jeta<NETABINS; jeta++)
        {
          double jetacenter = ETAMIN + (jeta + 0.5) * ETABINWIDTH;
          for(int nn = 0; nn<5; nn++)
          {
            TComplex scalarprod = qsum_trg[nn][ieta]*TComplex::Conjugate(qsum_ass[nn][jeta]);
            if(eventcorr_trg.run==eventcorr_ass.run && eventcorr_trg.event==eventcorr_ass.event)
	    {	    
              if(ieta==jeta) scalarprod = qsum_trg[nn][ieta]*TComplex::Conjugate(qsum_ass[nn][jeta])-q2sum_trg[0][ieta];		    
              hSignalCosn[nn]->Fill(ietacenter,jetacenter,scalarprod.Re());
              hSignalSinn[nn]->Fill(ietacenter,jetacenter,scalarprod.Im());	    
	    }
	    else
	    {
              hBackgroundCosn[nn]->Fill(ietacenter,jetacenter,scalarprod.Re());
              hBackgroundSinn[nn]->Fill(ietacenter,jetacenter,scalarprod.Im());		    
	    }
	  }
	}
      }
}


int EPEtaPtDecoAnalyzerSPMatrix::getEtaBin(double eta, double etamin, double etamax, double binwidth) {
    if (eta < etamin || eta >= etamax) {
        // out of range
        return -1;
    }
    int ieta = static_cast<int>(std::floor((eta - etamin) / binwidth));
    return ieta;
}
