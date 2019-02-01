//============ Float.cc
//=======================================================================

#include "DOL.hh"
#include "Float.hh"


//-----------------------------------------------------------------------
// Float::Float

Float::Float(Real_64 arg1)
{
    value = arg1;
}

//-----------------------------------------------------------------------
// Float::Float

Float::Float()
{}

//-----------------------------------------------------------------------
// Float::operator==

Boolean Float::operator==(Float x)
{
    return memcmp(this, &x, 8) == 0;
}

//-----------------------------------------------------------------------
// Float::operator<

Boolean Float::operator<(Float x)
{
    return memcmp(this, &x, 8) < 0;
}


//-----------------------------------------------------------------------
// FloatAttribute::get

DbResultCode FloatAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Float& buffer)
{	
    return dbObject->getValue(index, &buffer);
}

//-----------------------------------------------------------------------
// FloatAttribute::get

DbResultCode FloatAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Float& buffer, int arrayindex)
{	
    return dbObject->getSlice(index, arrayindex*8, 8, &buffer);
}

//-----------------------------------------------------------------------
// FloatAttribute::set

DbResultCode FloatAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Float buffer)
{	
    return dbObject->putValue(index, &buffer);
}

//-----------------------------------------------------------------------
// FloatAttribute::set

DbResultCode FloatAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Float buffer, int arrayindex)
{	
    return dbObject->putSlice(index, arrayindex*8, 8, &buffer);
}

//-- EoF ------------------------------------------------------------
