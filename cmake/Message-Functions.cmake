function(reportvar var)
  message(STATUS "${ARGVN}${var}=${${var}}")
endfunction()

function(reportallvars)
	get_cmake_property(_variableNames VARIABLES)
	list (SORT _variableNames)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endfunction()