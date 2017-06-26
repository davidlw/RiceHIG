//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldExample.cxx 279 2011-02-11 18:23:44Z T.J.Adye $
//
// Description:
//      Simple example usage of the RooUnfold package using toy MC.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Fergus Wilson <fwilson@slac.stanford.edu>
//
//==============================================================================

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"
#endif

//==============================================================================
// Global definitions
//==============================================================================

const Double_t cutdummy= -99999.0;

//==============================================================================
// Example Unfolding
//==============================================================================

void RooUnfoldExample()
{
#ifdef __CINT__
  gSystem->Load("libRooUnfold");
#endif

  cout << "==================================== TRAIN ====================================" << endl;
  RooUnfoldResponse response (40, -10.0, 10.0);


  TFile* fInput = new TFile("");
  TH1D* hMeas = (TH1D*)fInput->Get("");

  cout << "==================================== UNFOLD ===================================" << endl;
  RooUnfoldBayes   unfold (&response, hMeas, 4);    // OR
//RooUnfoldSvd     unfold (&response, hMeas, 20);   // OR
//RooUnfoldTUnfold unfold (&response, hMeas);

  TH1D* hReco= (TH1D*) unfold.Hreco();

  unfold.PrintTable (cout, hTrue);
  hReco->Draw();
  hMeas->Draw("SAME");
  hTrue->SetLineColor(8);
  hTrue->Draw("SAME");
}

#ifndef __CINT__
int main () { RooUnfoldExample(); return 0; }  // Main program when run stand-alone
#endif
