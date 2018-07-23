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
'root://cms-xrd-global.cern.ch//store/user/davidlw/AMPT_GenOnly/AMPT_PiAr_1430GeV_MinimumBias_test_v1/180620_211011/0000/step1_ampt_1.root'
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
process.corr_ana.etatrgmin = cms.double(-2.4)
process.corr_ana.etatrgmax = cms.double(2.4)
process.corr_ana.etaassmin = cms.double(-2.4)
process.corr_ana.etaassmax = cms.double(2.4)
process.corr_ana.pttrgmin = cms.vdouble(0.3, 1.0)
process.corr_ana.pttrgmax = cms.vdouble(3.0, 3.0)
process.corr_ana.ptassmin = cms.vdouble(0.3, 1.0)
process.corr_ana.ptassmax = cms.vdouble(1.0, 3.0)
process.corr_ana.nmin = cms.int32(125)
process.corr_ana.nmax = cms.int32(1000)
