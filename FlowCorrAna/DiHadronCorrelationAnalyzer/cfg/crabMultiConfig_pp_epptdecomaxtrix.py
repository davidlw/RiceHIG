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
#config.JobType.inputFiles = ['HeavyIonRPRcd_PbPb2018_offline.db']

config.section_('Data')
config.Data.splitting = 'LumiBased'
#config.Data.totalUnits = 10
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/5TeV/ReReco/Cert_306546-306826_5TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.inputDBS = 'global'
config.Data.publication = False
config.JobType.allowUndistributedCMSSW = True
config.Data.allowNonValidInputDataset = True

config.section_('Site')
config.Data.ignoreLocality = True
config.Site.whitelist = ['T1_US_*','T2_US_*','T1_FR_*','T2_FR_*','T2_CH_CERN']
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
            "ZB1_Run2017G_17Nov2017_miniaod": { "PD": "/HIZeroBias1/Run2017G-17Nov2017-v1/MINIAOD", "Units": 10, "Memory": 5000, "RunTime": 2500, "PSet": "epptdecomatrix_pp_miniaod_cfg.py" },
          }

#for i in range(0,1):
#    dataMap[("HIMinimumBias"+str(i))] = { "PD": ("/HIMinimumBias"+str(i)+"/HIRun2018A-04Apr2019-v1/AOD"), "Units": 7, "Memory": 5000, "RunTime": 2000, "PSet": "epptdecomatrix_PbPb2018_cfg.py" }

## Submit the muon PDs
for key, val in dataMap.items():
    config.General.requestName = 'epptdecomatrix_'+key+'_20210309v2'
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
