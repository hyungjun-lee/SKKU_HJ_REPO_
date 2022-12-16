#include "FTHit.hh"

FTHit::FTHit()
{

}

FTHit::~FTHit()
{

}

void FTHit::SetFTHit(int _moduleID, float _reco_x, float _reco_y, float _reco_e)
{
	moduleID = _moduleID;
	reco_x = _reco_x;
	reco_y = _reco_y;
	reco_e = _reco_e;
}

void FTHit::SetHitArray(TClonesArray *arr)
{

	std::cout << "here! set hit array" << std::endl;
}

void FTHit::TestCallMe()
{
	std::cout << "call me" << std::endl;
}