### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'epetadecomatrix_ucc_pttrg033_ptass033_eff1_etabin02_golden_v5'
config.General.workArea = 'HI2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.maxMemoryMB = 2800
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/epetadecomatrix_2015PbPb_ucc_cfg.py'

config.Data.inputDataset = '/HIFlowCorr/HIRun2015-25Aug2016-v1/AOD'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = 'Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
config.Data.lumiMask = 'Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.unitsPerJob = 7
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
