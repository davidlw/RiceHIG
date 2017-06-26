#include "../interface/EPEtaDecoAnalyzerSP.h"
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

EPEtaDecoAnalyzerSP::EPEtaDecoAnalyzerSP(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

EPEtaDecoAnalyzerSP::~EPEtaDecoAnalyzerSP() 
{}

void EPEtaDecoAnalyzerSP::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(int itrg=0;itrg<MAXETATRGBINS;itrg++)
  {
//    hSignalCosn[itrg] = theOutputs->make<TH2D>(Form("signalcosn_trg%d",itrg),";cos(n#Delta#phi);n",30000,-0.3,0.3,3,1.5,4.5);
//    hBackgroundCosn[itrg]= theOutputs->make<TH2D>(Form("backgroundcosn_trg%d",itrg),";cos(n#Delta#phi);n",30000,-0.3,0.3,3,1.5,4.5);

    hSignalCosn[itrg] = theOutputs->make<TH2D>(Form("signalcosn_trg%d",itrg),";cos(n#Delta#phi);n",5000,-0.5,0.5,3,1.5,4.5);
    hBackgroundCosn[itrg]= theOutputs->make<TH2D>(Form("backgroundcosn_trg%d",itrg),";cos(n#Delta#phi);n",5000,-0.5,0.5,3,1.5,4.5);
    hSignalNPairs[itrg] = theOutputs->make<TH1D>(Form("signalnpairs_trg%d",itrg),";N_{pair}",12000,0.,120000);
    hBackgroundNPairs[itrg] = theOutputs->make<TH1D>(Form("backgroundnpairs_trg%d",itrg),";N_{pair}",12000,0.,120000);

//    hSignalSinn[itrg] = theOutputs->make<TH2D>(Form("signalsinn_trg%d",itrg),";sin(n#Delta#phi);n",5000,-0.5,0.5,3,1.5,4.5);
//    hBackgroundSinn[itrg]= theOutputs->make<TH2D>(Form("backgroundsinn_trg%d",itrg),";sin(n#Delta#phi);n",5000,-0.5,0.5,3,1.5,4.5);
/*
    hSignalCosnSame[itrg] = theOutputs->make<TH2D>(Form("signalcosnsame_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hBackgroundCosnSame[itrg]= theOutputs->make<TH2D>(Form("backgroundcosnsame_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hSignalCosnDiff[itrg] = theOutputs->make<TH2D>(Form("signalcosndiff_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hBackgroundCosnDiff[itrg]= theOutputs->make<TH2D>(Form("backgroundcosndiff_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
*/
  }
/*
  for(int i=1;i<4;i++)
  {
    hSignalSinnPvsN[i] = theOutputs->make<TH2D>(Form("signalsin%dpvsn",i+1),Form(";sin(%d#Delta#phi)_{P};sin(%d#Delta#phi)_{N}",i+1,i+1),500,-0.3,0.3,500,-0.3,0.3);
    hBackgroundSinnPvsN[i] = theOutputs->make<TH2D>(Form("backgroundsin%dpvsn",i+1),Form(";sin(%d#Delta#phi)_{P};sin(%d#Delta#phi)_{N}",i+1,i+1),500,-0.3,0.3,500,-0.3,0.3);
  }
*/
  DiHadronCorrelationMultiBase::beginJob();
}

void EPEtaDecoAnalyzerSP::endJob()
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
    FillHistsSignal(eventcorrArray[i]);

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

void EPEtaDecoAnalyzerSP::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
void EPEtaDecoAnalyzerSP::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
    unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
    unsigned int nasssize = eventcorr.pVect_ass[0].size();
//    double nMultCorr_trg = eventcorr.nMultCorrVect_trg[0];
//    double nMultCorr_ass = eventcorr.nMultCorrVect_ass[0];

    double sumcosn_trg[MAXETATRGBINS][5]={{0.0}};
    double sumsinn_trg[MAXETATRGBINS][5]={{0.0}};
    double npairs_trg[MAXETATRGBINS][5]={{0.0}};
    double sumcosn_ass[5]={0.0};
    double sumsinn_ass[5]={0.0};
    double npairs_ass[5]={0.0};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];	  
      double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
      double eta_trg = pvector_trg.Eta()-cutPara.etacms;
      double phi_trg = pvector_trg.Phi();

      int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTH);
      if(cutPara.etaassmin<0 && cutPara.etaassmax<0) ietabin = (int)((2.4-eta_trg)/ETATRGBINWIDTH);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_trg[ietabin][nn] = sumcosn_trg[ietabin][nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_trg[ietabin][nn] = sumsinn_trg[ietabin][nn] + sin((nn+1)*phi_trg)/effweight_trg;
        npairs_trg[ietabin][nn] += 1.0/effweight_trg;
      }
   }

   for(unsigned int nass=0;nass<nasssize;nass++)
   {
     TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];   
     double effweight_ass = (eventcorr.effVect_ass[0])[nass];
     double phi_ass = pvector_ass.Phi();

     for(int nn = 1; nn<4; nn++)
     {
       sumcosn_ass[nn] = sumcosn_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
       sumsinn_ass[nn] = sumsinn_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
       npairs_ass[nn] += 1.0/effweight_ass;
     }
   }
    
   for(int i=0;i<MAXETATRGBINS;i++)
     for(int nn = 1; nn<4; nn++) 
      {
        if(npairs_trg[i][nn]==0.0 || npairs_ass[nn]==0.0) continue;
        double Qx = sumcosn_trg[i][nn]*sumcosn_ass[nn]+sumsinn_trg[i][nn]*sumsinn_ass[nn];
        double Qy = -sumcosn_trg[i][nn]*sumsinn_ass[nn]+sumsinn_trg[i][nn]*sumcosn_ass[nn];

        Qx = Qx/npairs_trg[i][nn]/npairs_ass[nn];
        Qy = Qy/npairs_trg[i][nn]/npairs_ass[nn];

        hSignalCosn[i]->Fill(Qx,nn+1);
        if(nn==1) hSignalNPairs[i]->Fill(npairs_trg[i][nn]*npairs_ass[nn]);
//        hSignalSinn[i]->Fill(Qy,nn+1);
/*
	double Qx2same = sumcosn_trg[i][nn]*sumcosn_trg[i][nn]+sumsinn_trg[i][nn]*sumsinn_trg[i][nn];
        double Qx2diff = sumcosn_trg[i][nn]*sumcosn_trg[MAXETATRGBINS-1-i][nn]+sumsinn_trg[i][nn]*sumsinn_trg[MAXETATRGBINS-1-i][nn];
        Qx2same = (Qx2same-npairs_trg[i][nn])/npairs_trg[i][nn]/(npairs_trg[i][nn]-1);
        Qx2diff = Qx2diff/npairs_trg[i][nn]/npairs_trg[MAXETATRGBINS-1-i][nn];

        hSignalCosnSame[i]->Fill(Qx2same,nn+1);
        hSignalCosnDiff[i]->Fill(Qx2diff,nn+1);
*/
      }
}

void EPEtaDecoAnalyzerSP::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
    unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
    unsigned int nasssize = eventcorr_ass.pVect_ass[0].size();
//      double nMultCorr_trg = eventcorr_trg.nMultCorrVect_trg[0];
//      double nMultCorr_ass = eventcorr_ass.nMultCorrVect_ass[0];

    double sumcosn_trg[MAXETATRGBINS][5]={{0.0}};
    double sumsinn_trg[MAXETATRGBINS][5]={{0.0}};
    double npairs_trg[MAXETATRGBINS][5]={{0.0}};
    double sumcosn_ass[5]={0.0};
    double sumsinn_ass[5]={0.0};
    double npairs_ass[5]={0.0};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];
      double effweight_trg = (eventcorr_trg.effVect_trg[0])[ntrg];
      double eta_trg = pvector_trg.Eta()-cutPara.etacms;
      double phi_trg = pvector_trg.Phi();

      int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTH);
      if(cutPara.etaassmin<0 && cutPara.etaassmax<0) ietabin = (int)((2.4-eta_trg)/ETATRGBINWIDTH);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_trg[ietabin][nn] = sumcosn_trg[ietabin][nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_trg[ietabin][nn] = sumsinn_trg[ietabin][nn] + sin((nn+1)*phi_trg)/effweight_trg;
        npairs_trg[ietabin][nn] += 1.0/effweight_trg;
      }
   }

   for(unsigned int nass=0;nass<nasssize;nass++)
   {
     TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[0])[nass];
     double effweight_ass = (eventcorr_ass.effVect_ass[0])[nass];
     double phi_ass = pvector_ass.Phi();

     for(int nn = 1; nn<4; nn++)
     {
       sumcosn_ass[nn] = sumcosn_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
       sumsinn_ass[nn] = sumsinn_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
       npairs_ass[nn] += 1.0/effweight_ass;
     }
   }

   for(int i=0;i<MAXETATRGBINS;i++)
     for(int nn = 1; nn<4; nn++)
      {
        if(npairs_trg[i][nn]==0.0 || npairs_ass[nn]==0.0) continue;
        double Qx = sumcosn_trg[i][nn]*sumcosn_ass[nn]+sumsinn_trg[i][nn]*sumsinn_ass[nn];
        double Qy = -sumcosn_trg[i][nn]*sumsinn_ass[nn]+sumsinn_trg[i][nn]*sumcosn_ass[nn];

        Qx = Qx/npairs_trg[i][nn]/npairs_ass[nn];
        Qy = Qy/npairs_trg[i][nn]/npairs_ass[nn];

        hBackgroundCosn[i]->Fill(Qx,nn+1);
        if(nn==1) hBackgroundNPairs[i]->Fill(npairs_trg[i][nn]*npairs_ass[nn]);
//        hBackgroundSinn[i]->Fill(Qy,nn+1);
/*
        double Qx2same = sumcosn_trg[i][nn]*sumcosn_trg[i][nn]+sumsinn_trg[i][nn]*sumsinn_trg[i][nn];
        double Qx2diff = sumcosn_trg[i][nn]*sumcosn_trg[MAXETATRGBINS-1-i][nn]+sumsinn_trg[i][nn]*sumsinn_trg[MAXETATRGBINS-1-i][nn];
        Qx2same = (Qx2same-npairs_trg[i][nn])/npairs_trg[i][nn]/(npairs_trg[i][nn]-1);
        Qx2diff = Qx2diff/npairs_trg[i][nn]/npairs_trg[MAXETATRGBINS-1-i][nn];

        hBackgroundCosnSame[i]->Fill(Qx2same,nn+1);
        hBackgroundCosnDiff[i]->Fill(Qx2diff,nn+1);
*/
      }
}
