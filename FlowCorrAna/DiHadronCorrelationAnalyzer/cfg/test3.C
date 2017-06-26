void test3()
{
  TFile* f = new TFile("lampolgen_acc2.root");
  TFile* f1 = new TFile("lampolgen.root");

  TH2D* hpt_acc = (TH2D*)f->Get("lampolgen/etapt_lam_trg0");
  TH2D* hpt = (TH2D*)f1->Get("lampolgen/etapt_lam_trg0");

  hpt_acc->Rebin2D(2,1);
  hpt->Rebin2D(2,1);

//  hpt_acc->SetMarkerStyle(20);
//  hpt->SetMarkerColor(2);

//  TCanvas* c = new TCanvas("c","c",550,500);
//  hpt_acc->Draw("PE");
//  hpt->Draw("histESAME");

  TH2D* hratio = (TH2D*)hpt_acc->Clone("ratio");
  hratio->Divide(hpt);

  TCanvas* c1 = new TCanvas("c1","c1",550,500);
  hratio->Draw("lego2");
}
