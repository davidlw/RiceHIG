import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_HeavyIon_v12', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
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
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIL1MinimumBiasHF*AND_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.load('HeavyIonsAnalysis.EventAnalysis.HIClusterCompatibilityFilter_cfi')
#process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)
process.evtsel_filter = cms.Sequence(process.hfCoincFilter3 * process.primaryVertexFilter)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/gsfs/Hydjet_Quenched_MinBias_Drum5Nv75/Hydjet_Quenched_MinBias_Drum5Nv75_RECO_20160318/160318_231321/0000/step3_MinBias_PbPb_RAW2DIGI_L1Reco_RECO_107.root'
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

process.ana = cms.Path(process.evtsel_filter * process.newCentralityBin * process.corr_ana_HI)
process.corr_ana_HI.centmin = cms.int32(-1)
process.corr_ana_HI.centmax = cms.int32(-1)
