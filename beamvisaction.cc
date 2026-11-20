
#include "beamvisaction.hh"

#include "G4VVisManager.hh"
#include "G4Polyline.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Point3D.hh"
#include "G4SystemOfUnits.hh"

BeamVisAction::BeamVisAction()
{}

BeamVisAction::~BeamVisAction()
{}

void BeamVisAction::Draw()
{
    G4VVisManager* visManager =
        G4VVisManager::GetConcreteInstance();

    if (!visManager)
        return;

    // Blue line attributes
    G4VisAttributes beamAttributes(
        G4Colour(0.0, 0.0, 1.0)
    );

    beamAttributes.SetLineWidth(5.0);

    // First incoming beam: -40 m to origin
    G4Polyline beam1;

    beam1.push_back(
        G4Point3D(0., 0., -40. * m)
    );

    beam1.push_back(
        G4Point3D(0., 0., 0.)
    );

    beam1.SetVisAttributes(beamAttributes);

    // Second incoming beam: +40 m to origin
    G4Polyline beam2;

    beam2.push_back(
        G4Point3D(0., 0., 40. * m)
    );

    beam2.push_back(
        G4Point3D(0., 0., 0.)
    );

    beam2.SetVisAttributes(beamAttributes);

    // Draw both incoming beam paths
    visManager->Draw(beam1);
    visManager->Draw(beam2);
}
