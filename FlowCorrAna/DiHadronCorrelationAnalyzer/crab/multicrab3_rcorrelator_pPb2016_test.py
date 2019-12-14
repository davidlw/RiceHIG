if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'CorrAna'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.allowUndistributedCMSSW = True
#    config.JobType.maxMemoryMB = 3000
#    config.Data.unitsPerJob = 10
#    config.Data.totalUnits = 1000
#    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'LumiBased'
#    config.Data.lumiMask = 'json_pPb.txt'
#    config.Data.lumiMask = 'Cert_285479-286496_HI8TeV_PromptReco_pPbPbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = False
#    config.Site.storageSite = 'T2_US_MIT'
    config.Site.storageSite = 'T3_US_Rice'

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

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM1_pPb_Golden_v2'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.JobType.psetName = '../cfg/rcorrelator_data_pPb_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 40
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM2_pPb_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM3_pPb_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM4_pPb_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM5_pPb_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM6_pPb_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM1_Pbp_Golden_v2'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM2_Pbp_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM3_Pbp_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM4_Pbp_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM5_Pbp_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RCorrelator_pPb2016_pt033_etaass35_N185HM6_Pbp_Golden_v2'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    submit(config)
