if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'LamPolAna'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = '../cfg/lamlongpol_pPb_mc_cfg.py'
#    config.JobType.maxMemoryMB = 2500
    config.Data.unitsPerJob = 1
    config.Data.totalUnits = -1
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
    config.Data.useParent = True
#    config.Data.lumiMask = 'json_DCSONLY.txt'
#    config.Data.lumiMask = 'json_run285537_285549.txt'
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

    config.General.requestName = 'lamlongpolana_pPb2016_cms_pPb_mc_v1'
    config.JobType.psetName = '../cfg/lamlongpol_cms_pPb_mc_cfg.py'
    config.Data.inputDataset = '/ReggeGribovPartonMC_EposLHC_pPb_4080_4080_DataBS/davidlw-RecoSkim2016_pPb_V0_v1-2fc6918bc3c19ca88eae36cad5440243/USER'
    submit(config)

    config.General.requestName = 'lamlongpolana_pPb2016_cms_Pbp_mc_v1'
    config.JobType.psetName = '../cfg/lamlongpol_cms_Pbp_mc_cfg.py'
    config.Data.inputDataset = '/ReggeGribovPartonMC_EposLHC_PbP_4080_4080_DataBS/davidlw-RecoSkim2016_Pbp_V0_v1-2fc6918bc3c19ca88eae36cad5440243/USER'
    submit(config)
