# SPDX-FileCopyrightText: 2026 marchingegno
# SPDX-License-Identifier: GPL-2.0-or-later

if(NEXTCLOUD_DEV)
    set( APPLICATION_NAME       "marchingegno cloud Dev" )
    set( APPLICATION_SHORTNAME  "marchingegnoclouddev" )
    set( APPLICATION_EXECUTABLE "marchingegnoclouddev" )
    set( APPLICATION_ICON_NAME  "marchingegnocloud" )
else()
    set( APPLICATION_NAME       "marchingegno cloud" )
    set( APPLICATION_SHORTNAME  "marchingegnocloud" )
    set( APPLICATION_EXECUTABLE "marchingegnocloud" )
    set( APPLICATION_ICON_NAME  "Nextcloud" )
endif()

set( APPLICATION_CONFIG_NAME "${APPLICATION_EXECUTABLE}" )
set( APPLICATION_DOMAIN     "marchingegno.info" )
set( APPLICATION_VENDOR     "marchingegno" )
set( APPLICATION_UPDATE_URL "" CACHE STRING "URL for updater" )
set( APPLICATION_HELP_URL   "https://marchingegno.info/help" CACHE STRING "URL for the help menu" )

set( APPLICATION_ICON_SET   "SVG" )
set( APPLICATION_SERVER_URL "https://cloud.marchingegno.info" CACHE STRING "URL for the server to use." )
set( APPLICATION_SERVER_URL_ENFORCE ON ) 
set( APPLICATION_REV_DOMAIN "info.marchingegno.desktopclient" )
set( APPLICATION_VIRTUALFILE_SUFFIX "marchingegno" CACHE STRING "Virtual file suffix")
set( APPLICATION_OCSP_STAPLING_ENABLED OFF )
set( APPLICATION_FORBID_BAD_SSL OFF )

set( LINUX_PACKAGE_SHORTNAME "marchingegnocloud" )
set( LINUX_APPLICATION_ID "${APPLICATION_REV_DOMAIN}.${LINUX_PACKAGE_SHORTNAME}")

set( THEME_CLASS            "NextcloudTheme" )
set( WIN_SETUP_BITMAP_PATH  "${CMAKE_SOURCE_DIR}/admin/win/nsi" )

## Opzioni Branding
set(MARCHINGEGNO_COLOR "#2ecc71" CACHE STRING "Colore principale Marchingegno")
set( APPLICATION_WIZARD_HEADER_BACKGROUND_COLOR ${MARCHINGEGNO_COLOR} CACHE STRING "Colore header")
set( APPLICATION_WIZARD_HEADER_TITLE_COLOR "#ffffff" CACHE STRING "Colore testo header")
option( APPLICATION_WIZARD_USE_CUSTOM_LOGO "" ON )

#
## Windows GUIDs - GENERATI NUOVI PER MARCHINGEGNO CLOUD
#
if(WIN32)
    # Context Menu
    set( WIN_SHELLEXT_CONTEXT_MENU_GUID      "{A1B2C3D4-E5F6-4A7B-8C9D-0E1F2A3B4C5D}" )

    # Overlays
    set( WIN_SHELLEXT_OVERLAY_GUID_ERROR     "{B1C2D3E4-F5A6-4B7C-8D9E-0F1A2B3C4D5E}" )
    set( WIN_SHELLEXT_OVERLAY_GUID_OK        "{C1D2E3F4-A5B6-4C7D-8E9F-0A1B2C3D4E5F}" )
    set( WIN_SHELLEXT_OVERLAY_GUID_OK_SHARED "{D1E2F3A4-B5C6-4D7E-8F9A-0B1C2D3E4F5A}" )
    set( WIN_SHELLEXT_OVERLAY_GUID_SYNC      "{E1F2A3B4-C5D6-4E7F-8A9B-0C1D2E3F4A5B}" )
    set( WIN_SHELLEXT_OVERLAY_GUID_WARNING   "{F1A2B3C4-D5E6-4F7A-8B9C-0D1E2F3A4B5C}" )

    # MSI Upgrade Code
    set( WIN_MSI_UPGRADE_CODE                "A7B8C9D0-E1F2-4321-B5C6-D7E8F9A0B1C2" )

    option( BUILD_WIN_MSI "Build MSI scripts" ON )
endif()
