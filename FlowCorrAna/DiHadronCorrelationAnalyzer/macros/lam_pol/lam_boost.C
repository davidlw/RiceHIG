void lam_boost()
{
  TLorentzVector pion;
  TLorentzVector proton;

  TGraph* gr_low = new TGraph(100);
  TGraph* gr_high = new TGraph(100);

  for(int i=0;i<100;i++)
  {
    pion.SetXYZM(-1.009254e-01,0,0,0.140);
    proton.SetXYZM(1.009254e-01,0,0,0.938);
    TVector3 vect(sqrt(i/1.116/(i/1.116+1)),0,0);
    pion.Boost(vect); 
    proton.Boost(vect);
    double ratio = pion.X()/proton.X();
    gr_low->SetPoint(i,i,ratio);
  }

  for(int i=0;i<100;i++)
  {
    pion.SetXYZM(1.009254e-01,0,0,0.140);
    proton.SetXYZM(-1.009254e-01,0,0,0.938);
    TVector3 vect(sqrt(i/1.116/(i/1.116+1)),0,0);
    pion.Boost(vect);
    proton.Boost(vect);
    double ratio = pion.X()/proton.X();
    gr_high->SetPoint(i,i,ratio);
  }

  TH2D* htmp = new TH2D("tmp",";p_{T};ratio",1000,0,100,100,0,1);
  TCanvas* c = new TCanvas("c","c",500,500);
  htmp->Draw();
  gr_high->Draw("CSAME");
  gr_low->Draw("CSAME");
}
