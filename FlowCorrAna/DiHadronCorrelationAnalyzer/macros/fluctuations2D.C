void fluctuations2D()
{
   gStyle->SetOptStat(0);

   TF2* func = new TF2("func","([0]-1)*([0]-1)*x*y*(2-x*x-y*y)**(0.5*[0]-1.5)",0,1,0,1);
   func->SetParameter(0,200);

   TH2D* h = new TH2D("h",";#epsilon_{n};#epsilon_{m}",20,0,1,20,0,1);
   for(int i=0;i<1000000;i++)
   {
     double xx=0;
     double yy=0;
     func->GetRandom2(xx,yy);
     h->Fill(xx,yy);
   }

   TCanvas* c = new TCanvas("c","c",600,500);
//   func->Draw("surf1");
   h->Draw("surf1");

cout<<h->GetCorrelationFactor()<<endl;
}
