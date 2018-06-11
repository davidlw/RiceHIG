if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'CorrAnaMB'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
#    config.JobType.maxMemoryMB = 3000
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_JPsi_cfg.py'
    config.Data.unitsPerJob = 10
#    config.Data.totalUnits = 100
    config.Data.splitting = 'LumiBased'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = True
    config.Site.storageSite = 'T2_US_MIT'
#    config.Site.storageSite = 'T3_US_Rice'

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

    config.General.requestName = 'pPb2016_pPb_Skim_JPsi_b1_v2'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_pPb_b1.json'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_JPsi_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_JPsi_b2_v2'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_pPb_b2.json'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_JPsi_b5_v2'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_pPb_b5.json'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_JPsi_b6_v2'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_pPb_b6.json'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_b1_v2'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_Pbp_b1.json'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_JPsi_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_b2_v2'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_Pbp_b2.json'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_b5_v3'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_Pbp_b5.json'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_b13_v2'
    config.Data.inputDataset = '/PAMinimumBias13/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_Pbp_b13.json'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_b18_v2'
    config.Data.inputDataset = '/PAMinimumBias18/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_Pbp_b18.json'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_b19_v2'
    config.Data.inputDataset = '/PAMinimumBias19/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'notFinishedLumis_Pbp_b19.json'
    submit(config)
