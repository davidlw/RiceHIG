import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 500

### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = '75X_mcRun2_HeavyIon_v7'
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
#process.HeavyIonGlobalParameters = cms.PSet(
#    centralitySrc = cms.InputTag("hiCentrality"),
#    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
#)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIL1Centralityext30100MinimumumBiasHF*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.load('HeavyIonsAnalysis.EventAnalysis.HIClusterCompatibilityFilter_cfi')
#process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)
process.evtsel_filter = cms.Sequence(process.hltHIMB * process.hfCoincFilter3 * process.primaryVertexFilter)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/step3pp_FILTER_RAW2DIGI_L1Reco_RECO_jb0.root'
#'/store/user/davidlw/step3PbPb_RAW2DIGI_L1Reco_RECO_jb0.root'
#'file:step3pp_FILTER_RAW2DIGI_L1Reco_RECO.root'
'/store/relval/CMSSW_7_5_8_patch4/RelValRunHI2015Periph/AOD/PU_75X_dataRun2_PromptHI_v3_testHIPeriph_RelVal_hi2015Periph-v5/00000/06FA7A75-3C09-E611-B708-00266CF9C210.root'
                ),
#                                secondaryFileNames = cms.untracked.vstring('')
                          eventsToProcess = cms.untracked.VEventRange(
#  '263286:24468035-263286:24468035',
#  '263286:24473723-263286:24473723', 
#  '263286:24543830-263286:24543830',  
#  '263286:24472382-263286:24472382',                
#  '263286:24472352-263286:24472352',                
#  '263286:24472744-263286:24472744',                
#  '263286:24465975-263286:24465975',                
#  '263286:24469573-263286:24469573',                
),
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation_pp.root')
                                   )

#process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
#process.newCentralityBin = process.centralityBin.clone()

process.primaryVertexFilter.src = cms.InputTag("offlinePrimaryVertices")

process.corr_ana_pp.pttrgmin = cms.vdouble(1)
process.corr_ana_pp.pttrgmax = cms.vdouble(3)
process.corr_ana_pp.ptassmin = cms.vdouble(1)
process.corr_ana_pp.ptassmax = cms.vdouble(3)
#process.corr_ana_pp.pttrgmin = cms.vdouble(0.8)
#process.corr_ana_pp.pttrgmax = cms.vdouble(2.4)
#process.corr_ana_pp.etatrgmin = cms.double(3)
#process.corr_ana_pp.etatrgmax = cms.double(5.2)
#process.corr_ana_pp.TriggerID = cms.string('CaloTower')
#process.corr_ana_pp.IsTrgEtaCutAbs = cms.bool(True)
#process.corr_ana_pp.IsCorr = cms.bool(False)
#process.corr_ana_pp.IsDebug = cms.bool(True)

process.ana = cms.Path(process.evtsel_filter * process.corr_ana_pp)
#process.ana = cms.Path(process.evtsel_filter * process.corr_ana_HI)

#process.epetadeco_ana_HI.centralityBinLabel = cms.InputTag("newCentralityBin","HFtowers")
#process.epetadecomatrix_ana_HI.centmin = cms.int32(80)
#process.epetadecomatrix_ana_HI.centmax = cms.int32(100)
