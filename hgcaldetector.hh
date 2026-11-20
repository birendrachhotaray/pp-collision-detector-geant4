#ifndef HGCALDETECTOR_HH
#define HGCALDETECTOR_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

class HGCALDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    HGCALDetectorConstruction();
    ~HGCALDetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

private:
    void DefineMaterials();

    G4Box* worldBox;
    G4LogicalVolume* logicalWorld;
    G4VPhysicalVolume* physicalWorld;

    G4double xWorld, yWorld, zWorld;

    G4Material* worldMat;
    G4Material* tungstenMat;
    G4Material* siliconMat;
};

#endif
