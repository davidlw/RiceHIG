import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc_HIon', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
#process.hltHIMB.andOr = cms.bool(True)
#process.hltHIMB.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_1007_1_ACm.root',
#'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_2067_1_opp.root'
#'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_2058_1_MSV.root',
#'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_444_1_yq5.root',
#'/store/user/twang/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110/8279ae7c7b9873cb2e7129d3c6d86a22/step3_RAW2DIGI_L1Reco_RECO_451_1_vB8.root'
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

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.newCentralityBin = process.centralityBin.clone()

process.ana = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_hf)
process.scalarprod_ana_HI_hf.IsReCenterTrg = cms.bool(True)
process.scalarprod_ana_HI_hf.IsReCenterAss = cms.bool(True)
process.scalarprod_ana_HI_hf.centmin = cms.int32(-1)
process.scalarprod_ana_HI_hf.centmax = cms.int32(-1)
process.scalarprod_ana_HI_hf.nmin = cms.int32(400)
process.scalarprod_ana_HI_hf.nmax = cms.int32(10000)
process.scalarprod_ana_HI_hf.centralityBinLabel = cms.InputTag("newCentralityBin","HFtowers")