-- MySQL dump 10.13  Distrib 5.5.35, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: ICTUMTest
-- ------------------------------------------------------
-- Server version	5.5.35-0ubuntu0.13.10.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Actors`
--

DROP TABLE IF EXISTS `Actors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Actors` (
  `actor_id` INTEGER AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `middleName` varchar(100) DEFAULT NULL,
  `lastName` varchar(100) DEFAULT NULL,
  `rol_id` int(11) DEFAULT NULL,
  `ou_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`actor_id`),
  KEY `rol_id` (`rol_id`),
  KEY `ou_id` (`ou_id`),
  CONSTRAINT `Actors_ibfk_1` FOREIGN KEY (`rol_id`) REFERENCES `Roles` (`rol_id`),
  CONSTRAINT `Actors_ibfk_2` FOREIGN KEY (`ou_id`) REFERENCES `OrganizationalUnits` (`ou_id`)
) ENGINE=InnoDB AUTOINCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Actors`
--

LOCK TABLES `Actors` WRITE;
/*!40000 ALTER TABLE `Actors` DISABLE KEYS */;
INSERT INTO `Actors` VALUES (1,'Mitch','','Yoda',1,1),(2,'Mace','','Windu',2,1),(3,'Obi-Wan','','Kenobi',2,1),(4,'Riyo','','Chuchi',5,2);
/*!40000 ALTER TABLE `Actors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ActorsProcesses`
--

DROP TABLE IF EXISTS `ActorsProcesses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ActorsProcesses` (
  `actor_id` int(11) NOT NULL DEFAULT '0',
  `process_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`actor_id`,`process_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ActorsProcesses`
--

LOCK TABLES `ActorsProcesses` WRITE;
/*!40000 ALTER TABLE `ActorsProcesses` DISABLE KEYS */;
/*!40000 ALTER TABLE `ActorsProcesses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DataEntity`
--

DROP TABLE IF EXISTS `DataEntity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DataEntity` (
  `data_entity_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `information_service_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`data_entity_id`),
  KEY `information_service_id` (`information_service_id`),
  CONSTRAINT `DataEntity_ibfk_1` FOREIGN KEY (`information_service_id`) REFERENCES `InformationSystemServices` (`information_service_id`)
) ENGINE=InnoDB AUTOINCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DataEntity`
--

LOCK TABLES `DataEntity` WRITE;
/*!40000 ALTER TABLE `DataEntity` DISABLE KEYS */;
INSERT INTO `DataEntity` VALUES (1,'Padawans','Contain information about all the padawans of the Jedi Order',1),(2,'Younglings','Holocron that contains information about the force sensitive childs in the galaxy',1),(3,'Seeker Indexes Database','Is a database used by The Seeker program to save and use the indexes it uses to perform searches.',4);
/*!40000 ALTER TABLE `DataEntity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Functions`
--

DROP TABLE IF EXISTS `Functions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Functions` (
  `function_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`function_id`)
) ENGINE=InnoDB AUTOINCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Functions`
--

LOCK TABLES `Functions` WRITE;
/*!40000 ALTER TABLE `Functions` DISABLE KEYS */;
INSERT INTO `Functions` VALUES (1,'Agresive negociations','Negociations made with the light saber'),(2,'The force','allow the Jedi to use mind control, telekinesis, sense the others feelings, throw rays from the hands and predict the immediate future.'),(3,'Create New Law','allow people to create new laws for the Galactic Republic	');
/*!40000 ALTER TABLE `Functions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `InformationSystemServices`
--

DROP TABLE IF EXISTS `InformationSystemServices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `InformationSystemServices` (
  `information_service_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `physical_technology_component_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`information_service_id`),
  KEY `physical_technology_component_id` (`physical_technology_component_id`),
  CONSTRAINT `InformationSystemServices_ibfk_1` FOREIGN KEY (`physical_technology_component_id`) REFERENCES `PhysicalTechnologiesComponents` (`physical_technology_component_id`)
) ENGINE=InnoDB AUTOINCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `InformationSystemServices`
--

LOCK TABLES `InformationSystemServices` WRITE;
/*!40000 ALTER TABLE `InformationSystemServices` DISABLE KEYS */;
INSERT INTO `InformationSystemServices` VALUES (1,'Padawan Administrator','A web app that allows jedi Knights check the improvements of their padawans, this app also holds the personal information of all the padawans in the jedi order ',1),(2,'Younglings Information Manager','An application that allow the Supreme Jedi council menmbers access  ALL KIND OF information about all the younglings that are meant to become Jedi Knights.',1),(3,'Jedi Manager','An application that holds information about all Jedi knights including their padawans, and their rank within the Jedi order.',1),(4,'The Seeker','Is a program capable of find any information requested regarding anything subject, like Galactic Republic History, Jedi Knight, younglings or padawan information.....seriously anything you want to know. ',2),(5,'Authentication Program','verify if the user have the clearance to access the requested data',1);
/*!40000 ALTER TABLE `InformationSystemServices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `IssDependency`
--

DROP TABLE IF EXISTS `IssDependency`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `IssDependency` (
  `information_service_id` int(11) NOT NULL,
  `depends` int(11) NOT NULL,
  PRIMARY KEY (`information_service_id`,`depends`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `IssDependency`
--

LOCK TABLES `IssDependency` WRITE;
/*!40000 ALTER TABLE `IssDependency` DISABLE KEYS */;
INSERT INTO `IssDependency` VALUES (4,0),(4,1),(4,2),(4,3);
/*!40000 ALTER TABLE `IssDependency` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `IssDependsSupport`
--

DROP TABLE IF EXISTS `IssDependsSupport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `IssDependsSupport` (
  `information_service_id` int(11) NOT NULL,
  `depends` int(11) NOT NULL DEFAULT '0',
  `suplies` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`information_service_id`,`depends`,`suplies`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `IssDependsSupport`
--

LOCK TABLES `IssDependsSupport` WRITE;
/*!40000 ALTER TABLE `IssDependsSupport` DISABLE KEYS */;
INSERT INTO `IssDependsSupport` VALUES (1,0,3),(3,1,0),(4,0,1),(4,0,2),(4,0,3),(4,5,0);
/*!40000 ALTER TABLE `IssDependsSupport` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `IssSupport`
--

DROP TABLE IF EXISTS `IssSupport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `IssSupport` (
  `information_service_id` int(11) NOT NULL,
  `support` int(11) NOT NULL,
  PRIMARY KEY (`information_service_id`,`support`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `IssSupport`
--

LOCK TABLES `IssSupport` WRITE;
/*!40000 ALTER TABLE `IssSupport` DISABLE KEYS */;
INSERT INTO `IssSupport` VALUES (1,3),(3,1),(5,1),(5,3),(5,4);
/*!40000 ALTER TABLE `IssSupport` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Locations`
--

DROP TABLE IF EXISTS `Locations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Locations` (
  `location_id` int(11) NOT NULL AUTOINCREMENT,
  `location` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`location_id`)
) ENGINE=InnoDB AUTOINCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Locations`
--

LOCK TABLES `Locations` WRITE;
/*!40000 ALTER TABLE `Locations` DISABLE KEYS */;
INSERT INTO `Locations` VALUES (1,'Coruscant');
/*!40000 ALTER TABLE `Locations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `OrganizationalUnits`
--

DROP TABLE IF EXISTS `OrganizationalUnits`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `OrganizationalUnits` (
  `ou_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `objective` varchar(255) DEFAULT NULL,
  `location` varchar(255) DEFAULT NULL,
  `tasks` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ou_id`)
) ENGINE=InnoDB AUTOINCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `OrganizationalUnits`
--

LOCK TABLES `OrganizationalUnits` WRITE;
/*!40000 ALTER TABLE `OrganizationalUnits` DISABLE KEYS */;
INSERT INTO `OrganizationalUnits` VALUES (1,'Jedi Temple','Coordinate jedi Operations in the galaxy','Coruscant','Coordinate jedi operantions in the galaxy, host supreme jedi council meetings, assing missions to the Jedi'),(2,'Senate','Manage Republic laws','Coruscant','take decisions about republic affairs, create new laws, modify laws, elect the supreme chancellor');
/*!40000 ALTER TABLE `OrganizationalUnits` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PhysicalComponentsSupport`
--

DROP TABLE IF EXISTS `PhysicalComponentsSupport`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PhysicalComponentsSupport` (
  `physical_technology_component_id` int(11) NOT NULL,
  `support` int(11) NOT NULL,
  PRIMARY KEY (`physical_technology_component_id`,`support`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PhysicalComponentsSupport`
--

LOCK TABLES `PhysicalComponentsSupport` WRITE;
/*!40000 ALTER TABLE `PhysicalComponentsSupport` DISABLE KEYS */;
/*!40000 ALTER TABLE `PhysicalComponentsSupport` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PhysicalTechnologiesComponents`
--

DROP TABLE IF EXISTS `PhysicalTechnologiesComponents`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PhysicalTechnologiesComponents` (
  `physical_technology_component_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `objective` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `location` int(11) DEFAULT NULL,
  PRIMARY KEY (`physical_technology_component_id`)
) ENGINE=InnoDB AUTOINCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PhysicalTechnologiesComponents`
--

LOCK TABLES `PhysicalTechnologiesComponents` WRITE;
/*!40000 ALTER TABLE `PhysicalTechnologiesComponents` DISABLE KEYS */;
INSERT INTO `PhysicalTechnologiesComponents` VALUES (1,'TriForce Hope Server','Host Padawna web app','1024 PB RAM, 1024 EB HDD, 2500 logic threads',1),(2,'TriForce Lotus Server','Host The Seeker Program','1024 EB RAM, 1024 YB HDD 400000000000 Logic Threads ',1);
/*!40000 ALTER TABLE `PhysicalTechnologiesComponents` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Processes`
--

DROP TABLE IF EXISTS `Processes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Processes` (
  `process_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `objective` varchar(150) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`process_id`)
) ENGINE=InnoDB AUTOINCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Processes`
--

LOCK TABLES `Processes` WRITE;
/*!40000 ALTER TABLE `Processes` DISABLE KEYS */;
INSERT INTO `Processes` VALUES (1,'Ensure Peace','End with Warfare','The Galactic Republic Use this Process to end with warfare between enemies systems'),(2,'Rescue Jedi','Rescue the captives Jedi','This process shows the standard procedure to rescue a captive Jedi 1-find the place where the Jedi is captive;2-send three Jedi to the place;3-kick everyone asses;4-rescue the Jedi;5-Get out of there;\n\0'),(3,'Legislar','Tomar decisiones sobre los asuntos de la Republica','Mediante este proceso es posible crear nuevas leyes, modificar las existentes y tomar decisiones sobre el camino que debe tomar la Republica ante cualquier situacion');
/*!40000 ALTER TABLE `Processes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Roles`
--

DROP TABLE IF EXISTS `Roles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Roles` (
  `rol_id` int(11) NOT NULL AUTOINCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `objective` varchar(255) DEFAULT NULL,
  `tasks` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`rol_id`)
) ENGINE=InnoDB AUTOINCREMENT=7 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Roles`
--

LOCK TABLES `Roles` WRITE;
/*!40000 ALTER TABLE `Roles` DISABLE KEYS */;
INSERT INTO `Roles` VALUES (1,'Jedi Grand Master','Lead the Supreme Jedi Council','Sumon Concil meetings, advice the supreme concelor about militar affairs '),(2,'Jedi Master','Serve in the jedi Council','vote in the jedi council'),(3,'Jedi','Mantain pace in the galaxy','serve as diplomatic embassador, serve as body guard, serve as an ally of justice by defeating the evil'),(4,'Padawan','Learn the ways of the Jedi','Learn how to be a great Jedi'),(5,'Senator','Legislate in behalf of the Republic','vote for the createation of new laws, vote to modify existent Laws, do diplomatic stuffs'),(6,'Asiste','Asistir','Asiste  a la gente');
/*!40000 ALTER TABLE `Roles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `RolesFunctions`
--

DROP TABLE IF EXISTS `RolesFunctions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `RolesFunctions` (
  `rol_id` int(11) NOT NULL,
  `function_id` int(11) NOT NULL,
  PRIMARY KEY (`rol_id`,`function_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `RolesFunctions`
--

LOCK TABLES `RolesFunctions` WRITE;
/*!40000 ALTER TABLE `RolesFunctions` DISABLE KEYS */;
INSERT INTO `RolesFunctions` VALUES (1,1),(1,2),(2,1),(2,2),(3,1),(3,2),(4,1),(4,2),(5,3);
/*!40000 ALTER TABLE `RolesFunctions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `RolesProcesses`
--

DROP TABLE IF EXISTS `RolesProcesses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `RolesProcesses` (
  `rol_id` int(11) NOT NULL,
  `process_id` int(11) NOT NULL,
  PRIMARY KEY (`rol_id`,`process_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `RolesProcesses`
--

LOCK TABLES `RolesProcesses` WRITE;
/*!40000 ALTER TABLE `RolesProcesses` DISABLE KEYS */;
INSERT INTO `RolesProcesses` VALUES (2,2),(3,1),(3,2),(5,0),(5,3);
/*!40000 ALTER TABLE `RolesProcesses` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-04-21 22:56:10
