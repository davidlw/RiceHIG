import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
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
'/store/user/davidlw/AMPT_PbPb5TeV_Gen/b812_string_batch1/160318_160457/0000/amptDefault_cfi_py_GEN_114.root',
#'/store/user/davidlw/AMPT_PbPb5TeV_Gen/b812_string_batch1/160318_160457/0000/amptDefault_cfi_py_GEN_115.root',
#'/store/user/davidlw/AMPT_PbPb5TeV_Gen/b812_string_batch1/160318_160457/0000/amptDefault_cfi_py_GEN_116.root'
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

process.ana_step = cms.Path(process.lampolgen)
#process.lampolgen.b_genmin = cms.double(-1)
#process.lampolgen.b_genmax = cms.double(-1)
process.lampolgen.pol_lam_mean = cms.double(0.3)
