enum
{
    L4,
    L6,
    L8,
    L10
};

void FT_res()
{
    /// @load mc file
    TFile *MCfilename = new TFile("out_g4event_LH.mc.root", "READ");
    TTree *MCfiletree = (TTree *)MCfilename->Get("event");

    /// @declaration histogram
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    gPad->SetGrid();
    gStyle->SetOptStat(0);
    TH1D *Hist[4];
    TLegend *legend_data = new TLegend(0.719298, 0.744348, 0.943609, 0.918261, NULL, "brNDC");

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

                MCTrack_px[iMCTree] = MCMomentum.X();
                MCTrack_py[iMCTree] = MCMomentum.Y();
                MCTrack_pz[iMCTree] = MCMomentum.Z();
            }
        }
    }

    /// @load result file
    TFile *KBfilename[4];
    TTree *KBfiletree[4];
    for (int i = 3; i < 4; i++)
    {
        Hist[i] = new TH1D(Form("hist_%i", i), Form("hist_%i", i), 500, 0.95, 1.05);
        KBfilename[i] = new TFile(Form("out_g4event_LH.conv.eb7a905.L%i.root", 2 * (i + 2)), "READ");
        KBfiletree[i] = (TTree *)KBfilename[i]->Get("event");

        int num_KBfiletree = KBfiletree[i]->GetEntriesFast();

        TClonesArray *fKBTrack = new TClonesArray("KBHelixTrack");
        TClonesArray *fFTHit = new TClonesArray("FTHit");

        TBranch *bKBTrack = (TBranch *)KBfiletree[i]->GetBranch("Tracklet");
        TBranch *bFTHit = (TBranch *)KBfiletree[i]->GetBranch("FTHit");

        bKBTrack->SetAddress(&fKBTrack);
        bFTHit->SetAddress(&fFTHit);

        TVector3 KBMomentum_arr[num_KBfiletree];

        for (int iKBTree = 0; iKBTree < num_KBfiletree; iKBTree++)
        {
            KBfiletree[i]->GetEntry(iKBTree);

            /// @KBTrack
            int num_KBTrack = fKBTrack->GetEntriesFast();

            double KBTrack_px[num_KBfiletree];
            double KBTrack_py[num_KBfiletree];
            double KBTrack_pz[num_KBfiletree];

            for (int iKBTrack = 0; iKBTrack < num_KBTrack; iKBTrack++)
            {
                auto KBTrack = (KBHelixTrack *)fKBTrack->At(iKBTrack);
                auto KBMomentum = KBTrack->Momentum();

                KBTrack_px[iKBTree] = -KBMomentum.X();
                KBTrack_py[iKBTree] = KBMomentum.Y();
                KBTrack_pz[iKBTree] = -KBMomentum.Z();
                // KBMomentum_arr[iKBTree] = KBMomentum.Unit();
                KBMomentum_arr[iKBTree].SetXYZ(KBTrack_px[iKBTree], KBTrack_py[iKBTree], KBTrack_pz[iKBTree]);
                KBMomentum_arr[iKBTree] = KBMomentum_arr[iKBTree].Unit();
            }

            double dot_result = MCMomentum_arr[iKBTree].Dot(KBMomentum_arr[iKBTree]);
            if (dot_result > 0.9)
                cout << iKBTree << endl;
            Hist[i]->Fill(dot_result);
        }

        /// @ dot product histogram fill
        Hist[i]->GetXaxis()->SetTitle("cos#theta");
        Hist[i]->GetYaxis()->SetTitle("count");
        Hist[i]->SetTitle(" ");
        Hist[i]->SetLineColor(i + 1);
        Hist[i]->Draw("same");
        legend_data->AddEntry(Form("hist_%i", i), Form("Layer amount %i", 2 * (i + 2)), "l");
    }
    legend_data->SetBorderSize(1);
    legend_data->SetTextAlign(22);
    legend_data->SetTextFont(62);
    legend_data->SetTextSize(0.0313043);
    legend_data->SetTextAlign(12);
    //legend_data->Draw();

    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////

    // TFile *KBfilename[i] = new TFile("out_g4event_LH.conv.eb7a905.L4.root", "READ");
    // TTree *KBfiletree[i] = (TTree *)KBfilename->Get("event");
    /*

     int num_MCfiletree = MCfiletree->GetEntriesFast();
     int num_KBfiletree = KBfiletree->GetEntriesFast();

     if (num_MCfiletree != num_KBfiletree)
     {
         cout << "   Each # of tree is not SAME!" << endl;
         return;
     }

     TVector3 MCMomentum_arr[num_MCfiletree];
     TVector3 KBMomentum_arr[num_KBfiletree];
     /// @MC Part
     TClonesArray *fMCTrack = new TClonesArray("KBMCTrack");
     TClonesArray *fMCStep40 = new TClonesArray("KBMCStep");
     TBranch *bMCTrack = (TBranch *)MCfiletree->GetBranch("MCTrack");
     TBranch *bMCStep40 = (TBranch *)MCfiletree->GetBranch("MCStep40");

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

                 MCTrack_px[iMCTree] = MCMomentum.X();
                 MCTrack_py[iMCTree] = MCMomentum.Y();
                 MCTrack_pz[iMCTree] = MCMomentum.Z();
             }
         }

         /// @MCStep
         int num_MCStep40 = fMCStep40->GetEntriesFast();

                 vector<double> MCStep_x[num_MCStep40];
                 vector<double> MCStep_y[num_MCStep40];
                 vector<double> MCStep_z[num_MCStep40];

                 for (int iStep40 = 0; iStep40 < num_MCStep40; iStep40++)
                 {
                     auto MCStep40 = (KBMCStep *)fMCStep40->At(iStep40);
                     int MCStep40_Mid = MCStep40->GetModuleID();

                     MCStep_x[MCStep40_Mid].push_back(MCStep40->GetX());
                     MCStep_y[MCStep40_Mid].push_back(MCStep40->GetY());
                     MCStep_z[MCStep40_Mid].push_back(MCStep40->GetZ());
                 }
         */
    // }
    /*
        /// @Result Part
        TClonesArray *fKBTrack = new TClonesArray("KBHelixTrack");
        TClonesArray *fFTHit = new TClonesArray("FTHit");

        TBranch *bKBTrack = (TBranch *)KBfiletree->GetBranch("Tracklet");
        TBranch *bFTHit = (TBranch *)KBfiletree->GetBranch("FTHit");

        bKBTrack->SetAddress(&fKBTrack);
        bFTHit->SetAddress(&fFTHit);

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
                KBTrack_px[iKBTree] = KBMomentum.X();
                KBTrack_py[iKBTree] = KBMomentum.Y();
                KBTrack_pz[iKBTree] = KBMomentum.Z();
            }
        }

        /// @Find resolution

        /// @Momentum
        TH1D *h1 = new TH1D("h1", "h1", 100, -1.1, 1.1);
        TH1D *h2 = new TH1D("h2", "h2", 100, -1.5, 1.5);
        TH1D *h3 = new TH1D("h3", "h3", 100, -1.5, 1.5);
        TCanvas *c1 = new TCanvas("c1","c1",800,600);
            gPad->SetGrid();
        gStyle->SetOptStat(0);
        for (int i = 0; i < num_KBfiletree; i++)
        {
            double dot_result = MCMomentum_arr[i].Dot(KBMomentum_arr[i]);
            if (dot_result > 0.9)
            {
                cout << i << endl;
            }
            h1->Fill(dot_result);
            h2->Fill(MCMomentum_arr[i].Y());
            h3->Fill(KBMomentum_arr[i].Y());
        }
        h1->SetTitle(" ");
        h1->GetXaxis()->SetTitle("cos#theta");
        h1->GetYaxis()->SetTitle("count");
        h1->Draw();
        */
}