#ifndef PHG4ForwardEcalSubsystem_h
#define PHG4ForwardEcalSubsystem_h

#include <g4main/PHG4Subsystem.h>

#include <Geant4/G4Types.hh>
#include <Geant4/G4String.hh>

class PHG4ForwardEcalDetector;
class PHG4ForwardEcalSteppingAction;
class PHG4EventAction;

class PHG4ForwardEcalSubsystem: public PHG4Subsystem
{

public:

  /** Constructor
   */
  PHG4ForwardEcalSubsystem( const std::string &name = "FORWARD_ECAL_DEFAULT", const int layer = 0 );

  /** Destructor
   */
  virtual ~PHG4ForwardEcalSubsystem( void )
  {}

  /**
     Creates the detector_ object and place it on the node tree, under "DETECTORS" node (or whatever)
     Creates the stepping action and place it on the node tree, under "ACTIONS" node
     Creates relevant hit nodes that will be populated by the stepping action and stored in the output DST
  */
  int Init(PHCompositeNode *);

  /** Event processing
   */
  int process_event(PHCompositeNode *);

  /** Accessors (reimplemented)
   */
  virtual PHG4Detector* GetDetector( void ) const;
  virtual PHG4SteppingAction* GetSteppingAction( void ) const;

  /** Set mapping file for calorimeter towers
   */
  void SetTowerMappingFile( std::string filename )
  {
    mappingfile_ = filename;
  }

private:

  /** Pointer to the Geant4 implementation of the detector
   */
  PHG4ForwardEcalDetector* detector_;

  /** Stepping action
   */
  PHG4ForwardEcalSteppingAction* steppingAction_;
  PHG4EventAction *eventAction_;

  int active;

  std::string detector_type;
  std::string mappingfile_;

};

#endif
