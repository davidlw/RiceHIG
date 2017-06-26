#include "/net/hisrv0001/home/davidlw/useful_macros/GetGraphFromFile.C"

void vnvsn()
{
  gStyle->SetOptStat(0);

  TGraphErrors* gr[20];

  gr[0] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt1.txt",1,20,1,1);
  gr[1] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt2.txt",1,20,1,1);
  gr[2] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt3.txt",1,20,1,1);
  gr[3] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt4.txt",1,20,1,1);
  gr[4] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt5.txt",1,20,1,1);
  gr[5] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt6.txt",1,20,1,1);
  gr[6] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt7.txt",1,20,1,1);
  gr[7] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt8.txt",1,20,1,1);
  gr[8] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt9.txt",1,20,1,1);
  gr[9] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt10.txt",1,20,1,1);
  gr[10] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt11.txt",1,20,1,1);
  gr[11] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt12.txt",1,20,1,1);
  gr[12] = GetGraphWithSymmYErrorsFromFile("Fig2left_pt13.txt",1,20,1,1);

  TH2D* htmp = new TH2D("tmp",";n;v_{n}",7,1,8,100,0,0.085);

  TCanvas* c = new TCanvas("c","c",1200,900);
  c->Divide(4,3);
  for(int i=0;i<12;i++)
  {
    c->cd(i+1);
//    c->GetPad(i+1)->SetLogy();
    htmp->Draw();
    gr[i]->Draw("PESAME");
  }
}
