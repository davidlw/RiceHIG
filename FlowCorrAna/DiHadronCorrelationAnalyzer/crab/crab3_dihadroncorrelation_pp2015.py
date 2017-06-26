### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = '2015E_n130150_had_incl_v5_test'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.maxMemoryMB = 2500
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_had_n130150_incl_cfg.py'

config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015E5TeV_HM_v6-befba58f8a32dcd47f4a079ba9e47d7f/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 15
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
