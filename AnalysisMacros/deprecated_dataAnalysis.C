// Macros to create the histogramsInvariantMass for efficiency and acceptance
#include "Utils.C"
// Input is an array of pointers 1D - histograms, an array of 

Int_t startingEvent = 0;

// Tree was having trouble with these events, this function hard-codes each troublesome evenve
// TODO - There must be a good event selector in the tree, have to investigate this.
bool goodEventSelector(Int_t eventNumber)
{
	switch(eventNumber)
	{
		case(1831): case(3218): case(137118): case(152490): case(219038):
		case(386033): case(503861): case(633631): case(693277): case(695696): 
		case(745655): case(829393): case(879798): case(881615): case(924552):
		case(930862): case(1046707): case(1061755): case(1144019): case(1157373):
		case(1166346): case(1252551): case(1454766): case(1532136): case(1565490):
		case(1618758): case(1691686): case(1771085): case(2069164): case(2249871):
		case(2439033): case(2448977): case(2565679): case(2611100): case(2616253):
		case(2621563): case(2694990): case(2735617): case(2812494): case(2830322):
		case(2925805): case(2937788): case(2945005): case(3026216): case(3036630):
		case(3077736): case(3094606): case(3166834): case(3198309): case(3203718):
		case(3375148): case(3433434): case(3442409): case(3471902): case(3577529):
		case(3648096): case(3783123): case(3962612): case(4062045): case(4070127):
		case(4139226): case(4187729): case(4251887):
		return false;
	}
	return true;
}

void fillHistograms(TH1D *histogramsToBeFilled[], const TLorentzVector* lorentzArray[], Int_t mode)
{
  // Mode 0 is Invariant Mass - With three different Rapidity binnings 
  // Mode 1 is Rapidity - With three different Invariant binnings
  // Mode 2 is Acoplanarity - WIP
  //
  // See Histograms Array Convention to see what orders each follow
  //
  // Lorentz Array will have the following convention: 0 - Mu Plus
  //                                                   1 - Mu Minus
  //                                                   2 - DiMuon
  //

  switch(mode)
  {
    case 0:
      for(Int_t iterator = 0; iterator < 3; iterator++)
      {

      }      
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
        std::cout << "a/b = " << (a/b) << "\n";
      }
      else
      {
        temp->Fill(0);
        std::cout << "0 \n";
      }
    }
    return temp;
}

// TODO Change the CUTS integer into a TCuts, so the function is really just a generic cutting function
bool Cut(TLorentzVector* mumi, TLorentzVector* mupl, TLorentzVector* dimu,Int_t Reco_QQ_sign, Int_t Ntracks,Int_t CUTS)
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
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4)
			return true;
			break;
		case(4):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0)
			return true;
			break;
		case(5):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu->M() > 10)
			return true;
			break;
		case(6):
			if(mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu->M() > 10
			&& (1 - (TMath::Abs(mumi->Phi() - mupl->Phi()) / TMath::Pi()) ) < 0.008)
			return true;
			break;
	}

        return false;
}


// TODO Implement more variables, like rapidity and acoplanarity
void dataAnalysis()
{
  TFile* inFile = new TFile("../Tree/OniaTree_part_NoCuts_allTrig.root");

  TTree* myTree = (TTree*) inFile->Get("hionia/myTree");

  //Set up all pertinent variables for the loop-de-looping
  Int_t            Ntracks;
  Int_t            Gen_QQ_size;
  TClonesArray    *Gen_QQ_4mom;
  TClonesArray    *Gen_QQ_mupl_4mom;
  TClonesArray    *Gen_QQ_mumi_4mom;

  TBranch        *b_Ntracks;
  TBranch        *b_Gen_QQ_size;   //!
  TBranch        *b_Gen_QQ_4mom;   //!
  TBranch        *b_Gen_QQ_mupl_4mom;   //!
  TBranch        *b_Gen_QQ_mumi_4mom;   //!

  Int_t		       Reco_QQ_sign;
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

  
  myTree->SetBranchAddress("Ntracks", &Ntracks, &b_Ntracks);

  myTree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  myTree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  myTree->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
  myTree->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
  myTree->SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign, &b_Reco_QQ_sign);


  // Dynamically create the invariant Mass Histograms - Could be extended to create every other type of histograms within it
  TH1D *histogramsInvariantMass[7];

  Int_t binsMass = 200;
  TString titleInvariantMass = TString("MC - #mu^{+}#mu^{-} - InvariantMass - ");
  Int_t numberOfInvariantMassHistograms = 7;

  // CONVENTION - The zeroeth histogram is always going to be the generated events, no cuts.
  // Check Util.C for the whole list of cuts and their indices
  for(Int_t i = 0; i < numberOfInvariantMassHistograms; i++)
  {
    TString tag = recTag;
    if(i == 0) tag = genTag;
    tag += i;
    tag += invTag;
    histogramsInvariantMass[i] = new TH1D(tag, titleInvariantMass + cuts[i] , binsMass, 0, 100);
  }

  // Settings for Rapidity
  TH1D *histogramsRapidity[7];
  Int_t binsRapidity = 100;
  Double_t minRapidity = -2.5;
  Double_t maxRapidity =  2.5;
  TString titleRapidity = TString("MC - #mu^{+}#mu^{-} - Rapidity - ");
  Int_t numberOfRapidityHistograms = 7;

  for(Int_t i = 0; i < numberOfRapidityHistograms; i++)
  {
    TString tag = recTag;
    if(i == 0) tag = genTag;
    tag += i;
    tag += rapTag;
    histogramsRapidity[i] = new TH1D(tag, titleRapidity + cuts[i] , 26, -2.5, 2.5);
  }


  TH1D *histogramsAcoplanarity[7];
  Double_t maxAcoplanarity = 0.06;
  Int_t binsAcoplanarity = 30;
  TString titleAcoplanarity = TString("MC - Acoplanarity - ");

  for(Int_t i = 0; i < numberOfRapidityHistograms; i++)
  {
    TString tag = recTag;
    if(i == 0) tag = genTag;
    tag += i;
    tag += acoTag;
    histogramsAcoplanarity[i] = new TH1D(tag, titleAcoplanarity + cuts[i], binsAcoplanarity, 0, maxAcoplanarity);
  }

  //Start the show
  Int_t numberOfEvents = myTree->GetEntries();

  //Generated events first
  for (Int_t eventIterator = startingEvent; eventIterator < numberOfEvents; eventIterator++)
  {
  		if(!goodEventSelector(eventIterator)) eventIterator += 2;
  		myTree->GetEvent(eventIterator);
// Reconstructed events next  	
  	//std::cout << "Event number: " << eventIterator << "\n";
	for(Int_t i = 0; i < Reco_QQ_size; i++)
      {
        TLorentzVector *mupl_RECO = (TLorentzVector*) Reco_QQ_mupl_4mom->At(i);
        TLorentzVector *mumi_RECO = (TLorentzVector*) Reco_QQ_mumi_4mom->At(i);
        TLorentzVector *dimu_RECO = (TLorentzVector*) Reco_QQ_4mom->At(i);
        TLorentzVector *vectors[] = {mupl_RECO, mumi_RECO, dimu_RECO};

        for(Int_t u = 1; u < 7; u++)
          {
      if(Cut(mumi_RECO, mupl_RECO, dimu_RECO, Reco_QQ_sign,Ntracks, u))
            {
              //Fill histogramsInvariantMass invariantMass of dimuon
              histogramsInvariantMass[u]->Fill(dimu_RECO->M());
              histogramsRapidity[u]->Fill(dimu_RECO->Rapidity());
              histogramsAcoplanarity[u]->Fill(1 - (TMath::Abs(mupl_RECO->Phi() - mumi_RECO->Phi() )) / TMath::Pi() );
            }
          }
      }
  }

  // Draw histogramsInvariantMass
	histogramsInvariantMass[0]->SetFillColor(kYellow); // TODO - Change into an array of colors
	Double_t entriesOfGen = histogramsInvariantMass[0]->GetEntries();  
	std::cout << "Number of entries " << entriesOfGen; 

  // ------------- DRAW INVARIANT MASS ----------

  TCanvas *invariantMassCanvas = new TCanvas("invariantMassCanvas", "invMassCanv", 1000,1000);
	TLegend *legend = new TLegend(0.65,0.57,0.98,0.76);
  for(Int_t i = 0; i < 7; i++)
  {
    TString options = "SAME";
    if(i == 0) options = ""; // Reset the sucker
	  histogramsInvariantMass[i]->SetFillColor(i * 5 + 8);  
	  //histogramsInvariantMass[i]->Scale(1/entriesOfGen);  
    histogramsInvariantMass[i]->Draw(options);
    legend->AddEntry(histogramsInvariantMass[i], histogramsInvariantMass[i]->GetTitle(), "f");
  }
  legend->Draw("SAME");

  // ------------- DRAW ACOPLANARITY ----------

  TCanvas *acoplanarityCanvas = new TCanvas("acoCanvas", "acoCanv", 1000,1000);
  TLegend *acoLegend = new TLegend(0.65,0.57,0.98,0.76);
  for(Int_t i = 0; i < 7; i++)
  {
    TString options = "SAME";
    if(i == 0) options = ""; // Reset the sucker
    histogramsAcoplanarity[i]->SetFillColor(i * 5 + 8);  
    histogramsAcoplanarity[i]->Draw(options);
    acoLegend->AddEntry(histogramsAcoplanarity[i], histogramsAcoplanarity[i]->GetTitle(), "f");
  }

  acoLegend->Draw("SAME");

  // ------------- DRAW RAPIDITY -------------

  histogramsRapidity[0]->SetFillColor(kYellow); // TODO - Change into an array of colors
  Double_t entriesOfGenRapidity = histogramsRapidity[0]->GetEntries();  

  TCanvas *neued = new TCanvas("canvas", "neue", 1000,1000);
  TLegend *legendRapidity = new TLegend(0.65,0.57,0.98,0.76);
  
  for(Int_t i = 0; i < 7; i++)
  {
    TString options = "SAME";
    if(i == 0) options = ""; // Reset the sucker
    histogramsRapidity[i]->SetFillColor(i * 5 + 8);  
    //histogramsRapidity[i]->Scale(1/entriesOfGenRapidity);  
    histogramsRapidity[i]->Draw(options);
    legendRapidity->AddEntry(histogramsRapidity[i], histogramsRapidity[i]->GetTitle(), "f");
  }
  neued->SetLogy();

  // ---------------- DRAW RATIO INVMASS ---------------
  TCanvas *rapidityCanvas = new TCanvas("invMassRatioCanvas", "Invariant Mass Ratio Canvas", 1000,1000);
  TH1D *histogramRatioRapidityCutNone = new TH1D("RatioRapid1", "MC - Reconstructed / Generated - Rapidity - No Cuts",binsRapidity,0, 5);
  TH1D *histogramRatioRapidityCutOne = new TH1D("RatioRapid2", "MC - Reconstructed / Generated - Rapidity - Pt < 4 && |Eta| < 2.4",binsRapidity,0, 5);
  TH1D *histogramRatioRapidityCutTwo = new TH1D("RatioRapid3", "MC - Reconstructed / Generated - Rapidity - Pt < 4 && |Eta| < 2.4 && Etc",binsRapidity,0, 5);

  // TODO fix ugliness

  histogramRatioRapidityCutNone = histogramRatiosBinByBin(histogramsInvariantMass[1], histogramsInvariantMass[0], 200, 0, 100);
  histogramRatioRapidityCutOne = histogramRatiosBinByBin(histogramsInvariantMass[3], histogramsInvariantMass[0], 200,0 , 100);
  histogramRatioRapidityCutTwo = histogramRatiosBinByBin(histogramsInvariantMass[4], histogramsInvariantMass[0], 200, 0 , 100);

  TH1D *histogramRatiosRapidity[3];
  histogramRatiosRapidity[0] = histogramRatioRapidityCutNone;
  histogramRatiosRapidity[1] = histogramRatioRapidityCutOne;
  histogramRatiosRapidity[2] = histogramRatioRapidityCutTwo;

  Int_t arrayOfColors[3] = {kYellow, kRed, kBlue};

  TH1D *den = (TH1D*) histogramsInvariantMass[0]->Clone("den");
  TH1D *num = (TH1D*) histogramsInvariantMass[6]->Clone("num");
  num->Divide(den);

  for(Int_t it = 0; it < 3; it++)
  {
      //histogramRatiosRapidity[it]->Scale(1 / entriesOfGen);
      histogramRatiosRapidity[it]->SetFillColorAlpha(arrayOfColors[it], 1);
      TString mode = "SAME";
      if(it == 0) mode = "";
      histogramRatiosRapidity[it]->Draw(mode);
      legendRapidity->AddEntry(histogramRatiosRapidity[it], histogramRatiosRapidity[it]->GetTitle(), "f");
  }
  legendRapidity->Draw("SAME");

  num->SetTitle("MC - InvMass - RECO / GEN");
  num->GetXaxis()->SetTitle("Invariant Mass - GeV / C");
  num->SetMarkerStyle(20);
  num->SetMarkerSize(0.4);
  num->Draw("ep");
  rapidityCanvas->SaveAs("invMassRatio.png");

  TCanvas *rapidityRatioCanvas = new TCanvas("rapidityRatioCanvas", "Rapidity Ratio Canvas", 1000, 1000);

  TH1D *numRapidity = (TH1D*) histogramsRapidity[6]->Clone("numRapidity");
  TH1D *denRapidity = (TH1D*) histogramsRapidity[0]->Clone("numRapidity");
  numRapidity->Divide(denRapidity);
  numRapidity->SetTitle("MC - Rapidity - RECO / GEN");
  numRapidity->GetXaxis()->SetTitle("Rapidity");
  numRapidity->SetMarkerStyle(20);
  numRapidity->SetMarkerSize(0.4);
  numRapidity->Draw("ep");
  rapidityRatioCanvas->SaveAs("rapidityRatio.png");

  //------------ ACOPLANARITY RATIO ------------
  //TH1D* histogramRatiosAcoplanarity[7];

  TCanvas *acoplanarityRatioCanvas = new TCanvas("acoplanarityRatioCanvas", "Acoplanarity Ratio Canvas", 1000, 1000);

  TH1D* histogramAcoplanarityRatioDen = (TH1D*) histogramsAcoplanarity[0]->Clone("histogramAcoplanarityRatioDen");
  TH1D* histogramAcoplanarityRatio = (TH1D*) histogramsAcoplanarity[6]->Clone("histogramAcoplanarityRatio");
  histogramAcoplanarityRatio->Divide( histogramAcoplanarityRatioDen );
  histogramAcoplanarityRatio->SetTitle("MC - Acoplanarity - RECO / GEN");
  histogramAcoplanarityRatio->GetXaxis()->SetTitle("Aco = #pi - |#Delta #phi|");
  histogramAcoplanarityRatio->SetMarkerStyle(20);
  histogramAcoplanarityRatio->SetMarkerSize(0.4);
  histogramAcoplanarityRatio->Draw("ep");
  acoplanarityRatioCanvas->SaveAs("acoRatio.png");
}
