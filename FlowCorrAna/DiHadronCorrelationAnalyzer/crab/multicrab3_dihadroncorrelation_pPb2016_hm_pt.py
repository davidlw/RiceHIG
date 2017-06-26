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
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
#    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'LumiBased'
#    config.Data.lumiMask = 'json_DCSONLY.txt'
    config.Data.lumiMask = 'json_run285537_285549.txt'
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

    config.General.requestName = 'corrana_pPb2016_pt033_N185210_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N185210_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N210230_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N210230_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N230250_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N230250_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N250270_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N250270_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N270300_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N270300_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 20
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N300330_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N300330_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 20
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N330360_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N330360_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 20
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N360400_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N360400_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 20
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N400500_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N400500_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 20
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N120135_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N120135_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N135150_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N135150_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N150160_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N150160_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)

    config.General.requestName = 'corrana_pPb2016_pt033_N160185_run285537_285549_v1'
    config.JobType.psetName = '../cfg/dihadroncorrelation_pPb2016_N160185_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.unitsPerJob = 10
    submit(config)
