/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c QuickSearchDaemonInterface -p ../interface/quicksearchdaemon_interface quicksearchdaemon.xml
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef QUICKSEARCHDAEMON_INTERFACE_H
#define QUICKSEARCHDAEMON_INTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.filemanager.daemon.QuickSearchDaemon
 */
class QuickSearchDaemonInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.filemanager.daemon.QuickSearchDaemon"; }

public:
    QuickSearchDaemonInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~QuickSearchDaemonInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusVariant> createCache()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("createCache"), argumentList);
    }

    inline QDBusPendingReply<QDBusVariant> search(const QDBusVariant &current_dir, const QDBusVariant &key_words)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(current_dir) << QVariant::fromValue(key_words);
        return asyncCallWithArgumentList(QStringLiteral("search"), argumentList);
    }

    inline QDBusPendingReply<QDBusVariant> whetherCacheCompletely()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("whetherCacheCompletely"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace deepin {
    namespace filemanager {
      namespace daemon {
        typedef ::QuickSearchDaemonInterface QuickSearchDaemon;
      }
    }
  }
}
#endif
