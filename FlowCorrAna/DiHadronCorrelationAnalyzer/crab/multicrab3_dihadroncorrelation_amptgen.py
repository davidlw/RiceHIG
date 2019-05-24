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
    config.Data.totalUnits = -1
    config.Data.inputDBS = 'phys03'
    config.Data.splitting = 'FileBased'
#    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/'
    config.Data.publication = False
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

#    config.General.requestName = 'corrana_amptgen_pPb8TeV_B0_n125_v1'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PPb_8160GeV_B0_batch1_v2-5275a0c25d43c9362adce48773751362/USER'
#    config.JobType.psetName = '../cfg/dihadroncorrelation_amptgen_n1251000_cfg.py'
#    config.Data.unitsPerJob = 20
#    submit(config)

#    config.General.requestName = 'corrana_amptgen_pPb8TeV_B0_all_v1'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PPb_8160GeV_B0_batch1_v2-5275a0c25d43c9362adce48773751362/USER'
#    config.JobType.psetName = '../cfg/dihadroncorrelation_amptgen_mb_cfg.py'
#    config.Data.unitsPerJob = 20
#    submit(config)

#    config.General.requestName = 'corrana_amptgen_piAr1430GeV_mb_v3'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiAr_1430GeV_MinimumBias_test_v1-6ea33dfe0b743538f4cbea7b6302c6a6/USER'
#    config.JobType.psetName = '../cfg/dihadroncorrelation_amptgen_n1201000_cfg.py'
#    config.Data.unitsPerJob = 10
#    submit(config)


#    config.General.requestName = 'corrana_amptgen_piO1850GeV_mb_v3'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiO_1850GeV_MinimumBias_test_v1-3a307c8cee17f20c8de8f5dae9de544d/USER'
#    config.Data.unitsPerJob = 10
#    submit(config)


#    config.General.requestName = 'corrana_amptgen_piP1500GeV_mb_v3'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiP_1500GeV_MinimumBias_test_v1-48f9a16fcdd34d03efb43bfc627ba685/USER'
#    config.Data.unitsPerJob = 10
#    submit(config)

#    config.General.requestName = 'corrana_amptgen_piPb950GeV_mb_v3'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiPb_950GeV_MinimumBias_test_v1-ce935f3d385aab9a6795f2c1d76b7ba3/USER'
#    config.Data.unitsPerJob = 10
#    submit(config)


    config.General.requestName = 'corrana_amptgen_piAu110GeV_mb_v4'
    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiAu_110GeV_MinimumBias_test_v1-beaf35aa4206534b59a30ed527ade76b/USER'
    config.JobType.psetName = '../cfg/dihadroncorrelation_amptgen_cfg.py'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'corrana_amptgen_piAu90GeV_mb_v4'
    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiAu_90GeV_MinimumBias_test_v1-fa17c9dc8ba14c1cb29e0199fa6b954a/USER'
    config.Data.unitsPerJob = 5
    submit(config)

    config.General.requestName = 'corrana_amptgen_piAu65GeV_mb_v4'
    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiAu_65GeV_MinimumBias_test_v1-257f75a4872315dad87efadb8b9cec49/USER'
    config.Data.unitsPerJob = 5
    submit(config)

#    config.General.requestName = 'corrana_amptgen_pPb8TeV_n125_v1'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PPb_8160GeV_MinimumBias_batch1_v1-3cd8c63f33222e5ba4742c1e2f4f2366/USER'
#    config.Data.unitsPerJob = 20
#    submit(config)

#    config.General.requestName = 'corrana_amptgen_piPb8TeV_n125_v1'
#    config.Data.inputDataset = '/AMPT_GenOnly/davidlw-AMPT_PiPb_8160GeV_MinimumBias_batch1_v1-4e3f823d363d09ddebf04f1c9c36b82c/USER'
#    config.Data.unitsPerJob = 20
#    submit(config)
