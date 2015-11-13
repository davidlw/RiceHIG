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
#'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_v15/702fa69daea9da948fe2472b4d29b5b5/pPb_HM_282_1_izm.root'
#'file:/mnt/hadoop/cms/store/user/davidlw/MinBias_TuneMonash13_13TeV-pythia8/RecoSkim_batch4_v1/00b3bbd68a41a1bc2b98cf5da8508e09/pPb_HM_35_1_qTo.root'
#'file:/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_7_4_2/src/RiceHIG/Skim2013/test/pPb_HM.root'
#'/store/user/mguilbau/ZeroBias4/ZeroBias4_RecoSkim2015_v1/150717_161343/0000/pp_MB_lowPU_5.root'
#'/store/user/davidlw/HighMultiplicity85/RecoSkim2015_2015C_NoV0_v2/150831_155112/0000/pPb_HM_93.root'
'/store/data/Run2015C/L1MinimumBiasHF5/RECO/PromptReco-v1/000/255/031/00000/0003CB33-144E-E511-83A4-02163E0141FA.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana = cms.Path(process.hltMBPP13TeV*process.corr_ana)
#process.ana = cms.Path(process.corr_ana)
process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.nvtxmax = cms.int32(1)
