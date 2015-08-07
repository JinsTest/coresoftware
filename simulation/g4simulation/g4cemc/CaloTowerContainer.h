#ifndef CALOTOWERCONTAINER_H__
#define CALOTOWERCONTAINER_H__

#include <phool/PHObject.h>
#include <phool/phool.h>
#include <iostream>
#include <map>

class CaloTower;

class CaloTowerContainer : public PHObject
{

 public:

  typedef std::map<unsigned int,CaloTower *> Map;
  typedef Map::iterator Iterator;
  typedef Map::const_iterator ConstIterator;
  typedef std::pair<Iterator, Iterator> Range;
  typedef std::pair<ConstIterator, ConstIterator> ConstRange;

  CaloTowerContainer() {}
  virtual ~CaloTowerContainer() {}

  void Reset();
  int isValid() const;
  void identify(std::ostream& os=std::cout) const;
  ConstIterator AddTower( CaloTower *twr );
  CaloTower *getTower( const unsigned int towerid );
  //! return all towers
  ConstRange getTowers( void ) const;

  unsigned int size() const {return _towers.size();}
  void compress(const double emin);
  double getTotalEdep() const;

 protected:
  Map _towers;

  ClassDef(CaloTowerContainer,1)
};

#endif /* CALOTOWERCONTAINER_H__ */
