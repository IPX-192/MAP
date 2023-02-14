#include "mapsysdatabase.hpp"
namespace Database {
using namespace litesql;
const litesql::FieldType ProductInfoTable::Own::Id("id_",A_field_type_integer,"ProductInfoTable_");
const std::string ProductInfoTable::type__("ProductInfoTable");
const std::string ProductInfoTable::table__("ProductInfoTable_");
const std::string ProductInfoTable::sequence__("ProductInfoTable_seq");
const litesql::FieldType ProductInfoTable::Id("id_",A_field_type_integer,table__);
const litesql::FieldType ProductInfoTable::Type("type_",A_field_type_string,table__);
const litesql::FieldType ProductInfoTable::StrSoftVersion("strSoftVersion_",A_field_type_string,table__);
void ProductInfoTable::defaults() {
    id = 0;
    strSoftVersion = "1.0.0.1";
}
ProductInfoTable::ProductInfoTable(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), strSoftVersion(StrSoftVersion) {
    defaults();
}
ProductInfoTable::ProductInfoTable(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), strSoftVersion(StrSoftVersion) {
    defaults();
    size_t size = (rec.size() > 3) ? 3 : rec.size();
    switch(size) {
    case 3: strSoftVersion = convert<const std::string&, std::string>(rec[2]);
        strSoftVersion.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
ProductInfoTable::ProductInfoTable(const ProductInfoTable& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), strSoftVersion(obj.strSoftVersion) {
}
const ProductInfoTable& ProductInfoTable::operator=(const ProductInfoTable& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        strSoftVersion = obj.strSoftVersion;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string ProductInfoTable::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(strSoftVersion.name());
    values.push_back(strSoftVersion);
    strSoftVersion.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void ProductInfoTable::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void ProductInfoTable::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, strSoftVersion);
}
void ProductInfoTable::addIDUpdates(Updates& updates) {
}
void ProductInfoTable::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(StrSoftVersion);
}
void ProductInfoTable::delRecord() {
    deleteFromTable(table__, id);
}
void ProductInfoTable::delRelations() {
}
void ProductInfoTable::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void ProductInfoTable::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<ProductInfoTable> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool ProductInfoTable::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<ProductInfoTable> ProductInfoTable::upcast() const {
    return auto_ptr<ProductInfoTable>(new ProductInfoTable(*this));
}
std::auto_ptr<ProductInfoTable> ProductInfoTable::upcastCopy() const {
    ProductInfoTable* np = new ProductInfoTable(*this);
    np->id = id;
    np->type = type;
    np->strSoftVersion = strSoftVersion;
    np->inDatabase = inDatabase;
    return auto_ptr<ProductInfoTable>(np);
}
std::ostream & operator<<(std::ostream& os, ProductInfoTable o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.strSoftVersion.name() << " = " << o.strSoftVersion << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType UserInfoTable::Own::Id("id_",A_field_type_integer,"UserInfoTable_");
const std::string UserInfoTable::type__("UserInfoTable");
const std::string UserInfoTable::table__("UserInfoTable_");
const std::string UserInfoTable::sequence__("UserInfoTable_seq");
const litesql::FieldType UserInfoTable::Id("id_",A_field_type_integer,table__);
const litesql::FieldType UserInfoTable::Type("type_",A_field_type_string,table__);
const litesql::FieldType UserInfoTable::StrUserID("strUserID_",A_field_type_string,table__);
const litesql::FieldType UserInfoTable::StrUserName("strUserName_",A_field_type_string,table__);
const litesql::FieldType UserInfoTable::StrDepartment("strDepartment_",A_field_type_string,table__);
const litesql::FieldType UserInfoTable::StrRole("strRole_",A_field_type_string,table__);
const litesql::FieldType UserInfoTable::ItagID("itagID_",A_field_type_integer,table__);
void UserInfoTable::defaults() {
    id = 0;
    strRole = "0";
    itagID = 0;
}
UserInfoTable::UserInfoTable(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), strUserID(StrUserID), strUserName(StrUserName), strDepartment(StrDepartment), strRole(StrRole), itagID(ItagID) {
    defaults();
}
UserInfoTable::UserInfoTable(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), strUserID(StrUserID), strUserName(StrUserName), strDepartment(StrDepartment), strRole(StrRole), itagID(ItagID) {
    defaults();
    size_t size = (rec.size() > 7) ? 7 : rec.size();
    switch(size) {
    case 7: itagID = convert<const std::string&, int>(rec[6]);
        itagID.setModified(false);
    case 6: strRole = convert<const std::string&, std::string>(rec[5]);
        strRole.setModified(false);
    case 5: strDepartment = convert<const std::string&, std::string>(rec[4]);
        strDepartment.setModified(false);
    case 4: strUserName = convert<const std::string&, std::string>(rec[3]);
        strUserName.setModified(false);
    case 3: strUserID = convert<const std::string&, std::string>(rec[2]);
        strUserID.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
UserInfoTable::UserInfoTable(const UserInfoTable& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), strUserID(obj.strUserID), strUserName(obj.strUserName), strDepartment(obj.strDepartment), strRole(obj.strRole), itagID(obj.itagID) {
}
const UserInfoTable& UserInfoTable::operator=(const UserInfoTable& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        strUserID = obj.strUserID;
        strUserName = obj.strUserName;
        strDepartment = obj.strDepartment;
        strRole = obj.strRole;
        itagID = obj.itagID;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string UserInfoTable::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(strUserID.name());
    values.push_back(strUserID);
    strUserID.setModified(false);
    fields.push_back(strUserName.name());
    values.push_back(strUserName);
    strUserName.setModified(false);
    fields.push_back(strDepartment.name());
    values.push_back(strDepartment);
    strDepartment.setModified(false);
    fields.push_back(strRole.name());
    values.push_back(strRole);
    strRole.setModified(false);
    fields.push_back(itagID.name());
    values.push_back(itagID);
    itagID.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void UserInfoTable::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void UserInfoTable::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, strUserID);
    updateField(updates, table__, strUserName);
    updateField(updates, table__, strDepartment);
    updateField(updates, table__, strRole);
    updateField(updates, table__, itagID);
}
void UserInfoTable::addIDUpdates(Updates& updates) {
}
void UserInfoTable::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(StrUserID);
    ftypes.push_back(StrUserName);
    ftypes.push_back(StrDepartment);
    ftypes.push_back(StrRole);
    ftypes.push_back(ItagID);
}
void UserInfoTable::delRecord() {
    deleteFromTable(table__, id);
}
void UserInfoTable::delRelations() {
}
void UserInfoTable::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void UserInfoTable::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<UserInfoTable> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool UserInfoTable::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<UserInfoTable> UserInfoTable::upcast() const {
    return auto_ptr<UserInfoTable>(new UserInfoTable(*this));
}
std::auto_ptr<UserInfoTable> UserInfoTable::upcastCopy() const {
    UserInfoTable* np = new UserInfoTable(*this);
    np->id = id;
    np->type = type;
    np->strUserID = strUserID;
    np->strUserName = strUserName;
    np->strDepartment = strDepartment;
    np->strRole = strRole;
    np->itagID = itagID;
    np->inDatabase = inDatabase;
    return auto_ptr<UserInfoTable>(np);
}
std::ostream & operator<<(std::ostream& os, UserInfoTable o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.strUserID.name() << " = " << o.strUserID << std::endl;
    os << o.strUserName.name() << " = " << o.strUserName << std::endl;
    os << o.strDepartment.name() << " = " << o.strDepartment << std::endl;
    os << o.strRole.name() << " = " << o.strRole << std::endl;
    os << o.itagID.name() << " = " << o.itagID << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType TagInfoTable::Own::Id("id_",A_field_type_integer,"TagInfoTable_");
const std::string TagInfoTable::type__("TagInfoTable");
const std::string TagInfoTable::table__("TagInfoTable_");
const std::string TagInfoTable::sequence__("TagInfoTable_seq");
const litesql::FieldType TagInfoTable::Id("id_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::Type("type_",A_field_type_string,table__);
const litesql::FieldType TagInfoTable::ITagID("iTagID_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::IMapID("iMapID_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::IBattery("iBattery_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::IPosX("iPosX_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::IPosY("iPosY_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::IPosZ("iPosZ_",A_field_type_integer,table__);
const litesql::FieldType TagInfoTable::IStaticTime("iStaticTime_",A_field_type_integer,table__);
void TagInfoTable::defaults() {
    id = 0;
    iTagID = 0;
    iMapID = 0;
    iBattery = 0;
    iPosX = 0;
    iPosY = 0;
    iPosZ = 0;
    iStaticTime = 0;
}
TagInfoTable::TagInfoTable(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), iTagID(ITagID), iMapID(IMapID), iBattery(IBattery), iPosX(IPosX), iPosY(IPosY), iPosZ(IPosZ), iStaticTime(IStaticTime) {
    defaults();
}
TagInfoTable::TagInfoTable(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), iTagID(ITagID), iMapID(IMapID), iBattery(IBattery), iPosX(IPosX), iPosY(IPosY), iPosZ(IPosZ), iStaticTime(IStaticTime) {
    defaults();
    size_t size = (rec.size() > 9) ? 9 : rec.size();
    switch(size) {
    case 9: iStaticTime = convert<const std::string&, int>(rec[8]);
        iStaticTime.setModified(false);
    case 8: iPosZ = convert<const std::string&, int>(rec[7]);
        iPosZ.setModified(false);
    case 7: iPosY = convert<const std::string&, int>(rec[6]);
        iPosY.setModified(false);
    case 6: iPosX = convert<const std::string&, int>(rec[5]);
        iPosX.setModified(false);
    case 5: iBattery = convert<const std::string&, int>(rec[4]);
        iBattery.setModified(false);
    case 4: iMapID = convert<const std::string&, int>(rec[3]);
        iMapID.setModified(false);
    case 3: iTagID = convert<const std::string&, int>(rec[2]);
        iTagID.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
TagInfoTable::TagInfoTable(const TagInfoTable& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), iTagID(obj.iTagID), iMapID(obj.iMapID), iBattery(obj.iBattery), iPosX(obj.iPosX), iPosY(obj.iPosY), iPosZ(obj.iPosZ), iStaticTime(obj.iStaticTime) {
}
const TagInfoTable& TagInfoTable::operator=(const TagInfoTable& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        iTagID = obj.iTagID;
        iMapID = obj.iMapID;
        iBattery = obj.iBattery;
        iPosX = obj.iPosX;
        iPosY = obj.iPosY;
        iPosZ = obj.iPosZ;
        iStaticTime = obj.iStaticTime;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string TagInfoTable::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(iTagID.name());
    values.push_back(iTagID);
    iTagID.setModified(false);
    fields.push_back(iMapID.name());
    values.push_back(iMapID);
    iMapID.setModified(false);
    fields.push_back(iBattery.name());
    values.push_back(iBattery);
    iBattery.setModified(false);
    fields.push_back(iPosX.name());
    values.push_back(iPosX);
    iPosX.setModified(false);
    fields.push_back(iPosY.name());
    values.push_back(iPosY);
    iPosY.setModified(false);
    fields.push_back(iPosZ.name());
    values.push_back(iPosZ);
    iPosZ.setModified(false);
    fields.push_back(iStaticTime.name());
    values.push_back(iStaticTime);
    iStaticTime.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void TagInfoTable::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void TagInfoTable::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, iTagID);
    updateField(updates, table__, iMapID);
    updateField(updates, table__, iBattery);
    updateField(updates, table__, iPosX);
    updateField(updates, table__, iPosY);
    updateField(updates, table__, iPosZ);
    updateField(updates, table__, iStaticTime);
}
void TagInfoTable::addIDUpdates(Updates& updates) {
}
void TagInfoTable::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(ITagID);
    ftypes.push_back(IMapID);
    ftypes.push_back(IBattery);
    ftypes.push_back(IPosX);
    ftypes.push_back(IPosY);
    ftypes.push_back(IPosZ);
    ftypes.push_back(IStaticTime);
}
void TagInfoTable::delRecord() {
    deleteFromTable(table__, id);
}
void TagInfoTable::delRelations() {
}
void TagInfoTable::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void TagInfoTable::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<TagInfoTable> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool TagInfoTable::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<TagInfoTable> TagInfoTable::upcast() const {
    return auto_ptr<TagInfoTable>(new TagInfoTable(*this));
}
std::auto_ptr<TagInfoTable> TagInfoTable::upcastCopy() const {
    TagInfoTable* np = new TagInfoTable(*this);
    np->id = id;
    np->type = type;
    np->iTagID = iTagID;
    np->iMapID = iMapID;
    np->iBattery = iBattery;
    np->iPosX = iPosX;
    np->iPosY = iPosY;
    np->iPosZ = iPosZ;
    np->iStaticTime = iStaticTime;
    np->inDatabase = inDatabase;
    return auto_ptr<TagInfoTable>(np);
}
std::ostream & operator<<(std::ostream& os, TagInfoTable o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.iTagID.name() << " = " << o.iTagID << std::endl;
    os << o.iMapID.name() << " = " << o.iMapID << std::endl;
    os << o.iBattery.name() << " = " << o.iBattery << std::endl;
    os << o.iPosX.name() << " = " << o.iPosX << std::endl;
    os << o.iPosY.name() << " = " << o.iPosY << std::endl;
    os << o.iPosZ.name() << " = " << o.iPosZ << std::endl;
    os << o.iStaticTime.name() << " = " << o.iStaticTime << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType MapOriginConfig::Own::Id("id_",A_field_type_integer,"MapOriginConfig_");
const std::string MapOriginConfig::type__("MapOriginConfig");
const std::string MapOriginConfig::table__("MapOriginConfig_");
const std::string MapOriginConfig::sequence__("MapOriginConfig_seq");
const litesql::FieldType MapOriginConfig::Id("id_",A_field_type_integer,table__);
const litesql::FieldType MapOriginConfig::Type("type_",A_field_type_string,table__);
const litesql::FieldType MapOriginConfig::IPosX("iPosX_",A_field_type_integer,table__);
const litesql::FieldType MapOriginConfig::IPosY("iPosY_",A_field_type_integer,table__);
const litesql::FieldType MapOriginConfig::IPosZ("iPosZ_",A_field_type_integer,table__);
void MapOriginConfig::defaults() {
    id = 0;
    iPosX = 0;
    iPosY = 0;
    iPosZ = 0;
}
MapOriginConfig::MapOriginConfig(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), iPosX(IPosX), iPosY(IPosY), iPosZ(IPosZ) {
    defaults();
}
MapOriginConfig::MapOriginConfig(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), iPosX(IPosX), iPosY(IPosY), iPosZ(IPosZ) {
    defaults();
    size_t size = (rec.size() > 5) ? 5 : rec.size();
    switch(size) {
    case 5: iPosZ = convert<const std::string&, int>(rec[4]);
        iPosZ.setModified(false);
    case 4: iPosY = convert<const std::string&, int>(rec[3]);
        iPosY.setModified(false);
    case 3: iPosX = convert<const std::string&, int>(rec[2]);
        iPosX.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
MapOriginConfig::MapOriginConfig(const MapOriginConfig& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), iPosX(obj.iPosX), iPosY(obj.iPosY), iPosZ(obj.iPosZ) {
}
const MapOriginConfig& MapOriginConfig::operator=(const MapOriginConfig& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        iPosX = obj.iPosX;
        iPosY = obj.iPosY;
        iPosZ = obj.iPosZ;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string MapOriginConfig::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(iPosX.name());
    values.push_back(iPosX);
    iPosX.setModified(false);
    fields.push_back(iPosY.name());
    values.push_back(iPosY);
    iPosY.setModified(false);
    fields.push_back(iPosZ.name());
    values.push_back(iPosZ);
    iPosZ.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void MapOriginConfig::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void MapOriginConfig::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, iPosX);
    updateField(updates, table__, iPosY);
    updateField(updates, table__, iPosZ);
}
void MapOriginConfig::addIDUpdates(Updates& updates) {
}
void MapOriginConfig::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(IPosX);
    ftypes.push_back(IPosY);
    ftypes.push_back(IPosZ);
}
void MapOriginConfig::delRecord() {
    deleteFromTable(table__, id);
}
void MapOriginConfig::delRelations() {
}
void MapOriginConfig::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void MapOriginConfig::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<MapOriginConfig> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool MapOriginConfig::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<MapOriginConfig> MapOriginConfig::upcast() const {
    return auto_ptr<MapOriginConfig>(new MapOriginConfig(*this));
}
std::auto_ptr<MapOriginConfig> MapOriginConfig::upcastCopy() const {
    MapOriginConfig* np = new MapOriginConfig(*this);
    np->id = id;
    np->type = type;
    np->iPosX = iPosX;
    np->iPosY = iPosY;
    np->iPosZ = iPosZ;
    np->inDatabase = inDatabase;
    return auto_ptr<MapOriginConfig>(np);
}
std::ostream & operator<<(std::ostream& os, MapOriginConfig o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.iPosX.name() << " = " << o.iPosX << std::endl;
    os << o.iPosY.name() << " = " << o.iPosY << std::endl;
    os << o.iPosZ.name() << " = " << o.iPosZ << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
MapSysDatabase::MapSysDatabase(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> MapSysDatabase::getSchema() const {
    vector<Database::SchemaItem> res;
    string TEXT = backend->getSQLType(A_field_type_string);
    string rowIdType = backend->getRowIDType();
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ "+TEXT+", type_ "+TEXT+", sql_ "+TEXT+")"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("ProductInfoTable_seq","sequence",backend->getCreateSequenceSQL("ProductInfoTable_seq")));
        res.push_back(Database::SchemaItem("UserInfoTable_seq","sequence",backend->getCreateSequenceSQL("UserInfoTable_seq")));
        res.push_back(Database::SchemaItem("TagInfoTable_seq","sequence",backend->getCreateSequenceSQL("TagInfoTable_seq")));
        res.push_back(Database::SchemaItem("MapOriginConfig_seq","sequence",backend->getCreateSequenceSQL("MapOriginConfig_seq")));
    }
    res.push_back(Database::SchemaItem("ProductInfoTable_","table","CREATE TABLE ProductInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",strSoftVersion_ " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("UserInfoTable_","table","CREATE TABLE UserInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",strUserID_ " + backend->getSQLType(A_field_type_string,"") + "" +",strUserName_ " + backend->getSQLType(A_field_type_string,"") + "" +",strDepartment_ " + backend->getSQLType(A_field_type_string,"") + "" +",strRole_ " + backend->getSQLType(A_field_type_string,"") + "" +",itagID_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("TagInfoTable_","table","CREATE TABLE TagInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",iTagID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iMapID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iBattery_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosX_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosY_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosZ_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iStaticTime_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("MapOriginConfig_","table","CREATE TABLE MapOriginConfig_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",iPosX_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosY_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosZ_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("ProductInfoTable_id_idx","index","CREATE INDEX ProductInfoTable_id_idx ON ProductInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("UserInfoTable_id_idx","index","CREATE INDEX UserInfoTable_id_idx ON UserInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("TagInfoTable_id_idx","index","CREATE INDEX TagInfoTable_id_idx ON TagInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("MapOriginConfig_id_idx","index","CREATE INDEX MapOriginConfig_id_idx ON MapOriginConfig_ (id_)"));
    return res;
}
void MapSysDatabase::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
