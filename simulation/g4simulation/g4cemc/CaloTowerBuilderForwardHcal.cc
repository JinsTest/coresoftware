#include "CaloTowerBuilderForwardHcal.h"

#include "CaloTowerID.h"
#include "CaloTowerContainer.h"
#include "CaloTowerv1.h"

#include <g4main/PHG4Hit.h>
#include <g4main/PHG4HitContainer.h>

#include <phool/PHCompositeNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/PHIODataNode.h>

#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/getClass.h>

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <map>

using namespace std;

CaloTowerBuilderForwardHcal::CaloTowerBuilderForwardHcal(const std::string& name):
  SubsysReco(name),
  _towers(NULL),
  detector("CRYSTALCALO"),
  emin(1e-6),
  _timer( PHTimeServer::get()->insert_new(name) )
{}

int
CaloTowerBuilderForwardHcal::InitRun(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode;
  dstNode = dynamic_cast<PHCompositeNode*>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
    {
      std::cout << PHWHERE << "DST Node missing, doing nothing." << std::endl;
      exit(1);
    }

  try
    {
      CreateNodes(topNode);
    }
  catch (std::exception& e)
    {
      std::cout << e.what() << std::endl;
      //exit(1);
    }
  return Fun4AllReturnCodes::EVENT_OK;
}

int
CaloTowerBuilderForwardHcal::process_event(PHCompositeNode *topNode)
{
  // get hits
  hitnodename = "G4HIT_" + detector;
  PHG4HitContainer *g4hit = findNode::getClass<PHG4HitContainer>(topNode, hitnodename.c_str());
  if (!g4hit)
    {
      cout << "Could not locate g4 hit node " << hitnodename << endl;
      exit(1);
    }

  // loop over all hits in the event
  PHG4HitContainer::ConstIterator hiter;
  PHG4HitContainer::ConstRange hit_begin_end = g4hit->getHits();

  for (hiter = hit_begin_end.first; hiter != hit_begin_end.second; hiter++)
    {
      PHG4Hit* g4hit_i =  hiter->second ;

      /* encode CaloTowerID from j, k index of tower / hit and calorimeter ID */
      unsigned int calotowerid = calotowerid::Encode( calotowerid::HHCAL ,
						      g4hit_i->get_index_j() ,
						      g4hit_i->get_index_k() );

      /* add the energy to the corresponding tower */
      CaloTowerv1 *tower = dynamic_cast<CaloTowerv1 *> (_towers->getTower( calotowerid ));
      if (! tower)
        {
          tower = new CaloTowerv1( calotowerid );
          _towers->AddTower( tower );
        }
      tower->add_ecell(g4hit_i->get_trkid(), g4hit_i->get_edep());
    }

  float towerE = 0.;

  if (verbosity)
    {
      towerE = _towers->getTotalEdep();
    }

  _towers->compress(emin);
  if (verbosity)
    {
      cout << "Energy lost by dropping towers with less than "
           << emin << " energy, lost energy: "  << towerE - _towers->getTotalEdep() << endl;
      _towers->identify();
      CaloTowerContainer::ConstRange begin_end = _towers->getTowers();
      CaloTowerContainer::ConstIterator iter;
      for (iter =  begin_end.first; iter != begin_end.second; ++iter)
        {
          iter->second->identify();
        }
    }

  return Fun4AllReturnCodes::EVENT_OK;
}

int
CaloTowerBuilderForwardHcal::End(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

void
CaloTowerBuilderForwardHcal::CreateNodes(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);
  PHCompositeNode *runNode = static_cast<PHCompositeNode*>(iter.findFirst("PHCompositeNode", "RUN"));
  if (!runNode)
    {
      std::cerr << PHWHERE << "Run Node missing, doing nothing." << std::endl;
      throw std::runtime_error("Failed to find Run node in CaloTowerBuilderForwardHcal::CreateNodes");
    }

  PHCompositeNode *dstNode = static_cast<PHCompositeNode*>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
    {
      std::cerr << PHWHERE << "DST Node missing, doing nothing." << std::endl;
      throw std::runtime_error("Failed to find DST node in CaloTowerBuilderForwardHcal::CreateNodes");
    }

  // Create the tower nodes on the tree
  _towers = new CaloTowerContainer();
  TowerNodeName = "TOWER_" + detector;

  PHIODataNode<PHObject> *towerNode = new PHIODataNode<PHObject>(_towers, TowerNodeName.c_str(), "PHObject");
  dstNode->addNode(towerNode);

  return;
}
