option(AUTO_FIND_VULKAN "AUTO_FIND_VULKAN" ON)

if(AUTO_FIND_VULKAN)
	message(STATUS "Auto find Vulkan......")
	find_package(Vulkan REQUIRED)

	if(Vulkan_FOUND)
		STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
		message(STATUS "Vulkan path: ${VULKAN_PATH}")
	else()
		message(STATUS "Failed to find Vulkan")
	endif()
else()
	message(STATUS "Manual find Vulkan......")
	set(VULKAN_SDK "D:/Program/3rdlibs/VulkanSDK")
	set(VULKAN_VERSION "1.3.268.0")
	set(VULKAN_PATH "${VULKAN_SDK}/${VULKAN_VERSION}")

	if(EXISTS "${VULKAN_PATH}")
		message(STATUS "Vulkan path: ${VULKAN_PATH}")
	else()
		message(STATUS "Failed to find Vulkan")
	endif()
endif()