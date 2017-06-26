### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'RecoSkim2015_pprereco_TrackerOnly_v5'
config.General.workArea = 'PbPb2015Skim'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/PbPbFlowCorrSkim_pprereco_75X_cfg.py'

config.Data.inputDataset = '/HIMinimumBias5/HIRun2015-02May2016-v1/AOD'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = 'missing_golden.json'
#config.Data.lumiMask = 'Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.lumiMask = 'Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
config.Data.unitsPerJob = 2
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'RecoSkim2015_pprereco_TrackerOnly_v5'
config.Site.storageSite = 'T2_US_MIT'
#config.Site.whitelist = ['T2_US_*','T1_US_*']
