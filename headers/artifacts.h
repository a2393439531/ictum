#ifndef ARTIFACTS_H
#define ARTIFACTS_H

#include <QWidget>

class Actor;
class Role;
class OrganizationalUnit;
class Function;
class DataEntity;
class InformationSystemService;
class PhysicalTechnologyComponent;
class Location;
class ActorRoleMatrix;
class ActorOuMatrix;
class PhysicalTechComponentLocationMatrix;
class RoleFunctionMatrix;
class DataEntityInfoSystemMatrix;
class InfoSystemServicesDependencyMatrix;
class ActorFunctionMatrix;
class OuFunctionMatrix;
class Process;
class ActorProcessMatrix;
class RoleProcessMatrix;
class InfoSystemServiceSupportMatrix;
class PhysicalComponentSupportMatrix;


class Artifacts : public QWidget
{
 public:
	Artifacts(QWidget* parent = 0);
	
  private:
	OrganizationalUnit* ou;
	Role* role;
	Actor* actor;
	Function* function;
	DataEntity* dataEntity;
	InformationSystemService* infoSystemService;
	PhysicalTechnologyComponent* physicalTechComp;
	Location* loc;
	ActorRoleMatrix* roleMatrix;
	ActorOuMatrix* ouMatrix;
	PhysicalTechComponentLocationMatrix* pTCLM;		
	RoleFunctionMatrix* rFM;
	DataEntityInfoSystemMatrix* dE;
	InfoSystemServicesDependencyMatrix* iSSDM;
	ActorFunctionMatrix* aFM;
	OuFunctionMatrix* oUFM;
	Process * process;
	ActorProcessMatrix* aPM;
	RoleProcessMatrix* rPM;
	InfoSystemServiceSupportMatrix* iSSSM;
	PhysicalComponentSupportMatrix* pCSM;
};
#endif
