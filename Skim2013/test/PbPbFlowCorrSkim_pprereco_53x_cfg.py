import FWCore.ParameterSet.Config as cms
process = cms.Process("ANASKIM")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
  '/store/user/davidlw/HIMinBiasUPC/pprereco_53X_v4/f8fba1ae36aa7f91f9872c20446c6a79/reco_ppRECO_mbUpc_53X_1000_1_l3D.root'
)
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

# =============== Import Sequences =====================
process.load('HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff')

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHM.HLTPaths = ['HLT_HIMinBiasHfOrBSC_v*']
process.hltHM.andOr = cms.bool(True)
process.hltHM.throw = cms.bool(False)

process.eventFilter_HM = cms.Sequence( 
    process.hltHM *
    process.PAcollisionEventSelection *
    process.pileupVertexFilterCutGplus
)

process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

########## V0 candidate rereco ############################################################### 

process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    tkNhitsCut = cms.int32(0),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(1.0),
    dauLongImpactSigCut = cms.double(1.0),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(0.0)
)
process.v0rereco_step = cms.Path( process.eventFilter_HM * process.generalV0CandidatesNew )

########## ReTracking #########################################################################
process.generalTracksLowPt = process.generalTracks.clone()
process.iterTracking.replace(process.generalTracks,process.generalTracksLowPt)
process.offlinePrimaryVerticesLowPt = process.offlinePrimaryVertices.clone( TrackLabel = cms.InputTag("generalTracksLowPt") )
process.generalV0CandidatesLowPt = process.generalV0CandidatesNew.clone(
  trackRecoAlgorithm = cms.InputTag('generalTracksLowPt'),
  vertexRecoAlgorithm = cms.InputTag('offlinePrimaryVerticesLowPt')
)

process.lowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.1
process.detachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.1
process.mixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.ptMin = 0.25
process.mixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.ptMin = 0.35
process.pixelLessStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.5
process.pixelPairStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.3

process.dedxTruncated40LowPt = process.dedxTruncated40.clone(
    tracks                     = cms.InputTag("generalTracksLowPt"),
    trajectoryTrackAssociation = cms.InputTag("generalTracksLowPt")
)
process.dedxHarmonic2LowPt = process.dedxHarmonic2.clone(
    tracks                     = cms.InputTag("generalTracksLowPt"),
    trajectoryTrackAssociation = cms.InputTag("generalTracksLowPt")
)
process.dedxDiscrimASmiLowPt = process.dedxDiscrimASmi.clone(
    tracks                     = cms.InputTag("generalTracksLowPt"),
    trajectoryTrackAssociation = cms.InputTag("generalTracksLowPt")
)
process.trackingGlobalReco.replace(process.dedxTruncated40,process.dedxTruncated40LowPt)
process.trackingGlobalReco.replace(process.dedxHarmonic2,process.dedxHarmonic2LowPt)
process.trackingGlobalReco.replace(process.dedxDiscrimASmi,process.dedxDiscrimASmiLowPt)

process.reTracking = cms.Sequence(
   process.siPixelRecHits *
   process.siStripMatchedRecHits *
   process.recopixelvertexing *
   process.trackingGlobalReco *
   process.offlinePrimaryVerticesLowPt *
   process.generalV0CandidatesLowPt
)

process.reTracking_step = cms.Path( process.eventFilter_HM * process.reTracking )

###############################################################################################

process.load("RiceHIG.Skim2013.ppanalysisSkimContentFull_cff")
process.output_HM = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('pPb_HM.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_HM_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD'),
      filterName = cms.untracked.string('pPb_HM'))
)

process.output_HM_step = cms.EndPath(process.output_HM)

process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.reTracking_step,
    process.v0rereco_step,
    process.output_HM_step
)
