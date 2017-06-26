import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HIMinBiasUPC/PR2011_MBUCC_TRKANASKIM_official_v1/71a7d203fff2b3f389673e6fdd587ee0/hiGoodColl_1023_1_S52.root'
#'root://xrootd.unl.edu//store/user/appeltel/HIMinBiasUPC/pixelTrackReco_devel_v0/a236e4501225ae15b3601563d612abb5/pixeltrackreco_6_1_qSR.root'
#'file:/mnt/hadoop/cms/store/user/davidlw/JetHT/PP2012_FlowCorr_Jet400_v1/8db2b1c671424ba59874aa53380c8144/pPb_HM_53_1_t5X.root'
#'file:/mnt/hadoop/cms/store/user/davidlw/Hijing_PPb502_MinimumBias/RecoSkim_batch4_v1/84cb8c951385c1f95541c031462cec6b/pPb_MB_22_1_zGV.root'
'/store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_107.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.chasymdihadroncorrelation_cff")
process.load("RiceHIG.V0Analysis.v0selector_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.corr_ana_PbPb_pos = process.corr_ana_PbPb.clone(
  TriggerID = cms.string('TrackP'),
  AssociateID = cms.string('TrackP')
)
process.corr_ana_PbPb_neg = process.corr_ana_PbPb.clone(
  TriggerID = cms.string('TrackM'),
  AssociateID = cms.string('TrackM')
)
process.ana_pos = cms.Path(process.corr_ana_PbPb_pos)
process.ana_neg = cms.Path(process.corr_ana_PbPb_neg)

process.corr_ana_PbPb_neg.nmin = cms.int32(185)
process.corr_ana_PbPb_neg.nmax = cms.int32(220)
process.corr_ana_PbPb_pos.nmin = cms.int32(185)
process.corr_ana_PbPb_pos.nmax = cms.int32(220)
#process.corr_ana_PbPb_neg.IsCorr = cms.bool(False)
#process.corr_ana_PbPb_pos.IsCorr = cms.bool(False)
