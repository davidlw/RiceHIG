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
   fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov///store/himc/HINPbPbAutumn18DR/MinBias_Hydjet_Drum5F_2018_5p02TeV/AODSIM/NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/120000/0816F843-27D9-A64F-8C27-DA319B780FBB.root')
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

# Define the analysis steps
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.corr_ana_PbPb2018.IsCorr = cms.bool(False)
process.corr_ana_PbPb2018.IsDebug = cms.bool(True)
process.corr_ana_PbPb2018.IsGenMult = cms.bool(True)
process.corr_ana_PbPb2018.IsVtxSel = cms.bool(False)
process.corr_ana_PbPb2018.etatrgmin = cms.double(-1.0)
process.corr_ana_PbPb2018.etatrgmax = cms.double(1.0)
process.corr_ana_PbPb2018.etamultmin = cms.double(-1)
process.corr_ana_PbPb2018.etamultmax = cms.double(1)
process.corr_ana_PbPb2018.pttrgmin = cms.vdouble(0.)
process.corr_ana_PbPb2018.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_PbPb2018.ptmultmin = cms.double(0.)
process.corr_ana_PbPb2018.ptmultmax = cms.double(10000.0)
#process.corr_ana_PbPb2018.ischarge_ass = cms.bool(False)
#process.corr_ana_PbPb2018.IsPtWeightAss = cms.bool(True)
#process.corr_ana_PbPb2018.IsAssEtaCutAbs = cms.bool(True)

process.corr_ana_PbPb2018.EffFileName = cms.string('')
process.corr_ana_PbPb2018.TriggerID = cms.string('GenParticle')
process.corr_ana_PbPb2018.AssociateID = cms.string('GenParticle')

process.ana_step = cms.Path(
process.corr_ana_PbPb2018
)

# Define the output
process.TFileService = cms.Service("TFileService", fileName = cms.string('dihadroncorrelation.root'))

# Define the process schedule
process.schedule = cms.Schedule(
    process.ana_step 
)
