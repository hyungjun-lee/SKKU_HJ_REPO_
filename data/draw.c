void draw()
{
  auto file = new TFile("out_g4event_LH.conv.eb7a905.root");
  auto tree = (TTree *)file->Get("event");

  TClonesArray *hitArray = nullptr;
  tree->SetBranchAddress("TPCHit", &hitArray);

  int num_tree = tree->GetEntriesFast();

  for (int i = 0; i < num_tree; i++)
  {
    tree->GetEntry(i);
    auto numHits = hitArray->GetEntries();
    auto kbHitArray = new KBHitArray();
    cout << numHits << endl;
    for (auto iHit = 0; iHit < numHits; ++iHit)
    {
      auto hit = (KBTpcHit *)hitArray->At(iHit);
      kbHitArray->AddHit(hit);
    }

    kbHitArray->FitHelix();
    // kbHitArray -> Print();
    kbHitArray -> DrawFitCircle();
  }
}
