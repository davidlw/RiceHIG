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
    config.JobType.maxMemoryMB = 2500
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
#    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'LumiBased'
    config.Data.lumiMask = 'json_DCSONLY.txt'
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

    config.General.requestName = 'corrana_pPb2016_pt033_N010_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N010_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N1020_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N1020_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N2030_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N2030_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N3040_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N3040_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N4050_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N4050_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N5060_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N5060_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N6070_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N6070_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N7080_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N7080_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N80100_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N80100_cfg.py'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N100120_run285479_285530_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N100120_cfg.py'
    submit(config)
