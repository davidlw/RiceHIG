### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'lampol_PbPb_sig_cut_v8'
config.General.workArea = 'pprerecoAnaMC'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.maxMemoryMB = 2500
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/lampol_pprereco_n1851000_cfg.py'

#config.Data.inputDataset = '/HIMinimumBias5/davidlw-RecoSkim2015_pprereco_v5-70836070e3530d592901940b96c951fe/USER'
config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV_750/davidlw-RecoSkim2015_pprereco_v5-6a0ec9ce1fc8d0d49fd93e892717c3d0/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2 
config.Data.totalUnits = -1
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.allowNonValidInputDataset = True
config.Site.storageSite = 'T2_US_MIT'
