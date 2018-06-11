#ifndef DiHadronCorrelationMultiBaseNew_
#define DiHadronCorrelationMultiBaseNew_

#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
#endif

class DiHadronCorrelationMultiBaseNew : public DiHadronCorrelationMultiBase {
   
 protected:

   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void FillHistsSignal(DiHadronCorrelationEvent&);
   
 public:

   explicit DiHadronCorrelationMultiBaseNew(const edm::ParameterSet&);
   ~DiHadronCorrelationMultiBaseNew() {};
};
#endif  // DiHadronCorrelationMultiBaseNew_
