void Draw_XY_comp(int eventnum = 1)
{
    TFile *filename_mc = new TFile("out_g4event_LH.mc.root", "READ");
    TTree *filetree_mc = (TTree *)filename_mc->Get("event");

    TFile *filename_data = new TFile("out_g4event_LH.conv.eb7a905.root", "READ");
    TTree *filetree_data = (TTree *)filename_data->Get("event");

    TClonesArray *fMCHit = new TClonesArray("KBMCStep");
    TBranch *bMCHit = (TBranch *)filetree_mc->GetBranch("MCStep40");
    bMCHit->SetAddress(&fMCHit);

    TClonesArray *fTracklet = new TClonesArray("KBHelixTrack");
    TClonesArray *fFTHit = new TClonesArray("FTHit");
    TBranch *bTracklet = (TBranch *)filetree_data->GetBranch("Tracklet");
    TBranch *bFTHit = (TBranch *)filetree_data->GetBranch("FTHit");
    bTracklet->SetAddress(&fTracklet);
    bFTHit->SetAddress(&fFTHit);

    int num_events_data = filetree_data->GetEntriesFast();
    int num_events_mc = filetree_mc->GetEntriesFast();

    vector<double> FTHit_x[num_events_data];
    vector<double> FTHit_y[num_events_data];

    vector<double> MCHit_x[num_events_mc];
    vector<double> MCHit_y[num_events_mc];

    /// @histogram
    auto c1 = new TCanvas("c1", "c1", 1000, 1000);
    auto hist_hit = new TH2D("hist_hit", "hist_hit", 100, -500, 500, 100, -500, 500);
    auto hist_mc = new TH2D("hist_mc", "hist_mc", 100, -500, 500, 100, -500, 500);

    /// @hit
    filetree_data->GetEntry(eventnum);
    int num_hit_data = fFTHit->GetEntriesFast();
    for (int iHit = 0; iHit < num_hit_data; iHit++)
    {
        auto hit = (FTHit *)fFTHit->At(iHit);
        FTHit_x[0].push_back(hit->GetX());
        FTHit_y[0].push_back(hit->GetY());
    }

    /// @step
    filetree_mc->GetEntry(eventnum);
    int num_hit_mc = fMCHit->GetEntriesFast();
    for (int iStep = 0; iStep < num_hit_mc; iStep++)
    {
        auto step = (KBMCStep *)fMCHit->At(iStep);
        MCHit_x[0].push_back(step->GetX());
        MCHit_y[0].push_back(step->GetY());
    }

    /// @Fill histogram
    for (int iHit = 0; iHit < num_hit_data; iHit++)
    {
        hist_hit->Fill(FTHit_x[0].at(iHit), FTHit_y[0].at(iHit));
    }

    for (int iStep = 0; iStep < num_hit_mc; iStep++)
    {
        hist_mc->Fill(MCHit_x[0].at(iStep), MCHit_y[0].at(iStep));
    }

    c1->SetGrid();

    hist_hit->SetMarkerStyle(24);
    hist_hit->SetMarkerColor(4);
    
    hist_hit->SetTitle(Form("Run number : %d", eventnum));
    hist_hit->GetXaxis()->SetTitle("x[mm]");
    hist_hit->GetYaxis()->SetTitle("y[mm]");
    hist_hit->GetXaxis()->SetLabelSize(0.02);
    hist_hit->GetYaxis()->SetLabelSize(0.02);

    hist_mc->SetMarkerStyle(20);
    hist_mc->SetMarkerSize(0.5);
    hist_mc->SetMarkerColor(kRed);

    gStyle->SetOptStat(0);
    hist_hit->Draw("LCsame");
    hist_mc->Draw("LCsame");

    TLegend *l1 = new TLegend(0.75, 0.75, 0.87, 0.87);
    l1->AddEntry("hist_hit", "FT hit", "pb");
    l1->AddEntry("hist_mc", "MC step", "pb");
    l1->Draw();
}