### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'task_sp_rc_hf_v9'
config.General.workArea = 'HI2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/scalarprod_mc_cent0100_hf_cfg.py'

config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV_750/twang-Hydjet_Quenched_MinBias_5020GeV_750_HiFall15_step3_20151110-8279ae7c7b9873cb2e7129d3c6d86a22/USER'
#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-266f47bcc90a343001055b934437977e/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
