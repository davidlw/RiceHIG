import FWCore.ParameterSet.Config as cms

from TrackingCode.pileUpFilter.pileUpFilter_cff import *
from HeavyIonsAnalysis.Configuration.collisionEventSelection_cff import *

PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True),   # otherwise it won't filter the events
)

#Reject beam scraping events standard pp configuration
NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

PAcollisionEventSelection = cms.Sequence(
                                         hfCoincFilter *
                                         PAprimaryVertexFilter *
                                         NoScraping 
                                       #  *~pileUpFilter_pPb8TeV_vtx1
#                                         *pileUpFilter_pPb8TeV_Gplus
                                         *olvFilter_pPb8TeV_dz1p0
                                         )
