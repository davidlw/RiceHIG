from datetime import datetime
from CRABClient.UserUtilities import config
config = config()

inputList = 'filelist_HIPhysicsRawPrime1.txt'
pd_name = "HIPhysicsRawPrime1"
#request_name += '_%s' % datetime.now().strftime('%y%m%d_%H%M%S')
request_name = 'SoS_'+pd_name+'_HIRun2023_PromptReco_MBZDCOREffv6b_tight_20250112v1'

config.section_('General')
config.General.workArea = 'crab_projects'
config.General.requestName = request_name
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'SoS_PbPb2023_MINIAOD_cfg.py'
#config.JobType.psetName = 'dihadroncorrelation_PbPb2023_pfcand_cfg.py'
config.JobType.maxMemoryMB = 3000
#config.JobType.maxJobRuntimeMin = 300
config.JobType.scriptExe = 'submitScript.sh'
config.JobType.inputFiles = ['emap_2023_newZDC_v3.txt']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.userInputFiles = open(inputList).readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 400
config.Data.publication = False
config.Data.outputPrimaryDataset = pd_name

config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw'

config.section_('Site')
#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_CH_CERN'
