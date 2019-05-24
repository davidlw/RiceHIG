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
    config.JobType.psetName = '../test/pPbFlowCorrSkim_2016_JPsi_MC_cfg.py'
    config.Data.unitsPerJob = 5
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

    config.General.requestName = 'pPb2016_pPb_Skim_JPsi_MC_b1_v1'
    config.Data.inputDataset = '/Psi1SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8/pPb816Summer16DR-pPbBst_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_JPsi_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_Psi2S_MC_b1_v1'
    config.Data.inputDataset = '/Psi2SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8/pPb816Summer16DR-pPbBst_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_Psi2S_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_Skim_NPJPsi12S_MC_b1_v1'
    config.Data.inputDataset = '/NonPrPsi1_2SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8/pPb816Summer16DR-pPbBst_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_NPJPsi12S_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_JPsi_MC_b1_v1'
    config.Data.inputDataset = '/Psi1SToMuMu_pTMu-2p5_PbP-Bst_8p16-Pythia8/pPb816Summer16DR-PbPBst_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_JPsi_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_Psi2S_MC_b1_v1'
    config.Data.inputDataset = '/Psi2SToMuMu_pTMu-2p5_PbP-Bst_8p16-Pythia8/pPb816Summer16DR-PbPBst_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_Psi2S_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_Skim_NPJPsi12S_MC_b1_v1'
    config.Data.inputDataset = '/NonPrPsi1_2SToMuMu_pTMu-2p5_PbP-Bst_8p16-Pythia8/pPb816Summer16DR-PbPBst_80X_mcRun2_pA_v4-v1/AODSIM'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_NPJPsi12S_v1'
    submit(config)
