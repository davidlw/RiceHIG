void compare_spectra2()
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

  TH1D* hnew[10];
  TH1D* hnew1[10];
  TH1D* hnew2[10];
  TH1D* hnew3[10]; 

  int xmin = h2Dnew->GetXaxis()->FindBin(20);
  int xmax = h2Dnew->GetXaxis()->FindBin(40);
  hnew[0] = (TH1D*)h2Dnew->ProjectionY("hnew",xmin,xmax,"e");
  hnew1[0] = (TH1D*)h2Dnew1->ProjectionY("hnew1",xmin,xmax,"e");
  hnew2[0] = (TH1D*)h2Dnew2->ProjectionY("hnew2",xmin,xmax,"e");
  hnew3[0] = (TH1D*)h2Dnew3->ProjectionY("hnew3",xmin,xmax,"e");
  xmin = h2Dnew->GetXaxis()->FindBin(40);
  xmax = h2Dnew->GetXaxis()->FindBin(80);
  hnew[1] = (TH1D*)h2Dnew->ProjectionY("hnew_1",xmin,xmax,"e");
  hnew1[1] = (TH1D*)h2Dnew1->ProjectionY("hnew1_1",xmin,xmax,"e");
  hnew2[1] = (TH1D*)h2Dnew2->ProjectionY("hnew2_1",xmin,xmax,"e");
  hnew3[1] = (TH1D*)h2Dnew3->ProjectionY("hnew3_1",xmin,xmax,"e");

  TH1D* hmultnew = (TH1D*)hnew[0]->Clone("multnew");
  TH1D* hmultnew1 = (TH1D*)hnew1[0]->Clone("multnew1");
  TH1D* hmultnew2 = (TH1D*)hnew2[0]->Clone("multnew2");
  TH1D* hmultnew3 = (TH1D*)hnew3[0]->Clone("multnew3");
  hmultnew->Reset();
  hmultnew1->Reset();
  hmultnew2->Reset();
  hmultnew3->Reset();

  hmult->Rebin(5);
  hmult1->Rebin(5);
  hmult2->Rebin(5);
  hmult3->Rebin(5);
  for(int i=1;i<=hmultnew->GetNbinsX();i++)
  {
    hmultnew->SetBinContent(i,hmult->GetBinContent(i));
    hmultnew->SetBinError(i,hmult->GetBinError(i));

    hmultnew1->SetBinContent(i,hmult1->GetBinContent(i));
    hmultnew1->SetBinError(i,hmult1->GetBinError(i));

    hmultnew2->SetBinContent(i,hmult2->GetBinContent(i));
    hmultnew2->SetBinError(i,hmult2->GetBinError(i));

    hmultnew3->SetBinContent(i,hmult3->GetBinContent(i));
    hmultnew3->SetBinError(i,hmult3->GetBinError(i));
  }

  hnew[0]->Divide(hmultnew);
  hnew1[0]->Divide(hmultnew1);
  hnew2[0]->Divide(hmultnew2);
  hnew3[0]->Divide(hmultnew3);

  double norm = hnew[0]->GetBinContent(10);
  hnew[0]->Scale(1./norm);
  hnew1[0]->Scale(1./norm);
  hnew2[0]->Scale(1./norm);
  hnew3[0]->Scale(1./norm);

  hnew[0]->SetMarkerStyle(20);
  hnew1[0]->SetMarkerStyle(20);
  hnew2[0]->SetMarkerStyle(20);
  hnew3[0]->SetMarkerStyle(20);

  hnew[0]->SetMarkerColor(1);
  hnew1[0]->SetMarkerColor(2);
  hnew2[0]->SetMarkerColor(3);
  hnew3[0]->SetMarkerColor(4);

  hnew[0]->SetAxisRange(0,25,"Y");
  hnew[0]->SetAxisRange(0,350,"X");

  hnew[1]->Divide(hmultnew);
  hnew1[1]->Divide(hmultnew1);
  hnew2[1]->Divide(hmultnew2);
  hnew3[1]->Divide(hmultnew3);

  norm = hnew[1]->GetBinContent(10);
  hnew[1]->Scale(1./norm);
  hnew1[1]->Scale(1./norm);
  hnew2[1]->Scale(1./norm);
  hnew3[1]->Scale(1./norm);

  hnew[1]->SetMarkerStyle(24);
  hnew1[1]->SetMarkerStyle(24);
  hnew2[1]->SetMarkerStyle(24);
  hnew3[1]->SetMarkerStyle(24);

  hnew[1]->SetMarkerColor(1);
  hnew1[1]->SetMarkerColor(2);
  hnew2[1]->SetMarkerColor(3);
  hnew3[1]->SetMarkerColor(4);

  hnew[1]->SetAxisRange(0,25,"Y");
  hnew[1]->SetAxisRange(0,350,"X");


  TCanvas* c = new TCanvas("c","c",600,600);
//  c->SetLogy();
  hnew[0]->Draw("PE");
  hnew1[0]->Draw("PESAME");
  hnew2[0]->Draw("PESAME");
  hnew3[0]->Draw("PESAME");
  hnew[1]->Draw("PESAME");
  hnew1[1]->Draw("PESAME");
  hnew2[1]->Draw("PESAME");
  hnew3[1]->Draw("PESAME");

}
