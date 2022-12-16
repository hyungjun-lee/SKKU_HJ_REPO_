//#ifdef KBFTPSEUDOPAD_HH
//#define KBFTPSEUDOPAD_HH

#include "KBPadPlane.hh"
#include "KBTpcHit.hh"
#include "TF1.h"
#include "KBRun.hh"
#include "KBParameterContainer.hh"

typedef vector<KBHit*> KBTPCHits;

class KBFTPseudoPad : public KBPadPlane 
{
	public :
		KBFTPseudoPad();
		virtual ~KBFTPseudoPad() {}

		virtual bool Init();
		virtual bool IsInBoundary(Double_t i, Double_t j){};
	    	virtual TH2* GetHist(Option_t *option = "-1"){};
    		virtual Int_t FindPadID(Double_t i, Double_t j){};
		virtual Int_t FindPadID(Int_t section, Int_t row, Int_t layer){};
		virtual Double_t PadDisplacement() const {};

		void SetHitArray(TClonesArray * hitarray);

	private :
		

};

//#endif
