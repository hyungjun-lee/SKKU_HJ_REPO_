#include "FTHitRecoTask.hh"
#include "FTHit.hh"
#include "KBRun.hh"

#include <vector>
#include <iostream>
#include <TH3D.h>
using namespace std;

FTHitRecoTask::FTHitRecoTask()
	: KBTask("FTHitRecoTask", "")
{
}

FTHitRecoTask::~FTHitRecoTask()
{
}

bool FTHitRecoTask::Init()
{
	KBRun *run = KBRun::GetRun();

	fMCStepArray = (TClonesArray *)run->GetBranch(Form("MCStep%d", fDetID));
	fStepArray = new TClonesArray("KBMCStep");
	run->RegisterBranch("FTStep", fStepArray, fPersistency);

	fFTHitArray = new TClonesArray("FTHit");
	run->RegisterBranch("FTHit", fFTHitArray, fPersistency);

	kb_info << " # of FT Layers : " << layerN << endl;

	return true;
}

void FTHitRecoTask::Exec(Option_t *)
{
	fStepArray->Clear();
	fFTHitArray->Clear();
	Long64_t nMCSteps = fMCStepArray->GetEntries();

	kb_info << " Number of found steps in FT : " << nMCSteps << endl;
	vector<double> RecoCandHit[nMCSteps];
	vector<int> countI;
	for (Long64_t iStep = 0; iStep < nMCSteps; iStep++)
	{

		KBMCStep *step = (KBMCStep *)fMCStepArray->At(iStep);
		double FT_step_x = step->GetX();
		double FT_step_y = step->GetY();
		double FT_step_z = step->GetZ();
		double FT_step_edep = step->GetEdep();
		double FT_step_time = step->GetTime();
		int FT_step_moduleID = step->GetModuleID();
		double FT_step_trackID = step->GetTrackID();
		double FT_step_copyNo = step->GetcopyNo();

		auto SingleStep = (KBMCStep *)fStepArray->ConstructedAt(iStep);
//		KBMCStep *SingleStep = new ((*fStepArray)[iStep]) KBMCStep();

		SingleStep->SetMCStep(FT_step_trackID, FT_step_moduleID, FT_step_x, FT_step_y, FT_step_z, FT_step_time, FT_step_edep);
		
		if(FT_step_trackID != 1)
		{
			continue;
		}	
		
		if (RAWSTEP)
		{
			auto SingleHit = (FTHit *)fFTHitArray->ConstructedAt(iStep);
			SingleHit->SetX(FT_step_x);
			SingleHit->SetY(FT_step_y);
			SingleHit->SetZ(FT_step_z);
			SingleHit->SetHitID(iStep * 10);
			SingleHit->SetCharge(1);
			SingleHit->SetTrackID(FT_step_trackID);

		}
	}

/*
		double data[5] = {FT_step_time, FT_step_x, FT_step_y, FT_step_edep, FT_step_copyNo};
		for (auto digit : data)
		{
			RecoCandHit[iStep].push_back(digit);
		}

		reco_3d[FT_step_moduleID]->Fill(FT_step_time, FT_step_x, FT_step_y, FT_step_edep);

	for (int i = 0; i < nMCSteps; i++)
	{
		for (int j = 0; j < nMCSteps; j++)
		{
			if (RecoCandHit[i][4] < RecoCandHit[j][4])
			{
				vector<double> temp;
				temp = RecoCandHit[i];
				RecoCandHit[i] = RecoCandHit[j];
				RecoCandHit[j] = temp;
			}
		}
	}

	for (int i = RecoCandHit[0][4]; i <= RecoCandHit[nMCSteps - 1][4]; i++)
	{
		countI.push_back(i);
	}

	// FT step moduleID = layerN, in this case.
	if (RECONSTRUCTION)
	{
		kb_info << "FTHit reconstruction start" << endl;
		for (int i = 0; i < nMCSteps; i++)
		{
			// auto SingleHit = (FTHit*) fFTHitArray -> ConstructedAt(count);

			while (reco_3d[i]->Integral() > 0)
			{
				int binnum_t, binnum_x, binnum_y, binnum_e;
				float reco_t = 0, reco_x = 0, reco_y = 0, reco_e = 0;
				int maxbin = reco_3d[i]->GetMaximumBin();

				reco_3d[i]->GetBinXYZ(maxbin, binnum_t, binnum_x, binnum_y);

				for (int it = 0; it < lim_time * 2; it++)
				{
					int temp_t = binnum_t - lim_time + it;
					for (int ix = 0; ix < lim_pos * 2; ix++)
					{
						for (int iy = 0; iy < lim_pos * 2; iy++)
						{
							int temp_x = binnum_x - lim_pos + ix;
							int temp_y = binnum_y - lim_pos + iy;
							reco_e += (reco_3d[i]->GetBinContent(temp_t, temp_x, temp_y));
							reco_x += (reco_3d[i]->GetBinContent(temp_t, temp_x, temp_y)) * (reco_3d[i]->GetYaxis()->GetBinCenter(temp_x));
							reco_y += (reco_3d[i]->GetBinContent(temp_t, temp_x, temp_y)) * (reco_3d[i]->GetZaxis()->GetBinCenter(temp_y));

							reco_3d[i]->SetBinContent(temp_t, temp_x, temp_y, 0.0);
						}
					}
				}

				reco_x /= reco_e;
				reco_y /= reco_e;

				FTHit *SingleHit = new ((*fFTHitArray)[count]) FTHit();
				SingleHit->SetX(reco_x);
				SingleHit->SetY(reco_y);
				SingleHit->SetZ(950 + i * 50);
				SingleHit->SetHitID(i * 10);
				SingleHit->SetCharge(1);

				// SingleHit -> SetPadID(50000+i*10);
				SingleHit->SetPadID(i * 10);

				count++;

				kb_info << "Reco X : " << setw(8) << reco_x << setw(10)
						<< "(mm)|   Reco Y : " << setw(8) << reco_y << setw(10)
						<< "(mm)|	Reco E : " << setw(8) << reco_e << setw(12)
						<< "(MeV)|	Rest.. : " << setw(8) << reco_3d[i]->Integral() << setw(12)
						<< "(MeV)| Layer : " << setw(3) << i + 1 << " / " << layerN << endl;
			}
		}
	}
	*/
}

void FTHitRecoTask::SetPersistency(bool val)
{
	fPersistency = val;
}

void FTHitRecoTask::SetDetID(int id)
{
	fDetID = id;
}

int FTHitRecoTask::SetLayerN(int _layerN)
{
	layerN = _layerN;
	return layerN;
}

int FTHitRecoTask::GetLayerN()
{
	return layerN;
}

void FTHitRecoTask::SetRecoHist(int num, int bin_x, int min_x, int max_x, int bin_y, int min_y, int max_y, int bin_z, int min_z, int max_z)
{
	kb_info << " hit reconstruction histogram initailized ... " << endl;

	for (int i = 0; i < num; i++)
	{
		reco_3d[i] = new TH3D(Form("reco hist_%d", i), Form("reco hist n_%d t:x:y", i), bin_x, min_x, max_x, bin_y, min_y, max_y, bin_z, min_z, max_z);
	}
}

void FTHitRecoTask::SetLimitTimePos(int time, int pos)
{
	lim_time = time;
	lim_pos = pos;
}
