/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.12.4
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

  // C:/Users/Admin/Videos/XUEXI/QMapSystem/SystemConfig.qml
  
  
    // C:/Users/Admin/Videos/XUEXI/QMapSystem/main.qml
  
  
  
static const unsigned char qt_resource_data[3717] = { 'Q', 'R', 'C', '_', 'D', 'A', 'T', 'A' };

static const unsigned char qt_resource_name[] = {
  // SystemConfig.qml
  0x0,0x10,
  0x9,0x70,0x5a,0x1c,
  0x0,0x53,
  0x0,0x79,0x0,0x73,0x0,0x74,0x0,0x65,0x0,0x6d,0x0,0x43,0x0,0x6f,0x0,0x6e,0x0,0x66,0x0,0x69,0x0,0x67,0x0,0x2e,0x0,0x71,0x0,0x6d,0x0,0x6c,
    // main.qml
  0x0,0x8,
  0x8,0x1,0x5a,0x5c,
  0x0,0x6d,
  0x0,0x61,0x0,0x69,0x0,0x6e,0x0,0x2e,0x0,0x71,0x0,0x6d,0x0,0x6c,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/main.qml
  0x0,0x0,0x0,0x26,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x9,0xd,
0x0,0x0,0x1,0x86,0x46,0x8c,0x2f,0x50,
  // :/SystemConfig.qml
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x86,0x46,0x8e,0x38,0xbf,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_qml)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_qml)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x2, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qml)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qml)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x2, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_qml)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qml)(); }
   } dummy;
}
