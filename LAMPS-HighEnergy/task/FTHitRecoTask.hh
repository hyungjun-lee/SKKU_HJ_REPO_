#include "KBTask.hh"
#include "TClonesArray.h"

#include <TH3D.h>

class FTHitRecoTask : public KBTask
{
public:
	FTHitRecoTask();
	virtual ~FTHitRecoTask();

	bool Init();
	void Exec(Option_t *);

	void SetPersistency(bool val);
	void SetDetID(int id);
	int SetLayerN(int _layerN);
	void SetRecoHist(int num, int bin_x, int min_x, int max_x, int bin_y, int min_y, int max_y, int bin_z, int min_z, int max_z);
	void SetLimitTimePos(int time, int pos);

	int GetLayerN();

private:
	TClonesArray *fMCStepArray;
	TClonesArray *fStepArray;
	TClonesArray *fFTHitArray;
	TClonesArray *fFTHit;

	TH3D *reco_3d[100];

	bool RECONSTRUCTION = false;
	bool RAWSTEP = true;

	bool fPersistency = true;
	int fDetID = 40;
	int layerN;
	int lim_time;
	int lim_pos;

	int count = 0;
};
