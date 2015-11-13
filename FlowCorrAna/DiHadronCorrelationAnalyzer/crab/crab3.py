### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'mult_mb_noevtsel_debug_v1_seq10_test'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_mult_noevtsel_cfg.py'

#config.Data.inputDataset = '/ZeroBias1/mguilbau-ZeroBias1_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias/mguilbau-ZeroBias0_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias2/mguilbau-ZeroBias2_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias3/mguilbau-ZeroBias3_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias4/mguilbau-ZeroBias4_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias5/mguilbau-ZeroBias5_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias7/mguilbau-ZeroBias7_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias8/mguilbau-ZeroBias8_RecoSkim2015_v1-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/HighMultiplicity/mguilbau-HM_RecoSkim2015_v1-d139a4b90b297b0d5bd5704da8084410/USER'
#config.Data.inputDataset = '/HighMultiplicity85/davidlw-PromptReco2015_v2-39e7b8be269a53a3b306d6f302d78aa3/USER'
config.Data.inputDataset = '/ZeroBias8/Run2015B-PromptReco-v1/RECO'
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'pp2015_lowPU.txt'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
