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
config.Data.splitting = 'LumiBased'
#config.Data.totalUnits = 200
config.Data.lumiMask = '/afs/cern.ch/user/d/davidlw/CMSSW/CMSSW_9_4_1/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/Cert_304899-304906_XeXe_PromptReco_Collisions17_JSON.txt'
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
#            "HIDoubleMuon": { "PD": "/HIDoubleMuon/HIRun2018A-04Apr2019-v1/AOD", "Units": 5, "Memory": 2500, "RunTime": 1800, "PSet": "PbPbSkimAndTree2018_DiMuContBoth_ZDC_cfg.py" },
#            "HISingleMuon": { "PD": "/HISingleMuon/HIRun2018A-04Apr2019-v1/AOD", "Units": 5, "Memory": 2500, "RunTime": 1800, "PSet": "PbPbSkimAndTree2018_DiMuContBoth_ZDC_cfg.py" },
#            "HIDoubleMuonPsiPeri": { "PD": "/HIDoubleMuonPsiPeri/HIRun2018A-04Apr2019-v1/AOD", "Units": 5, "Memory": 2500, "RunTime": 1800, "PSet": "PbPbSkimAndTree2018_DiMuContBoth_ZDC_cfg.py" },
#            "HIForward": { "PD": "/HIForward/HIRun2018A-04Apr2019-v1/AOD", "Units": 30, "Memory": 1800, "RunTime": 1400, "PSet": "PbPbSkimAndTree2018_DiMuContBoth_ZDC_ALLDIMU_cfg.py" },
            }

for i in range(1,21):
    dataMap[("HIMinimumBias"+str(i))] = { "PD": ("/HIMinimumBias"+str(i)+"/XeXeRun2017-13Dec2017-v1/AOD"), "Units": 25, "Memory": 4000, "RunTime": 2100, "PSet": "SoS_XeXe2017_AOD_cfg.py" } # UCC

## Submit the muon PDs
for key, val in dataMap.items():
    config.General.requestName = 'SoS_'+key+'_HIRun2017XeXe_13Dec2017_AOD_20230116'
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
