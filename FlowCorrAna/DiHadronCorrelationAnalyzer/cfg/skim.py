import FWCore.ParameterSet.Config as cms

# Define the process
process = cms.Process("SKIM")

# Load the default configuration for services
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

# Define the number of events (-1 means all events)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input files (replace with your dataset or input file)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd-cms.infn.it//store/hidata/HIRun2023A/HIForward0/MINIAOD/16Jan2024-v1/2810000/3151fd93-8b9b-40ea-9275-826a3977638c.root'  # Replace with your input file
    )
)

# Add trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltFilter.andOr = cms.bool(True)
process.hltFilter.throw = cms.bool(False)
process.hltFilter.HLTPaths = [
    # photo-nuclear
#    'HLT_HIUPC_ZDC1nAsymXOR_MBHF*AND_PixelTrackMultiplicity*_v*'
#    'HLT_HIMinimumBiasHF1ANDZDC1nOR_*', # MinimumBias
#     'HLT_HIUPC_ZDC1nAsymXOR_MBHF1AND_PixelTrackMultiplicity20_v*',
#     'HLT_HIUPC_ZDC1nXOR_MBHF1AND_PixelTrackMultiplicity20_v*',
     'HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v*',
     'HLT_HIUPC_ZDC1nOR_MinPixelCluster400_MaxPixelCluster10000_v*',
]

# Output module
process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('skimmed_output_zdcor.root'),  # Output file name
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('filterPath')  # Select only events that pass the trigger filter
    )
)

# Define the path for the trigger filter
process.filterPath = cms.Path(process.hltFilter)

# End path for output
process.end = cms.EndPath(process.output)

# Configure the MessageLogger for verbosity (optional)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
