APP_NAME = T3Presenter

CONFIG += qt warn_on cascades10
LIBS   += -lpps -lscreen -lEGL -lGLESv1_CM -lfreetype -lpng  -lbb -lbbutility
 QT += network
 LIBS += -lpng14 

include(config.pri)
