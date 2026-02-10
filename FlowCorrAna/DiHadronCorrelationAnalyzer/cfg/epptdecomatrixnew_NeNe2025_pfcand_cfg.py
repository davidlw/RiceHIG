import FWCore.ParameterSet.Config as cms
process = cms.Process('ANASKIM')

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
'root://cmsxrootd.fnal.gov//store/hidata/NeNeRun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/272/00000/21b15b8b-2cbb-47dc-aeb6-d122a90e86df.root'
   )
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2025Nene_394269_394272_golden.json').getVLuminosityBlockRange()

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(50000))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '150X_dataRun3_Prompt_v1', '')

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_MinimumBiasHF_OR_BptxAND_v*'
#    'HLT_OxyZeroBias_v*'
]

# Add PbPb collision event selection
process.load('VertexCompositeAnalysis.VertexCompositeProducer.collisionEventSelection_cff')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.primaryVertexRecoveryForUPC_cfi')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.hffilterPF_cfi')
process.primaryVertexFilterHI = process.primaryVertexFilter.clone(src = "offlinePrimaryVertices")

process.load('HeavyIonsAnalysis.VertexAnalysis.pileupvertexfilter_cfi')
process.pileupvertexfilter.doOO = False
process.pileupvertexfilter.doNeNe = True

process.eventFilter_MB = cms.Sequence(
    process.hltFilter *
    process.primaryVertexFilterHI *
    process.pileupvertexfilter *
    process.phfCoincFilterPF2Th4
)
process.eventFilter_MB_step = cms.Path( process.eventFilter_MB )

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epptdecomatrixnew_cff")
# running on particle flow
#process.epptdecomatrixnew_ana_NeNe2025.TriggerID = cms.string('PackedPFHadron')
#process.epptdecomatrixnew_ana_NeNe2025.AssociateID = cms.string('PackedPFHadron')
process.epptdecomatrixnew_ana_NeNe2025.TriggerID = cms.string('Track')
process.epptdecomatrixnew_ana_NeNe2025.AssociateID = cms.string('Track')
process.epptdecomatrixnew_ana_NeNe2025.etatrgmin = cms.double(-2.4)
process.epptdecomatrixnew_ana_NeNe2025.etatrgmax = cms.double(2.4)
process.epptdecomatrixnew_ana_NeNe2025.etaassmin = cms.double(-2.4)
process.epptdecomatrixnew_ana_NeNe2025.etaassmax = cms.double(2.4)
process.epptdecomatrixnew_ana_NeNe2025.EffFileName = cms.string('EffFakVsNpixel3D_OO2025.root')
process.epptdecomatrixnew_ana_NeNe2025.FakFileName = cms.string('')
process.epptdecomatrixnew_ana_NeNe2025.EffHistName = cms.string('hCombFit3D')
process.epptdecomatrixnew_ana_NeNe2025.FakHistName = cms.string('')

#  //Official O table
#  //float binBoundaries[nCentTableBins+1]={0,0.717572,1.43514,2.15272,2.87029,3.58786,4.30543,5.023,5.74057,6.45815,7.17572,7.89329,8.61086,9.32843,10.046,10.5615,10.9358,11.3222,11.7114,12.1054,12.5071,12.9114,13.3242,13.7529,14.1895,14.6323,15.0788,15.5384,16.0017,16.4718,16.954,17.4529,17.965,18.4818,19.0081,19.5384,20.0798,20.6295,21.1904,21.7624,22.3333,22.9144,23.5082,24.108,24.7103,25.3327,25.9643,26.6021,27.2404,27.8889,28.551,29.2201,29.8838,30.5609,31.2582,31.959,32.6755,33.3996,34.127,34.8736,35.624,36.3835,37.1513,37.9462,38.7306,39.5312,40.3522,41.1784,41.9996,42.8382,43.7007,44.5735,45.4614,46.3438,47.2291,48.1364,49.0614,49.9993,50.9485,51.9135,52.8921,53.8808,54.8964,55.893,56.9136,57.9568,59.0177,60.0888,61.1833,62.2824,63.399,64.5337,65.6807,66.8337,68.0214,69.219,70.4243,71.651,72.9014,74.165,75.4546,76.7537,78.0703,79.4045,80.7569,82.1322,83.5298,84.9421,86.3744,87.8423,89.3304,90.8548,92.361,93.9159,95.4992,97.0799,98.6655,100.303,101.96,103.647,105.32,107.036,108.77,110.55,112.332,114.116,115.936,117.785,119.708,121.683,123.605,125.589,127.588,129.583,131.654,133.746,135.887,138.016,140.191,142.401,144.623,146.867,149.14,151.514,153.909,156.277,158.74,161.209,163.662,166.177,168.728,171.298,173.901,176.575,179.302,182.038,184.793,187.576,190.47,193.355,196.279,199.296,202.355,205.406,208.567,211.746,215.007,218.296,221.624,224.981,228.464,231.972,235.5,239.147,242.785,246.538,250.308,254.2,258.246,262.353,266.531,270.819,275.228,279.794,284.51,289.356,294.368,299.561,305.114,310.888,316.984,323.451,330.516,337.981,346.265,355.527,366.193,379.001,395.659,421.298,10000.0};

#  //Official Ne table
#  float binBoundaries[nCentTableBins+1]={0,0.796165,1.59233,2.3885,3.18466,3.98083,4.77699,5.57316,6.36932,7.16549,7.96165,8.75782,9.55398,10.3419,10.7459,11.1487,11.5557,11.9765,12.3958,12.8224,13.2575,13.7055,14.169,14.6409,15.131,15.6285,16.1319,16.6369,17.1592,17.6922,18.2389,18.7954,19.3801,19.9707,20.5712,21.181,21.795,22.4167,23.0559,23.688,24.3333,25.0232,25.6847,26.366,27.0754,27.7975,28.5169,29.2585,30.0149,30.7655,31.5565,32.3414,33.1446,33.9552,34.7554,35.5799,36.4235,37.2709,38.1186,38.9817,39.876,40.7619,41.6532,42.5763,43.5095,44.4509,45.441,46.4229,47.4092,48.4152,49.4382,50.4775,51.5114,52.5722,53.6107,54.7073,55.8258,56.9313,58.0735,59.2244,60.3905,61.5803,62.7754,63.9791,65.207,66.4599,67.7295,69 ,70.2905,71.5994,72.9536,74.3647,75.7388,77.1391,78.6117,80.0714,81.5776,83.0758,84.5599,86.1067,87.6935,89.2532,90.8864,92.5324,94.1888,95.8598,97.5337,99.3035,101.063,102.856,104.653,106.51,108.354,110.208,112.087,113.988,116.017,118.019,120.009,122.028,124.098,126.204,128.262,130.478,132.636,134.851,137.051,139.344,141.672,143.971,146.403,148.866,151.302,153.751,156.341,158.886,161.498,164.124,166.743,169.48,172.182,174.888,177.683,180.585,183.401,186.342,189.27,192.243,195.327,198.388,201.58,204.781,208.052,211.405,214.7,217.998,221.41,224.906,228.41,231.989,235.662,239.378,243.093,246.897,250.762,254.688,258.664,262.633,266.688,270.844,274.934,279.274,283.731,288.117,292.555,297.233,302.007,306.79,311.65,316.716,321.818,327.039,332.417,337.989,343.573,349.285,355.543,362.012,368.619,375.276,382.614,390.501,398.567,407.709,417.137,428.164,440.928,456.362,476.098,505.708,10000.0};
process.epptdecomatrixnew_ana_NeNe2025_cent01 = process.epptdecomatrixnew_ana_NeNe2025.clone()
process.epptdecomatrixnew_ana_NeNe2025_cent05 = process.epptdecomatrixnew_ana_NeNe2025.clone()
process.epptdecomatrixnew_ana_NeNe2025_cent510 = process.epptdecomatrixnew_ana_NeNe2025.clone()
process.epptdecomatrixnew_ana_NeNe2025_cent1030 = process.epptdecomatrixnew_ana_NeNe2025.clone()
process.epptdecomatrixnew_ana_NeNe2025_cent3050 = process.epptdecomatrixnew_ana_NeNe2025.clone()
process.epptdecomatrixnew_ana_NeNe2025_cent5070 = process.epptdecomatrixnew_ana_NeNe2025.clone()
process.epptdecomatrixnew_ana_NeNe2025_cent01.hfsummin = cms.double(476.098)
process.epptdecomatrixnew_ana_NeNe2025_cent01.hfsummax = cms.double(10000.0)
process.epptdecomatrixnew_ana_NeNe2025_cent05.hfsummin = cms.double(382.614)
process.epptdecomatrixnew_ana_NeNe2025_cent05.hfsummax = cms.double(10000.0)
process.epptdecomatrixnew_ana_NeNe2025_cent510.hfsummin = cms.double(321.818)
process.epptdecomatrixnew_ana_NeNe2025_cent510.hfsummax = cms.double(382.614)
process.epptdecomatrixnew_ana_NeNe2025_cent1030.hfsummin = cms.double(172.182)
process.epptdecomatrixnew_ana_NeNe2025_cent1030.hfsummax = cms.double(321.818)
process.epptdecomatrixnew_ana_NeNe2025_cent3050.hfsummin = cms.double(87.6935)
process.epptdecomatrixnew_ana_NeNe2025_cent3050.hfsummax = cms.double(172.182)
process.epptdecomatrixnew_ana_NeNe2025_cent5070.hfsummin = cms.double(39.876)
process.epptdecomatrixnew_ana_NeNe2025_cent5070.hfsummax = cms.double(87.6935)

process.ana_step_cent01 = cms.Path(process.eventFilter_MB * process.epptdecomatrixnew_ana_NeNe2025_cent01)
process.ana_step_cent05 = cms.Path(process.eventFilter_MB * process.epptdecomatrixnew_ana_NeNe2025_cent05)
process.ana_step_cent510 = cms.Path(process.eventFilter_MB * process.epptdecomatrixnew_ana_NeNe2025_cent510)
process.ana_step_cent1030 = cms.Path(process.eventFilter_MB * process.epptdecomatrixnew_ana_NeNe2025_cent1030)
process.ana_step_cent3050 = cms.Path(process.eventFilter_MB * process.epptdecomatrixnew_ana_NeNe2025_cent3050)
process.ana_step_cent5070 = cms.Path(process.eventFilter_MB * process.epptdecomatrixnew_ana_NeNe2025_cent5070)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('epptdecomatrixnew_pfcand.root'))

# Define the process schedule

process.schedule = cms.Schedule(
    process.ana_step_cent01,
    process.ana_step_cent05,
    process.ana_step_cent510,
    process.ana_step_cent1030,
    process.ana_step_cent3050,
    process.ana_step_cent5070    
)

process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.eventFilter_MB.insert(0, process.unpackedTracksAndVertices)

from HLTrigger.Configuration.CustomConfigs import massReplaceInputTag
process = massReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
process = massReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")
