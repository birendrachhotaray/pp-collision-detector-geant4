#include "actioninit.hh"

#include "primarygenerator.hh"

// Constructor
ActionInitialization::ActionInitialization()
{
}

// Destructor
ActionInitialization::~ActionInitialization()
{
}

// Register user actions
void ActionInitialization::Build() const
{
    // Primary particle generator
    SetUserAction(new PrimaryGeneratorAction());
}
