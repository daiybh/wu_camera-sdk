cmake_minimum_required (VERSION 3.16)

set(cameraSDK_VERSION 1.0.0)
project (CameraSDK
		VERSION ${cameraSDK_VERSION}
		LANGUAGES CXX)

		
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)


add_library(CameraSDK INTERFACE)



target_include_directories(CameraSDK
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)



#target_link_directories(combinedLib INTERFACE lib/)

#add_executable(test test.cpp)
#target_link_libraries(test combinedLib)

configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/CameraSDK-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/beicode
	NO_SET_AND_CHECK_MACRO)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/CameraSDK-config-version.cmake
	VERSION ${cameraSDK_VERSION}
	COMPATIBILITY SameMajorVersion)
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/CameraSDK-config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/CameraSDK-config-version.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/CameraSDK)

install(TARGETS CameraSDK EXPORT CameraSDK-targets)
install(DIRECTORY inc/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY lib/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(EXPORT CameraSDK-targets
	NAMESPACE CameraSDK::
	DESTINATION ${CMAKE_INSTALL_DATADIR}/CameraSDK)