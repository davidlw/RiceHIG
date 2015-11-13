### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'mult_pythia8_dsgen_v3'
#config.General.requestName = 'mult_epos_dsgen_v3'
#config.General.requestName = 'mult_epos_evtsel_v3'
#config.General.requestName = 'mult_pythia8_evtsel_v3'
config.General.requestName = 'pp13_MB1251000_v1'

config.General.workArea = 'AMPTGen'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/dihadroncorrelation_amptgen_n1251000_cfg.py'

#config.Data.inputDataset = '/AMPT_pp_Gen/davidlw-MB_string_v2-979568b35a762a2522e333301fdcc1a9/USER'
config.Data.inputDataset = '/AMPT_pp_Gen/davidlw-HM95_string_v3-3c78ce595414be7d6fe2f5cc51b09c7a/USER'
config.Data.inputDBS = 'phys03'
#config.Data.totalUnits = 
config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 6 #4095
#config.Data.unitsPerJob = 3 #040
#config.Data.unitsPerJob = 12 #95125
config.Data.unitsPerJob = 40 #1251000
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
