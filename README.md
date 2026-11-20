# PYTHIA-Geant4 Proton-Proton Collision Simulation

## About the Project

This project combines PYTHIA 8 and Geant4 to simulate proton-proton collisions and study the transport and interaction of produced particles inside a detector.

PYTHIA generates the collision and its final-state particles. These particles are subsequently transferred to Geant4, which simulates their propagation and interactions with detector materials.

The detector currently consists of nested cubic layers of tungsten and silicon, forming a simple sampling calorimeter around the collision point.

## Current Features

- Proton-proton collision generation using PYTHIA 8.
- Proton beam energy of 100.938 GeV per beam.
- Transfer of PYTHIA-generated final-state particles to Geant4.
- Particle transport and interactions with detector materials.
- Nested cubic tungsten-silicon detector geometry.
- Visualization of particle trajectories and detector geometry.
- Adjustable number of detector layers.

## Detector Geometry

The detector consists of alternating layers of:

- Tungsten (W): Absorber material.
- Silicon (Si): Active material.

The current configuration contains 10 tungsten-silicon layer pairs. The number of layers can be modified according to the requirements of the simulation.

The detector is positioned around the collision point at the centre of the simulation world.

## Requirements

- Geant4 with visualization support
- PYTHIA 8
- CMake
- C++ compiler

## Compilation

Clone the repository and enter the project directory:

```bash
git clone https://github.com/birendrachhotaray/pp-collision-detector-geant4.git
cd pp-collision-detector-geant4
```

Create a build directory and configure the project:

```bash
mkdir build
cd build
cmake ..
```

Compile the simulation:

```bash
cmake --build . -j$(nproc)
```

## Running the Simulation

From the build directory, execute:

```bash
./G-space-suit
```

## Future Development

This project is currently under development. Future work will focus on energy-deposition measurements, layer-wise energy analysis, particle shower studies, detector response investigations, and further development and optimization of the detector geometry.
