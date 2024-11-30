function(SetupGLFW TARGET)
	target_compile_definitions(${TARGET} PUBLIC GLFW_INCLUDE_NONE)
	if(WIN32)
		target_compile_definitions(${TARGET} PUBLIC GLFW_EXPOSE_NATIVE_WIN32)
	endif()
endfunction()