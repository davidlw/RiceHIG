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
#    config.JobType.psetName = '../test/pPbFlowCorrSkimSlim_2016_cfg.py'
#    config.JobType.psetName = '../test/pPbFlowCorrSkimSlim_2016_D0_cfg.py'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_D0_cfg.py'
#    config.Data.unitsPerJob = 20
#    config.Data.unitsPerJob = 40 # for V0 only
    config.Data.unitsPerJob = 2
#    config.Data.totalUnits = 3000
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

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b1_v2'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b2_v2'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b3_v2'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b4_v2'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b5_v2'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b6_v2'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b7_NoPCA_v2'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_NoPCA_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0_b8_v2'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b1_v2'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b2_v2'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b3_v2'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b4_v2'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b5_v2'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b6_v2'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b7_v2'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_D0_b8_v2'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_D0_v2'
    submit(config)
