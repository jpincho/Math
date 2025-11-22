project (Math)

function (generate_vec_code COMPONENT_COUNT TYPENAME VAR_TYPE ZERO_VALUE )
	file(READ vec_template.h TEMPLATE_TEXT)
	string(REPLACE "TYPENAME" ${TYPENAME} TEXT "${TEMPLATE_TEXT}")
	string(REPLACE "COMPONENT_COUNT" ${COMPONENT_COUNT} TEXT "${TEXT}")
	string(REPLACE "TYPE" ${VAR_TYPE} TEXT "${TEXT}")
	string(REPLACE "ZERO" ${ZERO_VALUE} TEXT "${TEXT}")
	file(GENERATE OUTPUT ${CMAKE_CURRENT_LIST_DIR}/${TYPENAME}_funcs.h CONTENT "${TEXT}")
endfunction()


set(GENERATE_MATH_CODE FALSE)
if (GENERATE_MATH_CODE)
generate_vec_code(2 "vec2" "float" "0.0f")
generate_vec_code(2 "ivec2" "int" "0")
generate_vec_code(2 "uvec2" "unsigned" "0")

generate_vec_code(3 "vec3" "float" "0.0f")
generate_vec_code(3 "ivec3" "int" "0")
generate_vec_code(3 "uvec3" "unsigned" "0")

generate_vec_code(4 "vec4" "float" "0.0f")
generate_vec_code(4 "ivec4" "int" "0")
generate_vec_code(4 "uvec4" "unsigned" "0")
endif()

file ( GLOB SOURCES "*.h" "*.c" )
add_library ( Math ${SOURCES} )