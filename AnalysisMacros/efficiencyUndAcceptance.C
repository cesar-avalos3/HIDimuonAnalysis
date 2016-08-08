// File to create the histograms for efficiency and acceptance



// TODO Change the CUTS integer into a TCuts, so the function is really just a generic cutting function
bool Cut(TLorentzVector* mumi, TLorentzVector* mupl, TLorentzVector* dimu,Int_t Reco_QQ_sign ,int CUTS)
{

  TCut cut0 = TCut("1 > 0");
  TCut cut1 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4");
  TCut cut2 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 ");
  TCut cut3 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 ");
  TCut cut4 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10");
  TCut cut5 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10 && (1 - (TMath::Abs(mumi.Phi() - mupl.Phi()) / pi) ) < 0.008");

  switch(CUTS)
	{
		case(0):
		case(1):
			if(1 > 0)
			return true;
		break;
		case(2):
			if(mumi->Pt() > 4 && mupl->Pt() > 4)
			return true;
		break;
		case(3):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) && TMath::Abs(mupl->PseudoRapidity()) < 2.4)
			return true;
			break;
		case(4):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0)
			return true;
			break;
	}
        return false;
}


// TODO Implement more variables, like rapidity and acoplanarity
void efficiencyUndAcceptance()
{
  inFile = new TFile("OniaTree_MC_ppRec.root");

  myTree = (TTree*) inFile->Get("hionia/myTree");

  //Set up all pertinent variables for the loop-de-looping
  Int_t           Gen_QQ_size;
  TClonesArray    *Gen_QQ_4mom;
  TClonesArray    *Gen_QQ_mupl_4mom;
  TClonesArray    *Gen_QQ_mumi_4mom;

  TBranch        *b_Gen_QQ_size;   //!
  TBranch        *b_Gen_QQ_4mom;   //!
  TBranch        *b_Gen_QQ_mupl_4mom;   //!
  TBranch        *b_Gen_QQ_mumi_4mom;   //!

  Int_t		  Reco_QQ_sign;
  Int_t           Reco_QQ_size;
  TClonesArray    *Reco_QQ_4mom;
  TClonesArray    *Reco_QQ_mupl_4mom;
  TClonesArray    *Reco_QQ_mumi_4mom;

  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_4mom;   //!
  TBranch        *b_Reco_QQ_mumi_4mom;   //!
  TBranch	 *b_Reco_QQ_sign;

  //// mandatory
  Gen_QQ_4mom = 0;
  Gen_QQ_mupl_4mom = 0;
  Gen_QQ_mumi_4mom = 0;

  Reco_QQ_4mom = 0;
  Reco_QQ_mupl_4mom = 0;
  Reco_QQ_mumi_4mom = 0;
  Reco_QQ_sign = 0;

  
  myTree->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
  myTree->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
  myTree->SetBranchAddress("Gen_QQ_mupl_4mom", &Gen_QQ_mupl_4mom, &b_Gen_QQ_mupl_4mom);
  myTree->SetBranchAddress("Gen_QQ_mumi_4mom", &Gen_QQ_mumi_4mom, &b_Gen_QQ_mumi_4mom);

  myTree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  myTree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  myTree->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
  myTree->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
  myTree->SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign, &b_Reco_QQ_sign);

  TH1D *histogramGeneratedMass = new TH1D("Gen0", "MC - Generated - Invariant Mass", 100, 0, 100);
  TH1D *histogramReconstructedMass = new TH1D("Gen1", "MC - Generated - Invariant Mass", 100, 0, 100);
  TH1D *histogramReconstructedMassCuts1 = new TH1D("Gen2", "MC - Generated - Invariant Mass - Pt < 4",100,0,100);
  TH1D *histogramReconstructedMassCuts2 = new TH1D("Gen3", "MC - Generated - Invariant Mass - Pt < 4 && |Eta| < 2.4",100,0,100);
  TH1D *histogramReconstructedMassCuts3 = new TH1D("Gen4", "MC - Generated - Invariant Mass - Pt < 4 && |Eta| < 2.4 && Etc",100,0,100);
  TH1D *histograms[5];

  // The zeroeth histogram is always going to be the generated events, no cuts.

  histograms[0] = histogramGeneratedMass;
  histograms[1] = histogramReconstructedMass;
  histograms[2] = histogramReconstructedMassCuts1;
  histograms[3] = histogramReconstructedMassCuts2;
  histograms[4] = histogramReconstructedMassCuts3;


  //CUTS!

  TString fullGenericCut = TString("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10 && (1 - (TMath::Abs(mumi.Phi() - mupl.Phi()) / pi) ) < 0.008");
  TString cut0 = TString("1 > 0");
  TString cut1 = TString("mumi.Pt() > 4 && mupl.Pt() > 4");
  TString cut2 = TString("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) && TMath::Abs(mupl.PseudoRapidity()) < 2.4 ");
  TString cut3 = TString("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 ");
  
  TString* cuts[5];
  cuts[0] = &cut0;
  cuts[1] = &cut0;
  cuts[2] = &cut1;
  cuts[3] = &cut2;
  cuts[4] = &cut3;
  //Start the show
  Int_t numberOfEvents = myTree->GetEntries();

  //Acceptance furst
  for (Int_t eventIterator = 0; eventIterator < numberOfEvents; eventIterator++)
  {
  		myTree->GetEvent(eventIterator);
    
    if (Gen_QQ_size ==0) continue;
  	//Create Lorentz Vectors
      for(Int_t i = 0; i < Gen_QQ_size; i++)
      {
      	TLorentzVector *mupl_GEN = (TLorentzVector*) Gen_QQ_mupl_4mom->At(i);
      	TLorentzVector *mumi_GEN = (TLorentzVector*) Gen_QQ_mumi_4mom->At(i);
      	TLorentzVector *dimu_GEN = (TLorentzVector*) Gen_QQ_4mom->At(i);

      	for(Int_t u = 0; u < 1; u++)
      		{
			if(Cut(mumi_GEN, mupl_GEN, dimu_GEN, 0,u))
      			{
      				//Fill histograms invariantMass of dimuon
      				histograms[u]->Fill(dimu_GEN->M());
      			}
      		}
      }

for(Int_t i = 0; i < Reco_QQ_size; i++)
      {
        TLorentzVector *mupl_RECO = (TLorentzVector*) Reco_QQ_mupl_4mom->At(i);
        TLorentzVector *mumi_RECO = (TLorentzVector*) Reco_QQ_mumi_4mom->At(i);
        TLorentzVector *dimu_RECO = (TLorentzVector*) Reco_QQ_4mom->At(i);

        for(Int_t u = 1; u < 4; u++)
          {
      if(Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign, u))
            {
              //Fill histograms invariantMass of dimuon
              histograms[u]->Fill(dimu_RECO->M());
            }
          }
      }
  }

	histograms[0]->SetFillColor(kYellow);
	Double_t entriesOfGen = histograms[0]->GetEntries();  
	std::cout << "Number of entries " << entriesOfGen; 
	histograms[0]->Scale(1/entriesOfGen);
	histograms[0]->Draw();
	for(Int_t i = 1; i < 4; i++)
  {
	histograms[i]->SetFillColor(i * 5 + 8);  
	histograms[i]->Scale(1/entriesOfGen);  
        histograms[i]->Draw("SAME");

 }


}
