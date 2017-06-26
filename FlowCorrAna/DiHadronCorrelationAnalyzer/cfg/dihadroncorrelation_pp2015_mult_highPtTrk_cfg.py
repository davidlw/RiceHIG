import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

### conditions
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_ExpressHI_v2', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltMB1 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB1.HLTPaths = ['HLT_HIL1MinimumBiasHF1ANDExpress_v1']
#process.hltMB1.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1']
process.hltMB1.andOr = cms.bool(True)
process.hltMB1.throw = cms.bool(False)

process.hltMB2 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB2.HLTPaths = ['HLT_HIL1MinimumBiasHF2ANDExpress_v1']
#process.hltMB2.HLTPaths = ['HLT_HIL1MinimumBiasHF2AND_v1']
process.hltMB2.andOr = cms.bool(True)
process.hltMB2.throw = cms.bool(False)

process.hltMB3 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB3.HLTPaths = ['HLT_HIL1HFplusANDminusTH0Express_v1']
#process.hltMB3.HLTPaths = ['HLT_HIL1HFplusANDminusTH0_v1']
process.hltMB3.andOr = cms.bool(True)
process.hltMB3.throw = cms.bool(False)

process.collisionEventSelection_new = cms.Sequence(
                                       process.hfCoincFilter3 *
                                       process.primaryVertexFilter)

process.eventFilter_MB1 = cms.Sequence(
    process.hltMB1 *
    process.collisionEventSelection_new
)

process.eventFilter_MB1_nosel = cms.Sequence(
    process.hltMB1 
)

process.eventFilter_MB2 = cms.Sequence(
    process.hltMB2 *
    process.collisionEventSelection_new
)

process.eventFilter_MB2_nosel = cms.Sequence(
    process.hltMB2
)

process.eventFilter_MB3 = cms.Sequence(
    process.hltMB3 *
    process.collisionEventSelection_new
)

process.eventFilter_MB3_nosel = cms.Sequence(
    process.hltMB3
)


#process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'root://xrootd-cms.infn.it//store/express/HIRun2015/HIExpressPhysics/FEVT/Express-v1/000/262/834/00000/34BF890B-D196-E511-BB9F-02163E014434.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.newCentralityBin = process.centralityBin.clone()

process.corr_ana_HI.IsCorr = cms.bool(False)
#process.corr_ana_HI.IsDebug = cms.bool(True)
process.corr_ana_HI.pttrgmin = cms.vdouble(0.0)
process.corr_ana_HI.pttrgmax = cms.vdouble(10000)
process.corr_ana_HI.centmin = cms.int32(0)
process.corr_ana_HI.centmax = cms.int32(200)

process.corr_ana_HI_1 = process.corr_ana_HI.clone()
process.corr_ana_HI_2 = process.corr_ana_HI.clone()
process.corr_ana_HI_3 = process.corr_ana_HI.clone()
process.corr_ana_HI_nosel1 = process.corr_ana_HI.clone()
process.corr_ana_HI_nosel2 = process.corr_ana_HI.clone()
process.corr_ana_HI_nosel3 = process.corr_ana_HI.clone()

process.ana1 = cms.Path(process.eventFilter_MB1 * process.newCentralityBin * process.corr_ana_HI_1)
process.ana1_nosel = cms.Path( process.eventFilter_MB1_nosel * process.newCentralityBin * process.corr_ana_HI_nosel1)
process.ana2 = cms.Path(process.eventFilter_MB2 * process.newCentralityBin * process.corr_ana_HI_2)
process.ana2_nosel = cms.Path( process.eventFilter_MB2_nosel * process.newCentralityBin * process.corr_ana_HI_nosel2)
#process.ana3 = cms.Path(process.eventFilter_MB3 * process.newCentralityBin * process.corr_ana_HI_3)
#process.ana3_nosel = cms.Path( process.eventFilter_MB3_nosel * process.newCentralityBin * process.corr_ana_HI_nosel3)
