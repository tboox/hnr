/****************************************************************************
** Meta object code from reading C++ file 'qimagescene.h'
**
** Created: Wed Jul 1 20:48:29 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qimagescene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qimagescene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QImageScene[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      26,   12,   12,   12, 0x08,
      39,   12,   12,   12, 0x08,
      54,   12,   12,   12, 0x08,
      74,   12,   12,   12, 0x08,
      91,   12,   12,   12, 0x08,
     119,   12,   12,   12, 0x08,
     146,   12,   12,   12, 0x08,
     175,   12,   12,   12, 0x08,
     203,   12,   12,   12, 0x08,
     225,   12,   12,   12, 0x08,
     249,   12,   12,   12, 0x08,
     266,   12,   12,   12, 0x08,
     281,   12,   12,   12, 0x08,
     301,   12,   12,   12, 0x08,
     309,   12,   12,   12, 0x08,
     319,   12,   12,   12, 0x08,
     328,   12,   12,   12, 0x08,
     340,   12,   12,   12, 0x08,
     347,   12,   12,   12, 0x08,
     356,   12,   12,   12, 0x08,
     367,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QImageScene[] = {
    "QImageScene\0\0gy_general()\0gy_stretch()\0"
    "gy_histogram()\0gy_part_histogram()\0"
    "oh_mean_smooth()\0th_global_basic_threshold()\0"
    "th_global_otsu_threshold()\0"
    "th_partial_basic_threshold()\0"
    "th_partial_otsu_threshold()\0"
    "dn_median_denoising()\0dn_discrete_denoising()\0"
    "cs_kmean_split()\0cs_fcm_split()\0"
    "cs_labeling_split()\0sobel()\0prewitt()\0"
    "kirsch()\0isotropic()\0marr()\0deskew()\0"
    "thinning()\0pp_preprocess()\0"
};

const QMetaObject QImageScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_QImageScene,
      qt_meta_data_QImageScene, 0 }
};

const QMetaObject *QImageScene::metaObject() const
{
    return &staticMetaObject;
}

void *QImageScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QImageScene))
        return static_cast<void*>(const_cast< QImageScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int QImageScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: gy_general(); break;
        case 1: gy_stretch(); break;
        case 2: gy_histogram(); break;
        case 3: gy_part_histogram(); break;
        case 4: oh_mean_smooth(); break;
        case 5: th_global_basic_threshold(); break;
        case 6: th_global_otsu_threshold(); break;
        case 7: th_partial_basic_threshold(); break;
        case 8: th_partial_otsu_threshold(); break;
        case 9: dn_median_denoising(); break;
        case 10: dn_discrete_denoising(); break;
        case 11: cs_kmean_split(); break;
        case 12: cs_fcm_split(); break;
        case 13: cs_labeling_split(); break;
        case 14: sobel(); break;
        case 15: prewitt(); break;
        case 16: kirsch(); break;
        case 17: isotropic(); break;
        case 18: marr(); break;
        case 19: deskew(); break;
        case 20: thinning(); break;
        case 21: pp_preprocess(); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
