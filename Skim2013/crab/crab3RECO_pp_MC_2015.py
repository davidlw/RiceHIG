### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'RecoSkim2015_v1'
config.General.workArea = 'ppMC2015Skim'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_MB_singlefile_NoGplus_MC_cfg.py'

config.Data.inputDataset = '/ReggeGribovPartonMC_13TeV-EPOS/RunIISpring15DR74-NoPURawReco_castor_MCRUN2_74_V8B-v1/GEN-SIM-RECO'
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
#config.Data.lumiMask = 'pp2015_lowPU.txt'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
#config.Data.allowNonValidInputDataset = True
config.Data.publishDataName = 'RecoSkim2015_v1'
config.Site.storageSite = 'T2_US_MIT'
