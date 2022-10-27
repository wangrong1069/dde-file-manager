// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "../dbusservice/dbusinterface/vaultbruteforceprevention_interface.h"

/*
 * Implementation of interface class VaultBruteForcePreventionInterface
 */

VaultBruteForcePreventionInterface::VaultBruteForcePreventionInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

VaultBruteForcePreventionInterface::~VaultBruteForcePreventionInterface()
{
}
