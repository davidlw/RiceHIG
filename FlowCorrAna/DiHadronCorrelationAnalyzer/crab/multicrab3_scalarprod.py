if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'HI2015Ana'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.Data.userInputFiles = list(open('HIMinBias2015_1M.txt'))
    config.Data.splitting = 'FileBased'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = False
    config.Data.ignoreLocality = False
    config.Site.storageSite = 'T2_US_MIT'
    config.JobType.allowUndistributedCMSSW = True

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

    config.General.requestName = 'task_cent010_v4'
    config.JobType.psetName = '../cfg/scalarprod_data_cent010_cfg.py'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    submit(config)

    config.General.requestName = 'task_cent1020_v4'
    config.JobType.psetName = '../cfg/scalarprod_data_cent1020_cfg.py'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    submit(config)

    config.General.requestName = 'task_cent2030_v4'
    config.JobType.psetName = '../cfg/scalarprod_data_cent2030_cfg.py'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    submit(config)

    config.General.requestName = 'task_cent3040_v4'
    config.JobType.psetName = '../cfg/scalarprod_data_cent3040_cfg.py'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    submit(config)

    config.General.requestName = 'task_cent4050_v4'
    config.JobType.psetName = '../cfg/scalarprod_data_cent4050_cfg.py'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    submit(config)

    config.General.requestName = 'task_cent5060_v4'
    config.JobType.psetName = '../cfg/scalarprod_data_cent5060_cfg.py'
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    submit(config)
