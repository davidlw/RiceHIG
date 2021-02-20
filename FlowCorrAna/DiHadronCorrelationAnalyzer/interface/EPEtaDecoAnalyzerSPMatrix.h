#ifndef EPEtaDecoAnalyzerSPMatrix_
#define EPEtaDecoAnalyzerSPMatrix_

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

#define MAXETATRGBINSMATRIX 50

class EPEtaDecoAnalyzerSPMatrix : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH1D* hSignalCosn[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hBackgroundCosn[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hSignalCosnNew[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hBackgroundCosnNew[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hSignalSinn[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hBackgroundSinn[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hSignalSinnNew[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hBackgroundSinnNew[5][MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hSignalNPairs[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];
   TH1D* hBackgroundNPairs[MAXETATRGBINSMATRIX][MAXETATRGBINSMATRIX];

   // parameters
   int    bkgFactor;
   double    etaBinWidth;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPEtaDecoAnalyzerSPMatrix(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzerSPMatrix();

};
#endif  // EPEtaDecoAnalyzerSPMatrix_
