#ifndef EPPtDecoAnalyzerSPNew_
#define EPPtDecoAnalyzerSPNew_

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

class EPPtDecoAnalyzerSPNew : public DiHadronCorrelationMultiBaseNew {
   
 protected:

   float sumcos1_trk[20][50];
   float sumsin1_trk[20][50];
   float sumcos2_trk[20][50];
   float sumsin2_trk[20][50];
   float sumcos3_trk[20][50];
   float sumsin3_trk[20][50];
   float sumcos4_trk[20][50];
   float sumsin4_trk[20][50];
   float sumcos5_trk[20][50];
   float sumsin5_trk[20][50];
   float npairs_trk[20][50];
   float sumcosn_p_hf[10];
   float sumsinn_p_hf[10];
   float npairs_p_hf;
   float sumcosn_m_hf[10];
   float sumsinn_m_hf[10];
   float npairs_m_hf;

   // parameters
   double etaBinWidth;
   unsigned int NETABINS;
   unsigned int NPTBINS;

   TTree* qVectorTree;
   
//   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void beginJob();
   virtual void endJob();

//   virtual void NormalizeHists();
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:
   EPPtDecoAnalyzerSPNew(const edm::ParameterSet&);
//   ~EPPtDecoAnalyzerSPNew();
};
#endif  // EPPtDecoAnalyzerSPNew_
