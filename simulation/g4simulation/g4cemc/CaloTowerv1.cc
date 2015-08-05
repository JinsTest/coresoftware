#include "CaloTowerv1.h"
#include <iostream>
#include <algorithm>

#include <map>

using namespace std;

ClassImp(CaloTowerv1)

CaloTowerv1::CaloTowerv1() : 
  bineta(-1), 
  binphi(-1)
{}

CaloTowerv1::CaloTowerv1(const int ieta, const int iphi) :
  bineta(ieta),
  binphi(iphi)
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
  os << "CaloTowerv1: etabin: " << bineta << ", phibin: " << binphi 
     << " energy=" << get_energy() << std::endl;
}

bool CaloTowerv1::is_adjacent(CaloTower& tower)
{
  if (bineta - 1 <= tower.get_bineta() && tower.get_bineta() <= bineta + 1)
    {
      if (binphi - 1 <= tower.get_binphi() && tower.get_binphi() <= binphi + 1)
        {
          return true;
        }
      // cluster through the phi-wraparound
      //       else if(((tower.get_binphi() == _nphi-1) && (binphi == 0)) ||
      // 	      ((tower.get_binphi() == 0) && (binphi == _nphi-1)))
      // 	{
      // 	  return true;
      // 	}
    }

  return false;
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

