#include "../interface/ScalarProdVnAnalyzer.h"
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

ScalarProdVnAnalyzer::ScalarProdVnAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

ScalarProdVnAnalyzer::~ScalarProdVnAnalyzer() 
{}

void ScalarProdVnAnalyzer::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      hSignalCosnSame_pm[itrg][jass] = theOutputs->make<TH2D>(Form("signalcosnsame_pm_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",20000,-1.0,1.0,3,1.5,4.5);
      hBackgroundCosnSame_pm[itrg][jass]= theOutputs->make<TH2D>(Form("backgroundcosnsame_pm_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",20000,-1.0,1.0,3,1.5,4.5);
      hSignalCosnSame_mp[itrg][jass] = theOutputs->make<TH2D>(Form("signalcosnsame_mp_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",20000,-1.0,1.0,3,1.5,4.5);
      hBackgroundCosnSame_mp[itrg][jass]= theOutputs->make<TH2D>(Form("backgroundcosnsame_mp_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",20000,-1.0,1.0,3,1.5,4.5);
    }

  DiHadronCorrelationMultiBase::beginJob();
}

void ScalarProdVnAnalyzer::endJob()
{
  DiHadronCorrelationMultiBase::endJob();
  
  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running scalar product analysis!" << endl;

  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsBackground(eventcorrArray[i],eventcorrArray[i]);

    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;

    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      hDeltaZvtx->Fill(deltazvtx);
//      if(fabs(deltazvtx)>0.06) continue;

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running scalar product analysis!" << endl;
}

void ScalarProdVnAnalyzer::NormalizeHists()
{
}

void ScalarProdVnAnalyzer::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
   double sumcosn_trg_p[MAXPTTRGBINS][5]={{0.0}};
   double sumsinn_trg_p[MAXPTTRGBINS][5]={{0.0}};
   double npairs_trg_p[MAXPTTRGBINS][5]={{0.0}};
   double sumcosn_ass_p[MAXPTASSBINS][5]={{0.0}};
   double sumsinn_ass_p[MAXPTASSBINS][5]={{0.0}};
   double npairs_ass_p[MAXPTASSBINS][5]={{0.0}};

   double sumcosn_trg_m[MAXPTTRGBINS][5]={{0.0}};
   double sumsinn_trg_m[MAXPTTRGBINS][5]={{0.0}};
   double npairs_trg_m[MAXPTTRGBINS][5]={{0.0}};
   double sumcosn_ass_m[MAXPTASSBINS][5]={{0.0}};
   double sumsinn_ass_m[MAXPTASSBINS][5]={{0.0}};
   double npairs_ass_m[MAXPTASSBINS][5]={{0.0}};

   for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
   {
     unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();

     for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
     {
       TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[itrg])[ntrg];
       double effweight_trg = (eventcorr_trg.effVect_trg[itrg])[ntrg];
       double eta_trg = pvector_trg.Eta()-cutPara.etacms;
       double phi_trg = pvector_trg.Phi();

       for(int nn = 1; nn<4; nn++)
       {
         if(eta_trg>0)
         {
           sumcosn_trg_p[itrg][nn] = sumcosn_trg_p[itrg][nn] + cos((nn+1)*phi_trg)/effweight_trg;
           sumsinn_trg_p[itrg][nn] = sumsinn_trg_p[itrg][nn] + sin((nn+1)*phi_trg)/effweight_trg;
           npairs_trg_p[itrg][nn] += 1.0/effweight_trg;
         }
         if(eta_trg<0)
         {
           sumcosn_trg_m[itrg][nn] = sumcosn_trg_m[itrg][nn] + cos((nn+1)*phi_trg)/effweight_trg;
           sumsinn_trg_m[itrg][nn] = sumsinn_trg_m[itrg][nn] + sin((nn+1)*phi_trg)/effweight_trg;
           npairs_trg_m[itrg][nn] += 1.0/effweight_trg;
         }
       }
     }
   }

   for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
   {
     unsigned int nasssize = eventcorr_ass.pVect_ass[jass].size();
     for(unsigned int nass=0;nass<nasssize;nass++)
     {
       TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[jass])[nass];

       double effweight_ass = (eventcorr_ass.effVect_ass[jass])[nass];
       double eta_ass = pvector_ass.Eta()-cutPara.etacms;
       double phi_ass = pvector_ass.Phi();

       for(int nn = 1; nn<4; nn++)
       {
         if(eta_ass>0)
         {
           sumcosn_ass_p[jass][nn] = sumcosn_ass_p[jass][nn] + cos((nn+1)*phi_ass)/effweight_ass;
           sumsinn_ass_p[jass][nn] = sumsinn_ass_p[jass][nn] + sin((nn+1)*phi_ass)/effweight_ass;
           npairs_ass_p[jass][nn] += 1.0/effweight_ass;
         }
         if(eta_ass<0)
         {
           sumcosn_ass_m[jass][nn] = sumcosn_ass_m[jass][nn] + cos((nn+1)*phi_ass)/effweight_ass;
           sumsinn_ass_m[jass][nn] = sumsinn_ass_m[jass][nn] + sin((nn+1)*phi_ass)/effweight_ass;
           npairs_ass_m[jass][nn] += 1.0/effweight_ass;
         }
       }
     }
   }

   for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
     for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
     {
       for(int nn = 1; nn<4; nn++)
       {
         double Qx2same_pm = sumcosn_trg_p[itrg][nn]*sumcosn_ass_m[jass][nn]+sumsinn_trg_p[itrg][nn]*sumsinn_ass_m[jass][nn];
         double Qx2same_mp = sumcosn_trg_m[itrg][nn]*sumcosn_ass_p[jass][nn]+sumsinn_trg_m[itrg][nn]*sumsinn_ass_p[jass][nn];

         if(npairs_trg_p[itrg][nn]!=0.0 && npairs_ass_m[jass][nn]!=0.0)
           Qx2same_pm = Qx2same_pm/npairs_trg_p[itrg][nn]/npairs_ass_m[jass][nn];
         if(npairs_trg_m[itrg][nn]!=0.0 && npairs_ass_p[jass][nn]!=0.0)
           Qx2same_mp = Qx2same_mp/npairs_trg_m[itrg][nn]/npairs_ass_p[jass][nn];

         if(eventcorr_trg.run==eventcorr_ass.run && eventcorr_trg.event==eventcorr_ass.event) 
         {
           hSignalCosnSame_pm[itrg][jass]->Fill(Qx2same_pm,nn+1);
           hSignalCosnSame_mp[itrg][jass]->Fill(Qx2same_mp,nn+1);
         }
         else
         {
           hBackgroundCosnSame_pm[itrg][jass]->Fill(Qx2same_pm,nn+1);
           hBackgroundCosnSame_mp[itrg][jass]->Fill(Qx2same_mp,nn+1);
         } 
       }
     }
}
