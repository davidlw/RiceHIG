#!/bin/bash

export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
scramv1 runtime -sh

# Run the code
cmsRun -j FrameworkJobReport.xml PSet.py
