# -------------------------------------------------
# Project created by QtCreator 2009-01-01T19:08:36
# -------------------------------------------------
QT += sql
TARGET = HNR
CONFIG += qt \
    warn_on
contains(QT_BUILD_PARTS, tools):CONFIG += uitools
else:DEFINES += QT_NO_UITOOLS

TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    sampleview.cpp \
    imageconvector.cpp \
    qimagescene.cpp
HEADERS += mainwindow.h \
    qimage_painter.h \
    sample_helper.h \
    sampleview.h \
    network.h \
    imageconvector.h \
    prefix.h \
    sh_gy.h \
    sh_oh.h \
    sh_th.h \
    sh_cs.h \
    sh_rl.h \
    sh_dn.h \
    sh_pp.h \
    sh_zm.h \
    sh_dk.h \
    sh_tn.h \
    sh_ed.h \
    sh_fx.h \
    sh_hp.h \
    sh_sc.h \
    qimagescene.h
FORMS += mainwindow.ui
RESOURCES += res/res.qrc
