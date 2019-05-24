#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ScalarProdVnAnalyzerNew.h"
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

ScalarProdVnAnalyzerNew::ScalarProdVnAnalyzerNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
  etaBinWidth = iConfig.getParameter<double>("etaBinWidth");
}

//ScalarProdVnAnalyzerNew::~ScalarProdVnAnalyzerNew()
//{}

//
// member functions
//

void ScalarProdVnAnalyzerNew::beginJob()
{
  int NETABINS = (int)(4.8/etaBinWidth);
  for(int itrg=0;itrg<NETABINS;itrg++)
  { 
    hPairCosn_hfp[itrg] = theOutputs->make<TH2D>(Form("paircosn_hfp_trg%d",itrg),";cos(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
    hPairSinn_hfp[itrg] = theOutputs->make<TH2D>(Form("pairsinn_hfp_trg%d",itrg),";sin(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
    hPairCosn_hfm[itrg] = theOutputs->make<TH2D>(Form("paircosn_hfm_trg%d",itrg),";cos(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
    hPairSinn_hfm[itrg] = theOutputs->make<TH2D>(Form("pairsinn_hfm_trg%d",itrg),";sin(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
    hCosnTrg[itrg] = theOutputs->make<TH2D>(Form("cosn_trg%d",itrg),";cos(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
    hSinnTrg[itrg] = theOutputs->make<TH2D>(Form("sinn_trg%d",itrg),";sin(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  }
  
  hPairCosnAss = theOutputs->make<TH2D>("paircosn_ass",";cos(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hPairSinnAss = theOutputs->make<TH2D>("pairsinn_ass",";sin(n#Delta#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hCosnAss_hfp = theOutputs->make<TH2D>("cosn_hfp_ass",";cos(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hSinnAss_hfp = theOutputs->make<TH2D>("sinn_hfp_ass",";sin(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hCosnAss_hfm = theOutputs->make<TH2D>("cosn_hfm_ass",";cos(n#phi);n",10,-1.0,1.0,5,0.5,5.5);
  hSinnAss_hfm = theOutputs->make<TH2D>("sinn_hfm_ass",";sin(n#phi);n",10,-1.0,1.0,5,0.5,5.5);

  DiHadronCorrelationMultiBaseNew::beginJob();
}

// ------------ method called to for each event  -----------
/*
void ScalarProdVnAnalyzerNew::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBaseNew::analyze(iEvent,iSetup);

  FillHistsSignal(*eventcorr);
}
*/

void ScalarProdVnAnalyzerNew::endJob()
{}

void ScalarProdVnAnalyzerNew::FillHistsSignal(DiHadronCorrelationEvent& eventcorr)
{
   double sumcosn_trg[100][5]={{0.0}};
   double sumsinn_trg[100][5]={{0.0}};
   double npairs_trg[100][5]={{0.0}};
   double sumcosn_p_ass[5]={0.0};
   double sumsinn_p_ass[5]={0.0};
   double npairs_p_ass[5]={0.0};
   double sumcosn_m_ass[5]={0.0};
   double sumsinn_m_ass[5]={0.0};
   double npairs_m_ass[5]={0.0};

   int NETABINS = (int)(4.8/etaBinWidth);

   unsigned int ntrgsize = eventcorr.pVect_trg[0].size();

   for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
   {
     TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];
     double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
     double eta_trg = pvector_trg.Eta()-cutPara.etacms;
     double phi_trg = pvector_trg.Phi();

     for(int itrg=0;itrg<NETABINS;itrg++)
     {
       if(eta_trg>(-2.4+etaBinWidth*itrg) && eta_trg<(-2.4+etaBinWidth*(itrg+1)))
       {
         for(int nn = 0; nn<5; nn++)
         {
           sumcosn_trg[itrg][nn] = sumcosn_trg[itrg][nn] + cos((nn+1)*phi_trg)/effweight_trg;
           sumsinn_trg[itrg][nn] = sumsinn_trg[itrg][nn] + sin((nn+1)*phi_trg)/effweight_trg;
           npairs_trg[itrg][nn] += 1.0/fabs(effweight_trg);
         }
       }
     }
   }

   for(int itrg=0;itrg<NETABINS;itrg++)
   {
     for(int nn = 0; nn<5; nn++)
     {
       hCosnTrg[itrg]->Fill(sumcosn_trg[itrg][nn]/npairs_trg[itrg][nn],nn+1,npairs_trg[itrg][nn]);
       hSinnTrg[itrg]->Fill(sumsinn_trg[itrg][nn]/npairs_trg[itrg][nn],nn+1,npairs_trg[itrg][nn]);
     }
   }

   unsigned int nasssize = eventcorr.pVect_ass[0].size();
   for(unsigned int nass=0;nass<nasssize;nass++)
   {
     TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];

     double effweight_ass = (eventcorr.effVect_ass[0])[nass];
     double eta_ass = pvector_ass.Eta()-cutPara.etacms;
     double phi_ass = pvector_ass.Phi();

     for(int nn = 0; nn<5; nn++)
     {
       if(eta_ass>0.0)
       {
         sumcosn_p_ass[nn] = sumcosn_p_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
         sumsinn_p_ass[nn] = sumsinn_p_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
         npairs_p_ass[nn] += 1.0/effweight_ass;
       }
       else if(nn==0) 
       {
         sumcosn_m_ass[nn] = sumcosn_m_ass[nn] - cos((nn+1)*phi_ass)/effweight_ass;
         sumsinn_m_ass[nn] = sumsinn_m_ass[nn] - sin((nn+1)*phi_ass)/effweight_ass;
         npairs_m_ass[nn] += 1.0/effweight_ass;
       }
       else
       {
         sumcosn_m_ass[nn] = sumcosn_m_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
         sumsinn_m_ass[nn] = sumsinn_m_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
         npairs_m_ass[nn] += 1.0/effweight_ass;
       }
     }
   }

   for(int nn = 0; nn<5; nn++)
   {
     hCosnAss_hfp->Fill(sumcosn_p_ass[nn]/npairs_p_ass[nn],nn+1,npairs_p_ass[nn]);
     hSinnAss_hfp->Fill(sumsinn_p_ass[nn]/npairs_p_ass[nn],nn+1,npairs_p_ass[nn]);
     hCosnAss_hfm->Fill(sumcosn_m_ass[nn]/npairs_m_ass[nn],nn+1,npairs_m_ass[nn]);
     hSinnAss_hfm->Fill(sumsinn_m_ass[nn]/npairs_m_ass[nn],nn+1,npairs_m_ass[nn]);
   }

   for(int itrg=0;itrg<NETABINS;itrg++)
   {
     for(int nn = 0; nn<5; nn++)
     {
       double Qx2_p = sumcosn_trg[itrg][nn]*sumcosn_p_ass[nn]+sumsinn_trg[itrg][nn]*sumsinn_p_ass[nn];
       double Qy2_p = -sumcosn_trg[itrg][nn]*sumsinn_p_ass[nn]+sumsinn_trg[itrg][nn]*sumcosn_p_ass[nn];
       hPairCosn_hfp[itrg]->Fill(Qx2_p/npairs_trg[itrg][nn]/npairs_p_ass[nn],nn+1,npairs_trg[itrg][nn]*npairs_p_ass[nn]);
       hPairSinn_hfp[itrg]->Fill(Qy2_p/npairs_trg[itrg][nn]/npairs_p_ass[nn],nn+1,npairs_trg[itrg][nn]*npairs_p_ass[nn]);

       double Qx2_m = sumcosn_trg[itrg][nn]*sumcosn_m_ass[nn]+sumsinn_trg[itrg][nn]*sumsinn_m_ass[nn];
       double Qy2_m = -sumcosn_trg[itrg][nn]*sumsinn_m_ass[nn]+sumsinn_trg[itrg][nn]*sumcosn_m_ass[nn];
       hPairCosn_hfm[itrg]->Fill(Qx2_m/npairs_trg[itrg][nn]/npairs_m_ass[nn],nn+1,npairs_trg[itrg][nn]*npairs_m_ass[nn]);
       hPairSinn_hfm[itrg]->Fill(Qy2_m/npairs_trg[itrg][nn]/npairs_m_ass[nn],nn+1,npairs_trg[itrg][nn]*npairs_m_ass[nn]);
     }
   }

   for(int nn = 0; nn<5; nn++)
   {
     double Qx2 = sumcosn_m_ass[nn]*sumcosn_p_ass[nn]+sumsinn_m_ass[nn]*sumsinn_p_ass[nn];
     double Qy2 = -sumcosn_m_ass[nn]*sumsinn_p_ass[nn]+sumsinn_m_ass[nn]*sumcosn_p_ass[nn];
     hPairCosnAss->Fill(Qx2/npairs_m_ass[nn]/npairs_p_ass[nn],nn+1,npairs_m_ass[nn]*npairs_p_ass[nn]);
     hPairSinnAss->Fill(Qy2/npairs_m_ass[nn]/npairs_p_ass[nn],nn+1,npairs_m_ass[nn]*npairs_p_ass[nn]);
   }
}
