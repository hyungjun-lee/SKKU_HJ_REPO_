#include "KBPadPlane.hh"
#include "KBTpcHit.hh"
#include "TF1.h"
#include "KBFTPseudoPad.hh"

#include "TMath.h"
#include "TCollection.h"
#include "TLine.h"


using namespace std;
using namespace TMath;

KBFTPseudoPad::KBFTPseudoPad()
:KBPadPlane("FTPseudoPlane","FT-PseudoPlane")
{
}

void KBFTPseudoPad::SetHitArray(TClonesArray *hitArray)
{
  Int_t numHits = hitArray -> GetEntries();
  for (auto iHit = 0; iHit < numHits; ++iHit)
  {
    auto hit = (KBHit *) hitArray -> At(iHit);
    std::cout << "hit make : " << hit->GetX() << "\t" << hit->GetY() << "\t" << hit->GetZ() << std::endl;
  
  }
}

bool KBFTPseudoPad::Init()
{
	
	TObjArray *fInPadArray = new TObjArray();
	
	int padID = 0;

	auto fAxis = fPar -> GetParAxis("LHTF_refAxis");
	
	int layerN = 3;
	int row = 10;
	int column = 10;


//이부분은 다시 살려야함.
	//Double_t FTXsize = fPar -> GetParDouble("FTLayerD");
	//Double_t FTYsize = fPar -> GetParDouble("FTLayerD");

	//auto fPadWidth = FTXsize/row;
	//auto fPadHeight = FTYsize/column;


	for(Int_t i = 0; i < layerN; i++)
	{
		Double_t pos_z = 950 + 50 * i;

		for(Int_t j = 0; j < row; j++)
		{
			for(Int_t k = 0; k < column; k++)
			{
				KBPad * pad = new KBPad();
				//이부분 수정
				Double_t pos_x = j;
				Double_t pos_y = k;
				//
				KBVector3 posPad(fAxis,pos_x,pos_y,pos_z);
				
				pad -> SetPosition(posPad);
				pad -> SetPadID(padID);
				padID++;
				fChannelArray -> Add(pad);
			}
		}
			
	}
	

	return true;
}
