void Draw_ZT(int eventnum = 0)
{
    TFile *filename = new TFile("out_g4event_LH.conv.eb7a905.L4.root", "READ");
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
    vector<double> FTHit_z[num_events];
    vector<double> FTHit_t[num_events];

    filetree->GetEntry(eventnum);

    auto track_graph = new TGraph();
    auto graphLongTraj = new TGraph();
    
    
    /// @histogram
    auto c1 = new TCanvas("c1", "c1", 1000, 1000);
    auto hist_hit = new TH2D("hist_hit", "hist_hit", 100, 0, 1600, 100, -500, 500);

    /// @track
    int num_tracklet = fTracklet->GetEntriesFast();
    for (int iTrack = 0; iTrack < num_tracklet; iTrack++)
    {
        auto track = (KBHelixTrack *)fTracklet->At(iTrack);
        track->Fit();
        track_graph = track->TrajectoryOnPlane(KBVector3::kZ, KBVector3::kY);

        for (auto i = -0.5; i < 1.5; i += 0.01)
        {
            auto point = track->ExtrapolateByRatio(i);
            graphLongTraj->SetPoint(graphLongTraj->GetN(), point.Z(), point.Y());
        }
    }

    /// @hit
    int num_hit = fFTHit->GetEntriesFast();
    for (int iHit = 0; iHit < num_hit; iHit++)
    {
        auto hit = (FTHit *)fFTHit->At(iHit);
        FTHit_x[0].push_back(hit->GetX());
        FTHit_y[0].push_back(hit->GetY());
        FTHit_z[0].push_back(hit->GetZ());
    }

    /// @Fill histogram
    for (int iHit = 0; iHit < num_hit; iHit++)
    {

        // FTHit_t[0].push_back(sqrt(FTHit_x[0].at(iHit) * FTHit_x[0].at(iHit) + FTHit_y[0].at(iHit) * FTHit_y[0].at(iHit)));
        FTHit_t[0].push_back(FTHit_y[0].at(iHit));
        hist_hit->Fill(FTHit_z[0].at(iHit), FTHit_t[0].at(iHit));
    }
    gStyle->SetOptStat(0);
    gPad->SetGrid();
    track_graph->SetLineWidth(4);
    hist_hit->GetXaxis()->SetLabelSize(0.02);
    hist_hit->GetYaxis()->SetLabelSize(0.02);
    graphLongTraj->SetLineWidth(10);
    graphLongTraj->SetFillColorAlpha(kGray,0.6);
    hist_hit->SetMarkerStyle(21);
    hist_hit->SetMarkerColor(4);
    hist_hit->Draw("LC");
    track_graph->Draw("same");
    graphLongTraj->Draw("samef");

    hist_hit->SetTitle("Track Fit view of side");
    hist_hit->GetXaxis()->SetTitle("z[mm]");
    hist_hit->GetYaxis()->SetTitle("y[mm]");
    
    TLegend * l1 = new TLegend(0.75,0.75,0.87,0.87);
    l1->AddEntry("graphLongTraj","fit track extrapolate","bl");
    l1->AddEntry("track_graph","fit track","bl");
    l1->AddEntry("hist_hit","FT hit","pb");
    l1->Draw();
}