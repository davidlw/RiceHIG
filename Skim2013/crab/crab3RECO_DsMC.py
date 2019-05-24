### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'DsMC_KsK_v4'
config.General.workArea = 'DsMC'
config.General.transferOutputs = True
config.General.transferLogs = False

config.Data.inputDBS = 'phys03'
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_DS_MC_cfg.py'
config.Data.inputDataset = '/Pythia8_8160GeV_Ds_KsKaon/zhchen-Pythia8_8160GeV_Ds_KsKaon_AODSIM_v1-batch1-517fbb26312f777f94848083dc6dc607/USER'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
#config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'DsMC_KsK_v4'
config.Site.storageSite = 'T2_US_MIT'