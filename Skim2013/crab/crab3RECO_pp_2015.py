### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

#config.General.requestName = 'RecoSkim2015_ZB_2015C_NoV0_v2'
#config.General.requestName = 'RecoSkim2015_MB_2015CLowPU_NoV0_batch8_v3'
#config.General.requestName = 'RecoSkim2015_HM85_2015C_NoV0_v2'
#config.General.requestName = 'RecoSkim2015_HM85_2015B_v4'
#config.General.requestName = 'RecoSkim2015_HM85_2015C_run255031_v4'
#config.General.requestName = 'RecoSkim2015_HM_2015D_v4'
#config.General.requestName = 'RecoSkim2015_MB_2015D_batch8_v4'
#config.General.requestName = 'RecoSkim2015_MB_2015C_batch8_v4'
config.General.requestName = 'RecoSkim2015_ZeroBias_2015B_batch8_v4'
config.General.workArea = 'pp2015Skim'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
#config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_ZB_singlefile_NoGplus_cfg.py'
#config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_MB_singlefile_NoGplus_cfg.py'
#config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_HM_singlefile_NoGplus_cfg.py'
#config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_HM_singlefile_NoGplus_ReTracking_cfg.py'
#config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_MB_singlefile_NoGplus_ReTracking_cfg.py'
config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_ZB_singlefile_NoGplus_ReTracking_cfg.py'

#config.Data.inputDataset = '/ZeroBias1/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias2/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias3/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias4/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias5/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias6/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias7/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/ZeroBias8/Run2015B-05Aug2015-v1/RECO'

config.Data.inputDataset = '/ZeroBias8/Run2015B-PromptReco-v1/RECO'

#config.Data.inputDataset = '/ZeroBias1/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias2/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias3/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias4/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias5/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias6/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias7/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ZeroBias8/Run2015C-PromptReco-v1/RECO'

#config.Data.inputDataset = '/L1MinimumBiasHF1/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF2/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF3/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF4/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF5/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF6/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF7/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/L1MinimumBiasHF8/Run2015C-PromptReco-v1/RECO'

#config.Data.inputDataset = '/L1MinimumBiasHF8/Run2015D-PromptReco-v4/RECO'
#config.Data.inputDataset = '/HighMultiplicity85/Run2015B-16Oct2015-v1/RECO'
#config.Data.inputDataset = '/HighMultiplicity/Run2015C_25ns-05Oct2015-v1/RECO'
#config.Data.inputDataset = '/HighMultiplicity85/Run2015C_25ns-05Oct2015-v1/RECO'
#config.Data.inputDataset = '/HighMultiplicity/Run2015D-PromptReco-v4/RECO'
#config.Data.inputDataset = '/HighMultiplicity/Run2015B-05Aug2015-v1/RECO'
#config.Data.inputDataset = '/HighMultiplicity85/Run2015B-22Jul2015-v1/RECO'
#config.Data.inputDataset = '/HighMultiplicity85/Run2015C-PromptReco-v1/RECO'
#config.Data.inputDataset = '/ExpressPhysics/Run2015B-Express-v1/FEVT'
#config.Data.inputDataset = '/ZeroBias1/Run2015B-PromptReco-v1/RECO'
#config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = 'pp2015_lowPU.txt'
#config.Data.lumiMask = 'json_DCSONLY.txt'
#config.Data.lumiMask = 'json_DCSONLY_lowPU25ns.txt'
#config.Data.lumiMask = 'Cert_259152-259431_13TeV_PromptReco_Collisions15_25ns_Totem_JSON.txt'
#config.Data.lumiMask = 'json_255031.txt'
#config.Data.lumiMask = 'Cert_254986-255031_13TeV_PromptReco_Collisions15_LOWPU_25ns_JSON.txt'
config.Data.lumiMask = 'Cert_246908-252126_13TeV_PromptReco_Collisions15_LOWPU_50ns_JSON.txt'
config.Data.unitsPerJob = 4
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
#config.Data.allowNonValidInputDataset = True
config.Data.publishDataName = 'RecoSkim2015_2015BLowPU_ZB_ReTracking_v4'
#config.Data.publishDataName = 'RecoSkim2015_2015CLowPU_ReTracking_v4'
#config.Data.publishDataName = 'RecoSkim2015_2015DLowPU_ReTracking_v4'
config.Site.storageSite = 'T2_US_MIT'
