#include "../interface/EPPtDecoAnalyzerSPMatrixNew.h"
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

EPPtDecoAnalyzerSPMatrixNew::EPPtDecoAnalyzerSPMatrixNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
  for (size_t i = 0; i < cutPara.pttrgmin.size(); i++) {
      ptBins.push_back(cutPara.pttrgmin[i]);
  }
  // add the last upper edge
  ptBins.push_back(cutPara.pttrgmax.back());
  nPtBins = ptBins.size() - 1;   // number of bins  
}

void EPPtDecoAnalyzerSPMatrixNew::beginJob()
{

  for(int n=0;n<5;n++)
  {
      hSignalPtCosn[n] = theOutputs->make<TProfile2D>(Form("signalptcos%d",n),";p_{T}^{trg};p_{T}^{ass}",nPtBins, ptBins.data(),nPtBins, ptBins.data());
      hSignalPtSinn[n] = theOutputs->make<TProfile2D>(Form("signalptsin%d",n),";p_{T}^{trg};p_{T}^{ass}",nPtBins, ptBins.data(),nPtBins, ptBins.data());
  }

  for(int n=0;n<5;n++)
  {
      hSinglePtCosn[n] = theOutputs->make<TProfile2D>(Form("singleptcos%d",n),";p_{T};#eta", nPtBins, ptBins.data(),MAXETATRGBINSPT,-2.4,2.4);
      hSinglePtSinn[n] = theOutputs->make<TProfile2D>(Form("singleptsin%d",n),";p_{T};#eta", nPtBins, ptBins.data(),MAXETATRGBINSPT,-2.4,2.4);
  }
  
  DiHadronCorrelationMultiBaseNew::beginJob();
}

void EPPtDecoAnalyzerSPMatrixNew::endJob()
{}

void EPPtDecoAnalyzerSPMatrixNew::NormalizeHists() 
{}

//--------------- Calculate signal distributions ----------------------
void EPPtDecoAnalyzerSPMatrixNew::FillHistsSignal(DiHadronCorrelationEvent& eventcorr_trg)
{
  TComplex qsum_trg[5][nPtBins][MAXETATRGBINSPT];
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
      unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[itrg])[ntrg];
        double effweight_trg = (eventcorr_trg.effVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta()-cutPara.etacms;
        double phi_trg = pvector_trg.Phi();

        for(int nn = 0; nn<5; nn++)
        {
                int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTHPT);
                TComplex q_tmp(effweight_trg*cos(nn*phi_trg),effweight_trg*sin(nn*phi_trg));
                qsum_trg[nn][itrg][ietabin] += q_tmp;
        }
      }  
  }

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    double iptcenter = getPtBinCenter(itrg, ptBins);	  
    for(unsigned int jass=0;jass<cutPara.pttrgmin.size();jass++)
    {
      double jptcenter = getPtBinCenter(jass, ptBins);	          
      for(int nn = 0; nn<5; nn++)
      {
          TComplex scalarprod_sum;
          for(int ieta=0;ieta<MAXETATRGBINSPT;ieta++)
            for(int jeta=0;jeta<MAXETATRGBINSPT;jeta++)
            {
              if(fabs(jeta-ieta)<(int)(2.0/ETATRGBINWIDTHPT)) continue;
              scalarprod_sum += qsum_trg[nn][itrg][ieta]*TComplex::Conjugate(qsum_trg[nn][jass][jeta]);
            }
          hSignalPtCosn[nn]->Fill(iptcenter,jptcenter,scalarprod_sum.Re());
          hSignalPtSinn[nn]->Fill(iptcenter,jptcenter,scalarprod_sum.Im());
      }
    }
  }

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    double iptcenter = getPtBinCenter(itrg, ptBins);
    for(int nn = 0; nn<5; nn++)
    {
      for(int ieta=0;ieta<MAXETATRGBINSPT;ieta++)
      {
        double ietacenter = -2.4 + (ieta + 0.5) * ETATRGBINWIDTHPT;

        hSinglePtCosn[nn]->Fill(iptcenter,ietacenter,qsum_trg[nn][itrg][ieta].Re());
        hSinglePtSinn[nn]->Fill(iptcenter,ietacenter,qsum_trg[nn][itrg][ieta].Im());
      }
    }
  }
}

double EPPtDecoAnalyzerSPMatrixNew::getPtBinCenter(int ibin, const std::vector<double>& ptBins) {
    if (ibin < 0 || ibin >= (int)ptBins.size() - 1) {
        throw std::out_of_range("getPtBinCenter: bin index out of range");
    }
    return 0.5 * (ptBins[ibin] + ptBins[ibin+1]);
}
