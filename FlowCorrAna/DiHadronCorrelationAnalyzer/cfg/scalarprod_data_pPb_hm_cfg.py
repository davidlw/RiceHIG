import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_PAFullTracks_Multiplicity185_v*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/hidata/PARun2016C/PAHighMultiplicity7/AOD/PromptReco-v1/000/285/530/00000/001FD395-CFB0-E611-B11B-02163E011AB6.root'
#'/store/user/davidlw/PAHighMultiplicity7/RecoSkim2016_pPb_HM280_v4/170103_123148/0000/pPb_HM_127.root'
'root://cmsxrootd.fnal.gov///store/hidata/PARun2016C/PAHighMultiplicity7/AOD/PromptReco-v1/000/285/480/00000/5E0F96D9-08AF-E611-9C83-FA163E0C8993.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.scalarprodnew_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('scalarprod.root')
                                   )

process.scalarprod_ana_hm_hfp.nmin = cms.int32(185)
process.scalarprod_ana_hm_hfp.nmax = cms.int32(250)
process.scalarprod_ana_hm_hfm.nmin = cms.int32(185)
process.scalarprod_ana_hm_hfm.nmax = cms.int32(250)
process.scalarprod_ana_hfphfm.nmin = cms.int32(185)
process.scalarprod_ana_hfphfm.nmax = cms.int32(250)

process.ana_hm_hfp = cms.Path(process.scalarprod_ana_hm_hfp)
process.ana_hm_hfm = cms.Path(process.scalarprod_ana_hm_hfm)
process.ana_hfphfm = cms.Path(process.scalarprod_ana_hfphfm)
