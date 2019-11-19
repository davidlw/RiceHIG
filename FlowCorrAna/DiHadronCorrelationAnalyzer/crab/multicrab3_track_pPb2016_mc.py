if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'trackAna'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = '../cfg/track_mc_pPb_cfg.py'
#    config.JobType.maxMemoryMB = 2500
    config.Data.unitsPerJob = 1
    config.Data.totalUnits = -1
#    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/'
#    config.Data.publication = True
#    config.Site.storageSite = 'T2_US_MIT'
    config.Site.storageSite = 'T2_CH_CERN'

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

    config.General.requestName = 'track_pPb2016_pPb_mc_v1'
    config.Data.inputDataset = '/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
    submit(config)

    config.General.requestName = 'track_pPb2016_Pbp_mc_v1'
    config.Data.inputDataset = '/ReggeGribovPartonMC_EposLHC_PbP_4080_4080_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
    submit(config)

    config.General.requestName = 'track_hijing_pPb2016_pPb_mc_v1'
    config.Data.inputDataset = '/HIJING_pPb_8160_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
    submit(config)

    config.General.requestName = 'track_hijing_pPb2016_Pbp_mc_v1'
    config.Data.inputDataset = '/HIJING_PbP_8160_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
    submit(config)

    config.General.requestName = 'track_ampt_pPb2016_pPb_mc_v1'
    config.Data.inputDataset = '/AMPT_pPb_8160_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
    submit(config)

    config.General.requestName = 'track_ampt_pPb2016_Pbp_mc_v1'
    config.Data.inputDataset = '/AMPT_PbP_8160_DataBS/pPb816Summer16DR-MB_80X_mcRun2_pA_v4-v2/AODSIM'
    submit(config)
