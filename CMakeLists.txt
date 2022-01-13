cmake_minimum_required(VERSION 3.2)

PROJECT(dmgit2ssh)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ModuleInclude("dmformat" "thirdparty/dmformat")
LibImport("execute_module" "src/execute_module")
ExeImport("tools" "execute_module")

IF (WIN32)
    ADD_CUSTOM_COMMAND(
        TARGET dmgit2ssh
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/win/awk.exe
        $<TARGET_FILE_DIR:dmgit2ssh>

    INSTALL(TARGETS dmgit2ssh
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

)
ELSE(WIN32)
    INCLUDE(GNUInstallDirs)
    INSTALL(TARGETS dmgit2ssh
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION /${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION /${CMAKE_INSTALL_LIBDIR})
ENDIF(WIN32)

AddUninstallTarget()