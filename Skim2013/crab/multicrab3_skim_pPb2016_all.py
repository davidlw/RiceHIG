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
#    config.JobType.psetName = '../test/pPbFlowCorrSkimSlim_2016_cfg.py'
#    config.JobType.psetName = '../test/pPbFlowCorrSkimSlim_2016_D0_cfg.py'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_D0_cfg.py'
#    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_D0WrongSign_cfg.py'
#    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_D0Both_cfg.py'
#    config.Data.unitsPerJob = 20
#    config.Data.unitsPerJob = 40 # for V0 only
    config.Data.unitsPerJob = 5
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

    config.General.requestName = 'pPb2016_pPb_Skim_DS_b1_v2'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_DS_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_DS_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_DPM_b1_v2'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_DPM_cfg.py'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_DPM_v2'
    submit(config)
