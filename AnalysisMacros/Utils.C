  //CUTS! - Not doing anything right now

  TString genTag = TString("Gen");
  TString recTag = TString("Rec");

  TString invTag = TString("invM");
  TString acoTag = TString("aco");
  TString rapTag = TString("rap");


  TString ratioTag = TString("ratio");

  TString cut0 = TString("GEN - No cut");
  TString cut1 = TString("RECO - No cut");
  TString cut2 = TString("RECO - Pt_#mu > 4");
  TString cut3 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4");
  TString cut4 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4 sign == 0");
  TString cut5 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4 sign == 0 M_{#mu^+ #mu^-} > 10");
  TString cut6 = TString("RECO - Pt_#mu > 4 |#eta_#mu| < 2.4 sign == 0 M_{#mu^+ #mu^-} > 10 Aco < 0.008");

  TString cuts[7] = {cut0, cut1,cut2,cut3,cut4,cut5,cut6};