### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'epetadeco_cent05_pttrg10inf_ptassallweight_etaass445_eff0_v4'
config.General.workArea = 'HI2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/epetadeco_2015PbPb_cent05_cfg.py'

#config.Data.inputDataset = '/HIMinimumBias1/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias10/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias11/HIRun2015-PromptReco-v1/AOD'
config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias3/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias4/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias5/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias6/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias7/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias8/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIMinimumBias9/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIOniaL1DoubleMu0/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIOniaL1DoubleMu0B/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIOniaL1DoubleMu0C/HIRun2015-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HIOniaL1DoubleMu0D/HIRun2015-PromptReco-v1/AOD'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'json_DCSONLY_2015.txt'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
