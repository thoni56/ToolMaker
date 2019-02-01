//============ AttributeType.cc
//=======================================================================

#include "DOL.hh"
#include "AttributeType.hh"

// Include subclasses:
#include "ArrayAttributeType.hh"

// Include referenced classes:
#include "DbEntity.hh"


//-----------------------------------------------------------------------
// AttributeType::create

AttributeType* AttributeType::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(AttributeType_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// AttributeType::getClassNo

int AttributeType::getClassNo()
{
    return AttributeType_CLASS_ID;
}



//-----------------------------------------------------------------------
// AttributeType::open

AttributeType* AttributeType::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (AttributeType*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case AttributeType_CLASS_ID:
	    return new AttributeType (object, tempObject, op, trId, title);
	case ArrayAttributeType_CLASS_ID:
	    return (AttributeType*) new ArrayAttributeType (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// AttributeType::open

AttributeType* AttributeType::open(DbTitle *title, DbResultCode& result, AttributeType* dol)
{
    result = dol->reOpen(title);
    if (result != SUCCEEDED) 
        return NULL;
    else {
        dol->init(OPEN);
        return dol;
    }
}


//-----------------------------------------------------------------------
// AttributeType::AttributeType

AttributeType::AttributeType(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    AttributeType::init(op);
}


//-----------------------------------------------------------------------
// AttributeType::init

void AttributeType::init(DBOperation op)
{
    if (op == CREATE) {
    }
    int i = 0;
    item_ = NULL;
}


//-----------------------------------------------------------------------
// AttributeType::updateitem

DbEntity* AttributeType::updateitem(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (item_ != NULL)
        title = item_->getTitle();
    else {
        item_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return DbEntity::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeType::removeitem

DbEntity* AttributeType::removeitem(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (item_ != NULL)
        title = item_->getTitle();
    else {
        item_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DbEntity::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeType::openrlockitem

DbEntity* AttributeType::openrlockitem(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (item_ != NULL)
        title = item_->getTitle();
    else {
        item_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DbEntity::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// AttributeType::openitem

DbEntity* AttributeType::openitem(DbResultCode& result, DbEntity* dol)
{
    DbTitle* title;
    if (item_ != NULL)
        title = item_->getTitle();
    else {
        item_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return DbEntity::open(title, result, OPEN, NULL);
        else
            return DbEntity::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeType::item

void AttributeType::item(DbEntity* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (item_ &&  item_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete item_;
	if (data)
            item_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    item_ = DbTitleRef::nilRef();
    }
    else error("AttributeType::item");
}





//-----------------------------------------------------------------------
// AttributeType::prepare

DbResultCode AttributeType::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (item_ != NULL) {
        DbTitle* title = item_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            item_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// AttributeType::commit

void AttributeType::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (item_ != NULL) {
        item_->commit(theObject, 1);
	if (item_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete item_;
	item_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// AttributeType::rollback

void AttributeType::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (item_)
	if (item_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete item_;
    item_ = NULL;
    DbAbstractObject::rollback();
}







//-- EoF ------------------------------------------------------------
