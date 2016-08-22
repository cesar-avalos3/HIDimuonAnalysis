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

TString cuts[7] = {cut0, cut1, cut2, cut3, cut4, cut5, cut6};

TString titleInvariantMassMC = TString("MC - #mu^{+}#mu^{-} - InvariantMass - ");
TString titleInvariantMassDATA = TString("DATA - #mu^{+}#mu^{-} - InvariantMass - ");
TString titleRapidityMC = TString("MC - #mu^{+}#mu^{-} - Rapidity - ");
TString titleRapidityDATA = TString("DATA - #mu^{+}#mu^{-} - Rapidity - ");
TString titleAcoDATA = TString("DATA - #mu^{+}#mu^{-} - Aco - ");
TString titleAcoMC = TString("DATA - #mu^{+}#mu^{-} - Aco - ");
Double_t TLegendSize[] = {0.611, 0.85, 0.984, 0.65};
Int_t canvasXResolution = 800;
Int_t canvasYResolution = 800;

Double_t varBinMass[] = {10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 33.0, 36.0, 39.0, 42.0, 46.0, 49.0, 55.0, 65.0, 75.0, 95.0, 100.0};

// Risky business
// Mode 0 is MC - Mode 1 is DATA
void createArrayOfHistogramsInvariantMass(TH1D **histArray, Int_t mode) {
  TString modeString = MCtag;
  TString titleInvariantMass = titleInvariantMassMC;
  if (mode == 1) {
    modeString = DATAtag;
    titleInvariantMass = titleInvariantMassDATA;
  }

  for (Int_t i = 0; i < 7; i++) {
    TString tag = modeString;
    tag += recTag;
    if (i == 0 && mode == 0) {
      tag = genTag;
    }
    tag += i;
    tag += invTag;
    histArray[i] = new TH1D(tag, titleInvariantMass + cuts[i], 26, varBinMass);
    histArray[i]->GetXaxis()->SetTitle("Invariant Mass - (GeV / C)");
    histArray[i]->GetYaxis()->SetTitle("Counts");
  }
}

// Mode 0 is MC - Mode 1 is DATA
void createArrayOfHistogramsRapidity(TH1D **histArray, Int_t mode) {
  TString modeString = MCtag;
  TString titleRapidity = titleRapidityMC;
  if (mode == 1) {
    modeString = DATAtag;
    titleRapidity = titleRapidityDATA;
  }

  for (Int_t i = 0; i < 7; i++) {
    TString tag = modeString;
    tag += recTag;
    if (i == 0 && mode == 0) {
      tag = genTag;
    }
    tag += i;
    tag += rapTag;

    histArray[i] = new TH1D(tag, titleRapidity + cuts[i], 25, -2.5, 2.5);
  }
}

void createArrayOfHistogramsAcoplanarity(TH1D **histArray, Int_t mode) {
  TString modeString = MCtag;
  TString titleAco = "Acoplanarity - ";
  if (mode == 1) {
    modeString = DATAtag;
    titleAco = titleAcoDATA;
  }

  for (Int_t i = 0; i < 7; i++) {
    TString tag = modeString;
    tag += recTag;
    if (i == 0 && mode == 0) {
      tag = genTag;
    }
    tag += i;
    tag += acoTag;

    histArray[i] = new TH1D(tag, titleAco + cuts[i], 30, 0, 0.06);
  }
}

bool goodEventSelector(Int_t eventNumber) {
  switch (eventNumber) {
  case (1831):
  case (3218):
  case (137118):
  case (152490):
  case (219038):
  case (386033):
  case (503861):
  case (633631):
  case (693277):
  case (695696):
  case (745655):
  case (829393):
  case (879798):
  case (881615):
  case (924552):
  case (930862):
  case (1046707):
  case (1061755):
  case (1144019):
  case (1157373):
  case (1166346):
  case (1252551):
  case (1454766):
  case (1532136):
  case (1565490):
  case (1618758):
  case (1691686):
  case (1771085):
  case (2069164):
  case (2249871):
  case (2439033):
  case (2448977):
  case (2565679):
  case (2611100):
  case (2616253):
  case (2621563):
  case (2694990):
  case (2735617):
  case (2812494):
  case (2830322):
  case (2925805):
  case (2937788):
  case (2945005):
  case (3026216):
  case (3036630):
  case (3077736):
  case (3094606):
  case (3166834):
  case (3198309):
  case (3203718):
  case (3375148):
  case (3433434):
  case (3442409):
  case (3471902):
  case (3577529):
  case (3648096):
  case (3783123):
  case (3962612):
  case (4062045):
  case (4070127):
  case (4139226):
  case (4187729):
  case (4251887):
    return false;
  }
  return true;
}

// TODO Change the CUTS integer into a TCuts, so the function is really just a generic cutting function
bool Cut(TLorentzVector *mumi, TLorentzVector *mupl, TLorentzVector *dimu, Int_t Reco_QQ_sign, Int_t Ntracks, Int_t CUTS) {

  switch (CUTS) {
  case (0):
    return true;
    break;
  case (1):
    return true;
    break;
  case (2):
    if (mumi->Pt() > 4 && mupl->Pt() > 4)
      return true;
    break;
  case (3):
    if (mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4)
      return true;
    break;
  case (4):
    if (mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0)
      return true;
    break;
  case (5):
    if (mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu->M() > 10)
      return true;
    break;
  case (6):
    if (mumi->Pt() > 4 && mupl->Pt() > 4 && TMath::Abs(mumi->PseudoRapidity()) < 2.4 && TMath::Abs(mupl->PseudoRapidity()) < 2.4 && Reco_QQ_sign == 0 && dimu->M() > 10 && Ntracks == 2)
      return true;
    break;
  }

  return false;
}

// Function requires an array of histograms, the array size, the title the canvas will have, the title above the first histogram, an arrya of colors,
// every histogram will be drawn using the same style of a solid color and no lines.
void drawAllHistogramsBasic(TH1D **arrayHistogram, Int_t arraySize, TString canvasTitle, TString mainHistogramTitle, Int_t *colorsArray, Int_t logY, Int_t logX) {

  TCanvas *temp = new TCanvas(canvasTitle, canvasTitle, canvasXResolution, canvasYResolution);
  if (logX)
    temp->SetLogx();
  if (logY)
    temp->SetLogy();

  TLegend *legendTemp = new TLegend(TLegendSize[0], TLegendSize[1], TLegendSize[2], TLegendSize[3]);
  arrayHistogram[0]->SetTitle(mainHistogramTitle);
  for (int i = 0; i < arraySize; i++) {
    TString mode = "SAME";
    if (i == 0)
      mode = "";
    arrayHistogram[i]->SetFillColor(colorsArray[i]);
    arrayHistogram[i]->Draw(mode);
    arrayHistogram[i]->Write();
    legendTemp->AddEntry(arrayHistogram[i], arrayHistogram[i]->GetTitle(), "f");
  }

  legendTemp->Draw("SAME");
  temp->SaveAs(mainHistogramTitle + ".png");
}

void drawHistogramsMCvDATA(TH1D *histMassMC, TH1D *histMassDATA, TString canvasTitle, TString mainHistogramTitle, Int_t logY, Int_t logX, Int_t normFactorMC, Int_t normFactorDATA) {
  TCanvas *temp = new TCanvas(canvasTitle, canvasTitle, canvasXResolution, canvasYResolution);
  if (logX)
    temp->SetLogx();
  if (logY)
    temp->SetLogy();

  histMassMC->Scale(1 / histMassMC->Integral());
  histMassDATA->Scale(1 / histMassDATA->Integral());

  TLegend *legendTemp = new TLegend(TLegendSize[0], TLegendSize[1], TLegendSize[2], TLegendSize[3]);

  histMassMC->SetTitle(mainHistogramTitle);
  histMassMC->SetFillColor(kGreen);
  histMassDATA->SetFillColor(kWhite);
  histMassDATA->SetMarkerStyle(4);
  histMassDATA->SetMarkerSize(1.3);
  histMassMC->Draw();
  histMassDATA->Draw("SAME&&P");
  legendTemp->AddEntry(histMassMC, "MC", "f");
  legendTemp->AddEntry(histMassDATA, "DATA");
  legendTemp->Draw("SAME");
  temp->SaveAs(mainHistogramTitle + ".png");
}

// The function will take a histogram and scale by the bin size bin by bin
TH1D *histogramsDeltaBinByBin(TH1D *histogramDelta, Double_t binArray[], Int_t binNumber) {
  TString newName = histogramDelta->GetName();
  newName += "delta";
  TH1D *temp = new TH1D(newName, histogramDelta->GetTitle(), binNumber, binArray);

  for (Int_t i = 0; i < binNumber; i++) {
    temp->SetBinContent(i, histogramDelta->GetBinContent(i) / binArray[i]);
  }

  return temp;
}
