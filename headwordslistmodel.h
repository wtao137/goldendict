#ifndef HEADWORDSLISTMODEL_H
#define HEADWORDSLISTMODEL_H

#include "dictionary.hh"

#include <QAbstractListModel>
#include <QStringList>

class HeadwordListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    HeadwordListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void numberPopulated(int number);

public slots:
  void setDict(Dictionary::Class * dict);

private:
    QStringList fileList;
    QAtomicInt wordsCount;
    long totalSize;
    Dictionary::Class * _dict;
};

#endif // HEADWORDSLISTMODEL_H
