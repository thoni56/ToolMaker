#include "DOL.hh"

//=======================================================================
// Database initialisations
void DB_init(void)
{
    DbmGeneral::init();
    DataBaseManager* dbmanager = getDbManager_t();
    install_t(dbmanager, DbEntity_CLASS_ID, "DbEntity.dbLoad");
    install_t(dbmanager, DbObject_CLASS_ID, "DbObject.dbLoad");
    install_t(dbmanager, Class_CLASS_ID, "Class.dbLoad");
    install_t(dbmanager, keySpecifikation_CLASS_ID, "keySpecifikation.dbLoad");
    install_t(dbmanager, Attribute_CLASS_ID, "Attribute.dbLoad");
    install_t(dbmanager, AttributeType_CLASS_ID, "AttributeType.dbLoad");
    install_t(dbmanager, ArrayAttributeType_CLASS_ID, "ArrayAttributeType.dbLoad");
    install_t(dbmanager, AttributeProperty_CLASS_ID, "AttributeProperty.dbLoad");
    install_t(dbmanager, Value_CLASS_ID, "Value.dbLoad");
    install_t(dbmanager, PrimitiveValue_CLASS_ID, "PrimitiveValue.dbLoad");
    install_t(dbmanager, IntegerValue_CLASS_ID, "IntegerValue.dbLoad");
    install_t(dbmanager, FloatValue_CLASS_ID, "FloatValue.dbLoad");
    install_t(dbmanager, BooleanValue_CLASS_ID, "BooleanValue.dbLoad");
    install_t(dbmanager, StringValue_CLASS_ID, "StringValue.dbLoad");
    install_t(dbmanager, NilValue_CLASS_ID, "NilValue.dbLoad");
    install_t(dbmanager, StructureValue_CLASS_ID, "StructureValue.dbLoad");
    install_t(dbmanager, Relation_CLASS_ID, "Relation.dbLoad");
    install_t(dbmanager, Structure_CLASS_ID, "Structure.dbLoad");
    install_t(dbmanager, PersistentStructure_CLASS_ID, "PersistentStructure.dbLoad");
    install_t(dbmanager, DynamicStructure_CLASS_ID, "DynamicStructure.dbLoad");
    install_t(dbmanager, Element_CLASS_ID, "Element.dbLoad");
    install_t(dbmanager, PersistentElement_CLASS_ID, "PersistentElement.dbLoad");
    install_t(dbmanager, PredefinedType_CLASS_ID, "PredefinedType.dbLoad");
    install_t(dbmanager, VolatileElement_CLASS_ID, "VolatileElement.dbLoad");
    install_t(dbmanager, DynamicString_CLASS_ID, "DynamicString.dbLoad");
    install_t(dbmanager, ClassAttributes_CLASS_ID, "ClassAttributes.dbLoad");
} 

//=======================================================================
// error() : Temporary solution. Will be replaced by exceptions.
void error(char* str)
{
cout << "error: " << str << "\n";
exit(1);
}

//-- EoF ------------------------------------------------------------

