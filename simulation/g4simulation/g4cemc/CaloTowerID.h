#include <string>

/* Namespace with functions to set / extract
 * calorimeter ID , which is stored as highest 8 bits of the CaloTowerID integer.
 * This 32 bit integer uniquely identifies each tower in the whole detector- the highest eight bits
 * contain an ID for the calorimeter, and the lower 24 bits contain an ID for the tower within
 * a given calorimeter.
 */
namespace CaloTowerID
{

  /* List of available calorimeter IDs
   */
  enum Calorimeter_t {
    cECAL=1,
    cHCAL_INNER,
    cHCAL_OUTER,
    eECAL,
    hECAL,
    hHCAL,
  };


  /* binary 00000000111111111111111111111111 to set
   * calorimeter ID to 0
   */
  int caloID_zero = 16777215;


  /* Returns the local tower ID, i.e. it strips the highest 8 bits
   * which encode the calorimeter this tower is in
   */
  int GetLocalCaloTowerID( int caloTowerID ){

    return caloTowerID & caloID_zero;

  }


  /* Returns new CaloTowerID with the highest 8 bits set to encode
   * given calorimeter
   */
  int SetCalorimeter( int caloTowerID , Calorimeter_t caloID ){

    // shift caloID by 24 bits
    int caloID_shift = caloID << 24;

    // clear old calorimeter ID
    int caloTowerID_new = caloTowerID & CaloTowerID::caloID_zero;

    // set new calorimeter ID
    caloTowerID_new = caloTowerID_new | caloID_shift;

    return caloTowerID_new;

  }


  /* Extract ID number of calorimeter from CaloTowerID
   */
  int GetCalorimeter( int caloTowerID ){

    // make 8 bits of calorimeter ID the lowest 8 bits of this integer
    return caloTowerID >> 24;

  }


  /* Extract name of calorimeter from CaloTowerID
   */
  std::string GetCalorimeterName( int caloTowerID ){

    int caloid = CaloTowerID::GetCalorimeter( caloTowerID );

    switch ( caloid ){

    case cECAL:
      return "cECAL";
      break;

    case cHCAL_INNER:
      return "cHCAL_INNER";
      break;

    case cHCAL_OUTER:
      return "cHCAL_OUTER";
      break;

    case eECAL:
      return "eECAL";
      break;

    case hECAL:
      return "hECAL";
      break;

    case hHCAL:
      return "hHCAL";
      break;

    default:
      return "NONE";

    }

  }

};
