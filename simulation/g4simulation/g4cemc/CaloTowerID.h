#include <string>

/*! Namespace with functions to set / extract
 * calorimeter ID , which is stored as highest 8 bits of the CaloTowerID integer.
 * This 32 bit integer uniquely identifies each tower in the whole detector- the highest eight bits
 * contain an ID for the calorimeter, and the lower 24 bits contain an ID for the tower within
 * a given calorimeter.
 *
 * \author Nils Feege <nils.feege@stonybrook.edu>
 *
 */
namespace calotowerid
{

  /*! List of available calorimeter IDs.
   * This enum can be safely extended up to 254 entries total but NO ALTERATIONS of existing entries.
   * '0' is effectively reserved for 'no calorimeter defined' which should not happen when you run the code-
   * each tower is to be in SOME calorimeter.
   */
  enum CalorimeterIds {
    CEMC=1,
    HCALOUT,
    HCALIN,
    EEMC,
    HEMC,
    HHCAL,
  };


  /*! binary 0000 0000 1111 1111 1111 1111 1111 1111 to set
   * calorimeter ID to 0
   */
  const unsigned int kCaloIdZeroMask = 16777215;

  /*! binary 1111 1111 0000 0000 0000 0000 0000 0000 to mask
   * everything but CaloTowerID
   */
  const unsigned int kCaloIdMask = 4278190080;

  /*! binary 0000 0000 1111 1111 1111 0000 0000 0000 to mask
   * everything but tower index 1
   */
  const unsigned int kTowerIndex1Mask = 16773120;

  /*! binary 0000 0000  0000 0000 0000 1111 1111 1111 to mask
   * everything but tower index 2
   */
  const unsigned int kTowerIndex2Mask = 4095;

  /*! Returns the local tower ID, i.e. it strips the highest 8 bits
   * which encode the calorimeter this tower is in
   */
  unsigned int StripCalorimeterId( const unsigned int calo_tower_id ){

    return calo_tower_id & calotowerid::kCaloIdZeroMask;

  }


  /*! Returns new CaloTowerID with the highest 8 bits set to encode
   * given calorimeter
   */
  unsigned int ChangeCalorimeterId( const unsigned int calo_tower_it , const CalorimeterIds calo_id ){

    // shift caloID by 24 bits
    unsigned int calo_id_shift = calo_id << 24;

    // clear old calorimeter ID
    unsigned int calo_tower_id_new = calo_tower_id & calotowerid::kCaloIdZeroMask;

    // set new calorimeter ID
    calo_tower_id_new = calo_tower_id_new | calo_id_shift;

    return calo_tower_id_new;

  }


  /*! Extract ID number of calorimeter from CaloTowerID
   */
  unsigned int DecodeCalorimeterId( const unsigned int calo_tower_id ){

    // make 8 bits of calorimeter ID the lowest 8 bits of this integer
    return calo_tower_id & calotowerid::kCaloIdMask;

  }


  /*! Extract index 1 of calorimeter tower from CaloTowerID
   */
  unsigned int DecodeTowerIndex1( const unsigned int calo_tower_id ){

    // make 8 bits of calorimeter ID the lowest 8 bits of this integer
    return calo_tower_id & calotowerid::kTowerIndex1Mask;

  }


  /*! Extract index 2 of calorimeter tower from CaloTowerID
   */
  unsigned int DecodeTowerIndex2( const unsigned int calo_tower_id ){

    // make 8 bits of calorimeter ID the lowest 8 bits of this integer
    return calo_tower_id & calotowerid::kTowerIndex2Mask;

  }


  /*! Extract name of calorimeter from CaloTowerID
   */
  std::string DecodeCalorimeterName( const unsigned int calo_tower_id ){

    unsigned int calo_id = calotowerid::DecodeCalorimeterId( calo_tower_id );

    switch ( calo_id ){

    case CEMCL:
      return "CEMC";
      break;

    case HCALIN:
      return "HCALIN";
      break;

    case HCALOUT:
      return "HCALOUT";
      break;

    case EEMC:
      return "EEMC";
      break;

    case HEMC:
      return "HEMC";
      break;

    case HHCAL:
      return "HHCAL";
      break;

    default:
      return "NONE";

    }

  }


  /*! Returns CaloTowerID for given CalirometerID, index 1, and index 2 of tower
   */
  unsigned int Encode( const CalorimeterIds calo_id , const unsigned int tower_index_1 = 0 , const unsigned int tower_index_2 = 0){

    unsigned int calo_tower_id = 0;

    // shift caloID by 24 bits
    unsigned int calo_id_shift = calo_id << 24;

    // shift tower_index_1 by 12 bits
    unsigned int tower_index_1_shift = tower_index_1 << 12;

    // shift tower_index_2 by 0 bits
    unsigned int tower_index_2_shift = tower_index_2 << 0;

    // encode calorimeter ID
    calo_tower_id = calo_tower_id | calo_id_shift;
    calo_tower_id = calo_tower_id | tower_index_1_shift;
    calo_tower_id = calo_tower_id | tower_index_2_shift;

    return calo_tower_id;

  }

};
