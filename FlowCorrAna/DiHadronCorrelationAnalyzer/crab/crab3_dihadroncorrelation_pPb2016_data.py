### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'corrana_pPb2016_mult_run285479_285530_v1'
#config.General.requestName = 'corrana_pPb2016_ridge_N300inf_v3'
config.General.workArea = 'CorrAna'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.maxMemoryMB = 2500
config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_cfg.py'
config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_mult_cfg.py'

config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
#config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
#config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
#config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 100
config.Data.lumiMask = 'json_DCSONLY.txt'
#config.Data.runRange = '285216'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
