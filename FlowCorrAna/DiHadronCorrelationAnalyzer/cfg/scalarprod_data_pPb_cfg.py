import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3000)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hlt = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hlt.HLTPaths = ['HLT_PAFullTracks_Multiplicity185*_v*'] # for allphysics
process.hlt.andOr = cms.bool(True)
process.hlt.throw = cms.bool(False)

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
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

process.eventFilter_HM = cms.Sequence(
    process.hlt *
    process.PAcollisionEventSelection
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/hidata/PARun2016C/PAHighMultiplicity7/AOD/PromptReco-v1/000/285/530/00000/001FD395-CFB0-E611-B11B-02163E011AB6.root'
#'/store/user/davidlw/PAHighMultiplicity7/RecoSkim2016_pPb_HM280_v4/170103_123148/0000/pPb_HM_127.root'
'root://cmsxrootd.fnal.gov///store/hidata/PARun2016C/PAHighMultiplicity7/AOD/PromptReco-v1/000/285/480/00000/5E0F96D9-08AF-E611-9C83-FA163E0C8993.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.scalarprodnew_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('scalarprod.root')
                                   )

process.scalarprod_ana.nmin = cms.int32(185)
process.scalarprod_ana.nmax = cms.int32(250)
process.scalarprod_ana_hp.nmin = cms.int32(185)
process.scalarprod_ana_hp.nmax = cms.int32(250)
process.scalarprod_ana_hm.nmin = cms.int32(185)
process.scalarprod_ana_hm.nmax = cms.int32(250)

process.ana_hp = cms.Path(process.eventFilter_HM * process.scalarprod_ana_hp)
process.ana_hm = cms.Path(process.eventFilter_HM * process.scalarprod_ana_hm)
process.ana = cms.Path(process.eventFilter_HM * process.scalarprod_ana)
