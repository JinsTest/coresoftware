#ifndef __GLOBALVERTEXMAP_H__
#define __GLOBALVERTEXMAP_H__

#include "GlobalVertex.h"

#include <phool/PHObject.h>
#include <map>
#include <iostream>

class GlobalVertexMap : public PHObject {
  
public:

  typedef std::map<unsigned int, GlobalVertex*>::const_iterator ConstIter;
  typedef std::map<unsigned int, GlobalVertex*>::iterator            Iter;
  
  virtual ~GlobalVertexMap() {}

  virtual void identify(std::ostream &os = std::cout) const {os << "GlobalVertexMap base class" << std::endl;}
  virtual void Reset()                                      {}
  virtual int  isValid() const                              {return 0;}
  
  virtual bool   empty()                   const            {return true;}
  virtual size_t size()                    const            {return 0;}
  virtual size_t count(unsigned int idkey) const            {return 0;}
  virtual void   clear()                                    {}
  
  virtual const GlobalVertex* get(unsigned int idkey) const {return NULL;}
  virtual       GlobalVertex* get(unsigned int idkey)       {return NULL;}
  virtual       GlobalVertex* insert(GlobalVertex* vertex)  {return NULL;}
  virtual       size_t        erase(unsigned int idkey)     {return 0;}

  virtual ConstIter begin()                   const {return std::map<unsigned int,GlobalVertex*>().end();}
  virtual ConstIter  find(unsigned int idkey) const {return std::map<unsigned int,GlobalVertex*>().end();}
  virtual ConstIter   end()                   const {return std::map<unsigned int,GlobalVertex*>().end();}

  virtual Iter begin()                   {return std::map<unsigned int,GlobalVertex*>().end();}
  virtual Iter  find(unsigned int idkey) {return std::map<unsigned int,GlobalVertex*>().end();}
  virtual Iter   end()                   {return std::map<unsigned int,GlobalVertex*>().end();}

protected:
  GlobalVertexMap() {}

private:

  ClassDef(GlobalVertexMap, 1);
};

#endif // __GLOBALVERTEXMAP_H__
