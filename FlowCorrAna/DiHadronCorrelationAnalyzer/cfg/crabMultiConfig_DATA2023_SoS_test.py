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

config.section_('Data')
#config.Data.inputDBS = 'global'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
#config.Data.totalUnits = 5000
#config.Data.lumiMask = 'Cert_Collisions2023HI_374288_375823_Golden.json'
#config.Data.runRange = '374288-375823'
config.Data.publication = False
config.JobType.allowUndistributedCMSSW = True
config.Data.allowNonValidInputDataset = True

config.section_('Site')
config.Data.ignoreLocality = True
config.Site.whitelist = ['T1_US_*','T2_US_*','T2_CH_CERN']
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
#            "2023HYBRID1": { "PD": "/HITrackerNZS/anstahll-RECO_Step2_HITrackerNZS_HIRun2023A_v1_AODSIM_2025_11_09-ef3d99e2d1dc508f5aa87e1a4ce8a6af/USER", "Units": 50, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_HYBRID1_cfg.py" },
#            "2023ZEROS1": { "PD": "/HITrackerNZS/anstahll-RECO_Step2_HITrackerNZS_HIRun2023A_v1_AODSIM_2025_11_09-ef3d99e2d1dc508f5aa87e1a4ce8a6af/USER", "Units": 50, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_ZEROS1_cfg.py" },
#            "2024HYBRID1": { "PD": "/HITrackerNZS/anstahll-RECO_Step2_HITrackerNZS_HIRun2024AB_v1_AODSIM_2025_11_09-e65e5fa23aa35bb0244d49f263fedc17/USER", "Units": 60, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_HYBRID1_cfg.py" },
            "2024ZEROS1": { "PD": "/HITrackerNZS/anstahll-RECO_Step2_HITrackerNZS_HIRun2024AB_v1_AODSIM_2025_11_09-e65e5fa23aa35bb0244d49f263fedc17/USER", "Units": 60, "Memory": 1500, "RunTime": 1800, "PSet": "SoS_PbPb2023_AOD_ZEROS1_cfg.py" },
            }

#for i in range(0,1):
#    dataMap[("HIPhysicsRawPrime"+str(i))] = { "PD": ("/HIPhysicsRawPrime"+str(i)+"/HIRun2023A-PromptReco-v2/MINIAOD"), "Units": 25, "Memory": 4000, "RunTime": 2100, "PSet": "SoS_PbPb2023_MINIAOD_cfg.py" } # UCC

## Submit the muon PDs
for key, val in dataMap.items():
    config.General.requestName = 'SoS_'+key+'_nopxlhole_20251114v4'
    config.Data.inputDataset = val["PD"]
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.JobType.psetName = val["PSet"]
    config.Data.outputDatasetTag = config.General.requestName
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw/' 

    print("Submitting CRAB job for: " + val["PD"])  # updated for Python 3

    submit(config)
