// Macros to create the histogramsInvariantMass for efficiency and acceptance


// Input is an array of pointers 1D - histograms, an array of 
void fillHistograms(TH1D *histogramsToBeFilled[], const *TLorentzVector[] lorentzArray, Int_t mode)
{
  // Mode 0 is Invariant Mass - With three different Rapidity binnings 
  // Mode 1 is Rapidity - With three different Invariant binnings
  // Mode 2 is Acoplanarity - WIP
  //
  // See Histograms Array Convention to see what orders each follow
  // Lorentz Array will have the following convention: 0 - Mu Plus
  //                                                   1 - Mu Minus
  //                                                   2 - DiMuon
  
  switch(mode)
  {
    case 0:
    break;
    case 1:
    break;
    case 2:
    break;
    case 3:
    break;
  }
}


TH1D *histogramRatiosBinByBin(TH1D *Numerator, TH1D *Denominator, Int_t numberOfBins, Double_t minX = -999, Double_t maxX = 999)
{
    //Default state, use the numerator's range
    if(maxX == 999 && minX == -999)
    {
      minX = Numerator->GetXaxis()->GetXmin();
      maxX = Numerator->GetXaxis()->GetXmax();
    }
    TH1D *temp = new TH1D("Ratio", Numerator->GetTitle(), numberOfBins, minX, maxX);
    
    for(Int_t it = 0; it < numberOfBins; it++)
    {
      Double_t a = Numerator->GetBinContent(it);
      Double_t b = Denominator->GetBinContent(it);
      if(b != 0)
      {
        temp->Fill(a/b);
      }
      else
      {
        temp->Fill(0);
      }
    }
    return temp;
}

// TODO Change the CUTS integer into a TCuts, so the function is really just a generic cutting function
bool Cut(TLorentzVector* mumi, TLorentzVector* mupl, TLorentzVector* dimu,Int_t Reco_QQ_sign ,Int_t CUTS)
{

 switch(CUTS)
	{
		case(0):
		case(1):
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
		case(5):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu->M() > 10)
			return true;
			break;
		case(6):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu->M() > 10
			&& (1 - (TMath::Abs(mumi->Phi() - mupl->Phi()) / TMath::Pi()) ) < 0.008)
			return true;
			break;
	}

        return false;
}


// TODO Implement more variables, like rapidity and acoplanarity
void efficiencyUndAcceptance()
{
  TFile* inFile = new TFile("../Tree/OniaTree_MC_ppRec.root");

  TTree* myTree = (TTree*) inFile->Get("hionia/myTree");

  //Set up all pertinent variables for the loop-de-looping
  Int_t            Gen_QQ_size;
  TClonesArray    *Gen_QQ_4mom;
  TClonesArray    *Gen_QQ_mupl_4mom;
  TClonesArray    *Gen_QQ_mumi_4mom;

  TBranch        *b_Gen_QQ_size;   //!
  TBranch        *b_Gen_QQ_4mom;   //!
  TBranch        *b_Gen_QQ_mupl_4mom;   //!
  TBranch        *b_Gen_QQ_mumi_4mom;   //!

  Int_t		         Reco_QQ_sign;
  Int_t            Reco_QQ_size;
  TClonesArray    *Reco_QQ_4mom;
  TClonesArray    *Reco_QQ_mupl_4mom;
  TClonesArray    *Reco_QQ_mumi_4mom;

  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_4mom;   //!
  TBranch        *b_Reco_QQ_mumi_4mom;   //!
  TBranch	       *b_Reco_QQ_sign;

  // Mandatory
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


  // TODO - Dynamically create this

  Int_t binsMass = 200;
  TH1D *histogramGeneratedMass = new TH1D("Gen0", "MC - Generated - Invariant Mass", binsMass, 0, 100);
  TH1D *histogramReconstructedMass = new TH1D("Gen1", "MC - Reconstructed - Invariant Mass", binsMass, 0, 100);
  TH1D *histogramReconstructedMassCuts1 = new TH1D("Gen2", "MC - Reconstructed - Invariant Mass - Pt < 4",binsMass,0,100);
  TH1D *histogramReconstructedMassCuts2 = new TH1D("Gen3", "MC - Reconstructed - Invariant Mass - Pt < 4 && |Eta| < 2.4",binsMass,0,100);
  TH1D *histogramReconstructedMassCuts3 = new TH1D("Gen4", "MC - Reconstructed - Invariant Mass - Pt < 4 && |Eta| < 2.4 && Etc",binsMass,0,100);
  
  TH1D *histogramsInvariantMass[5];


  // Settings for Rapidity
  Int_t binsRapidity = 100;
  Double_t minRapidity = -2.5;
  Double_t maxRapidity =  2.5;

  TH1D *histogramGeneratedRapidity = new TH1D("Rapid1", "MC - Generated - Rapidity", binsRapidity, minRapidity, maxRapidity);
  TH1D *histogramReconstructedRapidity = new TH1D("Rapid2", "MC - Reconstructed - Rapidity", binsRapidity, minRapidity, maxRapidity);
  TH1D *histogramReconstructedRapidityCuts1 = new TH1D("Rapid3", "MC - Reconstructed - Rapidity - Pt < 4",binsRapidity,minRapidity, maxRapidity);
  TH1D *histogramReconstructedRapidityCuts2 = new TH1D("Rapid4", "MC - Reconstructed - Rapidity - Pt < 4 && |Eta| < 2.4",binsRapidity,minRapidity, maxRapidity);
  TH1D *histogramReconstructedRapidityCuts3 = new TH1D("Rapid4", "MC - Reconstructed - Rapidity - Pt < 4 && |Eta| < 2.4 && Etc",binsRapidity,minRapidity, maxRapidity);

  TH1D *histogramsRapidity[5];



  // CONVENTION - The zeroeth histogram is always going to be the generated events, no cuts.
  histogramsInvariantMass[0] = histogramGeneratedMass;
  histogramsInvariantMass[1] = histogramReconstructedMass;
  histogramsInvariantMass[2] = histogramReconstructedMassCuts1;
  histogramsInvariantMass[3] = histogramReconstructedMassCuts2;
  histogramsInvariantMass[4] = histogramReconstructedMassCuts3;

  histogramsRapidity[0] = histogramGeneratedRapidity;
  histogramsRapidity[1] = histogramReconstructedRapidity;
  histogramsRapidity[2] = histogramReconstructedRapidityCuts1;
  histogramsRapidity[3] = histogramReconstructedRapidityCuts2;
  histogramsRapidity[4] = histogramReconstructedRapidityCuts3;



  //CUTS! - Not doing anything right now
  TCut cut0 = TCut("1 > 0");
  TCut cut1 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4");
  TCut cut2 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 ");
  TCut cut3 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 ");
  TCut cut4 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10");
  TCut cut5 = TCut("mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10 && (1 - (TMath::Abs(mumi.Phi() - mupl.Phi()) / pi) ) < 0.008");

  TCut* cuts[5];
  cuts[0] = &cut0;
  cuts[1] = &cut0;
  cuts[2] = &cut1;
  cuts[3] = &cut2;
  cuts[4] = &cut3;

  //Start the show
  Int_t numberOfEvents = myTree->GetEntries();

  //Generated events first
  for (Int_t eventIterator = 0; eventIterator < numberOfEvents; eventIterator++)
  {
  		myTree->GetEvent(eventIterator);
    
    if (Gen_QQ_size == 0) continue;
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
      				//Fill histogramsInvariantMass invariantMass of dimuon
      				histogramsInvariantMass[u]->Fill(dimu_GEN->M());
              histogramsRapidity[u]->Fill(dimu_GEN->Rapidity());
      			}
      		}
      }

// Reconstructed events next
for(Int_t i = 0; i < Reco_QQ_size; i++)
      {
        TLorentzVector *mupl_RECO = (TLorentzVector*) Reco_QQ_mupl_4mom->At(i);
        TLorentzVector *mumi_RECO = (TLorentzVector*) Reco_QQ_mumi_4mom->At(i);
        TLorentzVector *dimu_RECO = (TLorentzVector*) Reco_QQ_4mom->At(i);
        TLorentzVector *vectors[] = {mupl_RECO, mumi_RECO, dimu_RECO};

        for(Int_t u = 1; u < 4; u++)
          {
      if(Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign, u))
            {
              //Fill histogramsInvariantMass invariantMass of dimuon
              histogramsInvariantMass[u]->Fill(dimu_RECO->M());
              histogramsRapidity[u]->Fill(dimu_RECO->Rapidity());
            }
          }
      }
  }

  // Draw histogramsInvariantMass
	histogramsInvariantMass[0]->SetFillColor(kYellow); // TODO - Change into an array of colors
	Double_t entriesOfGen = histogramsInvariantMass[0]->GetEntries();  
	std::cout << "Number of entries " << entriesOfGen; 

  TCanvas *invariantMassCanvas = new TCanvas("invariantMassCanvas", "invMassCanv", 1000,1000);
	TLegend *legend = new TLegend(0.65,0.57,0.98,0.76);
  for(Int_t i = 0; i < 4; i++)
  {
    TString options = "SAME";
    if(i == 0) options = ""; // Reset the sucker
	  histogramsInvariantMass[i]->SetFillColor(i * 5 + 8);  
	  histogramsInvariantMass[i]->Scale(1/entriesOfGen);  
    histogramsInvariantMass[i]->Draw(options);
    legend->AddEntry(histogramsInvariantMass[i], histogramsInvariantMass[i]->GetTitle(), "f");
  }
  legend->Draw("SAME");


  histogramsRapidity[0]->SetFillColor(kYellow); // TODO - Change into an array of colors
  Double_t entriesOfGenRapidity = histogramsRapidity[0]->GetEntries();  

  TCanvas *neued = new TCanvas("canvas", "neue", 1000,1000);
  TLegend *legendRapidity = new TLegend(0.65,0.57,0.98,0.76);
  /*
  for(Int_t i = 0; i < 4; i++)
  {
    TString options = "SAME";
    if(i == 0) options = ""; // Reset the sucker
    histogramsRapidity[i]->SetFillColor(i * 5 + 8);  
    histogramsRapidity[i]->Scale(1/entriesOfGenRapidity);  
    histogramsRapidity[i]->Draw(options);
    legendRapidity->AddEntry(histogramsRapidity[i], histogramsRapidity[i]->GetTitle(), "f");
  }
*/
  TH1D *histogramRatioRapidityCutNone = new TH1D("RatioRapid1", "MC - Reconstructed / Generated - Rapidity - No Cuts",binsRapidity,0, 5);
  TH1D *histogramRatioRapidityCutOne = new TH1D("RatioRapid2", "MC - Reconstructed / Generated - Rapidity - Pt < 4 && |Eta| < 2.4",binsRapidity,0, 5);
  TH1D *histogramRatioRapidityCutTwo = new TH1D("RatioRapid3", "MC - Reconstructed / Generated - Rapidity - Pt < 4 && |Eta| < 2.4 && Etc",binsRapidity,0, 5);

  // TODO fix ugliness

  histogramRatioRapidityCutNone = histogramRatiosBinByBin(histogramReconstructedMass, histogramGeneratedMass, binsMass, 0, 2);
  histogramRatioRapidityCutOne = histogramRatiosBinByBin(histogramReconstructedMassCuts1, histogramGeneratedMass, binsMass,0 , 2);
  histogramRatioRapidityCutTwo = histogramRatiosBinByBin(histogramReconstructedMassCuts2, histogramGeneratedMass, binsMass, 0 , 2);


  TH1D *histogramRatiosRapidity[3];
  histogramRatiosRapidity[0] = histogramRatioRapidityCutNone;
  histogramRatiosRapidity[1] = histogramRatioRapidityCutOne;
  histogramRatiosRapidity[2] = histogramRatioRapidityCutTwo;

  Int_t arrayOfColors[3] = {kYellow, kRed, kBlue};

  for(Int_t it = 0; it < 3; it++)
  {
      histogramRatiosRapidity[it]->Scale(1 / entriesOfGen);
      histogramRatiosRapidity[it]->SetFillColorAlpha(arrayOfColors[it], 0.2 - (0.05 * it));
      TString mode = "SAME";
      if(it == 0) mode = "";
      histogramRatiosRapidity[it]->Draw(mode);
      legendRapidity->AddEntry(histogramRatiosRapidity[it], histogramRatiosRapidity[it]->GetTitle(), "f");
  }
  legendRapidity->Draw("SAME");
}
