#include "CaloTowerv1.h"
#include <iostream>
#include <algorithm>

#include <map>

using namespace std;

ClassImp(CaloTowerv1)

CaloTowerv1::CaloTowerv1() :
  _calotowerid(0)
{}

CaloTowerv1::CaloTowerv1( const unsigned int id ) :
  _calotowerid(id)
{}

CaloTowerv1::~CaloTowerv1()
{}


void CaloTowerv1::Reset()
{
  ecells.clear();
}


int CaloTowerv1::isValid() const
{
  return get_energy() != 0;
}


void CaloTowerv1::identify(std::ostream& os) const
{
  os << "CaloTowerv1: calotowerid: " << _calotowerid << " energy=" << get_energy()  << std::endl;
}


void CaloTowerv1::add_ecell(const unsigned int g4cellid, const float ecell)
{
  if (ecells.find(g4cellid) == ecells.end())
    {
      ecells[g4cellid] = ecell;
    }
  else
    {
      ecells[g4cellid] += ecell;
    }
}


float CaloTowerv1::get_energy() const
{
  map<unsigned int, float>::const_iterator iter;
  float esum = 0;
  for (iter = ecells.begin(); iter != ecells.end(); ++iter)
    {
      esum += iter->second;
    }
  return esum;
}
