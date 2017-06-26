### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'RecoSkim2015_MB2_2015E5TeV_v6'
config.General.workArea = 'pp2015Skim'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_MB_singlefile_NoGplus_cfg.py'

config.Data.inputDataset = '/MinimumBias2/Run2015E-PromptReco-v1/RECO'
#config.Data.inputDataset = '/HighMultiplicity/Run2015E-PromptReco-v1/RECO'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON.txt'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.outputDatasetTag = 'RecoSkim2015_2015E5TeV_MB2_v6'
config.Site.storageSite = 'T2_US_MIT'
