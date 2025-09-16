#include "../interface/EPEtaPtDecoAnalyzerSPMatrixNew.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile.h>
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

EPEtaPtDecoAnalyzerSPMatrixNew::EPEtaPtDecoAnalyzerSPMatrixNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{}

void EPEtaPtDecoAnalyzerSPMatrixNew::beginJob()
{
  for(int n=0;n<5;n++)
  {
      hSignalCosn[n] = theOutputs->make<TProfile2D>(Form("signalcos%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
      hSignalSinn[n] = theOutputs->make<TProfile2D>(Form("signalsin%d",n),";#eta_{trg};#eta_{ass}",NETABINS,ETAMIN,ETAMAX,NETABINS,ETAMIN,ETAMAX);
  }

  for(int n=0;n<5;n++)
  {
      hSingleCosn[n] = theOutputs->make<TProfile>(Form("singlecos%d",n),";#eta",NETABINS,ETAMIN,ETAMAX);
      hSingleSinn[n] = theOutputs->make<TProfile>(Form("singlesin%d",n),";#eta",NETABINS,ETAMIN,ETAMAX);
      hSingleCos2n[n] = theOutputs->make<TProfile>(Form("singlecos2%d",n),";#eta",NETABINS,ETAMIN,ETAMAX);
      hSingleSin2n[n] = theOutputs->make<TProfile>(Form("singlesin2%d",n),";#eta",NETABINS,ETAMIN,ETAMAX);
  }
  
  DiHadronCorrelationMultiBaseNew::beginJob();
}

void EPEtaPtDecoAnalyzerSPMatrixNew::endJob()
{}

void EPEtaPtDecoAnalyzerSPMatrixNew::NormalizeHists()
{}

//--------------- Calculate signal distributions ----------------------
void EPEtaPtDecoAnalyzerSPMatrixNew::FillHistsSignal(DiHadronCorrelationEvent& eventcorr_trg)
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

      for(int ieta=0; ieta<NETABINS; ieta++)
      {
        double ietacenter = ETAMIN + (ieta + 0.5) * ETABINWIDTH;
	
        for(int jeta=0; jeta<NETABINS; jeta++)
        {
          double jetacenter = ETAMIN + (jeta + 0.5) * ETABINWIDTH;
          for(int nn = 0; nn<5; nn++)
          {
              TComplex scalarprod = qsum_trg[nn][ieta]*TComplex::Conjugate(qsum_trg[nn][jeta]);
              if(ieta==jeta) scalarprod = qsum_trg[nn][ieta]*TComplex::Conjugate(qsum_trg[nn][jeta])-q2sum_trg[0][ieta];		    
              hSignalCosn[nn]->Fill(ietacenter,jetacenter,scalarprod.Re());
              hSignalSinn[nn]->Fill(ietacenter,jetacenter,scalarprod.Im());	    
	  }
  	}
      }

      for(int ieta=0; ieta<NETABINS; ieta++)
      {
        double ietacenter = ETAMIN + (ieta + 0.5) * ETABINWIDTH;
        for(int nn = 0; nn<5; nn++)
        {
            hSingleCosn[nn]->Fill(ietacenter,qsum_trg[nn][ieta].Re());
            hSingleSinn[nn]->Fill(ietacenter,qsum_trg[nn][ieta].Im());
            hSingleCos2n[nn]->Fill(ietacenter,q2sum_trg[nn][ieta].Re());
            hSingleSin2n[nn]->Fill(ietacenter,q2sum_trg[nn][ieta].Im());	    
        }
      }
}

int EPEtaPtDecoAnalyzerSPMatrixNew::getEtaBin(double eta, double etamin, double etamax, double binwidth) {
    if (eta < etamin || eta >= etamax) {
        // out of range
        return -1;
    }
    int ieta = static_cast<int>(std::floor((eta - etamin) / binwidth));
    return ieta;
}
