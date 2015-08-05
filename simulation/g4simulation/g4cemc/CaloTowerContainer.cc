#include "CaloTowerContainer.h"
#include "CaloTower.h"

#include <cstdlib>
#include <iostream>

ClassImp(CaloTowerContainer)

using namespace std;

unsigned int
CaloTowerContainer::genkey(const unsigned int ieta, const unsigned int iphi) const
{
  if (ieta > 0xFFFF || iphi > 0xFFFF)
    {
      cout << "ieta " << ieta << " or iphi " << iphi 
	   << " exceed max length of " << 0xFFFF << endl;
      cout << "reconsider the generation of unique keys" << endl;
      exit(1);
    }
  unsigned int key = 0;
  key |= (ieta << 16);
  key |= iphi;
  return key;
}

void 
CaloTowerContainer::compress(const double emin)
{
  if (emin <= 0) // no need to loop through the map if we don't apply a cut
    {
      return;
    }
  std::map<unsigned int, CaloTower*>::iterator itr = _towers.begin();
  std::map<unsigned int, CaloTower*>::iterator last = _towers.end();
  for (; itr != last; )
    {
      CaloTower *tower = (itr->second);
      if (tower->get_energy() < emin)
        {
	  delete tower;
          _towers.erase(itr++);
        }
      else
        {
          ++itr;
        }
    }
}

CaloTowerContainer::ConstRange
CaloTowerContainer::getTowers( void ) const
{
  return make_pair(_towers.begin(), _towers.end());
}

CaloTowerContainer::ConstIterator
CaloTowerContainer::AddTower(const int ieta, const int iphi, CaloTower *rawtower)
{
  unsigned int key = genkey(ieta,iphi);
  _towers[key] = rawtower;
  return _towers.find(key);
}

CaloTower *
CaloTowerContainer::getTower(const int ieta, const int iphi)
{
  unsigned int key = genkey(ieta,iphi);
  Iterator it = _towers.find(key);
  if (it != _towers.end())
    {
      return it->second;
    }
  return NULL;
}

int 
CaloTowerContainer::isValid() const
{
  return (!_towers.empty());
}

void
CaloTowerContainer::Reset()
{
  while (_towers.begin() != _towers.end())
    {
      delete _towers.begin()->second;
      _towers.erase(_towers.begin());
    }
}

void 
CaloTowerContainer::identify(std::ostream& os) const
{
  os << "CaloTowerContainer, number of towers: " << size() << std::endl;
}

double
CaloTowerContainer::getTotalEdep() const
{
  double totalenergy = 0;
  ConstIterator iter;
  for (iter = _towers.begin(); iter != _towers.end(); ++iter)
    {
      totalenergy += iter->second->get_energy();
    }
  return totalenergy;
}
