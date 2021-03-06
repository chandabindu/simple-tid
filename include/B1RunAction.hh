#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class B1RunAction : public G4UserRunAction
{
public:
  B1RunAction();
  virtual ~B1RunAction();

  // virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);

  void AddEdep (std::vector<G4double> edep); 

private:
  G4Accumulable<G4double> fEdepF;
  G4Accumulable<G4double> fEdepF2;
  G4Accumulable<G4double> fEdepB;
  G4Accumulable<G4double> fEdepB2;
  G4Accumulable<G4double> fEdepM;
  G4Accumulable<G4double> fEdepM2;
};

#endif

