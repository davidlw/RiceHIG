### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'task_v2ksDb120150'
#config.General.requestName = 'task_v2ksDb'
#config.General.requestName = 'dihadroncorrelation_pp2015_n1051000_2015D_lambda_v1'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_lam_n120150_cfg.py'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_lam_n120150_sig_cfg.py'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_ks_n120150_sig_cfg.py'
#config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_lam_n120150_bkg_cfg.py'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_ks_n120150_bkg_cfg.py'

#config.Data.inputDataset = '/HighMultiplicity85/davidlw-RecoSkim2015_2015C_NoV0_v2-e014e0b44d2b2810761794155b973e57/USER'
#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015C_NoV0_v2-e014e0b44d2b2810761794155b973e57/USER'
#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015B_NoV0_v2-e014e0b44d2b2810761794155b973e57/USER'
#config.Data.inputDataset = '/HighMultiplicity85/davidlw-RecoSkim2015_2015B_NoV0_v2-e014e0b44d2b2810761794155b973e57/USER'
#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_v2-266f47bcc90a343001055b934437977e/USER'
config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-266f47bcc90a343001055b934437977e/USER'
#config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
#config.Data.inputDataset = '/HighMultiplicity85/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 3 # signal
config.Data.unitsPerJob = 6 # background
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
