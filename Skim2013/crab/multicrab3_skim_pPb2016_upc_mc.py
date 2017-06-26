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
    config.Data.inputDataset = '/ReggeGribovPartonMC_EposLHC_pPb_4080_4080/pPb816Summer16DR-80X_mcRun2_asymptotic_v17-v1/AODSIM'
    config.Data.unitsPerJob = 2
    config.Data.totalUnits = -1
    config.Data.splitting = 'FileBased'
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

    config.General.requestName = 'RecoSkim2016_pPb_UpcP_mc_b1_v1'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_UpcP_v1'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_UPC_P_2016_cfg.py'
    submit(config)

    config.General.requestName = 'RecoSkim2016_pPb_UpcN_mc_b1_v1'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_UpcN_v1'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_UPC_N_2016_cfg.py'
    submit(config)
