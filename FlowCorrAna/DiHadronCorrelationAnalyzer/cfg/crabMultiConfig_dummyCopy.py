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

config.section_('Data')
config.Data.inputDBS = 'global'
#config.Data.splitting = 'LumiBased'
config.Data.splitting = 'FileBased'
config.Data.totalUnits = 1
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
config.Data.runRange = '304899-304906'
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
            "XeXe_ZB": { "PD": "/HIZeroBias/XeXeRun2017-13Dec2017-v1/AOD", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },

#            "Hydjet_Drum5F_2018_5p02TeV": { "PD": "/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbAutumn18DR-NoPUmva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
#            "MinBias_TuneCP5_13TeV_pythia8": { "PD": "/MinBias_TuneCP5_13TeV_pythia8/RunIILowPUAutumn18DR-102X_upgrade2018_realistic_v15-v1/AODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
#            "MinBias_TuneCUETP8M1_13TeV_pythia8": { "PD": "/MinBias_TuneCUETP8M1_13TeV-pythia8/RunIISummer16DR80-NoPU_80X_mcRun2_asymptotic_v14-v1/AODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
#            "QCD_Pt_15to30_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-NoPU_102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
#            "QCD_Pt_30to50_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-NoPU_102X_upgrade2018_realistic_v15-v1/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
#            "QCD_Pt_50to80_TuneCP5_13TeV_pythia8_miniaod": { "PD": "/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIIAutumn18MiniAOD-NoPU_102X_upgrade2018_realistic_v15-v1/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
#            "QCD_Pt_15to30_TuneCP5_13TeV_pythia8_miniaodUL": { "PD": "/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAOD-106X_upgrade2018_realistic_v11_L1v1-v2/MINIAODSIM", "Units": 1, "Memory": 1800, "RunTime": 1400, "PSet": "dummyCopy_cfg.py" },
          }

#/MinBias_TuneCP5_13TeV_pythia8/RunIILowPUAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM

## Submit the PDs
for key, val in dataMap.items():
    config.General.requestName = 'TestSample_'+key+''
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