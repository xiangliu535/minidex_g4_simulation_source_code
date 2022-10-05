#include <Randomize.hh>

#include <sys/time.h>

#include "HPGeAnalysisManager.hh"

#include "HPGeRunAction.hh"

HPGeRunAction::HPGeRunAction(HPGeAnalysisManager *pAnalysisManager)
{
	m_pAnalysisManager = pAnalysisManager;
}

HPGeRunAction::~HPGeRunAction()
{

}

void
HPGeRunAction::BeginOfRunAction(const G4Run *pRun)
{
	if(m_pAnalysisManager)
		m_pAnalysisManager->BeginOfRun(pRun);

     // automatic (time-based) random seeds for each run
         G4cout << "*******************" << G4endl;
         G4cout << "*** AUTOSEED ON ***" << G4endl;
         G4cout << "*******************" << G4endl;
         long seeds[2];
         time_t systime = time(NULL);
         seeds[0] = (long) systime;
         seeds[1] = (long) (systime*G4UniformRand());
         G4Random::setTheSeeds(seeds);
         G4Random::showEngineStatus();

/*
	struct timeval hTimeValue;
	gettimeofday(&hTimeValue, NULL);

	CLHEP::HepRandom::setTheEngine(new CLHEP::DRand48Engine);
	CLHEP::HepRandom::setTheSeed(hTimeValue.tv_usec);
*/
}

void
HPGeRunAction::EndOfRunAction(const G4Run *pRun)
{
	if(m_pAnalysisManager)
		m_pAnalysisManager->EndOfRun(pRun);
}

