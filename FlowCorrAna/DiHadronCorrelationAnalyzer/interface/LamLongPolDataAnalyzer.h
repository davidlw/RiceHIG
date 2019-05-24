#ifndef LamLongPolDataAnalyzer_
#define LamLongPolDataAnalyzer_

#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class LamLongPolDataAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH2D* hLongPolFull[MAXPTTRGBINS];
   TH2D* hLongPol[MAXPTTRGBINS][8];
   TH2D* hLongPolCos[MAXPTTRGBINS];
   TH2D* hLongPolSin[MAXPTTRGBINS];
   TH2D* hdPhiEP[MAXPTTRGBINS];
   TH1D* hcos2p_ref;
   TH1D* hsin2p_ref;
   TH1D* hcos1p_ref;
   TH1D* hcos1p_p_ref;
   TH1D* hcos1p_m_ref;
   TH1D* hsin1p_ref;
   TH1D* hsin1p_p_ref;
   TH1D* hsin1p_m_ref;

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   
 public:
   LamLongPolDataAnalyzer(const edm::ParameterSet&);
   ~LamLongPolDataAnalyzer();
};
#endif  // LamLongPolDataAnalyzer_
