from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

# We want to put all the CRAB project directories from the tasks we submit here into one common directory.
# That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
from CRABClient.UserUtilities import config
config = config()

config.section_("General")
config.General.workArea = 'CorrAna'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../cfg/vnptcorr_data_pPb_cfg.py'

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.lumiMask = 'Cert_285479-286496_HI8TeV_PromptReco_pPbPbp_Collisions16_JSON_NoL1T.txt'
config.Data.runRange = '285479-286496'
#config.Data.totalUnits = 100
config.Data.publication = False
config.JobType.allowUndistributedCMSSW = True

config.section_('Site')
#config.Data.ignoreLocality = True
#config.Site.whitelist = ['T1_US_*','T2_US_*','T1_FR_*','T2_FR_*','T2_CH_CERN','T2_BE_*','T1_IT_*']
config.Site.storageSite = 'T3_US_Rice'

def submit(config):
    try:
        crabCommand('submit', config = config, dryrun=False)
    except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
    except ClientException as cle:
        print "Failed submitting task: %s" % (cle)

#############################################################################################
## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
#############################################################################################
dataMap = {}
#for i in range(6,7):
#    dataMap[("PAHighMultiplicity"+str(i)+"_pPb")] = { "PD": ("/PAHighMultiplicity"+str(i)+"/PARun2016C-PromptReco-v1/AOD"), "Units": 5, "Memory": 4000, "RunTime": 2000, "lumiMask": 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt' }
#for i in range(6,7):
#    dataMap[("PAHighMultiplicity"+str(i)+"_Pbp")] = { "PD": ("/PAHighMultiplicity"+str(i)+"/PARun2016C-PromptReco-v1/AOD"), "Units": 5, "Memory": 4000, "RunTime": 2000, "lumiMask": 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt' }

#for i in range(1,9):
#    dataMap[("PAMinimumBias"+str(i)+"_pPb")] = { "PD": ("/PAMinimumBias"+str(i)+"/PARun2016C-PromptReco-v1/AOD"), "Units": 20, "Memory": 3000, "RunTime": 1200, "lumiMask": 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt' }
for i in range(1,21):
    dataMap[("PAMinimumBias"+str(i)+"_Pbp")] = { "PD": ("/PAMinimumBias"+str(i)+"/PARun2016C-PromptReco-v1/AOD"), "Units": 30, "Memory": 3000, "RunTime": 1200, "lumiMask": 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt' }

## Submit the PDs
for key, val in dataMap.items():
    config.General.requestName = 'VertexCompositeTree_'+key+'_PARun2016C_VnPtCorr_20200703'
    config.Data.inputDataset = val["PD"]
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.Data.outputDatasetTag = config.General.requestName
#    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/'
#    config.Data.outLFNDirBase = '/store/group/phys_heavyions/%s/RiceHIN/pPb2016/TREE/%s' % (getUsernameFromSiteDB(), config.General.requestName)
    config.Data.outLFNDirBase = '/store/user/davidlw/'
    print("Submitting CRAB job for: "+val["PD"])
    submit(config)
