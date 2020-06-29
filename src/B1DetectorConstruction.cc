#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 50*cm;
  G4double world_sizeZ  = 50*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material* W = nist->FindOrBuildMaterial("G4_W");
  G4Material* C = nist->FindOrBuildMaterial("G4_C");
  G4Material* H = nist->FindOrBuildMaterial("G4_H");
  G4Material* O = nist->FindOrBuildMaterial("G4_O");
  G4Material* Cl = nist->FindOrBuildMaterial("G4_Cl");
  G4Material* Cu = nist->FindOrBuildMaterial("G4_Cu");

  G4Material* epoxy = new G4Material("epoxy",1.3*g/cm3,3);
  epoxy->AddMaterial(C,0.5354);
  epoxy->AddMaterial(H,0.1318);
  epoxy->AddMaterial(O,0.3328);

  G4Material* G10 = new G4Material("G10",1.3*g/cm3,3);
  G10->AddMaterial(Cl,0.080);
  G10->AddMaterial(epoxy,0.147);
  G10->AddMaterial(SiO2,0.773);
/*
  <material name="Epoxy" state="solid">
   <D value="1.3" unit="g/cm3"/>
   <fraction n="0.5354" ref="C"/>
   <fraction n="0.1318" ref="H"/>
   <fraction n="0.3328" ref="O"/>
</material>
<material name="G10" state="solid">
 <D value="1.3" unit="g/cm3"/>
<fraction n="0.773" ref="G4_SILICON_DIOXIDE"/>
 <fraction n="0.147" ref="Epoxy"/>
 <fraction n="0.080" ref="G4_Cl"/>
</material>
  */
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
	      0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
  
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  G4Box* solidSh =    
    new G4Box("solidSh",                    //its name
	      0.5*2*cm, 0.5*2*cm, 0.5*3*cm); //its size
                     
  G4Box* solidF =    
    new G4Box("solidF",                    //its name
	      0.5*1*cm, 0.5*1*cm, 0.5*3*mm); //its size

  G4Box* solidB =    
    new G4Box("solidB",                    //its name
	      0.5*1*cm, 0.5*1*cm, 0.5*38*mm); //its size

  G4Box* solidMid =    
    new G4Box("solidMid",                    //its name
	      0.5*1*cm, 0.5*1*cm, 0.5*1*mm); //its size

  G4LogicalVolume* logicSh =                         
    new G4LogicalVolume(solidSh,            //its solid
                        W,             //its material
                        "logicSh");         //its name
  G4LogicalVolume* logicF =                         
    new G4LogicalVolume(solidF,            //its solid
                        W,             //its material
                        "logicF");         //its name
  G4LogicalVolume* logicMid =                         
    new G4LogicalVolume(solidMid,            //its solid
                        G10,             //its material
                        "logicMid");         //its name
  G4LogicalVolume* logicB =
    new G4LogicalVolume(solidB,            //its solid
                        Cu,             //its material
                        "logicB");         //its name

/*  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,-4*cm),
                    logicSh,                //its logical volume
                    "shield",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
*/ 
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,-2.0*mm),
                    logicF,                //its logical volume
                    "front",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,19.5*mm),
                    logicB,                //its logical volume
                    "back",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),
                    logicMid,                //its logical volume
                    "mid",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume.push_back(logicF);
  fScoringVolume.push_back(logicMid);
  fScoringVolume.push_back(logicB);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
