from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from http.client import HTTPException  # updated import for Python 3

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
#config.JobType.inputFiles = ['']

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
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
        print("Failed submitting task: %s" % (hte.headers))  # updated for Python 3

    except ClientException as cle:
        print("Failed submitting task: %s" % (cle))  # updated for Python 3

#############################################################################################
## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
#############################################################################################

dataMap = {
#            "HijingMBMC": { "PD": "/MinBias_OO_5p36TeV_hijing/HINOOSpring25MiniAOD-NoPU_150X_mcRun3_2025_forOO_realistic_v7-v2/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "SoS_OO2025_MINIAOD_mc_cfg.py" },
            "HijingMBGen": { "PD": "/MinBias_OO_5p36TeV_hijing/HINOOSpring25MiniAOD-NoPU_150X_mcRun3_2025_forOO_realistic_v7-v2/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "SoS_OO2025_MINIAOD_gen_cfg.py" },
#            "HijingQCDMC": { "PD": "/QCD-dijet_Pthat-15_TuneCP5_OO_5p36TeV_pythia8/HINOOSpring25MiniAOD-150X_mcRun3_2025_forOO_realistic_v7-v2/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "SoS_OO2025_MINIAOD_mc_cfg.py" },
#            "HijingQCDGen": { "PD": "/QCD-dijet_Pthat-15_TuneCP5_OO_5p36TeV_pythia8/HINOOSpring25MiniAOD-150X_mcRun3_2025_forOO_realistic_v7-v2/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "SoS_OO2025_MINIAOD_gen_cfg.py" },
            }

#for i in range(0,10):
#    dataMap[("IonPhysics"+str(i))] = { "PD": ("/IonPhysics"+str(i)+"/OORun2025-PromptReco-v1/MINIAOD"), "Units": 25, "Memory": 4000, "RunTime": 2100, "PSet": "SoS_OO2025_MINIAOD_cfg.py" } 

## Submit the muon PDs
for key, val in dataMap.items():
    config.General.requestName = 'sosana_'+key+'_OO2025_20251016v3'
    config.Data.inputDataset = val["PD"]
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.JobType.psetName = val["PSet"]
    config.Data.outputDatasetTag = config.General.requestName
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw/' 

    print("Submitting CRAB job for: " + val["PD"])  # updated for Python 3

    # --- important: drop cached pset so a different cfg can be loaded
    import sys
    if 'pset' in sys.modules:
        del sys.modules['pset']

    submit(config)
