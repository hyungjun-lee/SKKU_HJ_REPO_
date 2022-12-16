//#ifdef KBFTDETECTOR_HH
//#define KBFTDETECTOR_HH


#include "KBTpc.hh"

class KBFTDetector : public KBTpc
{
	public :
		KBFTDetector();
		virtual ~KBFTDetector() {};

		virtual bool Init();
		
	private : 
		virtual bool BuildDetectorPlane();
		virtual bool BuildGeometry() {};
		virtual KBVector3::Axis GetEFieldAxis() {};
		virtual TVector3 GetEField(TVector3 pos) {};
		virtual KBPadPlane *GetDriftPlane(TVector3 pos) {};


};

//#endif
