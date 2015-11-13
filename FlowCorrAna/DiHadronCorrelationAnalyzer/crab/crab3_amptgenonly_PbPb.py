### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'task_v1_pol050_n5001500'

config.General.workArea = 'Gen'
config.General.transferOutputs = True
config.General.transferLogs = False 

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_cfg.py'

config.Data.inputDataset = '/AMPT_PbPb_Gen/davidlw-MB_string_v4-8f4c8eeead3283ef9d84889483e24cb0/USER'
config.Data.inputDBS = 'phys03'
#config.Data.totalUnits = 
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 15 
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
