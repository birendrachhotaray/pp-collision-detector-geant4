#include "hgcaldetector.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ThreeVector.hh"

// Constructor
HGCALDetectorConstruction::HGCALDetectorConstruction()
{
    xWorld = 40. * m;
    yWorld = 40. * m;
    zWorld = 40. * m;

    DefineMaterials();
}

// Destructor
HGCALDetectorConstruction::~HGCALDetectorConstruction()
{}

// Define materials
void HGCALDetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    worldMat = nist->FindOrBuildMaterial("G4_AIR");

    tungstenMat = nist->FindOrBuildMaterial("G4_W");

    siliconMat = nist->FindOrBuildMaterial("G4_Si");
}

// Construct detector geometry
G4VPhysicalVolume* HGCALDetectorConstruction::Construct()
{
    // ------------------------------------------------
    // 1. WORLD VOLUME
    // ------------------------------------------------

    worldBox = new G4Box(
        "worldBox",
        xWorld,
        yWorld,
        zWorld
    );

    logicalWorld = new G4LogicalVolume(
        worldBox,
        worldMat,
        "logicalWorld"
    );

    physicalWorld = new G4PVPlacement(
        nullptr,
        G4ThreeVector(0., 0., 0.),
        logicalWorld,
        "physicalWorld",
        nullptr,
        false,
        0,
        true
    );

    // ------------------------------------------------
    // 2. DETECTOR DIMENSIONS
    // ------------------------------------------------

    G4double innerHalfLength = 10. * cm;

    G4double tungstenThickness = 10. * mm;

    G4double siliconThickness = 0.3 * mm;

    // Number of sampling layers
    G4int numberOfLayers = 10;

    // ------------------------------------------------
    // 3. VISUAL ATTRIBUTES
    // ------------------------------------------------

    G4VisAttributes* tungstenVis = new G4VisAttributes(
        G4Colour(0.35, 0.35, 0.35)
    );

    tungstenVis->SetForceSolid(true);

    G4VisAttributes* siliconVis = new G4VisAttributes(
        G4Colour(1.0, 0.85, 0.0)
    );

    siliconVis->SetForceSolid(true);

    // ------------------------------------------------
    // 4. ALTERNATING TUNGSTEN AND SILICON LAYERS
    // ------------------------------------------------

    for (G4int i = 0; i < numberOfLayers; i++)
    {
        // Calculate the inner and outer dimensions
        // of the current tungsten layer

        G4double innerW = innerHalfLength +
            i * (tungstenThickness + siliconThickness);

        G4double outerW = innerW + tungstenThickness;

        // --------------------------------------------
        // TUNGSTEN ABSORBER
        // --------------------------------------------

        G4Box* tungstenOuterBox = new G4Box(
            "tungstenOuterBox",
            outerW,
            outerW,
            outerW
        );

        G4Box* tungstenInnerBox = new G4Box(
            "tungstenInnerBox",
            innerW,
            innerW,
            innerW
        );

        G4SubtractionSolid* tungstenShell = new G4SubtractionSolid(
            "tungstenShell",
            tungstenOuterBox,
            tungstenInnerBox
        );

        G4LogicalVolume* logicalTungsten = new G4LogicalVolume(
            tungstenShell,
            tungstenMat,
            "logicalTungsten"
        );

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(0., 0., 0.),
            logicalTungsten,
            "physicalTungsten",
            logicalWorld,
            false,
            i,
            true
        );

        logicalTungsten->SetVisAttributes(tungstenVis);

        // --------------------------------------------
        // SILICON SENSOR LAYER
        // --------------------------------------------

        G4double innerSi = outerW;
        G4double outerSi = innerSi + siliconThickness;

        G4Box* siliconOuterBox = new G4Box(
            "siliconOuterBox",
            outerSi,
            outerSi,
            outerSi
        );

        G4Box* siliconInnerBox = new G4Box(
            "siliconInnerBox",
            innerSi,
            innerSi,
            innerSi
        );

        G4SubtractionSolid* siliconShell = new G4SubtractionSolid(
            "siliconShell",
            siliconOuterBox,
            siliconInnerBox
        );

        G4LogicalVolume* logicalSilicon = new G4LogicalVolume(
            siliconShell,
            siliconMat,
            "logicalSilicon"
        );

        new G4PVPlacement(
            nullptr,
        G4ThreeVector(0., 0., 0.),
            logicalSilicon,
            "physicalSilicon",
            logicalWorld,
            false,
            i,
            true
        );

        logicalSilicon->SetVisAttributes(siliconVis);
    }

    // ------------------------------------------------
    // 5. RETURN WORLD
    // ------------------------------------------------

    return physicalWorld;
}
