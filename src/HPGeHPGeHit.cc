#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

#include "HPGeHPGeHit.hh"

using namespace CLHEP;

G4Allocator<HPGeHPGeHit> HPGeHPGeHitAllocator;

HPGeHPGeHit::HPGeHPGeHit() {}

HPGeHPGeHit::~HPGeHPGeHit()
{
	if(m_pParticleType) delete m_pParticleType;
	if(m_pParentType) delete m_pParentType;
	if(m_pCreatorProcess) delete m_pCreatorProcess;
	if(m_pDepositingProcess) delete m_pDepositingProcess;
        if(m_pVolumeName)        delete m_pVolumeName;
//        if(m_hPosition)          delete m_hPosition;
}

HPGeHPGeHit::HPGeHPGeHit(const HPGeHPGeHit &hHPGeHPGeHit):G4VHit()
{
	m_iTrackId = hHPGeHPGeHit.m_iTrackId;
	m_iTrackPDG = hHPGeHPGeHit.m_iTrackPDG;
	m_iParentId = hHPGeHPGeHit.m_iParentId;
	m_pParticleType = hHPGeHPGeHit.m_pParticleType;
	m_pParentType = hHPGeHPGeHit.m_pParentType ;
	m_pCreatorProcess = hHPGeHPGeHit.m_pCreatorProcess ;
	m_pDepositingProcess = hHPGeHPGeHit.m_pDepositingProcess ;
        m_pVolumeName = hHPGeHPGeHit.m_pVolumeName ;
	m_hPosition = hHPGeHPGeHit.m_hPosition;
	m_dEnergyDeposited = hHPGeHPGeHit.m_dEnergyDeposited;
	m_dKineticEnergy = hHPGeHPGeHit.m_dKineticEnergy ;
	m_dTime = hHPGeHPGeHit.m_dTime;
}

const HPGeHPGeHit &
HPGeHPGeHit::operator=(const HPGeHPGeHit &hHPGeHPGeHit)
{
	m_iTrackId = hHPGeHPGeHit.m_iTrackId;
	m_iTrackPDG = hHPGeHPGeHit.m_iTrackPDG;
	m_iParentId = hHPGeHPGeHit.m_iParentId;
	m_pParticleType = hHPGeHPGeHit.m_pParticleType;
	m_pParentType = hHPGeHPGeHit.m_pParentType ;
	m_pCreatorProcess = hHPGeHPGeHit.m_pCreatorProcess ;
	m_pDepositingProcess = hHPGeHPGeHit.m_pDepositingProcess ;
        m_pVolumeName = hHPGeHPGeHit.m_pVolumeName ;
	m_hPosition = hHPGeHPGeHit.m_hPosition;
	m_dEnergyDeposited = hHPGeHPGeHit.m_dEnergyDeposited;
	m_dKineticEnergy = hHPGeHPGeHit.m_dKineticEnergy ;
	m_dTime = hHPGeHPGeHit.m_dTime;
	
	return *this;
}

G4int
HPGeHPGeHit::operator==(const HPGeHPGeHit &hHPGeHPGeHit) const
{
	return ((this == &hHPGeHPGeHit) ? (1) : (0));
}

void HPGeHPGeHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	
	if(pVVisManager)
	{
		G4Circle hCircle(m_hPosition);
		G4Colour hColour(1.000, 0.973, 0.184);
		G4VisAttributes hVisAttributes(hColour);
		
		hCircle.SetScreenSize(0.1);
		hCircle.SetFillStyle(G4Circle::filled);
		hCircle.SetVisAttributes(hVisAttributes);
		pVVisManager->Draw(hCircle);
	}
}

void HPGeHPGeHit::Print()
{
	G4cout << "-------------------- LXe hit --------------------" 
		<< "Id: " << m_iTrackId
		<< " Particle: " << *m_pParticleType
		<< " ParentId: " << m_iParentId
		<< " ParentType: " << *m_pParentType << G4endl
		<< "CreatorProcess: " << *m_pCreatorProcess
		<< " DepositingProcess: " << *m_pDepositingProcess << G4endl
                << " VolumeName: " << *m_pVolumeName << G4endl
		<< "Position: " << m_hPosition.x()/mm
		<< " " << m_hPosition.y()/mm
		<< " " << m_hPosition.z()/mm
		<< " mm" << G4endl
		<< "EnergyDeposited: " << m_dEnergyDeposited/keV << " keV"
		<< " KineticEnergyLeft: " << m_dKineticEnergy/keV << " keV"
		<< " Time: " << m_dTime/s << " s" << G4endl;
}

