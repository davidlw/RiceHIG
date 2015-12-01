### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
config.General.requestName = 'FlowVn_1M_allcent_v2'
config.General.workArea = 'HIMinBias2015'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.allowUndistributedCMSSW = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/scalarprod_data_allcent_cfg.py'

config.Data.userInputFiles = list(open('HIMinBias2015_1M.txt'))
config.Data.splitting = 'FileBased'
config.Data.ignoreLocality = False
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
