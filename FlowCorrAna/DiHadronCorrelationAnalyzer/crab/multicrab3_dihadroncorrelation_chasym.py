if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'ChAsym'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.maxMemoryMB = 2500
    config.Data.unitsPerJob = 4
    config.Data.totalUnits = -1
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
#    config.Data.inputDataset = '/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Reverse_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER'
#    config.Data.inputDataset = '/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER'
#    config.Data.inputDataset = '/PAHighPt/davidlw-PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_ReTracking_v18-28b2b9cce04ec3f20baeb96fbd2295a8/USER'
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

#    config.General.requestName = 'chasymdihadroncorrelation_n185220_pprereco_eff_v4'
#    config.JobType.psetName = '../cfg/chasymdihadroncorrelation_pprereco_n185220_cfg.py'
#    config.Data.inputDataset = '/HIMinimumBias5/davidlw-RecoSkim2015_pprereco_v5-70836070e3530d592901940b96c951fe/USER'
#    submit(config)

    config.General.requestName = 'chasymdihadroncorrelation_cent3040_pprereco_eff_v4'
    config.JobType.psetName = '../cfg/chasymdihadroncorrelation_pprereco_cent3040_cfg.py'
    config.Data.inputDataset = '/HIMinimumBias5/davidlw-RecoSkim2015_pprereco_v5-70836070e3530d592901940b96c951fe/USER'
    submit(config)
