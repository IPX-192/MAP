#ifndef mapsysdatabase_hpp
#define mapsysdatabase_hpp
#include "litesql.hpp"
namespace Database {
class ProductInfoTable;
class UserInfoTable;
class TagInfoTable;
class MapOriginConfig;
class TagDataTable;
class DevInfoTable;
class ProductInfoTable : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType StrSoftVersion;
    litesql::Field<std::string> strSoftVersion;
protected:
    void defaults();
public:
    ProductInfoTable(const litesql::Database& db);
    ProductInfoTable(const litesql::Database& db, const litesql::Record& rec);
    ProductInfoTable(const ProductInfoTable& obj);
    const ProductInfoTable& operator=(const ProductInfoTable& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<ProductInfoTable> upcast() const;
    std::auto_ptr<ProductInfoTable> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, ProductInfoTable o);
class UserInfoTable : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType StrUserID;
    litesql::Field<std::string> strUserID;
    static const litesql::FieldType StrUserName;
    litesql::Field<std::string> strUserName;
    static const litesql::FieldType StrDepartment;
    litesql::Field<std::string> strDepartment;
    static const litesql::FieldType StrRole;
    litesql::Field<std::string> strRole;
    static const litesql::FieldType ItagID;
    litesql::Field<int> itagID;
protected:
    void defaults();
public:
    UserInfoTable(const litesql::Database& db);
    UserInfoTable(const litesql::Database& db, const litesql::Record& rec);
    UserInfoTable(const UserInfoTable& obj);
    const UserInfoTable& operator=(const UserInfoTable& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<UserInfoTable> upcast() const;
    std::auto_ptr<UserInfoTable> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, UserInfoTable o);
class TagInfoTable : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType ITagID;
    litesql::Field<int> iTagID;
    static const litesql::FieldType IMapID;
    litesql::Field<int> iMapID;
    static const litesql::FieldType IBattery;
    litesql::Field<int> iBattery;
    static const litesql::FieldType IPosX;
    litesql::Field<int> iPosX;
    static const litesql::FieldType IPosY;
    litesql::Field<int> iPosY;
    static const litesql::FieldType IPosZ;
    litesql::Field<int> iPosZ;
    static const litesql::FieldType IStaticTime;
    litesql::Field<int> iStaticTime;
protected:
    void defaults();
public:
    TagInfoTable(const litesql::Database& db);
    TagInfoTable(const litesql::Database& db, const litesql::Record& rec);
    TagInfoTable(const TagInfoTable& obj);
    const TagInfoTable& operator=(const TagInfoTable& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<TagInfoTable> upcast() const;
    std::auto_ptr<TagInfoTable> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, TagInfoTable o);
class MapOriginConfig : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType IPosX;
    litesql::Field<int> iPosX;
    static const litesql::FieldType IPosY;
    litesql::Field<int> iPosY;
    static const litesql::FieldType IPosZ;
    litesql::Field<int> iPosZ;
protected:
    void defaults();
public:
    MapOriginConfig(const litesql::Database& db);
    MapOriginConfig(const litesql::Database& db, const litesql::Record& rec);
    MapOriginConfig(const MapOriginConfig& obj);
    const MapOriginConfig& operator=(const MapOriginConfig& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<MapOriginConfig> upcast() const;
    std::auto_ptr<MapOriginConfig> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, MapOriginConfig o);
class TagDataTable : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType IDataID;
    litesql::Field<int> iDataID;
    static const litesql::FieldType ITagID;
    litesql::Field<int> iTagID;
    static const litesql::FieldType SaveTime;
    litesql::Field<std::string> saveTime;
    static const litesql::FieldType IMapID;
    litesql::Field<int> iMapID;
    static const litesql::FieldType IBattery;
    litesql::Field<int> iBattery;
    static const litesql::FieldType IPosX;
    litesql::Field<int> iPosX;
    static const litesql::FieldType IPosY;
    litesql::Field<int> iPosY;
    static const litesql::FieldType IPosZ;
    litesql::Field<int> iPosZ;
    static const litesql::FieldType IStaticTime;
    litesql::Field<int> iStaticTime;
    static const litesql::FieldType StrUserID;
    litesql::Field<std::string> strUserID;
    static const litesql::FieldType StrUserName;
    litesql::Field<std::string> strUserName;
    static const litesql::FieldType StrDepartment;
    litesql::Field<std::string> strDepartment;
    static const litesql::FieldType StrRole;
    litesql::Field<std::string> strRole;
protected:
    void defaults();
public:
    TagDataTable(const litesql::Database& db);
    TagDataTable(const litesql::Database& db, const litesql::Record& rec);
    TagDataTable(const TagDataTable& obj);
    const TagDataTable& operator=(const TagDataTable& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<TagDataTable> upcast() const;
    std::auto_ptr<TagDataTable> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, TagDataTable o);
class DevInfoTable : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType IDevID;
    litesql::Field<int> iDevID;
    static const litesql::FieldType DevName;
    litesql::Field<std::string> devName;
    static const litesql::FieldType DevPos;
    litesql::Field<int> devPos;
protected:
    void defaults();
public:
    DevInfoTable(const litesql::Database& db);
    DevInfoTable(const litesql::Database& db, const litesql::Record& rec);
    DevInfoTable(const DevInfoTable& obj);
    const DevInfoTable& operator=(const DevInfoTable& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<DevInfoTable> upcast() const;
    std::auto_ptr<DevInfoTable> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, DevInfoTable o);
class MapSysDatabase : public litesql::Database {
public:
    MapSysDatabase(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
