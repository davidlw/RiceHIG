void compare()
{
  TFile* f = new TFile("V0Eff_counting_PbPbPeri.root");
  TFile* f1 = new TFile("V0Eff_counting_10M.root");

  TH2D* ks2D = (TH2D*)f->Get("EffCountEtaPt_ks");
  TH2D* la2D = (TH2D*)f->Get("EffCountEtaPt_la");
  TH1D* ks1D = (TH1D*)f->Get("EffCountPt_ks_7");
  TH1D* la1D = (TH1D*)f->Get("EffCountPt_la_7");

  TH2D* ks2D1 = (TH2D*)f1->Get("EffCountEtaPt_ks");
  TH2D* la2D1 = (TH2D*)f1->Get("EffCountEtaPt_la");
  TH1D* ks1D1 = (TH1D*)f1->Get("EffCountPt_ks_7");
  TH1D* la1D1 = (TH1D*)f1->Get("EffCountPt_la_7");

  TH1D* ks1Deta = (TH1D*)f->Get("EffCountEta_ks");
  TH1D* la1Deta = (TH1D*)f->Get("EffCountEta_la");
  TH1D* ks1D1eta = (TH1D*)f1->Get("EffCountEta_ks");
  TH1D* la1D1eta = (TH1D*)f1->Get("EffCountEta_la");

  TCanvas* aa = new TCanvas("aa","aa",800,400);
  aa->Divide(2,1);
  aa->cd(1);
  ks2D->SetAxisRange(0,0.3,"Z");
  ks2D->GetXaxis()->CenterTitle();
  ks2D->GetYaxis()->CenterTitle();
  ks2D->GetZaxis()->CenterTitle();
  ks2D->SetTitle("Efficiency of K^{0}_{short};#eta;p_{T} (GeV/c);");
  ks2D->Draw("lego2");
  aa->cd(2);
  la2D->SetAxisRange(0,0.3,"Z");
  la2D->GetXaxis()->CenterTitle();
  la2D->GetYaxis()->CenterTitle();
  la2D->GetZaxis()->CenterTitle();
  la2D->SetTitle("Efficiency of #Lambda;#eta;p_{T} (GeV/c);");
  la2D->Draw("lego2");
//  SaveCanvas(aa,"HI/V0","EfficiencyVsEtaPt_V0");

  TCanvas* a = new TCanvas("a","a",900,900);
  a->Divide(2,2);
  a->cd(1);
  ks1D->SetMarkerColor(2);
  ks1D->Scale(1.0/0.692);
  ks1D->SetAxisRange(0,0.4,"Y");
  ks1D->Draw("PE");
  ks1D1->Draw("PESAME");
  a->cd(2);
  la1D->SetMarkerColor(2);
  la1D->Scale(1.0/0.639);
  la1D->SetAxisRange(0,0.4,"Y");
  la1D->Draw("PE");
  la1D1->Draw("PESAME");
  a->cd(3);
  ks1Deta->SetMarkerColor(2);
  ks1Deta->Scale(1.0/0.692);
  ks1Deta->SetAxisRange(0,0.4,"Y");
  ks1Deta->Draw("PE");
  ks1D1eta->Draw("PESAME");
  a->cd(4);
  la1Deta->SetMarkerColor(2);
  la1Deta->Scale(1.0/0.639);
  la1Deta->SetAxisRange(0,0.4,"Y");
  la1Deta->Draw("PE");
  la1D1eta->Draw("PESAME");

  TCanvas* c10 = new TCanvas("c10","c10",900,600);
  c10->Divide(3,2);
  TCanvas* c11 = new TCanvas("c11","c11",900,600);
  c11->Divide(3,2);

  TH1D* hEffvsPt_ks[6];
  TH1D* hEffvsPt_la[6];
  TH1D* hEffvsPt1_ks[6];
  TH1D* hEffvsPt1_la[6];
  TString string_eta[6] = {"-2.4<#eta<-1.6","-1.6<#eta<-0.8","-0.8<#eta<0","0<#eta<0.8","0.8<#eta<1.6","1.6<#eta<2.4"};
  for(int i=0;i<6;i++)
  {
    c10->cd(i+1);
//    hEffvsPt1_ks[i] = (TH1D*)f1->Get(Form("EffCountPt_ks_%d",i+1));
//    hEffvsPt1_ks[i]->Draw("PE");
    hEffvsPt_ks[i] = (TH1D*)f->Get(Form("EffCountPt_ks_%d",i+1));
    hEffvsPt_ks[i]->GetXaxis()->CenterTitle();
    hEffvsPt_ks[i]->GetYaxis()->CenterTitle();
    hEffvsPt_ks[i]->SetAxisRange(0.0,0.3,"Y");
    hEffvsPt_ks[i]->SetMarkerStyle(20);
    hEffvsPt_ks[i]->SetMarkerColor(2);
//    hEffvsPt_ks[i]->Scale(1.0/0.692);
    hEffvsPt_ks[i]->SetTitle(Form("%s;p_{T} (GeV/c);Efficiency of K^{0}_{short}",string_eta[i].Data())); 
    hEffvsPt_ks[i]->Draw("PE");
    hEffvsPt1_ks[i] = (TH1D*)f1->Get(Form("EffCountPt_ks_%d",i+1));
    hEffvsPt1_ks[i]->SetMarkerStyle(21);
    hEffvsPt1_ks[i]->SetMarkerColor(4);
    hEffvsPt1_ks[i]->Draw("PESAME");

    c11->cd(i+1);
//    hEffvsPt1_la[i] = (TH1D*)f1->Get(Form("EffCountPt_la_%d",i+1)); 
//    hEffvsPt1_la[i]->Draw("PE");
    hEffvsPt_la[i] = (TH1D*)f->Get(Form("EffCountPt_la_%d",i+1)); 
    hEffvsPt_la[i]->SetMarkerStyle(20);
    hEffvsPt_la[i]->SetMarkerColor(2);
//    hEffvsPt_la[i]->Scale(1.0/0.639);
    hEffvsPt_la[i]->GetXaxis()->CenterTitle();
    hEffvsPt_la[i]->GetYaxis()->CenterTitle();
    hEffvsPt_la[i]->SetAxisRange(0.0,0.3,"Y");
    hEffvsPt_la[i]->SetTitle(Form("%s;p_{T} (GeV/c);Efficiency of #Lambda",string_eta[i].Data()));
    hEffvsPt_la[i]->Draw("PE");
    hEffvsPt1_la[i] = (TH1D*)f1->Get(Form("EffCountPt_la_%d",i+1));
    hEffvsPt1_la[i]->SetMarkerStyle(21);
    hEffvsPt1_la[i]->SetMarkerColor(4);
    hEffvsPt1_la[i]->Draw("PESAME");
  }
 
  c10->cd(1);
  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->DrawLatex(0.3,0.8,"HIJING pPb MC 5.02 TeV");

  c11->cd(1);
  TLatex* latex1 = new TLatex();
  latex1->SetNDC();
  latex1->DrawLatex(0.3,0.8,"HIJING pPb MC 5.02 TeV");
return; 
  SaveCanvas(c10,"HI/V0","EfficiencyVsPt_Ks");
  SaveCanvas(c11,"HI/V0","EfficiencyVsPt_Lambda");
 /* 
  TFile* fout = new TFile("Efficiency2D_V0_pPbHijing_counting.root","recreate");
  ks2Dfiner->Write();
  la2Dfiner->Write();
  fout->Close();
*/
}

void compare_HijingEPOS()
{
  TFile* f = new TFile("V0Eff_counting_all.root");
  TFile* f1 = new TFile("V0Eff_counting_EPOS.root");

  TFile* f2 = new TFile("V0Eff_matching.root");
  TFile* f22 = new TFile("V0Eff_matching_tighter.root");
  TFile* f222 = new TFile("V0Eff_matching_looser.root");
  TFile* f3 = new TFile("V0Eff_matching_EPOS.root");
  TFile* f4 = new TFile("V0Eff_matching_EPOS_tighter.root");
  TFile* f5 = new TFile("V0Eff_matching_EPOS_looser.root");
  TH1D* ksetar = (TH1D*)f2->Get("ksetar");
  TH1D* laetar = (TH1D*)f2->Get("laetar");
  TH1D* ksetar1 = (TH1D*)f3->Get("ksetar");
  TH1D* laetar1 = (TH1D*)f3->Get("laetar");
  TH1D* lasec = (TH1D*)f3->Get("SecCountEtaPt_la");
  TH1D* lasec1 = (TH1D*)f4->Get("SecCountEtaPt_la");
  TH1D* lasec2 = (TH1D*)f5->Get("SecCountEtaPt_la");
  TH1D* lasech = (TH1D*)f2->Get("SecCountEtaPt_la");
  TH1D* lasech1 = (TH1D*)f22->Get("SecCountEtaPt_la");
  TH1D* lasech2 = (TH1D*)f222->Get("SecCountEtaPt_la");

  TCanvas* c10 = new TCanvas("c10","c10",900,600);
  c10->Divide(3,2);
  TCanvas* c11 = new TCanvas("c11","c11",900,600);
  c11->Divide(3,2);

  TH1D* hEffvsPt_ks[6];
  TH1D* hEffvsPt_la[6];
  TH1D* hEffvsPt1_ks[6];
  TH1D* hEffvsPt1_la[6];
  TString string_eta[6] = {"-2.4<#eta<-1.6","-1.6<#eta<-0.8","-0.8<#eta<0","0<#eta<0.8","0.8<#eta<1.6","1.6<#eta<2.4"};
  for(int i=0;i<6;i++)
  {
    c10->cd(i+1);
    hEffvsPt_ks[i] = (TH1D*)f->Get(Form("EffCountPt_ks_%d",i+1));
    hEffvsPt_ks[i]->GetXaxis()->CenterTitle();
    hEffvsPt_ks[i]->GetYaxis()->CenterTitle();
    hEffvsPt_ks[i]->SetAxisRange(0.0,0.3,"Y");
    hEffvsPt_ks[i]->SetMarkerColor(2);
    hEffvsPt_ks[i]->SetTitle(Form("%s;p_{T} (GeV/c);Efficiency of K^{0}_{short}",string_eta[i].Data()));
    hEffvsPt_ks[i]->Draw("PE");
    hEffvsPt1_ks[i] = (TH1D*)f1->Get(Form("EffCountPt_ks_%d",i+1));
    hEffvsPt1_ks[i]->Draw("PESAME");

    c11->cd(i+1);
    hEffvsPt_la[i] = (TH1D*)f->Get(Form("EffCountPt_la_%d",i+1));
    hEffvsPt_la[i]->SetMarkerColor(2);
    hEffvsPt_la[i]->GetXaxis()->CenterTitle();
    hEffvsPt_la[i]->GetYaxis()->CenterTitle();
    hEffvsPt_la[i]->SetAxisRange(0.0,0.3,"Y");
    hEffvsPt_la[i]->SetTitle(Form("%s;p_{T} (GeV/c);Efficiency of #Lambda",string_eta[i].Data()));
    hEffvsPt_la[i]->Draw("PE");
    hEffvsPt1_la[i] = (TH1D*)f1->Get(Form("EffCountPt_la_%d",i+1));
    hEffvsPt1_la[i]->Draw("PESAME");
  }

  TCanvas* c2 = new TCanvas("c2","c2",800,400);
  c2->Divide(2,1);
  c2->cd(1);
  ksetar->SetMarkerColor(2);
  ksetar1->Draw("PE");
  ksetar->Draw("PESAME");
  c2->cd(2);
  laetar->SetMarkerColor(2);
  laetar1->Draw("PE");
  laetar->Draw("PESAME");

  TCanvas* c3 = new TCanvas("c3","c3",800,400);
  c3->Divide(2,1);
  c3->cd(1);
  lasech1->SetTitle("Hijing");
  lasech->SetMarkerColor(2);
  lasech2->SetMarkerColor(4);
  lasech1->SetAxisRange(0,0.15,"Y");
  lasech1->Draw("PE");
  lasech->Draw("PESAME");
  lasech2->Draw("PESAME");
  c3->cd(2);
  lasec1->SetTitle("EPOS");
  lasec->SetMarkerColor(2);
  lasec2->SetMarkerColor(4);
  lasec1->SetAxisRange(0,0.15,"Y");
  lasec1->Draw("PE");
  lasec->Draw("PESAME");
  lasec2->Draw("PESAME");

  TLegend* legend = new TLegend(0.5,0.7,0.85,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(hEffvsPt_ks[0],"HIJING","P");
  legend->AddEntry(hEffvsPt1_ks[0],"EPOS","P");
  c10->cd(1);
  legend->Draw();
  c11->cd(1);
  legend->Draw();
  c2->cd(1); 
  legend->Draw();
  c2->cd(2);
  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->DrawLatex(0.5,0.7,"1<p_{T}<1.5");
  latex->DrawLatex(0.5,0.6,"|#eta|<2.4");
  latex->Draw("same");
  
  TLegend* legend1 = new TLegend(0.5,0.7,0.85,0.9);
  legend1->SetFillColor(0);
  legend1->AddEntry(lasech,"Standard","P");
  legend1->AddEntry(lasech1,"Looser","P");
  legend1->AddEntry(lasech2,"Tighter","P");
  c3->cd(1);
  legend1->Draw();

  SaveCanvas(c10,"HI/V0","EfficiencyVsPt_Ks_compare");
  SaveCanvas(c11,"HI/V0","EfficiencyVsPt_Lambda_compare");
  SaveCanvas(c2,"HI/V0","EfficiencyVsR_KsLambda_compare");
  SaveCanvas(c3,"HI/V0","CascadeVsPt_compare");
}
