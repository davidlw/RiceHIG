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
#config.Data.totalUnits = 5000
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
            "HydjetUCC": { "PD": "/MinBias_UCC_bmax6_Drum5F_5p36TeV_hydjet/HINPbPbSpring23MiniAOD-NoPU_132X_mcRun3_2023_realistic_HI_v9-v2/MINIAODSIM", "Units": 1, "Memory": 5000, "RunTime": 1800, "PSet": "SoS_PbPb2023_MINIAOD_gen_cfg.py" },
            "HydjetMB": { "PD": "/MinBias_Drum5F_5p36TeV_hydjet/HINPbPbSpring23MiniAOD-NoPU_132X_mcRun3_2023_realistic_HI_v9-v2/MINIAODSIM", "Units": 1, "Memory": 5000, "RunTime": 1800, "PSet": "SoS_PbPb2023_MINIAOD_gen_cfg.py" },            
            }

#for i in range(0,1):
#    dataMap[("HIForward"+str(i))] = { "PD": ("/HIForward"+str(i)+"/HIRun2023A-16Jan2024-v1/MINIAOD"), "Units": 25, "Memory": 2000, "RunTime": 1200, "PSet": "dihadroncorrelation_PbPb2023_pfcand_cfg.py" } # UCC

## Submit the PDs
for key, val in dataMap.items():
    config.General.requestName = 'SoS_'+key+'_gen_20250111v1'
    config.Data.inputDataset = val["PD"]
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.JobType.psetName = val["PSet"]
    config.Data.outputDatasetTag = config.General.requestName
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw/' 

    print("Submitting CRAB job for: " + val["PD"])  # updated for Python 3

    submit(config)
