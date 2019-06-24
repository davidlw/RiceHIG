if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'VertexCompositeAna'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.maxMemoryMB = 4000
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N185250_cfg.py'
    config.Data.unitsPerJob = 15
#    config.Data.totalUnits = 2000
    config.Data.splitting = 'LumiBased'
#    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
#    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
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

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b1_v2'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N185250_cfg.py'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'pPb_ptspectra_v2'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b2_v2'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b3_v2'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b4_v2'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b5_v2'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b6_v2'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b0n120_v2'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N120150_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b0n150_v2'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N150185_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_pPbHM_ptspectra_b7_v2'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N250_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_pPbMB_ptspectra_b1_v2'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_MB_cfg.py'
    submit(config)
 
    config.General.requestName = 'pPb2016_pPbTrack_ptspectra_b1_v2'
    config.Data.inputDataset = '/PADTrack1/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_highpt_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_pPbTrack_ptspectra_b2_v2'
    config.Data.inputDataset = '/PADTrack2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b1_v2'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N185250_cfg.py'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'Pbp_ptspectra_v2'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b2_v2'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b3_v2'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b4_v2'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b5_v2'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b6_v2'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b0n120_v2'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N120150_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b0n150_v2'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N150185_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_PbpHM_ptspectra_b7_v2'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_N250_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_PbpMB_ptspectra_b1_v2'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.JobType.psetName = '../cfg/ptspectra_pPb2016_MB_cfg.py'
    config.Data.outputDatasetTag = 'Pbp_ptspectra_v2'
    submit(config)

