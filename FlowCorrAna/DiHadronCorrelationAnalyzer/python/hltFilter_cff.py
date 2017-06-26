import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
hltHM220 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM220.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*','HLT_PAPixelTracks_Multiplicity160_v*','HLT_PAPixelTracks_Multiplicity190_v*']
hltHM220.andOr = cms.bool(True)
hltHM220.throw = cms.bool(False)

hltHM185220 = hltHM220.clone()
hltHM185220.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*','HLT_PAPixelTracks_Multiplicity160_v*']

hltHM150185 = hltHM220.clone()
hltHM150185.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*']

hltHM120150 = hltHM220.clone()
hltHM120150.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*']

hltMB = hltHM220.clone()
hltMB.HLTPaths = ['HLT_PAZeroBiasPixel_SingleTrack_v*']

hltHM100On = hltHM220.clone()
hltHM100On.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*']

hltHM130On = hltHM220.clone()
hltHM130On.HLTPaths = ['HLT_PAPixelTracks_Multiplicity130_v*']

hltHM160On = hltHM220.clone()
hltHM160On.HLTPaths = ['HLT_PAPixelTracks_Multiplicity160_v*']

hltHM190On = hltHM220.clone()
hltHM190On.HLTPaths = ['HLT_PAPixelTracks_Multiplicity190_v*']

hltZBPP13TeV = hltHM220.clone()
hltZBPP13TeV.HLTPaths = ['HLT_ZeroBias_part*_v*']

hltMBPP13TeV = hltHM220.clone()
hltMBPP13TeV.HLTPaths = ['HLT_L1MinimumBiasHF1OR_part*_v*']

hltHM60OnPP13TeV = hltHM220.clone()
hltHM60OnPP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*']

hltHM85OnPP13TeV = hltHM220.clone()
hltHM85OnPP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity85*_v*']

hltHM110OnPP13TeV = hltHM220.clone()
hltHM110OnPP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity110*_v*']

hltHM80105PP13TeV = hltHM220.clone()
hltHM80105PP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_FullTracks_Multiplicity80_v*']

hltHM105135PP13TeV60On = hltHM220.clone()
hltHM105135PP13TeV60On.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','!HLT_PixelTracks_Multiplicity85*_v*']
hltHM105135PP13TeV60On.andOr = cms.bool(False)

hltHM105135PP13TeV85On = hltHM220.clone()
hltHM105135PP13TeV85On.HLTPaths = ['HLT_PixelTracks_Multiplicity85*_v*']

hltHM105135PP13TeV = hltHM220.clone()
hltHM105135PP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*','HLT_FullTracks_Multiplicity100_v*','HLT_FullTracks_Multiplicity80_v*']

hltHM135155PP13TeV = hltHM220.clone()
hltHM135155PP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*','HLT_PixelTracks_Multiplicity110_v*','HLT_FullTracks_Multiplicity100_v*','HLT_FullTracks_Multiplicity80_v*','HLT_FullTracks_Multiplicity130_v*']

hltHM155infPP13TeV = hltHM220.clone()
hltHM155infPP13TeV.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*','HLT_PixelTracks_Multiplicity110_v*','HLT_PixelTracks_Multiplicity135_v*','HLT_FullTracks_Multiplicity100_v*','HLT_FullTracks_Multiplicity80_v*','HLT_FullTracks_Multiplicity130_v*','HLT_FullTracks_Multiplicity150_v*']
