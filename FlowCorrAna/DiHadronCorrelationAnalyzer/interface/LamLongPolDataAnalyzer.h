#ifndef LamLongPolDataAnalyzer_
#define LamLongPolDataAnalyzer_

<<<<<<< HEAD
#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
=======
#ifndef DiHadronCorrelationMultiBaseNew_
#include "DiHadronCorrelationMultiBaseNew.h"
>>>>>>> a0623bf651233e590d34b2e295af2623a4f87153
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

<<<<<<< HEAD
class LamLongPolDataAnalyzer : public DiHadronCorrelationMultiBase {
=======
class LamLongPolDataAnalyzer : public DiHadronCorrelationMultiBaseNew {
>>>>>>> a0623bf651233e590d34b2e295af2623a4f87153
   
 protected:

   // histograms
<<<<<<< HEAD
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
=======
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
>>>>>>> a0623bf651233e590d34b2e295af2623a4f87153

//   void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

<<<<<<< HEAD
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
=======
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
>>>>>>> a0623bf651233e590d34b2e295af2623a4f87153
   
 public:
   LamLongPolDataAnalyzer(const edm::ParameterSet&);
   ~LamLongPolDataAnalyzer();
};
#endif  // LamLongPolDataAnalyzer_
