import FWCore.ParameterSet.Config as cms
process = cms.Process("ANASKIM")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.MessageLogger.cerr.FwkReport.reportEvery = 200

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
#'/store/data/Run2015B/ZeroBias8/AOD/PromptReco-v1/000/251/025/00000/56545168-3E26-E511-A65E-02163E01272F.root'
#'/store/data/Run2015B/ZeroBias8/RECO/PromptReco-v1/000/251/025/00000/0A9803D6-3F26-E511-8B95-02163E01340A.root'
#'/store/express/Run2015B/ExpressPhysics/FEVT/Express-v1/000/251/244/00000/1ADB8189-B625-E511-B858-02163E011BB9.root'
#'/store/data/Run2015B/HighMultiplicity/RECO/PromptReco-v1/000/251/721/00000/00BA646E-D82B-E511-A218-02163E01439E.root'
#'/store/data/Run2015B/HighMultiplicity85/RECO/05Aug2015-v1/40000/3C47E215-203C-E511-A5B9-002618943972.root'
#'/store/data/Run2015D/HighMultiplicity/RECO/PromptReco-v4/000/259/431/00000/04E7F9FE-B579-E511-8594-02163E0144CC.root'
'/store/data/Run2015D/L1MinimumBiasHF1/RECO/PromptReco-v4/000/259/431/00000/08DA5C59-BB79-E511-B16C-02163E014678.root'
)
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.GlobalTag.globaltag = 'GR_P_V56'
process.GlobalTag.globaltag = '74X_dataRun2_Prompt_v2'

# =============== Import Sequences =====================
#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHM.HLTPaths = ['HLT_L1MinimumBiasHF1OR_part*_v*']
process.hltHM.andOr = cms.bool(True)
process.hltHM.throw = cms.bool(False)

process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
#    cut = cms.string("!isFake && abs(z) <= 1 && position.Rho <= 2 && tracksSize >= 5"),
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
    process.hltHM *
    process.PAcollisionEventSelection
)

process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

#process.dEdx_step = cms.Path( process.eventFilter_HM * process.produceEnergyLoss )

########## V0 candidate rereco ###############################################################
process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    selectD0s = cms.bool(False),
    selectLambdaCs = cms.bool(False),
#    selectXis = cms.bool(False),
#    selectOmegas = cms.bool(False),

    tkNhitsCut = cms.int32(3),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(1.0),
    dauLongImpactSigCut = cms.double(1.0),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(4.0),

    collinearityCut = cms.double(0.95)
)
process.v0rereco_step = cms.Path( process.eventFilter_HM * process.generalV0CandidatesNew )

########## ReTracking #########################################################################
process.globalreco1 = cms.Sequence(process.offlineBeamSpot*
                          process.MeasurementTrackerEventPreSplitting* # unclear where to put this
                          process.siPixelClusterShapeCachePreSplitting* # unclear where to put this
#                          process.standalonemuontracking*
                          process.trackingGlobalReco*
                          process.vertexreco)

#process.iterTracking.remove(process.muonSeededStep)

process.reconstruction1 = cms.Sequence(process.localreco*process.globalreco1)
modulesToRemove = list() # copy does not work well
noTrackingAndDependent = list()
noTrackingAndDependent.append(process.siPixelClustersPreSplitting)
noTrackingAndDependent.append(process.siStripZeroSuppression)
noTrackingAndDependent.append(process.siStripClusters)
noTrackingAndDependent.append(process.initialStepSeedLayersPreSplitting)
noTrackingAndDependent.append(process.initialStepSeedsPreSplitting)
noTrackingAndDependent.append(process.initialStepTrackCandidatesPreSplitting)
noTrackingAndDependent.append(process.initialStepTracksPreSplitting)
noTrackingAndDependent.append(process.firstStepPrimaryVerticesPreSplitting)
noTrackingAndDependent.append(process.initialStepTrackRefsForJetsPreSplitting)
noTrackingAndDependent.append(process.caloTowerForTrkPreSplitting)
noTrackingAndDependent.append(process.ak4CaloJetsForTrkPreSplitting)
noTrackingAndDependent.append(process.jetsForCoreTrackingPreSplitting)
noTrackingAndDependent.append(process.siPixelClusterShapeCachePreSplitting)
noTrackingAndDependent.append(process.siPixelClusters)
noTrackingAndDependent.append(process.clusterSummaryProducer)
noTrackingAndDependent.append(process.siPixelRecHitsPreSplitting)
noTrackingAndDependent.append(process.MeasurementTrackerEventPreSplitting)
noTrackingAndDependent.append(process.dedxHitInfo)
noTrackingAndDependent.append(process.trackExtrapolator)
noTrackingAndDependent.append(process.convClusters)
noTrackingAndDependent.append(process.convLayerPairs)
noTrackingAndDependent.append(process.photonConvTrajSeedFromSingleLeg)
noTrackingAndDependent.append(process.convTrackCandidates)
noTrackingAndDependent.append(process.convStepTracks)
noTrackingAndDependent.append(process.convStepSelector)
noTrackingAndDependent.append(process.conversionStepTracks)
noTrackingAndDependent.append(process.initialStepSeedClusterMask)
noTrackingAndDependent.append(process.pixelPairStepSeedClusterMask)
noTrackingAndDependent.append(process.mixedTripletStepSeedClusterMask)
noTrackingAndDependent.append(process.pixelLessStepSeedClusterMask)
noTrackingAndDependent.append(process.tripletElectronSeedLayers)
noTrackingAndDependent.append(process.tripletElectronSeeds)
noTrackingAndDependent.append(process.tripletElectronClusterMask)
noTrackingAndDependent.append(process.pixelPairElectronSeedLayers)
noTrackingAndDependent.append(process.pixelPairElectronSeeds)
noTrackingAndDependent.append(process.stripPairElectronSeedLayers)
noTrackingAndDependent.append(process.stripPairElectronSeeds)
noTrackingAndDependent.append(process.newCombinedSeeds)
#noTrackingAndDependent.append(process.unsortedOfflinePrimaryVertices)
#noTrackingAndDependent.append(process.trackWithVertexRefSelectorBeforeSorting)
#noTrackingAndDependent.append(process.trackRefsForJetsBeforeSorting)
#noTrackingAndDependent.append(process.offlinePrimaryVerticesWithBS)
#noTrackingAndDependent.append(process.inclusiveVertexFinder)
#noTrackingAndDependent.append(process.vertexMerger)
#noTrackingAndDependent.append(process.trackVertexArbitrator)
#noTrackingAndDependent.append(process.inclusiveSecondaryVertices)

modulesToRemove.append(process.dt1DRecHits)
modulesToRemove.append(process.dt1DCosmicRecHits)
modulesToRemove.append(process.csc2DRecHits)
modulesToRemove.append(process.rpcRecHits)
modulesToRemove.append(process.ecalMultiFitUncalibRecHit)
modulesToRemove.append(process.ecalDetIdToBeRecovered)
modulesToRemove.append(process.ecalRecHit)
modulesToRemove.append(process.ecalCompactTrigPrim)
modulesToRemove.append(process.ecalTPSkim)
modulesToRemove.append(process.ecalPreshowerRecHit)
modulesToRemove.append(process.selectDigi)
modulesToRemove.append(process.hbheprereco)
modulesToRemove.append(process.hbhereco)
modulesToRemove.append(process.hfreco)
modulesToRemove.append(process.horeco)
modulesToRemove.append(process.hcalnoise)
modulesToRemove.append(process.zdcreco)
modulesToRemove.append(process.castorreco)
process.reconstruction_fromRECO1 = process.reconstruction1.copyAndExclude(modulesToRemove+noTrackingAndDependent)

process.generalTracksLowPt = process.generalTracks.clone()
#process.offlinePrimaryVerticesLowPt = process.offlinePrimaryVertices.clone()
#process.generalV0CandidatesLowPt = process.generalV0Candidates.clone()
#process.iterTracking.replace(process.generalTracks,process.generalTracksLowPt)
process.offlinePrimaryVerticesLowPt = process.offlinePrimaryVertices.clone( TrackLabel = cms.InputTag("generalTracksLowPt") )
process.generalV0CandidatesLowPt = process.generalV0CandidatesNew.clone(
  trackRecoAlgorithm = cms.InputTag('generalTracksLowPt'),
  vertexRecoAlgorithm = cms.InputTag('offlinePrimaryVerticesLowPt')
)

process.reconstruction_fromRECO1.replace(process.generalTracks,process.generalTracksLowPt)
process.reconstruction_fromRECO1.replace(process.offlinePrimaryVertices,process.offlinePrimaryVerticesLowPt)
process.reconstruction_fromRECO1.replace(process.generalV0Candidates,process.generalV0CandidatesLowPt)

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
process.reconstruction_fromRECO1.replace(process.dedxTruncated40,process.dedxTruncated40LowPt)
process.reconstruction_fromRECO1.replace(process.dedxHarmonic2,process.dedxHarmonic2LowPt)
process.reconstruction_fromRECO1.replace(process.dedxDiscrimASmi,process.dedxDiscrimASmiLowPt)
#process.trackingGlobalReco.replace(process.dedxTruncated40,process.dedxTruncated40LowPt)
#process.trackingGlobalReco.replace(process.dedxHarmonic2,process.dedxHarmonic2LowPt)
#process.trackingGlobalReco.replace(process.dedxDiscrimASmi,process.dedxDiscrimASmiLowPt)

#process.reTracking = cms.Sequence(
#   process.siPixelClustersPreSplitting *
#   process.siPixelRecHitsPreSplitting *
#   process.siStripMatchedRecHits *
#   process.pixelTracks *
#   process.ckftracks *
#   process.recopixelvertexing *
#   process.trackingGlobalReco *
#   process.offlinePrimaryVerticesLowPt *
#   process.generalV0CandidatesLowPt
#)

#process.reTracking_step = cms.Path( process.eventFilter_HM * process.reTracking )

process.reTracking_step = cms.Path( process.eventFilter_HM * process.reconstruction_fromRECO1 )
###############################################################################################

process.load("RiceHIG.Skim2013.ppanalysisSkimContentSlim_cff")
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
#    process.dEdx_step,
    process.v0rereco_step,
    process.reTracking_step,
    process.output_HM_step
)
