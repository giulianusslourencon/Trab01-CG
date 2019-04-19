

set(command "/usr/bin/cmake;-DCMAKE_INSTALL_PREFIX=/home/psy/Documentos/GitProjects/icmc-cg/build/glfw;-DCMAKE_BUILD_TYPE=Release;-DGLFW_BUILD_EXAMPLES=OFF;-DGLFW_BUILD_TESTS=OFF;-DGLFW_BUILD_DOCS=OFF;-C/home/psy/Documentos/GitProjects/icmc-cg/build/glfw/tmp/glfw-cache-.cmake;-GUnix Makefiles;/home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-configure-out.log"
  ERROR_FILE "/home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "glfw configure command succeeded.  See also /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-configure-*.log")
  message(STATUS "${msg}")
endif()
