#ifndef CutParameters_
#define CutParameters_

#include <vector>
#include <TString.h>

using namespace std;

class CutParameters {                                                                                  

 public:                                                                                           
   unsigned int runmin;
   unsigned int runmax;
   int     nmin;
   int     nmax;
   int     centmin;
   int     centmax;
   double  etatrgmin;                                                                                     
   double  etatrgmax;
   double  etaassmin;
   double  etaassmax;   
   double  etamultmin;
   double  etamultmax;
   double  chargeasymmin;
   double  chargeasymmax;
   vector<double>  pttrgmin;
   vector<double>  pttrgmax;
   vector<double>  ptassmin;
   vector<double>  ptassmax;
   double  ptmultmin;
   double  ptmultmax;   
   double  xvtxcenter;
   double  yvtxcenter;
   double  zvtxcenter;
   double  rhomin;
   double  rhomax;
   double  zvtxmin;
   double  zvtxmax;
   double  zvtxbin;
   double  vtxsepmin;
   double  etacms;
   double  etagap;
   int     nvtxmax;
   bool    istrigger;
   vector<TString> triggernames;
   vector<TString> vetonames;
   int     njetsmin;
   int     njetsmax;
   double  jetetmin;
   double  jetetmax;
   double  jetetfraction;
   double  leadjetetmin;
   double  subjetetmin;
   double  pthard1;
   double  pthard2;
   double  delta;
   double  mass_trg;
   double  mass_ass;
   vector<double>  massmean_trg;
   vector<double>  massmean_ass;
   vector<double>  masswidth_trg;
   vector<double>  masswidth_ass;
   double  genpdgId_trg;
   double  genpdgId_ass;
   bool    isstable_trg;
   bool    isstable_ass;
   bool    ischarge_trg;
   bool    ischarge_ass; 
   TString trgtrackCollection;
   TString asstrackCollection;
   TString vertexCollection;
   TString jetCollection;
   TString genParticleCollection;
   TString genJetCollection;
   TString chargeCandidateCollection;
   TString superClusterCollection;
   TString superClusterFwdCollection;
   TString centralityCollection;
   TString v0CandidateCollection;
   TString pfCandidateCollection;
   bool IsGenMult;
   bool IsGenVtx;
   bool IsVtxSel;
   bool IsEventEngineer;
   bool IsInvMass;
   bool IsCorr;
   bool IsHI;
   bool IsV0SignalTrg;
   bool IsV0SignalAss;
   bool IsV0BkgTrg;
   bool IsV0BkgAss;
   bool IsDoEventShape;
   bool IsTrackNtuple;
   bool IsHIGenInfoNtuple;
   bool IsLeadTrack;
   bool IsSubJet;
   bool IsMonoJet;
   bool IsFullMatrix;
   bool IsSymmetrize;
   bool IsPtWeightTrg;  
   bool IsPtWeightAss;
   bool IsTrgEtaCutAbs;
   bool IsAssEtaCutAbs; 
   bool IsHarmonics;
   bool IsHarmonicsEta1Eta2;
   bool IsFlowQVector;
   bool IsPPTrkQuality;
   bool IsHITrkQuality;
   bool IsDebug;
   bool IsReCenter;
   bool IsDSGenEvt;
   bool IsCheckTrgV0Dau;
   bool IsCheckAssV0Dau;
   bool IsBoostRestFrameGen;
   bool IsBoostRestFrameV0;
   bool IsGenRP;
};

#endif  // CutParameters_
