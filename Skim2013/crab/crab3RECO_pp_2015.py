### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Test3_RecoSkim2015_v1'
config.General.workArea = 'pp2015Skim'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_MB_singlefile_NoGplus_cfg.py'

config.Data.inputDataset = '/ExpressPhysics/Run2015B-Express-v1/FEVT'
#config.Data.inputDataset = '/ZeroBias1/Run2015B-PromptReco-v1/RECO'
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'pp2015_lowPU.txt'
#config.Data.lumiMask = 'pp2015_251244.txt'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
#config.Data.allowNonValidInputDataset = True
config.Data.publishDataName = 'Test3_RecoSkim2015_v1'
config.Site.storageSite = 'T2_US_MIT'
