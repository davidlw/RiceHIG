RiceHIG
=======

Repository for analysis codes of Rice heavy ion physics group

Instructions on running two-particle correlation analysis on 2023 PbPb data:

cmsrel CMSSW_13_2_4
cd CMSSW_13_2_4/src
cmsenv
git clone -b CMSSW_13X_Run3 https://github.com/davidlw/RiceHIG
mv RiceHIG/FlowCorrAna ./
scram b -j6
cd FlowCorrAna/DiHadronCorrelationAnalyzer/cfg
voms-proxy-init --voms cms
cmsRun dihadroncorrelation_PbPb2023_pfcand_cfg.py
 

To run crab jobs:

source /cvmfs/cms.cern.ch/common/crab-setup.csh
python3 crabMultiConfig_DATA2023_dihadroncorrelation.py 
