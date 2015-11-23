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
#        nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
#        centralitySrc = cms.InputTag("hiCentrality")
#        )

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
#process.hltHIMB.andOr = cms.bool(True)
#process.hltHIMB.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_1007_1_ACm.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.scalarprod_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('scalarprod.root')
                                   )

process.ana = cms.Path(process.scalarprod_ana_HI)
process.scalarprod_ana_HI.TriggerID = cms.string('GenParticle')
process.scalarprod_ana_HI.AssociateID = cms.string('GenParticle')
#process.scalarprod_ana_HI.IsGenMult = cms.bool(True)
#process.scalarprod_ana_HI.IsVtxSel = cms.bool(False)
process.scalarprod_ana_HI.IsDebug = cms.bool(True)
process.scalarprod_ana_HI.ptassmin = cms.vdouble(0.0)
process.scalarprod_ana_HI.ptassmax = cms.vdouble(10000.0)
process.scalarprod_ana_HI.IsGenMult = cms.bool(True)
process.scalarprod_ana_HI.IsVtxSel = cms.bool(False)
