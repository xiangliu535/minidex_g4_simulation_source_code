#ifndef __XENON10PRUNACTION_H__
#define __XENON10PRUNACTION_H__

#include <G4UserRunAction.hh>

class G4Run;

class HPGeAnalysisManager;

class HPGeRunAction: public G4UserRunAction
{
public:
	HPGeRunAction(HPGeAnalysisManager *pAnalysisManager=0);
	~HPGeRunAction();

public:
	void BeginOfRunAction(const G4Run *pRun);
	void EndOfRunAction(const G4Run *pRun);

private:
	HPGeAnalysisManager *m_pAnalysisManager;
};

#endif // __XENON10PRUNACTION_H__

