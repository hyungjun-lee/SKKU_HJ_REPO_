
int run_g4sim(const char *name = "LH");

void run_FT2(const char *name = "g4event")
{

	const bool bG4SIM = false;
	const bool bDIGI = true;
	const bool bRECO = true;
	const bool TPCDet = true;
	const bool FTDet = false;
	
	if (bG4SIM)
	{
		if (!run_g4sim(name))
			return;
	}

	if (bDIGI || bRECO)
	{
		auto run = KBRun::GetRun();
		// run->SetIOFile(Form("./data/%s.mc",name), Form("./data/%s.reco",name));
		run->SetIOFile(Form("out_%s_LH.mc", name), Form("out_%s_LH.conv", name));
		run->AddDetector(new LHTpc());
		run->AddDetector(new KBFTDetector()); //
		// run->SetParameterContainer("kbpar_LH.conf");
		// run->AddParameterContainer("input/kbpar_sim.conf");

		auto fPar = new KBParameterContainer("kbpar_LH.conf");
		int LayerN = fPar->GetParInt("FTLayerN");

		if (bDIGI)
		{
			auto drift = new LHDriftElectronTask();
			drift->SetPadPersistency(true);
			drift->SetDetID(10); // TPC
			run->Add(drift);

			auto electronics = new LHElectronicsTask(true);
			run->Add(electronics);
		}

		if (bDIGI && bRECO)
		{

			auto psa = new KBPSATask();
			psa->SetInputBranchName("TPCPad");
			psa->SetOutputBranchName("TPCHit");
			// psa -> SetHitPersistency(fal);
			psa->SetPSA(new KBPSAFastFit());
			run->Add(psa);
			
			auto fthit = new FTHit();
			auto ftreco = new FTHitRecoTask();
			ftreco->SetDetID(40);
			ftreco->SetLayerN(LayerN);
			ftreco->SetRecoHist(ftreco->GetLayerN(), 200, 0, 200, 1000, -500, 500, 1000, -500, 500);
			ftreco->SetLimitTimePos(3, 50);
			run->Add(ftreco);

			if (TPCDet)
			{
				auto htfTask = new LHHelixTrackFindingTask();
				htfTask->SetHitBranchName("TPCHit");
				htfTask->SetHitBranchName_FT("FTHit"); //
				htfTask->SetTrackletBranchName("Tracklet");
				run->Add(htfTask);
			}

			if (FTDet)
			{
				auto htfTask = new FTHelixTrackFindingTask();
				htfTask->SetHitBranchName("FTHit");
				htfTask->SetTrackletBranchName("Tracklet");
				run->Add(htfTask);
			}

			/// auto gfTask = new LHGenfitTask();

			/// gfTask->SetDetID(10); //TPC
			/// gfTask->SetDetID(40); //FT

			//	run->Add(gfTask);
			//	run->Add(new LHNDFastDigiTask()); //필요한건가..? 에러생겨;;
			//	run->Add(new LHVertexFindingTask());
		}

		run->Init();
		run->Print();
		run->Run();
	//	run->RunSingle(1);
	}
}

int run_g4sim(const char *name = "LH")
{

	TString fname = Form("kbpar_%s.conf", name);
	gSystem->FindFile("./", fname);

	if (fname.Length() == 0)
	{
		cout << "Can not find the macrofile" << endl;
		return 0;
	}
	else
	{
		fname = Form("kbpar_%s.conf", name);
		gSystem->Exec(Form("./run_mc.g4sim %s", fname.Data()));
	}

	return 1;
}
