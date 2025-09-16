RiceHIG
=======

Repository for analysis codes of Rice heavy ion physics group

Instructions on running two-particle correlation analysis on 2025 OO data:

- cmsrel CMSSW_15_0_8
- cd CMSSW_15_0_8/src
- cmsenv
- git clone -b CMSSW_15X_Run3 https://github.com/davidlw/RiceHIG
- mv RiceHIG/FlowCorrAna ./
- scram b -j6
- cd FlowCorrAna/DiHadronCorrelationAnalyzer/cfg
- voms-proxy-init --voms cms
- cmsRun dihadroncorrelation_OO2025_pfcand_cfg.py
 

To run crab jobs:

- source /cvmfs/cms.cern.ch/common/crab-setup.csh
- python3 crabMultiConfig_DATA2025_dihadroncorrelation.py 
