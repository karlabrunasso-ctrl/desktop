/*
 * SPDX-FileCopyrightText: 2016 Nextcloud GmbH and Nextcloud contributors
 * SPDX-FileCopyrightText: 2012 ownCloud GmbH
 * SPDX-License-Identifier: GPL-2.0-or-later
 * MODIFIED FOR: marchingegno cloud
 */

#include "theme.h"
#include "common/utility.h"
#include "version.h"
#include "configfile.h"
#include "common/vfs.h"

#include <QtCore>
#ifndef TOKEN_AUTH_ONLY
#include <QtGui>
#include <QStyle>
#include <QApplication>
#endif
#include <QGuiApplication>
#include <QStyleHints>
#include <QSslSocket>
#include <QSvgRenderer>
#include <QPainter>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLoggingCategory>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "nextcloudtheme.h"

#ifdef THEME_INCLUDE
#define Mirall OCC // namespace hack to make old themes work
#define QUOTEME(M) #M
#define INCLUDE_FILE(M) QUOTEME(M)
#include INCLUDE_FILE(THEME_INCLUDE)
#undef Mirall
#endif

namespace {

QUrl imagePathToUrl(const QString &imagePath)
{
    if (imagePath.startsWith(':')) {
        auto url = QUrl();
        url.setScheme(QStringLiteral("qrc"));
        url.setPath(imagePath.mid(1));
        return url;
    } else {
        return QUrl::fromLocalFile(imagePath);
    }
}

bool shouldPreferSvg()
{
    return QByteArray(APPLICATION_ICON_SET).toUpper() == QByteArrayLiteral("SVG");
}

#ifdef Q_OS_WIN
bool isWindows11OrGreater() {
    return QOperatingSystemVersion::current().version() >= QOperatingSystemVersion::Windows11.version();
}
#endif

}

namespace OCC {

Q_LOGGING_CATEGORY(lcTheme, "marchingegno.gui.theme", QtInfoMsg)

Theme *Theme::_instance = nullptr;

Theme *Theme::instance()
{
    if (!_instance) {
        _instance = new THEME_CLASS;
        _instance->_mono = false;
    }
    return _instance;
}

Theme::~Theme() = default;

QString Theme::statusHeaderText(SyncResult::Status status) const
{
    QString resultStr;

    switch (status) {
    case SyncResult::Undefined:
        resultStr = QCoreApplication::translate("theme", "Sync status is unknown");
        break;
    case SyncResult::NotYetStarted:
        resultStr = QCoreApplication::translate("theme", "Waiting to start syncing");
        break;
    case SyncResult::SyncRunning:
        resultStr = QCoreApplication::translate("theme", "Sync is running");
        break;
    case SyncResult::Success:
        resultStr = QCoreApplication::translate("theme", "Sync was successful");
        break;
    case SyncResult::Problem:
        resultStr = QCoreApplication::translate("theme", "Sync was successful but some files were ignored");
        break;
    case SyncResult::Error:
        resultStr = QCoreApplication::translate("theme", "Error occurred during sync");
        break;
    case SyncResult::SetupError:
        resultStr = QCoreApplication::translate("theme", "Error occurred during setup");
        break;
    case SyncResult::SyncPrepare:
        resultStr = QCoreApplication::translate("theme", "Preparing to sync");
        break;
    case SyncResult::SyncAbortRequested:
        resultStr = QCoreApplication::translate("theme", "Stopping sync");
        break;
    case SyncResult::Paused:
        resultStr = QCoreApplication::translate("theme", "Sync is paused");
        break;
    }
    return resultStr;
}

bool Theme::isBranded() const
{
    // Forziamo il branding personalizzato
    return true;
}

QString Theme::appNameGUI() const
{
    // NOME VISIBILE NELLE FINESTRE
    return QStringLiteral("marchingegno cloud");
}

QString Theme::appName() const
{
    // NOME INTERNO/CARTELLA CONFIGURAZIONE
    return QStringLiteral("marchingegnocloud");
}

// --- LOGICA DELLE IMMAGINI (Rimane invariata, userà quelle che sostituirai nella cartella branding) ---
QUrl Theme::stateOnlineImageSource() const { return imagePathToUrl(themeImagePath("state-ok")); }
QUrl Theme::stateOfflineImageSource() const { return imagePathToUrl(themeImagePath("state-offline", 16)); }
QUrl Theme::statusOnlineImageSource() const { return imagePathToUrl(themeImagePath("user-status-online", 16)); }
QUrl Theme::statusDoNotDisturbImageSource() const { return imagePathToUrl(themeImagePath("user-status-dnd", 16)); }
QUrl Theme::statusAwayImageSource() const { return imagePathToUrl(themeImagePath("user-status-away", 16)); }
QUrl Theme::statusBusyImageSource() const { return imagePathToUrl(themeImagePath("user-status-busy", 16)); }
QUrl Theme::statusInvisibleImageSource() const { return imagePathToUrl(themeImagePath("user-status-invisible", 64)); }
QUrl Theme::syncStatusOk() const { return imagePathToUrl(themeImagePath("state-ok", 16)); }
QUrl Theme::syncStatusError() const { return imagePathToUrl(themeImagePath("state-error", 16)); }
QUrl Theme::syncStatusRunning() const { return imagePathToUrl(themeImagePath("state-sync", 16)); }
QUrl Theme::syncStatusPause() const { return imagePathToUrl(themeImagePath("state-pause", 16)); }
QUrl Theme::syncStatusWarning() const { return imagePathToUrl(themeImagePath("state-warning", 16)); }
QUrl Theme::folderOffline() const { return imagePathToUrl(themeImagePath("state-offline")); }
QUrl Theme::offline() const { return imagePathToUrl(themeImagePath("offline")); }
QUrl Theme::ok() const { return imagePathToUrl(themeImagePath("ok")); }
QUrl Theme::error() const { return imagePathToUrl(themeImagePath("error")); }
QUrl Theme::sync() const { return imagePathToUrl(themeImagePath("sync")); }
QUrl Theme::pause() const { return imagePathToUrl(themeImagePath("pause")); }
QUrl Theme::warning() const { return imagePathToUrl(themeImagePath("warning")); }

QString Theme::version() const { return MIRALL_VERSION_STRING; }
QString Theme::versionSuffix() const { return QString::fromLatin1(MIRALL_VERSION_SUFFIX); }
QString Theme::configFileName() const { return QStringLiteral("marchingegnocloud.cfg"); }

#ifndef TOKEN_AUTH_ONLY
QIcon Theme::applicationIcon() const
{
    return themeIcon(QStringLiteral(APPLICATION_ICON_NAME "-icon"));
}

QIcon Theme::themeIcon(const QString &name, bool sysTray) const
{
    QString flavor = sysTray ? systrayIconFlavor(_mono) : QLatin1String("colored");
    QString key = name + "," + flavor;
    QIcon &cached = _iconCache[key];
    if (cached.isNull()) {
        const auto useSvg = shouldPreferSvg();
        const auto sizes = useSvg ? QVector<int>{ 16, 32, 64, 128, 256 }
                                  : QVector<int>{ 16, 22, 32, 48, 64, 128, 256, 512, 1024 };
        for (int size : sizes) {
            const QString filePath = useSvg 
                ? QString(Theme::themePrefix) + QString::fromLatin1("%1/%2.svg").arg(flavor).arg(name)
                : QString(Theme::themePrefix) + QString::fromLatin1("%1/%2-%3.png").arg(flavor).arg(name).arg(size);
            QPixmap px(filePath);
            if (!px.isNull()) cached.addPixmap(px);
        }
    }
    return cached;
}

QString Theme::themeImagePath(const QString &name, int size, bool sysTray) const
{
    const auto flavor = QLatin1String("colored");
    const auto useSvg = shouldPreferSvg();
    const QString filePath = (useSvg || size <= 0)
            ? QString(Theme::themePrefix) + QString::fromLatin1("%1/%2").arg(flavor).arg(name)
            : QString(Theme::themePrefix) + QString::fromLatin1("%1/%2-%3").arg(flavor).arg(name).arg(size);
    return useSvg ? filePath + ".svg" : filePath + ".png";
}

bool Theme::isHidpi(QPaintDevice *dev)
{
    const auto devicePixelRatio = dev ? dev->devicePixelRatio() : qApp->primaryScreen()->devicePixelRatio();
    return devicePixelRatio > 1;
}

QIcon Theme::uiThemeIcon(const QString &iconName, bool uiHasDarkBg) const
{
    QString iconPath = QString(Theme::themePrefix) + (uiHasDarkBg ? "white/" : "black/") + iconName;
    return QIcon(QPixmap(iconPath));
}

QString Theme::hidpiFileName(const QString &fileName, QPaintDevice *dev)
{
    if (!Theme::isHidpi(dev)) return fileName;
    const int dotIndex = fileName.lastIndexOf(QLatin1Char('.'));
    if (dotIndex != -1) {
        QString at2xfileName = fileName;
        at2xfileName.insert(dotIndex, QStringLiteral("@2x"));
        if (QFile::exists(at2xfileName)) return at2xfileName;
    }
    return fileName;
}

QString Theme::hidpiFileName(const QString &iconName, const QColor &backgroundColor, QPaintDevice *dev)
{
    const auto isDarkBackground = Theme::isDarkColor(backgroundColor);
    const QString iconPath = QString(Theme::themePrefix) + (isDarkBackground ? "white/" : "black/") + iconName;
    return Theme::hidpiFileName(iconPath, dev);
}
#endif

Theme::Theme() : QObject(nullptr)
{
    connectToPaletteSignal();
    
    // --- FORZATURA DEL SERVER ---
    _forceOverrideServerUrl = true;
    setOverrideServerUrl(QStringLiteral("https://cloud.marchingegno.info"));
}

QString Theme::developerStringInfo() const
{
    return QStringLiteral("marchingegno cloud Desktop Client Version %1")
           .arg(QString::fromLatin1(MIRALL_HUMAN_VERSION_STRING));
}

bool Theme::singleSyncFolder() const { return false; }
bool Theme::multiAccount() const { return true; }
QString Theme::defaultServerFolder() const { return QLatin1String("/"); }

QString Theme::helpUrl() const
{
    // Puoi cambiare questa URL con la tua pagina di supporto
    return QStringLiteral("https://marchingegno.info/support");
}

QString Theme::conflictHelpUrl() const
{
    return helpUrl() + QStringLiteral("/conflicts");
}

QString Theme::overrideServerUrl() const { return _overrideServerUrl; }
bool Theme::forceOverrideServerUrl() const { return _forceOverrideServerUrl; }

void Theme::updateMultipleOverrideServers() { _multipleOverrideServers = false; }
bool Theme::multipleOverrideServers() const { return _multipleOverrideServers; }
bool Theme::isVfsEnabled() const { return _isVfsEnabled; }
bool Theme::startLoginFlowAutomatically() const { return true; }
bool Theme::enableStaplingOCSP() const { return true; }
bool Theme::forbidBadSSL() const { return true; }

QString Theme::forceConfigAuthType() const { return QString(); }
QString Theme::defaultClientFolder() const { return appName(); }

QString Theme::systrayIconFlavor(bool mono) const
{
    if (mono) return Utility::hasDarkSystray() ? QLatin1String("white") : QLatin1String("black");
    return QLatin1String("colored");
}

void Theme::setSystrayUseMonoIcons(bool mono) { _mono = mono; emit systrayUseMonoIconsChanged(mono); }
bool Theme::systrayUseMonoIcons() const { return _mono; }
bool Theme::monoIconsAvailable() const { return true; }
QString Theme::updateCheckUrl() const { return QString(); } // Disabilitiamo update Nextcloud originali
qint64 Theme::newBigFolderSizeLimit() const { return 500; }
bool Theme::wizardHideExternalStorageConfirmationCheckbox() const { return false; }
bool Theme::wizardHideFolderSizeLimitCheckbox() const { return false; }

QString Theme::gitSHA1() const { return QString(); }

QString Theme::aboutInfo() const
{
    return tr("<p>marchingegno cloud Desktop Client</p><p>Il tuo cloud personalizzato.</p>");
}

QString Theme::about() const { return appNameGUI(); }

QString Theme::aboutDetails() const
{
    return tr("<p>Questo software è fornito da marchingegno cloud.</p>");
}

#ifndef TOKEN_AUTH_ONLY
QVariant Theme::customMedia(CustomMediaType type) { return QVariant(); }

QIcon Theme::syncStateIcon(SyncResult::Status status, bool sysTray) const
{
    QString statusIcon;
    switch (status) {
        case SyncResult::Success: statusIcon = QLatin1String("state-ok"); break;
        case SyncResult::SyncRunning: statusIcon = QLatin1String("state-sync"); break;
        case SyncResult::Paused: statusIcon = QLatin1String("state-pause"); break;
        case SyncResult::Problem: statusIcon = QLatin1String("state-warning"); break;
        case SyncResult::Error: statusIcon = QLatin1String("state-error"); break;
        default: statusIcon = QLatin1String("state-ok");
    }
    return themeIcon(statusIcon, sysTray);
}

QIcon Theme::folderStateIcon(SyncResult::Status status) const
{
    return syncStateIcon(status, false);
}

QIcon Theme::folderOfflineIcon(bool sysTray) const { return themeIcon(QLatin1String("state-offline"), sysTray); }
QColor Theme::wizardHeaderTitleColor() const { return Qt::white; }
QColor Theme::wizardHeaderBackgroundColor() const { return QColor(0, 130, 200); } // Blu brand (cambialo se vuoi)

QPixmap Theme::wizardApplicationLogo() const { return applicationIcon().pixmap(128); }
QPixmap Theme::wizardHeaderLogo() const { return applicationIcon().pixmap(64); }

QPixmap Theme::wizardHeaderBanner() const
{
    QPixmap pix(750, 78);
    pix.fill(wizardHeaderBackgroundColor());
    return pix;
}
#endif

bool Theme::wizardSelectiveSyncDefaultNothing() const { return false; }
bool Theme::linkSharing() const { return true; }
bool Theme::userGroupSharing() const { return true; }
bool Theme::forceSystemNetworkProxy() const { return false; }
Theme::UserIDType Theme::userIDType() const { return UserIDType::UserIDUserName; }
QString Theme::customUserID() const { return QString(); }
QString Theme::userIDHint() const { return QString(); }
QString Theme::wizardUrlHint() const { return QString(); }
QString Theme::quotaBaseFolder() const { return QLatin1String("/"); }

QString Theme::versionSwitchOutput() const
{
    return QStringLiteral("marchingegno cloud version %1").arg(version());
}

double Theme::getColorDarkness(const QColor &color) { return 1.0 - (0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) / 255.0; }
bool Theme::isDarkColor(const QColor &color) { return getColorDarkness(color) > 0.5; }
QColor Theme::getBackgroundAwareLinkColor(const QColor &backgroundColor) { return isDarkColor(backgroundColor) ? QColor(0x6193dc) : QColor(Qt::blue); }
QColor Theme::getBackgroundAwareLinkColor() { return getBackgroundAwareLinkColor(Qt::white); }
void Theme::replaceLinkColorStringBackgroundAware(QString &l, const QColor &b) { replaceLinkColorString(l, getBackgroundAwareLinkColor(b)); }
void Theme::replaceLinkColorStringBackgroundAware(QString &l) { replaceLinkColorStringBackgroundAware(l, Qt::white); }
void Theme::replaceLinkColorString(QString &s, const QColor &c) { 
    static const QRegularExpression r("(<a href|<a style='color:#([a-zA-Z0-9]{6});' href)");
    s.replace(r, QStringLiteral("<a style='color:%1;' href").arg(c.name()));
}

QIcon Theme::createColorAwareIcon(const QString &name, const QPalette &palette) { return QIcon(name); }
QIcon Theme::createColorAwareIcon(const QString &name) { return QIcon(name); }
QPixmap Theme::createColorAwarePixmap(const QString &name, const QPalette &p) { return QPixmap(name); }
QPixmap Theme::createColorAwarePixmap(const QString &name) { return QPixmap(name); }

bool Theme::showVirtualFilesOption() const { return true; }
bool Theme::enforceVirtualFilesSyncFolder() const { return true; }
bool Theme::disableVirtualFilesSyncFolder() const { return false; }
QColor Theme::defaultColor() { return QColor(0, 130, 200); }

void Theme::connectToPaletteSignal() const {
    if (const auto ptr = qobject_cast<QGuiApplication*>(qApp)) {
        connect(ptr->styleHints(), &QStyleHints::colorSchemeChanged, this, &Theme::darkModeChanged, Qt::UniqueConnection);
    }
}

QVariantMap Theme::systemPalette() const { return QVariantMap(); }
bool Theme::darkMode() const { return qGuiApp->styleHints()->colorScheme() == Qt::ColorScheme::Dark; }
bool Theme::displayLegacyImportDialog() const { return false; }

void Theme::setOverrideServerUrl(const QString &url) { _overrideServerUrl = url; emit overrideServerUrlChanged(); }
void Theme::setForceOverrideServerUrl(bool f) { _forceOverrideServerUrl = f; emit forceOverrideServerUrlChanged(); }
void Theme::setVfsEnabled(bool e) { _isVfsEnabled = e; emit vfsEnabledChanged(); }
void Theme::setStartLoginFlowAutomatically(bool s) { _startLoginFlowAutomatically = s; emit startLoginFlowAutomaticallyChanged(); }
void Theme::systemPaletteHasChanged() {}

} // end namespace client