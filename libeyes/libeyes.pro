TEMPLATE = lib
TARGET = eyes

DEPENDENCY_LIBRARIES += \
  glib-2.0 \
  gtop-2.0

DEPENDENCY_INCLUDES += \
  glib-2.0 \
  libgtop-2.0

QT += network

SOURCES += \
  eyes.cc \
  clapper.cc \
  animation.cc \
  looker.cc \
  core.cpp \
  configuration.cc \
  hardware.cc \
  cdbg.cc \
  ostream.cc \
  eyes_menu.cc \
  camera.cpp \
  tm.cc \
  hungarian.cpp \
  connection.cc \
    devhelper.cpp

HEADERS += \
  defines.hxx\
  animation.hxx\
  debug.hxx\
  eyes.hxx\
  core.hxx\
  configuration.hxx \
  cdbg.hxx \
  hardware.hxx \
  ostream.hh \
  eyes_menu.hh \
  camera.hxx \
  tm.hh \
  img_fileinfo.hh \
  hungarian.h \
  connection.hxx \
    devhelper.h

VERSION = 0.10.1

system(../scripts/checklibs)

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
  $$system(../scripts/libcfg --cflags glib-2.0) \
  $$system(../scripts/libcfg --cflags libgtop-2.0) \
  $$system(../scripts/libcfg --cflags stackonfigure) \
  $$system(../scripts/libcfg --cflags opencv)

LIBS += \
  $$system(../scripts/libcfg --libs glib-2.0) \
  $$system(../scripts/libcfg --libs libgtop-2.0) \
  $$system(../scripts/libcfg --libs stackonfigure) \
  $$system(../scripts/libcfg --libs opencv) \
  -lrt

system ( echo "libEyes configured." )
system ( echo "  type 'make' to build libEyes." )

FORMS += \
    devhelper.ui
