### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'multana_2016G_MD2_mult135155_v10'
#config.General.requestName = 'multana_2016H_MD34_mult80105_v10'
config.General.requestName = 'multana_2016B_VdMScan_mult135155_v10'
config.General.workArea = 'MultiplicityAna'
config.General.transferOutputs = True
config.General.transferLogs = False

#config.JobType.maxMemoryMB = 2500
config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = '../cfg/multiplicityanalyzer_data_n80105_cfg.py'
#config.JobType.psetName = '../cfg/multiplicityanalyzer_data_n105135_cfg.py'
config.JobType.psetName = '../cfg/multiplicityanalyzer_data_n135155_cfg.py'

#config.Data.inputDataset = '/HighMultiplicityEOF/davidlw-RecoSkim2016_2016G_MD2Run279489_HM_v1-120ac2c4f6b9f3699b9331175dcc4953/USER'
config.Data.inputDataset = '/HighMultiplicityEOF/davidlw-RecoSkim2016_2016B_VdMScan_HM_v1-120ac2c4f6b9f3699b9331175dcc4953/USER'
#config.Data.inputDataset = '/HighMultiplicityEOF/davidlw-RecoSkim2016_2016H_MD34_HM_v1-120ac2c4f6b9f3699b9331175dcc4953/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
#config.Data.totalUnits = 100
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
