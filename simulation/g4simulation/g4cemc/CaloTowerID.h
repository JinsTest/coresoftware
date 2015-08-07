#ifndef CALOTOWERID_H__
#define CALOTOWERID_H__

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
   *
   * If you ADD a new CalorimeterID, please add it also to the DecodeCalorimeterName function below.
   */
  enum CalorimeterIds {
    NONE,
    CEMC,
    HCALOUT,
    HCALIN,
    EEMC,
    FEMC,
    FHCAL,
  };

  /*! Bit shift left << for encoding calorimeter id
   */
  const unsigned int kBitShiftCaloId = 24;

  /*! Bit shift left << for encoding tower index 1
   */
  const unsigned int kBitShiftTowerIndex1 = 12;

  /*! Bit shift left << for encoding tower index 2
   */
  const unsigned int kBitShiftTowerIndex2 = 0;

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


  /*! Returns CaloTowerID for given CalirometerID, index 1, and index 2 of tower
   */
  inline unsigned int Encode( const CalorimeterIds calo_id , const unsigned int tower_index_1 = 0 , const unsigned int tower_index_2 = 0){

    unsigned int calo_tower_id = 0;

    // shift caloID by 24 bits
    unsigned int calo_id_shift = calo_id << calotowerid::kBitShiftCaloId;

    // shift tower_index_1 by 12 bits
    unsigned int tower_index_1_shift = tower_index_1 << calotowerid::kBitShiftTowerIndex1;

    // shift tower_index_2 by 0 bits
    unsigned int tower_index_2_shift = tower_index_2 << calotowerid::kBitShiftTowerIndex2;

    // encode calorimeter ID
    calo_tower_id = calo_tower_id | calo_id_shift;
    calo_tower_id = calo_tower_id | tower_index_1_shift;
    calo_tower_id = calo_tower_id | tower_index_2_shift;

    return calo_tower_id;

  }


  /*! Extract ID number of calorimeter from CaloTowerID
   */
  inline unsigned int DecodeCalorimeterId( const unsigned int calo_tower_id ){

    return ( calo_tower_id & calotowerid::kCaloIdMask ) >> calotowerid::kBitShiftCaloId;

  }


  /*! Extract index 1 of calorimeter tower from CaloTowerID
   */
  inline unsigned int DecodeTowerIndex1( const unsigned int calo_tower_id ){

    return ( calo_tower_id & calotowerid::kTowerIndex1Mask ) >> calotowerid::kBitShiftTowerIndex1;

  }


  /*! Extract index 2 of calorimeter tower from CaloTowerID
   */
  inline unsigned int DecodeTowerIndex2( const unsigned int calo_tower_id ){

    return ( calo_tower_id & calotowerid::kTowerIndex2Mask ) >> calotowerid::kBitShiftTowerIndex2;

  }


  /*! Extract name of calorimeter from CaloTowerID
   */
  inline std::string DecodeCalorimeterName( const unsigned int calo_tower_id ){

    unsigned int calo_id = calotowerid::DecodeCalorimeterId( calo_tower_id );

    switch ( calo_id ){

    case NONE:
      return "NONE";
      break;

    case CEMC:
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

    case FEMC:
      return "FEMC";
      break;

    case FHCAL:
      return "FHCAL";
      break;

    default:
      return "unknown";

    }

  }


  /*! Returns new CaloTowerID with the highest 8 bits set to encode
   * given calorimeter
   */
  inline unsigned int ChangeCalorimeterId( const unsigned int calo_tower_id , const CalorimeterIds calo_id ){

    // shift caloID
    unsigned int calo_id_shift = calo_id << calotowerid::kBitShiftCaloId;

    // clear old calorimeter ID
    unsigned int calo_tower_id_new = calo_tower_id & calotowerid::kCaloIdZeroMask;

    // set new calorimeter ID
    calo_tower_id_new = calo_tower_id_new | calo_id_shift;

    return calo_tower_id_new;

  }

};

#endif
