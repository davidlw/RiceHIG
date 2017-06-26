import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1006.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1007.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1008.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1009.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1010.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1011.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1012.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1013.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1014.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1015.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1016.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1017.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1018.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1019.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1020.root',
'/store/user/davidlw/HighMultiplicity/RecoSkim2015_2015DLowPU_ReTracking_v4/151103_083952/0001/pPb_HM_1021.root'
                )
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana = cms.Path(process.hltHM105135PP13TeV85On*process.corr_ana_pp)
process.corr_ana_pp.nmin = cms.int32(120)
process.corr_ana_pp.nmax = cms.int32(121)
process.corr_ana_pp.pttrgmin = cms.vdouble(0.5)
process.corr_ana_pp.pttrgmax = cms.vdouble(5.0)
process.corr_ana_pp.ptassmin = cms.vdouble(0.5)
process.corr_ana_pp.ptassmax = cms.vdouble(5.0)
