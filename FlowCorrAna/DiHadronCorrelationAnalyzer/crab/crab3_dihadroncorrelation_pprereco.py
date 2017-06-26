### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'test1'
config.General.workArea = 'pprerecoAna'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.maxMemoryMB = 2500
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_2015PbPb_pprereco_cfg.py'

config.Data.inputDataset = '/RelValRunHI2015Periph/CMSSW_7_5_8_patch4-PU_75X_dataRun2_PromptHI_v3_testHIPeriph_RelVal_hi2015Periph-v5/AOD'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
