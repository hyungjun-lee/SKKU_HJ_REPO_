#include "KBFTDetector.hh"
#include "KBFTPseudoPad.hh"

KBFTDetector::KBFTDetector()
:KBTpc("FT","Foward detector")
{
}

bool KBFTDetector::Init()
{
	BuildDetectorPlane();
	return true;
}

bool KBFTDetector::BuildDetectorPlane()
{
	KBPadPlane *padplane = nullptr;

	padplane = new KBFTPseudoPad();
	padplane -> SetParameterContainer(fPar);
//  	padplane -> SetPlaneID(0);
//	padplane -> SetPlaneK(fPar -> GetParDouble("TPCPadPlaneK0"));
  	padplane -> SetAxis(KBVector3::kX, KBVector3::kY);
	padplane -> Init();

	AddPlane(padplane);

	return true;
	

}
