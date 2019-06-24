import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/hidata/PARun2016C/PADTrack1/AOD/PromptReco-v1/000/286/496/00000/FEF99E81-6EBD-E611-8EB7-02163E012863.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#Pileup filter
process.load("VertexCompositeAnalysis.VertexCompositeProducer.pileUpFilter_cff")

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltPt50_pPb = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltPt50_pPb.HLTPaths = ['HLT_PAFullTracks_HighPt50*_v*']
process.hltPt50_pPb.andOr = cms.bool(True)
process.hltPt50_pPb.throw = cms.bool(False)
process.hltPt40_pPb = process.hltPt50_pPb.clone()
process.hltPt40_pPb.HLTPaths = ['HLT_PAFullTracks_HighPt40*_v*']
process.hltPt30_pPb = process.hltPt50_pPb.clone()
process.hltPt30_pPb.HLTPaths = ['HLT_PAFullTracks_HighPt30*_v*']
process.hltPt20_pPb = process.hltPt50_pPb.clone()
process.hltPt20_pPb.HLTPaths = ['HLT_PAFullTracks_HighPt20*_v*']


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
                                         process.NoScraping *
                                         process.olvFilter_pPb8TeV_dz1p0
                                         )

process.eventFilter_HM = cms.Sequence(
    process.hltPt50_pPb *
    process.PAcollisionEventSelection
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.ptspectra_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('ptspectra_highpt.root')
                                   )

process.ana = cms.Path(process.eventFilter_HM*process.ptspectra_ana)
process.ptspectra_ana.IsCorr = cms.bool(False)
process.ptspectra_ana.nmin = cms.int32(0)
process.ptspectra_ana.nmax = cms.int32(100000)
process.ptspectra_ana.pttrgmin = cms.vdouble(0.0)
process.ptspectra_ana.pttrgmax = cms.vdouble(10000.0)
process.ptspectra_ana.ptassmin = cms.vdouble(0.0)
process.ptspectra_ana.ptassmax = cms.vdouble(10000.0)
