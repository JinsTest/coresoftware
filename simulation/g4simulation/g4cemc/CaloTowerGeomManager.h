#ifndef CALO_TOWER_GEOM_MANAGER__
#define CALO_TOWER_GEOM_MANAGER__

#include <phool/PHObject.h>
#include <phool/phool.h>

#include <TObject.h>

#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "CaloTowerID.h"

struct position {
  float x;
  float y;
  float z;
};

/** \brief Singleton giving access to CaloTower geometry information like position of tower center.
 *
 * \author Nils Feege <nils.feege@stonybrook.edu>
 *
 */
class CaloTowerGeomManager : public TObject {

public:

  ///! Return pointer to CaloTowerGeomManager instance
  static CaloTowerGeomManager* instance()
  {
    if ( ! CaloTowerGeomManager::instance_ )
      CaloTowerGeomManager::instance_ = new CaloTowerGeomManager();

    return CaloTowerGeomManager::instance_;
  }

  ///! Return cartesian position of tower center
  bool GetPositionXYZ ( const unsigned int, float &, float &, float &);

  ///! Return vector of neighboring towers
  std::vector< unsigned int > GetNeighbors( const unsigned int );

  ///! Read tower geometry from table / ascii file
  bool ReadGeometryFromTable( calotowerid::CalorimeterIds , std::string );

private:
  ///! Return vector of neighboring towers for forward calorimeter (EEMC, FEMC, FHCAL)
  std::vector< unsigned int > GetNeighborsFwdCal( const unsigned int );

  ///! Read tower geometry from table / ascii file for forward calorimeter (EEMC, FEMC, FHCAL)
  bool ReadGeometryFromTableFwdCal( calotowerid::CalorimeterIds , std::string );

  ///! Private constructor
  CaloTowerGeomManager(){}

  CaloTowerGeomManager(CaloTowerGeomManager const&); // Not Implemented

  void operator=(CaloTowerGeomManager const&); // Not Implemented

  ///! Pointer to only instance of CaloTowerGeomManager
  static CaloTowerGeomManager* instance_;

  ///! Map associating position struct to calo tower id
  std::map< unsigned int , position > _map_towers;

};

#endif
