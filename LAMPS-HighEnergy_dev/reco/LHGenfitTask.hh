#ifndef LHGENFITTASK_HH
#define LHGENFITTASK_HH

#include "KBTask.hh"
#include "KBHelixTrack.hh"
#include "KBHit.hh"
#include "KBVertex.hh"
#include "KBHitArray.hh"

#include "TClonesArray.h"

#include "LHSpacepointMeasurement.hh"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/fitters/include/AbsKalmanFitter.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/core/include/Track.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/trackReps/include/RKTrackRep.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/core/include/MeasurementFactory.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/core/include/MeasurementProducer.h"
#include "/Users/ihyeongjun/LAMPS/GenFit/GenFit_src/GFRave/include/GFRaveVertexFactory.h"

class LHGenfitTask : public KBTask
{ 
  public:
    LHGenfitTask();
    virtual ~LHGenfitTask() {}

    bool Init();
    void Exec(Option_t*);

    genfit::Track* FitTrack(KBHelixTrack *helixTrack, Int_t pdg);

		void SetDetID(int detID){ fDetectorID = detID; }

  private:
    TClonesArray* fTrackArray = nullptr;
		TClonesArray* fVertexArray = nullptr;

    TClonesArray *fGFTrackHitClusterArray;
    TClonesArray *fGenfitTrackArray;

		KBHitArray *fTrackHits = nullptr;

    Int_t fDetectorID = 0;

    genfit::AbsKalmanFitter *fKalmanFitter;
    genfit::MeasurementProducer<KBHit, genfit::LHSpacepointMeasurement> *fMeasurementProducer;
    genfit::MeasurementFactory<genfit::AbsMeasurement> *fMeasurementFactory;
    genfit::SharedPlanePtr fTargetPlane;

    // FitTrack output
    genfit::RKTrackRep *fCurrentTrackRep;
    genfit::FitStatus *fCurrentFitStatus;
    genfit::MeasuredStateOnPlane fCurrentFitState;
    TVector3 fCurrentMomTargetPlane;
    TVector3 fCurrentPosTargetPlane;

		genfit::GFRaveVertexFactory* fVertexFinder;

		bool fPersistency = true;

  ClassDef(LHGenfitTask, 1)
};

#endif
