if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'pp2016Skim'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.maxMemoryMB = 2500
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = '../test/ppFlowCorrSkim_trigger2015_MB_singlefile_NoGplus_cfg.py'
    config.Data.unitsPerJob = 3
    config.Data.totalUnits = -1
#    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'LumiBased'
#    config.Data.lumiMask = 'json_lowPU_MD.txt'
    config.Data.lumiMask = 'Cert_271036-274240_13TeV_PromptReco_Collisions16_JSON_LowPU.txt'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = True
    config.Site.storageSite = 'T2_US_MIT'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB0_v3'
    config.Data.inputDataset = '/L1MinimumBias0/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB0_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB1_v3'
    config.Data.inputDataset = '/L1MinimumBias1/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB1_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB2_v3'
    config.Data.inputDataset = '/L1MinimumBias2/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB2_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB3_v3'
    config.Data.inputDataset = '/L1MinimumBias3/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB3_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB4_v3'
    config.Data.inputDataset = '/L1MinimumBias4/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB4_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB5_v3'
    config.Data.inputDataset = '/L1MinimumBias5/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB5_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB6_v3'
    config.Data.inputDataset = '/L1MinimumBias6/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB6_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB7_v3'
    config.Data.inputDataset = '/L1MinimumBias7/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB7_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB8_v3'
    config.Data.inputDataset = '/L1MinimumBias8/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB8_v3'
    submit(config)

    config.General.requestName = 'RecoSkim2016_2016B_VdMScan_MB9_v3'
    config.Data.inputDataset = '/L1MinimumBias9/Run2016B-PromptReco-v2/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_2016B_VdMScan_MB9_v3'
    submit(config)
