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
    config.JobType.maxMemoryMB = 3000
#    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
#    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'LumiBased'
#    config.Data.lumiMask = 'json_pPb.txt'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
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

    config.General.requestName = 'corrana_pPb2016_pt033_N0MB1_pPb_Golden_zvtx-153_v8'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N0MB_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N30MB1_pPb_Golden_zvtx-153_v8'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N30MB_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N60MB1_pPb_Golden_zvtx-153_v8'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N60MB_cfg.py'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N185HM1_pPb_Golden_zvtx-153_v8r1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N185HM16_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N250HM7_pPb_Golden_zvtx-153_v8'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N250HM7_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 20
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N330HM7_pPb_Golden_zvtx-153_v8'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N330HM7_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 120
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N370HM7_pPb_Golden_zvtx-153_v8'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N370HM7_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 1200
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N120HM0_pPb_Golden_zvtx-153_v8r1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N120HM0_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)
