import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
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
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
#process.hltHIMB.andOr = cms.bool(True)
#process.hltHIMB.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/HIMinBias2015/recoExpress_45.root'
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

process.ana = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI)
process.scalarprod_ana_HI.IsReCenterTrg = cms.bool(False)
process.scalarprod_ana_HI.IsReCenterAss = cms.bool(True)
process.scalarprod_ana_HI.centralityBinLabel = cms.InputTag("newCentralityBin","HFtowers")
process.scalarprod_ana_HI_cent010 = process.scalarprod_ana_HI.clone()
process.scalarprod_ana_HI_cent010.centmin = cms.int32(0)
process.scalarprod_ana_HI_cent010.centmax = cms.int32(20)
process.scalarprod_ana_HI_cent1020 = process.scalarprod_ana_HI.clone()
process.scalarprod_ana_HI_cent1020.centmin = cms.int32(20)
process.scalarprod_ana_HI_cent1020.centmax = cms.int32(40)
process.scalarprod_ana_HI_cent2030 = process.scalarprod_ana_HI.clone()
process.scalarprod_ana_HI_cent2030.centmin = cms.int32(40)
process.scalarprod_ana_HI_cent2030.centmax = cms.int32(60)
process.scalarprod_ana_HI_cent3040 = process.scalarprod_ana_HI.clone()
process.scalarprod_ana_HI_cent3040.centmin = cms.int32(60)
process.scalarprod_ana_HI_cent3040.centmax = cms.int32(80)
process.scalarprod_ana_HI_cent4050 = process.scalarprod_ana_HI.clone()
process.scalarprod_ana_HI_cent4050.centmin = cms.int32(80)
process.scalarprod_ana_HI_cent4050.centmax = cms.int32(100)
process.scalarprod_ana_HI_cent5060 = process.scalarprod_ana_HI.clone()
process.scalarprod_ana_HI_cent5060.centmin = cms.int32(100)
process.scalarprod_ana_HI_cent5060.centmax = cms.int32(120)

process.ana_cent010 = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_cent010)
process.ana_cent1020 = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_cent1020)
process.ana_cent2030 = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_cent2030)
process.ana_cent3040 = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_cent3040)
process.ana_cent4050 = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_cent4050)
process.ana_cent5060 = cms.Path(process.newCentralityBin * process.scalarprod_ana_HI_cent5060)
