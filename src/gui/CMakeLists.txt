# SPDX-FileCopyrightText: 2017 Nextcloud GmbH and Nextcloud contributors
# SPDX-FileCopyrightText: 2014 ownCloud GmbH
# SPDX-License-Identifier: GPL-2.0-or-later
project(gui)
find_package(Qt${QT_MAJOR_VERSION} REQUIRED COMPONENTS Widgets Svg Qml Quick QuickControls2 QuickWidgets Xml Network)
find_package(KF6Archive REQUIRED)
find_package(KF6GuiAddons)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DQT_QML_DEBUG)
endif()

IF(BUILD_UPDATER)
    add_subdirectory(updater)
endif()

# Icon switch: forziamo l'uso delle icone caricate ieri
set(STATE_SUBDIR "")
if(APPLICATION_NAME STREQUAL "Marchingegno Cloud")
    set(STATE_SUBDIR "")
endif()

configure_file(${CMAKE_SOURCE_DIR}/theme.qrc.in ${CMAKE_SOURCE_DIR}/theme.qrc)
set(theme_dir ${CMAKE_SOURCE_DIR}/theme)

set(client_UI_SRCS
    accountsettings.ui
    conflictdialog.ui
    invalidfilenamedialog.ui
    caseclashfilenamedialog.ui
    foldercreationdialog.ui
    folderwizardsourcepage.ui
    folderwizardtargetpage.ui
    generalsettings.ui
    legalnotice.ui
    ignorelisteditor.ui
    ignorelisttablewidget.ui
    networksettings.ui
    sslerrordialog.ui
    addcertificatedialog.ui
    passwordinputdialog.ui
    proxyauthdialog.ui
    mnemonicdialog.ui
    vfsdownloaderrordialog.ui
    wizard/flow2authwidget.ui
    wizard/owncloudadvancedsetuppage.ui
    wizard/owncloudconnectionmethoddialog.ui
    wizard/owncloudhttpcredspage.ui
    wizard/owncloudsetupnocredspage.ui
    wizard/termsofservicecheckwidget.ui
    wizard/webview.ui
    wizard/welcomepage.ui
    wizard/proxysettings.ui
)

qt_add_resources(client_UI_SRCS ../../resources.qrc ${CMAKE_SOURCE_DIR}/theme.qrc)

set(client_SRCS
    accountmanager.h
    accountmanager.cpp
    accountsettings.h
    accountsettings.cpp
    accountsetupfromcommandlinejob.h
    accountsetupfromcommandlinejob.cpp
    accountsetupcommandlinemanager.h
    accountsetupcommandlinemanager.cpp
    application.h
    application.cpp
    invalidfilenamedialog.h
    invalidfilenamedialog.cpp
    caseclashfilenamedialog.h
    caseclashfilenamedialog.cpp
    callstatechecker.h
    callstatechecker.cpp
    conflictdialog.h
    conflictdialog.cpp
    conflictsolver.h
    conflictsolver.cpp
    connectionvalidator.h
    connectionvalidator.cpp
    editlocallyjob.h
    editlocallyjob.cpp
    editlocallymanager.h
    editlocallymanager.cpp
    editlocallyverificationjob.h
    editlocallyverificationjob.cpp
    filetagmodel.h
    filetagmodel.cpp
    folder.h
    folder.cpp
    foldercreationdialog.h
    foldercreationdialog.cpp
    folderman.h
    folderman.cpp
    folderstatusmodel.h
    folderstatusmodel.cpp
    folderstatusdelegate.h
    folderstatusdelegate.cpp
    folderstatusview.h
    folderstatusview.cpp
    folderwatcher.h
    folderwatcher.cpp
    folderwizard.h
    folderwizard.cpp
    generalsettings.h
    generalsettings.cpp
    legalnotice.h
    legalnotice.cpp
    ignorelisteditor.h
    ignorelisteditor.cpp
    ignorelisttablewidget.h
    ignorelisttablewidget.cpp
    lockwatcher.h
    lockwatcher.cpp
    logbrowser.h
    logbrowser.cpp
    networksettings.h
    networksettings.cpp
    ocsnavigationappsjob.h
    ocsnavigationappsjob.cpp
    ocsjob.h
    ocsjob.cpp
    ocssharejob.h
    ocssharejob.cpp
    ocsshareejob.h
    ocsshareejob.cpp
    openfilemanager.h
    openfilemanager.cpp
    owncloudgui.h
    owncloudgui.cpp
    owncloudsetupwizard.h
    owncloudsetupwizard.cpp
    passwordinputdialog.h
    passwordinputdialog.cpp
    selectivesyncdialog.h
    selectivesyncdialog.cpp
    settingsdialog.h
    settingsdialog.cpp
    sharemanager.h
    sharemanager.cpp
    profilepagewidget.h
    profilepagewidget.cpp
    sharee.h
    sharee.cpp
    sslbutton.h
    sslbutton.cpp
    sslerrordialog.h
    sslerrordialog.cpp
    syncrunfilelog.h
    syncrunfilelog.cpp
    systray.h
    systray.cpp
    userinfo.h
    userinfo.cpp
    vfsdownloaderrordialog.h
    vfsdownloaderrordialog.cpp
    accountstate.h
    accountstate.cpp
    addcertificatedialog.h
    addcertificatedialog.cpp
    authenticationdialog.h
    authenticationdialog.cpp
    proxyauthhandler.h
    proxyauthhandler.cpp
    proxyauthdialog.h
    proxyauthdialog.cpp
    tooltipupdater.h
    tooltipupdater.cpp
    notificationconfirmjob.h
    notificationconfirmjob.cpp
    guiutility.h
    guiutility.cpp
    elidedlabel.h
    elidedlabel.cpp
    iconutils.h
    iconutils.cpp
    remotewipe.h
    remotewipe.cpp
    userstatusselectormodel.h
    userstatusselectormodel.cpp
    emojimodel.h
    emojimodel.cpp
    syncconflictsmodel.h
    syncconflictsmodel.cpp
    fileactivitylistmodel.h
    fileactivitylistmodel.cpp
    filedetails/datefieldbackend.h
    filedetails/datefieldbackend.cpp
    filedetails/filedetails.h
    filedetails/filedetails.cpp
    filedetails/sharemodel.h
    filedetails/sharemodel.cpp
    filedetails/shareemodel.h
    filedetails/shareemodel.cpp
    filedetails/sortedsharemodel.h
    filedetails/sortedsharemodel.cpp
    tray/svgimageprovider.h
    tray/svgimageprovider.cpp
    tray/syncstatussummary.h
    tray/syncstatussummary.cpp
    tray/activitydata.h
    tray/activitydata.cpp
    tray/activitylistmodel.h
    tray/activitylistmodel.cpp
    tray/unifiedsearchresult.h
    tray/asyncimageresponse.cpp
    tray/unifiedsearchresult.cpp
    tray/unifiedsearchresultslistmodel.h
    tray/trayimageprovider.cpp
    tray/unifiedsearchresultslistmodel.cpp
    tray/usermodel.h
    tray/usermodel.cpp
    tray/notificationhandler.h
    tray/notificationhandler.cpp
    tray/sortedactivitylistmodel.h
    tray/sortedactivitylistmodel.cpp
    creds/credentialsfactory.h
    tray/talkreply.cpp
    creds/credentialsfactory.cpp
    creds/httpcredentialsgui.h
    creds/httpcredentialsgui.cpp
    creds/flow2auth.h
    creds/flow2auth.cpp
    creds/webflowcredentials.h
    creds/webflowcredentials.cpp
    creds/webflowcredentialsdialog.h
    creds/webflowcredentialsdialog.cpp
    wizard/abstractcredswizardpage.h
    wizard/abstractcredswizardpage.cpp
    wizard/owncloudadvancedsetuppage.h
    wizard/owncloudadvancedsetuppage.cpp
    wizard/owncloudconnectionmethoddialog.h
    wizard/owncloudconnectionmethoddialog.cpp
    wizard/owncloudhttpcredspage.h
    wizard/owncloudhttpcredspage.cpp
    wizard/flow2authcredspage.h
    wizard/flow2authcredspage.cpp
    wizard/flow2authwidget.h
    wizard/flow2authwidget.cpp
    wizard/owncloudsetuppage.h
    wizard/owncloudsetuppage.cpp
    wizard/termsofservicecheckwidget.h
    wizard/termsofservicecheckwidget.cpp
    wizard/termsofservicewizardpage.h
    wizard/termsofservicewizardpage.cpp
    wizard/owncloudwizardcommon.h
    wizard/owncloudwizardcommon.cpp
    wizard/owncloudwizard.h
    wizard/owncloudwizard.cpp
    wizard/slideshow.h
    wizard/slideshow.cpp
    wizard/welcomepage.h
    wizard/welcomepage.cpp
    wizard/linklabel.h
    wizard/linklabel.cpp
    wizard/wizardproxysettingsdialog.h
    wizard/wizardproxysettingsdialog.cpp
    integration/fileactionsmodel.h
    integration/fileactionsmodel.cpp
    )

if (NOT DISABLE_ACCOUNT_MIGRATION)
    list(APPEND client_SRCS
        legacyaccountselectiondialog.h
        legacyaccountselectiondialog.cpp
    )
endif()

if (WITH_WEBENGINE)
  list(APPEND client_SRCS
    wizard/webviewpage.h
    wizard/webviewpage.cpp
    wizard/webview.h
    wizard/webview.cpp
  )
endif()

IF(BUILD_UPDATER)
    set(updater_SRCS
        updater/ocupdater.h
        updater/ocupdater.cpp
        updater/updateinfo.h
        updater/updateinfo.cpp
        updater/updater.h
        updater/updater.cpp
    )
endif()

IF( APPLE )
    list(APPEND client_SRCS cocoainitializer_mac.mm)
    list(APPEND client_SRCS systray_mac_common.mm)
    list(APPEND client_SRCS macOS/singleinstancemanager_mac.mm)
    list(APPEND client_SRCS systray_mac_usernotifications.mm)
ENDIF()

IF( NOT WIN32 AND NOT APPLE )
    set(client_SRCS ${client_SRCS} folderwatcher_linux.cpp)
ENDIF()
IF( WIN32 )
    set(client_SRCS
        ${client_SRCS}
        folderwatcher_win.cpp
        navigationpanehelper.h
        navigationpanehelper.cpp
        shellextensionsserver.cpp
        ${CMAKE_SOURCE_DIR}/src/common/shellextensionutils.cpp)
ENDIF()
IF( APPLE )
    list(APPEND client_SRCS folderwatcher_mac.cpp)
ENDIF()

set(3rdparty_SRC
    ../3rdparty/QProgressIndicator/QProgressIndicator.h
    ../3rdparty/QProgressIndicator/QProgressIndicator.cpp
    ../3rdparty/kmessagewidget/kmessagewidget.h
    ../3rdparty/kmessagewidget/kmessagewidget.cpp
    ../3rdparty/kirigami/wheelhandler.h
    ../3rdparty/kirigami/wheelhandler.cpp
   )

set_target_properties(nextcloudCore PROPERTIES AUTOUIC ON AUTOMOC ON)

find_package(Qt${QT_VERSION_MAJOR} ${REQUIRED_QT_VERSION} COMPONENTS LinguistTools)
if(Qt${QT_MAJOR_VERSION}LinguistTools_FOUND)
    qt_add_translation(client_I18N ${TRANSLATIONS})
endif()

IF( WIN32 )
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
      ${CMAKE_CURRENT_BINARY_DIR}/version.rc
      @ONLY)
    set(client_version ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
ENDIF()

set( final_src
    ${client_SRCS}
    ${client_UI_SRCS}
    ${client_I18N}
    ${3rdparty_SRC}
)

# Gestione Icone per Marchingegno Cloud
include(GenerateIconsUtils)

# IMPORTANTE: Usiamo il nome fisico dei file (Nextcloud) per evitare l'errore "No ICONS"
set(APPLICATION_ICON_NAME "Nextcloud")

set(STATE_ICONS_COLORS colored)
foreach(state_icons_color ${STATE_ICONS_COLORS})
    set(STATE_ICONS_PATH "${theme_dir}/${state_icons_color}/")
    file(GLOB_RECURSE STATE_ICONS_SVG "${STATE_ICONS_PATH}/state-*.svg")
    foreach(state_icon_svg ${STATE_ICONS_SVG})
        get_filename_component(status_icon_name_wle ${state_icon_svg} NAME_WLE)
        foreach(size IN ITEMS 16;32;64;128;256)
            generate_sized_png_from_svg(${state_icon_svg} ${size} OUTPUT_ICON_FULL_NAME_WLE "${status_icon_name_wle}-${size}")
        endforeach()
    endforeach()
endforeach()

if(WIN32)
  set(STARTMENU_ICON_SVG "${theme_dir}/colored/${APPLICATION_ICON_NAME}-w10startmenu.svg")
  generate_sized_png_from_svg(${STARTMENU_ICON_SVG} 70)
  generate_sized_png_from_svg(${STARTMENU_ICON_SVG} 150)
endif()

set(APP_ICON_SVG "${theme_dir}/colored/${APPLICATION_ICON_NAME}-icon.svg")

if(WIN32)
    foreach(size IN ITEMS 16;20;24;32;40;48;64;128;256;512;1024)
        generate_sized_png_from_svg(${APP_ICON_SVG} ${size})
    endforeach()
endif()

# Questa riga corregge l'errore dello screenshot recuperando i file corretti
file(GLOB OWNCLOUD_ICONS "${theme_dir}/colored/*-icon*")

ecm_add_app_icon(APP_ICON ICONS "${OWNCLOUD_ICONS}" OUTFILE_BASENAME "${APPLICATION_ICON_NAME}")

add_library(nextcloudCore STATIC ${final_src})
target_link_libraries(nextcloudCore PUBLIC Nextcloud::sync Qt::Widgets Qt::Svg Qt::Network Qt::Xml Qt::Qml Qt::Quick Qt::QuickControls2 Qt::QuickWidgets KF6::Archive)

add_subdirectory(socketapi)

if(WIN32)
    add_executable(nextcloud WIN32 main.cpp ${client_version} ${APP_ICON})
    set_target_properties(nextcloud PROPERTIES OUTPUT_NAME "${APPLICATION_EXECUTABLE}")
endif()

target_link_libraries(nextcloud PRIVATE nextcloudCore)

install(TARGETS nextcloud RUNTIME DESTINATION bin)
