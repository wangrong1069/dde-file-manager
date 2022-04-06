/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     liqiang<liqianga@uniontech.com>
 *
 * Maintainer: liqiang<liqianga@uniontech.com>
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
#include "openwithmenuscene.h"
#include "action_defines.h"
#include "private/openwithmenuscene_p.h"

#include <services/common/menu/menu_defines.h>

#include <dfm-base/mimetype/mimesappsmanager.h>
#include <dfm-base/base/schemefactory.h>
#include <dfm-base/file/local/desktopfileinfo.h>

#include <QMenu>
#include <QVariant>

DPMENU_USE_NAMESPACE
DFMBASE_USE_NAMESPACE
DSC_USE_NAMESPACE

AbstractMenuScene *OpenWithMenuCreator::create()
{
    return new OpenWithMenuScene();
}

OpenWithMenuScenePrivate::OpenWithMenuScenePrivate(OpenWithMenuScene *qq)
    : AbstractMenuScenePrivate(qq)
{
    predicateName[ActionID::kOpenWith] = tr("Open with");
}

OpenWithMenuScene::OpenWithMenuScene(QObject *parent)
    : AbstractMenuScene(parent),
      d(new OpenWithMenuScenePrivate(this))
{
}

QString OpenWithMenuScene::name() const
{
    return OpenWithMenuCreator::name();
}

bool OpenWithMenuScene::initialize(const QVariantHash &params)
{
    d->currentDir = params.value(MenuParamKey::kCurrentDir).toUrl();
    d->selectFiles = params.value(MenuParamKey::kSelectFiles).value<QList<QUrl>>();
    d->focusFile = params.value(MenuParamKey::kFocusFile).toUrl();
    d->onDesktop = params.value(MenuParamKey::kOnDesktop).toBool();

    // 文件不存在，则无文件相关菜单项
    if (d->selectFiles.isEmpty())
        return false;

    QString errString;
    d->focusFileInfo = DFMBASE_NAMESPACE::InfoFactory::create<AbstractFileInfo>(d->focusFile, true, &errString);
    if (d->focusFileInfo.isNull()) {
        qDebug() << errString;
        return false;
    }

    d->recommendApps = MimesAppsManager::instance()->getRecommendedApps(d->focusFileInfo->redirectedFileUrl());

    // why?
    d->recommendApps.removeAll("/usr/share/applications/dde-open.desktop");
    d->recommendApps.removeAll("/usr/share/applications/display-im6.q16.desktop");
    d->recommendApps.removeAll("/usr/share/applications/display-im6.q16hdri.desktop");

    return !d->recommendApps.isEmpty();
}

AbstractMenuScene *OpenWithMenuScene::scene(QAction *action) const
{
    if (action == nullptr)
        return nullptr;

    if (d->predicateAction.values().contains(action))
        return const_cast<OpenWithMenuScene *>(this);

    return AbstractMenuScene::scene(action);
}

bool OpenWithMenuScene::create(QMenu *parent)
{
    if (d->selectFiles.isEmpty() || !d->focusFile.isValid())
        return false;

    QAction *tempAction = parent->addAction(d->predicateName.value(ActionID::kOpenWith));
    d->predicateAction[ActionID::kOpenWith] = tempAction;
    tempAction->setProperty(ActionPropertyKey::kActionID, QString(ActionID::kOpenWith));

    QMenu *subMenu = new QMenu(parent);
    tempAction->setMenu(subMenu);

    QList<QUrl> redirectedUrlList;
    for (const auto &fileUrl : d->selectFiles) {
        QString errString;
        auto fileInfo = DFMBASE_NAMESPACE::InfoFactory::create<AbstractFileInfo>(fileUrl, true, &errString);
        if (fileInfo.isNull()) {
            qDebug() << errString;
            continue;
        }
        redirectedUrlList << fileInfo->redirectedFileUrl();
    }

    foreach (QString app, d->recommendApps) {
        app = QUrl::fromLocalFile(app).toString();
        DesktopFileInfo desktop(app);
        QAction *action = subMenu->addAction(desktop.fileIcon(), desktop.fileDisplayName());

        // TODO(Lee or others): 此种外部注入的未分配谓词
        d->predicateAction[app] = tempAction;

        // action->setIcon(FileUtils::searchAppIcon(desktopFile));
        action->setProperty("app", app);
        action->setProperty("redirectedUrls", QVariant::fromValue(redirectedUrlList));
        subMenu->addAction(action);
    }

    return true;
}

void OpenWithMenuScene::updateState(QMenu *parent)
{
    if (!parent)
        return;
}

bool OpenWithMenuScene::triggered(QAction *action)
{
    Q_UNUSED(action)
    // TODO(Lee or others):

    return false;
}
