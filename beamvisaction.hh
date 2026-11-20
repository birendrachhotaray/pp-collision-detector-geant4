
#ifndef BEAMVISACTION_HH
#define BEAMVISACTION_HH

#include "G4VUserVisAction.hh"

class BeamVisAction : public G4VUserVisAction
{
public:
    BeamVisAction();
    ~BeamVisAction() override;

    void Draw() override;
};

#endif
