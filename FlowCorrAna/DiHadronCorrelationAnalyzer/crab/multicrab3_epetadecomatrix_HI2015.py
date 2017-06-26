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
    config.JobType.psetName = '../cfg/epetadecomatrix_2015PbPb_cent4050_cfg.py'
    config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = 'Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
    config.Data.lumiMask = 'Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
    config.Data.unitsPerJob = 10
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

#config.Data.inputDataset = '/HIMinimumBias1/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias10/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias11/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias3/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias4/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias5/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias6/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias7/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias8/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIMinimumBias9/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIOniaL1DoubleMu0/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIOniaL1DoubleMu0B/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIOniaL1DoubleMu0C/HIRun2015-PromptReco-v1/AOD' done
#config.Data.inputDataset = '/HIOniaL1DoubleMu0D/HIRun2015-PromptReco-v1/AOD'

    config.General.requestName = 'epetadecomatrix_cent4050_pttrg13_ptassallweight_etaass445_eff0_MB2_golden_v4'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'epetadecomatrix_cent4050_pttrg13_ptassallweight_etaass445_eff0_MB3_golden_v4'
    config.Data.inputDataset = '/HIMinimumBias3/HIRun2015-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'epetadecomatrix_cent4050_pttrg13_ptassallweight_etaass445_eff0_MB4_golden_v4'
    config.Data.inputDataset = '/HIMinimumBias4/HIRun2015-PromptReco-v1/AOD'
    submit(config)
