#include <G4Event.hh>

#include "HPGeEventAction.hh"

HPGeEventAction::HPGeEventAction(HPGeAnalysisManager *pAnalysisManager)
{
	m_pAnalysisManager = pAnalysisManager;
}

HPGeEventAction::~HPGeEventAction()
{
}

void
HPGeEventAction::BeginOfEventAction(const G4Event *pEvent)
{
	if(pEvent->GetEventID() % 1000 == 0)
	{
		G4cout << G4endl;
		G4cout << "------ Begin event " << pEvent->GetEventID()
			<< "------" << G4endl;
	}
	
	if(m_pAnalysisManager)
		m_pAnalysisManager->BeginOfEvent(pEvent);
}

void HPGeEventAction::EndOfEventAction(const G4Event *pEvent)
{
	if(m_pAnalysisManager)
		m_pAnalysisManager->EndOfEvent(pEvent);
}


