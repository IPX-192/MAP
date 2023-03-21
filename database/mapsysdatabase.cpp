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
void ProductInfoTable::initValues() {
}
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
void UserInfoTable::initValues() {
}
void UserInfoTable::defaults() {
    id = 0;
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
void TagInfoTable::initValues() {
}
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
void MapOriginConfig::initValues() {
}
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
const litesql::FieldType TagDataTable::Own::Id("id_",A_field_type_integer,"TagDataTable_");
const std::string TagDataTable::type__("TagDataTable");
const std::string TagDataTable::table__("TagDataTable_");
const std::string TagDataTable::sequence__("TagDataTable_seq");
const litesql::FieldType TagDataTable::Id("id_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::Type("type_",A_field_type_string,table__);
const litesql::FieldType TagDataTable::ITagID("iTagID_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::IDataID("iDataID_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::SaveTime("saveTime_",A_field_type_string,table__);
const litesql::FieldType TagDataTable::IMapID("iMapID_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::IBattery("iBattery_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::IPosX("iPosX_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::IPosY("iPosY_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::IPosZ("iPosZ_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::IStaticTime("iStaticTime_",A_field_type_integer,table__);
const litesql::FieldType TagDataTable::StrUserID("strUserID_",A_field_type_string,table__);
const litesql::FieldType TagDataTable::StrUserName("strUserName_",A_field_type_string,table__);
const litesql::FieldType TagDataTable::StrDepartment("strDepartment_",A_field_type_string,table__);
const litesql::FieldType TagDataTable::StrRole("strRole_",A_field_type_string,table__);
void TagDataTable::initValues() {
}
void TagDataTable::defaults() {
    id = 0;
    iTagID = 0;
    iDataID = 0;
    iMapID = 0;
    iBattery = 0;
    iPosX = 0;
    iPosY = 0;
    iPosZ = 0;
    iStaticTime = 0;
}
TagDataTable::TagDataTable(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), iTagID(ITagID), iDataID(IDataID), saveTime(SaveTime), iMapID(IMapID), iBattery(IBattery), iPosX(IPosX), iPosY(IPosY), iPosZ(IPosZ), iStaticTime(IStaticTime), strUserID(StrUserID), strUserName(StrUserName), strDepartment(StrDepartment), strRole(StrRole) {
    defaults();
}
TagDataTable::TagDataTable(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), iTagID(ITagID), iDataID(IDataID), saveTime(SaveTime), iMapID(IMapID), iBattery(IBattery), iPosX(IPosX), iPosY(IPosY), iPosZ(IPosZ), iStaticTime(IStaticTime), strUserID(StrUserID), strUserName(StrUserName), strDepartment(StrDepartment), strRole(StrRole) {
    defaults();
    size_t size = (rec.size() > 15) ? 15 : rec.size();
    switch(size) {
    case 15: strRole = convert<const std::string&, std::string>(rec[14]);
        strRole.setModified(false);
    case 14: strDepartment = convert<const std::string&, std::string>(rec[13]);
        strDepartment.setModified(false);
    case 13: strUserName = convert<const std::string&, std::string>(rec[12]);
        strUserName.setModified(false);
    case 12: strUserID = convert<const std::string&, std::string>(rec[11]);
        strUserID.setModified(false);
    case 11: iStaticTime = convert<const std::string&, int>(rec[10]);
        iStaticTime.setModified(false);
    case 10: iPosZ = convert<const std::string&, int>(rec[9]);
        iPosZ.setModified(false);
    case 9: iPosY = convert<const std::string&, int>(rec[8]);
        iPosY.setModified(false);
    case 8: iPosX = convert<const std::string&, int>(rec[7]);
        iPosX.setModified(false);
    case 7: iBattery = convert<const std::string&, int>(rec[6]);
        iBattery.setModified(false);
    case 6: iMapID = convert<const std::string&, int>(rec[5]);
        iMapID.setModified(false);
    case 5: saveTime = convert<const std::string&, std::string>(rec[4]);
        saveTime.setModified(false);
    case 4: iDataID = convert<const std::string&, int>(rec[3]);
        iDataID.setModified(false);
    case 3: iTagID = convert<const std::string&, int>(rec[2]);
        iTagID.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
TagDataTable::TagDataTable(const TagDataTable& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), iTagID(obj.iTagID), iDataID(obj.iDataID), saveTime(obj.saveTime), iMapID(obj.iMapID), iBattery(obj.iBattery), iPosX(obj.iPosX), iPosY(obj.iPosY), iPosZ(obj.iPosZ), iStaticTime(obj.iStaticTime), strUserID(obj.strUserID), strUserName(obj.strUserName), strDepartment(obj.strDepartment), strRole(obj.strRole) {
}
const TagDataTable& TagDataTable::operator=(const TagDataTable& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        iTagID = obj.iTagID;
        iDataID = obj.iDataID;
        saveTime = obj.saveTime;
        iMapID = obj.iMapID;
        iBattery = obj.iBattery;
        iPosX = obj.iPosX;
        iPosY = obj.iPosY;
        iPosZ = obj.iPosZ;
        iStaticTime = obj.iStaticTime;
        strUserID = obj.strUserID;
        strUserName = obj.strUserName;
        strDepartment = obj.strDepartment;
        strRole = obj.strRole;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string TagDataTable::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
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
    fields.push_back(iDataID.name());
    values.push_back(iDataID);
    iDataID.setModified(false);
    fields.push_back(saveTime.name());
    values.push_back(saveTime);
    saveTime.setModified(false);
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
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void TagDataTable::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void TagDataTable::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, iTagID);
    updateField(updates, table__, iDataID);
    updateField(updates, table__, saveTime);
    updateField(updates, table__, iMapID);
    updateField(updates, table__, iBattery);
    updateField(updates, table__, iPosX);
    updateField(updates, table__, iPosY);
    updateField(updates, table__, iPosZ);
    updateField(updates, table__, iStaticTime);
    updateField(updates, table__, strUserID);
    updateField(updates, table__, strUserName);
    updateField(updates, table__, strDepartment);
    updateField(updates, table__, strRole);
}
void TagDataTable::addIDUpdates(Updates& updates) {
}
void TagDataTable::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(ITagID);
    ftypes.push_back(IDataID);
    ftypes.push_back(SaveTime);
    ftypes.push_back(IMapID);
    ftypes.push_back(IBattery);
    ftypes.push_back(IPosX);
    ftypes.push_back(IPosY);
    ftypes.push_back(IPosZ);
    ftypes.push_back(IStaticTime);
    ftypes.push_back(StrUserID);
    ftypes.push_back(StrUserName);
    ftypes.push_back(StrDepartment);
    ftypes.push_back(StrRole);
}
void TagDataTable::delRecord() {
    deleteFromTable(table__, id);
}
void TagDataTable::delRelations() {
}
void TagDataTable::update() {
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
void TagDataTable::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<TagDataTable> p(upcastCopy());
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
bool TagDataTable::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<TagDataTable> TagDataTable::upcast() const {
    return auto_ptr<TagDataTable>(new TagDataTable(*this));
}
std::auto_ptr<TagDataTable> TagDataTable::upcastCopy() const {
    TagDataTable* np = new TagDataTable(*this);
    np->id = id;
    np->type = type;
    np->iTagID = iTagID;
    np->iDataID = iDataID;
    np->saveTime = saveTime;
    np->iMapID = iMapID;
    np->iBattery = iBattery;
    np->iPosX = iPosX;
    np->iPosY = iPosY;
    np->iPosZ = iPosZ;
    np->iStaticTime = iStaticTime;
    np->strUserID = strUserID;
    np->strUserName = strUserName;
    np->strDepartment = strDepartment;
    np->strRole = strRole;
    np->inDatabase = inDatabase;
    return auto_ptr<TagDataTable>(np);
}
std::ostream & operator<<(std::ostream& os, TagDataTable o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.iTagID.name() << " = " << o.iTagID << std::endl;
    os << o.iDataID.name() << " = " << o.iDataID << std::endl;
    os << o.saveTime.name() << " = " << o.saveTime << std::endl;
    os << o.iMapID.name() << " = " << o.iMapID << std::endl;
    os << o.iBattery.name() << " = " << o.iBattery << std::endl;
    os << o.iPosX.name() << " = " << o.iPosX << std::endl;
    os << o.iPosY.name() << " = " << o.iPosY << std::endl;
    os << o.iPosZ.name() << " = " << o.iPosZ << std::endl;
    os << o.iStaticTime.name() << " = " << o.iStaticTime << std::endl;
    os << o.strUserID.name() << " = " << o.strUserID << std::endl;
    os << o.strUserName.name() << " = " << o.strUserName << std::endl;
    os << o.strDepartment.name() << " = " << o.strDepartment << std::endl;
    os << o.strRole.name() << " = " << o.strRole << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType DevInfoTable::Own::Id("id_",A_field_type_integer,"DevInfoTable_");
const std::string DevInfoTable::type__("DevInfoTable");
const std::string DevInfoTable::table__("DevInfoTable_");
const std::string DevInfoTable::sequence__("DevInfoTable_seq");
const litesql::FieldType DevInfoTable::Id("id_",A_field_type_integer,table__);
const litesql::FieldType DevInfoTable::Type("type_",A_field_type_string,table__);
const litesql::FieldType DevInfoTable::IDevID("iDevID_",A_field_type_integer,table__);
const litesql::FieldType DevInfoTable::DevName("devName_",A_field_type_string,table__);
const litesql::FieldType DevInfoTable::DevPos("devPos_",A_field_type_integer,table__);
const litesql::FieldType DevInfoTable::DevWidth("devWidth_",A_field_type_integer,table__);
void DevInfoTable::initValues() {
}
void DevInfoTable::defaults() {
    id = 0;
    iDevID = 0;
    devPos = 0;
    devWidth = 0;
}
DevInfoTable::DevInfoTable(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), iDevID(IDevID), devName(DevName), devPos(DevPos), devWidth(DevWidth) {
    defaults();
}
DevInfoTable::DevInfoTable(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), iDevID(IDevID), devName(DevName), devPos(DevPos), devWidth(DevWidth) {
    defaults();
    size_t size = (rec.size() > 6) ? 6 : rec.size();
    switch(size) {
    case 6: devWidth = convert<const std::string&, int>(rec[5]);
        devWidth.setModified(false);
    case 5: devPos = convert<const std::string&, int>(rec[4]);
        devPos.setModified(false);
    case 4: devName = convert<const std::string&, std::string>(rec[3]);
        devName.setModified(false);
    case 3: iDevID = convert<const std::string&, int>(rec[2]);
        iDevID.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
DevInfoTable::DevInfoTable(const DevInfoTable& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), iDevID(obj.iDevID), devName(obj.devName), devPos(obj.devPos), devWidth(obj.devWidth) {
}
const DevInfoTable& DevInfoTable::operator=(const DevInfoTable& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        iDevID = obj.iDevID;
        devName = obj.devName;
        devPos = obj.devPos;
        devWidth = obj.devWidth;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string DevInfoTable::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(iDevID.name());
    values.push_back(iDevID);
    iDevID.setModified(false);
    fields.push_back(devName.name());
    values.push_back(devName);
    devName.setModified(false);
    fields.push_back(devPos.name());
    values.push_back(devPos);
    devPos.setModified(false);
    fields.push_back(devWidth.name());
    values.push_back(devWidth);
    devWidth.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void DevInfoTable::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void DevInfoTable::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, iDevID);
    updateField(updates, table__, devName);
    updateField(updates, table__, devPos);
    updateField(updates, table__, devWidth);
}
void DevInfoTable::addIDUpdates(Updates& updates) {
}
void DevInfoTable::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(IDevID);
    ftypes.push_back(DevName);
    ftypes.push_back(DevPos);
    ftypes.push_back(DevWidth);
}
void DevInfoTable::delRecord() {
    deleteFromTable(table__, id);
}
void DevInfoTable::delRelations() {
}
void DevInfoTable::update() {
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
void DevInfoTable::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<DevInfoTable> p(upcastCopy());
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
bool DevInfoTable::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<DevInfoTable> DevInfoTable::upcast() const {
    return auto_ptr<DevInfoTable>(new DevInfoTable(*this));
}
std::auto_ptr<DevInfoTable> DevInfoTable::upcastCopy() const {
    DevInfoTable* np = new DevInfoTable(*this);
    np->id = id;
    np->type = type;
    np->iDevID = iDevID;
    np->devName = devName;
    np->devPos = devPos;
    np->devWidth = devWidth;
    np->inDatabase = inDatabase;
    return auto_ptr<DevInfoTable>(np);
}
std::ostream & operator<<(std::ostream& os, DevInfoTable o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.iDevID.name() << " = " << o.iDevID << std::endl;
    os << o.devName.name() << " = " << o.devName << std::endl;
    os << o.devPos.name() << " = " << o.devPos << std::endl;
    os << o.devWidth.name() << " = " << o.devWidth << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType DevConfigTable::Own::Id("id_",A_field_type_integer,"DevConfigTable_");
const std::string DevConfigTable::type__("DevConfigTable");
const std::string DevConfigTable::table__("DevConfigTable_");
const std::string DevConfigTable::sequence__("DevConfigTable_seq");
const litesql::FieldType DevConfigTable::Id("id_",A_field_type_integer,table__);
const litesql::FieldType DevConfigTable::Type("type_",A_field_type_string,table__);
const litesql::FieldType DevConfigTable::BRightOrder("bRightOrder_",A_field_type_boolean,table__);
const litesql::FieldType DevConfigTable::MaxDev("maxDev_",A_field_type_integer,table__);
void DevConfigTable::initValues() {
}
void DevConfigTable::defaults() {
    id = 0;
    bRightOrder = 0;
    maxDev = 0;
}
DevConfigTable::DevConfigTable(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), bRightOrder(BRightOrder), maxDev(MaxDev) {
    defaults();
}
DevConfigTable::DevConfigTable(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), bRightOrder(BRightOrder), maxDev(MaxDev) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: maxDev = convert<const std::string&, int>(rec[3]);
        maxDev.setModified(false);
    case 3: bRightOrder = convert<const std::string&, bool>(rec[2]);
        bRightOrder.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
DevConfigTable::DevConfigTable(const DevConfigTable& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), bRightOrder(obj.bRightOrder), maxDev(obj.maxDev) {
}
const DevConfigTable& DevConfigTable::operator=(const DevConfigTable& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        bRightOrder = obj.bRightOrder;
        maxDev = obj.maxDev;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string DevConfigTable::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(bRightOrder.name());
    values.push_back(bRightOrder);
    bRightOrder.setModified(false);
    fields.push_back(maxDev.name());
    values.push_back(maxDev);
    maxDev.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void DevConfigTable::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void DevConfigTable::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, bRightOrder);
    updateField(updates, table__, maxDev);
}
void DevConfigTable::addIDUpdates(Updates& updates) {
}
void DevConfigTable::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(BRightOrder);
    ftypes.push_back(MaxDev);
}
void DevConfigTable::delRecord() {
    deleteFromTable(table__, id);
}
void DevConfigTable::delRelations() {
}
void DevConfigTable::update() {
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
void DevConfigTable::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<DevConfigTable> p(upcastCopy());
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
bool DevConfigTable::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<DevConfigTable> DevConfigTable::upcast() const {
    return auto_ptr<DevConfigTable>(new DevConfigTable(*this));
}
std::auto_ptr<DevConfigTable> DevConfigTable::upcastCopy() const {
    DevConfigTable* np = new DevConfigTable(*this);
    np->id = id;
    np->type = type;
    np->bRightOrder = bRightOrder;
    np->maxDev = maxDev;
    np->inDatabase = inDatabase;
    return auto_ptr<DevConfigTable>(np);
}
std::ostream & operator<<(std::ostream& os, DevConfigTable o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.bRightOrder.name() << " = " << o.bRightOrder << std::endl;
    os << o.maxDev.name() << " = " << o.maxDev << std::endl;
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
        res.push_back(Database::SchemaItem("TagDataTable_seq","sequence",backend->getCreateSequenceSQL("TagDataTable_seq")));
        res.push_back(Database::SchemaItem("DevInfoTable_seq","sequence",backend->getCreateSequenceSQL("DevInfoTable_seq")));
        res.push_back(Database::SchemaItem("DevConfigTable_seq","sequence",backend->getCreateSequenceSQL("DevConfigTable_seq")));
    }
    res.push_back(Database::SchemaItem("ProductInfoTable_","table","CREATE TABLE ProductInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",strSoftVersion_ " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("UserInfoTable_","table","CREATE TABLE UserInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",strUserID_ " + backend->getSQLType(A_field_type_string,"") + "" +",strUserName_ " + backend->getSQLType(A_field_type_string,"") + "" +",strDepartment_ " + backend->getSQLType(A_field_type_string,"") + "" +",strRole_ " + backend->getSQLType(A_field_type_string,"") + "" +",itagID_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("TagInfoTable_","table","CREATE TABLE TagInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",iTagID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iMapID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iBattery_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosX_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosY_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosZ_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iStaticTime_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("MapOriginConfig_","table","CREATE TABLE MapOriginConfig_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",iPosX_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosY_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosZ_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("TagDataTable_","table","CREATE TABLE TagDataTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",iTagID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iDataID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",saveTime_ " + backend->getSQLType(A_field_type_string,"") + "" +",iMapID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iBattery_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosX_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosY_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iPosZ_ " + backend->getSQLType(A_field_type_integer,"") + "" +",iStaticTime_ " + backend->getSQLType(A_field_type_integer,"") + "" +",strUserID_ " + backend->getSQLType(A_field_type_string,"") + "" +",strUserName_ " + backend->getSQLType(A_field_type_string,"") + "" +",strDepartment_ " + backend->getSQLType(A_field_type_string,"") + "" +",strRole_ " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("DevInfoTable_","table","CREATE TABLE DevInfoTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",iDevID_ " + backend->getSQLType(A_field_type_integer,"") + "" +",devName_ " + backend->getSQLType(A_field_type_string,"") + "" +",devPos_ " + backend->getSQLType(A_field_type_integer,"") + "" +",devWidth_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("DevConfigTable_","table","CREATE TABLE DevConfigTable_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",bRightOrder_ " + backend->getSQLType(A_field_type_boolean,"") + "" +",maxDev_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("ProductInfoTable_id_idx","index","CREATE INDEX ProductInfoTable_id_idx ON ProductInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("UserInfoTable_id_idx","index","CREATE INDEX UserInfoTable_id_idx ON UserInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("TagInfoTable_id_idx","index","CREATE INDEX TagInfoTable_id_idx ON TagInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("MapOriginConfig_id_idx","index","CREATE INDEX MapOriginConfig_id_idx ON MapOriginConfig_ (id_)"));
    res.push_back(Database::SchemaItem("TagDataTable_id_idx","index","CREATE INDEX TagDataTable_id_idx ON TagDataTable_ (id_)"));
    res.push_back(Database::SchemaItem("DevInfoTable_id_idx","index","CREATE INDEX DevInfoTable_id_idx ON DevInfoTable_ (id_)"));
    res.push_back(Database::SchemaItem("DevConfigTable_id_idx","index","CREATE INDEX DevConfigTable_id_idx ON DevConfigTable_ (id_)"));
    return res;
}
void MapSysDatabase::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
