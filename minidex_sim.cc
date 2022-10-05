#include <string>
#include <sstream>
#include <unistd.h>

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>
#include <G4VisExecutive.hh>

#include "HPGeDetectorConstruction.hh"
//#include "HPGePhysicsList.hh"
#include "HPGePrimaryGeneratorAction.hh"
#include "HPGeAnalysisManager.hh"
#include "HPGeStackingAction.hh"
#include "HPGeSteppingAction.hh"
#include "HPGeRunAction.hh"
#include "HPGeEventAction.hh"
#include "HPGeTrackingAction.hh"
#include <Shielding.hh>

#include <globals.hh>
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include "time.h"

void usage();

int
main(int argc, char **argv)
{
    std::cout<<" start "<<std::endl;

// random seeds
     //choose the Random engine
     CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
     //set random seed with system time
     G4long seed = time(NULL);
     CLHEP::HepRandom::setTheSeed(seed);

	// switches
	int c = 0;

	std::stringstream hStream;
	
	bool bInteractive = false;
	bool bVisualize = false;
	bool bVrmlVisualize = false;
	bool bOpenGlVisualize = false;

	bool bMacroFile = false;
	std::string hMacroFilename, hDataFilename;
	int iNbEventsToSimulate = 0;

	// parse switches
	while((c = getopt(argc,argv,"v:f:o:n:i")) != -1)
	{
		switch(c)
		{
			case 'v':
				bVisualize = true;
				hStream.str(optarg);
				if(hStream.str() == "vrml")
					bVrmlVisualize = true;
				else if(hStream.str() == "opengl")
					bOpenGlVisualize = true;
				hStream.clear();
				break;

			case 'f':
				bMacroFile = true;
				hMacroFilename = optarg;
				break;

			case 'o':
				hDataFilename = optarg;
				break;

			case 'n':
				hStream.str(optarg);
				hStream.clear();
				hStream >> iNbEventsToSimulate;
				break;

			case 'i':
				bInteractive = true;
				break;

			default:
				usage();
		}
	}

	// create the run manager
	G4RunManager *pRunManager = new G4RunManager;

	// set user-defined initialization classes
	pRunManager->SetUserInitialization(new HPGeDetectorConstruction);
//        pRunManager->SetUserInitialization(new Shielding);
    G4VModularPhysicsList* phys = new Shielding();
    pRunManager->SetUserInitialization(phys);
    G4double mydefaultCutValue  =       0.1*mm;
    phys->SetDefaultCutValue(mydefaultCutValue);
    phys->DumpCutValuesTable();

//	pRunManager->SetUserInitialization(new HPGePhysicsList);

	// create the primary generator action
	HPGePrimaryGeneratorAction *pPrimaryGeneratorAction = new HPGePrimaryGeneratorAction();

	// create an analysis manager object
	HPGeAnalysisManager *pAnalysisManager = new HPGeAnalysisManager(pPrimaryGeneratorAction);
	if(!hDataFilename.empty())
		pAnalysisManager->SetDataFilename(hDataFilename);
	if(iNbEventsToSimulate)
		pAnalysisManager->SetNbEventsToSimulate(iNbEventsToSimulate);

	// set user-defined action classes
	pRunManager->SetUserAction(pPrimaryGeneratorAction);
	pRunManager->SetUserAction(new HPGeStackingAction(pAnalysisManager));
	pRunManager->SetUserAction(new HPGeSteppingAction(pAnalysisManager));
	pRunManager->SetUserAction(new HPGeRunAction(pAnalysisManager));
	pRunManager->SetUserAction(new HPGeEventAction(pAnalysisManager));
	pRunManager->SetUserAction(new HPGeTrackingAction(pAnalysisManager));

	//pRunManager->Initialize();  // this is moved to macro, initialize must be done after GDML filename is set
	
	G4VisManager* pVisManager = new G4VisExecutive;
	pVisManager->Initialize();
	
	G4UImanager* pUImanager = G4UImanager::GetUIpointer();

	G4UIsession * pUIsession = 0;
	if(bInteractive)
	{
		pUIsession = new G4UIterminal(new G4UItcsh);
	}

	std::string hCommand;

	if(bVisualize)
	{
		pUImanager->ApplyCommand("/vis/scene/create");
		if(bVrmlVisualize)
			pUImanager->ApplyCommand("/vis/open VRML2FILE");
		if(bOpenGlVisualize)
			pUImanager->ApplyCommand("/vis/open OGLIX");
		pUImanager->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 0 0 deg");
		pUImanager->ApplyCommand("/vis/viewer/zoom 1.0");
		pUImanager->ApplyCommand("/tracking/storeTrajectory 1");
		pUImanager->ApplyCommand("/vis/scene/add/trajectories");
	}
	
	if(bMacroFile)
	{
		hCommand = "/control/execute " + hMacroFilename;
		pUImanager->ApplyCommand(hCommand);
	}

	
	if(iNbEventsToSimulate)
	{
		hStream.str("");
		hStream.clear();
		hStream << "/run/beamOn " << iNbEventsToSimulate;
		pUImanager->ApplyCommand(hStream.str());
	}

	if(bInteractive)
	{
		pUIsession->SessionStart();

		delete pUIsession;
	}


	delete pAnalysisManager;

	if(bVisualize)
		delete pVisManager;
	delete pRunManager;
	return 0;
}

void
usage()
{
	exit(0);
}
