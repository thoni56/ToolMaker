//============ Value.cc
//=======================================================================

#include "DOL.hh"
#include "Value.hh"

// Include subclasses:
#include "PrimitiveValue.hh"
#include "IntegerValue.hh"
#include "FloatValue.hh"
#include "BooleanValue.hh"
#include "StringValue.hh"
#include "NilValue.hh"
#include "StructureValue.hh"

// Include referenced classes:


//-----------------------------------------------------------------------
// Value::create

Value* Value::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(Value_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// Value::getClassNo

int Value::getClassNo()
{
    return Value_CLASS_ID;
}



//-----------------------------------------------------------------------
// Value::open

Value* Value::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (Value*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case Value_CLASS_ID:
	    return new Value (object, tempObject, op, trId, title);
	case PrimitiveValue_CLASS_ID:
	    return (Value*) new PrimitiveValue (object, tempObject, op, trId, title);
	case IntegerValue_CLASS_ID:
	    return (Value*) new IntegerValue (object, tempObject, op, trId, title);
	case FloatValue_CLASS_ID:
	    return (Value*) new FloatValue (object, tempObject, op, trId, title);
	case BooleanValue_CLASS_ID:
	    return (Value*) new BooleanValue (object, tempObject, op, trId, title);
	case StringValue_CLASS_ID:
	    return (Value*) new StringValue (object, tempObject, op, trId, title);
	case NilValue_CLASS_ID:
	    return (Value*) new NilValue (object, tempObject, op, trId, title);
	case StructureValue_CLASS_ID:
	    return (Value*) new StructureValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// Value::open

Value* Value::open(DbTitle *title, DbResultCode& result, Value* dol)
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
// Value::Value

Value::Value(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    Value::init(op);
}


//-----------------------------------------------------------------------
// Value::init

void Value::init(DBOperation op)
{
    if (op == CREATE) {
        // next_ = DbTitleRef::nilRef();    // 4f - Nil reference
    }
    int i = 0;
    next_ = NULL;
}


//-----------------------------------------------------------------------
// Value::updatenext

Value* Value::updatenext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Value::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Value::removenext

Value* Value::removenext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Value::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Value::openrlocknext

Value* Value::openrlocknext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Value::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Value::opennext

Value* Value::opennext(DbResultCode& result, Value* dol)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return Value::open(title, result, OPEN, NULL);
        else
            return Value::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Value::next

void Value::next(Value* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (next_ &&  next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete next_;
	if (data)
            next_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    next_ = DbTitleRef::nilRef();
    }
    else error("Value::next");
}





//-----------------------------------------------------------------------
// Value::prepare

DbResultCode Value::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (next_ != NULL) {
        DbTitle* title = next_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            next_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// Value::commit

void Value::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (next_ != NULL) {
        next_->commit(theObject, 1);
	if (next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete next_;
	next_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// Value::rollback

void Value::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (next_)
	if (next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete next_;
    next_ = NULL;
    DbAbstractObject::rollback();
}







//-- EoF ------------------------------------------------------------
