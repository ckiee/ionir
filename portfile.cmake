vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO ionlang/ionir
    REF 1600b755ff8882c12cef12736f4454f0fd8ffa48
    SHA512 1
    HEAD_REF dev
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

file(INSTALL ${SOURCE_PATH}/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/libionir RENAME copyright)
