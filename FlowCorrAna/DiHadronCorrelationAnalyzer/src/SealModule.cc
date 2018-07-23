#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiAnalyzerQ2.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiAnalyzerChAsym.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ScalarProdVnAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ScalarProdVnAnalyzerNew.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzerSPMatrix.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPPtDecoAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EbyEFlowAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/InvMassAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/MultiplicityAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ChargeDepCorrAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ChargeDepCorrAnalyzerSP2.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ChargeDepCorrAnalyzerSP3.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/LamPolGenAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/LamLongPolDataAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/LamPolGenAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/LamPolDataAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/LamPolDataAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzerSP2.h"


//DEFINE_SEAL_MODULE();

DEFINE_FWK_MODULE(DiHadronCorrelationMultiAnalyzer);
DEFINE_FWK_MODULE(DiHadronCorrelationMultiAnalyzerQ2);
DEFINE_FWK_MODULE(DiHadronCorrelationMultiAnalyzerChAsym);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzer);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzerSP);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzerSP2);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzerSPMatrix);
DEFINE_FWK_MODULE(EPPtDecoAnalyzerSP);
DEFINE_FWK_MODULE(EbyEFlowAnalyzer);
DEFINE_FWK_MODULE(InvMassAnalyzer);
DEFINE_FWK_MODULE(MultiplicityAnalyzer);
DEFINE_FWK_MODULE(ChargeDepCorrAnalyzerSP);
DEFINE_FWK_MODULE(ChargeDepCorrAnalyzerSP2);
DEFINE_FWK_MODULE(ChargeDepCorrAnalyzerSP3);
DEFINE_FWK_MODULE(LamPolGenAnalyzer);
DEFINE_FWK_MODULE(LamLongPolDataAnalyzer);
DEFINE_FWK_MODULE(LamPolGenAnalyzerSP);
DEFINE_FWK_MODULE(LamPolDataAnalyzer);
DEFINE_FWK_MODULE(LamPolDataAnalyzerSP);
DEFINE_FWK_MODULE(ScalarProdVnAnalyzer);
DEFINE_FWK_MODULE(ScalarProdVnAnalyzerNew);
