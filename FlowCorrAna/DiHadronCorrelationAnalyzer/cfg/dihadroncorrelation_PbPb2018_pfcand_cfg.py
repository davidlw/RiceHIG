import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
process = cms.Process('ANASKIM',eras.Run2_2018_pp_on_AA)

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')

# Limit the output messages
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('file:/eos/cms/store/group/phys_heavyions/flowcorr/F134F372-A1D6-9844-AB54-77742E73027C_PbPb2018.root'),
   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = cms.string('103X_dataRun2_v6')

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

# Add PbPb event plane
process.load("RecoHI.HiEvtPlaneAlgos.HiEvtPlane_cfi")
process.load("RecoHI.HiEvtPlaneAlgos.hiEvtPlaneFlat_cfi")
process.hiEvtPlane.trackTag = cms.InputTag("generalTracks")
process.hiEvtPlane.vertexTag = cms.InputTag("offlinePrimaryVerticesRecovery")
process.hiEvtPlane.loadDB = cms.bool(True)
process.hiEvtPlane.useNtrk = cms.untracked.bool(False)
process.hiEvtPlane.caloCentRef = cms.double(-1)
process.hiEvtPlane.caloCentRefWidth = cms.double(-1)
process.hiEvtPlaneFlat.caloCentRef = cms.double(-1)
process.hiEvtPlaneFlat.caloCentRefWidth = cms.double(-1)
process.hiEvtPlaneFlat.vertexTag = cms.InputTag("offlinePrimaryVerticesRecovery")
process.hiEvtPlaneFlat.useNtrk = cms.untracked.bool(False)
process.CondDB.connect = "sqlite_file:HeavyIonRPRcd_PbPb2018_offline.db"
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                       process.CondDB,
                                       toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRPRcd'),
                                                                  tag = cms.string('HeavyIonRPRcd_PbPb2018_offline')
                                                                  )
                                                         )
                                      )
process.es_prefer_flatparms = cms.ESPrefer('PoolDBESSource','')
process.evtplane_seq = cms.Sequence(process.hiEvtPlane * process.hiEvtPlaneFlat)

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
process.load('VertexCompositeAnalysis.VertexCompositeProducer.collisionEventSelection_cff')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.clusterCompatibilityFilter_cfi')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.hfCoincFilter_cff')
process.load("VertexCompositeAnalysis.VertexCompositeProducer.OfflinePrimaryVerticesRecovery_cfi")
process.colEvtSel = cms.Sequence(process.hfCoincFilter2Th4 * process.primaryVertexFilter * process.clusterCompatibilityFilter)

# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
    process.hltFilter *
    process.offlinePrimaryVerticesRecovery *
    process.colEvtSel
)
process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

# ZDC info
process.load('VertexCompositeAnalysis.VertexCompositeProducer.QWZDC2018Producer_cfi')
process.load('VertexCompositeAnalysis.VertexCompositeProducer.QWZDC2018RecHit_cfi')
process.pcentandep_step = cms.Path(process.eventFilter_HM * process.zdcdigi * process.QWzdcreco * process.cent_seq * process.evtplane_seq)

# Define the analysis steps
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_PbPb2018.IsCorr = cms.bool(False)
process.corr_ana_PbPb2018.IsDebug = cms.bool(True)
process.corr_ana_PbPb2018.centmin = cms.int32(0)
process.corr_ana_PbPb2018.centmax = cms.int32(200)
process.corr_ana_PbPb2018.TriggerID = cms.string('PFCandidate')
process.corr_ana_PbPb2018.AssociateID = cms.string('PFCandidate')
process.corr_ana_PbPb2018.etatrgmin = cms.double(-6)
process.corr_ana_PbPb2018.etatrgmax = cms.double(6)
process.corr_ana_PbPb2018.etaassmin = cms.double(-6)
process.corr_ana_PbPb2018.etaassmax = cms.double(6)
process.corr_ana_PbPb2018.pttrgmin = cms.vdouble(0.0)
process.corr_ana_PbPb2018.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2018.ptassmin = cms.vdouble(0.0)
process.corr_ana_PbPb2018.ptassmax = cms.vdouble(1000.0)
process.corr_ana_PbPb2018.IsPtWeightTrg = cms.bool(True)
process.corr_ana_PbPb2018.IsPtWeightAss = cms.bool(True)

process.corr_ana_PbPb2018_cent05 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent510 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent1030 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent3050 = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_cent50100 = process.corr_ana_PbPb2018.clone()
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

process.ana_step = cms.Path(process.eventFilter_HM *
process.corr_ana_PbPb2018_cent05 *
process.corr_ana_PbPb2018_cent510 *
process.corr_ana_PbPb2018_cent1030 *
process.corr_ana_PbPb2018_cent3050 *
process.corr_ana_PbPb2018_cent50100 
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('dihadroncorrelation_pfcand.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.pcentandep_step,
    process.ana_step 
)

# Add recovery for offline primary vertex
from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"
