#include "../interface/EPEtaDecoAnalyzerSPMatrix.h"
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

EPEtaDecoAnalyzerSPMatrix::EPEtaDecoAnalyzerSPMatrix(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

EPEtaDecoAnalyzerSPMatrix::~EPEtaDecoAnalyzerSPMatrix() 
{}

void EPEtaDecoAnalyzerSPMatrix::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(int itrg=0;itrg<MAXETATRGBINSMATRIX;itrg++)
  {
    for(int jass=itrg;jass<MAXETATRGBINSMATRIX;jass++)
    {
      hSignalCosn[itrg][jass] = theOutputs->make<TH2D>(Form("signalcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
      hBackgroundCosn[itrg][jass]= theOutputs->make<TH2D>(Form("backgroundcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    }
  }

  DiHadronCorrelationMultiBase::beginJob();
}

void EPEtaDecoAnalyzerSPMatrix::endJob()
{
  DiHadronCorrelationMultiBase::endJob();
  
  if(!cutPara.IsCorr) return;

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running correlation analysis!" << endl;

//  for(unsigned int i=0;i<eventcorrArray.size();i++) cout<< "zvtx=" << eventcorrArray[i].zvtx <<" nmult="<<eventcorrArray[i].nmult<<" cent="<<eventcorrArray[i].centbin<<endl;

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

//      if(fabs(deltazvtx)>0.06) continue;

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void EPEtaDecoAnalyzerSPMatrix::NormalizeHists()
{
}

void EPEtaDecoAnalyzerSPMatrix::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
    unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
    unsigned int nasssize = eventcorr_ass.pVect_trg[0].size();
//      double nMultCorr_trg = eventcorr_trg.nMultCorrVect_trg[0];
//      double nMultCorr_ass = eventcorr_ass.nMultCorrVect_ass[0];

    double sumcosn_trg[MAXETATRGBINSMATRIX][5]={{0.0}};
    double sumsinn_trg[MAXETATRGBINSMATRIX][5]={{0.0}};
    double npairs_trg[MAXETATRGBINSMATRIX][5]={{0.0}};
    double sumcosn_ass[MAXETATRGBINSMATRIX][5]={{0.0}};
    double sumsinn_ass[MAXETATRGBINSMATRIX][5]={{0.0}};
    double npairs_ass[MAXETATRGBINSMATRIX][5]={{0.0}};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];
      double effweight_trg = (eventcorr_trg.effVect_trg[0])[ntrg];
      double eta_trg = pvector_trg.Eta()-cutPara.etacms;
      double phi_trg = pvector_trg.Phi();

      int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTHMATRIX);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_trg[ietabin][nn] = sumcosn_trg[ietabin][nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_trg[ietabin][nn] = sumsinn_trg[ietabin][nn] + sin((nn+1)*phi_trg)/effweight_trg;
        npairs_trg[ietabin][nn] += 1.0/effweight_trg;
      }
   }

   for(unsigned int nass=0;nass<nasssize;nass++)
   {
      TLorentzVector pvector_ass = (eventcorr_ass.pVect_trg[0])[nass];
      double effweight_ass = (eventcorr_ass.effVect_trg[0])[nass];
      double eta_ass = pvector_ass.Eta()-cutPara.etacms;
      double phi_ass = pvector_ass.Phi();

      int ietabin = (int)((eta_ass+2.4)/ETATRGBINWIDTHMATRIX);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_ass[ietabin][nn] = sumcosn_ass[ietabin][nn] + cos((nn+1)*phi_ass)/effweight_ass;
        sumsinn_ass[ietabin][nn] = sumsinn_ass[ietabin][nn] + sin((nn+1)*phi_ass)/effweight_ass;
        npairs_ass[ietabin][nn] += 1.0/effweight_ass;
      }
   }

   for(int i=0;i<MAXETATRGBINSMATRIX;i++)
     for(int j=i;j<MAXETATRGBINSMATRIX;j++)
     {
       for(int nn = 1; nn<4; nn++)
       {
         if(npairs_trg[i][nn]==0.0 || npairs_ass[j][nn]==0.0) continue;
         double Qx2 = sumcosn_trg[i][nn]*sumcosn_ass[j][nn]+sumsinn_trg[i][nn]*sumsinn_ass[j][nn];

         if(eventcorr_trg.run==eventcorr_ass.run && eventcorr_trg.event==eventcorr_ass.event) 
         {
           if(i==j)
           {
             Qx2 = (Qx2-npairs_trg[i][nn])/npairs_trg[i][nn]/(npairs_ass[j][nn]-1);
           }
           else 
           {
             Qx2 = Qx2/npairs_trg[i][nn]/npairs_ass[j][nn];
           }
           hSignalCosn[i][j]->Fill(Qx2,nn+1);
         }
         else
         {
           Qx2 = Qx2/npairs_trg[i][nn]/npairs_ass[j][nn];
           hBackgroundCosn[i][j]->Fill(Qx2,nn+1);
         }
       }
     }
}
