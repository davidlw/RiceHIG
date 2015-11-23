import FWCore.ParameterSet.Config as cms

process = cms.Process("V0Val")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### standard includes
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.HiGenCommon.VtxSmearedRealisticPPbBoost8TeVCollision_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load("Configuration.StandardSequences.Digi_cff")
process.load("Configuration.StandardSequences.DigiToRaw_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("SimGeneral.MixingModule.mixNoPU_cfi")
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'STARTHI53_V17::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/EPOS_GEN-SIM_1M_batch7/RecoSkim_ReTracking_v4/5cde49c8740ff28f897f533d05a99dbc/pPb_MB_32_1_bGV.root'
                ),
secondaryFileNames = cms.untracked.vstring(
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3014_1_UGv.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3015_1_zW0.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3016_1_phR.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3017_1_J9N.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3018_1_PSU.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3019_1_cZK.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3021_1_j2O.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3022_1_Vyg.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3023_1_aBP.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3024_1_2Up.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3025_1_AYM.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3026_1_ZQI.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3027_1_LFO.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3028_1_C5M.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3029_1_zVD.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3030_1_oQ2.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3031_1_UYG.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3032_1_WvG.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3033_1_4Nk.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3034_1_GqS.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3035_1_YvA.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3036_1_c3n.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3037_1_y0k.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3038_1_Eg3.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3039_1_Pzl.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3040_1_4jI.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3041_1_4LT.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3042_1_qhU.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3043_1_QFu.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3044_1_uXd.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3045_1_vq8.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3046_1_lG8.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3047_1_6Wi.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3048_1_eBy.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3049_1_SRS.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3050_1_h1d.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3051_1_o5s.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3052_1_6C0.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3053_1_bxj.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3054_1_Msc.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3055_1_wNa.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3056_1_Crp.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3057_1_P0q.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3058_1_J5A.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3059_1_hNg.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3060_1_ln0.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3061_1_B3p.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3062_1_99I.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3063_1_nPR.root',
'/store/user/vzhukova/EPOS_GEN-SIM_1M_batch7/HIJING_RECO_1M_batch7/b7d33bba7673cdb1ee6f4983c0800c79/epos_reco_fix_3064_1_UhP.root'
)
)

### validation-specific includes
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByChi2_cfi")
process.load("RiceHIG.V0Analysis.v0selector_cff")
process.load("RiceHIG.V0Analysis.v0validator_cff")

#process.generalV0CandidatesNew = process.generalV0Candidates.clone (
#    tkNhitsCut = cms.int32(0),
#    tkChi2Cut = cms.double(7.0),
#    dauTransImpactSigCut = cms.double(0.0),
#    dauLongImpactSigCut = cms.double(0.0),
#    xiVtxSignificance3DCut = cms.double(0.0),
#    xiVtxSignificance2DCut = cms.double(0.0),
#    vtxSignificance2DCut = cms.double(0.0),
#    vtxSignificance3DCut = cms.double(4.0)
#)   

process.v0Validator.kShortCollection = cms.InputTag('selectV0CandidatesNewkshort:Kshort')
process.v0Validator.lambdaCollection = cms.InputTag('selectV0CandidatesNewlambda:Lambda')
#process.v0Validator.trackCollection = cms.InputTag('generalTracksLowPt')
process.v0Validator.isMatchByHitsOrChi2 = cms.bool(True)
process.v0Validator.isMergedTruth = cms.bool(True)

process.selectV0CandidatesNewlambda.v0CollName = cms.string("generalV0CandidatesNew")
process.selectV0CandidatesNewkshort.v0CollName = cms.string("generalV0CandidatesNew")
#process.selectV0CandidatesNewlambda.dxySigCut1 = cms.double(0.0)
#process.selectV0CandidatesNewlambda.dxySigCut2 = cms.double(0.0)
#process.selectV0CandidatesNewlambda.dzSigCut1 = cms.double(0.0)
#process.selectV0CandidatesNewlambda.dzSigCut2 = cms.double(0.0)
#process.selectV0CandidatesNewkshort.dxySigCut1 = cms.double(0.0)
#process.selectV0CandidatesNewkshort.dxySigCut2 = cms.double(0.0)
#process.selectV0CandidatesNewkshort.dzSigCut1 = cms.double(0.0)
#process.selectV0CandidatesNewkshort.dzSigCut2 = cms.double(0.0)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('v0validation.root')
                                   )
#process.TrackAssociatorByHits.Cut_RecoToSim = cms.double(0.5)
#process.TrackAssociatorByChi2ESProducer.chi2cut = cms.double(25.0)

process.v0validation = cms.Sequence(process.selectV0CandidatesNewlambda*process.selectV0CandidatesNewkshort*process.v0Validator)

process.p = cms.Path(process.v0validation)

process.schedule = cms.Schedule(process.p)
