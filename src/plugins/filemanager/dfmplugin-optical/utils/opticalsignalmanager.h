/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhangsheng<zhangsheng@uniontech.com>
 *
 * Maintainer: max-lv<lvwujun@uniontech.com>
 *             lanxuesong<lanxuesong@uniontech.com>
 *             xushitong<xushitong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef OPTICALSIGNALMANAGER_H
#define OPTICALSIGNALMANAGER_H

#include "dfmplugin_optical_global.h"

#include <QObject>

DPOPTICAL_BEGIN_NAMESPACE

class OpticalSignalManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OpticalSignalManager)

public:
    static OpticalSignalManager *instance();

signals:
    void discUnmounted(const QUrl &url);

private:
    explicit OpticalSignalManager(QObject *parent = nullptr);
};

DPOPTICAL_END_NAMESPACE

#endif   // OPTICALSIGNALMANAGER_H
