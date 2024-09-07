cmake_minimum_required(VERSION 3.10)

project(calib_plugin LANGUAGES CXX VERSION 0.0.1)

set(LIBRARY_NAME ${PROJECT_NAME})

if(BUILD_EXAMPLES)
  add_subdirectory(demo-label)
endif(BUILD_EXAMPLES)


add_subdirectory(calib-plugin)


# #****************************************************************************/
# #*                               INSTALL                         *
# #****************************************************************************/
# include(CMakePackageConfigHelpers)
# include(GNUInstallDirs)

# install(DIRECTORY ${PROJECT_SOURCE_DIR}/calib-plugin/include/
#   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )

# install(TARGETS ${LIBRARY_NAME}
#   EXPORT ${PROJECT_NAME}Targets
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/calib_plugin
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/calib_plugin
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/calib_plugin
# )

# set(EXPORT_CONFIG_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake)
# set(EXPORT_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/cmake/${PROJECT_NAME})
# CONFIGURE_PACKAGE_CONFIG_FILE(
#     ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
#     ${EXPORT_CONFIG_FILE}
#     INSTALL_DESTINATION ${EXPORT_CONFIG_INSTALL_DIR}
#     NO_CHECK_REQUIRED_COMPONENTS_MACRO
# )
# install(EXPORT ${PROJECT_NAME}Targets
#     DESTINATION ${EXPORT_CONFIG_INSTALL_DIR}
# )
# install(FILES ${EXPORT_CONFIG_FILE}
#     DESTINATION ${EXPORT_CONFIG_INSTALL_DIR}
# )
