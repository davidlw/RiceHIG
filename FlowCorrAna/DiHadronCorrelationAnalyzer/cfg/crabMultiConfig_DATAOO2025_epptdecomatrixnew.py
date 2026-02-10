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
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'Cert_Collisions2025OO_394153_394217_golden.json'
#config.Data.lumiMask = 'OO_bin0v1.json'
config.Data.publication = False
config.JobType.allowUndistributedCMSSW = True
config.Data.allowNonValidInputDataset = True

config.section_('Site')
config.Data.ignoreLocality = True
config.Site.whitelist = ['T1_US_*','T2_US_*']
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
#            "HIForward": { "PD": "/HIForward/HIRun2018A-04Apr2019-v1/AOD", "Units": 30, "Memory": 1800, "RunTime": 1400, "PSet": "PbPbSkimAndTree2018_DiMuContBoth_ZDC_ALLDIMU_cfg.py" },
            }

for i in range(8,10):
    dataMap[("IonPhysics"+str(i))] = { "PD": ("/IonPhysics"+str(i)+"/OORun2025-PromptReco-v1/MINIAOD"), "Units": 5, "Memory": 3000, "RunTime": 2400, "PSet": "epptdecomatrixnew_OO2025_pfcand_cfg.py" } 

## Submit the PDs
for key, val in dataMap.items():
    config.General.requestName = 'epptdecomatrixnew_'+key+'_OO2025PR_effv1pu2_20251207v2'
    config.Data.inputDataset = val["PD"]
    config.Data.unitsPerJob = val["Units"]
    config.JobType.maxMemoryMB = val["Memory"]
    config.JobType.maxJobRuntimeMin = val["RunTime"]
    config.JobType.psetName = val["PSet"]
    config.Data.outputDatasetTag = config.General.requestName
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw/' 

    print("Submitting CRAB job for: " + val["PD"])  # updated for Python 3

    submit(config)
