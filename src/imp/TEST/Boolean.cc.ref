//============ Boolean.cc
//=======================================================================

#include "DOL.hh"
#include "Boolean.hh"


//-----------------------------------------------------------------------
// Boolean::Boolean

Boolean::Boolean(Boolean arg1)
{
    value = arg1;
}

//-----------------------------------------------------------------------
// Boolean::Boolean

Boolean::Boolean()
{}

//-----------------------------------------------------------------------
// Boolean::operator==

Boolean Boolean::operator==(Boolean x)
{
    return memcmp(this, &x, 1) == 0;
}

//-----------------------------------------------------------------------
// Boolean::operator<

Boolean Boolean::operator<(Boolean x)
{
    return memcmp(this, &x, 1) < 0;
}


//-----------------------------------------------------------------------
// BooleanAttribute::get

DbResultCode BooleanAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Boolean& buffer)
{	
    return dbObject->getValue(index, &buffer);
}

//-----------------------------------------------------------------------
// BooleanAttribute::get

DbResultCode BooleanAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Boolean& buffer, int arrayindex)
{	
    return dbObject->getSlice(index, arrayindex*1, 1, &buffer);
}

//-----------------------------------------------------------------------
// BooleanAttribute::set

DbResultCode BooleanAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Boolean buffer)
{	
    return dbObject->putValue(index, &buffer);
}

//-----------------------------------------------------------------------
// BooleanAttribute::set

DbResultCode BooleanAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Boolean buffer, int arrayindex)
{	
    return dbObject->putSlice(index, arrayindex*1, 1, &buffer);
}

//-- EoF ------------------------------------------------------------
