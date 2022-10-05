#ifndef __XENON10PSTEPPINGACTION_H__
#define __XENON10PSTEPPINGACTION_H__

#include <globals.hh>
#include <G4UserSteppingAction.hh>

class HPGeAnalysisManager;

class HPGeSteppingAction: public G4UserSteppingAction
{
public:
	HPGeSteppingAction(HPGeAnalysisManager *pAnalysisManager=0);
	~HPGeSteppingAction();
  
        void UserSteppingAction(const G4Step*);

private:
	HPGeAnalysisManager *m_pAnalysisManager;
};

#endif // __XENON10PSTEPPINGACTION_H__

