  //CUTS! - Not doing anything right now

  TString genTag = TString("Gen");
  TString recTag = TString("Rec");

  TString invTag = TString("-invM");

  TString cut0 = TString("Generated - No cut");
  TString cut1 = TString("Reconstructed - No cut");
  TString cut2 = TString("Reconstructed - mumi.Pt() > 4 && mupl.Pt() > 4");
  TString cut3 = TString("Reconstructed - mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 ");
  TString cut4 = TString("Reconstructed - mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 ");
  TString cut5 = TString("Reconstructed - mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10");
  TString cut6 = TString("Reconstructed - mumi.Pt() > 4 && mupl.Pt() > 4 && TMath::Abs(mumi.PseudoRapidity()) < 2.4 && TMath::Abs(mupl.PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu.M() > 10 && (1 - (TMath::Abs(mumi.Phi() - mupl.Phi()) / pi) ) < 0.008");

  TString cuts[7] = {cut0, cut1,cut2,cut3,cut4,cut5,cut6};