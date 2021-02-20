#include "../interface/EPEtaDecoAnalyzerSPMatrixNew.h"
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

EPEtaDecoAnalyzerSPMatrixNew::EPEtaDecoAnalyzerSPMatrixNew(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBaseNew(iConfig)
{
  etaBinWidth = iConfig.getParameter<double>("etaBinWidth"); 
}

EPEtaDecoAnalyzerSPMatrixNew::~EPEtaDecoAnalyzerSPMatrixNew() 
{}

void EPEtaDecoAnalyzerSPMatrixNew::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  int NETABINS = (int)((cutPara.etatrgmax-cutPara.etatrgmin+0.001)/etaBinWidth);
  for(int itrg=0;itrg<NETABINS;itrg++)
  {
    hSignalCosn[itrg] = theOutputs->make<TH2D>(Form("signalcosn_trg%d",itrg),";cos(n#Delta#phi);n",2,-1.0,1.0,3,1.5,4.5);     
    hSignalSinn[itrg] = theOutputs->make<TH2D>(Form("signalsinn_trg%d",itrg),";sin(n#Delta#phi);n",2,-1.0,1.0,3,1.5,4.5);
    hSignalNPairs[itrg] = theOutputs->make<TH1D>(Form("signalnpairs_trg%d",itrg),";N_{pair}",100,0.,10000);

    for(int jass=itrg;jass<NETABINS;jass++)
    {
      hSignalCosn2[itrg][jass] = theOutputs->make<TH2D>(Form("signalcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",2,-1.0,1.0,3,1.5,4.5);
      hSignalNPairs2[itrg][jass] = theOutputs->make<TH1D>(Form("signalnpairs_trg%d_ass%d",itrg,jass),";N_{pair}",100,0.,60000000);
    }
  }

  DiHadronCorrelationMultiBase::beginJob();
}

void EPEtaDecoAnalyzerSPMatrixNew::endJob()
{}

void EPEtaDecoAnalyzerSPMatrixNew::NormalizeHists()
{}

void EPEtaDecoAnalyzerSPMatrixNew::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
    unsigned int ntrgsize = eventcorr.pVect_trg[0].size();

    double sumcosn[MAXETATRGBINSMATRIX][15]={{0.0}};
    double sumsinn[MAXETATRGBINSMATRIX][15]={{0.0}};
    double npairs[MAXETATRGBINSMATRIX][15]={{0.0}};
    double npairs2[MAXETATRGBINSMATRIX][15]={{0.0}};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector = (eventcorr.pVect_trg[0])[ntrg];
      double effweight = (eventcorr.effVect_trg[0])[ntrg];
      double eta = pvector.Eta()-cutPara.etacms;
      double phi = pvector.Phi();

      int ietabin = (int)((eta+cutPara.etatrgmax)/etaBinWidth);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn[ietabin][nn] = sumcosn[ietabin][nn] + cos((nn+1)*phi)/effweight;
        sumsinn[ietabin][nn] = sumsinn[ietabin][nn] + sin((nn+1)*phi)/effweight;
        npairs[ietabin][nn] += 1.0/effweight;
        npairs2[ietabin][nn] += 1.0/effweight;
      }
   }

   int NETABINS = (int)((cutPara.etatrgmax-cutPara.etatrgmin+0.001)/etaBinWidth); 
   for(int nn = 1; nn<4; nn++)
   {
     for(int i=0;i<NETABINS;i++)
     {
       if(npairs[i][nn]==0.0) continue;

       hSignalCosn[i]->Fill(sumcosn[i][nn]/npairs[i][nn],nn+1,npairs[i][nn]);
       hSignalSinn[i]->Fill(sumsinn[i][nn]/npairs[i][nn],nn+1,npairs[i][nn]);
       if(nn==1) hSignalNPairs[i]->Fill(npairs[i][nn]);

       for(int j=i;j<NETABINS;j++)
       {
         if(npairs[j][nn]==0.0) continue;
         double Qx2 = sumcosn[i][nn]*sumcosn[j][nn]+sumsinn[i][nn]*sumsinn[j][nn];

         if(i==j)
         {
           Qx2 = (Qx2-npairs2[i][nn])/npairs[i][nn]/(npairs[j][nn]-1);
           hSignalCosn2[i][j]->Fill(Qx2,nn+1,npairs[i][nn]*(npairs[j][nn]-1));
         }
         else 
         {
           Qx2 = Qx2/npairs[i][nn]/npairs[j][nn];
           hSignalCosn2[i][j]->Fill(Qx2,nn+1,npairs[i][nn]*npairs[j][nn]);
         }
         if(nn==1) hSignalNPairs2[i][j]->Fill(npairs[i][nn]*npairs[j][nn]);
       }
     }
   }
}
