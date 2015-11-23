void Lambda_Xi()
{
  TFile* fepos = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation/v0validation_V0EffMatchAna_EPOS_v20.root");
  TFile* fhijing = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation/v0validation_V0EffMatchAna_Hijing_v20.root");   

  TH2D* hnum_epos = fepos->Get("v0Validator/LamCascadeVsEtaPt_num");
  TH2D* hdenom_epos = fepos->Get("v0Validator/LamFakeVsEtaPt_denom");
  TH2D* hnum1_epos = fepos->Get("v0Validator/LamFakeVsEtaPt_num");
  hdenom_epos->Add(hnum1_epos,-1);
  hnum_epos->Divide(hdenom_epos);
  hnum_epos->SetAxisRange(0.7,9.9,"Y");

  TH2D* hnum_hijing = fhijing->Get("v0Validator/LamCascadeVsEtaPt_num");
  TH2D* hdenom_hijing = fhijing->Get("v0Validator/LamFakeVsEtaPt_denom");
  TH2D* hnum1_hijing = fhijing->Get("v0Validator/LamFakeVsEtaPt_num");
  hdenom_hijing->Add(hnum1_hijing,-1);
  hnum_hijing->Divide(hdenom_hijing);
  hnum_hijing->SetAxisRange(0.7,9.9,"Y");

  TH1D* hnum_epos_1D = (TH1D*)hnum_epos->ProjectionY("hnum_epos_1D",3,3,"e");
  TH1D* hnum_hijing_1D = (TH1D*)hnum_hijing->ProjectionY("hnum_hijing_1D",3,3,"e");

  TCanvas* c = new TCanvas("c","",800,400);
  c->Divide(2,1);
  c->cd(1);
  hnum_epos->Draw("lego2");
  c->cd(2);
  hnum_hijing->Draw("lego2");

  TCanvas* c1 = new TCanvas("c1","",500,450);
  hnum_epos_1D->SetAxisRange(0,0.15,"Y");
  hnum_epos_1D->SetMarkerColor(2);
  hnum_epos_1D->Draw("PE");
  hnum_hijing_1D->Draw("PESAME");

  TLegend* legend = new TLegend(0.3,0.7,0.5,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(hnum_epos_1D,"EPOS","P");
  legend->AddEntry(hnum_hijing_1D,"Hijing","P");
  legend->Draw("same");

  TFile* fout = new TFile("NonPromptLambda_MC_all.root","recreate");
  hnum_epos->Write("EPOS_ratio");
  hdenom_epos->Write("EPOS_prompt");
  hnum_hijing->Write("HIJING_ratio");
  hdenom_hijing->Write("HIJING_prompt");
  fout->Close();
/*
  TCanvas* c = new TCanvas("c","",600,500);
  hnum_epos->SetMarkerColor(2);
  hnum_epos->Draw("PE");
  hnum_hijing->Draw("PESAME");

  TLegend* legend = new TLegend(0.6,0.7,0.8,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(hnum_epos,"EPOS","P");
  legend->AddEntry(hnum_hijing,"Hijing","P");
  legend->Draw("same");
*/
  SaveCanvas(c1,"HI/V0","Lambda_Xi_fraction");

}
