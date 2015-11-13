import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
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
'/store/user/davidlw/AMPT_PbPb_Gen/MB_string_v4/150808_142728/0000/amptDefault_cfi_py_GEN_642.root',
'/store/user/davidlw/AMPT_PbPb_Gen/MB_string_v4/150808_142728/0000/amptDefault_cfi_py_GEN_963.root',
'/store/user/davidlw/AMPT_PbPb_Gen/MB_string_v4/150808_142728/0000/amptDefault_cfi_py_GEN_205.root',
'/store/user/davidlw/AMPT_PbPb_Gen/MB_string_v4/150808_142728/0000/amptDefault_cfi_py_GEN_828.root',
'/store/user/davidlw/AMPT_PbPb_Gen/MB_string_v4/150808_142728/0000/amptDefault_cfi_py_GEN_191.root',
'/store/user/davidlw/AMPT_PbPb_Gen/MB_string_v4/150808_142728/0000/amptDefault_cfi_py_GEN_217.root'
                )
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.lampolgen_cfi")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('lampolgen.root')
                                   )

process.ana_step = cms.Path(process.corr_ana)
process.corr_ana.TriggerID = cms.string('GenParticle')
process.corr_ana.AssociateID = cms.string('GenParticle')
process.corr_ana.nmin = cms.int32(500)
process.corr_ana.nmax = cms.int32(1500)
process.corr_ana.pol_lam = cms.double(0.5)
