import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
process = cms.Process('ANASKIM',eras.Run2_2018_pp_on_AA)
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
process.load('Configuration.StandardSequences.PAT_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/hidata/HIRun2018A/HIMinimumBias0/MINIAOD/PbPb18_MiniAODv1-v1/00000/00cdc438-4cf1-4d3b-b6bf-ad53d558fb11.root'),
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '112X_dataRun2_PromptLike_HI_v6', '')

# Add PbPb centrality
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceZDChits = True
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
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1033p1x01_offline"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])
process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
    'HLT_HIMinimumBias_*', # MinimumBias  
]

# Add PbPb collision event selection
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
    process.phfCoincFilter2Th4 *
    process.primaryVertexFilterHI *
    process.clusterCompatibilityFilter
)
process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

# ZDC info
process.load('VertexCompositeAnalysis.VertexCompositeProducer.QWZDC2018Producer_cfi')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.QWZDC2018RecHit_cfi')
process.pcentandep_step = cms.Path(process.eventFilter_HM * process.zdcdigi * process.QWzdcreco * process.cent_seq )

# Define the analysis steps
process.load('MergingProducer.generalAndHiPixelTracks.MergingPixAndGenProducer_cfi')
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_PbPb2018.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracks")
process.corr_ana_PbPb2018.VertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices")
process.corr_ana_PbPb2018.IsPPTrkQuality = cms.bool(False)
process.corr_ana_PbPb2018.IsHITrkQuality = cms.bool(False)
process.corr_ana_PbPb2018.IsCorr = cms.bool(False)
process.corr_ana_PbPb2018.IsDebug = cms.bool(True)
process.corr_ana_PbPb2018.centmin = cms.int32(0)
process.corr_ana_PbPb2018.centmax = cms.int32(200)
process.corr_ana_PbPb2018.etamultmin = cms.double(-0.5)
process.corr_ana_PbPb2018.etamultmax = cms.double(0.5)
process.corr_ana_PbPb2018.ptmultmin = cms.double(0.3)
process.corr_ana_PbPb2018.pttrgmin = cms.vdouble(0.3)
process.corr_ana_PbPb2018.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2018.etatrgmin = cms.double(-0.5)
process.corr_ana_PbPb2018.etatrgmax = cms.double(0.5)
process.corr_ana_PbPb2018.ptassmin = cms.vdouble(0.0)
process.corr_ana_PbPb2018.ptassmax = cms.vdouble(0.0)
process.corr_ana_PbPb2018.AssociateID = cms.string('Track')
#process.corr_ana_PbPb2018.EffFileName = cms.string('')
process.corr_ana_PbPb2018.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol1_mcnpix_miniAOD_pidvaridalicemorebinsv2_v4.root')
#process.corr_ana_PbPb2018.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol1_mcnpix_miniAOD_morebins_v4.root')
#process.corr_ana_PbPb2018.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol1_mcnpix_miniAOD_v4.root')
#process.corr_ana_PbPb2018.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol1_mcnpix_miniAOD_v3.root')
process.corr_ana_PbPb2018.EffHistName = cms.string('Cor3D')
#process.corr_ana_PbPb2018.EffHistName = cms.string('Cor3D_fitsplit')

process.corr_ana_PbPb2018_cent005 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent05 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent510 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent1030 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent3050 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent50100 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin01 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin12 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin23 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin34 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin45 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin56 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin67 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin78 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin89 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin910 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin1012 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin1214 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin1416 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin1618 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_centbin1820 = process.corr_ana_PbPb2018.clone()

process.corr_ana_PbPb2018_cent005.centmin = cms.int32(0)
process.corr_ana_PbPb2018_cent005.centmax = cms.int32(1)
process.corr_ana_PbPb2018_cent05.centmin = cms.int32(0)
process.corr_ana_PbPb2018_cent05.centmax = cms.int32(10)
process.corr_ana_PbPb2018_cent510.centmin = cms.int32(10)
process.corr_ana_PbPb2018_cent510.centmax = cms.int32(20)
process.corr_ana_PbPb2018_cent1030.centmin = cms.int32(20)
process.corr_ana_PbPb2018_cent1030.centmax = cms.int32(60)
process.corr_ana_PbPb2018_cent3050.centmin = cms.int32(60)
process.corr_ana_PbPb2018_cent3050.centmax = cms.int32(100)
process.corr_ana_PbPb2018_cent50100.centmin = cms.int32(100)
process.corr_ana_PbPb2018_cent50100.centmax = cms.int32(200)
process.corr_ana_PbPb2018_centbin01.centmin = cms.int32(0)
process.corr_ana_PbPb2018_centbin01.centmax = cms.int32(1)
process.corr_ana_PbPb2018_centbin12.centmin = cms.int32(1)
process.corr_ana_PbPb2018_centbin12.centmax = cms.int32(2)
process.corr_ana_PbPb2018_centbin23.centmin = cms.int32(2)
process.corr_ana_PbPb2018_centbin23.centmax = cms.int32(3)
process.corr_ana_PbPb2018_centbin34.centmin = cms.int32(3)
process.corr_ana_PbPb2018_centbin34.centmax = cms.int32(4)
process.corr_ana_PbPb2018_centbin45.centmin = cms.int32(4)
process.corr_ana_PbPb2018_centbin45.centmax = cms.int32(5)
process.corr_ana_PbPb2018_centbin56.centmin = cms.int32(5)
process.corr_ana_PbPb2018_centbin56.centmax = cms.int32(6)
process.corr_ana_PbPb2018_centbin67.centmin = cms.int32(6)
process.corr_ana_PbPb2018_centbin67.centmax = cms.int32(7)
process.corr_ana_PbPb2018_centbin78.centmin = cms.int32(7)
process.corr_ana_PbPb2018_centbin78.centmax = cms.int32(8)
process.corr_ana_PbPb2018_centbin89.centmin = cms.int32(8)
process.corr_ana_PbPb2018_centbin89.centmax = cms.int32(9)
process.corr_ana_PbPb2018_centbin910.centmin = cms.int32(9)
process.corr_ana_PbPb2018_centbin910.centmax = cms.int32(10)
process.corr_ana_PbPb2018_centbin1012.centmin = cms.int32(10)
process.corr_ana_PbPb2018_centbin1012.centmax = cms.int32(12)
process.corr_ana_PbPb2018_centbin1214.centmin = cms.int32(12)
process.corr_ana_PbPb2018_centbin1214.centmax = cms.int32(14)
process.corr_ana_PbPb2018_centbin1416.centmin = cms.int32(14)
process.corr_ana_PbPb2018_centbin1416.centmax = cms.int32(16)
process.corr_ana_PbPb2018_centbin1618.centmin = cms.int32(16)
process.corr_ana_PbPb2018_centbin1618.centmax = cms.int32(18)
process.corr_ana_PbPb2018_centbin1820.centmin = cms.int32(18)
process.corr_ana_PbPb2018_centbin1820.centmax = cms.int32(20)

process.generalAndHiPixelTracksTight = process.generalAndHiPixelTracks.clone(
  dxyErrMax = cms.double(2.0),
  dzErrMax = cms.double(2.0),
  ptErrMax = cms.double(0.05),
  chi2nMax = cms.double(0.15),
  dzErrMaxPixel = cms.double(10.0),
  dxyErrMaxPixel = cms.double(5.0)
)

process.generalAndHiPixelTracksLoose = process.generalAndHiPixelTracks.clone(
  dxyErrMax = cms.double(5.0),
  dzErrMax = cms.double(5.0),
  ptErrMax = cms.double(0.15),
  dzErrMaxPixel = cms.double(10.0),
  dxyErrMaxPixel = cms.double(10.0)
)

process.corr_ana_PbPb2018_tight = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_tight.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracksTight")
#process.corr_ana_PbPb2018_tight.EffFileName = cms.string('EffCorrectionsMergedPbPb2018_tight.root')
process.corr_ana_PbPb2018_tight.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol1_mcnpix_miniAOD_tight_v3.root')
process.corr_ana_PbPb2018_loose = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_loose.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracksLoose")
#process.corr_ana_PbPb2018_loose.EffFileName = cms.string('EffCorrectionsMergedPbPb2018_loose.root')
process.corr_ana_PbPb2018_loose.EffFileName = cms.string('EffCorrectionsPbPb2018_merged_3D_pol1_mcnpix_miniAOD_loose_v3.root')

#process.corr_ana_PbPb2018_tight.EffFileName = cms.string('')
#process.corr_ana_PbPb2018_loose.EffFileName = cms.string('')
#process.corr_ana_PbPb2018.EffFileName = cms.string('')

process.corr_ana_PbPb2018_tight_cent05 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent510 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent1030 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent3050 = process.corr_ana_PbPb2018_tight.clone()
process.corr_ana_PbPb2018_tight_cent50100 = process.corr_ana_PbPb2018_tight.clone()
#process.corr_ana_PbPb2018_tight_cent05.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_tight_cent510.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_tight_cent1030.EffHistName = cms.string('Cor_10_30')
#process.corr_ana_PbPb2018_tight_cent3050.EffHistName = cms.string('Cor_30_50')
#process.corr_ana_PbPb2018_tight_cent50100.EffHistName = cms.string('Cor_50_100')
process.corr_ana_PbPb2018_tight_cent05.centmin = cms.int32(0)
process.corr_ana_PbPb2018_tight_cent05.centmax = cms.int32(10)
process.corr_ana_PbPb2018_tight_cent510.centmin = cms.int32(10)
process.corr_ana_PbPb2018_tight_cent510.centmax = cms.int32(20)
process.corr_ana_PbPb2018_tight_cent1030.centmin = cms.int32(20)
process.corr_ana_PbPb2018_tight_cent1030.centmax = cms.int32(60)
process.corr_ana_PbPb2018_tight_cent3050.centmin = cms.int32(60)
process.corr_ana_PbPb2018_tight_cent3050.centmax = cms.int32(100)
process.corr_ana_PbPb2018_tight_cent50100.centmin = cms.int32(100)
process.corr_ana_PbPb2018_tight_cent50100.centmax = cms.int32(200)

process.corr_ana_PbPb2018_loose_cent05 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent510 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent1030 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent3050 = process.corr_ana_PbPb2018_loose.clone()
process.corr_ana_PbPb2018_loose_cent50100 = process.corr_ana_PbPb2018_loose.clone()
#process.corr_ana_PbPb2018_loose_cent05.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_loose_cent510.EffHistName = cms.string('Cor_0_5')
#process.corr_ana_PbPb2018_loose_cent1030.EffHistName = cms.string('Cor_10_30')
#process.corr_ana_PbPb2018_loose_cent3050.EffHistName = cms.string('Cor_30_50')
#process.corr_ana_PbPb2018_loose_cent50100.EffHistName = cms.string('Cor_50_100')
process.corr_ana_PbPb2018_loose_cent05.centmin = cms.int32(0)
process.corr_ana_PbPb2018_loose_cent05.centmax = cms.int32(10)
process.corr_ana_PbPb2018_loose_cent510.centmin = cms.int32(10)
process.corr_ana_PbPb2018_loose_cent510.centmax = cms.int32(20)
process.corr_ana_PbPb2018_loose_cent1030.centmin = cms.int32(20)
process.corr_ana_PbPb2018_loose_cent1030.centmax = cms.int32(60)
process.corr_ana_PbPb2018_loose_cent3050.centmin = cms.int32(60)
process.corr_ana_PbPb2018_loose_cent3050.centmax = cms.int32(100)
process.corr_ana_PbPb2018_loose_cent50100.centmin = cms.int32(100)
process.corr_ana_PbPb2018_loose_cent50100.centmax = cms.int32(200)

process.ana_ucc_step = cms.Path(process.eventFilter_HM * process.generalAndHiPixelTracks *
  process.corr_ana_PbPb2018_cent005
)

process.ana_step = cms.Path(process.eventFilter_HM * process.generalAndHiPixelTracks *
  process.corr_ana_PbPb2018_cent05 *
  process.corr_ana_PbPb2018_cent510 #*
#process.corr_ana_PbPb2018_centbin01 *
#process.corr_ana_PbPb2018_centbin12 *
#process.corr_ana_PbPb2018_centbin23 *
#process.corr_ana_PbPb2018_centbin34 *
#process.corr_ana_PbPb2018_centbin45 *
#process.corr_ana_PbPb2018_centbin56 *
#process.corr_ana_PbPb2018_centbin67 *
#process.corr_ana_PbPb2018_centbin78 *
#process.corr_ana_PbPb2018_centbin89 *
#process.corr_ana_PbPb2018_centbin910 *
#process.corr_ana_PbPb2018_centbin1012 *
#process.corr_ana_PbPb2018_centbin1214 *
#process.corr_ana_PbPb2018_centbin1416 *
#process.corr_ana_PbPb2018_centbin1618 *
#process.corr_ana_PbPb2018_centbin1820
#  process.corr_ana_PbPb2018_cent1030 *
#  process.corr_ana_PbPb2018_cent3050 *
#  process.corr_ana_PbPb2018_cent50100
)

process.ana_step_syst = cms.Path(process.eventFilter_HM * process.generalAndHiPixelTracksTight * process.generalAndHiPixelTracksLoose *
  process.corr_ana_PbPb2018_tight_cent05 *
  process.corr_ana_PbPb2018_tight_cent510 *
#  process.corr_ana_PbPb2018_tight_cent1030 *
#  process.corr_ana_PbPb2018_tight_cent3050 *
#  process.corr_ana_PbPb2018_tight_cent50100 *
  process.corr_ana_PbPb2018_loose_cent05 *
  process.corr_ana_PbPb2018_loose_cent510 #*
#  process.corr_ana_PbPb2018_loose_cent1030 *
#  process.corr_ana_PbPb2018_loose_cent3050 *
#  process.corr_ana_PbPb2018_loose_cent50100
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('dihadroncorrelation.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.pcentandep_step,
#    process.ana_ucc_step,
    process.ana_step #,
#    process.ana_step_syst
)

# Add recovery for offline primary vertex
#from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
#process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
#process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"
