### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'dihadroncorrelation_n035_std_v1_seq1'
config.General.workArea = 'pp2015Ana'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_pp2015_n035_cfg.py'

config.Data.inputDataset = '/ZeroBias1/mguilbau-ZeroBias1_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias2/mguilbau-ZeroBias2_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias3/mguilbau-ZeroBias3_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias4/mguilbau-ZeroBias4_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias5/mguilbau-ZeroBias5_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias6/mguilbau-ZeroBias6_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias7/mguilbau-ZeroBias7_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
#config.Data.inputDataset = '/ZeroBias8/mguilbau-ZeroBias8_RecoSkim2015_v3-164e1fce899939eaa6b0e31efc664c2c/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
#config.Data.lumiMask = 'pp2015_lowPU.txt'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
