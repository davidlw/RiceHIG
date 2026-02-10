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
           'root://cmsxrootd.fnal.gov//store/hidata/OORun2025/IonPhysics0/MINIAOD/PromptReco-v1/000/394/209/00000/07650c6a-82e9-42c5-a613-51f9ae2165d5.root'
   )
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_Collisions2025OO_394153_394217_golden.json').getVLuminosityBlockRange()

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

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
process.pileupvertexfilter.doOO = True
process.pileupvertexfilter.doNeNe = False

process.eventFilter_MB = cms.Sequence(
    process.hltFilter *
    process.primaryVertexFilterHI *
    process.pileupvertexfilter *
    process.phfCoincFilterPF2Th4
)
process.eventFilter_MB_step = cms.Path( process.eventFilter_MB )

process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetaptdecomatrixnew_cff")
# running on particle flow
#process.epetaptdecomatrixnew_ana_OO2025.TriggerID = cms.string('PackedPFHadron')
#process.epetaptdecomatrixnew_ana_OO2025.AssociateID = cms.string('PackedPFHadron')
process.epetaptdecomatrixnew_ana_OO2025.TriggerID = cms.string('Track')
process.epetaptdecomatrixnew_ana_OO2025.AssociateID = cms.string('Track')
process.epetaptdecomatrixnew_ana_OO2025.etatrgmin = cms.double(-5.4)
process.epetaptdecomatrixnew_ana_OO2025.etatrgmax = cms.double(5.4)
process.epetaptdecomatrixnew_ana_OO2025.etaassmin = cms.double(-5.4)
process.epetaptdecomatrixnew_ana_OO2025.etaassmax = cms.double(5.4)
process.epetaptdecomatrixnew_ana_OO2025.pttrgmin = cms.vdouble(0.3)
process.epetaptdecomatrixnew_ana_OO2025.pttrgmax = cms.vdouble(3.0)
process.epetaptdecomatrixnew_ana_OO2025.ptassmin = cms.vdouble(0.3)
process.epetaptdecomatrixnew_ana_OO2025.ptassmax = cms.vdouble(3.0)
process.epetaptdecomatrixnew_ana_OO2025.IsPtWeightTrg = cms.bool(True)
process.epetaptdecomatrixnew_ana_OO2025.IsPtWeightAss = cms.bool(True)
process.epetaptdecomatrixnew_ana_OO2025.EffFileName = cms.string('EffFakVsNpixel3D_OO2025.root')
process.epetaptdecomatrixnew_ana_OO2025.FakFileName = cms.string('')
process.epetaptdecomatrixnew_ana_OO2025.EffHistName = cms.string('hCombFit3D')
process.epetaptdecomatrixnew_ana_OO2025.FakHistName = cms.string('')

process.epetaptdecomatrixnew_ana_OO2025_cent01 = process.epetaptdecomatrixnew_ana_OO2025.clone()
process.epetaptdecomatrixnew_ana_OO2025_cent05 = process.epetaptdecomatrixnew_ana_OO2025.clone()
process.epetaptdecomatrixnew_ana_OO2025_cent510 = process.epetaptdecomatrixnew_ana_OO2025.clone()
process.epetaptdecomatrixnew_ana_OO2025_cent1030 = process.epetaptdecomatrixnew_ana_OO2025.clone()
process.epetaptdecomatrixnew_ana_OO2025_cent3050 = process.epetaptdecomatrixnew_ana_OO2025.clone()
process.epetaptdecomatrixnew_ana_OO2025_cent5070 = process.epetaptdecomatrixnew_ana_OO2025.clone()
process.epetaptdecomatrixnew_ana_OO2025_cent01.hfsummin = cms.double(395.659)
process.epetaptdecomatrixnew_ana_OO2025_cent01.hfsummax = cms.double(10000.0)
process.epetaptdecomatrixnew_ana_OO2025_cent05.hfsummin = cms.double(316.984)
process.epetaptdecomatrixnew_ana_OO2025_cent05.hfsummax = cms.double(10000.0)
process.epetaptdecomatrixnew_ana_OO2025_cent510.hfsummin = cms.double(266.531)
process.epetaptdecomatrixnew_ana_OO2025_cent510.hfsummax = cms.double(316.984)
process.epetaptdecomatrixnew_ana_OO2025_cent1030.hfsummin = cms.double(144.623)
process.epetaptdecomatrixnew_ana_OO2025_cent1030.hfsummax = cms.double(266.531)
process.epetaptdecomatrixnew_ana_OO2025_cent3050.hfsummin = cms.double(75.4546)
process.epetaptdecomatrixnew_ana_OO2025_cent3050.hfsummax = cms.double(144.623)
process.epetaptdecomatrixnew_ana_OO2025_cent5070.hfsummin = cms.double(35.624)
process.epetaptdecomatrixnew_ana_OO2025_cent5070.hfsummax = cms.double(75.4546)

process.ana_step_cent01 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_OO2025_cent01)
process.ana_step_cent05 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_OO2025_cent05)
process.ana_step_cent510 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_OO2025_cent510)
process.ana_step_cent1030 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_OO2025_cent1030)
process.ana_step_cent3050 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_OO2025_cent3050)
process.ana_step_cent5070 = cms.Path(process.eventFilter_MB * process.epetaptdecomatrixnew_ana_OO2025_cent5070)

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
