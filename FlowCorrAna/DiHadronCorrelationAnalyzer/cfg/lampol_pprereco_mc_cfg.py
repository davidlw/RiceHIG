import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_10.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_11.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_12.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_13.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_14.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_15.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_16.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_17.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_18.root',
'/store/user/davidlw/EPOS_PbPb5TeV/Cent30100_DIGI-RECO_v1/160629_095734/0000/step2_FILTER_DIGI_L1_DIGI2RAW_RAW2DIGI_L1Reco_RECO_19.root',
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.lampoldata_cfi")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
#process.hltHIMB.andOr = cms.bool(True)
#process.hltHIMB.throw = cms.bool(False)

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

#process.ana = cms.Path(process.selectV0CandidatesNewlambda*process.corr_ana)
process.ana = cms.Path(process.corr_ana)
#process.corr_ana.IsCorr = cms.bool(False)
#process.corr_ana.nmin = cms.int32(150)
#process.corr_ana.nmax = cms.int32(10000)
#process.corr_ana.V0CandidateCollection = cms.string('selectV0CandidatesNewlambda')
process.corr_ana.V0CandidateCollection = cms.string('generalV0Candidates')
process.corr_ana.pttrgmin = cms.vdouble(0.8,1.5,2.5)
process.corr_ana.pttrgmax = cms.vdouble(1.5,2.5,10)
process.corr_ana.massmean_trg = cms.vdouble(1.116,1.116,1.116)
process.corr_ana.masswidth_trg = cms.vdouble(0.003,0.003,0.003)
#process.corr_ana.IsV0SignalTrg = cms.bool(False)
#process.corr_ana.IsV0BkgTrg = cms.bool(True)
