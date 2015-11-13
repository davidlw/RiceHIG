### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'mult_pythia8_dsgen_v3'
#config.General.requestName = 'mult_epos_dsgen_v3'
#config.General.requestName = 'mult_epos_evtsel_v3'
#config.General.requestName = 'mult_pythia8_evtsel_v3'
config.General.requestName = 'mult_pythia8_evtsel_purej_dz01_debug_v5'

config.General.workArea = 'ppMC2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_evtsel_cfg.py'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_evtsel_purej_cfg.py'

config.Data.inputDataset = '/MinBias_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-NoPURecodebug_TrackingParticle_MCRUN2_74_V8B-v2/GEN-SIM-DIGI-RECO'
#config.Data.inputDataset = '/ReggeGribovPartonMC_13TeV-EPOS/RunIISpring15DR74-NoPURawReco_castor_MCRUN2_74_V8B-v1/GEN-SIM-RECO'
#config.Data.inputDataset = '/MinBias_TuneCUETP8M1_13TeV-pythia8/davidlw-RecoSkim_v1-00b3bbd68a41a1bc2b98cf5da8508e09/USER'
#config.Data.inputDBS = 'phys03'
config.Data.totalUnits = 50
config.Data.splitting = 'FileBased'
#config.Data.lumiMask = 'pp2015_lowPU.txt'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
