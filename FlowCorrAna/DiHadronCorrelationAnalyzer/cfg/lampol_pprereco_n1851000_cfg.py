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
#'file:/mnt/hadoop/cms/store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v6/ccf03100d177f42de0f9cdc7627799d3/pPb_HM_2654_1_Kdg.root'
#'/store/hidata/HIRun2015/HIMinimumBias5/AOD/02May2016-v1/10000/00E8A45B-2622-E611-84A9-90B11C443B9C.root'
#'/store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_900.root',
#'/store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_901.root',
#'/store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_902.root',
#'/store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_903.root',
#'/store/user/davidlw/HIMinimumBias5/RecoSkim2015_pprereco_v5/160727_021048/0000/PbPb_MB_904.root',
#'/store/user/gsfs/Hydjet_Quenched_MinBias_5020GeV_750/Hydjet_30_100_w_pp_RECO_20160724/160725_221957/0000/step3_FILTER_RAW2DIGI_L1Reco_RECO_102.root'
'/store/user/davidlw/Hydjet_Quenched_MinBias_5020GeV_750/RecoSkim2015_pprereco_v5/160805_143600/0000/PbPb_MB_10.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.lampoldata_cfi")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('lampol.root')
                                   )

process.load("RiceHIG.V0Analysis.v0selector_cff")
process.selectV0CandidatesNewlambda.v0CollName = cms.string("generalV0CandidatesNew")
#process.selectV0CandidatesNewlambda.dxySigCut1= cms.double(2.0)
#process.selectV0CandidatesNewlambda.dxySigCut2= cms.double(2.0)
#process.selectV0CandidatesNewlambda.dzSigCut1= cms.double(2.0)
#process.selectV0CandidatesNewlambda.dzSigCut2= cms.double(2.0)
#process.selectV0CandidatesNewlambda.cosThetaCut = cms.double(0.999)
#process.selectV0CandidatesNewlambda.decayLSigCut = cms.double(5.0)

process.ana = cms.Path(process.selectV0CandidatesNewlambda*process.corr_ana)
#process.ana = cms.Path(process.corr_ana)
#process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.nmin = cms.int32(150)
#process.corr_ana.nmax = cms.int32(10000)
process.corr_ana.V0CandidateCollection = cms.string('selectV0CandidatesNewlambda')
#process.corr_ana.V0CandidateCollection = cms.string('generalV0Candidates')
#process.corr_ana.pttrgmin = cms.vdouble(0.8,0.8,1.5,2.5)
#process.corr_ana.pttrgmax = cms.vdouble(10.0,1.5,2.5,10.0)
#process.corr_ana.massmean_trg = cms.vdouble(1.116,1.116,1.116,1.116)
#process.corr_ana.masswidth_trg = cms.vdouble(0.003,0.003,0.003,0.003)
process.corr_ana.pttrgmin = cms.vdouble(0.8)
process.corr_ana.pttrgmax = cms.vdouble(10.0)
process.corr_ana.massmean_trg = cms.vdouble(1.116)
process.corr_ana.masswidth_trg = cms.vdouble(0.003)
#process.corr_ana.IsV0SignalTrg = cms.bool(False)
#process.corr_ana.IsV0BkgTrg = cms.bool(True)
