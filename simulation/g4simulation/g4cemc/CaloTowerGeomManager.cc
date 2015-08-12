#include "CaloTowerGeomManager.h"

#include "CaloTowerID.h"

#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

// initialize static member variable
CaloTowerGeomManager* CaloTowerGeomManager::instance_ = NULL;


//___________________________________________________________________________
bool CaloTowerGeomManager::GetPositionXYZ ( const unsigned int towerid, float &x, float &y, float &z) {

  x = y = z = 0;

  std::map< unsigned int, position >::iterator map_it;

  map_it = _map_towers.find( towerid );
  if ( map_it != _map_towers.end() )
    {
      x = map_it->second.x;
      y = map_it->second.y;
      z = map_it->second.z;

      return true;
    }

  return false;

}


//___________________________________________________________________________
bool CaloTowerGeomManager::ReadGeometryFromTable( const calotowerid::CalorimeterIds calo_id , const string mapping_tower_file ) {

  switch ( calo_id ){

  case calotowerid::NONE:
    return false;
    break;

  case calotowerid::CEMC:
    return false;
    break;

  case calotowerid::HCALIN:
    return false;
    break;

  case calotowerid::HCALOUT:
    return false;
    break;

  case calotowerid::EEMC:
    return ReadGeometryFromTableFwdCal( calo_id , mapping_tower_file );
    break;

  case calotowerid::FEMC:
    return ReadGeometryFromTableFwdCal( calo_id , mapping_tower_file );
    break;

  case calotowerid::FHCAL:
    return ReadGeometryFromTableFwdCal( calo_id , mapping_tower_file );
    break;

  default:
    return false;

  }

}


//___________________________________________________________________________
bool CaloTowerGeomManager::ReadGeometryFromTableFwdCal( const calotowerid::CalorimeterIds calo_id , const string mapping_tower_file ) {

  /* Stream to read table from file */
  ifstream istream_mapping;

  /* Open the datafile, if it won't open return an error */
  if (!istream_mapping.is_open())
    {
      istream_mapping.open( mapping_tower_file.c_str() );
      if(!istream_mapping)
	{
	  cerr << "CaloTowerGeomManager::ReadGeometryFromTable - ERROR Failed to open mapping file " << mapping_tower_file << endl;
	  exit(1);
	}
    }

  string line_mapping;

  while ( getline( istream_mapping, line_mapping ) )
    {

      unsigned idx_j, idx_k, idx_l;
      float pos_x, pos_y, pos_z;
      float dummy;

      istringstream iss(line_mapping);

      /* Skip lines starting with / including a '#' */
      if ( line_mapping.find("#") != string::npos )
	{
	  continue;
	}

      /* read string- break if error */
      if ( !( iss >> idx_j >> idx_k >> idx_l >> pos_x >> pos_y >> pos_z >> dummy >> dummy >> dummy >> dummy ) )
	{
	  cerr << "CaloTowerGeomManager::ReadGeometryFromTable - ERROR Failed to read line in mapping file " << mapping_tower_file << endl;
	  exit(1);
	}

      /* Construct unique Tower ID */
      unsigned int temp_id = calotowerid::Encode( calo_id , idx_j , idx_k );

      /* Position */
      pos_z += 415;
      position temp_pos { pos_x, pos_y, pos_z };

      /* Insert this tower into position map */
      _map_towers.insert( pair< unsigned int , position >( temp_id , temp_pos ) );
    }

  return true;

}



