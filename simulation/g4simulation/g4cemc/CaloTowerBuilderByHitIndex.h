#ifndef _CALO_TOWER_BUILDER_BY_HIT_INDEX__
#define _CALO_TOWER_BUILDER_BY_HIT_INDEX__

#include <fun4all/SubsysReco.h>
#include <string>

#include <phool/PHTimeServer.h>

#include "CaloTowerID.h"

class PHCompositeNode;
class CaloTowerContainer;
class PHG4HitContainer;

/**
 * \brief SubsysReco module creating calorimeter tower objects (CaloTowerv1) from hits
 * (PHG4Hit) using j,k indeces of these hits
 *
 * \author Nils Feege <nils.feege@stonybrook.edu>
 *
 */
class CaloTowerBuilderByHitIndex : public SubsysReco {

public:

  CaloTowerBuilderByHitIndex( const std::string& name="CaloTowerBuilderByHitIndex" );
  virtual ~CaloTowerBuilderByHitIndex(){}

  int InitRun(PHCompositeNode *topNode);

  int process_event(PHCompositeNode *topNode);

  int End(PHCompositeNode *topNode);

  /** Name of the detector node the G4Hits should be taken from.
   */
  void Detector( const std::string &d , const calotowerid::CalorimeterIds calo_id )
  {
    detector_ = d;
    calo_id_ = calo_id;
  }

  /** Define minimum tower energy. After processing an event, towers with lower energy
   * are will be deleted.
   */
  void EminCut(const double e) {emin_ = e;}

protected:

  /** Create nodes for output.
   *
   * Name of output node for RawTowerContainer: "TOWER_" + detector;
   */
  void CreateNodes(PHCompositeNode *topNode);

  CaloTowerContainer* towers_;

  std::string detector_;
  std::string node_name_hits_;
  std::string node_name_towers_;

  calotowerid::CalorimeterIds calo_id_;

  double emin_;

  PHTimeServer::timer timer_;

};

#endif
