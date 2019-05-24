import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
#process.HeavyIonGlobalParameters = cms.PSet(
#        centralityVariable = cms.string("HFtowers"),
##       nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
#        centralitySrc = cms.InputTag("hiCentrality")
#        )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/EPOS_PbPb5TeV/MB_Gen_v1/160628_112907/0000/ReggeGribovPartonMC_EposLHC_5TeV_PbPb_cfi_py_GEN_10.root'
#'/store/himc/HINPbPbWinter16DR/Hydjet_Quenched_MinBias_5020GeV_750/AODSIM/NoPU_75X_mcRun2_HeavyIon_v1_75X_mcRun2_HeavyIon_v13-v1/40000/0223C75F-B8F5-E511-B30C-14187741212B.root'
#'file:/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_7_4_7_patch2_AMPT/src/MinBias_TuneZ2_7TeV_pythia6_cff_py_GEN.root'
#'/store/user/davidlw/MinBias_TuneZ2_7TeV_pythia6/HM85_batch1/150825_015323/0000/MinBias_TuneZ2_7TeV_pythia6_cff_py_GEN_382.root'
#'/store/user/davidlw/AMPT_pp_Gen/HM95_string_v2/150808_041857/0000/amptDefault_cfi_py_GEN_834.root',
#'/store/user/davidlw/AMPT_pp_Gen/HM95_string_v2/150808_041857/0000/amptDefault_cfi_py_GEN_836.root',
#'/store/user/davidlw/AMPT_pp_Gen/HM95_string_v2/150808_041857/0000/amptDefault_cfi_py_GEN_846.root',
#'/store/user/davidlw/AMPT_pp_Gen/HM95_string_v2/150808_041857/0000/amptDefault_cfi_py_GEN_849.root'

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_1.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_10.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_14.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_17.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_18.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_20.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_21.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_22.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_23.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_24.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_25.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_28.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_3.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_33.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_34.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_35.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_36.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_37.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_39.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_4.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_40.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_8.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiO_1850GeV_MinimumBias_test_v1/180620_211032/0000/step1_ampt_9.root',

'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_1.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_10.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_11.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_12.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_14.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_15.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_17.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_18.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_19.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_20.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_21.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_22.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_23.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_24.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_25.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_26.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_27.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_29.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_3.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_30.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_32.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_33.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_34.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_35.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_37.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_38.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_39.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_4.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_5.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_7.root',
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_9.root',

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_1.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_2.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_3.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_4.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_5.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_6.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_7.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_8.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_9.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_8160GeV_MinimumBias_test_v1/180614_112828/0000/step1_ampt_10.root'

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_1.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_2.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_3.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_4.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_5.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_6.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_7.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_8.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_9.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_10.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_11.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_12.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_13.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_14.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_15.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_16.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_17.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_18.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_19.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPb_950GeV_MinimumBias_test_v1/180621_211536/0000/step1_ampt_20.root',

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_31.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_32.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_33.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_34.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_35.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_36.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_37.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_3.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_39.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PPb_8160GeV_MinimumBias_test_v1/180614_112810/0000/step1_ampt_30.root',

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_1.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_2.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_39.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_40.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_5.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_6.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_7.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_8.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_9.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_30.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_11.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_12.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_13.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_14.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_15.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_16.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_17.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_18.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_19.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiP_8160GeV_MinimumBias_test_v1/180620_211115/0000/step1_ampt_20.root',

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_10.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_11.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_12.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_13.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_14.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_15.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_16.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_17.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_18.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_19.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_20.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_21.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_22.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_23.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_24.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_25.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_26.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_27.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_28.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PP_8160GeV_MinimumBias_test_v1/180620_211137/0000/step1_ampt_29.root',

#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_1.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_10.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_11.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_16.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_17.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_18.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_2.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_21.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_23.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_24.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_25.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_27.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_29.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_30.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_32.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_33.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_39.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_6.root',
#'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiPi_8160GeV_MinimumBias_test_v1/180620_215245/0000/step1_ampt_8.root',
                )
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana_step = cms.Path(process.corr_ana)
process.corr_ana.TriggerID = cms.string('GenParticle')
process.corr_ana.AssociateID = cms.string('GenParticle')
process.corr_ana.IsVtxSel = cms.bool(False)
process.corr_ana.IsGenMult = cms.bool(True)
process.corr_ana.IsDebug = cms.bool(True)
process.corr_ana.IsCorr = cms.bool(False)
process.corr_ana.etatrgmin = cms.double(-10.)
process.corr_ana.etatrgmax = cms.double(10.)
process.corr_ana.etaassmin = cms.double(-10.)
process.corr_ana.etaassmax = cms.double(10.)
process.corr_ana.pttrgmin = cms.vdouble(0.0)
process.corr_ana.pttrgmax = cms.vdouble(1000.0)
process.corr_ana.ptassmin = cms.vdouble(0.0)
process.corr_ana.ptassmax = cms.vdouble(1000.0)
process.corr_ana.etamultmin = cms.double(-3.)
process.corr_ana.etamultmax = cms.double(5.)
process.corr_ana.ptmultmin = cms.double(0.2)
process.corr_ana.ptmultmax = cms.double(10000)
process.corr_ana.nmin = cms.int32(120)
process.corr_ana.nmax = cms.int32(1000)
