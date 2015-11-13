import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v3/July09/run0pbPbv3x10more/energy2760GeVA/MinBias/CRAB3_AMPTstring_July2015_generation_run0pbPb2760GeVv3x10moreA/150709_175916/0000/ampt_StringMelting_pbPb2760GeV_GEN_103.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetadeco_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('epetadeco.root')
                                   )

process.ana_hfp = cms.Path(process.epetadeco_ana_HI_hfp)
process.ana_hfm = cms.Path(process.epetadeco_ana_HI_hfm)
process.epetadeco_ana_HI_hfp.rhomin = cms.double(0.0)
process.epetadeco_ana_HI_hfp.rhomax = cms.double(2.0)
process.epetadeco_ana_HI_hfm.rhomin = cms.double(0.0)
process.epetadeco_ana_HI_hfm.rhomax = cms.double(2.0)
process.epetadeco_ana_HI_hfp.etaassmin = cms.double(4.4)
process.epetadeco_ana_HI_hfp.etaassmax = cms.double(5.0)
process.epetadeco_ana_HI_hfp.pttrgmin = cms.vdouble(0.3)
process.epetadeco_ana_HI_hfm.etaassmin = cms.double(-5.0)
process.epetadeco_ana_HI_hfm.etaassmax = cms.double(-4.4)
process.epetadeco_ana_HI_hfm.pttrgmin = cms.vdouble(0.3)
process.epetadeco_ana_HI_hfp.IsVtxSel = cms.bool(False)
process.epetadeco_ana_HI_hfp.IsGenMult = cms.bool(True)
process.epetadeco_ana_HI_hfm.IsVtxSel = cms.bool(False)
process.epetadeco_ana_HI_hfm.IsGenMult = cms.bool(True)
process.epetadeco_ana_HI_hfp.TriggerID = cms.string('GenParticle')
process.epetadeco_ana_HI_hfp.AssociateID = cms.string('GenParticle')
process.epetadeco_ana_HI_hfm.TriggerID = cms.string('GenParticle')
process.epetadeco_ana_HI_hfm.AssociateID = cms.string('GenParticle')
