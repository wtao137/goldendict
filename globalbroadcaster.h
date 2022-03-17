#ifndef GLOBAL_GLOBALBROADCASTER_H
#define GLOBAL_GLOBALBROADCASTER_H

#include <QObject>
#include <string>
#include <QMetaType>
struct ActiveDictIds {
  QString word;
  QStringList dictIds;
}
;

struct AudioLink {
  QString dictId;
  QString audioLink;
}
;
Q_DECLARE_METATYPE(AudioLink)
class GlobalBroadcaster : public QObject
{
  Q_OBJECT
public:
  GlobalBroadcaster(QObject *parent = nullptr);
  static GlobalBroadcaster *instance();
  void emitAudioLink(AudioLink  al);
signals:
  void audioLink(AudioLink  al);

  void emitDictIds(ActiveDictIds  ad);

};


#endif // GLOBAL_GLOBALBROADCASTER_H
