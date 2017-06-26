### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'multana_hydjet_v3'
config.General.workArea = 'MultiplicityAna'
config.General.transferOutputs = True
config.General.transferLogs = False

#config.JobType.maxMemoryMB = 2500
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/multiplicityanalyzer_mc_cfg.py'

#config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV_750/davidlw-ppRECO_std_v3-b19fc96d6ecc5870a54312d2edbb74e0/USER'
#config.Data.inputDataset = '/EPOS_PbPb5TeV/davidlw-Cent30100_DIGI-RECO_v1-d1b7f9a11ac0f50a520ee8a635252e33/USER'
config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV_750/gsfs-Hydjet_30_100_w_pp_RECO_20160724-8b7c2d63f6cfb8f7bc91cc78d10289ff/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 100
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
