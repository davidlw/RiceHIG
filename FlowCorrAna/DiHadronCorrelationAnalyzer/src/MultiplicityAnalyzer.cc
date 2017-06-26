#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/MultiplicityAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EventShape.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TObjString.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

MultiplicityAnalyzer::MultiplicityAnalyzer(const edm::ParameterSet& iConfig) :
  hEffWeight(0),
  hTrgWeight(0),
  nMult(0),
  nMultCorr(0),
  nMultGen(0),
  nVertices(0),
  maxofflinetracks(0),
  xVtx(-99999.),
  yVtx(-99999.),
  zVtx(-99999.),	
  xVtxError(99999.),
  yVtxError(99999.),
  zVtxError(99999.)
{
  TH1::SetDefaultSumw2();

  token_vertices = consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("VertexCollection"));
  token_tracks = consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("TrgTrackCollection"));
  token_genparticles = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("GenParticleCollection"));
   
  cutPara.xvtxcenter = iConfig.getParameter<double>("xvtxcenter");
  cutPara.yvtxcenter = iConfig.getParameter<double>("yvtxcenter");
  cutPara.zvtxcenter = iConfig.getParameter<double>("zvtxcenter");
  cutPara.rhomin = iConfig.getParameter<double>("rhomin");
  cutPara.rhomax = iConfig.getParameter<double>("rhomax");
  cutPara.zvtxmin = iConfig.getParameter<double>("zvtxmin");
  cutPara.zvtxmax = iConfig.getParameter<double>("zvtxmax");  
  cutPara.zvtxbin = iConfig.getParameter<double>("zvtxbin");
  cutPara.etamultmin = iConfig.getParameter<double>("etamultmin");
  cutPara.etamultmax = iConfig.getParameter<double>("etamultmax");
  cutPara.ptmultmin = iConfig.getParameter<double>("ptmultmin");
  cutPara.ptmultmax = iConfig.getParameter<double>("ptmultmax");
  cutPara.nvtxmax = iConfig.getParameter<int>("nvtxmax");

  cutPara.IsGenMult = iConfig.getParameter<bool>("IsGenMult");
  cutPara.IsVtxSel = iConfig.getParameter<bool>("IsVtxSel");
  cutPara.IsPPTrkQuality = iConfig.getParameter<bool>("IsPPTrkQuality");
  cutPara.IsHITrkQuality = iConfig.getParameter<bool>("IsHITrkQuality");

  TString eff_filename(iConfig.getParameter<string>("EffFileName")); 
  if(eff_filename.IsNull()) return;
  edm::FileInPath fip(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",eff_filename.Data()));
  TFile f(fip.fullPath().c_str(),"READ");
  hEffWeight = (TH2D*)f.Get("rTotalEff3D");
}

//MultiplicityAnalyzer::~MultiplicityAnalyzer()
//{}

//
// member functions
//

void MultiplicityAnalyzer::beginJob()
{
   Double_t multbins[156] = {0};
   for(int i=0;i<101;i++) multbins[i] = i;
   for(int i=101;i<126;i++) multbins[i] = multbins[100] + (i-100)*2;
   for(int i=126;i<136;i++) multbins[i] = multbins[125] + (i-125)*4;
   for(int i=136;i<140;i++) multbins[i] = multbins[135] + (i-135)*10;
   for(int i=140;i<150;i++) multbins[i] = multbins[139] + (i-139)*20;
   for(int i=150;i<156;i++) multbins[i] = multbins[149] + (i-149)*70;

  hMultRawVsPt_eta1 = theOutputs->make<TH2D>("multrawvspt_eta1",";N_{trk}^{offline};p_{T} (GeV/c)",600,0,600,500,0,50);
  hMultRawVsPtCorr_eta1 = theOutputs->make<TH2D>("multrawvsptcorr_eta1",";N_{trk}^{offline};p_{T} (GeV/c)",600,0,600,500,0,50);
  hMultRawVsPt_eta2 = theOutputs->make<TH2D>("multrawvspt_eta2",";N_{trk}^{offline};p_{T} (GeV/c)",600,0,600,500,0,50);
  hMultRawVsPtCorr_eta2 = theOutputs->make<TH2D>("multrawvsptcorr_eta2",";N_{trk}^{offline};p_{T} (GeV/c)",600,0,600,500,0,50);
  hMultRawVsPt_eta3 = theOutputs->make<TH2D>("multrawvspt_eta3",";N_{trk}^{offline};p_{T} (GeV/c)",600,0,600,500,0,50);
  hMultRawVsPtCorr_eta3 = theOutputs->make<TH2D>("multrawvsptcorr_eta3",";N_{trk}^{offline};p_{T} (GeV/c)",600,0,600,500,0,50);
  hMultRawVsGen = theOutputs->make<TH2D>("multrawvsgen",";N_{trk}^{offline};N_{trk}^{Gen}",155,&multbins[0],155,&multbins[0]);
  hMultCorrVsGen = theOutputs->make<TH2D>("multcorrvsgen",";N_{trk}^{corrected};N_{trk}^{Gen}",155,&multbins[0],155,&multbins[0]);
  hZVtx = theOutputs->make<TH1D>("zvtx",";z_{vtx} (cm)",160,-20,20);
  hXYVtx = theOutputs->make<TH2D>("xyvtx",";x_{vtx} (cm);y_{vtx} (cm)",100,-0.5,0.5,100,-0.5,0.5);
  hNVtx = theOutputs->make<TH1D>("nvtx",";nVertices",51,-0.5,50.5);
  hMultRaw = theOutputs->make<TH1D>("multraw",";N_{trk}^{offline}",5000,0,5000);
  hMultCorr = theOutputs->make<TH1D>("multcorr",";N_{trk}^{offline}",5000,0,5000);
}

// ------------ method called to for each event  -----------
void MultiplicityAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  nMult=0;
  nMultCorr=0;
  nMultGen=0;

  // Select vertex
  if(cutPara.IsVtxSel)
  {
    GetVertices(iEvent,iSetup);
    hZVtx->Fill(zVtx);
    hXYVtx->Fill(xVtx,yVtx);
    hNVtx->Fill(nVertices);

    if(nVertices>cutPara.nvtxmax) return;

    double zVtxtmp = zVtx-cutPara.zvtxcenter;
    double yVtxtmp = yVtx-cutPara.yvtxcenter;
    double xVtxtmp = xVtx-cutPara.xvtxcenter;
    double rhotmp = sqrt(xVtxtmp*xVtxtmp+yVtxtmp*yVtxtmp);
//    zvtxbincentertmp = (int)((zVtxtmp-cutPara.zvtxmin)/cutPara.zvtxbin)*cutPara.zvtxbin+cutPara.zvtxmin+cutPara.zvtxbin/2;
    if( zVtxtmp<cutPara.zvtxmin || zVtxtmp>cutPara.zvtxmax || rhotmp<cutPara.rhomin || rhotmp>cutPara.rhomax ) return;
  }

  // Select multiplicity
  GetMult(iEvent,iSetup);
  hMultRawVsGen->Fill(nMult,nMultGen);
  hMultCorrVsGen->Fill(nMultCorr,nMultGen,1.0/GetTrgWeight(nMult));
  hMultRaw->Fill(nMult);
  hMultCorr->Fill(nMultCorr,1.0/GetTrgWeight(nMult));

  edm::Handle< reco::TrackCollection > tracks;
  iEvent.getByToken(token_tracks, tracks);

  if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

  for(unsigned it=0; it<tracks->size(); ++it){

    const reco::Track & trk = (*tracks)[it];

    if(trk.pt()<0.0001) continue;

    math::XYZPoint bestvtx(xVtx,yVtx,zVtx);

    double dzvtx = trk.dz(bestvtx);
    double dxyvtx = trk.dxy(bestvtx);
    double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
    double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);

    if(cutPara.IsPPTrkQuality)
    {
      if(!trk.quality(reco::TrackBase::highPurity)) continue;
      if(fabs(trk.ptError())/trk.pt()>0.1) continue;
      if(fabs(dzvtx/dzerror) > 3.0) continue;
      if(fabs(dxyvtx/dxyerror) > 3.0) continue;
    }

    if(cutPara.IsHITrkQuality && !trk.quality(reco::TrackBase::highPurity)) continue;

    double eta = trk.eta();
    double pt  = trk.pt();
    double effweight = GetEffWeight(eta,pt);

    if(fabs(eta)<1.0)
    {
      hMultRawVsPt_eta1->Fill(nMult,pt);
      hMultRawVsPtCorr_eta1->Fill(nMult,pt,1.0/effweight);
    }
    if(fabs(eta)<2.0 && fabs(eta)>1.0)
    {
      hMultRawVsPt_eta2->Fill(nMult,pt);
      hMultRawVsPtCorr_eta2->Fill(nMult,pt,1.0/effweight);
    }
    if(fabs(eta)<2.4 && fabs(eta)>2.0)
    {
      hMultRawVsPt_eta3->Fill(nMult,pt);
      hMultRawVsPtCorr_eta3->Fill(nMult,pt,1.0/effweight);
    }
  }

}

void MultiplicityAnalyzer::endJob()
{
}

// ---------------------------------------------------------------
void MultiplicityAnalyzer::GetMult(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
     //----- loop over tracks -----
     edm::Handle< reco::TrackCollection > tracks;
     iEvent.getByToken(token_tracks, tracks);
     if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

     for(unsigned it=0; it<tracks->size(); ++it){

       const reco::Track & trk = (*tracks)[it];

       if(trk.pt()<0.0001) continue;

       // select tracks based on proximity to best vertex 
       math::XYZPoint bestvtx(xVtx,yVtx,zVtx);

       double dzvtx = trk.dz(bestvtx);
       double dxyvtx = trk.dxy(bestvtx);      
       double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
       double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);

       // standard quality cuts

       if(cutPara.IsPPTrkQuality)
       {
         if(!trk.quality(reco::TrackBase::highPurity)) continue;
         if(fabs(trk.ptError())/trk.pt()>0.1) continue;
         if(fabs(dzvtx/dzerror) > 3.0) continue;
         if(fabs(dxyvtx/dxyerror) > 3.0) continue;
       }

       if(cutPara.IsHITrkQuality && !trk.quality(reco::TrackBase::highPurity)) continue;

       double eta = trk.eta();
       double pt  = trk.pt();

       double effweight = GetEffWeight(eta,pt);

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) { nMult++; nMultCorr=nMultCorr+1.0/effweight; }
     }
 
     if(!cutPara.IsGenMult) return;

     //----- loop over particles -----
     edm::Handle<reco::GenParticleCollection> genTracks;
     iEvent.getByToken(token_genparticles, genTracks);

     if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }
     
     for(unsigned ip=0; ip<genTracks->size(); ++ip){
       const reco::GenParticle & p = (*genTracks)[ip];
       if(p.status() != 1) continue;
       if(p.charge() == 0) continue;

       double eta = p.eta();
       double pt  = p.pt();

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) nMultGen++;
     }
}

// ------------- Fill Vertex distribution ---------------------
void MultiplicityAnalyzer::GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    nVertices=0;
    maxofflinetracks=0;
    xVtx = -99999.9;
    yVtx = -99999.9;
    zVtx = -99999.9;
    xVtxError = -99999.9;
    yVtxError = -99999.9;
    zVtxError = -99999.9;

    edm::Handle< reco::VertexCollection > vertices;
    iEvent.getByToken(token_vertices, vertices);

    if(!vertices->size()) { cout<<"Invalid or empty vertex collection!"<<endl; return; }

    for(unsigned int iv=0; iv<vertices->size(); ++iv)
    {
      const reco::Vertex & vtx = (*vertices)[iv];
      if(!vtx.isFake() && vtx.tracksSize()>=2) 
      { 
        nVertices++;
        if(vtx.tracksSize()>=maxofflinetracks)
        {
          xVtx = vtx.x();
          yVtx = vtx.y();
          zVtx = vtx.z();
          xVtxError = vtx.xError();
          yVtxError = vtx.yError();
          zVtxError = vtx.zError();

          maxofflinetracks = vtx.tracksSize();
        }
      }
    }
}

double MultiplicityAnalyzer::GetTrgWeight(double nmult)
{
  double trgweight=1.0;
  if(hTrgWeight) trgweight = hTrgWeight->GetBinContent(hTrgWeight->FindBin(nmult));
  return trgweight;
}

double MultiplicityAnalyzer::GetEffWeight(double eta, double pt)
{
  double effweight = 1.0;
  if(!hEffWeight) return effweight;
  effweight = hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt));
//  if(effweight<0.001) effweight=1.0;
  return effweight;
}
