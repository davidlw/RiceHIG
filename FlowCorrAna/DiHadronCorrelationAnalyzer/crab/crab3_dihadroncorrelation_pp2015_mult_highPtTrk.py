### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'dihadroncorrelation_pp2015_highPtTrk_mult_run262273_v1'
config.General.requestName = 'test_centrality_run263322_v2'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_highPtTrk_cfg.py'

#config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
config.Data.inputDataset = '/HIExpressPhysics/HIRun2015-Express-v1/FEVT'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.lumiMask = 'HIExpress2015_run263322.txt'
#config.Data.runRange = '263234-263234'
#config.Data.runRange = '262273-262273'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
