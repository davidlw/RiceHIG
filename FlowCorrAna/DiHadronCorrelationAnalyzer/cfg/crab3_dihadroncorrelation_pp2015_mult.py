### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'dihadroncorrelation_pp2015_MB8_2015C_mult_v1'
#config.General.requestName = 'dihadroncorrelation_pp2015_HM85_2015D_mult_v4'
#config.General.requestName = 'dihadroncorrelation_pp2015_HM60_2015C_mult_v1'
#config.General.requestName = 'dihadroncorrelation_pp2015_HM60_2015B_mult_noHM85_v1'
#config.General.requestName = 'dihadroncorrelation_pp2015_HM85_2015C_mult_v1'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_cfg.py'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_noHM85_cfg.py'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_HM60_noHM85_cfg.py'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_HM85_cfg.py'

#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_v2-266f47bcc90a343001055b934437977e/USER'
#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-266f47bcc90a343001055b934437977e/USER'
config.Data.inputDataset = '/L1MinimumBiasHF8/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
