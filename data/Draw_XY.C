void Draw_XY(int eventnum = 1)
{
    TFile *filename = new TFile("out_g4event_LH.conv.eb7a905.L10.TPC.root", "READ");
    TTree *filetree = (TTree *)filename->Get("event");

    TClonesArray *fTracklet = new TClonesArray("KBHelixTrack");
    TClonesArray *fFTHit = new TClonesArray("FTHit");
    TBranch *bTracklet = (TBranch *)filetree->GetBranch("Tracklet");
    TBranch *bFTHit = (TBranch *)filetree->GetBranch("FTHit");
    bTracklet->SetAddress(&fTracklet);
    bFTHit->SetAddress(&fFTHit);

    int num_events = filetree->GetEntriesFast();

    vector<double> FTHit_x[num_events];
    vector<double> FTHit_y[num_events];

    double FitTrack_x[num_events];
    double FitTrack_y[num_events];
    double FitTrack_r[num_events];

    filetree->GetEntry(eventnum);

    /// @histogram
    auto c1 = new TCanvas("c1", "c1", 1000, 1000);
    auto hist_fitcenter = new TH2D("hist_fitcenter", "hist_fitcenter", 1000, -500, 500, 1000, -500, 500);
    auto hist_fitcircle = new TH2D("hist_fitcircle", "hist_fitcircle", 1000, -500, 500, 1000, -500, 500);
    auto hist_hit = new TH2D("hist_hit", "hist_hit", 100, -500, 500, 100, -500, 500);

    /// @track
    int num_tracklet = fTracklet->GetEntriesFast();
    for (int iTrack = 0; iTrack < num_tracklet; iTrack++)
    {
        auto track = (KBHelixTrack *)fTracklet->At(iTrack);
        FitTrack_x[0] = track->GetHelixCenterI();
        FitTrack_y[0] = track->GetHelixCenterJ();
        FitTrack_r[0] = track->GetHelixRadius();
    
    }

    /// @hit
    int num_hit = fFTHit->GetEntriesFast();
    for (int iHit = 0; iHit < num_hit; iHit++)
    {
        auto hit = (FTHit *)fFTHit->At(iHit);
        FTHit_x[0].push_back(hit->GetX());
        FTHit_y[0].push_back(hit->GetY());
    }

    /// @Fill histogram
    hist_fitcenter->Fill(FitTrack_x[0], FitTrack_y[0]);
    for (int iCount = 0; iCount < 3600; iCount++)
    {
        auto rx = FitTrack_x[0] + FitTrack_r[0] * TMath::Cos(iCount * TMath::Pi() / 1800);
        auto ry = FitTrack_y[0] + FitTrack_r[0] * TMath::Sin(iCount * TMath::Pi() / 1800);
        hist_fitcircle->Fill(rx, ry);
    }

    for (int iHit = 0; iHit < num_hit; iHit++)
    {
        hist_hit->Fill(FTHit_x[0].at(iHit), FTHit_y[0].at(iHit));
    }

    c1->SetGrid();

    hist_fitcenter->SetMarkerStyle(3);
    hist_fitcenter->SetMarkerColor(2);
    hist_fitcenter->SetMarkerSize(2);
    hist_fitcenter->GetXaxis()->SetTitle("x[mm]");
    hist_fitcenter->GetYaxis()->SetTitle("y[mm]");
    hist_fitcenter->SetTitle("Track Fit view of forward");

    hist_fitcircle->SetMarkerStyle(7);
    hist_fitcircle->SetMarkerSize(0.5);
    hist_fitcircle->SetMarkerColor(kGray);
    hist_fitcenter->GetXaxis()->SetLabelSize(0.02);
    hist_fitcenter->GetYaxis()->SetLabelSize(0.02);
    hist_hit->SetMarkerStyle(21);
    hist_hit->SetMarkerColor(4);

    gStyle->SetOptStat(0);
    hist_fitcenter->Draw("P");
    hist_fitcircle->Draw("LCsame");
    hist_hit->Draw("LCsame");

    TLegend * l1 = new TLegend(0.75,0.75,0.87,0.87);
    l1->AddEntry("hist_fitcenter","fit center","pb");
    l1->AddEntry("hist_fitcircle","fit circle","pbl");
    l1->AddEntry("hist_hit","FT hit","pb");
    l1->Draw();
}