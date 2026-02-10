from datetime import datetime
from CRABClient.UserUtilities import config
config = config()

pd_name = "PhysicsHITrackerNZS"
inputList = 'Run399486_emulation.txt'
request_name = 'SoS_Run399486ZEROS1_20251115v1'

config.section_('General')
config.General.workArea = 'crab_projects'
config.General.requestName = request_name
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'SoS_PbPb2023_AOD_ZEROS1_cfg.py'
config.JobType.maxMemoryMB = 1500
#config.JobType.maxJobRuntimeMin = 300
config.JobType.scriptExe = 'submitScript.sh'
config.JobType.inputFiles = ['submitScript.sh']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
config.Data.inputDBS = 'global'
config.Data.userInputFiles = open(inputList).readlines()
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
#config.Data.totalUnits = 3
config.Data.publication = False
config.Data.outputPrimaryDataset = pd_name

config.Data.outLFNDirBase = '/store/group/phys_heavyions/davidlw'

config.section_('Site')
config.Site.whitelist = ['T2_CH_CERN']
config.Site.storageSite = 'T2_CH_CERN'
