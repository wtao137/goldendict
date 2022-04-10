/* Thin wrappers for retaining compatibility for both Qt4.x and Qt5.x */

#ifndef UTILS_HH
#define UTILS_HH

#include <QString>
#include <QAtomicInt>
#include <QTextDocument>
#include <QKeyEvent>
#include <QUrl>
#include <QUrlQuery>
#include <string>
using std::string;
namespace Utils
{

/**
 * remove right end space
 */
inline QString rstrip(const QString &str) {
  int n = str.size() - 1;
  for (; n >= 0; --n) {
    if (!str.at(n).isSpace()) {
      return str.left(n + 1);
    }
  }
  return "";
}

inline string repeat(string s, int n) {
  string repeat;

  for (int i = 0; i < n; i++)
    repeat += s;

  return repeat;
}

inline bool isExternalLink(QUrl const &url) {
  return url.scheme() == "http" || url.scheme() == "https" ||
         url.scheme() == "ftp" || url.scheme() == "mailto" ||
         url.scheme() == "file";
}

inline QString escape( QString const & plain )
{
  return plain.toHtmlEscaped();
}

// should ignore key event.
inline bool ignoreKeyEvent(QKeyEvent *keyEvent) {
  if ( keyEvent->key() == Qt::Key_Space ||
      keyEvent->key() == Qt::Key_Backspace ||
      keyEvent->key() == Qt::Key_Tab ||
      keyEvent->key() == Qt::Key_Backtab ||
      keyEvent->key() == Qt::Key_Escape)
    return true;
  return false;
}

namespace AtomicInt
{

inline int loadAcquire( QAtomicInt const & ref )
{
  return ref.loadAcquire();
}

}

namespace Url
{
// This wrapper is created due to behavior change of the setPath() method
// See: https://bugreports.qt-project.org/browse/QTBUG-27728
//       https://codereview.qt-project.org/#change,38257
inline QString ensureLeadingSlash( const QString & path )
{
  QLatin1Char slash( '/' );
  if ( path.startsWith( slash ) )
    return path;
  return slash + path;
}

inline bool hasQueryItem( QUrl const & url, QString const & key )
{
  return QUrlQuery( url ).hasQueryItem( key );
}

inline QString queryItemValue( QUrl const & url, QString const & item )
{
  return QUrlQuery( url ).queryItemValue( item, QUrl::FullyDecoded );
}

inline QByteArray encodedQueryItemValue( QUrl const & url, QString const & item )
{
  return QUrlQuery( url ).queryItemValue( item, QUrl::FullyEncoded ).toLatin1();
}

inline void addQueryItem( QUrl & url, QString const & key, QString const & value )
{
  QUrlQuery urlQuery( url );
  urlQuery.addQueryItem( key, value );
  url.setQuery( urlQuery );
}

inline void removeQueryItem( QUrl & url, QString const & key )
{
  QUrlQuery urlQuery( url );
  urlQuery.removeQueryItem( key );
  url.setQuery( urlQuery );
}

inline void setQueryItems( QUrl & url, QList< QPair< QString, QString > > const & query )
{
  QUrlQuery urlQuery( url );
  urlQuery.setQueryItems( query );
  url.setQuery( urlQuery );
}

inline QString path( QUrl const & url )
{
  return url.path( QUrl::FullyDecoded );
}

inline void setFragment( QUrl & url, const QString & fragment )
{
  url.setFragment( fragment, QUrl::DecodedMode );
}

inline QString fragment( const QUrl & url )
{
  return url.fragment( QUrl::FullyDecoded );
}

// extract query word from url
inline QString getWordFromUrl( const QUrl & url )
{
  QString word;
  if( url.scheme().compare( "bword" ) == 0 )
  {
    word = url.path();
  }
  else if( url.scheme() == "gdlookup" ) // Plain html links inherit gdlookup scheme
  {
    if( hasQueryItem( url, "word" ) )
    {
      word = queryItemValue( url, "word" );
    }
    else
    {
      word = url.path().mid( 1 );
    }
  }

  return word;
}
}

}

#endif // UTILS_HH
