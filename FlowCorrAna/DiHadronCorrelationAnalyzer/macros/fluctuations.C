void fluctuations()
{
   gStyle->SetOptStat(0);

   TF1* func = new TF1("func","([0]-1)*x*(1-x*x)**(0.5*[0]-1.5)",0,1);
   func->SetParameter(0,18);
   func->SetLineColor(1);
   func->SetLineWidth(3);

   TF1* func1 = new TF1("func1","([0]-1)*x*(1-x*x)**(0.5*[0]-1.5)",0,1);
   func1->SetParameter(0,4);
   func1->SetLineWidth(3);

   TH2D* htmp = new TH2D("",";#epsilon_{n};P(#epsilon_{n})",100,0,1,100,0,3);

   TCanvas* c = new TCanvas("c","c",600,500);
   htmp->Draw("");
   htmp->GetXaxis()->CenterTitle();
   htmp->GetYaxis()->CenterTitle();
   htmp->GetXaxis()->SetTitleOffset(htmp->GetXaxis()->GetTitleOffset()*1.0);
   htmp->GetYaxis()->SetTitleOffset(htmp->GetYaxis()->GetTitleOffset()*1.0);
   htmp->GetXaxis()->SetTitleSize(htmp->GetXaxis()->GetTitleSize()*1.4);
   htmp->GetYaxis()->SetTitleSize(htmp->GetYaxis()->GetTitleSize()*1.4);
   func->Draw("LSAME");
   func1->Draw("LSAME");

   c->Print("fluctuation.pdf");
   c->Print("fluctuation.gif");
}
