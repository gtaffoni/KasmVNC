# This file is included from the top-level CMakeLists.txt.  We just store it
# here to avoid cluttering up that file.


#
# Windows installer (Inno Setup)
#

if(WIN32)

if(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(INST_NAME ${CMAKE_PROJECT_NAME}64-${VERSION})
  set(INST_DEFS -DWIN64)
else()
  set(INST_NAME ${CMAKE_PROJECT_NAME}-${VERSION})
endif()

if(BUILD_WINVNC)
  set(INST_DEFS ${INST_DEFS} -DBUILD_WINVNC)
  set(INST_DEPS ${INST_DEPS} winvnc4 wm_hooks vncconfig)
endif()

configure_file(release/kasmvnc.iss.in release/kasmvnc.iss)

add_custom_target(installer
  iscc -o. ${INST_DEFS} -F${INST_NAME} release/kasmvnc.iss
  DEPENDS ${INST_DEPS}
  SOURCES release/kasmvnc.iss)

endif() # WIN32


#
# Mac DMG
#

if(APPLE)

set(DEFAULT_OSX_X86_BUILD ${CMAKE_SOURCE_DIR}/osxx86)
set(OSX_X86_BUILD ${DEFAULT_OSX_X86_BUILD} CACHE PATH
  "Directory containing 32-bit OS X build to include in universal binaries (default: ${DEFAULT_OSX_X86_BUILD})")

configure_file(release/makemacapp.in release/makemacapp)
configure_file(release/Info.plist.in release/Info.plist)

add_custom_target(dmg sh release/makemacapp
  SOURCES release/makemacapp)

add_custom_target(udmg sh release/makemacapp universal
  SOURCES release/makemacapp)

endif() # APPLE


#
# Binary tarball
#

if(UNIX)

configure_file(release/maketarball.in release/maketarball)

set(TARBALL_DEPENDS vncpasswd vncconfig)

add_custom_target(tarball bash release/maketarball
  DEPENDS ${TARBALL_DEPENDS}
  SOURCES release/maketarball)

add_custom_target(servertarball bash release/maketarball server
  DEPENDS ${TARBALL_DEPENDS}
  SOURCES release/maketarball)

endif() #UNIX

#
# Common
#

install(FILES ${CMAKE_SOURCE_DIR}/LICENCE.TXT DESTINATION ${DOC_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/README.md DESTINATION ${DOC_DIR})
