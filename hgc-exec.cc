
#include <iostream>

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExtent.hh"
#include "G4SystemOfUnits.hh"
#include "FTFP_BERT.hh"

#include "hgcaldetector.hh"
#include "actioninit.hh"
#include "beamvisaction.hh"

int main(int argc, char** argv)
{
    // Create the Geant4 run manager
    G4RunManager* runManager = new G4RunManager();

    // Register detector geometry
    runManager->SetUserInitialization(
        new HGCALDetectorConstruction()
    );

    // Register physics list
    runManager->SetUserInitialization(
        new FTFP_BERT()
    );

    // Initialise user actions
    runManager->SetUserInitialization(
        new ActionInitialization()
    );

    // Initialise Geant4
    runManager->Initialize();

    // Create and initialise visualisation manager
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Register incoming proton beam visualization
    visManager->RegisterEndOfEventUserVisAction(
        "BeamVisAction",
        new BeamVisAction(),
        G4VisExtent(
            -40. * m, 40. * m,
            -40. * m, 40. * m,
            -40. * m, 40. * m
        )
    );

    // Create user interface
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    // Get UI manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Open visualisation window
    UImanager->ApplyCommand("/vis/open OGL");

    // Draw detector geometry
    UImanager->ApplyCommand("/vis/drawVolume");

    // Add incoming proton beam paths to visualization
    UImanager->ApplyCommand(
        "/vis/scene/add/userAction BeamVisAction"
    );

    // Set viewing direction
    UImanager->ApplyCommand(
        "/vis/viewer/set/viewpointVector -1 -1 1"
    );

    // Display smooth particle trajectories
    UImanager->ApplyCommand(
        "/vis/scene/add/trajectories smooth"
    );

    UImanager->ApplyCommand(
        "/vis/modeling/trajectories/list"
    );

    // Enable automatic refresh
    UImanager->ApplyCommand(
        "/vis/viewer/set/autoRefresh true"
    );

    // Add scale
    UImanager->ApplyCommand(
        "/vis/scene/add/scale 2 m"
    );

    // Add coordinate axes
    // UImanager->ApplyCommand("/vis/scene/add/axes");

    // Start interactive session
    ui->SessionStart();

    // Clean up
    delete ui;
    delete visManager;
    delete runManager;

    return 0;
}
