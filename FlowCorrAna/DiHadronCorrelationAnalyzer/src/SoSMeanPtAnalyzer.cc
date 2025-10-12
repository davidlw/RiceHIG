#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/SoSMeanPtAnalyzer.h"
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

SoSMeanPtAnalyzer::SoSMeanPtAnalyzer(const edm::ParameterSet& iConfig) :
  hEffWeight(0),
  hTrgWeight(0),
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
  usesResource("TFileService");

  token_vertices = consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("VertexCollection"));
  token_tracks = consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("TrgTrackCollection"));
  token_genparticles = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("GenParticleCollection"));
  token_packedPFCandidates = consumes<pat::PackedCandidateCollection>(edm::InputTag("packedPFCandidates")); 
  token_packedgenparticles = consumes<pat::PackedGenParticleCollection>(edm::InputTag("packedGenParticles"));
  token_centrality = consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centralitySrc"));
  token_centralitybin = consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinLabel"));
//  token_zdc = consumes<QIE10DigiCollection>(edm::InputTag("zdcDigiSrc"));
  zdcDigiSrc_ = iConfig.getParameter<edm::InputTag>("zdcDigiSrc");
  consumes<QIE10DigiCollection>(zdcDigiSrc_);
  
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
  TString eff_histname(iConfig.getParameter<string>("EffHistName"));
  hEffWeight = 0;
  if(!eff_filename.IsNull())
  {
    edm::FileInPath fip(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",eff_filename.Data()));
    TFile f(fip.fullPath().c_str(),"READ");
    if(eff_histname.IsNull()) hEffWeight = (TH3D*)f.Get("hEff_3D");
    else hEffWeight = (TH3D*)f.Get(eff_histname.Data());
    f.Close();
  }

  TString fak_filename(iConfig.getParameter<string>("FakFileName"));
  TString fak_histname(iConfig.getParameter<string>("FakHistName"));
  hFakWeight = 0;
  if(!fak_filename.IsNull())
  {
    edm::FileInPath fip(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",fak_filename.Data()));
    TFile f(fip.fullPath().c_str(),"READ");
    if(fak_histname.IsNull()) hFakWeight = (TH3D*)f.Get("hFak_3D");
    else hFakWeight = (TH3D*)f.Get(fak_histname.Data());
    f.Close();
  }
  
}

//SoSMeanPtAnalyzer::~SoSMeanPtAnalyzer()
//{}

//
// member functions
//

void SoSMeanPtAnalyzer::beginJob()
{
  hZVtx = theOutputs->make<TH1D>("zvtx",";z_{vtx} (cm)",160,-20,20);
  hXYVtx = theOutputs->make<TH2D>("xyvtx",";x_{vtx} (cm);y_{vtx} (cm)",50,-0.5,0.5,50,-0.5,0.5);
  hNVtx = theOutputs->make<TH1D>("nvtx",";nVertices",51,-0.5,50.5);
  hCentrality = theOutputs->make<TH1D>("centrality",";centbin",200,-1,200-1);

  hHF = theOutputs->make<TH1D>("hHF",";#SigmaE^{HF}_{T} (3<|#eta|<5) (GeV)",1240,0,6200);
  hHFvsNpixel = theOutputs->make<TH2D>("hHFvsnpixel",";HF Sum E_{T}; Npixel;",800,0,8000,800,0,160000);
  hHFvsZDC = theOutputs->make<TH2D>("hHFvszdc",";HF Sum E_{T}; ZDC Sum E_{T};",800,0,8000,400,0,800000);
  /*
  hHFvsZDCP = theOutputs->make<TH2D>("hHFvszdcp",";HF Sum E_{T}; ZDC Sum E_{T};",800,0,8000,200,0,400000);
  hHFvsZDCM = theOutputs->make<TH2D>("hHFvszdcm",";HF Sum E_{T}; ZDC Sum E_{T};",800,0,8000,200,0,400000);  
//  hNVtxVsHF = theOutputs->make<TH2D>("hNVtxVsHF",";#SigmaE^{HF}_{T} (3<|#eta|<5) (GeV);nVertices",800,0,8000,51,-0.5,10.5);
  hCentVsHF = theOutputs->make<TH2D>("hCentVsHF",";centbin;#SigmaE^{HF}_{T} (3<|#eta|<5) (GeV)",200,-1,200-1,800,0,8000);
  hCentVsNpixel = theOutputs->make<TH2D>("hCentVsNpixel",";centbin; Npixel",200,-1,200-1,800,0,160000);
  hCentVsZDC = theOutputs->make<TH2D>("hCentVsZDC",";centbin; ZDC Sum E_{T}",200,-1,200-1,400,0,800000);
*/
  for(int i=0;i<4;i++)
  {
	  hEhftowerCentRapVsPt[i] = theOutputs->make<TH2D>(Form("EhftowerCentRapVsPt_Rap%d",i),";#SigmaE^{HF}_{T} (3<|#eta|<5) (GeV); p_{T} (GeV);",1240,0,6200,500,0,25);
//          hCentVsPt[i] = theOutputs->make<TH2D>(Form("CentVsPt_Rap%d",i),";centbin; p_{T} (GeV);",200,-1,200-1,500,0,25);
  }

  TString histname[] = {"#SigmaE_{T} (3<|#eta|<5) (GeV)","#SigmaE_{T} (4<|#eta|<5) (GeV)","#SigmaE_{T} (3<|#eta|<4) (GeV)"};
  for(int j=0;j<3;j++)
  {
          hEhfcentestimator[j] = theOutputs->make<TH1D>(Form("Ehfcentestimator%d",j),Form(";%s;",histname[j].Data()),1240,0,6200);
      	  for(int i=0;i<4;i++) hEhfCentRapVsPt[j][i] = theOutputs->make<TH2D>(Form("EhfCentRapVsPt_E%d_Rap%d",j,i),Form(";%s; p_{T} (GeV);",histname[i].Data()),1240,0,6200,500,0,25);
  }

  TString histname1[] = {"#SigmaE_{T} (1<|#eta|<3) (GeV)","#SigmaE_{T} (2<|#eta|<3) (GeV)","#SigmaE_{T} (1<|#eta|<2) (GeV)","#SigmaE_{T} (0<|#eta|<1) (GeV)","#SigmaE_{T} (0.5<|#eta|<1) (GeV)","#SigmaE_{T} (0<|#eta|<0.5) (GeV)"};
  for(int i=0;i<6;i++)
  {
	  hECentVsPtMidRap[i] = theOutputs->make<TH2D>(Form("ECentVsPtMidRap_E%d",i),Form(";%s; p_{T} (GeV);",histname1[i].Data()),1240,0,6200,500,0,25);
          hEcentestimator[i] = theOutputs->make<TH1D>(Form("Ecentestimator%d",i),Form(";%s;",histname1[i].Data()),1240,0,6200);
  }

  TString histname2[] = {"N_{ch} (1<|#eta|<2.4)", "N_{ch} (1<|#eta|<2)", "N_{ch} (0<|#eta|<1)", "N_{ch} (0<|#eta|<0.5)", "N_{ch} (0.5<|#eta|<1)"};
  for(int i=0;i<5;i++)
  {
	  hNCentVsPtMidRap[i] = theOutputs->make<TH2D>(Form("NCentVsPtMidRap_N%d",i),Form(";%s; p_{T} (GeV);",histname2[i].Data()),1240,0,6200,500,0,25);
          hNcentestimator[i] = theOutputs->make<TH1D>(Form("Ncentestimator%d",i),Form(";%s;",histname2[i].Data()),1240,0,6200);
  }
}

// ------------ method called to for each event  -----------
void SoSMeanPtAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
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
    if( zVtxtmp<cutPara.zvtxmin || zVtxtmp>cutPara.zvtxmax || rhotmp<cutPara.rhomin || rhotmp>cutPara.rhomax ) return;
  }

// Centrality  --------------------------------------------------------------
  edm::Handle<reco::Centrality> cent;
  iEvent.getByToken(token_centrality, cent);
  double hft = cent->EtHFtowerSum();
  double npixel = cent->multiplicityPixel();

  edm::Handle<QIE10DigiCollection> zdcdigis;
//  iEvent.getByToken(token_zdc, zdcdigis);
  iEvent.getByLabel(zdcDigiSrc_, zdcdigis);

  int nhits = 0;
  float chargefC[6][56];
  for (auto it = zdcdigis->begin(); it != zdcdigis->end(); it++)
  {
    const QIE10DataFrame digi = static_cast<const QIE10DataFrame>(*it);
    for( int ts = 0; ts < digi.samples(); ts++ )
      chargefC[ts][nhits] = QWAna::ZDC2018::QIE10_regular_fC[ digi[ts].adc() ][ digi[ts].capid() ];
    nhits++;
  }
  // Very preliminary calibration
  float sumcEMP = 0;
  float sumcEMN = 0;
  float sumcHDP = 0;
  float sumcHDN = 0;
  // 2023 EM: idet = 0-5 and 12-16
  for( int idet = 0; idet < 5; idet++ )
  {
    int idet_m = idet;
    int idet_p = idet + 12;
    sumcEMN += chargefC[2][idet_m] - chargefC[1][idet_m];
    sumcEMP += chargefC[2][idet_p] - chargefC[1][idet_p];
  }
  // 2023 HAD: idet = 8-11 and 20-23
  for( int idet = 8; idet < 12; idet++ )
  {
    int idet_m = idet;
    int idet_p = idet + 12;
    sumcHDN += chargefC[2][idet_m] - chargefC[1][idet_m];
    sumcHDP += chargefC[2][idet_p] - chargefC[1][idet_p];
  }
  double zdcSumMinus = (sumcEMN * 0.1 + sumcHDN) * 0.5031;
  double zdcSumPlus  = (sumcEMP * 0.1 + sumcHDP) * 0.9397;
  double zdc = zdcSumPlus + zdcSumMinus;
  
  if( zdc > (-56.*(hft-8100.)) ) return;
  if( npixel > (7500.+18.5*hft) ) return; //for data

  hHF->Fill(hft);
  hHFvsNpixel->Fill(hft,npixel);
  hHFvsZDC->Fill(hft,zdc);
//  hHFvsZDCP->Fill(hft,zdcSumPlus);
//  hHFvsZDCM->Fill(hft,zdcSumMinus);  
//  hNVtxVsHF->Fill(hft,nVertices);

  edm::Handle<int> cbin;
  iEvent.getByToken(token_centralitybin,cbin);
  int centbin = *cbin;

  hCentrality->Fill(centbin);
  /*
  hCentVsHF->Fill(centbin,hft);
  hCentVsNpixel->Fill(centbin,npixel);
  hCentVsZDC->Fill(centbin,zdc);
*/
//---------------------------------------------------------------------------

  double etatrkmin[4] = {0.0,0.5,1.0,1.5};
  double etatrkmax[4] = {0.5,1.0,1.5,2.0};
  
  double ehfcentetamin[3] = {2.5,4.0,2.9};
  double ehfcentetamax[3] = {5.5,5.2,4.0};
  
  double ncentetamin[5] = {1.0,1.0,0.0,0.0,0.5};
  double ncentetamax[5] = {2.4,2.0,1.0,0.5,1.0}; 

  double ecentetamin[6] = {1.0,2.0,1.0,0.0,0.5,0.0};
  double ecentetamax[6] = {3.0,3.0,2.0,1.0,1.0,0.5};
  
  double ehfcentestimator[3] = {0.0};
  double ecentestimator[6] = {0.0};
  double ncentestimator[5] = {0.0};
 
if(!cutPara.IsGenMult)
{  
  edm::Handle<pat::PackedCandidateCollection> packedPFCandidates;
  iEvent.getByToken(token_packedPFCandidates, packedPFCandidates);

  // E-based centrality estimator
  for (const auto& cand : *packedPFCandidates) {
    // Access candidate properties
    double pt = cand.pt();
    double eta = cand.eta();
    double phi = cand.phi();
    int pdgId = cand.pdgId();
    
    if(pt<0.4 && fabs(eta)<3) continue;

    for(int i=0;i<3;i++) if((fabs(pdgId) == 1 || fabs(pdgId) == 2) && fabs(eta)>ehfcentetamin[i] && fabs(eta)<ehfcentetamax[i]) ehfcentestimator[i] += pt;
    for(int i=0;i<6;i++) if(fabs(eta)>ecentetamin[i] && fabs(eta)<ecentetamax[i]) ecentestimator[i] += pt;
    // Do something with the candidate information
//    std::cout << "Candidate: pt = " << pt << ", eta = " << eta << ", phi = " << phi << ", pdgId = " << pdgId << std::endl;
  }

  for(int i=0;i<3;i++) hEhfcentestimator[i]->Fill(ehfcentestimator[i]);
  for(int i=0;i<6;i++) hEcentestimator[i]->Fill(ecentestimator[i]);
  
  edm::Handle< reco::TrackCollection > tracks;
  iEvent.getByToken(token_tracks, tracks);

  if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

  // Nch-based centrality estimator 
  for(unsigned it=0; it<tracks->size(); ++it){

    const reco::Track & trk = (*tracks)[it];

    if(trk.pt()<0.4) continue;

    math::XYZPoint bestvtx(xVtx,yVtx,zVtx);

    double dzvtx = trk.dz(bestvtx);
    double dxyvtx = trk.dxy(bestvtx);
    double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
    double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);

    if(cutPara.IsPPTrkQuality)
    {
      if(!trk.quality(reco::TrackBase::highPurity)) continue;
      if(fabs(trk.ptError())/trk.pt()>0.1) continue;
//      if(fabs(trk.ptError())/trk.pt()>0.05) continue;
      if(fabs(dzvtx/dzerror) > 3.0) continue;
      if(fabs(dxyvtx/dxyerror) > 3.0) continue;
    }

    if(cutPara.IsHITrkQuality)
    {
      if(!trk.quality(reco::TrackBase::highPurity)) continue;
      // Standard
      if(fabs(trk.ptError())/trk.pt()>0.1 && trk.pt()>10) continue;
      if(fabs(dzvtx/dzerror) > 3.0) continue;
      if(fabs(dxyvtx/dxyerror) > 3.0) continue;
      
      // Tight
/*       
      if(fabs(trk.ptError())/trk.pt()>0.05) continue;
      if(fabs(dzvtx/dzerror) > 2.0) continue;
      if(fabs(dxyvtx/dxyerror) > 2.0) continue;
*/      
      // Loose
      /*
      if(fabs(dzvtx/dzerror) > 5.0) continue;
      if(fabs(dxyvtx/dxyerror) > 5.0) continue;
      */
    }

    double eta = trk.eta();
    for(int i=0;i<5;i++)    
      if(fabs(eta)>ncentetamin[i] && fabs(eta)<ncentetamax[i])
	    ncentestimator[i]++;
  }

  for(int i=0;i<5;i++) hNcentestimator[i]->Fill(ncentestimator[i]);

  // spectra analysis 
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

    if(cutPara.IsHITrkQuality)
    {
      if(!trk.quality(reco::TrackBase::highPurity)) continue;
      // Standard
      if(fabs(trk.ptError())/trk.pt()>0.1 && trk.pt()>10) continue;
      if(fabs(dzvtx/dzerror) > 3.0) continue;
      if(fabs(dxyvtx/dxyerror) > 3.0) continue;

      // Tight
/*
      if(fabs(trk.ptError())/trk.pt()>0.05) continue;
      if(fabs(dzvtx/dzerror) > 2.0) continue;
      if(fabs(dxyvtx/dxyerror) > 2.0) continue;
*/      
      // Loose
      /*
      if(fabs(dzvtx/dzerror) > 5.0) continue;
      if(fabs(dxyvtx/dxyerror) > 5.0) continue;
      */      
    }

    double eta = trk.eta();
    double pt  = trk.pt();
//    double effweight = GetEffWeight(eta,pt,centbin);
    double effweight = GetEffWeight(eta,pt,npixel);

//    cout<<effweight<<endl;
    for(int i=0;i<4;i++)
      if(fabs(eta)>etatrkmin[i] && fabs(eta)<etatrkmax[i])
	{	      
          hEhftowerCentRapVsPt[i]->Fill(hft,pt,1.0/effweight);
//	  hCentVsPt[i]->Fill(centbin,pt,1.0/effweight);
	}

    for(int j=0;j<3;j++)  
      for(int i=0;i<4;i++)  
        if(fabs(eta)>etatrkmin[i] && fabs(eta)<etatrkmax[i])
          hEhfCentRapVsPt[j][i]->Fill(ehfcentestimator[j],pt,1.0/effweight);

    for(int i=0;i<6;i++)
        hECentVsPtMidRap[i]->Fill(ecentestimator[i],pt,1.0/effweight);
    
    for(int i=0;i<5;i++) 
        hNCentVsPtMidRap[i]->Fill(ncentestimator[i],pt,1.0/effweight);
  }
}
else
{
   edm::Handle<std::vector<pat::PackedGenParticle>> packedGenParticles;
   iEvent.getByToken(token_packedgenparticles, packedGenParticles);
   if(!packedGenParticles->size()) { cout<<"Invalid or empty PackedGenParticle collection!"<<endl; return; }

   for(unsigned it = 0; it < packedGenParticles->size(); ++it){

     const pat::PackedGenParticle & p = (*packedGenParticles)[it];

     if(p.status() != 1) continue;

     double eta = p.eta();
     double phi = p.phi();
     double pt  = p.pt();
     double charge = p.charge();
     double mass = p.mass();

     for(int i=0;i<3;i++) if(fabs(eta)>ehfcentetamin[i] && fabs(eta)<ehfcentetamax[i]) ehfcentestimator[i] += pt;
     for(int i=0;i<6;i++) if(fabs(eta)>ecentetamin[i] && fabs(eta)<ecentetamax[i]) ecentestimator[i] += pt;
     for(int i=0;i<5;i++)
       if(charge!=0 && fabs(eta)>ncentetamin[i] && fabs(eta)<ncentetamax[i])
             ncentestimator[i]++;
  }
  for(int i=0;i<3;i++) hEhfcentestimator[i]->Fill(ehfcentestimator[i]);
  for(int i=0;i<6;i++) hEcentestimator[i]->Fill(ecentestimator[i]);   
  for(int i=0;i<5;i++) hNcentestimator[i]->Fill(ncentestimator[i]);  

  for(unsigned it = 0; it < packedGenParticles->size(); ++it){

    const pat::PackedGenParticle & p = (*packedGenParticles)[it];

    if(p.status() != 1) continue;
    if(p.charge() == 0) continue;

    double eta = p.eta();
    double pt  = p.pt();
    double effweight = 1.0;

    for(int i=0;i<4;i++)
      if(fabs(eta)>etatrkmin[i] && fabs(eta)<etatrkmax[i])
        {
          hEhftowerCentRapVsPt[i]->Fill(hft,pt,1.0/effweight);
//          hCentVsPt[i]->Fill(centbin,pt,1.0/effweight);
        }

    for(int j=0;j<3;j++)
      for(int i=0;i<4;i++)
        if(fabs(eta)>etatrkmin[i] && fabs(eta)<etatrkmax[i])
          hEhfCentRapVsPt[j][i]->Fill(ehfcentestimator[j],pt,1.0/effweight);

    for(int i=0;i<6;i++)
        hECentVsPtMidRap[i]->Fill(ecentestimator[i],pt,1.0/effweight);

    for(int i=0;i<5;i++)
        hNCentVsPtMidRap[i]->Fill(ncentestimator[i],pt,1.0/effweight);     
  }
}
}

void SoSMeanPtAnalyzer::endJob()
{
}

// ------------- Fill Vertex distribution ---------------------
void SoSMeanPtAnalyzer::GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

double SoSMeanPtAnalyzer::GetTrgWeight(double nmult)
{
  double trgweight=1.0;
  if(hTrgWeight) trgweight = hTrgWeight->GetBinContent(hTrgWeight->FindBin(nmult));
  return trgweight;
}

double SoSMeanPtAnalyzer::GetEffWeight(double eta, double pt, int centbin)
{
  if(pt>9.8) pt=9.8;

  double effweight = 1.0;
  if(!hEffWeight) return effweight;
  effweight = hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt,centbin));
  if(effweight<0.0001) effweight=1.0;
 
  if(!hFakWeight) return effweight; 
  double fakweight = hFakWeight->GetBinContent(hFakWeight->FindBin(eta,pt,centbin));
  if(fakweight>0.9999) fakweight=1.0;
  effweight /= (1-fakweight);

  return effweight;
}
