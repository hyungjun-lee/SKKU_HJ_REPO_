
#pragma once
#include "KBTpcHit.hh"
#include "KBTask.hh"

class FTHit : public KBTpcHit //, public KBTask

{
	public :
		FTHit();
		virtual ~FTHit();
		void SetFTHit(int _moduleID, float _reco_x, float _reco_y, float _reco_e);

		void SetHitArray(TClonesArray *arr);
		void TestCallMe();

	private :
		int moduleID;
		float reco_x;
		float reco_y;
		float reco_e;

		TClonesArray * arr = nullptr;
};
