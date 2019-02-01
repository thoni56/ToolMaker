//============ ClassAttributes.cc
//=======================================================================

#include "DOL.hh"
#include "ClassAttributes.hh"
#include "Class.hh"




//-----------------------------------------------------------------------
// ClassAttributes::ClassAttributes

ClassAttributes::ClassAttributes(DbTitle* title, DBOperation op, Class* mainObject, DbResultCode& result)
    : (title, op, result, mainObject->get_Transaction()) 
{
    main_Object = mainObject;
}


//-----------------------------------------------------------------------
// ClassAttributes::ClassAttributes

ClassAttributes::ClassAttributes(ClassIdentity classIdentity, Class* mainObject, DbResultCode& result)
    : (classIdentity, result, mainObject->get_Transaction())
{
    main_Object = mainObject;
}


//-----------------------------------------------------------------------
// ClassAttributes::add

void ClassAttributes::add(Attribute* dol)
{
    if (operation == UPDATE || operation == CREATE) {
        switch (dol->getTitle()->getClassIdentity()) {
        case Attribute_CLASS_ID:
	    addElement(dol->getTitle());
	    break;
        default:
	    error("ClassAttributes::add : 2");
        }
    }
    else error("ClassAttributes::add : 3");
}


//-----------------------------------------------------------------------
// ClassAttributes::sub

void ClassAttributes::sub(Attribute* dol)
{
    if (operation == UPDATE || operation == CREATE) {
        switch (dol->getTitle()->getClassIdentity()) {
        case Attribute_CLASS_ID:
	    removeElement(dol->getTitle());
	    break;
        default:
	    error("ClassAttributes::sub");
        }
    }
    else error("ClassAttributes::sub");
}



//-----------------------------------------------------------------------
// ClassAttributes::updateNext

Attribute* ClassAttributes::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbSetAbstractObject::iterate();
    if (title)
    	return Attribute::open(title, result, UPDATE, trId);
    else {
	result = END_OF_SET;
 	return NULL;
    }
}


//-----------------------------------------------------------------------
// ClassAttributes::openrlockNext

Attribute* ClassAttributes::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbSetAbstractObject::iterate();
    if (title)
    	return Attribute::open(title, result, OPENRLOCK, trId);
    else {
	result = END_OF_SET;
 	return NULL;
    }
}


//-----------------------------------------------------------------------
// ClassAttributes::openNext

Attribute* ClassAttributes::openNext(DbResultCode& result, Attribute* dol)
{
    DbTitle* title = DbSetAbstractObject::iterate();
    if (title) {
	if (dol == NULL)
	    return Attribute::open(title, result, OPEN, NULL);
	else
	    return Attribute::open(title, result, dol);
    }
    else {
        result = END_OF_SET;
 	return NULL;
    }
}


//-----------------------------------------------------------------------
// ClassAttributes::isMember

Boolean ClassAttributes::isMember(Attribute* dol)
{
    return DbSetAbstractObject::isMember(dol->getTitle());
}






//-----------------------------------------------------------------------
// ClassAttributes::prepare

DbResultCode ClassAttributes::prepare()
{
    CLID clid;
    LID lid;
    DbAbstractObject* temp;
    DbResultCode result;
    for (int i = 0; i<insertCounter; ++i) {
        temp = new DbAbstractObject (addList[i], OPEN, result);
        if (result == SUCCEEDED) {
            temp->getClidLid(clid, lid);
            addList[i]->putClidLid(clid, lid);
	}
        delete temp;
    }
    for (int j = 0; j < deleteCounter; ++j) {
        temp = new DbAbstractObject (deleteList[j],OPEN,result);
        if (result == SUCCEEDED) {
            temp->getClidLid(clid,lid);
            deleteList[j]->putClidLid(clid,lid);
	}
        delete temp;
    }
    return SUCCEEDED;
}


//-----------------------------------------------------------------------
// ClassAttributes::rollbackSubObject

void ClassAttributes::rollbackSubObject()
{
    for (int i = 0; i<insertCounter; ++i)
        addList[i]= 0;
    for (int j = 0; j<deleteCounter; ++j)
        deleteList[j] = 0;
    insertCounter = deleteCounter = 0;
    LocalTransItem::rollbackSubObject(operation, theObject, uo_object);
}

//-- EoF ------------------------------------------------------------
