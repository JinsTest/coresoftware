#ifndef RAWCLUSTERBUILDER_H__
#define RAWCLUSTERBUILDER_H__

#include <fun4all/SubsysReco.h>
#include <string>

class PHCompositeNode;
class RawCluster;
class RawClusterContainer;
class RawTowerContainer;
class RawTowerGeomContainer;

class RawClusterBuilder : public SubsysReco {

 public:
  RawClusterBuilder(const std::string& name = "RawClusterBuilder"); 
  virtual ~RawClusterBuilder() {}

  int InitRun(PHCompositeNode *topNode);
  int process_event(PHCompositeNode *topNode);
  int End(PHCompositeNode *topNode);
  void Detector(const std::string &d) {detector = d;}

  void set_threshold_energy(const float e) {_min_tower_e = e;}
  void checkenergy(const int i = 1) {chkenergyconservation = i;}

 private:
  void CreateNodes(PHCompositeNode *topNode);
  bool CorrectPhi(RawCluster* cluster, RawTowerContainer* towers, RawTowerGeomContainer *towergemom);

  RawClusterContainer* _clusters;

  float _min_tower_e;
  int chkenergyconservation;

  std::string detector;
  std::string ClusterNodeName;

};

#endif /* RAWCLUSTERBUILDER_H__ */
