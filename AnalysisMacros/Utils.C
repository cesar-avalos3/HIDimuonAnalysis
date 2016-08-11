  //CUTS! - Not doing anything right now

  TString genTag = TString("Gen");
  TString recTag = TString("Rec");

  TString invTag = TString("invM");
  TString acoTag = TString("aco");
  TString rapTag = TString("rap");

  TString MCtag = TString("MC_");
  TString DATAtag = TString("DATA_");

  TString ratioTag = TString("ratio");

  TString cut0 = TString("GEN - No cut");
  TString cut1 = TString("RECO - No cut");
  TString cut2 = TString("RECO - Pt_#mu > 4");
  TString cut3 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4");
  TString cut4 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4 sign == 0");
  TString cut5 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4 sign == 0 M_{#mu^+ #mu^-} > 10");
  TString cut6 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4 sign == 0 M_{#mu^+ #mu^-} > 10 Aco < 0.008");

  TString cuts[7] = {cut0, cut1,cut2,cut3,cut4,cut5,cut6};

  TString titleInvariantMassMC   = TString("MC - #mu^{+}#mu^{-} - InvariantMass - ");
  TString titleInvariantMassDATA = TString("DATA - #mu^{+}#mu^{-} - InvariantMass - ");
  TString titleRapidityMC = TString("MC - #mu^{+}#mu^{-} - Rapidity - ");
  TString titleRapidityDATA = TString("DATA - #mu^{+}#mu^{-} - Rapidity - ");

  // Risky business
  // Mode 0 is MC - Mode 1 is DATA
  void createArrayOfHistogramsInvariantMass(TH1D** histArray, Int_t mode)
  {	
  	TString modeString = MCtag;
  	TString titleInvariantMass = titleInvariantMassMC;
  	if(mode == 1) {modeString = DATAtag; titleInvariantMass = titleInvariantMassDATA;} 
  	

  Double_t varBinMass[]     = {10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0,18.0, 19.0, 20.0,22.0,24.0,26.0,28.0,30.0,33.0,36.0,39.0,42.0,46.0,49.0,55.0,65.0,75.0,95.0,100.0};
  	for(Int_t i = 0; i < 7; i++)
  	{
  		TString tag = modeString;
  		tag += recTag;
  		if(i == 0 && mode == 0){tag = genTag;}
  		tag += i;
  		tag += invTag;
  		histArray[i] = new TH1D(tag, titleInvariantMass + cuts[i], 26,varBinMass);
  		histArray[i]->GetXaxis()->SetTitle("Invariant Mass - (GeV / C)");
  		histArray[i]->GetYaxis()->SetTitle("Counts");
  	}
  }

  // Mode 0 is MC - Mode 1 is DATA
  TH1D **createArrayOfHistogramsRapidity(Int_t mode)
  {	
  	TH1D *temp[7];
  	TString modeString = MCtag;
  	TString titleInvariantMass = titleInvariantMassMC;
  	if(modeString == 1) {modeString = DATAtag; titleInvariantMass = titleInvariantMassDATA;} 

  	for(Int_t i = 0; i < 7; i++)
  	{
  		TString tag = modeString;
  		tag += recTag;
  		if(i == 0 && mode == 0){tag = genTag;}
  		tag += i;
  		tag += invTag;

  		temp[i] = new TH1D(tag, titleInvariantMass + cuts[i], 200, 0, 100);
  	}
  	return temp;
  }

  

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
			&& (1 - (TMath::Abs(mumi->Phi() - mupl->Phi()) / TMath::Pi()) ) < 0.008 && Ntracks == 2)
			return true;
			break;
	}

        return false;
}

