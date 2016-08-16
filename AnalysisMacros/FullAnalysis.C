#include "FullAnalysis.h"

void FullAnalysis()
{
	TH1D *histogramsInvariantMassMC[7];
	TH1D *histogramsRapidityMC[7];
	TH1D *histogramsAcoplanarityMC[7];

	TH1D *histogramsInvariantMassDATA[7];
	TH1D *histogramsRapidityDATA[7];
	TH1D *histogramsAcoplanarityDATA[7];

	TH1D *histogramsInvariantMassMC_GEN_CUTS = new TH1D("GENcuts", "Invariant Mass - Generated with cuts", 26,varBinMass);

	createArrayOfHistogramsInvariantMass(histogramsInvariantMassMC,0);
	createArrayOfHistogramsInvariantMass(histogramsInvariantMassDATA,1);
	createArrayOfHistogramsRapidity(histogramsRapidityMC, 0);
	createArrayOfHistogramsRapidity(histogramsRapidityDATA, 1);

	TFile* inFileMC   = new TFile("../Tree/OniaTree_MC_ppRec_tracks.root");
	TFile* inFileDATA = new TFile("../Tree/OniaTree_part_NoCuts_allTrig.root");

	TTree* myTreeMC = (TTree*) inFileMC->Get("hionia/myTree");
	TTree* myTreeDATA = (TTree*) inFileDATA->Get("hionia/myTree");

	// Create the branches variables

	Int_t            Ntracks_MC;
	Int_t            Gen_QQ_size_MC;
	TClonesArray    *Gen_QQ_4mom_MC;
	TClonesArray    *Gen_QQ_mupl_4mom_MC;
	TClonesArray    *Gen_QQ_mumi_4mom_MC;
	TBranch         *b_Ntracks_MC;
	TBranch         *b_Gen_QQ_size_MC;   //!
	TBranch         *b_Gen_QQ_4mom_MC;   //!
	TBranch         *b_Gen_QQ_mupl_4mom_MC;   //!
	TBranch         *b_Gen_QQ_mumi_4mom_MC;   //!
	Int_t		     Reco_QQ_sign_MC;
	Int_t            Reco_QQ_size_MC;
	TClonesArray    *Reco_QQ_4mom_MC;
	TClonesArray    *Reco_QQ_mupl_4mom_MC;
	TClonesArray    *Reco_QQ_mumi_4mom_MC;
	TBranch         *b_Reco_QQ_size_MC;   //!
	TBranch         *b_Reco_QQ_4mom_MC;   //!
	TBranch         *b_Reco_QQ_mupl_4mom_MC;   //!
	TBranch         *b_Reco_QQ_mumi_4mom_MC;   //!
	TBranch	        *b_Reco_QQ_sign_MC;

	Int_t            Ntracks_DATA;
	Int_t            Gen_QQ_size_DATA;
	TClonesArray    *Gen_QQ_4mom_DATA;
	TClonesArray    *Gen_QQ_mupl_4mom_DATA;
	TClonesArray    *Gen_QQ_mumi_4mom_DATA;
	TBranch         *b_Ntracks_DATA;
	TBranch         *b_Gen_QQ_size_DATA;   //!
	TBranch         *b_Gen_QQ_4mom_DATA;   //!
	TBranch         *b_Gen_QQ_mupl_4mom_DATA;   //!
	TBranch         *b_Gen_QQ_mumi_4mom_DATA;   //!
	Int_t						 Reco_QQ_sign_DATA;
	Int_t            Reco_QQ_size_DATA;
	TClonesArray    *Reco_QQ_4mom_DATA;
	TClonesArray    *Reco_QQ_mupl_4mom_DATA;
	TClonesArray    *Reco_QQ_mumi_4mom_DATA;
	TBranch         *b_Reco_QQ_size_DATA;   //!
	TBranch         *b_Reco_QQ_4mom_DATA;   //!
	TBranch         *b_Reco_QQ_mupl_4mom_DATA;   //!
	TBranch         *b_Reco_QQ_mumi_4mom_DATA;   //!
	TBranch	        *b_Reco_QQ_sign_DATA;

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
	for (Int_t eventIterator = 0; eventIterator < numberOfEventsMC; eventIterator++)
	{
		myTreeMC->GetEvent(eventIterator);
    if (Gen_QQ_size_MC == 0) continue;
  	//Create Lorentz Vectors
    for(Int_t i = 0; i < Gen_QQ_size_MC; i++)
    	{
				TLorentzVector *mupl_GEN = (TLorentzVector*) Gen_QQ_mupl_4mom_MC->At(i);
				TLorentzVector *mumi_GEN = (TLorentzVector*) Gen_QQ_mumi_4mom_MC->At(i);
				TLorentzVector *dimu_GEN = (TLorentzVector*) Gen_QQ_4mom_MC->At(i);
				for(Int_t u = 0; u < 1; u++)
					{
						if(Cut(mumi_GEN, mupl_GEN, dimu_GEN, 0, Ntracks_MC, u))
						{
      			//Fill histogramsInvariantMass invariantMass of dimuon
							histogramsInvariantMassMC[u]->Fill(dimu_GEN->M());
							histogramsRapidityMC[u]->Fill(dimu_GEN->Rapidity());
							//histogramsAcoplanarity[u]->Fill(1 - (TMath::Abs(mupl_GEN->Phi() - mumi_GEN->Phi() )) / TMath::Pi() );
      			}

						// Now apply the final cut on the Generated Data - For Acceptance
						if(Cut(mumi_GEN, mupl_GEN, dimu_GEN, 0, Ntracks_MC, 6))
						{
							histogramsInvariantMassMC_GEN_CUTS->Fill(dimu_GEN->M());
						}
      		}
      }

// Reconstructed events next
	for(Int_t i = 0; i < Reco_QQ_size_MC; i++)
      {
        TLorentzVector *mupl_RECO = (TLorentzVector*) Reco_QQ_mupl_4mom_MC->At(i);
        TLorentzVector *mumi_RECO = (TLorentzVector*) Reco_QQ_mumi_4mom_MC->At(i);
        TLorentzVector *dimu_RECO = (TLorentzVector*) Reco_QQ_4mom_MC->At(i);
        TLorentzVector *vectors[] = {mupl_RECO, mumi_RECO, dimu_RECO};

        for(Int_t u = 1; u < 7; u++)
          {
      			if(Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign_MC,Ntracks_MC, u))
            {
              //Fill histogramsInvariantMass invariantMass of dimuon
              histogramsInvariantMassMC[u]->Fill(dimu_RECO->M());
              histogramsRapidityMC[u]->Fill(dimu_RECO->Rapidity());
              //histogramsAcoplanarity[u]->Fill(1 - (TMath::Abs(mupl_RECO->Phi() - mumi_RECO->Phi() )) / TMath::Pi() );
            }
          }
      }
  }

	// ----------  Loop through the Data Events -------------
	std::cout << "Looping through the DATA \n";
  Int_t numberOfEventsDATA = myTreeDATA->GetEntries();

  //Reconstructed events only
  for (Int_t eventIterator = 0; eventIterator < numberOfEventsDATA; eventIterator++)
  {
  		if(!goodEventSelector(eventIterator)) eventIterator += 2;
  		myTreeDATA->GetEvent(eventIterator);
  	//std::cout << "Event number: " << eventIterator << "\n";
	for(Int_t i = 0; i < Reco_QQ_size_DATA; i++)
      {
        TLorentzVector *mupl_RECO = (TLorentzVector*) Reco_QQ_mupl_4mom_DATA->At(i);
        TLorentzVector *mumi_RECO = (TLorentzVector*) Reco_QQ_mumi_4mom_DATA->At(i);
        TLorentzVector *dimu_RECO = (TLorentzVector*) Reco_QQ_4mom_DATA->At(i);
        TLorentzVector *vectors[] = {mupl_RECO, mumi_RECO, dimu_RECO};

        for(Int_t u = 0; u < 7; u++)
          {
      			if(Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign_DATA,Ntracks_DATA, 1 + u))
            {
              //Fill histogramsInvariantMass invariantMass of dimuon
              histogramsInvariantMassDATA[u]->Fill(dimu_RECO->M());
              histogramsRapidityDATA[u]->Fill(dimu_RECO->Rapidity());
              //histogramsAcoplanarityDATA[u]->Fill(1 - (TMath::Abs(mupl_RECO->Phi() - mumi_RECO->Phi() )) / TMath::Pi() );
            }
          }
      }
  }

	// Set up the canvas - Hide the stat box
	gStyle->SetOptStat(kFALSE);

 // -------------------- Calculate Efficiency and Acceptance -----------------------

 // ----------------------  Efficiency Invariant Mass  -----------------------------

  TH1D *invMassEffNum = (TH1D*) histogramsInvariantMassMC[6]->Clone("invMassEffNum");
  TH1D *invMassEffDen = (TH1D*) histogramsInvariantMassMC[0]->Clone("invMassEffDen");

  invMassEffNum->Sumw2();
  invMassEffNum->SetStats(0);
  invMassEffNum->Divide(invMassEffDen);
	invMassEffNum->SetTitle("Efficiency - Invariant Mass (RECO / GEN)");
  TCanvas *efficiencyCanvas = new TCanvas("Efficiency", "Efficiency - RECO / GEN ", canvasXResolution,canvasYResolution);
  invMassEffNum->Draw("ep");
	efficiencyCanvas->SaveAs("Efficiency - Invariant Mass.png");

	// ----------------------  Acceptance Invariant Mass  -----------------------------


	TH1D *invMassAccNum = (TH1D*) histogramsInvariantMassMC_GEN_CUTS->Clone("invMassAccNum");
	TH1D *invMassAccDen = (TH1D*) histogramsInvariantMassMC[0]->Clone("invMassAccDen");

	invMassAccNum->Sumw2();
	invMassAccNum->SetStats(0);
	invMassAccNum->Divide(invMassAccDen);
	invMassAccNum->SetTitle("Acceptance - Invariant Mass (GEN_{cuts} / GEN)");
	TCanvas *acceptanceCanvas = new TCanvas("Acceptance", "Acceptance - RECO / GEN ", canvasXResolution,canvasYResolution);
	invMassAccNum->Draw("ep");
	acceptanceCanvas->SaveAs("Acceptance - InvariantMass.png");


 // ------------ Save histograms to a new file --------------------------
  TFile *out = new TFile("outputAnalysis.root", "RECREATE");


 // --------------------- DRAW THE SUCKERS ------------------------------

  Int_t palette[] = {kGreen, kRed, kBlue, kTeal, kYellow, kViolet, kMagenta};

  Double_t numberOfRecoEventsMC   = histogramsInvariantMassMC[6]->Integral();
  Double_t numberOfRecoEventsDATA = histogramsInvariantMassDATA[5]->Integral();

	//(TH1D** arrayHistogram, Int_t arraySize, TString canvasTitle, TString mainHistogramTitle, Int_t* colorsArray,Int_t logY, Int_t logX)
  drawAllHistogramsBasic(histogramsInvariantMassMC, 7, "invariantMassMC", "Invariant Mass - MC", palette,1, 1);
  drawAllHistogramsBasic(histogramsInvariantMassDATA, 7, "invariantMassData", "Invariant Mass - DATA", palette,1, 1);
	drawAllHistogramsBasic(histogramsRapidityMC, 7, "rapidityMC", "Rapidity - MC", palette, 1, 0);
	drawAllHistogramsBasic(histogramsRapidityDATA, 7, "rapidityDATA", "Rapidity - DATA", palette, 1, 0);

	//(TH1D *histMassMC, TH1D *histMassDATA, TString canvasTitle, TString mainHistogramTitle, Int_t logY, Int_t logX, Int_t normFactorMC, Int_t normFactorDATA)
  drawHistogramsMCvDATA(histogramsInvariantMassMC[6], histogramsInvariantMassDATA[5], "invariantMassMCvDATA", "Invariant Mass - MC vs DATA", 1, 1, numberOfRecoEventsMC, numberOfRecoEventsDATA);
	drawHistogramsMCvDATA(histogramsRapidityMC[6], histogramsRapidityDATA[5], "rapidityMCvDATA", "Rapidity - MC vs DATA", 1, 0, 1, 1);

}
