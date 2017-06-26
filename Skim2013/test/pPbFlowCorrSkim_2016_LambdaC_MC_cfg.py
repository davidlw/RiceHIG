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
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_100.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_101.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_102.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_103.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_104.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_105.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_106.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_107.root',
#'/store/user/zhchen/Pythia8_8160GeV_LambdaC_LambdaPion/Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL/170530_210458/0000/Pythia8_8160GeV_LambdaC_LambdaPion_step2_108.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_10.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_11.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_12.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_13.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_14.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_15.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_16.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_17.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_18.root',
'/store/user/zhchen/Pythia8_8160GeV_LambdaC_KsProton/Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL/170530_205915/0000/Pythia8_8160GeV_LambdaC_KsProton_step2_19.root',
)
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = '80X_mcRun2_pA_v4'

# =============== Import Sequences =====================
#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHM.HLTPaths = ['HLT_PAFullTracks_Multiplicity280_v*']
process.hltHM.HLTPaths = ['HLT_PAFullTracks_Multiplicity280_v*']
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
#    process.hltHM *
#    process.PAcollisionEventSelection
)

process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

#process.dEdx_step = cms.Path( process.eventFilter_HM * process.produceEnergyLoss )

########## V0 candidate rereco ###############################################################
process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    selectD0s = cms.bool(False),
    selectLambdaCToLamPis = cms.bool(False),
    selectXis = cms.bool(False),
    selectOmegas = cms.bool(False),

    tkNhitsCut = cms.int32(3),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(1.0),
    dauLongImpactSigCut = cms.double(1.0),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(2.5),

    collinearityCut = cms.double(0.997),

    innerHitPosCut = cms.double(-1)
)
process.v0rereco_step = cms.Path( process.eventFilter_HM * process.generalV0CandidatesNew )

########## Xi candidate rereco ###############################################################
process.generalCascadeCandidatesNew = process.generalV0Candidates.clone (
    selectD0s = cms.bool(False),
    selectLambdaCToLamPis = cms.bool(True),
#    selectLambdaCToKsPs = cms.bool(True),
    selectXis = cms.bool(False),
    selectOmegas = cms.bool(False),

    tkNhitsCut = cms.int32(3),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(1.0),
    dauLongImpactSigCut = cms.double(1.0),
    batDauTransImpactSigCut = cms.double(0.0),
    batDauLongImpactSigCut = cms.double(0.0),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(2.5),

    collinearityCut = cms.double(0.997),
    xiCollinearityCut = cms.double(0.0),

    innerHitPosCut = cms.double(-1)
)
process.cascaderereco_step = cms.Path( process.eventFilter_HM * process.generalCascadeCandidatesNew )

###############################################################################################

#process.load("RiceHIG.Skim2013.ppanalysisSkimContentFull_cff")
#process.load("RiceHIG.Skim2013.ppanalysisSkimContentSlim_cff")
process.load("RiceHIG.Skim2013.ppanalysisSkimContentV0_cff")
process.output_HM = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('pPb_HM.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_HM_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD')
#      filterName = cms.untracked.string('pPb_HM')
    )
)

process.output_HM_step = cms.EndPath(process.output_HM)

process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
#    process.dEdx_step,
    process.v0rereco_step,
    process.cascaderereco_step,
    process.output_HM_step
)
