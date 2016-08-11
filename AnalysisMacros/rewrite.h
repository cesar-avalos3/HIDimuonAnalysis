#include "Utils.C"

	TH1D *histogramsInvariantMassMC[7];
	TH1D *histogramsRapidityMC[7];
	TH1D *histogramsAcoplanarityMC[7];

	TH1D *histogramsInvariantMassDATA[7];
	TH1D *histogramsRapidityDATA[7];
	TH1D *histogramsAcoplanarityDATA[7];

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
	Int_t		     Reco_QQ_sign_DATA;
	Int_t            Reco_QQ_size_DATA;
	TClonesArray    *Reco_QQ_4mom_DATA;
	TClonesArray    *Reco_QQ_mupl_4mom_DATA;
	TClonesArray    *Reco_QQ_mumi_4mom_DATA;
	TBranch         *b_Reco_QQ_size_DATA;   //!
	TBranch         *b_Reco_QQ_4mom_DATA;   //!
	TBranch         *b_Reco_QQ_mupl_4mom_DATA;   //!
	TBranch         *b_Reco_QQ_mumi_4mom_DATA;   //!
	TBranch	        *b_Reco_QQ_sign_DATA;
