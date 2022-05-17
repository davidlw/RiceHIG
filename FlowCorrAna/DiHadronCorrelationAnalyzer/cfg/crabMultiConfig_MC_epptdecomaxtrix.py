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
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.totalUnits = 1000
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
#            "MinBias_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/MinBias_TuneCP5_13TeV_pythia8/RunIILowPUAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM", "Units": 1, "Memory": 4000, "RunTime": 2000, "PSet": "epptdecomatrix_pythia_miniaod_cfg.py" },
#            "QCD_Pt_15to30_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-NoPU_102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM", "Units": 1, "Memory": 5000, "RunTime": 2500, "PSet": "epptdecomatrix_pythia_miniaod_cfg.py" },
            "QCD_Pt_30to50_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-NoPU_102X_upgrade2018_realistic_v15-v1/MINIAODSIM", "Units": 1, "Memory": 5000, "RunTime": 2500, "PSet": "epptdecomatrix_pythia_miniaod_cfg.py" },
            "QCD_Pt_50to80_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-NoPU_102X_upgrade2018_realistic_v15-v1/MINIAODSIM", "Units": 1, "Memory": 5000, "RunTime": 2500, "PSet": "epptdecomatrix_pythia_miniaod_cfg.py" },
#            "MinBias_TuneCP5_13TeV_pythia8": { "PD": "/MinBias_TuneCP5_13TeV_pythia8/RunIILowPUAutumn18DR-102X_upgrade2018_realistic_v15-v1/AODSIM", "Units": 1, "Memory": 4000, "RunTime": 2000, "PSet": "epptdecomatrix_pythia_cfg.py" },
#            "QCD_Pt_15to30_TuneCP5_13TeV_pythia8": { "PD": "/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIIAutumn18DR-NoPU_102X_upgrade2018_realistic_v15_ext1-v2/AODSIM", "Units": 1, "Memory": 4000, "RunTime": 2000, "PSet": "epptdecomatrix_pythia_cfg.py" },
#            "QCD_Pt_30to50_TuneCP5_13TeV_pythia8": { "PD": "/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIAutumn18DR-NoPU_102X_upgrade2018_realistic_v15-v1/AODSIM", "Units": 1, "Memory": 4000, "RunTime": 2000, "PSet": "epptdecomatrix_pythia_cfg.py" },
#            "QCD_Pt_50to80_TuneCP5_13TeV_pythia8": { "PD": "/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIIAutumn18DR-NoPU_102X_upgrade2018_realistic_v15-ext1-v2/AODSIM", "Units": 1, "Memory": 4000, "RunTime": 2000, "PSet": "epptdecomatrix_pythia_cfg.py" },
          }

#for i in range(0,1):
#    dataMap[("HIMinimumBias"+str(i))] = { "PD": ("/HIMinimumBias"+str(i)+"/HIRun2018A-04Apr2019-v1/AOD"), "Units": 7, "Memory": 5000, "RunTime": 2000, "PSet": "epptdecomatrix_PbPb2018_cfg.py" }

## Submit the muon PDs
for key, val in dataMap.items():
    config.General.requestName = 'epptdecomatrix_'+key+'_20210227v1'
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
