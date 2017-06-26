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
#'/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/216/00000/04214B66-30AC-E611-BFBC-FA163EBFF447.root'
 '/store/hidata/PARun2016B/PAMinimumBias1/AOD/PromptReco-v1/000/285/090/00000/DC56AAB2-5EAB-E611-A27A-FA163E251515.root'
)
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(3000))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v15'

# =============== Import Sequences =====================
#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHM.HLTPaths = ['HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_*_v*']
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

process.hfUPCFilterP = cms.Sequence(
    process.towersAboveThreshold *
    process.hfPosTowers *
    process.hfNegTowers *
    process.hfPosFilter *
    ~process.hfNegFilter)

process.hfUPCFilterN = cms.Sequence(
    process.towersAboveThreshold *
    process.hfPosTowers *
    process.hfNegTowers *
    ~process.hfPosFilter *
    process.hfNegFilter)

process.PAUpcP = cms.Sequence(
                                         process.hfUPCFilterP * 
                                         process.PAprimaryVertexFilter *
                                         process.NoScraping
                                         )

process.PAUpcN = cms.Sequence(
                                         process.hfUPCFilterN *
                                         process.PAprimaryVertexFilter *
                                         process.NoScraping
                                         )

process.eventFilter_P = cms.Sequence( 
    process.hltHM *
    process.PAUpcP
)

process.eventFilter_N = cms.Sequence( 
    process.hltHM *
    process.PAUpcN
)

process.eventFilter_P_step = cms.Path( process.eventFilter_P )
process.eventFilter_N_step = cms.Path( process.eventFilter_N )

#process.dEdx_step = cms.Path( process.eventFilter_HM * process.produceEnergyLoss )

########## V0 candidate rereco ###############################################################
process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    selectD0s = cms.bool(False),
    selectLambdaCs = cms.bool(False),
    selectXis = cms.bool(False),
    selectOmegas = cms.bool(False),

    tkNhitsCut = cms.int32(3),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(1.0),
    dauLongImpactSigCut = cms.double(1.0),
    xiVtxSignificance3DCut = cms.double(2.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(2.5),

    collinearityCut = cms.double(0.995),

    innerHitPosCut = cms.double(-1)
)
process.v0rereco_P_step = cms.Path( process.eventFilter_P * process.generalV0CandidatesNew )
process.v0rereco_N_step = cms.Path( process.eventFilter_N * process.generalV0CandidatesNew )

########## Xi candidate rereco ###############################################################
process.generalCascadeCandidatesNew = process.generalV0Candidates.clone (
    selectD0s = cms.bool(False),
    selectLambdaCs = cms.bool(False),
    selectXis = cms.bool(True),
    selectOmegas = cms.bool(True),

    tkNhitsCut = cms.int32(3),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(2.0),
    dauLongImpactSigCut = cms.double(2.0),
    batDauTransImpactSigCut = cms.double(4.0),
    batDauLongImpactSigCut = cms.double(4.0),
    xiVtxSignificance3DCut = cms.double(1.5),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(10),

    collinearityCut = cms.double(0.5),

    innerHitPosCut = cms.double(-1)
)
process.cascaderereco_P_step = cms.Path( process.eventFilter_P * process.generalCascadeCandidatesNew )
process.cascaderereco_N_step = cms.Path( process.eventFilter_N * process.generalCascadeCandidatesNew )

###############################################################################################

process.load("RiceHIG.Skim2013.ppanalysisSkimContentFull_cff")
#process.load("RiceHIG.Skim2013.ppanalysisSkimContentV0_cff")
process.output_P = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('pPb_P.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_P_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD')
    )
)
process.output_N = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('pPb_N.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_N_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD')
    )
)

process.output_P_step = cms.EndPath(process.output_P)
process.output_N_step = cms.EndPath(process.output_N)

process.schedule = cms.Schedule(
    process.eventFilter_P_step,
    process.eventFilter_N_step,
    process.v0rereco_P_step,
    process.v0rereco_N_step,
    process.cascaderereco_P_step,
    process.cascaderereco_N_step,
    process.output_P_step,
    process.output_N_step
)
