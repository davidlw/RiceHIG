#include "../interface/EPPtDecoAnalyzerSPMatrix.h"
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

EPPtDecoAnalyzerSPMatrix::EPPtDecoAnalyzerSPMatrix(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

EPPtDecoAnalyzerSPMatrix::~EPPtDecoAnalyzerSPMatrix() 
{}

void EPPtDecoAnalyzerSPMatrix::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;
    
      for(int n=0;n<4;n++)
      {
        hSignalCosn[n][itrg][jass] = theOutputs->make<TH1D>(Form("signalcos%d_trg%d_ass%d",n+1,itrg,jass),";cos(n#Delta#phi)",2,-1.0,1.0);
        hBackgroundCosn[n][itrg][jass] = theOutputs->make<TH1D>(Form("backgroundcos%d_trg%d_ass%d",n+1,itrg,jass),";cos(n#Delta#phi)",2,-1.0,1.0);
        hSignalCosnNew[n][itrg][jass] = theOutputs->make<TH1D>(Form("signalcosnew%d_trg%d_ass%d",n+1,itrg,jass),";cos(n#Delta#phi)",2,-1.0,1.0);
        hBackgroundCosnNew[n][itrg][jass] = theOutputs->make<TH1D>(Form("backgroundcosnew%d_trg%d_ass%d",n+1,itrg,jass),";cos(n#Delta#phi)",2,-1.0,1.0);
/*
        hSignalSinn[n][itrg][jass] = theOutputs->make<TH1D>(Form("signalsin%d_trg%d_ass%d",n+1,itrg,jass),";sin(n#Delta#phi)",2,-1.0,1.0);
        hBackgroundSinn[n][itrg][jass] = theOutputs->make<TH1D>(Form("backgroundsin%d_trg%d_ass%d",n+1,itrg,jass),";sin(n#Delta#phi)",2,-1.0,1.0);
        hSignalSinnNew[n][itrg][jass] = theOutputs->make<TH1D>(Form("signalsinnew%d_trg%d_ass%d",n+1,itrg,jass),";sin(n#Delta#phi)",2,-1.0,1.0);
        hBackgroundSinnNew[n][itrg][jass] = theOutputs->make<TH1D>(Form("backgroundsinnew%d_trg%d_ass%d",n+1,itrg,jass),";sin(n#Delta#phi)",2,-1.0,1.0);

*/        hSignalNpairs[itrg][jass] = theOutputs->make<TH1D>(Form("signalnpairs_trg%d_ass%d",itrg,jass),";Npairs",10,0,100000);
        hBackgroundNpairs[itrg][jass] = theOutputs->make<TH1D>(Form("backgroundnpairs_trg%d_ass%d",itrg,jass),";Npairs",10,0,100000);
      }
    }
  }

  DiHadronCorrelationMultiBase::beginJob();
}

void EPPtDecoAnalyzerSPMatrix::endJob()
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

void EPPtDecoAnalyzerSPMatrix::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
void EPPtDecoAnalyzerSPMatrix::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      if(!cutPara.IsFullMatrix && itrg<jass) continue;

      unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr_ass.pVect_trg[jass].size();

      double sumcosn_trg[MAXETATRGBINSPT][5]={{0.0}};
      double sumsinn_trg[MAXETATRGBINSPT][5]={{0.0}};
      double npairs_trg[MAXETATRGBINSPT][5]={{0.0}};
      double sumcosn_ass[MAXETATRGBINSPT][5]={{0.0}};
      double sumsinn_ass[MAXETATRGBINSPT][5]={{0.0}};
      double npairs_ass[MAXETATRGBINSPT][5]={{0.0}};

      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[itrg])[ntrg];
	double effweight_trg = (eventcorr_trg.effVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta()-cutPara.etacms;
        double phi_trg = pvector_trg.Phi();

        int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTHPT);

        for(int nn = 0; nn<4; nn++)
        {
          sumcosn_trg[ietabin][nn] = sumcosn_trg[ietabin][nn] + cos((nn+1)*phi_trg)/effweight_trg;
          sumsinn_trg[ietabin][nn] = sumsinn_trg[ietabin][nn] + sin((nn+1)*phi_trg)/effweight_trg;
          npairs_trg[ietabin][nn] += 1.0/effweight_trg;
        }
      }

      for(unsigned int nass=0;nass<nasssize;nass++)
      {
        TLorentzVector pvector_ass = (eventcorr_ass.pVect_trg[jass])[nass];
        double effweight_ass = (eventcorr_ass.effVect_trg[jass])[nass];
        double eta_ass = pvector_ass.Eta()-cutPara.etacms;
        double phi_ass = pvector_ass.Phi();

        int ietabin = (int)((eta_ass+2.4)/ETATRGBINWIDTHPT);

        for(int nn = 0; nn<4; nn++)
        {
          sumcosn_ass[ietabin][nn] = sumcosn_ass[ietabin][nn] + cos((nn+1)*phi_ass)/effweight_ass;
          sumsinn_ass[ietabin][nn] = sumsinn_ass[ietabin][nn] + sin((nn+1)*phi_ass)/effweight_ass;
          npairs_ass[ietabin][nn] += 1.0/effweight_ass;
        }
      }

      for(int nn = 0; nn<4; nn++)
      {
        double Qx=0;
        double Qy=0;
        double npairs_tot=0;
        for(int i=0;i<MAXETATRGBINSPT;i++)
          for(int j=0;j<MAXETATRGBINSPT;j++)
          {
            if(fabs(j-i)<(int)(2.0/ETATRGBINWIDTHPT)) continue;
            if(npairs_trg[i][nn]==0.0 || npairs_ass[j][nn]==0.0) continue;
            Qx += sumcosn_trg[i][nn]*sumcosn_ass[j][nn]+sumsinn_trg[i][nn]*sumsinn_ass[j][nn];
            Qy += -sumcosn_trg[i][nn]*sumsinn_ass[j][nn]+sumsinn_trg[i][nn]*sumcosn_ass[j][nn];
            npairs_tot += npairs_trg[i][nn]*npairs_ass[j][nn];
          }
        Qx = Qx/npairs_tot;
        Qy = Qy/npairs_tot;
        if(eventcorr_trg.run==eventcorr_ass.run && eventcorr_trg.event==eventcorr_ass.event)
        { 
          hSignalCosn[nn][itrg][jass]->Fill(Qx,npairs_tot);
          hSignalCosnNew[nn][itrg][jass]->Fill(Qx);
//          hSignalSinn[nn][itrg][jass]->Fill(Qy,npairs_tot);
//          hSignalSinnNew[nn][itrg][jass]->Fill(Qy);
          hSignalNpairs[itrg][jass]->Fill(npairs_tot);
        }
        else
        {
          hBackgroundCosn[nn][itrg][jass]->Fill(Qx,npairs_tot);
          hBackgroundCosnNew[nn][itrg][jass]->Fill(Qx);
//          hBackgroundSinn[nn][itrg][jass]->Fill(Qy,npairs_tot);
//          hBackgroundSinnNew[nn][itrg][jass]->Fill(Qy);
          hBackgroundNpairs[itrg][jass]->Fill(npairs_tot);
        }
      }
    }
}
