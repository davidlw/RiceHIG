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
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/himc/HINPbPbAutumn18DR/MinBias_Hydjet_Drum5F_2018_5p02TeV/AODSIM/NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/120000/411DF9D7-A2FF-AD42-8FE2-5D2396C0970D.root'),
   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '')

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
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("HeavyIonRcd"),
        tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5F_v1032x02_mc"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        label = cms.untracked.string("HFtowers")
        ),
    ])
#process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)
process.cent_seq = cms.Sequence(process.centralityBin)

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
#process.load('VertexCompositeAnalysis.VertexCompositeProducer.collisionEventSelection_cff')
#process.load('VertexCompositeAnalysis.VertexCompositeProducer.clusterCompatibilityFilter_cfi')
#process.load('VertexCompositeAnalysis.VertexCompositeProducer.hfCoincFilter_cff')
#process.load("VertexCompositeAnalysis.VertexCompositeProducer.OfflinePrimaryVerticesRecovery_cfi")
#process.colEvtSel = cms.Sequence(process.hfCoincFilter2Th4 * process.primaryVertexFilter * process.clusterCompatibilityFilter)

# Define the event selection sequence
process.eventFilter_HM = cms.Sequence(
#    process.hltFilter *
#    process.offlinePrimaryVerticesRecovery *
#    process.colEvtSel
)
process.eventFilter_HM_step = cms.Path( process.eventFilter_HM )

# Define the analysis steps
process.load('MergingProducer.generalAndHiPixelTracks.MergingPixAndGenProducer_cfi')
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_PbPb2018.TrgTrackCollection = cms.InputTag("generalAndHiPixelTracks")
process.corr_ana_PbPb2018.IsPPTrkQuality = cms.bool(False)
process.corr_ana_PbPb2018.IsHITrkQuality = cms.bool(False)
process.corr_ana_PbPb2018.IsCorr = cms.bool(False)
process.corr_ana_PbPb2018.IsDebug = cms.bool(True)
process.corr_ana_PbPb2018.centmin = cms.int32(-1)
process.corr_ana_PbPb2018.centmax = cms.int32(-1)
process.corr_ana_PbPb2018.etamultmin = cms.double(3)
process.corr_ana_PbPb2018.etamultmax = cms.double(5.2)
process.corr_ana_PbPb2018.ptmultmin = cms.double(0.0)
process.corr_ana_PbPb2018.pttrgmin = cms.vdouble(0.0)
process.corr_ana_PbPb2018.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2018.etatrgmin = cms.double(3.0)
process.corr_ana_PbPb2018.etatrgmax = cms.double(5.2)
process.corr_ana_PbPb2018.ptassmin = cms.vdouble(0.0)
process.corr_ana_PbPb2018.ptassmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2018.etaassmin = cms.double(3.0)
process.corr_ana_PbPb2018.etaassmax = cms.double(5.2)
process.corr_ana_PbPb2018.AssociateID = cms.string('CaloTower')

process.corr_ana_PbPb2018_gen = process.corr_ana_PbPb2018.clone()
process.corr_ana_PbPb2018_gen.EffFileName = cms.string('')
process.corr_ana_PbPb2018_gen.IsGenMult = cms.bool(True)
process.corr_ana_PbPb2018_gen.TriggerID = cms.string('GenParticle')
process.corr_ana_PbPb2018_gen.IsPtWeightTrg = cms.bool(True)
process.corr_ana_PbPb2018_gen.IsTrgEtaCutAbs = cms.bool(True)
process.corr_ana_PbPb2018_gen.ischarge_trg = cms.bool(False)
process.corr_ana_PbPb2018_genmult = process.corr_ana_PbPb2018_gen.clone()
process.corr_ana_PbPb2018_genmult.IsGenCentrality = cms.bool(True)
process.corr_ana_PbPb2018_genmult.IsVtxSel = cms.bool(False)

process.ana_step_gen = cms.Path(process.eventFilter_HM * #* process.generalAndHiPixelTracks *
process.corr_ana_PbPb2018_genmult
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('hfres.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.eventFilter_HM_step,
    process.ana_step_gen
)
