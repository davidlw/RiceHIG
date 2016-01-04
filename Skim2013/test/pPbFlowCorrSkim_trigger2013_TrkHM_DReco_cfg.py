import FWCore.ParameterSet.Config as cms
process = cms.Process("D0RECO")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('RecoHI.HiCentralityAlgos.pACentrality_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.MessageLogger.cerr.FwkReport.reportEvery = 200

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
'/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18/28b2b9cce04ec3f20baeb96fbd2295a8/pPb_HM_1618_2_sB4.root'
),
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR_P_V43F::All'

# =============== Import Sequences =====================

########## V0 candidate rereco ###############################################################
process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    tkNhitsCut = cms.int32(0),
    tkChi2Cut = cms.double(1000.0),
    tkPtCut = cms.double(0.5),
    tkDCACut = cms.double(0.5),
    dauTransImpactSigCut = cms.double(0.0),
    dauLongImpactSigCut = cms.double(0.0),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(0.0),
    mPiPiCutMax = cms.double(2.2),
    mPiPiCutMin = cms.double(0.8),
    innerHitPosCut = cms.double(-1),

    d0MassCut = cms.double(0.2),

    selectD0s = cms.bool(True),
    selectLambdaCs = cms.bool(False),
    selectKshorts = cms.bool(False),
    selectLambdas = cms.bool(False),
    selectXis = cms.bool(False),
    selectOmegas = cms.bool(False)
)
process.v0rereco_step = cms.Path( process.generalV0CandidatesNew )

###############################################################################################

process.load("RiceHIG.Skim2013.ppanalysisSkimContentFull_cff")
process.output_HM = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('pPb_HM.root'),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD'))
)
process.output_HM.outputCommands.extend(['drop *'])
process.output_HM.outputCommands.extend(['keep *_generalV0CandidatesNew_D0_D0RECO'])

process.output_HM_step = cms.EndPath(process.output_HM)

process.schedule = cms.Schedule(
    process.v0rereco_step,
    process.output_HM_step
)
