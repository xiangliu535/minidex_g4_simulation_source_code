#ifndef __XENON10PEVENTACTION_H__
#define __XENON10PEVENTACTION_H__

#include <G4UserEventAction.hh>

#include "HPGeAnalysisManager.hh"

class G4Event;

class HPGeEventAction : public G4UserEventAction
{
public:
	HPGeEventAction(HPGeAnalysisManager *pAnalysisManager = 0);
	~HPGeEventAction();

public:
	void BeginOfEventAction(const G4Event *pEvent);
	void EndOfEventAction(const G4Event *pEvent);

private:
	HPGeAnalysisManager *m_pAnalysisManager;
};

#endif // __XENON10PEVENTACTION_H__

