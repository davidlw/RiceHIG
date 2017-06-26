if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'Gen'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.maxMemoryMB = 2500
    config.JobType.pluginName = 'Analysis'
    config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-b812_string_batch2-5d2cffe8e7bf7d2204de362aa65aa714/USER'
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
    config.Data.unitsPerJob = 10
    config.Data.totalUnits = -1
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

#    config.General.requestName = 'lampol_p001_s000_b812_pttrg065_etaass35_pteff2_batch2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol000_cfg.py'
#    submit(config)

#    config.General.requestName = 'lampol_p001_s000_b812_pttrg065_etaass35_acc2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol001_cfg.py'
#    submit(config)

#    config.General.requestName = 'lampol_p003_s000_b812_pttrg065_etaass35_acc2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol003_cfg.py'
#    submit(config)

#    config.General.requestName = 'lampol_p005_s000_b812_pttrg065_etaass35_acc2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol005_cfg.py'
#    submit(config)

    config.General.requestName = 'lampol_p010_s000_b812_pttrg065_etaass35_pteff2_batch2_v6'
    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol010_cfg.py'
    submit(config)

#    config.General.requestName = 'lampol_p030_s000_b812_pttrg065_etaass35_acc2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol030_cfg.py'
#    submit(config)

    config.General.requestName = 'lampol_p050_s000_b812_pttrg065_etaass35_pteff2_batch2_v6'
    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol050_cfg.py'
    submit(config)

#    config.General.requestName = 'lampol_p075_s000_b812_pttrg065_etaass35_acc2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol075_cfg.py'
#    submit(config)

#    config.General.requestName = 'lampol_p100_s000_b812_pttrg065_etaass35_acc2_v6'
#    config.JobType.psetName = '../cfg/lampolgen_amptgen_pbpb_pol100_cfg.py'
#    submit(config)

#    config.General.requestName = 'scalarprod_b812_etatrg1_etaass35_v4'
#    config.JobType.psetName = '../cfg/scalarprod_amptgen_pbpb_cfg.py'
#    submit(config)
