# SPDX-FileCopyrightText: 2026 marchingegno
# SPDX-License-Identifier: GPL-2.0-or-later

# ------------------------------------
# Version information - MARCHINGEGNO CLOUD
# ------------------------------------
set(MIRALL_VERSION_MAJOR 33)
set(MIRALL_VERSION_MINOR 0)
set(MIRALL_VERSION_PATCH 3)
set(MIRALL_VERSION_YEAR  2026)
set(MIRALL_SOVERSION     0)
set(MIRALL_PREVERSION_HUMAN "33.0.3") 
set(NCEXT_BUILD_NUM 1)
set(NCEXT_VERSION 1,0,0,${NCEXT_BUILD_NUM})

# ------------------------------------
# Minimum supported server versions
# ------------------------------------
set(NEXTCLOUD_SERVER_VERSION_MIN_SUPPORTED_MAJOR 20)
set(NEXTCLOUD_SERVER_VERSION_MIN_SUPPORTED_MINOR 0)
set(NEXTCLOUD_SERVER_VERSION_MIN_SUPPORTED_PATCH 0)

set(NEXTCLOUD_SERVER_VERSION_SECURE_FILEDROP_MIN_SUPPORTED_MAJOR 26)
set(NEXTCLOUD_SERVER_VERSION_SECURE_FILEDROP_MIN_SUPPORTED_MINOR 0)
set(NEXTCLOUD_SERVER_VERSION_SECURE_FILEDROP_MIN_SUPPORTED_PATCH 0)

set(NEXTCLOUD_SERVER_VERSION_MOUNT_ROOT_PROPERTY_SUPPORTED_MAJOR 28)
set(NEXTCLOUD_SERVER_VERSION_MOUNT_ROOT_PROPERTY_SUPPORTED_MINOR 0)
set(NEXTCLOUD_SERVER_VERSION_MOUNT_ROOT_PROPERTY_SUPPORTED_PATCH 3)

# ------------------------------------
# Define default suffixes - REMOVED DAILY FOR PRODUCTION
# ------------------------------------
if(NOT DEFINED MIRALL_VERSION_SUFFIX)
    set(MIRALL_VERSION_SUFFIX "") 
endif()

if(NOT DEFINED MIRALL_VERSION_BUILD)
    set(MIRALL_VERSION_BUILD "1")
endif()

# ------------------------------------
# Composite version definitions
# ------------------------------------
set(MIRALL_VERSION "${MIRALL_VERSION_MAJOR}.${MIRALL_VERSION_MINOR}.${MIRALL_VERSION_PATCH}")
set(MIRALL_VERSION_FULL "${MIRALL_VERSION}.${MIRALL_VERSION_BUILD}")
set(MIRALL_VERSION_STRING "${MIRALL_VERSION}")
set(MIRALL_HUMAN_VERSION_STRING "${MIRALL_VERSION}")

if(MIRALL_VERSION_BUILD)
    set(MIRALL_VERSION_STRING "${MIRALL_VERSION_STRING} (build ${MIRALL_VERSION_BUILD})")
endif()

# ------------------------------------
# Misc
# ------------------------------------
set(QT_MAJOR_VERSION 6)