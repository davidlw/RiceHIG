import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
process = cms.Process('ANASKIM', Run3_pp_on_PbPb)

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
#process.load('Configuration.StandardSequences.PAT_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 2000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIForward0/MINIAOD/16Jan2024-v1/30000/a99ea21d-d0cc-4f1e-8097-c2c6d2f79cdb.root'),
#   fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIForward0/MINIAOD/16Jan2024-v1/2810000/3151fd93-8b9b-40ea-9275-826a3977638c.root'),
#    fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIPhysicsRawPrime0/MINIAOD/PromptReco-v2/000/375/790/00000/56ad580f-b228-4f3c-b8e3-17f9d95c7654.root')
#    fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov///store/hidata/HIRun2023A/HIPhysicsRawPrime0/MINIAOD/PromptReco-v2/000/375/754/00000/51783dff-2cfa-474c-a19f-e7624fad7a36.root'),
#   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2023HI_374288_375823_Golden.json').getVLuminosityBlockRange()

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '132X_dataRun3_Prompt_v7', '')

# ==================================================================
# ==================== modification needed for 2023 data ===========
from CondCore.CondDB.CondDB_cfi import *
process.es_pool = cms.ESSource("PoolDBESSource",
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string("HcalElectronicsMapRcd"),
            tag = cms.string("HcalElectronicsMap_2021_v2.0_data")
        )
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
        authenticationMethod = cms.untracked.uint32(1)
    )

process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')
process.es_ascii = cms.ESSource(
    'HcalTextCalibrations',
    input = cms.VPSet(
        cms.PSet(

            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath("emap_2023_newZDC_v3.txt")

             )
        )
    )
# =======================================================================

# Add PbPb centrality
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceZDChits = False
process.hiCentrality.produceETmidRapidity = False
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = False
process.hiCentrality.producePixelTracks = False
process.hiCentrality.reUseCentrality = True
process.hiCentrality.srcZDChits = cms.InputTag("QWzdcreco")
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","reRECO")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")
process.cent_seq = cms.Sequence(process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # photo-nuclear 
     'HLT_HIUPC_ZDC1nAsymXOR_MBHF1AND_PixelTrackMultiplicity20_v*',
     'HLT_HIUPC_ZDC1nXOR_MBHF1AND_PixelTrackMultiplicity20_v*',
]

process.hltFilter_zdcor = process.hltFilter.clone()
process.hltFilter_zdcor.HLTPaths = [
     'HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v*',
     'HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v*',
]

process.hltFilter_zb = process.hltFilter.clone()
process.hltFilter_zb.HLTPaths = [
     'HLT_HIUPC_ZeroBias_SinglePixelTrackLowPt_MaxPixelCluster400_v*',
     'HLT_HIUPC_ZeroBias_MinPixelCluster400_MaxPixelCluster10000_v*',
]

# Add PbPb collision event selection
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hffilter_cfi')
process.primaryVertexFilterHI.src = cms.InputTag("offlinePrimaryVertices")

process.eventFilter_MB = cms.Sequence(
    process.hltFilter *
    process.primaryVertexFilterHI *
    process.cent_seq
)

process.eventFilter_zdcor = cms.Sequence(
    process.hltFilter_zdcor *
    process.primaryVertexFilterHI *
    process.cent_seq
)

process.eventFilter_zb = cms.Sequence(
    process.hltFilter_zb *
    process.primaryVertexFilterHI *
    process.cent_seq
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_PbPb2023.centmin = cms.int32(0)
process.corr_ana_PbPb2023.centmax = cms.int32(200)
process.corr_ana_PbPb2023.nmin = cms.int32(-1)
process.corr_ana_PbPb2023.nmax = cms.int32(-1)
process.corr_ana_PbPb2023.IsDebug = cms.bool(True)
process.corr_ana_PbPb2023.IsCorr = cms.bool(False)

# running on particle flow
process.corr_ana_PbPb2023.TriggerID = cms.string('PackedPFHadronHF')
process.corr_ana_PbPb2023.AssociateID = cms.string('Track')
process.corr_ana_PbPb2023.etaassmin = cms.double(-2.4)
process.corr_ana_PbPb2023.etaassmax = cms.double(2.4)
process.corr_ana_PbPb2023.etatrgmin = cms.double(3)
process.corr_ana_PbPb2023.etatrgmax = cms.double(5)
process.corr_ana_PbPb2023.ptassmin = cms.vdouble(0.3,1.0)
process.corr_ana_PbPb2023.ptassmax = cms.vdouble(3.0,3.0)
process.corr_ana_PbPb2023.pttrgmin = cms.vdouble(0.0)
process.corr_ana_PbPb2023.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2023.IsPtWeightTrg = cms.bool(True)
#process.corr_ana_PbPb2023.IsPtWeightAss = cms.bool(True)
process.corr_ana_PbPb2023.EffFileName = cms.string('')
process.corr_ana_PbPb2023.FakFileName = cms.string('')
process.corr_ana_PbPb2023.IsAssEtaCutAbs = cms.bool(False)
process.corr_ana_PbPb2023.IsTrgEtaCutAbs = cms.bool(False)

process.corr_ana_PbPb2023_TrkCalo = process.corr_ana_PbPb2023.clone()
process.corr_ana_PbPb2023_TrkCaloM = process.corr_ana_PbPb2023_TrkCalo.clone(
  etaassmin = cms.double(-2.4),
  etaassmax = cms.double(2.4),
  etatrgmin = cms.double(-5.0),
  etatrgmax = cms.double(-3.0),
)
process.corr_ana_PbPb2023_TrkCaloP = process.corr_ana_PbPb2023_TrkCalo.clone(
  etaassmin = cms.double(-2.4),
  etaassmax = cms.double(2.4),
  etatrgmin = cms.double(3.0),
  etatrgmax = cms.double(5.0),
)

process.corr_ana_PbPb2023_CaloCaloPM = process.corr_ana_PbPb2023_TrkCalo.clone(
  TriggerID = cms.string('PackedPFHadronHF'),
  AssociateID = cms.string('PackedPFHadronHF'),

  IsPtWeightTrg = cms.bool(True),
  IsPtWeightAss = cms.bool(True),

  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(10000.0),
  
  etatrgmin = cms.double(-5.0),
  etatrgmax = cms.double(-3.0),
  etaassmin = cms.double(3.0),
  etaassmax = cms.double(5.0),
)

process.ana_seq1 = cms.Sequence(process.corr_ana_PbPb2023_TrkCaloP)
process.ana_seq1a = cms.Sequence(process.corr_ana_PbPb2023_TrkCaloM)
process.ana_seq1b = cms.Sequence(process.corr_ana_PbPb2023_CaloCaloPM)

process.ana1 = cms.Path(process.eventFilter_MB * process.ana_seq1)
process.ana1a = cms.Path(process.eventFilter_zdcor * process.ana_seq1a)
process.ana1b = cms.Path(process.eventFilter_zb * process.ana_seq1b)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('corr_pfcand_2023.root'))

# Define the process schedule

process.schedule = cms.Schedule(
    process.ana1,
    process.ana1a,
    process.ana1b    
)

process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')
process.eventFilter_MB.insert(0, process.unpackedTracksAndVertices)
process.eventFilter_zdcor.insert(0, process.unpackedTracksAndVertices)
process.eventFilter_zb.insert(0, process.unpackedTracksAndVertices)

from HLTrigger.Configuration.CustomConfigs import massReplaceInputTag
process = massReplaceInputTag(process,"offlinePrimaryVertices","unpackedTracksAndVertices")
process = massReplaceInputTag(process,"generalTracks","unpackedTracksAndVertices")
