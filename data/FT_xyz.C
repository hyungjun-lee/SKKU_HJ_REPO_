enum
{
    rX = 0,
    rY,
    rZ
};

void FT_xyz()
{
    /// @load mc file
    TFile *MCfilename = new TFile("out_g4event_LH.mc.root", "READ");
    TTree *MCfiletree = (TTree *)MCfilename->Get("event");

    /// @declaration histogram
    TCanvas *c1 = new TCanvas("c1", "c1", 1800, 600);
    gPad->SetGrid();
    gStyle->SetOptStat(0);

    TH1D *HistMC[3];
    TH1D *HistDATA[3];

    TString HistTitle[3] ={"pX","pY","pZ"};

    for (int iHist = 0; iHist < 3; iHist++)
    {
        HistMC[iHist] = new TH1D(Form("hMC%d", iHist), "hMC "+ HistTitle[iHist], 100, -1.1, 1.1);
        HistDATA[iHist] = new TH1D(Form("hDATA%d", iHist), "hDATA " + HistTitle[iHist], 100, -1.1, 1.1);
    }

    /// @MC Part
    TClonesArray *fMCTrack = new TClonesArray("KBMCTrack");
    TClonesArray *fMCStep40 = new TClonesArray("KBMCStep");
    TBranch *bMCTrack = (TBranch *)MCfiletree->GetBranch("MCTrack");
    TBranch *bMCStep40 = (TBranch *)MCfiletree->GetBranch("MCStep40");
    int num_MCfiletree = MCfiletree->GetEntriesFast();

    TVector3 MCMomentum_arr[num_MCfiletree];
    bMCTrack->SetAddress(&fMCTrack);
    bMCStep40->SetAddress(&fMCStep40);

    for (int iMCTree = 0; iMCTree < num_MCfiletree; iMCTree++)
    {
        MCfiletree->GetEntry(iMCTree);

        /// @MCTrack
        int num_MCTrack = fMCTrack->GetEntriesFast();
        double MCTrack_px[num_MCfiletree];
        double MCTrack_py[num_MCfiletree];
        double MCTrack_pz[num_MCfiletree];

        for (int iTrack = 0; iTrack < num_MCTrack; iTrack++)
        {
            auto MCTrack = (KBMCTrack *)fMCTrack->At(iTrack);
            if (MCTrack->GetCreatorProcessID() == 0) // primary particle
            {
                auto MCMomentum = MCTrack->GetMomentum();
                MCMomentum_arr[iMCTree] = MCMomentum.Unit();

                MCTrack_px[iMCTree] = MCMomentum.Unit().X();
                MCTrack_py[iMCTree] = MCMomentum.Unit().Y();
                MCTrack_pz[iMCTree] = MCMomentum.Unit().Z();
                HistMC[rX]->Fill(MCTrack_px[iMCTree]);
                HistMC[rY]->Fill(MCTrack_py[iMCTree]);
                HistMC[rZ]->Fill(MCTrack_pz[iMCTree]);
            }
        }
    }

    /// @load result file
    TFile *KBfilename;
    TTree *KBfiletree;

    KBfilename = new TFile("out_g4event_LH.conv.eb7a905.L4.root", "READ");
    KBfiletree = (TTree *)KBfilename->Get("event");
    int num_KBfiletree = KBfiletree->GetEntriesFast();

    TClonesArray *fKBTrack = new TClonesArray("KBHelixTrack");
    TClonesArray *fFTHit = new TClonesArray("FTHit");

    TBranch *bKBTrack = (TBranch *)KBfiletree->GetBranch("Tracklet");
    TBranch *bFTHit = (TBranch *)KBfiletree->GetBranch("FTHit");

    bKBTrack->SetAddress(&fKBTrack);
    bFTHit->SetAddress(&fFTHit);

    TVector3 KBMomentum_arr[num_KBfiletree];

    for (int iKBTree = 0; iKBTree < num_KBfiletree; iKBTree++)
    {
        KBfiletree->GetEntry(iKBTree);

        /// @KBTrack
        int num_KBTrack = fKBTrack->GetEntriesFast();

        double KBTrack_px[num_KBfiletree];
        double KBTrack_py[num_KBfiletree];
        double KBTrack_pz[num_KBfiletree];

        for (int iKBTrack = 0; iKBTrack < num_KBTrack; iKBTrack++)
        {
            auto KBTrack = (KBHelixTrack *)fKBTrack->At(iKBTrack);
            auto KBMomentum = KBTrack->Momentum();

            KBMomentum_arr[iKBTree] = KBMomentum.Unit();
            KBTrack_px[iKBTree] = KBMomentum.Unit().X();
            KBTrack_py[iKBTree] = KBMomentum.Unit().Y();
            KBTrack_pz[iKBTree] = KBMomentum.Unit().Z();

            HistDATA[rX]->Fill(KBTrack_px[iKBTree]);
            HistDATA[rY]->Fill(KBTrack_py[iKBTree]);
            HistDATA[rZ]->Fill(KBTrack_pz[iKBTree]);
        }

        // double dot_result = MCMomentum_arr[iKBTree].Dot(KBMomentum_arr[iKBTree]); dot product
    }

    c1->Divide(3, 2);
    for (int iNum = 0; iNum <= 2; iNum++)
    {
        c1->cd(iNum + 1);
        gPad->SetGrid();
        gStyle->SetOptStat(0);
        HistMC[iNum]->GetYaxis()->SetTitle("Count");
        HistMC[iNum]->GetXaxis()->SetTitle("Momentum(unit)");
        HistMC[iNum]->Draw("same");

        c1->cd(iNum + 4);
        gPad->SetGrid();
        gStyle->SetOptStat(0);
        HistDATA[iNum]->GetYaxis()->SetTitle("Count");
        HistDATA[iNum]->GetXaxis()->SetTitle("Momentum(unit)");
        HistDATA[iNum]->Draw("same");
    }
}