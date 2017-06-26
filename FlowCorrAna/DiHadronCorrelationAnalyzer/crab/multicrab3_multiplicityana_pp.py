if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'MultiplicityAna'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = '../cfg/multiplicityanalyzer_data_cfg.py'
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
    config.Data.unitsPerJob = 5
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

    config.General.requestName = 'multiplicityana_2015B_hm110_v1'
#    config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-266f47bcc90a343001055b934437977e/USER'
#    config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
#    config.Data.inputDataset = '/HighMultiplicity85/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
    config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015BLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b1_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF1/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b2_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF2/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b3_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF3/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b4_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF4/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b5_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF5/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b6_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF6/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b7_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF7/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)

    config.General.requestName = 'multiplicityana_2015D_b8_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF8/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    submit(config)
