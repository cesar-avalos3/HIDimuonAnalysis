#include "FullAnalysis.h"

void FullAnalysis() {
  TH1D *histogramsInvariantMassMC[7];
  TH1D *histogramsRapidityMC[7];
  TH1D *histogramsAcoplanarityMC[7];
  TH1D *histogramsInvariantMassDATA[7];
  TH1D *histogramsRapidityDATA[7];
  TH1D *histogramsAcoplanarityDATA[7];
  TH1D *histogramsInvariantMassCorrectedRatio[7];

  TH1D *histogramsInvariantMassMC_GEN_CUTS = new TH1D("GENcuts", "Invariant Mass - Generated with cuts", 26, varBinMass);

  Int_t palette[] = {kGreen, kRed, kBlue, kTeal, kYellow, kViolet, kMagenta};

  createArrayOfHistogramsInvariantMass(histogramsInvariantMassMC, 0);
  createArrayOfHistogramsInvariantMass(histogramsInvariantMassDATA, 1);
  createArrayOfHistogramsRapidity(histogramsRapidityMC, 0);
  createArrayOfHistogramsRapidity(histogramsRapidityDATA, 1);
  createArrayOfHistogramsAcoplanarity(histogramsAcoplanarityDATA, 1);
  createArrayOfHistogramsAcoplanarity(histogramsAcoplanarityMC, 0);

  TFile *inFileMC = new TFile("../Tree/OniaTree_MC_ppRec_tracks.root");
  TFile *inFileDATA = new TFile("../Tree/OniaTree_part_NoCuts_allTrig.root");

  TTree *myTreeMC = (TTree *)inFileMC->Get("hionia/myTree");
  TTree *myTreeDATA = (TTree *)inFileDATA->Get("hionia/myTree");

  // Create the branches variables

  Int_t Ntracks_MC;
  Int_t Gen_QQ_size_MC;
  TClonesArray *Gen_QQ_4mom_MC;
  TClonesArray *Gen_QQ_mupl_4mom_MC;
  TClonesArray *Gen_QQ_mumi_4mom_MC;
  TBranch *b_Ntracks_MC;
  TBranch *b_Gen_QQ_size_MC;      //!
  TBranch *b_Gen_QQ_4mom_MC;      //!
  TBranch *b_Gen_QQ_mupl_4mom_MC; //!
  TBranch *b_Gen_QQ_mumi_4mom_MC; //!
  Int_t Reco_QQ_sign_MC;
  Int_t Reco_QQ_size_MC;
  TClonesArray *Reco_QQ_4mom_MC;
  TClonesArray *Reco_QQ_mupl_4mom_MC;
  TClonesArray *Reco_QQ_mumi_4mom_MC;
  TBranch *b_Reco_QQ_size_MC;      //!
  TBranch *b_Reco_QQ_4mom_MC;      //!
  TBranch *b_Reco_QQ_mupl_4mom_MC; //!
  TBranch *b_Reco_QQ_mumi_4mom_MC; //!
  TBranch *b_Reco_QQ_sign_MC;

  Int_t Ntracks_DATA;
  Int_t Gen_QQ_size_DATA;
  TClonesArray *Gen_QQ_4mom_DATA;
  TClonesArray *Gen_QQ_mupl_4mom_DATA;
  TClonesArray *Gen_QQ_mumi_4mom_DATA;
  TBranch *b_Ntracks_DATA;
  TBranch *b_Gen_QQ_size_DATA;      //!
  TBranch *b_Gen_QQ_4mom_DATA;      //!
  TBranch *b_Gen_QQ_mupl_4mom_DATA; //!
  TBranch *b_Gen_QQ_mumi_4mom_DATA; //!
  Int_t Reco_QQ_sign_DATA;
  Int_t Reco_QQ_size_DATA;
  TClonesArray *Reco_QQ_4mom_DATA;
  TClonesArray *Reco_QQ_mupl_4mom_DATA;
  TClonesArray *Reco_QQ_mumi_4mom_DATA;
  TBranch *b_Reco_QQ_size_DATA;      //!
  TBranch *b_Reco_QQ_4mom_DATA;      //!
  TBranch *b_Reco_QQ_mupl_4mom_DATA; //!
  TBranch *b_Reco_QQ_mumi_4mom_DATA; //!
  TBranch *b_Reco_QQ_sign_DATA;

  // Just for caution, set them to 0
  // ---------------- MC ----------------
  Gen_QQ_4mom_MC = 0;
  Gen_QQ_mupl_4mom_MC = 0;
  Gen_QQ_mumi_4mom_MC = 0;
  Reco_QQ_4mom_MC = 0;
  Reco_QQ_mupl_4mom_MC = 0;
  Reco_QQ_mumi_4mom_MC = 0;
  Reco_QQ_sign_MC = 0;

  // --------------- DATA ----------------
  Gen_QQ_4mom_DATA = 0;
  Gen_QQ_mupl_4mom_DATA = 0;
  Gen_QQ_mumi_4mom_DATA = 0;
  Reco_QQ_4mom_DATA = 0;
  Reco_QQ_mupl_4mom_DATA = 0;
  Reco_QQ_mumi_4mom_DATA = 0;
  Reco_QQ_sign_DATA = 0;

  //Set branches addresses of MC
  myTreeMC->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size_MC, &b_Gen_QQ_size_MC);
  myTreeMC->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom_MC, &b_Gen_QQ_4mom_MC);
  myTreeMC->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom_MC, &b_Gen_QQ_mupl_4mom_MC);
  myTreeMC->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom_MC, &b_Gen_QQ_mumi_4mom_MC);
  myTreeMC->SetBranchAddress("Reco_trk_size", &Ntracks_MC, &b_Ntracks_MC);
  myTreeMC->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size_MC, &b_Reco_QQ_size_MC);
  myTreeMC->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom_MC, &b_Reco_QQ_4mom_MC);
  myTreeMC->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom_MC, &b_Reco_QQ_mupl_4mom_MC);
  myTreeMC->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom_MC, &b_Reco_QQ_mumi_4mom_MC);
  myTreeMC->SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign_MC, &b_Reco_QQ_sign_MC);

  //Set branches addresses of DATA
  myTreeDATA->SetBranchAddress("Ntracks", &Ntracks_DATA, &b_Ntracks_DATA);
  myTreeDATA->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size_DATA, &b_Reco_QQ_size_DATA);
  myTreeDATA->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom_DATA, &b_Reco_QQ_4mom_DATA);
  myTreeDATA->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom_DATA, &b_Reco_QQ_mupl_4mom_DATA);
  myTreeDATA->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom_DATA, &b_Reco_QQ_mumi_4mom_DATA);
  myTreeDATA->SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign_DATA, &b_Reco_QQ_sign_DATA);

  // ----------  Loop through the MonteCarlo Events -------------
  std::cout << "Looping through the MC \n";
  Int_t numberOfEventsMC = myTreeMC->GetEntries();
  //Generated events first
  for (Int_t eventIterator = 0; eventIterator < numberOfEventsMC; eventIterator++) {
    myTreeMC->GetEvent(eventIterator);
    if (Gen_QQ_size_MC == 0)
      continue;
    //Create Lorentz Vectors
    for (Int_t i = 0; i < Gen_QQ_size_MC; i++) {
      TLorentzVector *mupl_GEN = (TLorentzVector *)Gen_QQ_mupl_4mom_MC->At(i);
      TLorentzVector *mumi_GEN = (TLorentzVector *)Gen_QQ_mumi_4mom_MC->At(i);
      TLorentzVector *dimu_GEN = (TLorentzVector *)Gen_QQ_4mom_MC->At(i);
      for (Int_t u = 0; u < 1; u++) {
        if (Cut(mumi_GEN, mupl_GEN, dimu_GEN, 0, Ntracks_MC, u)) {
          //Fill histogramsInvariantMass invariantMass of dimuon
          histogramsInvariantMassMC[u]->Fill(dimu_GEN->M());
          histogramsRapidityMC[u]->Fill(dimu_GEN->Rapidity());
          histogramsAcoplanarityMC[u]->Fill(1 - (TMath::Abs(mupl_GEN->Phi() - mumi_GEN->Phi())) / TMath::Pi());
        }

        // Now apply the final cut on the Generated Data - For Acceptance
        if (Cut(mumi_GEN, mupl_GEN, dimu_GEN, 0, Ntracks_MC, 6)) {
          histogramsInvariantMassMC_GEN_CUTS->Fill(dimu_GEN->M());
        }
      }
    }

    // Reconstructed events next
    for (Int_t i = 0; i < Reco_QQ_size_MC; i++) {
      TLorentzVector *mupl_RECO = (TLorentzVector *)Reco_QQ_mupl_4mom_MC->At(i);
      TLorentzVector *mumi_RECO = (TLorentzVector *)Reco_QQ_mumi_4mom_MC->At(i);
      TLorentzVector *dimu_RECO = (TLorentzVector *)Reco_QQ_4mom_MC->At(i);
      TLorentzVector *vectors[] = {mupl_RECO, mumi_RECO, dimu_RECO};

      for (Int_t u = 1; u < 7; u++) {
        if (Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign_MC, Ntracks_MC, u)) {
          //Fill histogramsInvariantMass invariantMass of dimuon
          histogramsInvariantMassMC[u]->Fill(dimu_RECO->M());
          histogramsRapidityMC[u]->Fill(dimu_RECO->Rapidity());
          histogramsAcoplanarityMC[u]->Fill(1 - (TMath::Abs(mupl_RECO->Phi() - mumi_RECO->Phi())) / TMath::Pi());
        }
      }
    }
  }

  // ----------  Loop through the Data Events -------------
  std::cout << "Looping through the DATA \n";
  Int_t numberOfEventsDATA = myTreeDATA->GetEntries();

  //Reconstructed events only
  for (Int_t eventIterator = 0; eventIterator < numberOfEventsDATA; eventIterator++) {
    if (!goodEventSelector(eventIterator))
      eventIterator += 2;
    myTreeDATA->GetEvent(eventIterator);
    //std::cout << "Event number: " << eventIterator << "\n";
    for (Int_t i = 0; i < Reco_QQ_size_DATA; i++) {
      TLorentzVector *mupl_RECO = (TLorentzVector *)Reco_QQ_mupl_4mom_DATA->At(i);
      TLorentzVector *mumi_RECO = (TLorentzVector *)Reco_QQ_mumi_4mom_DATA->At(i);
      TLorentzVector *dimu_RECO = (TLorentzVector *)Reco_QQ_4mom_DATA->At(i);
      TLorentzVector *vectors[] = {mupl_RECO, mumi_RECO, dimu_RECO};

      for (Int_t u = 0; u < 7; u++) {
        if (Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign_DATA, Ntracks_DATA, 1 + u)) {
          //Fill histogramsInvariantMass invariantMass of dimuon
          histogramsInvariantMassDATA[u]->Fill(dimu_RECO->M());
          histogramsRapidityDATA[u]->Fill(dimu_RECO->Rapidity());
          histogramsAcoplanarityDATA[u]->Fill(1 - (TMath::Abs(mupl_RECO->Phi() - mumi_RECO->Phi())) / TMath::Pi());
        }
      }
    }
  }

  // ------------ Save histograms to a new file --------------------------
  TFile *out = new TFile("outputAnalysis.root", "RECREATE");

  // Set up the canvas - Hide the stat box
  gStyle->SetOptStat(kFALSE);

  // -------------------- Calculate Efficiency and Acceptance -----------------------

  Double_t numberOfGeneEventsMC = histogramsInvariantMassMC[0]->Integral();
  Double_t numberOfRecoEventsMC = histogramsInvariantMassMC[6]->Integral();
  Double_t numberOfRecoEventsDATA = histogramsInvariantMassDATA[5]->Integral();

  // ---------------------- Acceptance and Efficiency Invariant Mass  -----------------------------

  TH1D *invMassAccEffNum = (TH1D *)histogramsInvariantMassMC[6]->Clone("invMassAccEffNum");
  TH1D *invMassAccEffDen = (TH1D *)histogramsInvariantMassMC[0]->Clone("invMassAccEffDen");

  invMassAccEffNum->Sumw2();
  invMassAccEffNum->SetStats(0);
  invMassAccEffNum->Divide(invMassAccEffDen);
  invMassAccEffNum->SetTitle("Efficiency - Invariant Mass (RECO / GEN)");
  TCanvas *efficiencyCanvas = new TCanvas("Efficiency", "Efficiency - RECO / GEN ", canvasXResolution, canvasYResolution);
  invMassAccEffNum->Draw("ep");
  efficiencyCanvas->SaveAs("Efficiency - Invariant Mass.png");

  // ----------------------  Acceptance Invariant Mass  -----------------------------

  TH1D *invMassAccNum = (TH1D *)histogramsInvariantMassMC_GEN_CUTS->Clone("invMassAccNum");
  TH1D *invMassAccDen = (TH1D *)histogramsInvariantMassMC[0]->Clone("invMassAccDen");

  invMassAccNum->Sumw2();
  invMassAccNum->SetStats(0);
  invMassAccNum->Divide(invMassAccDen);
  invMassAccNum->SetTitle("Acceptance - Invariant Mass (GEN_{cuts} / GEN)");
  TCanvas *acceptanceCanvas = new TCanvas("Acceptance", "Acceptance - RECO / GEN ", canvasXResolution, canvasYResolution);
  invMassAccNum->Draw("ep");
  acceptanceCanvas->SaveAs("Acceptance - InvariantMass.png");

  // ----------------------- CORRECTED GENERATED DATA WITH AE ---------------------------
  TCanvas *correctedInvMassCanvas = new TCanvas("correctedInvMassCanvasDATA", "Invariant Mass - (DATA / AE ) / GEN ", canvasXResolution, canvasYResolution);
  TLegend *legendCorrectedInvMass = new TLegend(TLegendSize[0], TLegendSize[1], TLegendSize[2], TLegendSize[3]);

  for (Int_t i = 0; i < 7; i++) {
    // (Reco / ae)
    TString invMassRecoTitle1 = TString("invMassCorrectedRecoNum");
    invMassRecoTitle1 += i;
    TString invMassRecoTitle2 = TString("invMassCorrectedRecoDen");
    invMassRecoTitle2 += i;
    TString invMassRecoTitle3 = TString("invMassCorrectedRecoDenDen");
    invMassRecoTitle3 += i;
    TH1D *invMassCorrectedRecoNum = (TH1D *)histogramsInvariantMassDATA[i]->Clone(invMassRecoTitle1);
    TH1D *invMassCorrectedRecoDen = (TH1D *)invMassAccEffNum->Clone(invMassRecoTitle2);
    TH1D *invMassCorrectedRecoDenDen = (TH1D *)histogramsInvariantMassMC[0]->Clone(invMassRecoTitle3);
    if (i == 0)
      invMassCorrectedRecoNum->SetTitle("Invariant Mass - (DATA / AE ) / GEN");
    invMassCorrectedRecoNum->Sumw2();
    invMassCorrectedRecoNum->SetStats(0);
    invMassCorrectedRecoNum->Divide(invMassCorrectedRecoDen);
    invMassCorrectedRecoNum->SetStats(0);
    invMassCorrectedRecoNum->Sumw2();
    invMassCorrectedRecoNum->Divide(invMassCorrectedRecoDenDen);
    TString mode = "e2&&SAME";
    if (i == 0)
      mode = "e2";
    invMassCorrectedRecoNum->SetFillColor(palette[i]);
    invMassCorrectedRecoNum->Draw(mode);
    legendCorrectedInvMass->AddEntry(invMassCorrectedRecoNum, histogramsInvariantMassDATA[i]->GetTitle(), "f");
  }
  legendCorrectedInvMass->Draw("SAME");

  // ----------------------- CORRECTED GENERATED MC WITH AE ---------------------------
  TCanvas *correctedInvMassCanvasMC = new TCanvas("correctedInvMassCanvasMC", "Invariant Mass - (MC / AE ) / GEN ", canvasXResolution, canvasYResolution);
  TLegend *legendCorrectedInvMassMC = new TLegend(TLegendSize[0], TLegendSize[1], TLegendSize[2], TLegendSize[3]);

  TString invMassRecoTitle1 = TString("invMassCorrectedRecoNumMC");
  TString invMassRecoTitle2 = TString("invMassCorrectedRecoDenMC");
  TString invMassRecoTitle3 = TString("invMassCorrectedRecoDenDenMC");
  // Montecarlo Reconstructed is hist[1] - Generated is hist[0]
  TH1D *invMassCorrectedRecoNumMC = (TH1D *)histogramsInvariantMassMC[6]->Clone(invMassRecoTitle1);
  TH1D *invMassCorrectedRecoDenMC = (TH1D *)invMassAccEffNum->Clone(invMassRecoTitle2);
  TH1D *invMassCorrectedRecoDenDenMC = (TH1D *)histogramsInvariantMassMC[0]->Clone(invMassRecoTitle3);
  invMassCorrectedRecoNumMC->SetTitle("Invariant Mass - (RECO_{no cuts} / AE ) / GEN");
  invMassCorrectedRecoNumMC->Sumw2();
  invMassCorrectedRecoNumMC->SetStats(0);
  invMassCorrectedRecoNumMC->Divide(invMassCorrectedRecoDenMC);
  invMassCorrectedRecoNumMC->Divide(invMassCorrectedRecoDenDenMC);
  invMassCorrectedRecoNumMC->SetFillColor(palette[0]);
  invMassCorrectedRecoNumMC->Draw("e2");
  legendCorrectedInvMassMC->AddEntry(invMassCorrectedRecoNumMC, histogramsInvariantMassMC[1]->GetTitle(), "f");
  legendCorrectedInvMassMC->Draw("SAME");

  //	------------------------ CORRECT DATA --------------------------------------------
  TCanvas *correctedInvMassCanvasDATADATA = new TCanvas("correctedInvMassCanvasDATA2", "Invariant Mass - Corrected Data vs Generated Events ", canvasXResolution, canvasYResolution);
  TLegend *legendCorrectedInvMassDATADATA = new TLegend(TLegendSize[0], TLegendSize[1], TLegendSize[2], TLegendSize[3]);

  TH1D *invMassCorrecDataNum = (TH1D *)histogramsInvariantMassDATA[5]->Clone("invMassCorrecDataNum");
  TH1D *invMassCorrecDataNum2 = (TH1D *)invMassAccEffNum->Clone("invMassCorrecDataNum2");

  // We are going to normalize the histograms by the number of generated events
  TH1D *invMassGeneratedMC = (TH1D *)histogramsInvariantMassMC[0]->Clone("invMassGeneratedMC");
  invMassCorrecDataNum->Divide(invMassCorrecDataNum2);
  invMassCorrecDataNum->SetTitle("Invariant Mass - AE * N_{DATA}");
  invMassCorrecDataNum->SetMarkerStyle(20);
  invMassGeneratedMC->Scale(1 / numberOfGeneEventsMC);
  invMassGeneratedMC->Draw("");
  invMassCorrecDataNum->Scale(1 / numberOfGeneEventsMC);
  invMassCorrecDataNum->Draw("ep&&SAME");
  TH1D *test = histogramsDeltaBinByBin(invMassCorrecDataNum, varBinMass, 26);
  test->Draw("");
  test->Write();

  // --------------------- DRAW THE SUCKERS ------------------------------

  //(TH1D** arrayHistogram, Int_t arraySize, TString canvasTitle, TString mainHistogramTitle, Int_t* colorsArray,Int_t logY, Int_t logX)
  drawAllHistogramsBasic(histogramsInvariantMassMC, 7, "invariantMassMC", "Invariant Mass - MC", palette, 1, 1);
  drawAllHistogramsBasic(histogramsInvariantMassDATA, 7, "invariantMassData", "Invariant Mass - DATA", palette, 1, 1);
  drawAllHistogramsBasic(histogramsRapidityMC, 7, "rapidityMC", "Rapidity - MC", palette, 1, 0);
  drawAllHistogramsBasic(histogramsRapidityDATA, 7, "rapidityDATA", "Rapidity - DATA", palette, 1, 0);
  drawAllHistogramsBasic(histogramsAcoplanarityMC, 7, "acoMC", "Acoplanarity - MC", palette, 1, 0);
  drawAllHistogramsBasic(histogramsAcoplanarityDATA, 7, "acoDATA", "Acoplanarity - DATA", palette, 1, 0);

  //(TH1D *histMassMC, TH1D *histMassDATA, TString canvasTitle, TString mainHistogramTitle, Int_t logY, Int_t logX, Int_t normFactorMC, Int_t normFactorDATA)
  drawHistogramsMCvDATA(histogramsInvariantMassMC[6], histogramsInvariantMassDATA[5], "invariantMassMCvDATA", "Invariant Mass - MC vs DATA", 1, 1, numberOfRecoEventsMC, numberOfRecoEventsDATA);
  drawHistogramsMCvDATA(histogramsRapidityMC[6], histogramsRapidityDATA[5], "rapidityMCvDATA", "Rapidity - MC vs DATA", 1, 0, 1, 1);
  drawHistogramsMCvDATA(histogramsAcoplanarityMC[6], histogramsAcoplanarityDATA[5], "acoplanarityMCvDATA", "Acoplanarity - MC vs DATA", 1, 0, 1, 1);

  // Scale the corrected invariantMass histogram by the count of Generated Events
}
