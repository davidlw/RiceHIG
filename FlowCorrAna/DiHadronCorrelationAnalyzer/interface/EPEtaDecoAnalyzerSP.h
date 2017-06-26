#ifndef EPEtaDecoAnalyzerSP_
#define EPEtaDecoAnalyzerSP_

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

#define MAXETATRGBINS 16
#define ETATRGBINWIDTH 0.3

class EPEtaDecoAnalyzerSP : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXETATRGBINS];
   TH2D* hBackgroundCosn[MAXETATRGBINS];
   TH1D* hSignalNPairs[MAXETATRGBINS];
   TH1D* hBackgroundNPairs[MAXETATRGBINS];
   TH2D* hSignalCosnSame[MAXETATRGBINS];
   TH2D* hBackgroundCosnSame[MAXETATRGBINS];
   TH2D* hSignalCosnDiff[MAXETATRGBINS];
   TH2D* hBackgroundCosnDiff[MAXETATRGBINS];
   TH2D* hSignalSinn[MAXETATRGBINS];
   TH2D* hBackgroundSinn[MAXETATRGBINS];
   TH2D* hSignalSinnPvsN[5];
   TH2D* hBackgroundSinnPvsN[5];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPEtaDecoAnalyzerSP(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzerSP();

};
#endif  // EPEtaDecoAnalyzerSP_
