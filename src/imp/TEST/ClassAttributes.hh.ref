//============ ClassAttributes.hh
//=======================================================================

#ifndef _ClassAttributes_hh
#define _ClassAttributes_hh

#include "Attribute.hh"


//-----------------------------------------------------------------------
// ClassAttributes

#ifndef ClassAttributes_CLASS_ID
#define ClassAttributes_CLASS_ID 26
#endif

class ClassAttributes : public DbSetAbstractObject {
public:

    void add(Attribute*);
    void sub(Attribute*);
    Attribute* updateNext(DbResultCode& result, LocalTransaction* trId);
    Attribute* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    Attribute* openNext(DbResultCode& result, Attribute* dol = NULL);
    Boolean isMember(Attribute* dol);

protected:
    // Constructors
    ClassAttributes(DbTitle*, DBOperation, Class* mainObject, DbResultCode&);
    ClassAttributes(ClassIdentity classIdentity, Class* mainObject, DbResultCode&);
    // Transaction handling
    DbResultCode prepare();
    void rollbackSubObject();

    friend Class;

private:
    Class* main_Object;
}; // ClassAttributes

#endif
//-- EoF ------------------------------------------------------------
