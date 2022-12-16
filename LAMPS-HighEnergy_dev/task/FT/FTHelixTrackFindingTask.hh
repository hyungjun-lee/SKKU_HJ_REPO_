#ifndef FTHELIXTRACKFINDINGTASK_HH
#define FTHELIXTRACKFINDINGTASK_HH 
#endif


#pragma once
#include "TClonesArray.h"
#include "TGraphErrors.h"

#include "KBTask.hh"
#include "KBHelixTrack.hh"
#include "KBTpcHit.hh"
#include "KBHitArray.hh"

#include "LHTpc.hh"
#include "KBPadPlane.hh"

#include "FTHit.hh"
#include <vector>
using namespace std;

class FTHelixTrackFindingTask : public KBTask
{
    public :
        FTHelixTrackFindingTask() : KBTask("FTHelixTrackFindingTask","FTHelixTrackFindingTask") {}
        virtual ~FTHelixTrackFindingTask() {}

        virtual bool Init();
        virtual void Exec(Option_t *);

        void SetTrackPersistency(bool val) { fPersistency = val; }

        enum StepNo : int {
            kStepInitArray,
            kStepNewTrack,
            kStepEndOfEvent,
        };

        bool ExecStep();

        void SetHitBranchName(TString name) { fBranchNameHit = name; }
        void SetTrackletBranchName(TString name) { fBranchNameTracklet = name; }

        void UpCount() { cnt++; }
        int GetCount() { return cnt; }

        void SetNum(int val_) { val = val_; }
        int GetNum() { return val; }

    private :
        int StepInitArray();        
        int StepNewTrack();
        int StepEndEvent();

        int cnt = 0;
        int val = -999;

        TClonesArray * fHitArray = nullptr;
        TClonesArray * fTrackArray = nullptr;

        TClonesArray * fClonesArray = nullptr;
        KBHit * fHits = nullptr;

        TString fBranchNameHit = "Hit";
        TString fBranchNameTracklet = "Tracklet";

        bool fPersistency = true;

        KBHitArray * fTrackHits = nullptr;
        KBHitArray * fGoodHits = nullptr;

        KBVector3::Axis fReferenceAxis;

        Int_t fPhaseIndex = 0;

        KBHelixTrack * fCurrentTrack = nullptr;

        Int_t fNextStep = StepNo::kStepInitArray;
        Int_t fNumGoodHits;

        //ClassDef(KBHelixTrackFindingTask, 1)       
};