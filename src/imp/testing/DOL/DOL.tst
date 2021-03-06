%%PROCESS("ddl.imp")
%%--
%%PROCESS("ddlClasses.imp")
%%--
%%PROCESS("ddlRelations.imp")
%%--
%%PROCESS("ddlStructures.imp")
%%--
%%SET CLASSES()
%%--
%%-- CLASS DbEntity
%%SET CLASSES(, DbEntity)
%%SET CLASS_DbEntity()
%%SET CLASS_DbEntity_CLASSID(1)
%%SET CLASS_DbEntity_VERSION("DDL 1.0 Alpha")
%%SET CLASS_DbEntity_KEY()
%%SET CLASS_DbEntity_KEY(name)
%%SET CLASS_DbEntity_KEY_TYPE(Name)
%%SET CLASS_DbEntity_ALLOCATE()
%%SET CLASS_DbEntity_BASECLASSES()
%%SET CLASS_DbEntity_BASE_ATTRIBUTES(0)
%%SET CLASS_DbEntity_SUBCLASSES()
%%SET CLASS_DbEntity_SUBCLASSES(, DbObject)
%%SET CLASS_DbEntity_SUBCLASSES(, Class)
%%SET CLASS_DbEntity_SUBCLASSES(, Relation)
%%SET CLASS_DbEntity_SUBCLASSES(, Structure)
%%SET CLASS_DbEntity_SUBCLASSES(, PersistentStructure)
%%SET CLASS_DbEntity_SUBCLASSES(, DynamicStructure)
%%SET CLASS_DbEntity_ATTRIBUTES()
%%SET CLASS_DbEntity_ATTRIBUTES(, name)
%%SET CLASS_DbEntity_ATTRIBUTE_name_TYPE(Name)
%%SET CLASS_DbEntity_ATTRIBUTE_name_NOT_NULL()
%%SET CLASS_DbEntity_ATTRIBUTES(, version)
%%SET CLASS_DbEntity_ATTRIBUTE_version_TYPE(DynamicString)
%%SET CLASS_DbEntity_ATTRIBUTE_version_REFERENCE(1, 1)
%%--
%%-- CLASS DbObject
%%SET CLASSES(, DbObject)
%%SET CLASS_DbObject()
%%SET CLASS_DbObject_CLASSID(2)
%%SET CLASS_DbObject_VERSION("")
%%SET CLASS_DbObject_KEY()
%%SET CLASS_DbObject_KEY(name)
%%SET CLASS_DbObject_KEY_TYPE(Name)
%%SET CLASS_DbObject_BASECLASSES()
%%SET CLASS_DbObject_BASECLASSES(, DbEntity)
%%SET CLASS_DbObject_BASE_ATTRIBUTES(2)
%%SET CLASS_DbObject_SUBCLASSES()
%%SET CLASS_DbObject_SUBCLASSES(, Class)
%%SET CLASS_DbObject_SUBCLASSES(, Relation)
%%SET CLASS_DbObject_ATTRIBUTES()
%%--
%%-- CLASS Class
%%SET CLASSES(, Class)
%%SET CLASS_Class()
%%SET CLASS_Class_CLASSID(3)
%%SET CLASS_Class_VERSION("")
%%SET CLASS_Class_KEY()
%%SET CLASS_Class_KEY(name)
%%SET CLASS_Class_KEY_TYPE(Name)
%%SET CLASS_Class_BASECLASSES()
%%SET CLASS_Class_BASECLASSES(, DbObject)
%%SET CLASS_Class_BASECLASSES(, DbEntity)
%%SET CLASS_Class_BASE_ATTRIBUTES(2)
%%SET CLASS_Class_SUBCLASSES()
%%SET CLASS_Class_ATTRIBUTES()
%%SET CLASS_Class_ATTRIBUTES(, primaryKey)
%%SET CLASS_Class_ATTRIBUTE_primaryKey_TYPE(keySpecifikation)
%%SET CLASS_Class_ATTRIBUTE_primaryKey_REFERENCE(1, 1)
%%SET CLASS_Class_ATTRIBUTES(, allocate)
%%SET CLASS_Class_ATTRIBUTE_allocate_TYPE(Boolean)
%%SET CLASS_Class_ATTRIBUTES(, base)
%%SET CLASS_Class_ATTRIBUTE_base_TYPE(Class)
%%SET CLASS_Class_ATTRIBUTE_base_REFERENCE(1, 1)
%%SET CLASS_Class_ATTRIBUTES(, attributes)
%%SET CLASS_Class_ATTRIBUTE_attributes_TYPE(ClassAttributes)
%%SET CLASS_Class_ATTRIBUTE_attributes_REFERENCE(1, "N")
%%--
%%-- CLASS keySpecifikation
%%SET CLASSES(, keySpecifikation)
%%SET CLASS_keySpecifikation()
%%SET CLASS_keySpecifikation_CLASSID(4)
%%SET CLASS_keySpecifikation_VERSION("")
%%SET CLASS_keySpecifikation_KEY()
%%SET CLASS_keySpecifikation_BASECLASSES()
%%SET CLASS_keySpecifikation_BASE_ATTRIBUTES(0)
%%SET CLASS_keySpecifikation_SUBCLASSES()
%%SET CLASS_keySpecifikation_ATTRIBUTES()
%%SET CLASS_keySpecifikation_ATTRIBUTES(, name)
%%SET CLASS_keySpecifikation_ATTRIBUTE_name_TYPE(Attribute)
%%SET CLASS_keySpecifikation_ATTRIBUTE_name_REFERENCE(1, 1)
%%SET CLASS_keySpecifikation_ATTRIBUTE_name_NOT_NULL()
%%SET CLASS_keySpecifikation_ATTRIBUTES(, indexStructure)
%%SET CLASS_keySpecifikation_ATTRIBUTE_indexStructure_TYPE(Name)
%%--
%%-- CLASS Attribute
%%SET CLASSES(, Attribute)
%%SET CLASS_Attribute()
%%SET CLASS_Attribute_CLASSID(5)
%%SET CLASS_Attribute_VERSION("")
%%SET CLASS_Attribute_KEY()
%%SET CLASS_Attribute_KEY(name)
%%SET CLASS_Attribute_KEY_TYPE(UniqueName)
%%SET CLASS_Attribute_ALLOCATE()
%%SET CLASS_Attribute_BASECLASSES()
%%SET CLASS_Attribute_BASE_ATTRIBUTES(0)
%%SET CLASS_Attribute_SUBCLASSES()
%%SET CLASS_Attribute_ATTRIBUTES()
%%SET CLASS_Attribute_ATTRIBUTES(, name)
%%SET CLASS_Attribute_ATTRIBUTE_name_TYPE(UniqueName)
%%SET CLASS_Attribute_ATTRIBUTE_name_NOT_NULL()
%%SET CLASS_Attribute_ATTRIBUTES(, type)
%%SET CLASS_Attribute_ATTRIBUTE_type_TYPE(AttributeType)
%%SET CLASS_Attribute_ATTRIBUTE_type_REFERENCE(1, 1)
%%SET CLASS_Attribute_ATTRIBUTE_type_NOT_NULL()
%%SET CLASS_Attribute_ATTRIBUTES(, properties)
%%SET CLASS_Attribute_ATTRIBUTE_properties_TYPE(AttributeProperty)
%%SET CLASS_Attribute_ATTRIBUTE_properties_REFERENCE(1, 1)
%%SET CLASS_Attribute_ATTRIBUTES(, attributeIdentity)
%%SET CLASS_Attribute_ATTRIBUTE_attributeIdentity_TYPE(Integer)
%%--
%%-- CLASS AttributeType
%%SET CLASSES(, AttributeType)
%%SET CLASS_AttributeType()
%%SET CLASS_AttributeType_CLASSID(6)
%%SET CLASS_AttributeType_VERSION("")
%%SET CLASS_AttributeType_KEY()
%%SET CLASS_AttributeType_BASECLASSES()
%%SET CLASS_AttributeType_BASE_ATTRIBUTES(0)
%%SET CLASS_AttributeType_SUBCLASSES()
%%SET CLASS_AttributeType_SUBCLASSES(, ArrayAttributeType)
%%SET CLASS_AttributeType_ATTRIBUTES()
%%SET CLASS_AttributeType_ATTRIBUTES(, item)
%%SET CLASS_AttributeType_ATTRIBUTE_item_TYPE(DbEntity)
%%SET CLASS_AttributeType_ATTRIBUTE_item_REFERENCE(1, 1)
%%SET CLASS_AttributeType_ATTRIBUTE_item_NOT_NULL()
%%--
%%-- CLASS ArrayAttributeType
%%SET CLASSES(, ArrayAttributeType)
%%SET CLASS_ArrayAttributeType()
%%SET CLASS_ArrayAttributeType_CLASSID(7)
%%SET CLASS_ArrayAttributeType_VERSION("")
%%SET CLASS_ArrayAttributeType_KEY()
%%SET CLASS_ArrayAttributeType_BASECLASSES()
%%SET CLASS_ArrayAttributeType_BASECLASSES(, AttributeType)
%%SET CLASS_ArrayAttributeType_BASE_ATTRIBUTES(1)
%%SET CLASS_ArrayAttributeType_SUBCLASSES()
%%SET CLASS_ArrayAttributeType_ATTRIBUTES()
%%SET CLASS_ArrayAttributeType_ATTRIBUTES(, lowIndex)
%%SET CLASS_ArrayAttributeType_ATTRIBUTE_lowIndex_TYPE(Integer)
%%SET CLASS_ArrayAttributeType_ATTRIBUTE_lowIndex_NOT_NULL()
%%SET CLASS_ArrayAttributeType_ATTRIBUTES(, highIndex)
%%SET CLASS_ArrayAttributeType_ATTRIBUTE_highIndex_TYPE(Integer)
%%SET CLASS_ArrayAttributeType_ATTRIBUTE_highIndex_NOT_NULL()
%%--
%%-- CLASS AttributeProperty
%%SET CLASSES(, AttributeProperty)
%%SET CLASS_AttributeProperty()
%%SET CLASS_AttributeProperty_CLASSID(8)
%%SET CLASS_AttributeProperty_VERSION("")
%%SET CLASS_AttributeProperty_KEY()
%%SET CLASS_AttributeProperty_BASECLASSES()
%%SET CLASS_AttributeProperty_BASE_ATTRIBUTES(0)
%%SET CLASS_AttributeProperty_SUBCLASSES()
%%SET CLASS_AttributeProperty_ATTRIBUTES()
%%SET CLASS_AttributeProperty_ATTRIBUTES(, null)
%%SET CLASS_AttributeProperty_ATTRIBUTE_null_TYPE(Boolean)
%%SET CLASS_AttributeProperty_ATTRIBUTES(, initial)
%%SET CLASS_AttributeProperty_ATTRIBUTE_initial_TYPE(Value)
%%SET CLASS_AttributeProperty_ATTRIBUTE_initial_REFERENCE(1, 1)
%%SET CLASS_AttributeProperty_ATTRIBUTES(, reset)
%%SET CLASS_AttributeProperty_ATTRIBUTE_reset_TYPE(Value)
%%SET CLASS_AttributeProperty_ATTRIBUTE_reset_REFERENCE(1, 1)
%%--
%%-- CLASS Value
%%SET CLASSES(, Value)
%%SET CLASS_Value()
%%SET CLASS_Value_CLASSID(9)
%%SET CLASS_Value_VERSION("")
%%SET CLASS_Value_KEY()
%%SET CLASS_Value_BASECLASSES()
%%SET CLASS_Value_BASE_ATTRIBUTES(0)
%%SET CLASS_Value_SUBCLASSES()
%%SET CLASS_Value_SUBCLASSES(, PrimitiveValue)
%%SET CLASS_Value_SUBCLASSES(, IntegerValue)
%%SET CLASS_Value_SUBCLASSES(, FloatValue)
%%SET CLASS_Value_SUBCLASSES(, BooleanValue)
%%SET CLASS_Value_SUBCLASSES(, StringValue)
%%SET CLASS_Value_SUBCLASSES(, NilValue)
%%SET CLASS_Value_SUBCLASSES(, StructureValue)
%%SET CLASS_Value_ATTRIBUTES()
%%SET CLASS_Value_ATTRIBUTES(, next)
%%SET CLASS_Value_ATTRIBUTE_next_TYPE(Value)
%%SET CLASS_Value_ATTRIBUTE_next_REFERENCE(1, 1)
%%SET CLASS_Value_ATTRIBUTE_next_INITIAL()
%%SET CLASS_Value_ATTRIBUTE_next_INITIAL_VALUE(, "NIL")
%%--
%%-- CLASS PrimitiveValue
%%SET CLASSES(, PrimitiveValue)
%%SET CLASS_PrimitiveValue()
%%SET CLASS_PrimitiveValue_CLASSID(10)
%%SET CLASS_PrimitiveValue_VERSION("")
%%SET CLASS_PrimitiveValue_KEY()
%%SET CLASS_PrimitiveValue_BASECLASSES()
%%SET CLASS_PrimitiveValue_BASECLASSES(, Value)
%%SET CLASS_PrimitiveValue_BASE_ATTRIBUTES(1)
%%SET CLASS_PrimitiveValue_SUBCLASSES()
%%SET CLASS_PrimitiveValue_SUBCLASSES(, IntegerValue)
%%SET CLASS_PrimitiveValue_SUBCLASSES(, FloatValue)
%%SET CLASS_PrimitiveValue_SUBCLASSES(, BooleanValue)
%%SET CLASS_PrimitiveValue_SUBCLASSES(, StringValue)
%%SET CLASS_PrimitiveValue_SUBCLASSES(, NilValue)
%%SET CLASS_PrimitiveValue_ATTRIBUTES()
%%--
%%-- CLASS IntegerValue
%%SET CLASSES(, IntegerValue)
%%SET CLASS_IntegerValue()
%%SET CLASS_IntegerValue_CLASSID(11)
%%SET CLASS_IntegerValue_VERSION("")
%%SET CLASS_IntegerValue_KEY()
%%SET CLASS_IntegerValue_BASECLASSES()
%%SET CLASS_IntegerValue_BASECLASSES(, PrimitiveValue)
%%SET CLASS_IntegerValue_BASECLASSES(, Value)
%%SET CLASS_IntegerValue_BASE_ATTRIBUTES(1)
%%SET CLASS_IntegerValue_SUBCLASSES()
%%SET CLASS_IntegerValue_ATTRIBUTES()
%%SET CLASS_IntegerValue_ATTRIBUTES(, value)
%%SET CLASS_IntegerValue_ATTRIBUTE_value_TYPE(Integer)
%%--
%%-- CLASS FloatValue
%%SET CLASSES(, FloatValue)
%%SET CLASS_FloatValue()
%%SET CLASS_FloatValue_CLASSID(12)
%%SET CLASS_FloatValue_VERSION("")
%%SET CLASS_FloatValue_KEY()
%%SET CLASS_FloatValue_BASECLASSES()
%%SET CLASS_FloatValue_BASECLASSES(, PrimitiveValue)
%%SET CLASS_FloatValue_BASECLASSES(, Value)
%%SET CLASS_FloatValue_BASE_ATTRIBUTES(1)
%%SET CLASS_FloatValue_SUBCLASSES()
%%SET CLASS_FloatValue_ATTRIBUTES()
%%SET CLASS_FloatValue_ATTRIBUTES(, value)
%%SET CLASS_FloatValue_ATTRIBUTE_value_TYPE(Float)
%%--
%%-- CLASS BooleanValue
%%SET CLASSES(, BooleanValue)
%%SET CLASS_BooleanValue()
%%SET CLASS_BooleanValue_CLASSID(13)
%%SET CLASS_BooleanValue_VERSION("")
%%SET CLASS_BooleanValue_KEY()
%%SET CLASS_BooleanValue_BASECLASSES()
%%SET CLASS_BooleanValue_BASECLASSES(, PrimitiveValue)
%%SET CLASS_BooleanValue_BASECLASSES(, Value)
%%SET CLASS_BooleanValue_BASE_ATTRIBUTES(1)
%%SET CLASS_BooleanValue_SUBCLASSES()
%%SET CLASS_BooleanValue_ATTRIBUTES()
%%SET CLASS_BooleanValue_ATTRIBUTES(, value)
%%SET CLASS_BooleanValue_ATTRIBUTE_value_TYPE(Boolean)
%%--
%%-- CLASS StringValue
%%SET CLASSES(, StringValue)
%%SET CLASS_StringValue()
%%SET CLASS_StringValue_CLASSID(14)
%%SET CLASS_StringValue_VERSION("")
%%SET CLASS_StringValue_KEY()
%%SET CLASS_StringValue_BASECLASSES()
%%SET CLASS_StringValue_BASECLASSES(, PrimitiveValue)
%%SET CLASS_StringValue_BASECLASSES(, Value)
%%SET CLASS_StringValue_BASE_ATTRIBUTES(1)
%%SET CLASS_StringValue_SUBCLASSES()
%%SET CLASS_StringValue_ATTRIBUTES()
%%SET CLASS_StringValue_ATTRIBUTES(, value)
%%SET CLASS_StringValue_ATTRIBUTE_value_TYPE(DynamicString)
%%SET CLASS_StringValue_ATTRIBUTE_value_REFERENCE(1, 1)
%%--
%%-- CLASS NilValue
%%SET CLASSES(, NilValue)
%%SET CLASS_NilValue()
%%SET CLASS_NilValue_CLASSID(15)
%%SET CLASS_NilValue_VERSION("")
%%SET CLASS_NilValue_KEY()
%%SET CLASS_NilValue_BASECLASSES()
%%SET CLASS_NilValue_BASECLASSES(, PrimitiveValue)
%%SET CLASS_NilValue_BASECLASSES(, Value)
%%SET CLASS_NilValue_BASE_ATTRIBUTES(1)
%%SET CLASS_NilValue_SUBCLASSES()
%%SET CLASS_NilValue_ATTRIBUTES()
%%--
%%-- CLASS StructureValue
%%SET CLASSES(, StructureValue)
%%SET CLASS_StructureValue()
%%SET CLASS_StructureValue_CLASSID(16)
%%SET CLASS_StructureValue_VERSION("")
%%SET CLASS_StructureValue_KEY()
%%SET CLASS_StructureValue_BASECLASSES()
%%SET CLASS_StructureValue_BASECLASSES(, Value)
%%SET CLASS_StructureValue_BASE_ATTRIBUTES(1)
%%SET CLASS_StructureValue_SUBCLASSES()
%%SET CLASS_StructureValue_ATTRIBUTES()
%%SET CLASS_StructureValue_ATTRIBUTES(, values)
%%SET CLASS_StructureValue_ATTRIBUTE_values_TYPE(PrimitiveValue)
%%SET CLASS_StructureValue_ATTRIBUTE_values_REFERENCE(1, 1)
%%SET CLASS_StructureValue_ATTRIBUTE_values_NOT_NULL()
%%--
%%-- CLASS Relation
%%SET CLASSES(, Relation)
%%SET CLASS_Relation()
%%SET CLASS_Relation_CLASSID(17)
%%SET CLASS_Relation_VERSION("")
%%SET CLASS_Relation_KEY()
%%SET CLASS_Relation_KEY(name)
%%SET CLASS_Relation_KEY_TYPE(Name)
%%SET CLASS_Relation_BASECLASSES()
%%SET CLASS_Relation_BASECLASSES(, DbObject)
%%SET CLASS_Relation_BASECLASSES(, DbEntity)
%%SET CLASS_Relation_BASE_ATTRIBUTES(2)
%%SET CLASS_Relation_SUBCLASSES()
%%SET CLASS_Relation_ATTRIBUTES()
%%SET CLASS_Relation_ATTRIBUTES(, from)
%%SET CLASS_Relation_ATTRIBUTE_from_TYPE(Class)
%%SET CLASS_Relation_ATTRIBUTE_from_REFERENCE(1, 1)
%%SET CLASS_Relation_ATTRIBUTE_from_NOT_NULL()
%%SET CLASS_Relation_ATTRIBUTES(, to)
%%SET CLASS_Relation_ATTRIBUTE_to_TYPE(Class)
%%SET CLASS_Relation_ATTRIBUTE_to_REFERENCE(1, 1)
%%SET CLASS_Relation_ATTRIBUTE_to_NOT_NULL()
%%--
%%-- CLASS Structure
%%SET CLASSES(, Structure)
%%SET CLASS_Structure()
%%SET CLASS_Structure_CLASSID(18)
%%SET CLASS_Structure_VERSION("")
%%SET CLASS_Structure_KEY()
%%SET CLASS_Structure_KEY(name)
%%SET CLASS_Structure_KEY_TYPE(Name)
%%SET CLASS_Structure_BASECLASSES()
%%SET CLASS_Structure_BASECLASSES(, DbEntity)
%%SET CLASS_Structure_BASE_ATTRIBUTES(2)
%%SET CLASS_Structure_SUBCLASSES()
%%SET CLASS_Structure_SUBCLASSES(, PersistentStructure)
%%SET CLASS_Structure_SUBCLASSES(, DynamicStructure)
%%SET CLASS_Structure_ATTRIBUTES()
%%SET CLASS_Structure_ATTRIBUTES(, volatile)
%%SET CLASS_Structure_ATTRIBUTE_volatile_TYPE(VolatileElement)
%%SET CLASS_Structure_ATTRIBUTE_volatile_REFERENCE(1, 1)
%%--
%%-- CLASS PersistentStructure
%%SET CLASSES(, PersistentStructure)
%%SET CLASS_PersistentStructure()
%%SET CLASS_PersistentStructure_CLASSID(19)
%%SET CLASS_PersistentStructure_VERSION("")
%%SET CLASS_PersistentStructure_KEY()
%%SET CLASS_PersistentStructure_KEY(name)
%%SET CLASS_PersistentStructure_KEY_TYPE(Name)
%%SET CLASS_PersistentStructure_BASECLASSES()
%%SET CLASS_PersistentStructure_BASECLASSES(, Structure)
%%SET CLASS_PersistentStructure_BASECLASSES(, DbEntity)
%%SET CLASS_PersistentStructure_BASE_ATTRIBUTES(3)
%%SET CLASS_PersistentStructure_SUBCLASSES()
%%SET CLASS_PersistentStructure_ATTRIBUTES()
%%SET CLASS_PersistentStructure_ATTRIBUTES(, persistent)
%%SET CLASS_PersistentStructure_ATTRIBUTE_persistent_TYPE(PersistentElement)
%%SET CLASS_PersistentStructure_ATTRIBUTE_persistent_REFERENCE(1, 1)
%%--
%%-- CLASS DynamicStructure
%%SET CLASSES(, DynamicStructure)
%%SET CLASS_DynamicStructure()
%%SET CLASS_DynamicStructure_CLASSID(20)
%%SET CLASS_DynamicStructure_VERSION("")
%%SET CLASS_DynamicStructure_KEY()
%%SET CLASS_DynamicStructure_KEY(name)
%%SET CLASS_DynamicStructure_KEY_TYPE(Name)
%%SET CLASS_DynamicStructure_BASECLASSES()
%%SET CLASS_DynamicStructure_BASECLASSES(, Structure)
%%SET CLASS_DynamicStructure_BASECLASSES(, DbEntity)
%%SET CLASS_DynamicStructure_BASE_ATTRIBUTES(3)
%%SET CLASS_DynamicStructure_SUBCLASSES()
%%SET CLASS_DynamicStructure_ATTRIBUTES()
%%SET CLASS_DynamicStructure_ATTRIBUTES(, dynamic)
%%SET CLASS_DynamicStructure_ATTRIBUTE_dynamic_TYPE(PersistentElement)
%%SET CLASS_DynamicStructure_ATTRIBUTE_dynamic_REFERENCE(1, 1)
%%--
%%-- CLASS Element
%%SET CLASSES(, Element)
%%SET CLASS_Element()
%%SET CLASS_Element_CLASSID(21)
%%SET CLASS_Element_VERSION("")
%%SET CLASS_Element_KEY()
%%SET CLASS_Element_KEY(name)
%%SET CLASS_Element_KEY_TYPE(UniqueName)
%%SET CLASS_Element_ALLOCATE()
%%SET CLASS_Element_BASECLASSES()
%%SET CLASS_Element_BASE_ATTRIBUTES(0)
%%SET CLASS_Element_SUBCLASSES()
%%SET CLASS_Element_SUBCLASSES(, PersistentElement)
%%SET CLASS_Element_SUBCLASSES(, VolatileElement)
%%SET CLASS_Element_ATTRIBUTES()
%%SET CLASS_Element_ATTRIBUTES(, name)
%%SET CLASS_Element_ATTRIBUTE_name_TYPE(UniqueName)
%%SET CLASS_Element_ATTRIBUTE_name_NOT_NULL()
%%SET CLASS_Element_ATTRIBUTES(, next)
%%SET CLASS_Element_ATTRIBUTE_next_TYPE(Element)
%%SET CLASS_Element_ATTRIBUTE_next_REFERENCE(1, 1)
%%SET CLASS_Element_ATTRIBUTE_next_INITIAL()
%%SET CLASS_Element_ATTRIBUTE_next_INITIAL_VALUE(, "NIL")
%%--
%%-- CLASS PersistentElement
%%SET CLASSES(, PersistentElement)
%%SET CLASS_PersistentElement()
%%SET CLASS_PersistentElement_CLASSID(22)
%%SET CLASS_PersistentElement_VERSION("")
%%SET CLASS_PersistentElement_KEY()
%%SET CLASS_PersistentElement_KEY(name)
%%SET CLASS_PersistentElement_KEY_TYPE(UniqueName)
%%SET CLASS_PersistentElement_BASECLASSES()
%%SET CLASS_PersistentElement_BASECLASSES(, Element)
%%SET CLASS_PersistentElement_BASE_ATTRIBUTES(2)
%%SET CLASS_PersistentElement_SUBCLASSES()
%%SET CLASS_PersistentElement_ATTRIBUTES()
%%SET CLASS_PersistentElement_ATTRIBUTES(, type)
%%SET CLASS_PersistentElement_ATTRIBUTE_type_TYPE(PredefinedType)
%%SET CLASS_PersistentElement_ATTRIBUTE_type_REFERENCE(1, 1)
%%SET CLASS_PersistentElement_ATTRIBUTE_type_NOT_NULL()
%%SET CLASS_PersistentElement_ATTRIBUTES(, size)
%%SET CLASS_PersistentElement_ATTRIBUTE_size_TYPE(Integer)
%%--
%%-- CLASS PredefinedType
%%SET CLASSES(, PredefinedType)
%%SET CLASS_PredefinedType()
%%SET CLASS_PredefinedType_CLASSID(23)
%%SET CLASS_PredefinedType_VERSION("")
%%SET CLASS_PredefinedType_KEY()
%%SET CLASS_PredefinedType_KEY(name)
%%SET CLASS_PredefinedType_KEY_TYPE(Name)
%%SET CLASS_PredefinedType_ALLOCATE()
%%SET CLASS_PredefinedType_BASECLASSES()
%%SET CLASS_PredefinedType_BASE_ATTRIBUTES(0)
%%SET CLASS_PredefinedType_SUBCLASSES()
%%SET CLASS_PredefinedType_ATTRIBUTES()
%%SET CLASS_PredefinedType_ATTRIBUTES(, name)
%%SET CLASS_PredefinedType_ATTRIBUTE_name_TYPE(Name)
%%SET CLASS_PredefinedType_ATTRIBUTE_name_NOT_NULL()
%%--
%%-- CLASS VolatileElement
%%SET CLASSES(, VolatileElement)
%%SET CLASS_VolatileElement()
%%SET CLASS_VolatileElement_CLASSID(24)
%%SET CLASS_VolatileElement_VERSION("")
%%SET CLASS_VolatileElement_KEY()
%%SET CLASS_VolatileElement_KEY(name)
%%SET CLASS_VolatileElement_KEY_TYPE(UniqueName)
%%SET CLASS_VolatileElement_BASECLASSES()
%%SET CLASS_VolatileElement_BASECLASSES(, Element)
%%SET CLASS_VolatileElement_BASE_ATTRIBUTES(2)
%%SET CLASS_VolatileElement_SUBCLASSES()
%%SET CLASS_VolatileElement_ATTRIBUTES()
%%SET CLASS_VolatileElement_ATTRIBUTES(, type)
%%SET CLASS_VolatileElement_ATTRIBUTE_type_TYPE(Name)
%%SET CLASS_VolatileElement_ATTRIBUTE_type_NOT_NULL()
%%--
%%-- CLASS DynamicString
%%SET CLASSES(, DynamicString)
%%SET CLASS_DynamicString()
%%SET CLASS_DynamicString_CLASSID(25)
%%SET CLASS_DynamicString_VERSION("")
%%SET CLASS_DynamicString_KEY()
%%SET CLASS_DynamicString_BASECLASSES()
%%SET CLASS_DynamicString_BASE_ATTRIBUTES(0)
%%SET CLASS_DynamicString_SUBCLASSES()
%%SET CLASS_DynamicString_ATTRIBUTES()
%%SET CLASS_DynamicString_ATTRIBUTES(, string)
%%SET CLASS_DynamicString_ATTRIBUTE_string_TYPE(DynString)
%%SET CLASS_DynamicString_ATTRIBUTES(, next)
%%SET CLASS_DynamicString_ATTRIBUTE_next_TYPE(DynamicString)
%%SET CLASS_DynamicString_ATTRIBUTE_next_REFERENCE(1, 1)
%%SET CLASS_DynamicString_ATTRIBUTE_next_INITIAL()
%%SET CLASS_DynamicString_ATTRIBUTE_next_INITIAL_VALUE(, "NIL")
%%--
%%SET STRUCTURES()
%%--
%%-- STRUCTURE DynString
%%SET STRUCTURES(, DynString)
%%SET STRUCTURE_DynString()
%%SET STRUCTURE_DynString_VERSION("")
%%SET STRUCTURE_DynString_PERSISTENT_ELEMENTS()
%%SET STRUCTURE_DynString_DYNAMIC_ELEMENTS()
%%SET STRUCTURE_DynString_VOLATILE_ELEMENTS()
%%SET STRUCTURE_DynString_PERSISTENT_ELEMENTS(, full)
%%SET STRUCTURE_DynString_ELEMENT_full_TYPE(Boolean)
%%SET STRUCTURE_DynString_ELEMENT_full_SIZE(1)
%%SET STRUCTURE_DynString_PERSISTENT_ELEMENTS(, length)
%%SET STRUCTURE_DynString_ELEMENT_length_TYPE(Integer_16)
%%SET STRUCTURE_DynString_ELEMENT_length_SIZE(2)
%%SET STRUCTURE_DynString_PERSISTENT_ELEMENTS(, buffer)
%%SET STRUCTURE_DynString_ELEMENT_buffer_TYPE(String)
%%SET STRUCTURE_DynString_ELEMENT_buffer_SIZE(200)
%%--
%%-- STRUCTURE Boolean
%%SET STRUCTURES(, Boolean)
%%SET STRUCTURE_Boolean()
%%SET STRUCTURE_Boolean_VERSION("")
%%SET STRUCTURE_Boolean_PERSISTENT_ELEMENTS()
%%SET STRUCTURE_Boolean_DYNAMIC_ELEMENTS()
%%SET STRUCTURE_Boolean_VOLATILE_ELEMENTS()
%%SET STRUCTURE_Boolean_PERSISTENT_ELEMENTS(, value)
%%SET STRUCTURE_Boolean_ELEMENT_value_TYPE(Boolean)
%%SET STRUCTURE_Boolean_ELEMENT_value_SIZE(1)
%%--
%%-- STRUCTURE Integer
%%SET STRUCTURES(, Integer)
%%SET STRUCTURE_Integer()
%%SET STRUCTURE_Integer_VERSION("")
%%SET STRUCTURE_Integer_PERSISTENT_ELEMENTS()
%%SET STRUCTURE_Integer_DYNAMIC_ELEMENTS()
%%SET STRUCTURE_Integer_VOLATILE_ELEMENTS()
%%SET STRUCTURE_Integer_PERSISTENT_ELEMENTS(, value)
%%SET STRUCTURE_Integer_ELEMENT_value_TYPE(Integer_32)
%%SET STRUCTURE_Integer_ELEMENT_value_SIZE(4)
%%--
%%-- STRUCTURE Float
%%SET STRUCTURES(, Float)
%%SET STRUCTURE_Float()
%%SET STRUCTURE_Float_VERSION("")
%%SET STRUCTURE_Float_PERSISTENT_ELEMENTS()
%%SET STRUCTURE_Float_DYNAMIC_ELEMENTS()
%%SET STRUCTURE_Float_VOLATILE_ELEMENTS()
%%SET STRUCTURE_Float_PERSISTENT_ELEMENTS(, value)
%%SET STRUCTURE_Float_ELEMENT_value_TYPE(Real_64)
%%SET STRUCTURE_Float_ELEMENT_value_SIZE(8)
%%--
%%-- STRUCTURE UniqueName
%%SET STRUCTURES(, UniqueName)
%%SET STRUCTURE_UniqueName()
%%SET STRUCTURE_UniqueName_VERSION("")
%%SET STRUCTURE_UniqueName_PERSISTENT_ELEMENTS()
%%SET STRUCTURE_UniqueName_DYNAMIC_ELEMENTS()
%%SET STRUCTURE_UniqueName_VOLATILE_ELEMENTS()
%%SET STRUCTURE_UniqueName_PERSISTENT_ELEMENTS(, base)
%%SET STRUCTURE_UniqueName_ELEMENT_base_TYPE(String)
%%SET STRUCTURE_UniqueName_ELEMENT_base_SIZE(32)
%%SET STRUCTURE_UniqueName_PERSISTENT_ELEMENTS(, name)
%%SET STRUCTURE_UniqueName_ELEMENT_name_TYPE(String)
%%SET STRUCTURE_UniqueName_ELEMENT_name_SIZE(32)
%%--
%%-- STRUCTURE Name
%%SET STRUCTURES(, Name)
%%SET STRUCTURE_Name()
%%SET STRUCTURE_Name_VERSION("")
%%SET STRUCTURE_Name_PERSISTENT_ELEMENTS()
%%SET STRUCTURE_Name_DYNAMIC_ELEMENTS()
%%SET STRUCTURE_Name_VOLATILE_ELEMENTS()
%%SET STRUCTURE_Name_PERSISTENT_ELEMENTS(, value)
%%SET STRUCTURE_Name_ELEMENT_value_TYPE(String)
%%SET STRUCTURE_Name_ELEMENT_value_SIZE(32)
%%--
%%SET RELATIONS()
%%--
%%-- RELATION ClassAttributes
%%SET RELATIONS(, ClassAttributes)
%%SET RELATION_ClassAttributes()
%%SET RELATION_ClassAttributes_VERSION("")
%%SET RELATION_ClassAttributes_FROM(Class)
%%SET RELATION_ClassAttributes_TO(Attribute)
%%--
%%--
%%INCLUDE(makeDeclarations)
