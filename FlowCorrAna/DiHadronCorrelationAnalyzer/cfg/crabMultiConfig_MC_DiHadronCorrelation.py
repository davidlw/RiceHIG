from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

# We want to put all the CRAB project directories from the tasks we submit here into one common directory.
# That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
from CRABClient.UserUtilities import config
config = config()

config.section_("General")
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.inputFiles = ['HeavyIonRPRcd_PbPb2018_offline.db']

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.totalUnits = 50
config.Data.publication = False
config.JobType.allowUndistributedCMSSW = True
config.Data.allowNonValidInputDataset = True

config.section_('Site')
#config.Data.ignoreLocality = True
#config.Site.whitelist = ['T1_US_*','T2_US_*','T1_FR_*','T2_FR_*','T2_CH_CERN','T2_BE_IIHE']
config.Site.storageSite = 'T2_CH_CERN'

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

dataMap = {
            "MinBias_Hydjet_Drum5F_2018_5p02TeV": { "PD": "/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbAutumn18DR-NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM", "Units": 1, "Memory": 4500, "RunTime": 1800, "PSet": "dihadroncorrelation_PbPb2018_mc_cfg.py" },
#            "MinBias_Hydjet_Drum5F_2018_5p02TeV": { "PD": "/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbAutumn18DR-NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM", "Units": 4, "Memory": 4500, "RunTime": 1800, "PSet": "dihadroncorrelation_PbPb2018_gen_cfg.py" }
            }
#for i in range(0,1):
#    dataMap[("HIMinimumBias"+str(i))] = { "PD": ("/HIMinimumBias"+str(i)+"/HIRun2018A-04Apr2019-v1/AOD"), "Units": 10, "Memory": 2500, "RunTime": 1000, "PSet": "dihadroncorrelation_PbPb2018_cfg.py" }
#    dataMap[("HIMinimumBias"+str(i))] = { "PD": ("/HIMinimumBias"+str(i)+"/HIRun2018A-04Apr2019-v1/AOD"), "Units": 10, "Memory": 1800, "RunTime": 1000, "PSet": "dihadroncorrelation_PbPb2018_UCC_cfg.py" }

## Submit the muon PDs
for key, val in dataMap.items():
#    config.General.requestName = 'DiHadronCorrelation_'+key+'_gen_pt0_20211120'
    config.General.requestName = 'DiHadronCorrelation_'+key+'_mergedtracks_NoCorrDEBUG_UCCpol2v2_20211217'
#    config.General.requestName = 'DiHadronCorrelation_'+key+'_HIRun2018_04Apr2019_generaltracks_20211008'
    config.Data.inputDataset = val["PD"]
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.JobType.psetName = val["PSet"]
    config.Data.outputDatasetTag = config.General.requestName
#    config.Data.outLFNDirBase = '/store/user/davidlw/'
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/' 

    print("Submitting CRAB job for: "+val["PD"])
    submit(config)
