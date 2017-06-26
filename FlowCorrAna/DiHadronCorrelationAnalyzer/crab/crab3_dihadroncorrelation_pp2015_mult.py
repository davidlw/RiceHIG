### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'dihadroncorrelation_pp2015_HM_2015E_mult_v3'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_cfg.py'

config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015E5TeV_HM_v6-befba58f8a32dcd47f4a079ba9e47d7f/USER'
#config.Data.inputDataset = '/MinimumBias2/davidlw-RecoSkim2015_2015E5TeV_MB2_v6-b72b96dd85007877c6f44f47d661a92b/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
