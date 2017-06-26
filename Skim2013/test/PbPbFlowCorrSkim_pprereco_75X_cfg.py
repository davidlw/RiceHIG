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
#'/store/user/davidlw/step3pp_FILTER_RAW2DIGI_L1Reco_RECO_jb0.root'
'/store/hidata/HIRun2015/HIMinimumBias5/AOD/02May2016-v1/10000/00E8A45B-2622-E611-84A9-90B11C443B9C.root'
)
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(200))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = '75X_dataRun2_PromptHI_v3'

# =============== Import Sequences =====================
#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIL1Centralityext30100MinimumumBiasHF*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)
process.primaryVertexFilter.src = cms.InputTag("offlinePrimaryVertices")

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.evtsel_filter = cms.Sequence(process.hltHIMB * process.hfCoincFilter3 * process.primaryVertexFilter)
process.eventFilter_HM_step = cms.Path( process.evtsel_filter )

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
    xiVtxSignificance3DCut = cms.double(3.0),
    xiVtxSignificance2DCut = cms.double(3.0),
    vtxSignificance2DCut = cms.double(3.0),
    vtxSignificance3DCut = cms.double(3.0),

    collinearityCut = cms.double(0.999),

    innerHitPosCut = cms.double(-1)
)
process.v0rereco_step = cms.Path( process.evtsel_filter * process.generalV0CandidatesNew )

###############################################################################################

process.load("RiceHIG.Skim2013.ppanalysisSkimContentFull_cff")
process.output_HM = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('PbPb_MB.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_HM_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD'),
      filterName = cms.untracked.string('PbPb_MB'))
)
#process.output_HM.outputCommands.extend(cms.untracked.vstring('drop *','keep *_generalV0CandidatesNew_Kshort_*','keep *_generalV0CandidatesNew_Lambda_*','keep *_towerMaker_*_*'))

process.output_HM_step = cms.EndPath(process.output_HM)

process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.v0rereco_step,
    process.output_HM_step
)
