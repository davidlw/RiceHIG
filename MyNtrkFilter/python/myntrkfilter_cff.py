import FWCore.ParameterSet.Config as cms

from RiceHIG.MyNtrkFilter.myntrkfilter_cfi import *
from RiceHIG.MyNtrkFilter.hltFilter_cff import *

ntrk185220 = ntrkfilter.clone()
ntrk185220.nMultMin = cms.int32(185)
ntrk185220.nMultMax = cms.int32(220)

ntrk185220_PA = cms.Sequence(hltHM185220PA*ntrk185220)
