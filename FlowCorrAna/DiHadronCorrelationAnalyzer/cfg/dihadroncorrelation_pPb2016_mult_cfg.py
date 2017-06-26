import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(15000)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/04214B66-30AC-E611-BFBC-FA163EBFF447.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/06AF52AD-2EAC-E611-83B5-02163E014617.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/0805B68E-2DAC-E611-BDE5-02163E014186.root'
'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/18E99CF6-59AB-E611-8F92-02163E01440E.root',
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/DC56AAB2-5EAB-E611-A27A-FA163E251515.root'
#'file:/net/hisrv0001/home/davidlw/scratch1/RECO_5TeV.root'
#'/store/user/gsfs/EPOS5TeV_GEN_SIM/EPOS5TeV_RECO25ns_10262016/161026_112501/0000/step3_25ns_RAW2DIGI_L1Reco_RECO_101.root',
#'/store/user/gsfs/EPOS5TeV_GEN_SIM/EPOS5TeV_RECO25ns_10262016/161026_112501/0000/step3_25ns_RAW2DIGI_L1Reco_RECO_102.root',
#'/store/user/gsfs/EPOS5TeV_GEN_SIM/EPOS5TeV_RECO25ns_10262016/161026_112501/0000/step3_25ns_RAW2DIGI_L1Reco_RECO_103.root',
#'/store/user/gsfs/EPOS5TeV_GEN_SIM/EPOS5TeV_RECO25ns_10262016/161026_112501/0000/step3_25ns_RAW2DIGI_L1Reco_RECO_104.root',
#'/store/user/gsfs/EPOS5TeV_GEN_SIM/EPOS5TeV_RECO25ns_10262016/161026_112501/0000/step3_25ns_RAW2DIGI_L1Reco_RECO_105.root',
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#process.GlobalTag.globaltag = '80X_dataRun2_Express_v15'

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltMB_pPb = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB_pPb.HLTPaths = ['HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_*_v*']
#process.hltMB_pPb.HLTPaths = ['HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v1']
process.hltMB_pPb.andOr = cms.bool(True)
process.hltMB_pPb.throw = cms.bool(False)

# ================ L1 Filters =====================
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
from L1Trigger.Skimmer.l1Filter_cfi import l1Filter

process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 10 && tracksSize >= 2"),
#    cut = cms.string("!isFake && tracksSize >= 1"),
    filter = cms.bool(True),   # otherwise it won't filter the events
)

#Reject beam scraping events standard pp configuration
process.NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.PAcollisionEventSelection = cms.Sequence(
                                         process.hfCoincFilter *
                                         process.PAprimaryVertexFilter *
                                         process.NoScraping
                                         )

process.eventFilter_MB = cms.Sequence(
#    process.hltMB_pPb *
    process.PAcollisionEventSelection
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('pPb_2016.root')
                                   )

process.ana_mb = cms.Path(process.eventFilter_MB*process.corr_ana)

process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.IsDebug = cms.bool(True)
#process.corr_ana.TriggerID = cms.string('CaloTower')
process.corr_ana.pttrgmin = cms.vdouble(0.0)
process.corr_ana.pttrgmax = cms.vdouble(10000.0)
#process.corr_ana.ptassmin = cms.vdouble(1.0)
#process.corr_ana.ptassmax = cms.vdouble(3.0)
#process.corr_ana.nmin = cms.int32(110)
#process.corr_ana.nmax = cms.int32(1000)
