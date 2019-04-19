

set(command "/usr/bin/cmake;-GUnix Makefiles;/home/psy/Documentos/GitProjects/icmc-cg/build/glm/src/glm")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/psy/Documentos/GitProjects/icmc-cg/build/glm/src/glm-stamp/glm-configure-out.log"
  ERROR_FILE "/home/psy/Documentos/GitProjects/icmc-cg/build/glm/src/glm-stamp/glm-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/psy/Documentos/GitProjects/icmc-cg/build/glm/src/glm-stamp/glm-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "glm configure command succeeded.  See also /home/psy/Documentos/GitProjects/icmc-cg/build/glm/src/glm-stamp/glm-configure-*.log")
  message(STATUS "${msg}")
endif()
