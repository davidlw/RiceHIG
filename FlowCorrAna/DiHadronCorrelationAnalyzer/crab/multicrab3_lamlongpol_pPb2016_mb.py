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
    config.JobType.psetName = '../cfg/lamlongpol_pPb_mb_cfg.py'
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

    config.General.requestName = 'lamlongpolana_pPb2016_cms_pPb_mb_b1_v6'
    config.JobType.psetName = '../cfg/lamlongpol_cms_pPb_mb_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/davidlw-RecoSkim2016_pPb_V0Cascade_v1-97be9aa52ea60cba5455e64649c12464/USER'
    submit(config)

    config.General.requestName = 'lamlongpolana_pPb2016_cms_Pbp_mb_b1_v6'
    config.JobType.psetName = '../cfg/lamlongpol_cms_Pbp_mb_cfg.py'
    config.Data.inputDataset = '/PAHighMultiplicity1/davidlw-RecoSkim2016_Pbp_V0Cascade_v1-97be9aa52ea60cba5455e64649c12464/USER'
    submit(config)
