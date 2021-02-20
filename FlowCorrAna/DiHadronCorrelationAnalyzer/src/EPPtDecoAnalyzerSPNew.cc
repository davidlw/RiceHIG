#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPPtDecoAnalyzerSPNew.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TObjString.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGenPhaseSpace.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

EPPtDecoAnalyzerSPNew::EPPtDecoAnalyzerSPNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
  etaBinWidth = iConfig.getParameter<double>("etaBinWidth");
}

//EPPtDecoAnalyzerSPNew::~EPPtDecoAnalyzerSPNew()
//{}

//
// member functions
//

void EPPtDecoAnalyzerSPNew::beginJob()
{
  NETABINS = (int)(4.8/etaBinWidth)+1;
  NPTBINS = cutPara.pttrgmin.size();

  qVectorTree = theOutputs->make<TTree>("qVectorTree","qVectorTree");
  qVectorTree->Branch("nMult",&nMult,"nMult/i");
  qVectorTree->Branch("hiCentrality",&hiCentrality,"hiCentrality/i");
  qVectorTree->Branch("hft",&hft,"hft/F");
  qVectorTree->Branch("zdc",&zdc,"zdc/F");
  qVectorTree->Branch("npixel",&npixel,"npixel/i");
  qVectorTree->Branch("NPTBINS",&NPTBINS,"NPTBINS/i");
/*
  qVectorTree->Branch("sumcos1_trk",sumcos1_trk,"sumcos1_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumsin1_trk",sumsin1_trk,"sumsin1_trk[NPTBINS][25]/F");
*/
  qVectorTree->Branch("sumcos2_trk",sumcos2_trk,"sumcos2_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumsin2_trk",sumsin2_trk,"sumsin2_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumcos3_trk",sumcos3_trk,"sumcos3_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumsin3_trk",sumsin3_trk,"sumsin3_trk[NPTBINS][25]/F");
/*
  qVectorTree->Branch("sumcos4_trk",sumcos4_trk,"sumcos4_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumsin4_trk",sumsin4_trk,"sumsin4_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumcos5_trk",sumcos5_trk,"sumcos5_trk[NPTBINS][25]/F");
  qVectorTree->Branch("sumsin5_trk",sumsin5_trk,"sumsin5_trk[NPTBINS][25]/F");
*/
  qVectorTree->Branch("npairs_trk",npairs_trk,"npairs_trk[NPTBINS][25]/F");

  qVectorTree->Branch("sumcosn_p_hf",sumcosn_p_hf,"sumcosn_p_hf[3]/F");
  qVectorTree->Branch("sumsinn_p_hf",sumsinn_p_hf,"sumsinn_p_hf[3]/F");
  qVectorTree->Branch("sumcosn_m_hf",sumcosn_m_hf,"sumcosn_m_hf[3]/F");
  qVectorTree->Branch("sumsinn_m_hf",sumsinn_m_hf,"sumsinn_m_hf[3]/F");
  qVectorTree->Branch("npairs_p_hf",&npairs_p_hf,"npairs_p_hf/F");
  qVectorTree->Branch("npairs_m_hf",&npairs_m_hf,"npairs_m_hf/F");

  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------
/*
void EPPtDecoAnalyzerSPNew::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBaseNew::analyze(iEvent,iSetup);

  FillHistsSignal(*eventcorr);
}
*/

void EPPtDecoAnalyzerSPNew::endJob()
{}

void EPPtDecoAnalyzerSPNew::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{
  for(unsigned int i=0;i<20;i++)
    for(unsigned int j=0;j<50;j++)
    {
      sumcos1_trk[i][j]=0.0;
      sumsin1_trk[i][j]=0.0;
      sumcos2_trk[i][j]=0.0;
      sumsin2_trk[i][j]=0.0;
      sumcos3_trk[i][j]=0.0;
      sumsin3_trk[i][j]=0.0;
      sumcos4_trk[i][j]=0.0;
      sumsin4_trk[i][j]=0.0;
      sumcos5_trk[i][j]=0.0;
      sumsin5_trk[i][j]=0.0;
      npairs_trk[i][j]=0.0;
    }

  for(unsigned int i=0;i<10;i++)
  {
    sumcosn_p_hf[i]=0.0;
    sumsinn_p_hf[i]=0.0;
    sumcosn_m_hf[i]=0.0;
    sumsinn_m_hf[i]=0.0;
  }

  npairs_p_hf=0.0;
  npairs_m_hf=0.0;

   for(unsigned int ipt=0;ipt<cutPara.pttrgmin.size();ipt++)
   { 
     unsigned int ntrksize = eventcorr.pVect_trg[ipt].size();

     for(unsigned int ntrk=0;ntrk<ntrksize;ntrk++)
     {
       TLorentzVector pvector_trk = (eventcorr.pVect_trg[ipt])[ntrk];
       float effweight_trk = (eventcorr.effVect_trg[ipt])[ntrk];
       float eta_trk = pvector_trk.Eta()-cutPara.etacms;
       float phi_trk = pvector_trk.Phi();

       for(unsigned int jeta=0;jeta<NETABINS;jeta++)
       {
         if(eta_trk>(-2.4+etaBinWidth*jeta) && eta_trk<(-2.4+etaBinWidth*(jeta+1)))
         {
           sumcos1_trk[ipt][jeta] += cos(1.*phi_trk)/effweight_trk;
           sumsin1_trk[ipt][jeta] += sin(1.*phi_trk)/effweight_trk;
           sumcos2_trk[ipt][jeta] += cos(2.*phi_trk)/effweight_trk;
           sumsin2_trk[ipt][jeta] += sin(2.*phi_trk)/effweight_trk;
           sumcos3_trk[ipt][jeta] += cos(3.*phi_trk)/effweight_trk;
           sumsin3_trk[ipt][jeta] += sin(3.*phi_trk)/effweight_trk;
           sumcos4_trk[ipt][jeta] += cos(4.*phi_trk)/effweight_trk;
           sumsin4_trk[ipt][jeta] += sin(4.*phi_trk)/effweight_trk;
           sumcos5_trk[ipt][jeta] += cos(5.*phi_trk)/effweight_trk;
           sumsin5_trk[ipt][jeta] += sin(5.*phi_trk)/effweight_trk;
           npairs_trk[ipt][jeta] += 1.0/fabs(effweight_trk);
         }
       }
     }
   }

   unsigned int nhfsize = eventcorr.pVect_ass[0].size();
   for(unsigned int nhf=0;nhf<nhfsize;nhf++)
   {
     TLorentzVector pvector_hf = (eventcorr.pVect_ass[0])[nhf];

     float effweight_hf = (eventcorr.effVect_ass[0])[nhf];
     float eta_hf = pvector_hf.Eta()-cutPara.etacms;
     float phi_hf = pvector_hf.Phi();

     for(int nn = 0; nn<5; nn++)
     {
       if(eta_hf>0.0)
       {
         sumcosn_p_hf[nn] += cos((nn+1)*phi_hf)/effweight_hf;
         sumsinn_p_hf[nn] += sin((nn+1)*phi_hf)/effweight_hf;
         if(nn==0) npairs_p_hf += 1.0/effweight_hf;
       }
       else
       {
         sumcosn_m_hf[nn] += cos((nn+1)*phi_hf)/effweight_hf;
         sumsinn_m_hf[nn] += sin((nn+1)*phi_hf)/effweight_hf;
         if(nn==0) npairs_m_hf += 1.0/effweight_hf;
       }
     }
   }

   qVectorTree->Fill();
}
