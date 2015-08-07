#ifndef CALOTOWERV1_H_
#define CALOTOWERV1_H_

#include "CaloTower.h"

#include <map>

class CaloTowerv1 : public CaloTower {

 public:

  CaloTowerv1();
  CaloTowerv1( const unsigned int );
  virtual ~CaloTowerv1();

  void Reset();
  int isValid() const;
  void identify(std::ostream& os=std::cout) const;

  unsigned int get_id() const { return _calotowerid; }
  float get_energy() const;

  std::pair< std::map<unsigned int,float>::const_iterator, std::map<unsigned int,float>::const_iterator > get_g4cells()
  {return make_pair(ecells.begin(), ecells.end());}

  void add_ecell(const unsigned int g4cellid, const float ecell);

 protected:
  unsigned int _calotowerid;

  std::map<unsigned int, float> ecells;

  ClassDef(CaloTowerv1,1)
};

#endif /* CALOTOWERV1_H_ */
