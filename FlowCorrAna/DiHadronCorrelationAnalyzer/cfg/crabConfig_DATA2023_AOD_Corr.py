from datetime import datetime
from CRABClient.UserUtilities import config
config = config()

inputList = 'filelist_HIForward0_AOD.txt'
pd_name = "HIForward0"
#request_name += '_%s' % datetime.now().strftime('%y%m%d_%H%M%S')
request_name = 'Corr_'+pd_name+'_HIRun2023_UPC_AOD_20241016v8'

config.section_('General')
config.General.workArea = 'crab_projects'
config.General.requestName = request_name
config.General.transferOutputs = True
config.General.transferLogs = False

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'UPC_PbPb2023_AOD_cfg.py'
config.JobType.maxMemoryMB = 3500
#config.JobType.maxJobRuntimeMin = 300
config.JobType.scriptExe = 'submitScript.sh'
config.JobType.inputFiles = ['emap_2023_newZDC_v3.txt']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.userInputFiles = open(inputList).readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 3
config.Data.publication = False
config.Data.outputPrimaryDataset = pd_name

config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw'

config.section_('Site')
config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_CH_CERN'
