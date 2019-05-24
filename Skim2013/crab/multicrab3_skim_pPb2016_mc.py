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
#    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_MC_cfg.py'
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_D0Both_MC_cfg.py'
    config.Data.unitsPerJob = 2
    config.Data.splitting = 'FileBased'
#    config.Data.inputDBS = 'phys03'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = True
    config.Site.storageSite = 'T2_US_MIT'
#    config.Site.storageSite = 'T3_US_Rice'

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

#    config.General.requestName = 'pPb2016_pPb_Skim_D0Both_MC_b1_v1'
#    config.Data.inputDataset = '/EPOS_pPb_embed_prompt_D0_8160GeV/zhchen-EPOS_pPb_embed_prompt_D0_8160GeV_pt1p2_eta2p4_AOD-SIM-eb0de96e274499c444c51980f0cf37bd/USER'
#    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0Both_v1'
#    submit(config)

#    config.General.requestName = 'pPb2016_pPb_Skim_D0Both_MC_b2_v1'
#    config.Data.inputDataset = '/EPOS_pPb_embed_nonprompt_D0_8160GeV/zhchen-EPOS_pPb_embed_nonprompt_D0_8160GeV_pt1p2_eta2p4_AOD-SIM-eb0de96e274499c444c51980f0cf37bd/USER'
#    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0Both_v1'
#    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_D0Both_MC_b3_v2'
    config.Data.inputDataset = '/PromptD0_D0pT-1p2_pPb-EmbEPOS_8p16_Pythia8/pPb816Summer16DR-pPbEmb_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_D0Both_v2'
    submit(config)


    config.General.requestName = 'pPb2016_pPb_Skim_D0Both_MC_b3_v2'
    config.Data.inputDataset = '/PrmtD0_pThat-0_pT-1_eta-2p4_HydjetCymbMB_5p02-Pythia8/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v14-v1/AODSIM'

