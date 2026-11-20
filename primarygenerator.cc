
#include "primarygenerator.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Exception.hh"

#include <iostream>
#include <iomanip>

// Constructor
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Create particle gun
    particleGun = new G4ParticleGun(1);

    // Define proton-proton collision
    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");

    // Beam energies in GeV
    pythia.readString("Beams:frameType = 2");
    pythia.readString("Beams:eA = 100.938");
    pythia.readString("Beams:eB = 100.938");

    // Enable inelastic soft QCD interactions
    pythia.readString("SoftQCD:inelastic = on");

    // Initialize PYTHIA
    if (!pythia.init())
    {
        G4Exception(
            "PrimaryGeneratorAction::PrimaryGeneratorAction",
            "PYTHIA_INIT",
            FatalException,
            "PYTHIA initialization failed."
        );
    }

    std::cout << "PYTHIA initialized successfully."
              << std::endl;

    // Open CSV output file
    particleFile.open("particles.csv");

    if (!particleFile.is_open())
    {
        G4Exception(
            "PrimaryGeneratorAction::PrimaryGeneratorAction",
            "CSV_OPEN",
            FatalException,
            "Could not open particles.csv."
        );
    }

    // Write CSV header
    particleFile
        << "event_id,pythia_index,particle_name,pdg_id,"
        << "px_GeV,py_GeV,pz_GeV,pt_GeV,"
        << "total_energy_GeV,mass_GeV,kinetic_energy_GeV,"
        << "geant4_supported"
        << std::endl;
}

// Destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleGun;

    if (particleFile.is_open())
    {
        particleFile.close();
    }
}

// Generate primary particles
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Generate one proton-proton collision
    if (!pythia.next())
    {
        std::cerr << "PYTHIA event generation failed."
                  << std::endl;
        return;
    }

    // Access Geant4 particle table
    G4ParticleTable* particleTable =
        G4ParticleTable::GetParticleTable();

    // Get Geant4 event number
    G4int eventID = anEvent->GetEventID();

    // Loop over PYTHIA event record
    for (int i = 0; i < pythia.event.size(); ++i)
    {
        // Select final-state particles only
        if (!pythia.event[i].isFinal())
            continue;

        // Get particle information from PYTHIA
        G4int pdgID = pythia.event[i].id();

        G4double px = pythia.event[i].px();
        G4double py = pythia.event[i].py();
        G4double pz = pythia.event[i].pz();

        G4double pt = pythia.event[i].pT();

        G4double totalEnergy = pythia.event[i].e();
        G4double mass = pythia.event[i].m();

        G4double kineticEnergy = totalEnergy - mass;

        G4String particleName = pythia.event[i].name();

        // Check whether Geant4 recognises this particle
        G4ParticleDefinition* particle =
            particleTable->FindParticle(pdgID);

        G4int geant4Supported = (particle != nullptr) ? 1 : 0;

        // -----------------------------------------
        // Save particle information to CSV
        // -----------------------------------------

        particleFile
            << eventID << ","
            << i << ","
            << particleName << ","
            << pdgID << ","
            << std::setprecision(10)
            << px << ","
            << py << ","
            << pz << ","
            << pt << ","
            << totalEnergy << ","
            << mass << ","
            << kineticEnergy << ","
            << geant4Supported
            << "\n";

        // -----------------------------------------
        // Transfer particles to Geant4
        // -----------------------------------------

        // Skip particles not available in Geant4
        if (particle == nullptr)
            continue;

        // Convert momentum components to Geant4 units
        G4ThreeVector momentum(
            px * GeV,
            py * GeV,
            pz * GeV
        );

        // Skip zero-momentum particles
        if (momentum.mag() == 0.)
            continue;

        // Skip negative kinetic energy
        if (kineticEnergy < 0.)
            continue;

        // Set particle properties
        particleGun->SetParticleDefinition(particle);

        particleGun->SetParticlePosition(
            G4ThreeVector(0., 0., 0.)
        );

        particleGun->SetParticleMomentumDirection(
            momentum.unit()
        );

        particleGun->SetParticleEnergy(
            kineticEnergy * GeV
        );

        // Inject particle into Geant4 event
        particleGun->GeneratePrimaryVertex(anEvent);
    }

    // Ensure event information is written to disk
    particleFile.flush();
}
