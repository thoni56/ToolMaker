//============ Integer.cc
//=======================================================================

#include "DOL.hh"
#include "Integer.hh"


//-----------------------------------------------------------------------
// Integer::Integer

Integer::Integer(Integer_32 arg1)
{
    value = arg1;
}

//-----------------------------------------------------------------------
// Integer::Integer

Integer::Integer()
{}

//-----------------------------------------------------------------------
// Integer::operator==

Boolean Integer::operator==(Integer x)
{
    return memcmp(this, &x, 4) == 0;
}

//-----------------------------------------------------------------------
// Integer::operator<

Boolean Integer::operator<(Integer x)
{
    return memcmp(this, &x, 4) < 0;
}


//-----------------------------------------------------------------------
// IntegerAttribute::get

DbResultCode IntegerAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Integer& buffer)
{	
    return dbObject->getValue(index, &buffer);
}

//-----------------------------------------------------------------------
// IntegerAttribute::get

DbResultCode IntegerAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Integer& buffer, int arrayindex)
{	
    return dbObject->getSlice(index, arrayindex*4, 4, &buffer);
}

//-----------------------------------------------------------------------
// IntegerAttribute::set

DbResultCode IntegerAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Integer buffer)
{	
    return dbObject->putValue(index, &buffer);
}

//-----------------------------------------------------------------------
// IntegerAttribute::set

DbResultCode IntegerAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Integer buffer, int arrayindex)
{	
    return dbObject->putSlice(index, arrayindex*4, 4, &buffer);
}

//-- EoF ------------------------------------------------------------
