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
    config.Data.unitsPerJob = 6
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
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

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b1_v1'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_UpcP_v1'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_UPC_P_2016_cfg.py'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b2_v1'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b3_v1'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b4_v1'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b5_v1'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b6_v1'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b7_v1'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_b8_v1'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b1_v1'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_UpcN_v1'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_UPC_N_2016_cfg.py'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b2_v1'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b3_v1'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b4_v1'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b5_v1'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b6_v1'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b7_v1'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_b8_v1'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b1_v1'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_UpcP_v1'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_UPC_P_2016_cfg.py'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b2_v1'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b3_v1'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b4_v1'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b5_v1'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b6_v1'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b7_v1'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b8_v1'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b9_v1'
    config.Data.inputDataset = '/PAMinimumBias9/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b10_v1'
    config.Data.inputDataset = '/PAMinimumBias10/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b11_v1'
    config.Data.inputDataset = '/PAMinimumBias11/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b12_v1'
    config.Data.inputDataset = '/PAMinimumBias12/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b13_v1'
    config.Data.inputDataset = '/PAMinimumBias13/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b14_v1'
    config.Data.inputDataset = '/PAMinimumBias14/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b15_v1'
    config.Data.inputDataset = '/PAMinimumBias15/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b16_v1'
    config.Data.inputDataset = '/PAMinimumBias16/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b17_v1'
    config.Data.inputDataset = '/PAMinimumBias17/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b18_v1'
    config.Data.inputDataset = '/PAMinimumBias18/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b19_v1'
    config.Data.inputDataset = '/PAMinimumBias19/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcP_b20_v1'
    config.Data.inputDataset = '/PAMinimumBias20/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b1_v1'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_UpcN_v1'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_UPC_N_2016_cfg.py'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b2_v1'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b3_v1'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b4_v1'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b5_v1'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b6_v1'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b7_v1'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b8_v1'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b9_v1'
    config.Data.inputDataset = '/PAMinimumBias9/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b10_v1'
    config.Data.inputDataset = '/PAMinimumBias10/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b11_v1'
    config.Data.inputDataset = '/PAMinimumBias11/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b12_v1'
    config.Data.inputDataset = '/PAMinimumBias12/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b13_v1'
    config.Data.inputDataset = '/PAMinimumBias13/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b14_v1'
    config.Data.inputDataset = '/PAMinimumBias14/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b15_v1'
    config.Data.inputDataset = '/PAMinimumBias15/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b16_v1'
    config.Data.inputDataset = '/PAMinimumBias16/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b17_v1'
    config.Data.inputDataset = '/PAMinimumBias17/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b18_v1'
    config.Data.inputDataset = '/PAMinimumBias18/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b19_v1'
    config.Data.inputDataset = '/PAMinimumBias19/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'RecoSkim2016_Pbp_UpcN_b20_v1'
    config.Data.inputDataset = '/PAMinimumBias20/PARun2016C-PromptReco-v1/AOD'
    submit(config)
