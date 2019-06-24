void compare_spectra()
{
  TFile* f = new TFile("/eos/cms/store/group/phys_heavyions/flowcorr/ptspectra_mb_v2.root");
  TFile* f1 = new TFile("/eos/cms/store/group/phys_heavyions/flowcorr/ptspectra_hm250_v2.root");
  TFile* f2 = new TFile("/eos/cms/store/group/phys_heavyions/flowcorr/ptspectra_hm_v2.root");
  TFile* f3 = new TFile("/eos/cms/store/group/phys_heavyions/flowcorr/ptspectra_hm120185_v2.root");

  TH2D* h2Dnew = (TH2D*)f->Get("ptspectra_ana/ptmult_signal_trg_0");
  TH2D* h2Dnew1 = (TH2D*)f1->Get("ptspectra_ana/ptmult_signal_trg_0");
  TH2D* h2Dnew2 = (TH2D*)f2->Get("ptspectra_ana/ptmult_signal_trg_0");
  TH2D* h2Dnew3 = (TH2D*)f3->Get("ptspectra_ana/ptmult_signal_trg_0");
  TH1D* hmult = (TH1D*)f->Get("ptspectra_ana/multrawall");
  TH1D* hmult1 = (TH1D*)f1->Get("ptspectra_ana/multrawall");
  TH1D* hmult2 = (TH1D*)f2->Get("ptspectra_ana/multrawall");
  TH1D* hmult3 = (TH1D*)f3->Get("ptspectra_ana/multrawall");

  TH1D* hnewarr[10];
  hnewarr[0] = (TH1D*)h2Dnew->ProjectionX("hnew_0",1,7,"e");
  hnewarr[1] = (TH1D*)h2Dnew->ProjectionX("hnew_1",8,12,"e");
  hnewarr[2] = (TH1D*)h2Dnew->ProjectionX("hnew_2",13,18,"e");
  hnewarr[3] = (TH1D*)h2Dnew->ProjectionX("hnew_3",19,24,"e");
  TH1D* hnew = (TH1D*)h2Dnew->ProjectionX("hnew",-1,-1,"e");
  TH1D* hnew1 = (TH1D*)h2Dnew1->ProjectionX("hnew1",65,10000,"e");
  TH1D* hnew2 = (TH1D*)h2Dnew2->ProjectionX("hnew2",-1,-1,"e");
  TH1D* hnew3 = (TH1D*)h2Dnew3->ProjectionX("hnew3",-1,-1,"e");

  hnew->Scale(1.0/hmult->Integral()/hmult->GetMean());
//  hnew1->Scale(1.0/hmult1->Integral()/hmult1->GetMean());
  hnew2->Scale(1.0/hmult2->Integral()/hmult2->GetMean());
  hnew3->Scale(1.0/hmult3->Integral()/hmult3->GetMean());

  hmult1->SetAxisRange(320,10000,"X");
  hnew1->Scale(1.0/hmult1->Integral(321,10000)/hmult1->GetMean());

  hmult->SetAxisRange(0,34,"X"); 
  hnewarr[0]->Scale(1.0/hmult->Integral(1,35)/hmult->GetMean());
  hmult->SetAxisRange(35,59,"X");
  hnewarr[1]->Scale(1.0/hmult->Integral(36,60)/hmult->GetMean());
  hmult->SetAxisRange(60,89,"X");
  hnewarr[2]->Scale(1.0/hmult->Integral(61,90)/hmult->GetMean());
  hmult->SetAxisRange(90,119,"X");
  hnewarr[3]->Scale(1.0/hmult->Integral(91,120)/hmult->GetMean());

  double ptbins[208]={0};
  int nbins=0;
  while(ptbins[nbins]<10.-0.001) {ptbins[nbins+1] = ptbins[nbins]+0.2; nbins++;}
  while(ptbins[nbins]<20.-0.001) {ptbins[nbins+1] = ptbins[nbins]+0.4; nbins++;}
  while(ptbins[nbins]<40.-0.001) {ptbins[nbins+1] = ptbins[nbins]+2.0; nbins++;}
  while(ptbins[nbins]<60.-0.001) {ptbins[nbins+1] = ptbins[nbins]+4.0; nbins++;}
  while(ptbins[nbins]<100.-0.001) {ptbins[nbins+1] = ptbins[nbins]+10.0; nbins++;}
  while(ptbins[nbins]<200.+0.001) {ptbins[nbins+1] = ptbins[nbins]+25.0; nbins++;}

  cout<<nbins<<endl; 
  for(int i=0;i<nbins;i++) cout<<i<<" "<<ptbins[i]<<endl;

  TH1D* harr[10];
  TH1D* h = (TH1D*)hnew->Rebin(nbins-2,"h",ptbins);
  TH1D* h1 = (TH1D*)hnew1->Rebin(nbins-2,"h1",ptbins);
  TH1D* h2 = (TH1D*)hnew2->Rebin(nbins-2,"h2",ptbins);
  TH1D* h3 = (TH1D*)hnew3->Rebin(nbins-2,"h3",ptbins);
  harr[0] = (TH1D*)hnewarr[0]->Rebin(nbins-2,"h_0",ptbins);
  harr[1] = (TH1D*)hnewarr[1]->Rebin(nbins-2,"h_1",ptbins);
  harr[2] = (TH1D*)hnewarr[2]->Rebin(nbins-2,"h_2",ptbins);
  harr[3] = (TH1D*)hnewarr[3]->Rebin(nbins-2,"h_3",ptbins);

  h->SetMarkerStyle(20);
  h2->SetMarkerStyle(20);
  h3->SetMarkerStyle(20);
  h1->SetMarkerStyle(21);
  h->SetMarkerColor(2);
  h2->SetMarkerColor(7);
  h3->SetMarkerColor(5);
  h1->SetMarkerColor(4);

  harr[0]->SetMarkerStyle(20);
  harr[1]->SetMarkerStyle(20);
  harr[2]->SetMarkerStyle(20);
  harr[3]->SetMarkerStyle(20);
  harr[0]->SetMarkerColor(3);
  harr[1]->SetMarkerColor(1);
  harr[2]->SetMarkerColor(2);
  harr[3]->SetMarkerColor(6);

  h->SetAxisRange(0,200,"X");
  h1->SetAxisRange(0,200,"X");
  h2->SetAxisRange(0,200,"X");
  h3->SetAxisRange(0,200,"X");
  harr[0]->SetAxisRange(0,200,"X");
  harr[1]->SetAxisRange(0,200,"X");
  harr[2]->SetAxisRange(0,200,"X");
  harr[3]->SetAxisRange(0,200,"X");

  TH1D* h_ratio = (TH1D*)h1->Clone("ratio");
  TH1D* h2_ratio = (TH1D*)h2->Clone("ratio2");
  TH1D* h3_ratio = (TH1D*)h3->Clone("ratio3");
  h_ratio->Divide(h);
  h2_ratio->Divide(h);
  h3_ratio->Divide(h);

  TH1D* harr_ratio[10];
  harr_ratio[0] = (TH1D*)harr[0]->Clone("ratio_0");
  harr_ratio[1] = (TH1D*)harr[1]->Clone("ratio_1");
  harr_ratio[2] = (TH1D*)harr[2]->Clone("ratio_2");
  harr_ratio[3] = (TH1D*)harr[3]->Clone("ratio_3");
  harr_ratio[0]->Divide(h);
  harr_ratio[1]->Divide(h);
  harr_ratio[2]->Divide(h);
  harr_ratio[3]->Divide(h);

  TCanvas* c = new TCanvas("c","c",600,600);
  c->SetLogy();
  h->Draw("PE");
  h1->Draw("PESAME");

  h_ratio->SetAxisRange(0,2,"Y");
  h_ratio->SetAxisRange(0,20,"X");
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
//  c1->SetLogy();
  h_ratio->Draw();
  h2_ratio->Draw("PESAME");
  h3_ratio->Draw("PESAME");
  harr_ratio[0]->Draw("PESAME");
  harr_ratio[1]->Draw("PESAME");
  harr_ratio[2]->Draw("PESAME");
  harr_ratio[3]->Draw("PESAME");
}
