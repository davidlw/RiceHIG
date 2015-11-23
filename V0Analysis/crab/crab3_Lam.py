### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Lam_pPb_MB_v4'
config.General.workArea = 'LamAna'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/lamntanalysis_cfg.py'

config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'
#config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_Rereco_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'
#config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_Reverse_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 4
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
#config.Data.useParent = True
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
