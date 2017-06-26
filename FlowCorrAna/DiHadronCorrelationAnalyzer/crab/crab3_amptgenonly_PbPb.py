### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'lampol_gen_v1'
#config.General.requestName = 'task_v5_polall_centallv2'

config.General.workArea = 'EPOSGen'
config.General.transferOutputs = True
config.General.transferLogs = False 

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol000_cfg.py'

config.Data.inputDataset = '/EPOS_PbPb5TeV/davidlw-MB_Gen_v1-2ada62739cd61cf20443759fb2c8c82b/USER'
#config.Data.inputDataset = '/AMPT_PbPb_Gen/davidlw-MB_string_v3-8f4c8eeead3283ef9d84889483e24cb0/USER'
#config.Data.inputDataset = '/AMPT_PbPb_5TeV_Gen/davidlw-b8_12_string_v3-5d2cffe8e7bf7d2204de362aa65aa714/USER'
config.Data.inputDBS = 'phys03'
#config.Data.totalUnits = 
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
