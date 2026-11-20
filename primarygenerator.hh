
#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

#include "Pythia8/Pythia.h"

#include <fstream>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:

    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event* anEvent) override;

private:

    G4ParticleGun* particleGun;

    // PYTHIA event generator
    Pythia8::Pythia pythia;

    // Output file for PYTHIA final-state particles
    std::ofstream particleFile;
};

#endif
