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

# Define the analysis steps
#process.pcentandep_step = cms.Path(process.eventFilter_HM * process.zdcdigi * process.QWzdcreco * process.cent_seq * process.evtplane_seq)
process.pcentandep_step = cms.Path(process.eventFilter_HM * process.cent_seq)

process.load('MergingProducer.generalAndHiPixelTracks.MergingPixAndGenProducer_cfi')
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epptdecomatrix_cff")
process.epptdecomatrix_ana_PbPb2018.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracks")
process.epptdecomatrix_ana_PbPb2018.IsPPTrkQuality = cms.bool(False)
process.epptdecomatrix_ana_PbPb2018.IsHITrkQuality = cms.bool(False)
process.epptdecomatrix_ana_PbPb2018.centmin = cms.int32(0)
process.epptdecomatrix_ana_PbPb2018.centmax = cms.int32(2)
#process.epptdecomatrix_ana_PbPb2018.IsPtWeightTrg = cms.bool(True)
process.epptdecomatrix_ana_PbPb2018.EffFileName = cms.string('EffCorrectionsPixelPbPb2018_v1.root')
process.epptdecomatrix_ana_PbPb2018.EffHistName = cms.string('Eff_0_5')
process.epptdecomatrix_ana_PbPb2018.FakFileName = cms.string('')
process.epptdecomatrix_ana_PbPb2018.FakHistName = cms.string('')
process.epptdecomatrix_ana_PbPb2018.pttrgmin = cms.vdouble(0.3,0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15)
process.epptdecomatrix_ana_PbPb2018.pttrgmax = cms.vdouble(0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15,20)
process.epptdecomatrix_ana_PbPb2018.ptassmin = cms.vdouble(0.3,0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15)
process.epptdecomatrix_ana_PbPb2018.ptassmax = cms.vdouble(0.5,0.7,1.0,1.3,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10,15,20)

process.epptdecomatrix_ana_PbPb2018_cent01 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent05 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent510 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent1020 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent2030 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent3040 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent4050 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent5060 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent6070 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent7080 = process.epptdecomatrix_ana_PbPb2018.clone()
process.epptdecomatrix_ana_PbPb2018_cent05.centmin = cms.int32(0)
process.epptdecomatrix_ana_PbPb2018_cent05.centmax = cms.int32(10)
process.epptdecomatrix_ana_PbPb2018_cent510.centmin = cms.int32(10)
process.epptdecomatrix_ana_PbPb2018_cent510.centmax = cms.int32(20)
process.epptdecomatrix_ana_PbPb2018_cent1020.centmin = cms.int32(20)
process.epptdecomatrix_ana_PbPb2018_cent1020.centmax = cms.int32(40)
process.epptdecomatrix_ana_PbPb2018_cent2030.centmin = cms.int32(40)
process.epptdecomatrix_ana_PbPb2018_cent2030.centmax = cms.int32(60)
process.epptdecomatrix_ana_PbPb2018_cent3040.centmin = cms.int32(60)
process.epptdecomatrix_ana_PbPb2018_cent3040.centmax = cms.int32(80)
process.epptdecomatrix_ana_PbPb2018_cent4050.centmin = cms.int32(80)
process.epptdecomatrix_ana_PbPb2018_cent4050.centmax = cms.int32(100)
process.epptdecomatrix_ana_PbPb2018_cent5060.centmin = cms.int32(100)
process.epptdecomatrix_ana_PbPb2018_cent5060.centmax = cms.int32(120)
process.epptdecomatrix_ana_PbPb2018_cent6070.centmin = cms.int32(120)
process.epptdecomatrix_ana_PbPb2018_cent6070.centmax = cms.int32(140)
process.epptdecomatrix_ana_PbPb2018_cent7080.centmin = cms.int32(140)
process.epptdecomatrix_ana_PbPb2018_cent7080.centmax = cms.int32(160)
process.epptdecomatrix_ana_PbPb2018_cent510.EffHistName = cms.string('Eff_5_10')
process.epptdecomatrix_ana_PbPb2018_cent1020.EffHistName = cms.string('Eff_10_30')
process.epptdecomatrix_ana_PbPb2018_cent2030.EffHistName = cms.string('Eff_10_30')
process.epptdecomatrix_ana_PbPb2018_cent3040.EffHistName = cms.string('Eff_30_50')
process.epptdecomatrix_ana_PbPb2018_cent4050.EffHistName = cms.string('Eff_30_50')
process.epptdecomatrix_ana_PbPb2018_cent5060.EffHistName = cms.string('Eff_50_100')
process.epptdecomatrix_ana_PbPb2018_cent6070.EffHistName = cms.string('Eff_50_100')
process.epptdecomatrix_ana_PbPb2018_cent7080.EffHistName = cms.string('Eff_50_100')

#process.epptdecomatrix_ana_PbPb2018_cent05.IsCorr = cms.bool(False)

process.ana_step = cms.Path(process.eventFilter_HM 
                          * process.generalAndHiPixelTracks
                          * process.epptdecomatrix_ana_PbPb2018_cent01
                          * process.epptdecomatrix_ana_PbPb2018_cent05
                          * process.epptdecomatrix_ana_PbPb2018_cent510
                          * process.epptdecomatrix_ana_PbPb2018_cent1020
                          * process.epptdecomatrix_ana_PbPb2018_cent2030
                          * process.epptdecomatrix_ana_PbPb2018_cent3040
                          * process.epptdecomatrix_ana_PbPb2018_cent4050
                          * process.epptdecomatrix_ana_PbPb2018_cent5060
                          * process.epptdecomatrix_ana_PbPb2018_cent6070
                          * process.epptdecomatrix_ana_PbPb2018_cent7080
)


# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('epptdecomatrix.root'))

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
