#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiBase.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EventShape.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
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
#include <TGenPhaseSpace.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

DiHadronCorrelationMultiBase::DiHadronCorrelationMultiBase(const edm::ParameterSet& iConfig) :
//  cent(0),
  hEffWeight(0),
  hTrgWeight(0),
  nMult(0),
  nMultP(0),
  nMultM(0),
  nMultAll_trg(0),
  nMultAll_ass(0),
  nMultCorr(0),
  nMultAllCorr_trg(0),
  nMultAllCorr_ass(0),
  nVertices(0),
  maxofflinetracks(0),
  nCentBins(200),
  hft(0),
  npixel(0),
  zdc(0),
  xVtx(-99999.),
  yVtx(-99999.),
  zVtx(-99999.),	
  xVtxError(99999.),
  yVtxError(99999.),
  zVtxError(99999.),
  psi0_gen(-999.0),
  b_gen(-1.0),
  pol_lam(0.0),
  pol_lam_mean(0.0),
  pol_lam_sigma(0.0)
{
  TH1::SetDefaultSumw2();

  tag_ = consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinLabel"));
  centtag_ = consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centralitySrc"));

  token_vertices = consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("VertexCollection"));
  token_tracks = consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("TrgTrackCollection"));
  token_genparticles = consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("GenParticleCollection"));
  token_v0candidates = consumes<std::vector<reco::VertexCompositeCandidate>>(iConfig.getParameter<edm::InputTag>("V0CandidateCollection"));
  token_pfcandidates = consumes<std::vector<reco::PFCandidate>>(iConfig.getParameter<edm::InputTag>("pfCandidateCollection"));
  token_calotowers = consumes<edm::SortedCollection<CaloTower>>(edm::InputTag("towerMaker"));
  token_conversions = consumes<std::vector<reco::Conversion>>(iConfig.getParameter<edm::InputTag>("conversionCollection"));

  trgID = GetParticleID(iConfig.getParameter<string>("TriggerID"));
  assID = GetParticleID(iConfig.getParameter<string>("AssociateID"));

  NEtaBins = iConfig.getParameter<int>("NEtaBins");
  NPhiBins = iConfig.getParameter<int>("NPhiBins");
  checksign = iConfig.getParameter<int>("checksign");

  cutPara.nmin = iConfig.getParameter<int>("nmin");
  cutPara.nmax = iConfig.getParameter<int>("nmax");
  cutPara.centmin = iConfig.getParameter<int>("centmin");
  cutPara.centmax = iConfig.getParameter<int>("centmax");
//  cutPara.b_genmin = iConfig.getParameter<double>("b_genmin");
//  cutPara.b_genmax = iConfig.getParameter<double>("b_genmax");
  cutPara.b_genmin = -999.0;
  cutPara.b_genmax = 999.0;
  cutPara.xvtxcenter = iConfig.getParameter<double>("xvtxcenter");
  cutPara.yvtxcenter = iConfig.getParameter<double>("yvtxcenter");
  cutPara.zvtxcenter = iConfig.getParameter<double>("zvtxcenter");
  cutPara.rhomin = iConfig.getParameter<double>("rhomin");
  cutPara.rhomax = iConfig.getParameter<double>("rhomax");
  cutPara.zvtxmin = iConfig.getParameter<double>("zvtxmin");
  cutPara.zvtxmax = iConfig.getParameter<double>("zvtxmax");  
  cutPara.zvtxbin = iConfig.getParameter<double>("zvtxbin");
  cutPara.etatrgmin = iConfig.getParameter<double>("etatrgmin");
  cutPara.etatrgmax = iConfig.getParameter<double>("etatrgmax");
  cutPara.etaassmin = iConfig.getParameter<double>("etaassmin");
  cutPara.etaassmax = iConfig.getParameter<double>("etaassmax");
  cutPara.etamultmin = iConfig.getParameter<double>("etamultmin");
  cutPara.etamultmax = iConfig.getParameter<double>("etamultmax");
  cutPara.chargeasymmin = iConfig.getParameter<double>("chargeasymmin");
  cutPara.chargeasymmax = iConfig.getParameter<double>("chargeasymmax");
  cutPara.pttrgmin = iConfig.getParameter< std::vector<double> >("pttrgmin");
  cutPara.pttrgmax = iConfig.getParameter< std::vector<double> >("pttrgmax");
  cutPara.ptassmin = iConfig.getParameter< std::vector<double> >("ptassmin");
  cutPara.ptassmax = iConfig.getParameter< std::vector<double> >("ptassmax");
  cutPara.ptmultmin = iConfig.getParameter<double>("ptmultmin");
  cutPara.ptmultmax = iConfig.getParameter<double>("ptmultmax");
  cutPara.runmin = iConfig.getParameter<int>("runmin");
  cutPara.runmax = iConfig.getParameter<int>("runmax");
  cutPara.etacms = iConfig.getParameter<double>("etacms");
  cutPara.nvtxmax = iConfig.getParameter<int>("nvtxmax");

  cutPara.mass_trg = iConfig.getParameter<double>("mass_trg");
  cutPara.mass_ass = iConfig.getParameter<double>("mass_ass");
  cutPara.massmean_trg = iConfig.getParameter< std::vector<double> >("massmean_trg");
  cutPara.massmean_ass = iConfig.getParameter< std::vector<double> >("massmean_ass");
  cutPara.masswidth_trg = iConfig.getParameter< std::vector<double> >("masswidth_trg");
  cutPara.masswidth_ass = iConfig.getParameter< std::vector<double> >("masswidth_ass");
  cutPara.genpdgId_trg = iConfig.getParameter<int>("genpdgId_trg");
  cutPara.genpdgId_ass = iConfig.getParameter<int>("genpdgId_ass");
  cutPara.isstable_trg = iConfig.getParameter<bool>("isstable_trg");
  cutPara.isstable_ass = iConfig.getParameter<bool>("isstable_ass");
  cutPara.ischarge_trg = iConfig.getParameter<bool>("ischarge_trg");
  cutPara.ischarge_ass = iConfig.getParameter<bool>("ischarge_ass");

  cutPara.IsGenMult = iConfig.getParameter<bool>("IsGenMult");
  cutPara.IsGenCentrality = iConfig.getParameter<bool>("IsGenCentrality");
  cutPara.IsVtxSel = iConfig.getParameter<bool>("IsVtxSel");
  cutPara.IsCorr = iConfig.getParameter<bool>("IsCorr");
  cutPara.IsHI = iConfig.getParameter<bool>("IsHI");
  cutPara.IsV0SignalTrg = iConfig.getParameter<bool>("IsV0SignalTrg");
  cutPara.IsV0SignalAss = iConfig.getParameter<bool>("IsV0SignalAss");
  cutPara.IsV0BkgTrg = iConfig.getParameter<bool>("IsV0BkgTrg");
  cutPara.IsV0BkgAss = iConfig.getParameter<bool>("IsV0BkgAss");
  cutPara.IsFullMatrix = iConfig.getParameter<bool>("IsFullMatrix");
  cutPara.IsPtWeightTrg = iConfig.getParameter<bool>("IsPtWeightTrg");
  cutPara.IsPtWeightAss = iConfig.getParameter<bool>("IsPtWeightAss");   
  cutPara.IsTrgEtaCutAbs = iConfig.getParameter<bool>("IsTrgEtaCutAbs");
  cutPara.IsAssEtaCutAbs = iConfig.getParameter<bool>("IsAssEtaCutAbs");
  cutPara.IsPPTrkQuality = iConfig.getParameter<bool>("IsPPTrkQuality");
  cutPara.IsHITrkQuality = iConfig.getParameter<bool>("IsHITrkQuality");
  cutPara.IsDebug = iConfig.getParameter<bool>("IsDebug");
  cutPara.IsInvMass = iConfig.getParameter<bool>("IsInvMass");
  cutPara.IsEventEngineer = iConfig.getParameter<bool>("IsEventEngineer");
  cutPara.IsDSGenEvt = iConfig.getParameter<bool>("IsDSGenEvt");
  cutPara.IsCheckTrgV0Dau = iConfig.getParameter<bool>("IsCheckTrgV0Dau");
  cutPara.IsCheckAssV0Dau = iConfig.getParameter<bool>("IsCheckAssV0Dau");
  cutPara.IsBoostRestFrameGen = 1;
  cutPara.IsBoostRestFrameV0 = iConfig.getParameter<bool>("IsBoostRestFrameV0");
  cutPara.IsGenRP = 0;
  cutPara.IsGenB = 0;
  cutPara.IsGenAcc = 0;

  TString eff_filename(iConfig.getParameter<string>("EffFileName")); 
  TString eff_histname(iConfig.getParameter<string>("EffHistName"));
  hEffWeight = 0;
  if(!eff_filename.IsNull()) 
  {
    edm::FileInPath fip(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",eff_filename.Data()));
    TFile f(fip.fullPath().c_str(),"READ");
    if(eff_histname.IsNull()) hEffWeight = (TH3D*)f.Get("Eff3D");
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
    if(fak_histname.IsNull()) hFakWeight = (TH3D*)f.Get("Fak3D");
    else hFakWeight = (TH3D*)f.Get(fak_histname.Data());
    f.Close();
  }

  TString etaphi_filename(iConfig.getParameter<string>("EtaPhiFileName"));
  hEtaPhiWeightPos = 0;
  hEtaPhiWeightNeg = 0;
  if(!etaphi_filename.IsNull())
  {
    edm::FileInPath fip2(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",etaphi_filename.Data()));
    TFile f2(fip2.fullPath().c_str(),"READ");
    hEtaPhiWeightPos = (TH2D*)f2.Get("dNdetadphi_weight_pos");
    hEtaPhiWeightNeg = (TH2D*)f2.Get("dNdetadphi_weight_neg");
    if(hEtaPhiWeightPos && hEtaPhiWeightNeg) cout<<"Eta-Phi corrections loaded!"<<endl;
    f2.Close();
  }
/*
  TString centgen_filename(iConfig.getParameter<string>("CentGenFileName"));
  hCentGen = 0;
  if(!centgen_filename.IsNull())
  {
    edm::FileInPath fip3(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",centgen_filename.Data()));
    TFile f3(fip3.fullPath().c_str(),"READ");
    hCentGen = (TH2D*)f3.Get("cent_gen_b");
    f3.Close();
  }
*/
}

//DiHadronCorrelationMultiBase::~DiHadronCorrelationMultiBase()
//{}

//
// member functions
//
void DiHadronCorrelationMultiBase::beginRun(const edm::Run&, const edm::EventSetup& iSetup)
{
  if(trgID == kGenerator || assID == kGenerator) iSetup.getData(pdt);
}

void DiHadronCorrelationMultiBase::beginJob()
{
  // pt bins
  std::vector<double> ptBins;

  const double small = 1e-3;
  double pt;

  for(pt =   0  ; pt <   1.2-small; pt +=  0.02) ptBins.push_back(pt); // 24 bins
  for(pt =   1.2; pt <   2.4-small; pt +=  0.1 ) ptBins.push_back(pt); // 12 bins
  for(pt =   2.4; pt <   7.2-small; pt +=  0.4 ) ptBins.push_back(pt); // 12 bins
  for(pt =   7.2; pt <  14.4-small; pt +=  1.2 ) ptBins.push_back(pt); // 6 bins
  for(pt =  14.4; pt <  28.8-small; pt +=  2.4 ) ptBins.push_back(pt); // 6 bins 
  for(pt =  28.8; pt <  48.0-small; pt +=  3.2 ) ptBins.push_back(pt); // 6 bins
  for(pt =  48.0; pt <  86.4-small; pt +=  6.4 ) ptBins.push_back(pt); // 6 bins
  for(pt =  86.4; pt < 189.6-small; pt +=  8.6 ) ptBins.push_back(pt); // 6 bins
  ptBins.push_back(189.6);

  static float etaMin   = -6.0;
  static float etaMax   =  6.0;
  static float etaWidth =  0.4;
  std::vector<double> etaBins;

  for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
    etaBins.push_back(eta);

  hMultRawAll = theOutputs->make<TH1D>("multrawall",";n",10000,0,10000);
  hMultCorrAll = theOutputs->make<TH1D>("multcorrall",";n",10000,0,10000);
  if(cutPara.IsGenB) hMultVsB = theOutputs->make<TH2D>("multvsb",";nMult;b (fm)",500,0,10000,60,0,30);
  hMultChargeAsym = theOutputs->make<TH1D>("multchargeasym",";#frac{N_{+}-N_{-}}{N_{+}+N_{-}}",200,-1,1);
  hMultEtaAsym = theOutputs->make<TH2D>("multetaasym",";N_{trk};#frac{N_{#eta+}-N_{#eta-}}{N_{#eta+}+N_{#eta-}}",200,0,200,200,-1,1);
  hMultEtaPvsM = theOutputs->make<TH2D>("multetapvsm",";N_{#eta+};N_{#eta-}",200,0,200,200,0,200);
  hZVtx = theOutputs->make<TH1D>("zvtx",";z_{vtx} (cm)",160,-20,20);
  hXYVtx = theOutputs->make<TH2D>("xyvtx",";x_{vtx} (cm);y_{vtx} (cm)",100,-0.5,0.5,100,-0.5,0.5);
  hCentrality = theOutputs->make<TH1D>("centrality",";centbin",nCentBins,-1,nCentBins-1);
  hNVtx = theOutputs->make<TH1D>("nvtx",";nVertices",51,-0.5,50.5);

  if(trgID == kLambda || trgID == kLambdaP || trgID == kLambdaM || trgID == kKshort || assID == kLambda || assID == kLambdaP || assID == kLambdaM || assID == kKshort) 
  { 
    hThetaV0Plus = theOutputs->make<TH2D>("thetav0plus",";x_{F};cos#theta",200,0,0.2,100,-1,1);
    hThetaV0Minus = theOutputs->make<TH2D>("thetav0minus",";x_{F};cos#theta",200,0,0.2,100,-1,1);
    hV0InvMassVsP = theOutputs->make<TH2D>("v0invmassvsp",";p (GeV);Invariant Mass (GeV)",1000,0,1000,300,0.0,3.);
    hV0InvEtaVsP = theOutputs->make<TH2D>("v0etavsp",";p (GeV);#pseudorapidity",1000,0,1000,48,-2.4,2.4);
    hV0InvMassVsPt = theOutputs->make<TH2D>("v0invmassvspt",";p_{T}(GeV);Invariant Mass (GeV)",300,0,30,3000,0.,3.);
    hV0InvEtaVsPt = theOutputs->make<TH2D>("v0etavspt",";p_{T}(GeV);#pseudorapidity",100,0,10,48,-2.4,2.4);
  }

  if(cutPara.IsDebug)
  {
    hHFTowerSum = theOutputs->make<TH1D>("hftowersum",";HF Sum E_{T}",2400,0,12000);
    hHFvsNpixel = theOutputs->make<TH2D>("hfvsnpixel",";HF Sum E_{T}; Npixel;",2400,0,12000,1600,0,160000);
    hHFvsZDC = theOutputs->make<TH2D>("hfvszdc",";HF Sum E_{T}; ZDC Sum E_{T};",1200,0,12000,1000,0,2000000);
    hHFvsNtrk = theOutputs->make<TH2D>("hfvsntrk",";HF Sum E_{T}; Ntrack;",2400,0,12000,1000,0,5000);
    hHFvsNtrkCorr = theOutputs->make<TH2D>("hfvsntrkcorr",";HF Sum E_{T}; Ntrack;",2400,0,12000,1000,0,5000);
    hNtrkvsPt = theOutputs->make<TH2D>("ntrkvspt",";Ntrack; p_{T}(GeV/c);",1000,0,5000,400,0,20);
    hNtrkCorrvsPt = theOutputs->make<TH2D>("ntrkcorrvspt",";Ntrack; p_{T}(GeV/c);",1000,0,5000,400,0,20);
    hHFvsPt = theOutputs->make<TH2D>("hfvspt",";HF Sum E_{T}; p_{T}(GeV/c);",2400,0,12000,400,0,20);
    hNpixelvsPt = theOutputs->make<TH2D>("npixelvspt",";Npixel; p_{T}(GeV/c);",1600,0,160000,400,0,20);
    hPtAll_trg = theOutputs->make<TH1D>("ptall_trg",";p_{T}(GeV/c)",ptBins.size()-1, &ptBins[0]);
    hPTotAll_trg = theOutputs->make<TH1D>("ptotall_trg",";p_{T}(GeV/c)",10000,0,1000);
//  hNVtxVsNMult = theOutputs->make<TH2D>("nvtxvsnmult",";nMult;nVertices",500,0,500,50,0,50);
    hdNdetadptAll_trg = theOutputs->make<TH2D>("dNdetadptall_trg",";#eta;pT(GeV)",etaBins.size()-1, &etaBins[0],ptBins.size()-1, &ptBins[0]);
    hdNdetadpAll_trg = theOutputs->make<TH2D>("dNdetadpall_trg",";#eta;p (GeV)",160,-8,8,500,0,50);
    hdNdetadphiAll_trg = theOutputs->make<TH2D>("dNdetadphiall_trg",";#eta;#phi",40,-6.0,6.0,36,-PI,PI);
//    hdNdetadphiAll_dau1_trg = theOutputs->make<TH2D>("dNdetadphiall_dau1_trg",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
//    hdNdetadphiAll_dau2_trg = theOutputs->make<TH2D>("dNdetadphiall_dau2_trg",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
    hPtAll_ass = theOutputs->make<TH1D>("ptall_ass",";p_{T}(GeV/c)",5000,0,50);
    hPTotAll_ass = theOutputs->make<TH1D>("ptotall_ass",";p_{T}(GeV/c)",10000,0,1000);
    hdNdetadptAll_ass = theOutputs->make<TH2D>("dNdetadptall_ass",";#eta;pT(GeV)",120,-6.0,6.0,1000,0,10.0);
    hdNdetadpAll_ass = theOutputs->make<TH2D>("dNdetadpall_ass",";#eta;p (GeV)",160,-8,8,500,0,50);
    hdNdetadphiAll_ass = theOutputs->make<TH2D>("dNdetadphiall_ass",";#eta;#phi",40,-6.0,6.0,36,-PI,PI);
//    hdNdetadphiAll_dau1_ass = theOutputs->make<TH2D>("dNdetadphiall_dau1_ass",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
//    hdNdetadphiAll_dau2_ass = theOutputs->make<TH2D>("dNdetadphiall_dau2_ass",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
    hPtCorrAll_trg = theOutputs->make<TH1D>("ptcorrall_trg",";p_{T}(GeV/c)",ptBins.size()-1, &ptBins[0]);
    hdNdetadptCorrAll_trg = theOutputs->make<TH2D>("dNdetadptcorrall_trg",";#eta;pT(GeV)",etaBins.size()-1, &etaBins[0],ptBins.size()-1, &ptBins[0]);
    hdNdetadphiCorrAll_trg = theOutputs->make<TH2D>("dNdetadphicorrall_trg",";#eta;#phi",40,-6.0,6.0,36,-PI,PI);
    hPtCorrAll_ass = theOutputs->make<TH1D>("ptcorrall_ass",";p_{T}(GeV/c)",1000,0,100);
    hdNdetadptCorrAll_ass = theOutputs->make<TH2D>("dNdetadptcorrall_ass",";#eta;pT(GeV)",120,-6.0,6.0,1000,0,10.0);
    hdNdetadphiCorrAll_ass = theOutputs->make<TH2D>("dNdetadphicorrall_ass",";#eta;#phi",40,-6.0,6.0,36,-PI,PI);
//    hNpart = theOutputs->make<TH1D>("Npart",";N_{part}",500,0,500);
//    trackNtuple = theOutputs->make<TNtuple>("trackntuple","","pt:eta:phi:hit:pterr:d0:d0err:dz:dzerr:chi2:highPurity");
    hHighPurityFrac = theOutputs->make<TH1D>("hHighPurityFrac",";Fraction of highPurity tracks",100,0,1.0);

    hdzVtx = theOutputs->make<TH1D>("dzvtx",";dz_{vtx} (cm)",300,-30,30);
    hdxyVtx = theOutputs->make<TH2D>("dxyvtx",";dxy_{vtx} (cm)",100,-0.5,0.5,100,-0.5,0.5);
    hnprivsnsec = theOutputs->make<TH2D>("nprivsnsec",";npri;nsec",300,0,300,300,0,300);
    hnprivsnsec_dz1 = theOutputs->make<TH2D>("nprivsnsec_dz1",";npri;nsec",300,0,300,300,0,300);
    hdxyVtx_dz1 = theOutputs->make<TH2D>("dxyvtx_dz1",";dxy_{vtx} (cm)",100,-0.5,0.5,100,-0.5,0.5);
  }
  if(cutPara.IsInvMass) hInvMassVsPt_Signal = theOutputs->make<TH2D>("invmassvspt_signal",";p_{T}(GeV);Invariant Mass (GeV)",500,0,50,1500,0,3);
  if(cutPara.IsEventEngineer) hEventEngineer = theOutputs->make<TH2D>("eventengineer",";centrality;q_{2}",200,0,200,1000,0,1.0);
  if(cutPara.IsGenRP) hpol_lam =  theOutputs->make<TH1D>("pol_lam",";P_{#Lambda}",200,-1.0,1.0);

/*
  hV0InvMassVsPt = theOutputs->make<TH2D>("v0invmassvspt",";p_{T}(GeV);Invariant Mass (GeV)",200,0,20,1500,0,1.5);
  hV0InvMassVsPt_masspipicut = theOutputs->make<TH2D>("v0invmassvspt_masspipicut",";p_{T}(GeV);Invariant Mass (GeV)",200,0,20,1500,0,1.5);
  hV0AP = theOutputs->make<TH2D>("v0ap",";#alpha;#q_{T}",1000,-1,1,1000,0,0.5);
  hV0AP_masspipicut = theOutputs->make<TH2D>("v0ap_masspipicut",";#alpha;#q_{T}",1000,-1,1,1000,0,0.5);
  hV0MassPiPi = theOutputs->make<TH1D>("v0masspipi",";mass_pipi (GeV/c)",100,0.4,0.6);
  hV0MassEE = theOutputs->make<TH1D>("v0massee",";mass_ee (GeV/c)",100,0.0,0.2);
*/
  if(fabs(cutPara.genpdgId_trg)==3122 || fabs(cutPara.genpdgId_ass)==3122)
  {
    hLamPtvsProtonPt = theOutputs->make<TH2D>("lamPtvsProtonPt",";p^{#Lambda}_{T};p^{proton}_{T}",20,0,10.0,20,0,10.0);
    hLamPtvsPionPt = theOutputs->make<TH2D>("lamPtvsPionPt",";p^{#Lambda}_{T};p^{#pi}_{T}",20,0,10.0,20,0,10.0); 
    hLamDauPtRatiovsLamPt = theOutputs->make<TH2D>("lamDauPtRatiovsLamPt",";p^{#Lambda}_{T};p^{#pi}_{T}/p^{proton}_{T}",200,0,100.0,10,0,1.0);
  }

//  hMultCorr_trgVsass = theOutputs->make<TH2D>("multcorr_trgVsass",";n^{ass};n^{trg}",1000,0,10000,1000,0,10000);

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hMult_trg[itrg] = theOutputs->make<TH1D>(Form("mult_trg_%d",itrg),";n^{trg}",2000,0,2000);
    hMultCorr_trg[itrg] = theOutputs->make<TH1D>(Form("multcorr_trg_%d",itrg),";n^{trg}",2000,0,2000);
    hpT_Signal_trg[itrg] = theOutputs->make<TH1D>(Form("pt_signal_trg_%d",itrg),";pT(GeV)",2000,0,200.);
    hpTCorr_Signal_trg[itrg] = theOutputs->make<TH1D>(Form("ptcorr_signal_trg_%d",itrg),";pT(GeV)",2000,0,200.);
    hpTMult_Signal_trg[itrg] = theOutputs->make<TH2D>(Form("ptmult_signal_trg_%d",itrg),";N_{trk}^{offline};pT(GeV)",1000,0,10000,100,0,20.);
    hpTCorrMult_Signal_trg[itrg] = theOutputs->make<TH2D>(Form("ptcorrmult_signal_trg_%d",itrg),";N_{ch};pT(GeV)",1000,0,10000,100,0,20.);

    if(cutPara.IsDebug)
    {
      hdNdetadphi_trg[itrg] = theOutputs->make<TH2D>(Form("dNdetadphi_trg_%d",itrg),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
      hdNdetadphiCorr_trg[itrg] = theOutputs->make<TH2D>(Form("dNdetadphicorr_trg_%d",itrg),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
    }
  }

  for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
  {
    hMult_ass[jass] = theOutputs->make<TH1D>(Form("mult_ass_%d",jass),";n^{ass}",2000,0,2000);
    hMultCorr_ass[jass] = theOutputs->make<TH1D>(Form("multcorr_ass_%d",jass),";n^{ass}",2000,0,2000);
    hpT_Signal_ass[jass] = theOutputs->make<TH1D>(Form("pt_signal_ass_%d",jass),";pT(GeV)",2000,0,200.);
    hpTCorr_Signal_ass[jass] = theOutputs->make<TH1D>(Form("ptcorr_signal_ass_%d",jass),";pT(GeV)",2000,0,200.);
//    hpTMult_Signal_ass[jass] = theOutputs->make<TH2D>(Form("ptmult_signal_ass_%d",jass),";pT(GeV);N_{trk}^{offline}",1000,0,200.,100,0,500);
//    hpTCorrMult_Signal_ass[jass] = theOutputs->make<TH2D>(Form("ptcorrmult_signal_ass_%d",jass),";pT(GeV);N_{ch}",1000,0,200.,100,0,500);

    if(cutPara.IsDebug)
    {
      hdNdetadphi_ass[jass] = theOutputs->make<TH2D>(Form("dNdetadphi_ass_%d",jass),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
      hdNdetadphiCorr_ass[jass] = theOutputs->make<TH2D>(Form("dNdetadphicorr_ass_%d",jass),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
    }
  }
}

// ------------ method called to for each event  -----------
void DiHadronCorrelationMultiBase::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  nMult=0;
  nMultP=0;
  nMultM=0;
  nMultEtaP=0;
  nMultEtaM=0;
  nMultCorr=0;
  nMultAll_trg=0;
  nMultAllCorr_trg=0;
  nMultAll_ass=0;
  nMultAllCorr_ass=0;
  hfGen=0;

  psi0_gen = -999.0;
  if(cutPara.IsGenRP) 
  {
    psi0_gen = GetRP(iEvent,iSetup,1);
    if(psi0_gen<-4.) cout<<"reaction plane outside the range"<<endl;
    while(1) 
    {
      pol_lam = gRandom->Gaus(pol_lam_mean,pol_lam_sigma);
      if(pol_lam<=1.0 && pol_lam>=-1.0) break;
    }
    hpol_lam->Fill(pol_lam);
  }

  if(cutPara.IsGenB) 
  {
    b_gen = GetRP(iEvent,iSetup,2);
    if(b_gen<cutPara.b_genmin || b_gen>cutPara.b_genmax) return;
  }

  // Select vertex
  if(cutPara.IsVtxSel)
  {
    GetVertices(iEvent,iSetup);

    hNVtx->Fill(nVertices);

    if(nVertices>cutPara.nvtxmax) return;

    double zVtxtmp = zVtx-cutPara.zvtxcenter;
    double yVtxtmp = yVtx-cutPara.yvtxcenter;
    double xVtxtmp = xVtx-cutPara.xvtxcenter;

    double rhotmp = sqrt(xVtxtmp*xVtxtmp+yVtxtmp*yVtxtmp);
    if( zVtxtmp<cutPara.zvtxmin || zVtxtmp>cutPara.zvtxmax || rhotmp<cutPara.rhomin || rhotmp>cutPara.rhomax ) return;

    hZVtx->Fill(zVtx);
    hXYVtx->Fill(xVtx,yVtx);
  }

  hiCentrality=-1;
  if(cutPara.centmin!=-1 && cutPara.centmax!=-1)
  {
    hiCentrality = GetCentralityBin(iEvent,iSetup);

    if(hiCentrality<cutPara.centmin || hiCentrality>=cutPara.centmax) return;
/*
    if(cutPara.IsDebug)
    {
      hHFTowerSum->Fill(hft);
      hHFvsNpixel->Fill(hft,npixel);
      hHFvsZDC->Fill(hft,zdc);
    }
*/
  }
  hCentrality->Fill(hiCentrality);

  if(cutPara.IsDSGenEvt && !IsDSGen(iEvent,iSetup)) return;

  // Select multiplicity
  GetMult(iEvent,iSetup);
  if((nMult<cutPara.nmin || nMult>=cutPara.nmax) && (cutPara.nmin!=-1 || cutPara.nmax!=-1)) return;
  hMultRawAll->Fill(nMult);
  if(cutPara.IsGenB) hMultVsB->Fill(nMult,b_gen);
  hMultCorrAll->Fill(nMultCorr,1.0/GetTrgWeight(nMult));
  hMultEtaAsym->Fill(nMult,(double)(nMultEtaP-nMultEtaM)/(nMultEtaP+nMultEtaM));
  hMultEtaPvsM->Fill(nMultEtaP,nMultEtaM);

  if(nMult<0.09375*hft) return;

  if(cutPara.IsGenCentrality) hft = hfGen;

  hHFvsNtrk->Fill(hft,nMult);
  hHFvsNtrkCorr->Fill(hft,nMultCorr);

  double asym = (double)(nMultP-nMultM)/(nMultP+nMultM);
  if( asym<cutPara.chargeasymmin || asym>cutPara.chargeasymmax ) return;
  hMultChargeAsym->Fill(asym);

  if(cutPara.IsEventEngineer) hEventEngineer->Fill(hiCentrality,GetEventEngineer(iEvent,iSetup,2));

  eventcorr = new DiHadronCorrelationEvent();

  switch (trgID)
  {
     case kGenParticle:
       LoopParticles(iEvent,iSetup,1,cutPara.genpdgId_trg,cutPara.isstable_trg,cutPara.ischarge_trg);
       break;
     case kGenerator:
       LoopGenerators(iEvent,iSetup,1,cutPara.genpdgId_trg,cutPara.isstable_trg,cutPara.ischarge_trg);
       break;
     case kTrack:
       LoopTracks(iEvent,iSetup,1,-999);
       break;
     case kTrackP:
       LoopTracks(iEvent,iSetup,1,1);
       break;
     case kTrackM:
       LoopTracks(iEvent,iSetup,1,-1);
       break;
     case kCaloTower:
       LoopCaloTower(iEvent,iSetup,1);
       break;
     case kPFHadron:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::h);
       break;
     case kPFPhoton:
       cutPara.mass_trg=0.0;
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::gamma);
       break;
     case kPFElectron:
       cutPara.mass_trg=0.000511;
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::e);
       break;
     case kPFMuon:
       cutPara.mass_trg=0.1057;
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::mu);
       break;
     case kPFNeutral:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::h0);
       break;
     case kPFHadronHF:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::h_HF);
       break;
     case kPFEgammaHF:
       LoopPFCandidates(iEvent,iSetup,1,reco::PFCandidate::egamma_HF);
       break;
     case kKshort:
       cutPara.mass_trg=0.4976;
       LoopV0Candidates(iEvent,iSetup, 1, "Kshort",-1);
       break;
     case kLambda:
       cutPara.mass_trg=1.1159;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",-1);
       break;
     case kLambdaP:
       cutPara.mass_trg=1.1159;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",3122);
       break;
     case kLambdaM:
       cutPara.mass_trg=1.1159;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",-3122);
       break;
     case kD0:
       cutPara.mass_trg=1.86484;
       LoopV0Candidates(iEvent,iSetup, 1 , "D0",-1);
       break;
     case kConversion:
       cutPara.mass_trg=0.0;
       LoopConversions(iEvent,iSetup, 1);
       break;
     case kPFCandidate:
       LoopPFCandidates(iEvent,iSetup,1);
       break;
     default:
       break;
  }

  switch (assID)
  {
     case kGenParticle:
       LoopParticles(iEvent,iSetup,0,cutPara.genpdgId_ass,cutPara.isstable_ass,cutPara.ischarge_ass);
       break;     
     case kGenerator:
       LoopGenerators(iEvent,iSetup,0,cutPara.genpdgId_ass,cutPara.isstable_ass,cutPara.ischarge_ass);
       break;
     case kTrack:
       LoopTracks(iEvent,iSetup,0,-999);
       break;
     case kTrackP:
       LoopTracks(iEvent,iSetup,0,1);
       break;
     case kTrackM:
       LoopTracks(iEvent,iSetup,0,-1);
       break;
     case kCaloTower:
       LoopCaloTower(iEvent,iSetup,0);
       break;
     case kPFHadron:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::h);
       break;
     case kPFPhoton:
       cutPara.mass_ass=0.0;
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::gamma);
       break;
     case kPFElectron:
       cutPara.mass_ass=0.000511;
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::e);
       break;
     case kPFMuon:
       cutPara.mass_ass=0.1057;
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::mu);
       break;
     case kPFNeutral:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::h0);
       break;
     case kPFHadronHF:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::h_HF);
       break;
     case kPFEgammaHF:
       LoopPFCandidates(iEvent,iSetup,0,reco::PFCandidate::egamma_HF);
       break;
     case kKshort:
       cutPara.mass_ass=0.4976;
       LoopV0Candidates(iEvent,iSetup,0, "Kshort",-1);
       break;
     case kLambda:
       cutPara.mass_ass=1.1159;
       LoopV0Candidates(iEvent,iSetup,0, "Lambda",-1);
       break;
     case kLambdaP:
       cutPara.mass_ass=1.1159;
       LoopV0Candidates(iEvent,iSetup, 0, "Lambda",3122);
       break;
     case kLambdaM:
       cutPara.mass_ass=1.1159;
       LoopV0Candidates(iEvent,iSetup, 0, "Lambda",-3122);
       break;
     case kD0:
       cutPara.mass_ass=1.86484;
       LoopV0Candidates(iEvent,iSetup,0, "D0",-1);
       break;
     case kConversion:
       cutPara.mass_ass=0.0;
       LoopConversions(iEvent,iSetup, 0);
       break;
     case kPFCandidate:
       LoopPFCandidates(iEvent,iSetup,0);
       break;
     default:
       break;
  }

  eventcorr->run = iEvent.id().run();
//  eventcorr->lumi = iEvent.luminosityBlock();
  eventcorr->event = iEvent.id().event();
//  eventcorr->nmult=nMult;
//  eventcorr->centbin=hiCentrality;
  eventcorr->zvtx=zVtx;
  eventcorr->epangle=psi0_gen;
  eventcorr->chasym = asym;

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    nMult_trg[itrg]=eventcorr->pVect_trg[itrg].size();
    nMultCorr_trg[itrg]=0;
    for(unsigned int ntrg=0;ntrg<nMult_trg[itrg];ntrg++) nMultCorr_trg[itrg] = nMultCorr_trg[itrg] + 1.0/(eventcorr->effVect_trg[itrg])[ntrg];
    hMult_trg[itrg]->Fill(nMult_trg[itrg]);
    hMultCorr_trg[itrg]->Fill(nMultCorr_trg[itrg]);
    (eventcorr->nMultCorrVect_trg).push_back(nMultCorr_trg[itrg]);
  }

  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    nMult_ass[jass]=eventcorr->pVect_ass[jass].size();
    nMultCorr_ass[jass]=0;
    for(unsigned int nass=0;nass<nMult_ass[jass];nass++) nMultCorr_ass[jass] = nMultCorr_ass[jass] + 1.0/(eventcorr->effVect_ass[jass])[nass];
    hMult_ass[jass]->Fill(nMult_ass[jass]);
    hMultCorr_ass[jass]->Fill(nMultCorr_ass[jass]);
    (eventcorr->nMultCorrVect_ass).push_back(nMultCorr_ass[jass]);
  }

//  hMultCorr_trgVsass->Fill(nMultCorr_ass[0],nMultCorr_trg[0]);

  eventcorrArray.push_back(*eventcorr);

  delete eventcorr;
}

void DiHadronCorrelationMultiBase::endJob()
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  { 
    ptMean_trg[itrg]=hpTCorr_Signal_trg[itrg]->GetMean();
    ptMean2_trg[itrg]=hpTCorr_Signal_trg[itrg]->GetMean()*hpTCorr_Signal_trg[itrg]->GetMean()+hpTCorr_Signal_trg[itrg]->GetRMS()*hpTCorr_Signal_trg[itrg]->GetRMS();
  } 

  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    ptMean_ass[jass]=hpTCorr_Signal_ass[jass]->GetMean();
    ptMean2_ass[jass]=hpTCorr_Signal_ass[jass]->GetMean()*hpTCorr_Signal_ass[jass]->GetMean()+hpTCorr_Signal_ass[jass]->GetRMS()*hpTCorr_Signal_ass[jass]->GetRMS();
  }

  NormalizeHists();
}

// ---------------------------------------------------------------
void DiHadronCorrelationMultiBase::GetMult(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   if(!cutPara.IsGenMult) 
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

//       int algo = trk.algo();
       double dzvtx = trk.dz(bestvtx);
       double dxyvtx = trk.dxy(bestvtx);      
       double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
       double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
       double charge = trk.charge();
       int nhits = trk.numberOfValidHits();
       double chi2n = trk.normalizedChi2();
       int nlayers = trk.hitPattern().trackerLayersWithMeasurement();

       // standard quality cuts

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
         if(fabs(trk.ptError())/trk.pt()>0.1) continue;
         if(fabs(dzvtx/dzerror) > 3.0) continue;
         if(fabs(dxyvtx/dxyerror) > 3.0) continue;
         if(nhits<11) continue;
         if(chi2n/nlayers>0.18) continue;
       }

       double eta = trk.eta();
       double phi = trk.phi();
       double pt  = trk.pt();

//       double effweight = GetEffWeight(eta,phi,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality,charge);
       double effweight = GetEffWeight(eta,phi,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),npixel,charge);

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) 
       { 
         nMult++; 
         nMultCorr=nMultCorr+1.0/effweight;
         if(eta>0) nMultEtaP += 1.0;
         if(eta<0) nMultEtaM += 1.0;
       }
       if(charge>0 && eta>=-2.4 && eta<=2.4 && pt>=0.3 && pt<=3.0) nMultP += 1.0/effweight;
       if(charge<0 && eta>=-2.4 && eta<=2.4 && pt>=0.3 && pt<=3.0) nMultM += 1.0/effweight;
     }
   }
   else
   {
     if(trgID == kGenParticle)
     {
       //----- loop over particles -----
       edm::Handle<reco::GenParticleCollection> genTracks;
       iEvent.getByToken(token_genparticles, genTracks);

       if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }
     
       for(unsigned ip=0; ip<genTracks->size(); ++ip){
         const reco::GenParticle & p = (*genTracks)[ip];
         if(p.status() != 1) continue;
//         if(p.charge() == 0) continue;

         double eta = p.eta();
         double pt  = p.pt();

         if(p.charge() != 0 && eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) 
         {
           nMult++;
           nMultCorr++;
           if(eta>0) nMultEtaP += 1.0;
           if(eta<0) nMultEtaM += 1.0;
         }

         if(fabs(eta)<5.0 && fabs(eta)>3.0 && pt>0.0) hfGen += pt;

         if(p.charge()>0 && eta>=-2.4 && eta<=2.4 && pt>=0.3 && pt<=3.0) nMultP++;
         if(p.charge()<0 && eta>=-2.4 && eta<=2.4 && pt>=0.3 && pt<=3.0) nMultM++;
       }
     }
     if(trgID == kGenerator)
     {
       edm::Handle<HepMCProduct> mc;
       iEvent.getByLabel("generator",mc);
       const GenEvent* evt = mc->GetEvent();

       HepMC::GenEvent::particle_const_iterator begin = evt->particles_begin();
       HepMC::GenEvent::particle_const_iterator end = evt->particles_end();
       for(HepMC::GenEvent::particle_const_iterator it = begin; it != end; ++it){

         if((*it)->status()!=1) continue;

         int pdg_id = (*it)->pdg_id();
         const ParticleData * part = pdt->particle(pdg_id);
         int charge = static_cast<int>(part->charge());
//         if(charge == 0) continue;
         if((*it)->momentum().perp()<0.01) continue;
         if(fabs((*it)->momentum().eta())>20) continue;

         float eta = (*it)->momentum().eta();
         float pt = (*it)->momentum().perp();

         if(charge != 0 && eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax)
         {
           nMult++;
           nMultCorr++;
           if(eta>0) nMultEtaP += 1.0;
           if(eta<0) nMultEtaM += 1.0;
         }

         if(fabs(eta)<5.0 && fabs(eta)>3.0 && pt>0.0) hfGen += pt;
         if(charge > 0 && eta>=-2.4 && eta<=2.4 && pt>=0.3 && pt<=3.0) nMultP++;
         if(charge < 0 && eta>=-2.4 && eta<=2.4 && pt>=0.3 && pt<=3.0) nMultM++;
       }
     }
   }
}

bool DiHadronCorrelationMultiBase::IsDSGen(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<reco::GenParticleCollection> genTracks;
  iEvent.getByToken(token_genparticles, genTracks);
  if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return 0; }

  bool isforward=0;
  bool isbackward=0;
  for(unsigned ip=0; ip<genTracks->size(); ++ip){
    const reco::GenParticle & p = (*genTracks)[ip];
    if(p.status() != 1) continue;
//    if(p.charge() == 0) continue;

    double eta = p.eta();
    double energy = p.energy();
    if(eta>3.0 && eta<5.0 && energy>3.0) isforward = 1;
    if(eta>-5.0 && eta<-3.0 && energy>3.0) isbackward = 1;   
  }

  return (isforward && isbackward);
}

// ------------- Loop over generator particles -------------------
void DiHadronCorrelationMultiBase::LoopGenerators(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int pdgid, bool isstable, bool ischarge)
{
   edm::Handle<HepMCProduct> mc;
   iEvent.getByLabel("generator",mc);
   const GenEvent* evt = mc->GetEvent();

   HepMC::GenEvent::particle_const_iterator begin = evt->particles_begin();
   HepMC::GenEvent::particle_const_iterator end = evt->particles_end();
   for(HepMC::GenEvent::particle_const_iterator it = begin; it != end; ++it){

       if((*it)->status() != 1 && isstable) continue;

       int pdg_id = (*it)->pdg_id();
       const ParticleData * part = pdt->particle(pdg_id);
       int charge = static_cast<int>(part->charge());
       if(charge == 0 && ischarge) continue;

       if(pdg_id != pdgid && pdgid!=-999999) continue;
       if((*it)->momentum().perp()<0.01) continue;
       if(fabs((*it)->momentum().eta())>20) continue;

       float eta = (*it)->momentum().eta();
       float phi = (*it)->momentum().phi();
       float pt = (*it)->momentum().perp();
       float mass = (*it)->momentum().m();

       TLorentzVector p4((*it)->momentum().px(),(*it)->momentum().py(),(*it)->momentum().pz(),(*it)->momentum().e());

       TLorentzVector *pDau1 = 0;
       TLorentzVector *pDau2 = 0;
       if(fabs(pdgid)==3122)
       {
         double masses_dau[2] = {0.938272,0.13957};

         TGenPhaseSpace event;
         event.SetDecay(p4,2,masses_dau);

         pDau1 = event.GetDecay(0);
         pDau2 = event.GetDecay(1);

         double effweight = event.Generate();
//         cout<<"Weight: "<<effweight<<endl;
         if(TMath::IsNaN(effweight)) continue;
         effweight = 1.0;

//         cout<<cutPara.IsGenAcc<<"; "<<pDau1->Eta()<<","<<pDau1->Phi()<<"; "<<pDau2->Eta()<<","<<pDau2->Phi()<<endl;
         if(cutPara.IsGenAcc && (!Acceptance(pDau1->Eta(),pDau1->Phi(),pDau1->Pt()) || !Acceptance(pDau2->Eta(),pDau2->Phi(),pDau2->Pt()))) continue;

//cout<<"before boost: "<<p4.Pt()<<" "<<p4.Pz()<<"; "<<pDau1->Pt()<<" "<<pDau1->Pz()<<"; "<<pDau2->Pt()<<" "<<pDau2->Pz()<<endl;

         if(cutPara.IsBoostRestFrameGen)
         {
           TVector3 boost = -p4.BoostVector();
           pDau1->Boost(boost);
           pDau2->Boost(boost);

//cout<<"after boost: "<<p4.Pt()<<" "<<p4.Pz()<<"; "<<pDau1->Pt()<<" "<<pDau1->Pz()<<"; "<<pDau2->Pt()<<" "<<pDau2->Pz()<<endl;

           if(TMath::IsNaN(pDau1->Pt()) || TMath::IsNaN(pDau2->Pt())) continue;

           TVector3 rp_vector(cos(psi0_gen), sin(psi0_gen), 0);
           TVector3 beam_vector(0,0,1.0);
           TVector3 angmom_vector = rp_vector.Cross(beam_vector);

           double theta_star = (pDau1->Vect()).Angle(angmom_vector);

           effweight = effweight/(1+0.642*pol_lam*cos(theta_star));
         }
//cout<<"get here!"<<endl;
//cout<<"daughter pt:"<<pDau1->Pt()<<" "<<pDau2->Pt()<<endl;
         if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight,cutPara.IsCheckTrgV0Dau,pDau1->Pt(),pDau1->Eta(),pDau1->Phi(),pDau1->M(),pDau2->Pt(),pDau2->Eta(),pDau2->Phi(),pDau2->M());
         else AssignAssPtBins(pt,eta,phi,mass,charge,effweight,cutPara.IsCheckAssV0Dau,pDau1->Pt(),pDau1->Eta(),pDau1->Phi(),pDau1->M(),pDau2->Pt(),pDau2->Eta(),pDau2->Phi(),pDau2->M());
       }
       else
       {
         if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,1.0);
         else AssignAssPtBins(pt,eta,phi,mass,charge,1.0);
       }
   }
//cout<<"completed!"<<endl;
}

// ------------- Loop over all the particles ---------------------
void DiHadronCorrelationMultiBase::LoopParticles(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int pdgid, bool isstable, bool ischarge)
{
   //----- loop over particles -----
   edm::Handle<reco::GenParticleCollection> genTracks;
   iEvent.getByToken(token_genparticles, genTracks);
   if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }

   for(unsigned ip=0; ip<genTracks->size(); ++ip){
     const reco::GenParticle & p = (*genTracks)[ip];

     if(p.status() != 1 && isstable) continue;
     if(p.charge() == 0 && ischarge) continue;
     if(p.pdgId() != pdgid && pdgid!=-999999) continue;
//     if(p.pt()<0.001) continue;
//     if(p.mass()<(0.938272+0.13957)) continue;

//     cout<<"is prompt? "<<p.isPromptFinalState()<<endl;

     double eta = p.eta();
     double phi = p.phi();
     double pt  = p.pt();
     double charge = p.charge();
     double mass = p.mass();

     TLorentzVector p4(p.px(),p.py(),p.pz(),p.energy());

     TLorentzVector *pDau1 = 0;
     TLorentzVector *pDau2 = 0;
     if(fabs(pdgid)==3122)
     {
       double masses_dau[2] = {0.938272,0.13957};

       TGenPhaseSpace event;
       event.SetDecay(p4,2,masses_dau);

       pDau1 = event.GetDecay(0);
       pDau2 = event.GetDecay(1);

       double effweight = event.Generate();
       effweight = 1.0;

       hLamPtvsProtonPt->Fill(p4.Pt(),pDau1->Pt());
       hLamPtvsPionPt->Fill(p4.Pt(),pDau2->Pt());
       hLamDauPtRatiovsLamPt->Fill(p4.Pt(),pDau2->Pt()/pDau1->Pt());
       if(cutPara.IsBoostRestFrameGen)
       {
         TVector3 boost = -p4.BoostVector();
         pDau1->Boost(boost);
         pDau2->Boost(boost);

         TVector3 rp_vector(cos(psi0_gen), sin(psi0_gen), 0);
         TVector3 beam_vector(0,0,1.0);
         TVector3 angmom_vector = rp_vector.Cross(beam_vector);
  
         double theta_star = (pDau1->Vect()).Angle(angmom_vector);

         effweight = effweight/(1+0.642*pol_lam*cos(theta_star));
       }
       if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight,cutPara.IsCheckTrgV0Dau,pDau1->Pt(),pDau1->Eta(),pDau1->Phi(),pDau1->M(),pDau2->Pt(),pDau2->Eta(),pDau2->Phi(),pDau2->M());
       else AssignAssPtBins(pt,eta,phi,mass,charge,effweight,cutPara.IsCheckAssV0Dau,pDau1->Pt(),pDau1->Eta(),pDau1->Phi(),pDau1->M(),pDau2->Pt(),pDau2->Eta(),pDau2->Phi(),pDau2->M());
     } 
     else 
     {
       if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,1.0);
       else AssignAssPtBins(pt,eta,phi,mass,charge,1.0);
     }
   }
}

// ------------- Loop over all the tracks ---------------------
void DiHadronCorrelationMultiBase::LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge)
{	
   //----- loop over tracks -----
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByToken(token_tracks, tracks);

   if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

   int nall=0;
   int nHP=0;
   for(unsigned it=0; it<tracks->size(); ++it){     
 
     const reco::Track & trk = (*tracks)[it];

//     auto trk_ref = trk.get<reco::TrackRef>();

     double pt  = trk.pt();
     if(pt<0.0001) continue;
     double eta = trk.eta();
     double phi = trk.phi();

     // tracks' proximity to best vertex
     math::XYZPoint bestvtx(xVtx,yVtx,zVtx);
     double dzvtx = trk.dz(bestvtx);
     double dxyvtx = trk.dxy(bestvtx);
     double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
     double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
     double pterror = trk.ptError();
     int nhits = trk.numberOfValidHits();
/*
     double vx = trk.vx();
     double vy = trk.vy();
     double vz = trk.vz();
     double chi2 = trk.chi2();
*/
     double chi2n = trk.normalizedChi2();
     int nlayers = trk.hitPattern().trackerLayersWithMeasurement();
     double charge = trk.charge();
//     int algo = trk.algo();

     if(cutPara.IsDebug)
     {
//       trackNtuple->Fill(pt,eta,phi,nhits,pterror,dxyvtx,dxyvtx/dxyerror,dzvtx,dzvtx/dzerror,chi2n,trk.quality(reco::TrackBase::highPurity));
       nall++;
       if(trk.quality(reco::TrackBase::highPurity)) nHP++;
     }

     if(cutPara.IsPPTrkQuality)
     {
       if(!trk.quality(reco::TrackBase::highPurity)) continue;
       if(fabs(trk.ptError())/trk.pt() > 0.1) continue;
       if(fabs(dzvtx/dzerror) > 3.0) continue;
       if(fabs(dxyvtx/dxyerror) > 3.0) continue;

/*
       if(fabs(trk.ptError())/trk.pt() > 0.05) continue;
       if(fabs(dzvtx/dzerror) > 2.0) continue;
       if(fabs(dxyvtx/dxyerror) > 2.0) continue;
*/
     }

     if(cutPara.IsHITrkQuality)
     {
       if(!trk.quality(reco::TrackBase::highPurity)) continue;
       if(fabs(trk.ptError())/trk.pt()>0.1) continue; //{ cout<<"filtered by pterr"<<endl; continue;}
       if(fabs(dzvtx/dzerror) > 3.0) continue; //{ cout<<"filtered by dz"<<endl; continue;}
       if(fabs(dxyvtx/dxyerror) > 3.0) continue; //{ cout<<"filtered by dxy"<<endl; continue;}
       if(nhits<11) continue; //{ cout<<"filtered by nhits"<<endl; continue;}
       if(chi2n/nlayers>0.18) continue; //{ cout<<" filtered by chi2"<<endl; continue;}      
     }

//     double effweight = GetEffWeight(eta,phi,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality,charge);
     double effweight = GetEffWeight(eta,phi,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),npixel,charge);
     double trgweight = GetTrgWeight(nMult);

//cout<<effweight<<" "<<trgweight<<" "<<npixel<<" "<<eta<<" "<<pt<<endl;
     if(charge!=icharge && icharge!=-999) continue;
     if(istrg) AssignTrgPtBins(pt,eta,phi,cutPara.mass_trg,charge,effweight*trgweight);
     else AssignAssPtBins(pt,eta,phi,cutPara.mass_ass,charge,effweight*trgweight);
   }
   if(nall) hHighPurityFrac->Fill((double)nHP/(double)nall);
}

void DiHadronCorrelationMultiBase::LoopCaloTower(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg)
{
   edm::Handle<CaloTowerCollection> calotowers;
   iEvent.getByToken(token_calotowers, calotowers);
   if(!calotowers->size()) { cout<<"Invalid or empty calotower collection!"<<endl; return; }

   for(unsigned it=0; it<calotowers->size(); ++it){

     //const reco::Candidate & calotower = (*calotowers)[it];
     const CaloTower & calotower = (*calotowers)[it];

//     double et  = calotower.et();
//     if(et<0.01) continue;        
     double eta = calotower.eta();
     double phi = calotower.phi();
     double et  = calotower.energy();
     double charge = 0;
     
//     if(fabs(eta)>3 && fabs(eta)<5.2 && et>0.1 && et<0.2) {cout<<eta<<" "<<phi<<" "<<et<<endl;}
//     if(fabs(eta)>3 && fabs(eta)<5.2 && et>3.1 && et<3.2) {cout<<eta<<" "<<phi<<" "<<et<<endl;}
//     if(fabs(eta)>3 && fabs(eta)<5.2) {cout<<eta<<" "<<phi<<" "<<et<<endl;}

     double effweight = 1.0;

     if(istrg) AssignTrgPtBins(et,eta,phi,0,charge,effweight);
     else AssignAssPtBins(et,eta,phi,0,charge,effweight);
   }
}

void DiHadronCorrelationMultiBase::LoopConversions(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg)
{
   edm::Handle<ConversionCollection> conversions;
   iEvent.getByToken(token_conversions, conversions);
   if(!conversions->size()) { return; }

   for(unsigned it=0; it<conversions->size(); ++it){

     const Conversion & conversion = (*conversions)[it];

     if(conversion.nTracks()!=2) continue;

     double pt = conversion.pairMomentum().Rho();
     double eta = conversion.pairMomentum().Eta();
     double phi = conversion.pairMomentum().Phi();
     double mass = conversion.pairInvariantMass(); 

     double charge = 0.0;
     double effweight = 1.0;
     
     if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,mass,charge,effweight);
   }
}


void DiHadronCorrelationMultiBase::LoopV0Candidates(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, TString candtype, int pdgID)
{
   edm::Handle<reco::VertexCompositeCandidateCollection > v0candidates;
   iEvent.getByToken(token_v0candidates, v0candidates);
   if(!v0candidates->size()) return;

   for(unsigned it=0; it<v0candidates->size(); ++it){

     const VertexCompositeCandidate& v0candidate = (*v0candidates)[it];

     double eta = v0candidate.eta();
     double phi = v0candidate.phi();
     double pt  = v0candidate.pt();
     double p = v0candidate.p();
//     double pz = v0candidate.pz();
     double mass = v0candidate.mass();
     double charge = v0candidate.charge();
     int pdgid = v0candidate.pdgId();

     hV0InvMassVsPt->Fill(pt,mass);
     hV0InvEtaVsPt->Fill(pt,eta);
     hV0InvMassVsP->Fill(p,mass);
     hV0InvEtaVsP->Fill(p,eta);

     if(pdgID!=-1 && pdgid!=pdgID) continue;

     const reco::Candidate * d1 = v0candidate.daughter(0);
     const reco::Candidate * d2 = v0candidate.daughter(1);
     TLorentzVector dau1vec(d1->px(),d1->py(),d1->pz(), d1->energy());
     TLorentzVector dau2vec(d2->px(),d2->py(),d2->pz(), d2->energy());

     TLorentzVector p4(v0candidate.px(),v0candidate.py(),v0candidate.pz(),v0candidate.energy());

     if(cutPara.IsBoostRestFrameV0)
     {
       TVector3 boost = -p4.BoostVector();

       dau1vec.Boost(boost);
       dau2vec.Boost(boost);
     }
/*
     TVector3 beam(0,0,1);
     TVector3 npol(boost.Cross(beam));

     if(d1->charge()>0) hThetaV0Plus->Fill(pz/4000.,cos(dau1vec.Angle(npol)));
     if(d1->charge()<0) hThetaV0Minus->Fill(pz/4000.,cos(dau1vec.Angle(npol)));
*/
     double effweight = 1.0;

     if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight,cutPara.IsCheckTrgV0Dau,dau1vec.Pt(),dau1vec.Eta(),dau1vec.Phi(),dau1vec.M(),dau2vec.Pt(),dau2vec.Eta(),dau2vec.Phi(),dau2vec.M());
     else AssignAssPtBins(pt,eta,phi,mass,charge,effweight,cutPara.IsCheckAssV0Dau,dau1vec.Pt(),dau1vec.Eta(),dau1vec.Phi(),dau1vec.M(),dau2vec.Pt(),dau2vec.Eta(),dau2vec.Phi(),dau2vec.M());
   }
}

void DiHadronCorrelationMultiBase::LoopPFCandidates(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, reco::PFCandidate::ParticleType pfID)
{
   edm::Handle<reco::PFCandidateCollection > pfcandidates;
   iEvent.getByToken(token_pfcandidates, pfcandidates);
   if(!pfcandidates->size()) return;

   for(unsigned it=0; it<pfcandidates->size(); ++it){

     const reco::PFCandidate & pfCand = (*pfcandidates)[it];
     double eta = pfCand.eta();
     double phi = pfCand.phi();
     double pt  = pfCand.pt();
//     double p   = pfCand.p();
//     double etot = pfCand.ecalEnergy()+pfCand.hcalEnergy();
//     double etot = pfCand.hcalEnergy();
     double charge = pfCand.charge();
     double mass = pfCand.mass();

     if(reco::PFCandidate::ParticleType(pfCand.particleId())!=pfID) continue;

     // PID via velocity
//     hBetaVsP->Fill(p,p/etot);

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,mass,charge,effweight);
   }
}

void DiHadronCorrelationMultiBase::LoopPFCandidates(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg)
{
   edm::Handle<reco::PFCandidateCollection > pfcandidates;
   iEvent.getByToken(token_pfcandidates, pfcandidates);
   if(!pfcandidates->size()) { cout<<"pfcandidate is missing!"<<endl; return; }

   for(unsigned it=0; it<pfcandidates->size(); ++it){

     const reco::PFCandidate & pfCand = (*pfcandidates)[it];
     double eta = pfCand.eta();
     double phi = pfCand.phi();
     double pt  = pfCand.pt();
     double charge = pfCand.charge();
     double mass = pfCand.mass();

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,mass,charge,effweight);
   }
}

// ------------- Fill Vertex distribution ---------------------
void DiHadronCorrelationMultiBase::GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

    double ntrkmax = 0;
    double zvtxmax = -9999.0;
    double yvtxmax = -9999.0;
    double xvtxmax = -9999.0;
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
        if(cutPara.IsDebug)
        {
          if(iv == 0)
          {
            ntrkmax = vtx.tracksSize();
            zvtxmax = vtx.z();
            yvtxmax = vtx.y();
            xvtxmax = vtx.x();
          }
          else
          {
            hdzVtx->Fill(vtx.z()-zvtxmax);
            hdxyVtx->Fill(vtx.x()-xvtxmax,vtx.y()-yvtxmax);
            hnprivsnsec->Fill(ntrkmax,vtx.tracksSize());
            if(fabs(vtx.z()-zvtxmax)<1.)
            {
              hdxyVtx_dz1->Fill(vtx.x()-xvtxmax,vtx.y()-yvtxmax);
              hnprivsnsec_dz1->Fill(ntrkmax,vtx.tracksSize());
            }
          }
        }
      }
    }
}

void DiHadronCorrelationMultiBase::AssignTrgPtBins(double pt, double eta, double phi, double mass, double charge, double effweight, bool isv0,
                                                   double pt_dau1, double eta_dau1, double phi_dau1, double mass_dau1,
                                                   double pt_dau2, double eta_dau2, double phi_dau2, double mass_dau2 )
{
   if(cutPara.IsPtWeightTrg) effweight = effweight / pt;
   if(cutPara.IsDebug)
   {
     hdNdetadphiAll_trg->Fill(eta,phi);
     hdNdetadptAll_trg->Fill(eta,pt);
     hdNdetadpAll_trg->Fill(eta,pt*cosh(eta));
     hdNdetadphiCorrAll_trg->Fill(eta,phi,1.0/effweight);
     hdNdetadptCorrAll_trg->Fill(eta,pt,1.0/effweight);
     hPtAll_trg->Fill(pt,1.0/hPtAll_trg->GetBinWidth(hPtAll_trg->FindBin(pt)));
     hPtCorrAll_trg->Fill(pt,1./effweight/hPtAll_trg->GetBinWidth(hPtAll_trg->FindBin(pt)));

     double ptot = pt/sqrt(1-tanh(eta)*tanh(eta));
     hPTotAll_trg->Fill(ptot,1.0/hPTotAll_trg->GetBinWidth(hPTotAll_trg->FindBin(ptot)));
   }

   TLorentzVector pvector;
   pvector.SetPtEtaPhiM(pt,eta,phi,mass);
   TLorentzVector pvector_dau1;
   TLorentzVector pvector_dau2;
   if(isv0)
   {
     pvector_dau1.SetPtEtaPhiM(pt_dau1,eta_dau1,phi_dau1,mass_dau1);
     pvector_dau2.SetPtEtaPhiM(pt_dau2,eta_dau2,phi_dau2,mass_dau2);
//     hdNdetadphiAll_dau1_trg->Fill(eta_dau1,phi_dau1);
//     hdNdetadphiAll_dau2_trg->Fill(eta_dau2,phi_dau2);
   }

   for(int pttrgbin=0;pttrgbin<(int)(cutPara.pttrgmin.size());pttrgbin++)
   {
     if(GetPttrgBin(pt,eta,pttrgbin))
     {
       if(cutPara.IsV0SignalTrg && !cutPara.IsV0BkgTrg && fabs(mass-cutPara.massmean_trg[pttrgbin])>2*cutPara.masswidth_trg[pttrgbin]) continue;
       if(!cutPara.IsV0SignalTrg && cutPara.IsV0BkgTrg && fabs(mass-cutPara.massmean_trg[pttrgbin])<3*cutPara.masswidth_trg[pttrgbin]) continue;

       hpT_Signal_trg[pttrgbin]->Fill(pt);
       hpTCorr_Signal_trg[pttrgbin]->Fill(pt,1.0/effweight);
       hpTMult_Signal_trg[pttrgbin]->Fill(nMult,pt);
       hpTCorrMult_Signal_trg[pttrgbin]->Fill(nMultCorr,pt,1.0/effweight);

// cout<<eta<<" "<<pt<<" "<<effweight<<" "<<pttrgbin<<endl;

       hHFvsPt->Fill(hft,pt,1.0/effweight);
       hNpixelvsPt->Fill(npixel,pt,1.0/effweight);
       hNtrkCorrvsPt->Fill(nMultCorr,pt,1.0/effweight);
       hNtrkvsPt->Fill(nMult,pt,1.0/effweight);

       if(cutPara.IsDebug)
       {
         hdNdetadphi_trg[pttrgbin]->Fill(eta,phi);
         hdNdetadphiCorr_trg[pttrgbin]->Fill(eta,phi,1.0/effweight);
       }
       nMultAll_trg++; nMultAllCorr_trg = nMultAllCorr_trg + 1.0/effweight;
       (eventcorr->pVect_trg[pttrgbin]).push_back(pvector);
       if(isv0)
       {
         (eventcorr->pVect_trg_dau1[pttrgbin]).push_back(pvector_dau1);
         (eventcorr->pVect_trg_dau2[pttrgbin]).push_back(pvector_dau2);
       }
       (eventcorr->chgVect_trg[pttrgbin]).push_back(charge);
       (eventcorr->effVect_trg[pttrgbin]).push_back(effweight);
    }
   }
}

void DiHadronCorrelationMultiBase::AssignAssPtBins(double pt, double eta, double phi, double mass, double charge, double effweight, bool isv0,
                                                   double pt_dau1, double eta_dau1, double phi_dau1, double mass_dau1,
                                                   double pt_dau2, double eta_dau2, double phi_dau2, double mass_dau2 )
{
   if(cutPara.IsPtWeightAss) effweight = effweight / pt;

   if(cutPara.IsDebug)
   {
     hdNdetadphiAll_ass->Fill(eta,phi);
     hdNdetadptAll_ass->Fill(eta,pt);
     hdNdetadpAll_ass->Fill(eta,pt*cosh(eta));
     hdNdetadphiCorrAll_ass->Fill(eta,phi,1.0/effweight);
     hdNdetadptCorrAll_ass->Fill(eta,pt,1.0/effweight);
     hPtAll_ass->Fill(pt);
     hPtCorrAll_ass->Fill(pt,1.0/effweight);
     double ptot = pt/sqrt(1-tanh(eta)*tanh(eta));
     hPTotAll_ass->Fill(ptot,1.0/hPTotAll_ass->GetBinWidth(hPTotAll_ass->FindBin(ptot)));
   }

   TLorentzVector pvector;
   pvector.SetPtEtaPhiM(pt,eta,phi,mass);
   TLorentzVector pvector_dau1;
   TLorentzVector pvector_dau2;
   if(isv0)
   {
     pvector_dau1.SetPtEtaPhiM(pt_dau1,eta_dau1,phi_dau1,mass_dau1);
     pvector_dau2.SetPtEtaPhiM(pt_dau2,eta_dau2,phi_dau2,mass_dau2);
//     hdNdetadphiAll_dau1_ass->Fill(eta_dau1,phi_dau1);
//     hdNdetadphiAll_dau2_ass->Fill(eta_dau2,phi_dau2);
   }

   for(int ptassbin=0;ptassbin<(int)(cutPara.ptassmin.size());ptassbin++)
   {
     if(GetPtassBin(pt,eta,ptassbin))
     {
       if(cutPara.IsV0SignalAss && !cutPara.IsV0BkgAss && fabs(mass-cutPara.massmean_ass[ptassbin])>2*cutPara.masswidth_ass[ptassbin]) continue;
       if(!cutPara.IsV0SignalAss && cutPara.IsV0BkgAss && fabs(mass-cutPara.massmean_ass[ptassbin])<3*cutPara.masswidth_ass[ptassbin]) continue;

       hpT_Signal_ass[ptassbin]->Fill(pt);
       hpTCorr_Signal_ass[ptassbin]->Fill(pt,1.0/effweight);
       if(cutPara.IsDebug)
       {
         hdNdetadphi_ass[ptassbin]->Fill(eta,phi);
         hdNdetadphiCorr_ass[ptassbin]->Fill(eta,phi,1.0/effweight);
       }
       nMultAll_ass++; nMultAllCorr_ass = nMultAllCorr_ass + 1.0/effweight;
       (eventcorr->pVect_ass[ptassbin]).push_back(pvector);
       if(isv0)
       {
         (eventcorr->pVect_ass_dau1[ptassbin]).push_back(pvector_dau1);
         (eventcorr->pVect_ass_dau2[ptassbin]).push_back(pvector_dau2);
       }
       (eventcorr->chgVect_ass[ptassbin]).push_back(charge);
       (eventcorr->effVect_ass[ptassbin]).push_back(effweight);
     }
   }
}

double DiHadronCorrelationMultiBase::GetEventEngineer(const edm::Event& iEvent, const edm::EventSetup& iSetup, int nn)
{
   edm::Handle<CaloTowerCollection> calotowers;
   iEvent.getByLabel(std::string("towerMaker"), calotowers);
   if(!calotowers->size()) { cout<<"Invalid or empty calotower collection!"<<endl; return -1; }

   double q2x=0;
   double q2y=0;
   double wsum=0;
   for(unsigned it=0; it<calotowers->size(); ++it){

     const CaloTower & calotower = (*calotowers)[it];

     double eta = calotower.eta();
     double phi = calotower.phi();
     double et  = calotower.et();

     if(calotower.energy()<3) continue;
     if(fabs(eta)<3) continue;

     q2x = q2x + et*cos(nn*phi);
     q2y = q2y + et*sin(nn*phi);
     wsum = wsum + et;
   }
   q2x = q2x / wsum;
   q2y = q2y / wsum;

   double q2 = sqrt(q2x*q2x+q2y*q2y);
   return q2;
}

double DiHadronCorrelationMultiBase::GetRP(const edm::Event& iEvent, const edm::EventSetup& iSetup, int index)
{
   double phi0 = -999.0;
   double b = -999.0;

   edm::Handle<HepMCProduct> mc;
   iEvent.getByLabel("generator",mc);
   const GenEvent* evt = mc->GetEvent();
   const HeavyIon* hi = evt->heavy_ion();
   if(!hi) {cout<<"Cannot find HI event information!"<<endl; return phi0;}

   phi0 = hi->event_plane_angle();   
   b = hi->impact_parameter();

   if(index==1) return phi0;
   else if(index==2) return b;
   else return -999.0;
}


int DiHadronCorrelationMultiBase::GetCentralityBin(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
//  if(!cent) cent = new CentralityProvider(iSetup);
//  cent->newEvent(iEvent,iSetup);

  edm::Handle<reco::Centrality> cent;
  iEvent.getByToken(centtag_, cent);

  iEvent.getByToken(tag_,cbin_);
  int bin = *cbin_;

  hft = cent->EtHFtowerSum();
  npixel = cent->multiplicityPixel();
  int ntrk = cent->Ntracks();
  zdc = 10000.*(cent->zdcSumPlus()/7309.+cent->zdcSumMinus()/11420.);

  if(zdc>(-170.*(hft-8500.))) { bin=-1; return bin; }

  if(cutPara.IsDebug)
  {
    hHFTowerSum->Fill(hft);
    hHFvsNpixel->Fill(hft,npixel);
    hHFvsZDC->Fill(hft,zdc);
  }

//  int bin = cent->getBin();

// UCC centrality bins
//0.1%: 4730-4900
//0.01%: 4900-

  if(hft>4730 && hft<4900 && cutPara.centmin==1000 && cutPara.centmax == 10000) bin=1000;
  if(hft>4900 && cutPara.centmin==2000 && cutPara.centmax == 10000) bin=2000;

/*
  if(hft>3400 && hft<3600 && npixel>51000 && npixel<57000 && cutPara.centmin==2000 && cutPara.centmax == 10000) bin=2000;
  if(hft>3400 && hft<3600 && npixel>51000 && npixel<57000 && zdc<2000 && cutPara.centmin==3000 && cutPara.centmax == 10000) bin=3000;
  if(hft>3129.3 && cutPara.centmin==500 && cutPara.centmax == 10000) bin=500;
  if(hft>3094.3 && npixel>48787 && cutPara.centmin==510 && cutPara.centmax == 10000) bin=510;
  if((7.0*hft+zdc)<36000 && cutPara.centmin==5000 && cutPara.centmax == 10000) bin=5000;
//  if((7.0*hft+zdc)<36000 && hft>3260 && npixel>51400 && cutPara.centmin==1100 && cutPara.centmax == 10000) bin=1100; // hft>3420 && npixel>31300 && 45*hft+zdc<188372
//  if((20.*hft+zdc)<114000 && hft>3400 && npixel>31000 && cutPara.centmin==1100 && cutPara.centmax == 10000) bin=1100;
  if((20.*hft+zdc)<114000 && hft>3420 && npixel>31500 && cutPara.centmin==1100 && cutPara.centmax == 10000) bin=1100;
  if((7.0*hft+zdc)<36000 && 1.15*hft>zdc && hft>3260 && npixel>51400 && cutPara.centmin==1200 && cutPara.centmax == 10000) bin=1200;
  if((7.0*hft+zdc)<36000 && hft>3393 && npixel>53450 && cutPara.centmin==2100 && cutPara.centmax == 10000) bin=2100;
  if((7.0*hft+zdc)<36000 && 1.15*hft>zdc && hft>3393 && npixel>53450 && cutPara.centmin==2200 && cutPara.centmax == 10000) bin=2200;
*/
// pPb centrality bins
/*
  if(!cutPara.centralityCollection.Contains("pACentrality")) return bin;
  if(hft<10.) bin=0;  
  if(hft>10. && hft<20.) bin=1;
  if(hft>20. && hft<30.) bin=2;
  if(hft>30. && hft<40.) bin=3;
  if(hft>40. && hft<60.) bin=4;
  if(hft>60. && hft<80.) bin=5;
  if(hft>80. && hft<100.) bin=6;
  if(hft>100. && hft<120.) bin=7;
  if(hft>120. && hft<140.) bin=8;
  if(hft>140. && hft<155.) bin=9;
  if(hft>155. && hft<170.) bin=10;
  if(hft>170. && hft<190.) bin=11;
  if(hft>190. && hft<210.) bin=12;
  if(hft>210. && hft<250.) bin=13;
  if(hft>250.) bin=14;
*/
  return bin;
}

double DiHadronCorrelationMultiBase::GetDeltaEta(double eta_trg, double eta_ass)
{
        double deltaEta=eta_ass-eta_trg;
        return deltaEta;
}

double DiHadronCorrelationMultiBase::GetDeltaPhi(double phi_trg, double phi_ass)
{     
        double deltaPhi=phi_ass-phi_trg;
        if(deltaPhi>PI)
          deltaPhi=deltaPhi-2*PI;
        if(deltaPhi<-PI/2)
          deltaPhi=deltaPhi+2*PI;
        return deltaPhi;
}

bool DiHadronCorrelationMultiBase::GetPttrgBin(double pt, double eta, int itrg)
{
    if(pt>=cutPara.pttrgmin[itrg] && pt<=cutPara.pttrgmax[itrg] && eta>=cutPara.etatrgmin && eta<=cutPara.etatrgmax && !cutPara.IsTrgEtaCutAbs) 
      return kTRUE; 
    else if(pt>=cutPara.pttrgmin[itrg] && pt<=cutPara.pttrgmax[itrg] && fabs(eta)>=cutPara.etatrgmin && fabs(eta)<=cutPara.etatrgmax && cutPara.IsTrgEtaCutAbs)
      return kTRUE;
    else 
      return kFALSE;
}

bool DiHadronCorrelationMultiBase::GetPtassBin(double pt, double eta, int jass)
{
    if(pt>=cutPara.ptassmin[jass] && pt<=cutPara.ptassmax[jass] && eta>=cutPara.etaassmin && eta<=cutPara.etaassmax && !cutPara.IsAssEtaCutAbs) 
      return kTRUE;
    else if(pt>=cutPara.ptassmin[jass] && pt<=cutPara.ptassmax[jass] && fabs(eta)>=cutPara.etaassmin && fabs(eta)<=cutPara.etaassmax && cutPara.IsAssEtaCutAbs)
      return kTRUE;
    else 
      return kFALSE;
}

double DiHadronCorrelationMultiBase::GetTrgWeight(double nmult)
{
  double trgweight=1.0;
  if(hTrgWeight) trgweight = hTrgWeight->GetBinContent(hTrgWeight->FindBin(nmult));
  return trgweight;
}

double DiHadronCorrelationMultiBase::GetEffWeight(double eta, double phi, double pt, double zvtx, int centbin, double charge)
{
//  if(pt>2.0) pt=2.0;
  double effweight = 1.0;
  if(hEffWeight) 
  {
    effweight *= hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt,centbin));
    if(effweight<0.00001) effweight=1.0;
  }

  if(hFakWeight)
  {
    effweight /= (1-hFakWeight->GetBinContent(hFakWeight->FindBin(eta,pt,centbin)));
  }

  if(hEtaPhiWeightPos && charge>0) effweight *= hEtaPhiWeightPos->GetBinContent(hEtaPhiWeightPos->FindBin(eta,phi));
  if(hEtaPhiWeightNeg && charge<0) effweight *= hEtaPhiWeightNeg->GetBinContent(hEtaPhiWeightNeg->FindBin(eta,phi));

  return effweight;
}

bool DiHadronCorrelationMultiBase::Acceptance(double eta, double phi, double pt) 
{
   if(fabs(eta)>2.4) return false;
// v1
/*
   if(eta>1.5 && eta<2.2 && phi>-3.0 && phi<-1.8) return false;
   if(eta>0.5 && eta<0.8 && phi>0.4 && phi<2.6) return false;
   if(eta>-0.7 && eta<-0.1 && phi>-1.7 && phi<-0.3) return false;
   if(eta>-2.5 && eta<-1.0 && phi>0.0 && phi<0.8) return false;
*/
//acc v2
/*
   if(eta>1.5 && eta<2.2 && phi>-3.0 && phi<-1.8) return false;
   if(eta>0.5 && eta<2.0 && phi>0.4 && phi<2.6) return false;
   if(eta>-0.7 && eta<-0.1 && phi>-1.7 && phi<-0.3) return false;
   if(eta>-2.5 && eta<-1.0 && phi>0.0 && phi<0.8) return false;
*/
   double random = gRandom->Rndm();
   double erf_pt = TMath::Erf(pt/2.0);

//cout<<random<<" "<<erf_pt<<" "<<pt<<" "<<(random > erf_pt)<<endl;

   if(random > erf_pt) return false;

   return true;
}

DiHadronCorrelationMultiBase::ParticleType DiHadronCorrelationMultiBase::GetParticleID(TString particleid)
{
  ParticleType type;
  if(particleid == "GenParticle")
    type=kGenParticle;
  else if(particleid == "Generator")
    type=kGenerator;
  else if(particleid == "Track")
    type=kTrack;
  else if(particleid == "TrackP")
    type=kTrackP;
  else if(particleid == "TrackM")
    type=kTrackM;
  else if(particleid == "Jet")
    type=kJet;
  else if(particleid == "Muon")
    type=kMuon;
  else if(particleid == "Photon")
    type=kPhoton;
  else if(particleid == "EcalSC")
    type=kEcalSC;
  else if(particleid == "EcalBC")
    type=kEcalBC;
  else if(particleid == "PFHadron")
    type=kPFHadron;
  else if(particleid == "PFPhoton")
    type=kPFPhoton;  
  else if(particleid == "PFHadronPhoton")
    type=kPFHadronPhoton;
  else if(particleid == "PFPhotonTrack")
    type=kPFPhotonTrack;
  else if(particleid == "PFElectron")
    type=kPFElectron;
  else if(particleid == "PFMuon")
    type=kPFMuon;
  else if(particleid == "PFNeutral")
    type=kPFNeutral;
  else if(particleid == "PFHadronHF")
    type=kPFHadronHF;
  else if(particleid == "PFEgammaHF")
    type=kPFEgammaHF;
  else if(particleid == "PionZero")
    type=kPionZero;
  else if(particleid == "PionZeroBkgUp")
    type=kPionZeroBkgUp;
  else if(particleid == "PionZeroBkgDown")
    type=kPionZeroBkgDown;
  else if(particleid == "CaloTower")
    type=kCaloTower;
  else if(particleid == "EcalRecHit")
    type=kEcalRecHit;
  else if(particleid == "HcalRecHit")
    type=kHcalRecHit;
  else if(particleid == "Kshort")
    type=kKshort;
  else if(particleid == "Lambda")
    type=kLambda;
  else if(particleid == "LambdaP")
    type=kLambdaP;
  else if(particleid == "LambdaM")
    type=kLambdaM;
  else if(particleid == "D0")
    type=kD0;
  else if(particleid == "Conversion")
    type=kConversion;
  else if(particleid == "PFCandidate")
    type=kPFCandidate;
  return type;
}
