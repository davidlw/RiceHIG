import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_ExpressHI_v2', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.hltHITrk12 = process.hltHIMB.clone()
process.hltHITrk12.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1','HLT_HIFullTrack12_L1MinimumBiasHF1_AND_v1'] # for allphysics
process.hltHITrk12.andOr = cms.bool(False)
process.hltHITrk12.throw = cms.bool(False)

process.hltHITrk18 = process.hltHIMB.clone()
process.hltHITrk18.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1','HLT_HIFullTrack18_L1MinimumBiasHF1_AND_v1'] # for allphysics
process.hltHITrk18.andOr = cms.bool(False)
process.hltHITrk18.throw = cms.bool(False)

process.hltHITrk24 = process.hltHIMB.clone()
process.hltHITrk24.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1','HLT_HIFullTrack24_v1'] # for allphysics
process.hltHITrk24.andOr = cms.bool(False)
process.hltHITrk24.throw = cms.bool(False)

process.hltHITrk34 = process.hltHIMB.clone()
process.hltHITrk34.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1','HLT_HIFullTrack34_v1'] # for allphysics
process.hltHITrk34.andOr = cms.bool(False)
process.hltHITrk34.throw = cms.bool(False)

process.hltHITrk45 = process.hltHIMB.clone()
process.hltHITrk45.HLTPaths = ['HLT_HIL1MinimumBiasHF1AND_v1','HLT_HIFullTrack45_v1'] # for allphysics
process.hltHITrk45.andOr = cms.bool(False)
process.hltHITrk45.throw = cms.bool(False)

# ================ L1 Filters =====================
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
from L1Trigger.Skimmer.l1Filter_cfi import l1Filter
process.l1trk12 = l1Filter.clone(
    algorithms = ["L1_SingleTrack12_BptxAND"]
    )
process.l1trk16 = l1Filter.clone(
    algorithms = ["L1_SingleTrack16_BptxAND"]
    )
process.l1trk20 = l1Filter.clone(
    algorithms = ["L1_SingleTrack20_BptxAND"]
    )
process.l1trk24 = l1Filter.clone(
    algorithms = ["L1_SingleTrack24_BptxAND"]
    )
process.l1trk28 = l1Filter.clone(
    algorithms = ["L1_SingleTrack28_BptxAND"]
    )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
 '/store/user/davidlw/HIMinBias2015/recoExpress_0.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_1.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_10.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_100.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_101.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_102.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_103.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_105.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_106.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_107.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_108.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_109.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_11.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_110.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_111.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_112.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_113.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_114.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_115.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_116.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_117.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_118.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_119.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_12.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_120.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_121.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_122.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_123.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_124.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_125.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_126.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_127.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_128.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_129.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_13.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_130.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_131.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_132.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_133.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_134.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_135.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_136.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_137.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_138.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_139.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_14.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_140.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_141.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_142.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_143.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_144.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_145.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_146.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_147.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_148.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_149.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_15.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_150.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_151.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_152.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_153.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_154.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_155.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_156.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_157.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_158.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_159.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_16.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_160.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_161.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_162.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_163.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_164.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_165.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_166.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_167.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_168.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_169.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_17.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_170.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_171.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_172.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_173.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_174.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_175.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_176.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_177.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_178.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_179.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_18.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_180.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_181.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_182.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_183.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_184.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_185.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_186.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_187.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_188.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_189.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_19.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_190.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_191.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_192.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_193.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_194.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_195.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_196.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_197.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_198.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_199.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_2.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_20.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_200.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_201.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_202.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_203.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_204.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_205.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_206.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_207.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_208.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_209.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_21.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_210.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_211.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_212.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_213.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_214.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_215.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_216.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_217.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_218.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_219.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_22.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_220.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_221.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_222.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_223.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_224.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_225.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_226.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_227.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_228.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_229.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_23.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_230.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_231.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_232.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_233.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_234.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_236.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_237.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_238.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_239.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_24.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_240.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_241.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_242.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_243.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_244.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_245.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_246.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_247.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_248.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_249.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_25.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_250.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_251.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_252.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_253.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_254.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_255.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_256.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_257.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_258.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_26.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_27.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_28.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_29.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_3.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_30.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_31.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_32.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_33.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_34.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_35.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_36.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_37.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_38.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_39.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_4.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_40.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_41.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_42.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_43.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_44.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_45.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_46.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_47.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_48.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_49.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_5.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_50.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_51.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_52.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_53.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_54.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_55.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_56.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_57.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_58.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_59.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_6.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_60.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_61.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_62.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_63.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_64.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_65.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_66.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_67.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_68.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_69.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_7.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_9.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_90.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_91.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_92.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_93.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_94.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_95.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_96.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_97.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_98.root',
 '/store/user/davidlw/HIMinBias2015/recoExpress_99.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation_pt005.root')
                                   )
process.corr_ana_HI.IsCorr = cms.bool(False)
process.corr_ana_HI.etatrgmin = cms.double(-1.0)
process.corr_ana_HI.etatrgmax = cms.double(1.0)
process.corr_ana_HI.etaassmin = cms.double(-1.0)
process.corr_ana_HI.etaassmax = cms.double(1.0)

process.corr_ana_HI_trk12 = process.corr_ana_HI.clone()
process.corr_ana_HI_trk18 = process.corr_ana_HI.clone()
process.corr_ana_HI_trk24 = process.corr_ana_HI.clone()
process.corr_ana_HI_trk34 = process.corr_ana_HI.clone()
process.corr_ana_HI_trk45 = process.corr_ana_HI.clone()
process.corr_ana_HI_l1trk12 = process.corr_ana_HI.clone()
process.corr_ana_HI_l1trk16 = process.corr_ana_HI.clone()
process.corr_ana_HI_l1trk20 = process.corr_ana_HI.clone()
process.corr_ana_HI_l1trk24 = process.corr_ana_HI.clone()
process.corr_ana_HI_l1trk28 = process.corr_ana_HI.clone()

process.ana_mb = cms.Path(process.hltHIMB*process.corr_ana_HI)
process.ana_12 = cms.Path(process.hltHITrk12*process.corr_ana_HI_trk12)
process.ana_18 = cms.Path(process.hltHITrk18*process.corr_ana_HI_trk18)
process.ana_24 = cms.Path(process.hltHITrk24*process.corr_ana_HI_trk24)
process.ana_34 = cms.Path(process.hltHITrk34*process.corr_ana_HI_trk34)
process.ana_45 = cms.Path(process.hltHITrk45*process.corr_ana_HI_trk45)

process.ana_l112 = cms.Path(process.l1trk12*process.hltHIMB*process.corr_ana_HI_l1trk12)
process.ana_l116 = cms.Path(process.l1trk16*process.hltHIMB*process.corr_ana_HI_l1trk16)
process.ana_l120 = cms.Path(process.l1trk20*process.hltHIMB*process.corr_ana_HI_l1trk20)
process.ana_l124 = cms.Path(process.l1trk24*process.hltHIMB*process.corr_ana_HI_l1trk24)
process.ana_l128 = cms.Path(process.l1trk28*process.hltHIMB*process.corr_ana_HI_l1trk28)
