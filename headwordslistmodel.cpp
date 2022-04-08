#include "headwordslistmodel.h"

HeadwordListModel::HeadwordListModel(QObject *parent)
    : QAbstractListModel(parent), wordsCount(0)
{}

int HeadwordListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : wordsCount.loadAcquire();
}

QVariant HeadwordListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= totalSize || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return fileList.at(index.row());
    }
    return QVariant();
}

void HeadwordListModel::setDict(Dictionary::Class * dict){
  _dict = dict;
  beginResetModel();
  totalSize = dict->getWordCount();
  wordsCount=0;
  endResetModel();
  QThreadPool::globalInstance()->start(
    [ this, dict ]()
    {
      dict->getHeadwords( fileList );
      totalSize = fileList.size();
    } );
  QThreadPool::globalInstance()->start(
    [ this ]()
    {
      while(wordsCount<totalSize){
        auto existedHeadsCount = fileList.size();
        if( existedHeadsCount > wordsCount + 100 || existedHeadsCount>=totalSize)
        {
          beginInsertRows( QModelIndex(), wordsCount, existedHeadsCount - 1 );
          wordsCount.storeRelaxed(existedHeadsCount);
          endInsertRows();
        }
          QThread::msleep(0);
      }
    } );

}

