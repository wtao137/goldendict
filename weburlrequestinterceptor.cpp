#include "weburlrequestinterceptor.h"
#include <QDebug>
#include "utils.hh"

WebUrlRequestInterceptor::WebUrlRequestInterceptor(QObject *p)
  :QWebEngineUrlRequestInterceptor(p)
{

}
void WebUrlRequestInterceptor::interceptRequest( QWebEngineUrlRequestInfo &info) {
  if (QWebEngineUrlRequestInfo::NavigationTypeLink == info.navigationType() && info.resourceType() == QWebEngineUrlRequestInfo::ResourceTypeMainFrame) {
    emit linkClicked(info.requestUrl());
    qDebug() << "interceptor [clicked]" << info.resourceType() << info.navigationType() << info.requestUrl();
    info.block(true);
  }
  else
  {
    qDebug() << "interceptor" << info.resourceType()<<info.navigationType()<<info.requestUrl();
  }
}
