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
process.load('RecoHI.HiCentralityAlgos.pACentrality_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
  '/store/user/wangj/Hijing_PbPb_MinimumBias_b13_cmssw5_3_14_batch1/HIJING_PbPb_MB_b13_cmssw5314_batch1/4992ddddd224bc007f7586b304bb3f11/20141023_Hijing_PbPb_MinimumBias_b13_cmssw5_3_14_batch1_1000_1_4r6.root'
)
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(50))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'STARTHI53_V17::All'

# =============== Import Sequences =====================
process.load('HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff')
process.load("UserCode.EnergyLossPID.EnergyLossProducer_cff")

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHM.HLTPaths = ['HLT_*PixelTracks_Multiplicity*_v*']
process.hltHM.HLTPaths = ['HLT_PAZeroBiasPixel_SingleTrack_v*']
process.hltHM.andOr = cms.bool(True)
process.hltHM.throw = cms.bool(False)

process.eventFilter_HM = cms.Sequence( 
#    process.hltHM *
    process.PAcollisionEventSelection *
    process.pileupVertexFilterCutGplus
)

process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

process.pACentrality_step = cms.Path( process.eventFilter_HM * process.pACentrality)
process.pACentrality.producePixelhits = False

process.dEdx_step = cms.Path( process.eventFilter_HM *
                              process.refitterForEnergyLoss *
                              process.energyLossProducer)

########## V0 candidate rereco ###############################################################

process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    tkNhitsCut = cms.int32(0),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(0.5),
    dauLongImpactSigCut = cms.double(0.5),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(0.0)
)   
process.v0rereco_step = cms.Path( process.eventFilter_HM * process.generalV0CandidatesNew )

process.load("RiceHIG.Skim2013.ppanalysisSkimContentFull_cff")
process.output_HM = cms.OutputModule("PoolOutputModule",
    outputCommands = process.analysisSkimContent.outputCommands,
    fileName = cms.untracked.string('pPb_MB.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_HM_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AOD'),
      filterName = cms.untracked.string('pPb_HM'))
)

process.output_HM_step = cms.EndPath(process.output_HM)

process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.pACentrality_step,
    process.v0rereco_step,
    process.output_HM_step
)
