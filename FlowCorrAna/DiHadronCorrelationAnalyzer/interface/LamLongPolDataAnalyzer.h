#ifndef LamLongPolDataAnalyzer_
#define LamLongPolDataAnalyzer_

#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class LamLongPolDataAnalyzer : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   // histograms
   TH2D* hLongPol[MAXPTTRGBINS][8];
   TH2D* hLongPolFull[MAXPTTRGBINS];
   TH2D* hLongPolFull_pos[MAXPTTRGBINS];
   TH2D* hLongPolFull_neg[MAXPTTRGBINS];
   TH2D* hLongPolPerpFull[MAXPTTRGBINS];
   TH2D* hLongPolPerpFull_pos[MAXPTTRGBINS];
   TH2D* hLongPolPerpFull_neg[MAXPTTRGBINS];
   TH2D* hLongPolCos2[MAXPTTRGBINS];
   TH2D* hLongPolSin2[MAXPTTRGBINS];
   TH2D* hLongPolCos3[MAXPTTRGBINS];
   TH2D* hLongPolSin3[MAXPTTRGBINS];
   TH2D* hdPhiEP2[MAXPTTRGBINS];
   TH2D* hdPhiEP3[MAXPTTRGBINS];
   TH1D* hcos2_2p_ref;
   TH1D* hsin2_2p_ref;
   TH1D* hcos2_1p_ref;
   TH1D* hcos2_1p_p_ref;
   TH1D* hcos2_1p_m_ref;
   TH1D* hsin2_1p_ref;
   TH1D* hsin2_1p_p_ref;
   TH1D* hsin2_1p_m_ref;
   TH1D* hcos3_2p_ref;
   TH1D* hsin3_2p_ref;
   TH1D* hcos3_1p_ref;
   TH1D* hcos3_1p_p_ref;
   TH1D* hcos3_1p_m_ref;
   TH1D* hsin3_1p_ref;
   TH1D* hsin3_1p_p_ref;
   TH1D* hsin3_1p_m_ref;

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   LamLongPolDataAnalyzer(const edm::ParameterSet&);
   ~LamLongPolDataAnalyzer();
};
#endif  // LamLongPolDataAnalyzer_
