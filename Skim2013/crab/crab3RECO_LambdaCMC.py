### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'LambdaCMC_KsP_v1'
#config.General.requestName = 'LambdaCMC_LamPi_v1'
config.General.workArea = 'LambdaCMC'
config.General.transferOutputs = True
config.General.transferLogs = False

config.Data.inputDBS = 'phys03'
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_LambdaC_MC_cfg.py'
config.Data.inputDataset = '/Pythia8_8160GeV_LambdaC_KsProton/zhchen-Pythia8_8160GeV_LambdaC_KsProton_AODSIM_v5-batch1_NoPAngle_NoDL-517fbb26312f777f94848083dc6dc607/USER'
#config.Data.inputDataset = '/Pythia8_8160GeV_LambdaC_LambdaPion/zhchen-Pythia8_8160GeV_LambdaC_LambdaPion_AODSIM_v5-batch1_NoPAngle_NoDL-517fbb26312f777f94848083dc6dc607/USER'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
#config.Data.allowNonValidInputDataset = True
config.Data.outputDatasetTag = 'LambdaCMC_KsP_v1'
#config.Data.outputDatasetTag = 'LambdaCMC_LamPi_v1'
config.Site.storageSite = 'T2_US_MIT'
