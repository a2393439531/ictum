#include "../headers/artifacts.h"
#include "../headers/role.h"
#include "../headers/actor.h"
#include "../headers/organizational_unit.h"
#include "../headers/function.h"
#include "../headers/data_entity.h"
#include "../headers/information_system_service.h"
#include "../headers/physical_technology_component.h"
#include "../headers/location.h"
#include "../headers/actor_role_matrix.h"
#include "../headers/actor_ou_matrix.h"
#include "../headers/physical_tech_component_location_matrix.h"
#include "../headers/role_function_matrix.h"
#include "../headers/data_entity_info_system_matrix.h"
#include "../headers/info_system_services_dependency_matrix.h"
#include "../headers/actor_function_matrix.h"
#include "../headers/ou_function_matrix.h"
#include "../headers/process.h"
#include "../headers/actor_process_matrix.h"
#include "../headers/role_process_matrix.h"
#include "../headers/info_system_service_support_matrix.h"
#include "../headers/physical_component_support_matrix.h"
#include <QLabel>
#include <QDebug>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

Artifacts::Artifacts(QWidget* parent) : QWidget(parent)
{
	qDebug()<<"me llamaron";

	QWidget* centralWidget = new QWidget;
	QHBoxLayout* centralWidgetLayout = new QHBoxLayout(centralWidget);
	
	/* sets up the business architecture part of the UI*/
	//business architecture groupboxes
	QGroupBox* businessArchitectureWrapperGroupBox = new QGroupBox("Arquitectura de Negocio");
	QGroupBox* businessArchitectureCatalogsGroupBox = new QGroupBox("Catalogos");
	QGroupBox* businessArchitectureMatrixGroupBox = new QGroupBox("Matrices");
	
	//businessLayouts
	QVBoxLayout* businessWrapperGroupBoxLayout = new QVBoxLayout(businessArchitectureWrapperGroupBox);
	QVBoxLayout* businessCataloggroupBoxLayout = new QVBoxLayout(businessArchitectureCatalogsGroupBox);
	QVBoxLayout* businessMatricesGroupBoxLayout = new QVBoxLayout(businessArchitectureMatrixGroupBox);
	
	//add business architecture catalogs and matrices buttons to the main layout
	businessWrapperGroupBoxLayout->addWidget(businessArchitectureCatalogsGroupBox);
	businessWrapperGroupBoxLayout->addWidget(businessArchitectureMatrixGroupBox);

	//business architecture buttons catalogs
	QPushButton* actors = new QPushButton("Actores");
	actors->setFlat(true);
	QPushButton* roles = new QPushButton("Roles");
	roles->setFlat(true);
	QPushButton* ous = new QPushButton("Unidades Organizacionales");
	ous->setFlat(true);
	QPushButton* functions = new QPushButton("Funciones");
	functions->setFlat(true);
	QPushButton* processes = new QPushButton("procesos");
	processes->setFlat(true);
	QPushButton* locations = new QPushButton("Ubicaciones");
	locations->setFlat(true);
	
	//bussines architecture buttons matrices
	QPushButton* actorRoleMatrix = new QPushButton("Actores/Roles");
	actorRoleMatrix->setFlat(true);
	QPushButton* actorFunctionMatrix = new QPushButton("Actores/Functiones");
	actorFunctionMatrix->setFlat(true);
	QPushButton* actorProcessMatrix = new QPushButton("Actores/Procesos");
	actorProcessMatrix->setFlat(true);
	QPushButton* actorOuMatrix = new QPushButton("Actores/OU");
	actorOuMatrix->setFlat(true);
	QPushButton* functionOuMatrix = new QPushButton("OU/Funciones");
	functionOuMatrix->setFlat(true);
	QPushButton* rolesProcessMatrix = new QPushButton("Roles/Procesos");
	rolesProcessMatrix->setFlat(true);
	QPushButton* roleFunctionMatrix = new QPushButton("Roles/Functiones");
	roleFunctionMatrix->setFlat(true);

	//add business catalog buttons to the layout
	businessCataloggroupBoxLayout->addWidget(actors);
	businessCataloggroupBoxLayout->addWidget(roles);
	businessCataloggroupBoxLayout->addWidget(ous);
	businessCataloggroupBoxLayout->addWidget(functions);
	businessCataloggroupBoxLayout->addWidget(processes);
	businessCataloggroupBoxLayout->addWidget(locations);

	//add matrices buttons to the layout
	businessMatricesGroupBoxLayout->addWidget(actorRoleMatrix);
	businessMatricesGroupBoxLayout->addWidget(actorFunctionMatrix);
	businessMatricesGroupBoxLayout->addWidget(actorProcessMatrix);
	businessMatricesGroupBoxLayout->addWidget(actorOuMatrix);
	businessMatricesGroupBoxLayout->addWidget(functionOuMatrix);
	businessMatricesGroupBoxLayout->addWidget(rolesProcessMatrix);
	businessMatricesGroupBoxLayout->addWidget(roleFunctionMatrix);
	
	
	/* sets up the information architecture part of the UI */
	//data Architecture Groupboxes
	QGroupBox* informationArchitectureWrapperGroupBox = new QGroupBox("Arquitectura de la Inforamcion");
	QGroupBox* informationArchitectureCatalogsGroupBox = new QGroupBox("Catalogos");
	QGroupBox* informationArchitectureMatrixGroupBox = new QGroupBox("Matrices");

	//data Layouts		
	QVBoxLayout* informationWrapperGroupBoxLayout = new QVBoxLayout(informationArchitectureWrapperGroupBox);
	QVBoxLayout* informationCatalogGroupBoxLayout = new QVBoxLayout(informationArchitectureCatalogsGroupBox);
	QVBoxLayout* informationMatricesGroupBoxLayout = new QVBoxLayout(informationArchitectureMatrixGroupBox);
	
	//add information architecture cataloga and matrices buttons to the layout
	informationWrapperGroupBoxLayout->addWidget(informationArchitectureCatalogsGroupBox);
	informationWrapperGroupBoxLayout->addWidget(informationArchitectureMatrixGroupBox);
	
	//Information architecture catalog buttons
	QPushButton* dataEntities = new QPushButton("Entidad de datos");
	dataEntities->setFlat(true);
	QPushButton* iss = new QPushButton("Sistema de Servicios de Informacion");
	iss->setFlat(true);
	
	//Information architecture matrices buttons
	QPushButton* dataEntityIss = new QPushButton("Entida de datos/Sistemas de la Informacion");
	dataEntityIss->setFlat(true);
	QPushButton* infoSystemDepends = new QPushButton("Systema de Informacion/Dependencia");
	infoSystemDepends->setFlat(true);
	QPushButton* infoSystemSupport = new QPushButton("Systema de Informacion/Apoya");
	infoSystemSupport->setFlat(true);

	//add information architecture catalogs buttons to the layout
	informationCatalogGroupBoxLayout->addWidget(dataEntities);
	informationCatalogGroupBoxLayout->addWidget(iss);

	//adds information architecture matrix buttons to the layout
	informationMatricesGroupBoxLayout->addWidget(dataEntityIss);
	informationMatricesGroupBoxLayout->addWidget(infoSystemDepends);
	informationMatricesGroupBoxLayout->addWidget(infoSystemSupport);
	
	/*sets up the technology architecture part of the UI */
	//technology architecture groupboxes
	QGroupBox* technologyArchitectureWrapperGroupBox = new QGroupBox("Arquitectura Tecnologica");
	QGroupBox* technologyArchitectureCatalogsGroupBox = new QGroupBox("Catalogos");
	QGroupBox* technologyArchitectureMatrixGroupBox = new QGroupBox("Matrices");
	
	//Technology layouts
	QVBoxLayout* technologyWrapperGroupBoxLayout = new QVBoxLayout(technologyArchitectureWrapperGroupBox);
	QVBoxLayout* technologyCatalogGroupBoxLayout = new QVBoxLayout(technologyArchitectureCatalogsGroupBox);
	QVBoxLayout* technologyMatricesGroupBoxLayout = new QVBoxLayout(technologyArchitectureMatrixGroupBox);

	//add technology architecture cataloga and matrices buttons to the layout
	technologyWrapperGroupBoxLayout->addWidget(technologyArchitectureCatalogsGroupBox);
	technologyWrapperGroupBoxLayout->addWidget(technologyArchitectureMatrixGroupBox);

	//technology architecture catalog buttons
	QPushButton* ptc = new QPushButton("Componente Fisico Tecnologico");
	ptc->setFlat(true);

	//technology architecture matrices buttons
	QPushButton* physicalComponentLocation = new QPushButton("Componente Fisico/Ubicacion");
	physicalComponentLocation->setFlat(true);
	QPushButton* physicalComponenetDepends = new QPushButton("Componente Fisico/Depencia");
	physicalComponenetDepends->setFlat(true);
	QPushButton* physicalComponentSupport = new QPushButton("Componente Fisico/Apoyo");
	physicalComponentSupport->setFlat(true);

	//add physical architecture catalogs buttons to the layout
	technologyCatalogGroupBoxLayout->addWidget(ptc);

	//add physical architecture matrices to the layout
	technologyMatricesGroupBoxLayout->addWidget(physicalComponentLocation);
	technologyMatricesGroupBoxLayout->addWidget(physicalComponenetDepends);
	technologyMatricesGroupBoxLayout->addWidget(physicalComponentSupport);
	
	
	//add widgets to the main layout
	centralWidgetLayout->addWidget(businessArchitectureWrapperGroupBox);
	centralWidgetLayout->addStretch();
	centralWidgetLayout->addWidget(informationArchitectureWrapperGroupBox);
	centralWidgetLayout->addStretch();
	centralWidgetLayout->addWidget(technologyArchitectureWrapperGroupBox);

	this->setLayout(centralWidgetLayout);

	
	actor = new Actor(this);
	role = new Role(this);
	ou = new OrganizationalUnit(this);
	function = new Function(this);
	dataEntity = new DataEntity(this);
	infoSystemService = new InformationSystemService(this);
	physicalTechComp = new PhysicalTechnologyComponent(this);
	loc = new Location(this);
	roleMatrix = new ActorRoleMatrix(this);
	ouMatrix = new ActorOuMatrix(this);
	pTCLM = new PhysicalTechComponentLocationMatrix(this);
	rFM = new RoleFunctionMatrix(this);
	dE = new DataEntityInfoSystemMatrix(this);
	iSSDM = new InfoSystemServicesDependencyMatrix(this);
	aFM = new ActorFunctionMatrix(this);
	oUFM = new OuFunctionMatrix(this);
	process = new Process(this);
	aPM = new ActorProcessMatrix(this);
	rPM = new RoleProcessMatrix(this);
	iSSSM = new InfoSystemServiceSupportMatrix(this);
	pCSM = new PhysicalComponentSupportMatrix(this);

	//opens actor dialog when actors button is clicked
	connect(actors, SIGNAL(clicked()),
		   actor, SLOT(exec()));
	//opens roles dialog when roles button is clicked
	connect(roles, SIGNAL(clicked()),
			role, SLOT(exec()));
	//opens ou dialog when Organizational units button(ou) is clicked
	connect(ous, SIGNAL(clicked()),
		   ou, SLOT(exec()));
	//opens function dialog when Function buttons is clicked
	connect(functions, SIGNAL(clicked()),
			function, SLOT(exec()));
	//opens dataEntity dialog when dataEntity button is clicked
	connect(dataEntities, SIGNAL(clicked()),
			dataEntity, SLOT(exec()));
	//opens information system services dialog when its button is clicked	
	connect(iss, SIGNAL(clicked()),
			infoSystemService, SLOT(exec()));
	//opens physical technology component dialog when its button is clicked
	connect(ptc, SIGNAL(clicked()),
			physicalTechComp, SLOT(exec()));
	//opens location dialog when its button is clicked
	connect(locations, SIGNAL(clicked()),
			loc, SLOT(exec()));
	//opens actor/role dialog when its button is clicked
	connect(actorRoleMatrix, SIGNAL(clicked()),
			roleMatrix, SLOT(exec()));
	//opens actor/ou dialog when its button is clicked
	connect(actorOuMatrix, SIGNAL(clicked()),
			ouMatrix, SLOT(exec()));
	//opens physical Component/location dialog when its button is clicked
	connect(physicalComponentLocation,SIGNAL(clicked()),
			pTCLM, SLOT(exec()));
	//opens role/function dialog when its button is clicked
	connect(roleFunctionMatrix, SIGNAL(clicked()),
			rFM, SLOT(exec()));
	//opens data entity/information system services dialog when its button is clicked
	connect(dataEntityIss, SIGNAL(clicked()),
			dE, SLOT(exec()));
	//opens info system services/dependency system services dialog when its button is clicked
	connect(infoSystemDepends, SIGNAL(clicked()),
			iSSDM, SLOT(exec()));
	//opens actor/function system services dialog when its button is clicked
	connect(actorFunctionMatrix, SIGNAL(clicked()),
			aFM, SLOT(exec()));
	//opens ou/function system services dialog when its button is clicked
	connect(functionOuMatrix, SIGNAL(clicked()),
			oUFM, SLOT(exec()));
	//opens process dialog when its button is clicked
	connect(processes, SIGNAL(clicked()),
			process, SLOT(exec()));
	//opens actor/process dialog when its button is clicked
	connect(actorProcessMatrix, SIGNAL(clicked()),
			aPM, SLOT(exec()));
	//opens role/process dialog when its button is clicked
	connect(rolesProcessMatrix, SIGNAL(clicked()),
			rPM, SLOT(exec()));
	//opens role/process dialog when its button is clicked
	connect(infoSystemSupport, SIGNAL(clicked()),
			iSSSM, SLOT(exec()));
	//opens componente fisico/apoyo dialog when its button is clicked
	connect(physicalComponentSupport, SIGNAL(clicked()),
			pCSM, SLOT(exec()));
}
