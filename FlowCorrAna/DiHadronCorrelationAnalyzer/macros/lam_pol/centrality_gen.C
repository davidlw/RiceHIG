void centrality_gen()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/lampolgen_pol100_all.root");
  TH2D* hmultvsb = (TH2D*)f->Get("corr_ana/multvsb");
  TH1D* hmult = (TH1D*)hmultvsb->ProjectionX("hmult",-1,-1,"e");
  TH1D* hb = (TH1D*)hmultvsb->ProjectionY("hb",-1,-1,"e");

  double integral_total = hmultvsb->Integral();
  
  TCanvas* c = new TCanvas("c","c",800,400);
  c->Divide(2,1);
  c->cd(1);
  c->GetPad(1)->SetLogy();
  hmult->SetAxisRange(0,7000,"X");
  hmult->Draw();
  c->cd(2);
  hb->SetAxisRange(0,25,"X");
  hb->Draw();


  TH1D* hcent_b = new TH1D("cent_gen_b",";cbin",20,0,20);
  TH1D* hcent_mult = new TH1D("cent_gen_mult",";cbin",20,0,20);

  double cent_binwidth = 1./20;

  double fraction = 0;
  int m = 0;
  for(int i=1;i<=hb->GetNbinsX();i++)
  {
    fraction += hb->GetBinContent(i);
    if((fraction*1.0/integral_total)>=m*cent_binwidth) 
    {
cout<<fraction*1.0/integral_total<<" "<<m<<" "<<m*cent_binwidth<<" "<<hb->GetBinCenter(i)<<endl;
      hcent_b->SetBinContent(m,hb->GetBinCenter(i));
      m++;
    }
    if(m>20) break;
  }

  fraction=0;
  m=0;
  for(int i=1;i<=hmult->GetNbinsX();i++)
  {
    fraction += hmult->GetBinContent(i);
    if((fraction*1.0/integral_total)>=m*cent_binwidth)
    {
      hcent_mult->SetBinContent(m,hmult->GetBinCenter(i));
      m++;
    }
    if(m>20) break;
  }

  TCanvas* c1 = new TCanvas("c1","c1",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  hcent_mult->Draw();
  c1->cd(2);
  hcent_b->Draw();

  TFile* fout_cent = new TFile("centrality_AMPT_gen.root","recreate");
  hcent_mult->Write();
  hcent_b->Write();
  fout_cent->Close();

}
