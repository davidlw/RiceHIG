### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'RecoSkim2016_2016H_MD34_MB0_v3'
config.General.requestName = 'RecoSkim2016_2016H_MD34_HM_v3_rescure2'
#config.General.requestName = 'RecoSkim2016_2016G_MD2Run279489_HM_v3'
#config.General.requestName = 'RecoSkim2016_2016G_MD2Run279489_MB9_v1'
#config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB0_v1'
#config.General.requestName = 'RecoSkim2016_2016B_VdMScan_HM_v3'
config.General.workArea = 'pp2016Skim'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.maxMemoryMB = 3000
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_HM_singlefile_NoGplus_cfg.py'

#config.Data.inputDataset = '/HighMultiplicityEOF/Run2016G-23Sep2016-v1/AOD'
#config.Data.inputDataset = '/L1MinimumBias9/Run2016G-PromptReco-v1/AOD'
#config.Data.inputDataset = '/L1MinimumBias0/Run2016B-PromptReco-v2/RECO'
#config.Data.inputDataset = '/HighMultiplicityEOF/Run2016B-PromptReco-v2/AOD'
config.Data.inputDataset = '/HighMultiplicityEOF/Run2016H-PromptReco-v2/AOD'
#config.Data.inputDataset = '/L1MinimumBias0/Run2016H-PromptReco-v2/AOD'

#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'notFinishedLumis.json'
#config.Data.lumiMask = 'json_lowPU_MD.txt'
#config.Data.lumiMask = 'Cert_271036-274240_13TeV_PromptReco_Collisions16_JSON_LowPU.txt'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
#config.Data.outputDatasetTag = 'RecoSkim2016_2016H_MD34_MB0_v3'
config.Data.outputDatasetTag = 'RecoSkim2016_2016H_MD34_HM_v3'
#config.Data.outputDatasetTag = 'RecoSkim2016_2016G_MD2Run279489_HM_v3'
#config.Data.outputDatasetTag = 'RecoSkim2016_2016G_MD2Run279489_MB9_v1'
#config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB0_v1'
#config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_HM_v3'
config.Site.storageSite = 'T2_US_MIT'
#config.Site.blacklist = ['T2_US_Caltech']
