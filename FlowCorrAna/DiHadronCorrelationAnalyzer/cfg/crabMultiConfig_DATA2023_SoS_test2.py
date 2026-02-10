from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from http.client import HTTPException  # updated import for Python 3

# We want to put all the CRAB project directories from the tasks we submit here into one common directory.
# That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
from CRABClient.UserUtilities import config
config = config()

#inputList = 'Run399486_emulation.txt'
#inputList = 'Run399465_hybrid.txt'
#inputList = 'Run399466_tecZS.txt'
#inputList = 'Run399467_tectobZS.txt'
inputList = 'Run399471_fullZS.txt'

pd_name = "PhysicsHITrackerNZS"

config.section_("General")
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.scriptExe = 'submitScript.sh'

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.userInputFiles = open(inputList).readlines()
config.Data.splitting = 'FileBased'
config.Data.publication = False
config.JobType.allowUndistributedCMSSW = True
config.Data.allowNonValidInputDataset = True
config.Data.outputPrimaryDataset = pd_name

config.section_('Site')
config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_CH_CERN']
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
#            "Run399486HYBRID1": { "Units": 10, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_HYBRID1_cfg.py" },
#            "Run399486ZEROS1": { "Units": 10, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_ZEROS1_cfg.py" },
            "Run399471FullZS": { "Units": 10, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_STD_cfg.py" },
#            "Run399467tectobZS": { "Units": 10, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_STD_cfg.py" },
#            "Run399466tecZS": { "Units": 10, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_STD_cfg.py" },
#            "Run399465hybrid": { "Units": 10, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_STD_cfg.py" },
          }

#for i in range(0,1):
#    dataMap[("HIPhysicsRawPrime"+str(i))] = { "PD": ("/HIPhysicsRawPrime"+str(i)+"/HIRun2023A-PromptReco-v2/MINIAOD"), "Units": 25, "Memory": 4000, "RunTime": 2100, "PSet": "SoS_PbPb2023_MINIAOD_cfg.py" } # UCC

## Submit the muon PDs
for key, val in dataMap.items():
    config.General.requestName = 'SoS_'+key+'_20251115v1'
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.JobType.psetName = val["PSet"]
    config.Data.outputDatasetTag = config.General.requestName
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw/' 

    print("Submitting CRAB job!")  # updated for Python 3

    submit(config)
