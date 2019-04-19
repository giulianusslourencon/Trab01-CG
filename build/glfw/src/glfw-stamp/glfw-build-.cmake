

set(command "${make}")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-build-out.log"
  ERROR_FILE "/home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "glfw build command succeeded.  See also /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-build-*.log")
  message(STATUS "${msg}")
endif()
