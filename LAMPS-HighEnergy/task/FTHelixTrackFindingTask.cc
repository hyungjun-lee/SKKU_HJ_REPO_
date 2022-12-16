#include "KBRun.hh"
#include "FTHelixTrackFindingTask.hh"

#include <iostream>

ClassImp(FTHelixTrackFindingTask)

    bool FTHelixTrackFindingTask::Init()
{
    auto run = KBRun::GetRun();
    fHitArray = (TClonesArray *)run->GetBranch(fBranchNameHit);

    fTrackArray = new TClonesArray("KBHelixTrack");
    run->RegisterBranch(fBranchNameTracklet, fTrackArray, fPersistency);

    fTrackHits = new KBHitArray();
    fGoodHits = new KBHitArray();

    run->RegisterBranch("TrackHit", fTrackHits, false);
    run->RegisterBranch("GoodHit", fGoodHits, false);

    fNextStep = StepNo::kStepInitArray;

    int EventCounter = 0;

    fReferenceAxis = fPar->GetParAxis("LHTF_refAxis");

    return true;
}

void FTHelixTrackFindingTask::Exec(Option_t *)
{
    fNextStep = StepNo::kStepInitArray;
    while (ExecStep())
    {
    }
}

bool FTHelixTrackFindingTask::ExecStep()
{
    if (fNextStep == kStepEndOfEvent)
        return false;
    else if (fNextStep == kStepInitArray)
        fNextStep = StepInitArray();
    else if (fNextStep == kStepNewTrack)
        fNextStep = StepNewTrack();

    return true;
}

int FTHelixTrackFindingTask::StepInitArray()
{
    fCurrentTrack = nullptr;
    fPhaseIndex = 0;

    fTrackArray->Clear("C");
    fGoodHits->Clear();

    return kStepNewTrack;
}

int FTHelixTrackFindingTask::StepNewTrack()
{
    fTrackHits->Clear();
    fGoodHits->Clear();

    Int_t idx = fTrackArray->GetEntries();

    fCurrentTrack = new ((*fTrackArray)[idx]) KBHelixTrack(idx);
    fCurrentTrack->SetReferenceAxis(fReferenceAxis);

    for (int inum = 0; inum < fHitArray->GetEntries(); inum++)
    {
        KBHit *hit = (KBHit *)fHitArray->At(inum);

        fCurrentTrack->AddHit(hit);
        fGoodHits->AddHit(hit);
    }
    fCurrentTrack->Fit();
    return kStepEndOfEvent;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
