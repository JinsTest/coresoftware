#ifndef CALOTOWERV1_H_
#define CALOTOWERV1_H_

#include "CaloTower.h"

#include <map>

class CaloTowerv1 : public CaloTower {

 public:
  CaloTowerv1();
  CaloTowerv1(const int ieta, const int iphi);
  virtual ~CaloTowerv1();

  void Reset();
  int isValid() const;
  void identify(std::ostream& os=std::cout) const;

  int get_bineta() const { return bineta; }
  int get_binphi() const { return binphi; }
  float get_energy() const;

  bool is_adjacent(CaloTower& tower);

  std::pair< std::map<unsigned int,float>::const_iterator, std::map<unsigned int,float>::const_iterator > get_g4cells()
  {return make_pair(ecells.begin(), ecells.end());}
  void add_ecell(const unsigned int g4cellid, const float ecell);

 protected:
  int bineta;
  int binphi;

  std::map<unsigned int, float> ecells;

  ClassDef(CaloTowerv1,1)
};

#endif /* CALOTOWERV1_H_ */
