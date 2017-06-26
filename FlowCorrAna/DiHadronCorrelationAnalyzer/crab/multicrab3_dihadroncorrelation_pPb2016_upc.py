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
#    config.JobType.maxMemoryMB = 3000
#    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'LumiBased'
#    config.Data.lumiMask = 'json_pPb.txt'
#    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = False
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

    config.General.requestName = 'corrana_pPb2016_pt033_mb_pPb_Golden_UpcP_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_mb_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/davidlw-RecoSkim2016_pPb_UpcP_v1-c30a02e27dc3a3a9bbfb7fe4af25783d/USER'
    config.Data.unitsPerJob = 100
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_mb_pPb_Golden_UpcN_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_mb_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/davidlw-RecoSkim2016_pPb_UpcN_v1-796d6328d7086df37d7da1b9e22a6a88/USER'
    config.Data.unitsPerJob = 100
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_mb_Pbp_Golden_UpcP_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_mb_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/davidlw-RecoSkim2016_Pbp_UpcP_v1-c30a02e27dc3a3a9bbfb7fe4af25783d/USER'
    config.Data.unitsPerJob = 100
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_mb_Pbp_Golden_UpcN_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_mb_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/davidlw-RecoSkim2016_Pbp_UpcN_v1-796d6328d7086df37d7da1b9e22a6a88/USER'
    config.Data.unitsPerJob = 100
    submit(config)
