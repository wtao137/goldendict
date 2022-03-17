#include "globalbroadcaster.h"
#include <QGlobalStatic>


Q_GLOBAL_STATIC(GlobalBroadcaster, bdcaster)
GlobalBroadcaster::GlobalBroadcaster(QObject *parent) : QObject(parent)
{
 qRegisterMetaType<AudioLink>("AudioLink");
}

void GlobalBroadcaster::emitAudioLink(AudioLink  al)
{
  emit audioLink(al);
}

GlobalBroadcaster* GlobalBroadcaster::instance() { return bdcaster; }

// namespace global
