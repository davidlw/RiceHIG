import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("HFtowers"),
#       nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
        centralitySrc = cms.InputTag("hiCentrality")
        )

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.hltHIUCC = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIUCC.HLTPaths = ['HLT_HIUCC*_*'] # for allphysics
process.hltHIUCC.andOr = cms.bool(True)
process.hltHIUCC.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HIMinBiasUPC/PR2011_MBUCC_TRKANASKIM_official_v1/71a7d203fff2b3f389673e6fdd587ee0/hiGoodColl_1023_1_S52.root'
#'root://xrootd.unl.edu//store/user/appeltel/HIMinBiasUPC/pixelTrackReco_devel_v0/a236e4501225ae15b3601563d612abb5/pixeltrackreco_6_1_qSR.root'
'/store/user/davidlw/HIMinBiasUPC/Skim_rereco_MB_pixeltracks_final_v2/9c1b4b9b6b9ff3e493a474ba7d01bc76/hiMB_1766_1_1s8.root'
#'/store/user/davidlw/HIMinBiasUPC/Skim_rereco_generaltracks_MB_v1/9c1b4b9b6b9ff3e493a474ba7d01bc76/hiMB_1447_1_dKc.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetadecomatrix_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('epetadecomatrix.root')
                                   )

process.ana = cms.Path(process.hltHIMB*process.epetadecomatrix_ana_HI)
process.epetadecomatrix_ana_HI.centmin = cms.int32(0)
process.epetadecomatrix_ana_HI.centmax = cms.int32(10)
process.epetadecomatrix_ana_HI.EffFileName = cms.string('TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent05.root')
