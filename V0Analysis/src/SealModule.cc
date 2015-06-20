#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "RiceHIG/V0Analysis/interface/V0Validator.h"
#include "RiceHIG/V0Analysis/interface/V0Selector.h"
#include "RiceHIG/V0Analysis/interface/V0NTAnalyzer.h"
#include "RiceHIG/V0Analysis/interface/XiNTAnalyzer.h"

//DEFINE_SEAL_MODULE();

DEFINE_FWK_MODULE(V0Validator);
DEFINE_FWK_MODULE(V0Selector);
DEFINE_FWK_MODULE(V0NTAnalyzer);
DEFINE_FWK_MODULE(XiNTAnalyzer);
