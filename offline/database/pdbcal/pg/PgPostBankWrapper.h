#ifndef __PGPOSTBANKWRAPPER_HH__
#define __PGPOSTBANKWRAPPER_HH__

#include "PgPostCalBank.h"

#include <phool/PHTimeStamp.h>

#include <iostream>
#include <string>

class PgPostBankWrapper : public PgPostCalBank {
public:
  PgPostBankWrapper ();
  PgPostBankWrapper (PdbCalBank *b);
  virtual ~PgPostBankWrapper ();
  virtual PgPostCalBank * clone() const { return new PgPostBankWrapper(*this); }
  
  void printHeader () const;
  void print (){ bank->print(); }
  void printEntry (size_t s) { bank->printEntry(s); }
   
  size_t getLength () {return bank->getLength(); }
  PdbCalChan& getEntry (size_t pos) { return bank->getEntry(pos); } 
  void setLength (size_t len) { bank->setLength(len); }
  virtual bool commit();

  PdbBankID    getBankID()       const { return bankID; }
  PHTimeStamp getInsertTime()   const { return insertTime; }
  PHTimeStamp getStartValTime() const { return startValTime; }
  PHTimeStamp getEndValTime()   const { return endValTime; }
  std::string    getDescription()  const { return description; }
  std::string    getUserName()     const { return userName; }
  std::string    getTableName()    const { return tableName; }
 
  void setBankID(const PdbBankID & val)          { bankID = val; }
  void setInsertTime(const PHTimeStamp & val)   { insertTime = val; }
  void setStartValTime(const PHTimeStamp & val) { startValTime = val; }
  void setEndValTime(const PHTimeStamp & val)   { endValTime = val; }
  void setDescription(const std::string & val) { strcpy(description, val.c_str()); }  
  void setUserName(const std::string & val) { strcpy(userName, val.c_str()); }
  void setTableName(const std::string & val) { strcpy(tableName, val.c_str()); }

  PdbCalBank * getBank() { return  bank; }
  virtual int isValid (const PHTimeStamp &) const { return 0; }

private:

  PdbBankID     bankID;
  PHTimeStamp  insertTime;
  PHTimeStamp  startValTime;
  PHTimeStamp  endValTime;
  char         description[240];
  char         userName[200];
  char         tableName[400];

  PdbCalBank * bank;

  ClassDef(PgPostBankWrapper, 1);

};

#endif /* __PGPOSTBANKWRAPPER_HH__ */
