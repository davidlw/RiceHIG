import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
#process = cms.Process('ANASKIM', Run3_pp_on_PbPb)
process = cms.Process('ANASKIM')

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
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Define the input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
       #'root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIPhysicsRawPrime0/MINIAOD/PromptReco-v2/000/374/828/00000/495c8e99-0571-4c79-b70b-f9025a68591c.root'),
              'root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIPhysicsRawPrime0/MINIAOD/PromptReco-v2/000/375/666/00000/7b6ad1f4-b004-4d44-942d-3c4aa84202bf.root'),
#   inputCommands=cms.untracked.vstring('keep *', 'drop *_hiEvtPlane_*_*')
)

#import FWCore.PythonUtilities.LumiList as LumiList
#process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2023HI_374288_375823_Golden.json').getVLuminosityBlockRange()

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))

# Set the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '132X_dataRun3_Prompt_v7', '')

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
            file = cms.FileInPath("FlowCorrAna/DiHadronCorrelationAnalyzer/data/emap_2023_newZDC_v3.txt")

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
process.hiCentrality.produceZDChits = True
process.hiCentrality.produceETmidRapidity = False
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = False
process.hiCentrality.producePixelTracks = False
process.hiCentrality.reUseCentrality = True
process.hiCentrality.srcZDChits = cms.InputTag("QWzdcreco")
process.hiCentrality.srcReUse = cms.InputTag("hiCentrality","","RECO")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("")
process.cent_seq = cms.Sequence(process.hiCentrality * process.centralityBin)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # MinimumBias 
     'HLT_HIMinimumBiasHF1ANDZDC1nOR_*', # MinimumBias
#    'HLT_HIMinimumBiasHF1AND_*', # MinimumBias
]

# ZDC info
process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018Producer_cfi')
process.load('HeavyIonsAnalysis.ZDCAnalysis.QWZDC2018RecHit_cfi')
process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.cent_seq )
#process.pcentandep_step = cms.Sequence( process.zdcdigi * process.QWzdcreco * process.zdcanalyzer * process.cent_seq )

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
    process.clusterCompatibilityFilter  *
    process.phfCoincFilter2Th4 * 
    process.pcentandep_step
)

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetaptdecomatrixnew_cff")
process.epetaptdecomatrixnew_ana_PbPb2023.centmin = cms.int32(0)
process.epetaptdecomatrixnew_ana_PbPb2023.centmax = cms.int32(2)
# running on particle flow
#process.epetaptdecomatrixnew_ana_PbPb2023.TriggerID = cms.string('PackedPFHadron')
#process.epetaptdecomatrixnew_ana_PbPb2023.AssociateID = cms.string('PackedPFHadron')
process.epetaptdecomatrixnew_ana_PbPb2023.TriggerID = cms.string('Track')
process.epetaptdecomatrixnew_ana_PbPb2023.AssociateID = cms.string('Track')
process.epetaptdecomatrixnew_ana_PbPb2023.etatrgmin = cms.double(-5.4)
process.epetaptdecomatrixnew_ana_PbPb2023.etatrgmax = cms.double(5.4)
process.epetaptdecomatrixnew_ana_PbPb2023.etaassmin = cms.double(-5.4)
process.epetaptdecomatrixnew_ana_PbPb2023.etaassmax = cms.double(5.4)
process.epetaptdecomatrixnew_ana_PbPb2023.pttrgmin = cms.vdouble(0.4)
process.epetaptdecomatrixnew_ana_PbPb2023.pttrgmax = cms.vdouble(3.0)
process.epetaptdecomatrixnew_ana_PbPb2023.ptassmin = cms.vdouble(0.4)
process.epetaptdecomatrixnew_ana_PbPb2023.ptassmax = cms.vdouble(3.0)
process.epetaptdecomatrixnew_ana_PbPb2023.IsPtWeightTrg = cms.bool(True)
process.epetaptdecomatrixnew_ana_PbPb2023.IsPtWeightAss = cms.bool(True)
#process.epetaptdecomatrixnew_ana_PbPb2023.EffFileName = cms.string('GeneralTracks_2023_HydjetMB_Official_Eff_3D_Nominal_9thJune2025.root')
#process.epetaptdecomatrixnew_ana_PbPb2023.FakFileName = cms.string('GeneralTracks_2023_HydjetMB_Official_Eff_3D_Nominal_9thJune2025.root')
process.epetaptdecomatrixnew_ana_PbPb2023.EffFileName = cms.string('')
process.epetaptdecomatrixnew_ana_PbPb2023.FakFileName = cms.string('')
process.epetaptdecomatrixnew_ana_PbPb2023.EffHistName = cms.string('hEff_3D')
process.epetaptdecomatrixnew_ana_PbPb2023.FakHistName = cms.string('hFak_3D')

process.epetaptdecomatrixnew_ana_PbPb2023_cent01 = process.epetaptdecomatrixnew_ana_PbPb2023.clone()
process.epetaptdecomatrixnew_ana_PbPb2023_cent05 = process.epetaptdecomatrixnew_ana_PbPb2023.clone()
process.epetaptdecomatrixnew_ana_PbPb2023_cent510 = process.epetaptdecomatrixnew_ana_PbPb2023.clone()
process.epetaptdecomatrixnew_ana_PbPb2023_cent1030 = process.epetaptdecomatrixnew_ana_PbPb2023.clone()
process.epetaptdecomatrixnew_ana_PbPb2023_cent3050 = process.epetaptdecomatrixnew_ana_PbPb2023.clone()
process.epetaptdecomatrixnew_ana_PbPb2023_cent5070 = process.epetaptdecomatrixnew_ana_PbPb2023.clone()
process.epetaptdecomatrixnew_ana_PbPb2023_cent05.centmin = cms.int32(0)
process.epetaptdecomatrixnew_ana_PbPb2023_cent05.centmax = cms.int32(10)
process.epetaptdecomatrixnew_ana_PbPb2023_cent510.centmin = cms.int32(10)
process.epetaptdecomatrixnew_ana_PbPb2023_cent510.centmax = cms.int32(20)
process.epetaptdecomatrixnew_ana_PbPb2023_cent1030.centmin = cms.int32(20)
process.epetaptdecomatrixnew_ana_PbPb2023_cent1030.centmax = cms.int32(60)
process.epetaptdecomatrixnew_ana_PbPb2023_cent3050.centmin = cms.int32(60)
process.epetaptdecomatrixnew_ana_PbPb2023_cent3050.centmax = cms.int32(100)
process.epetaptdecomatrixnew_ana_PbPb2023_cent5070.centmin = cms.int32(100)
process.epetaptdecomatrixnew_ana_PbPb2023_cent5070.centmax = cms.int32(140)

process.ana_step_cent01 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_PbPb2023_cent01)
process.ana_step_cent05 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_PbPb2023_cent05)
process.ana_step_cent510 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_PbPb2023_cent510)
process.ana_step_cent1030 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_PbPb2023_cent1030)
process.ana_step_cent3050 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_PbPb2023_cent3050)
process.ana_step_cent5070 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_PbPb2023_cent5070)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('epetaptdecomatrixnew_pfcand.root'))

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
