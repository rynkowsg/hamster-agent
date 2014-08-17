set(INITD_DIR /etc/init.d)

configure_file( "script-initd.sh.in"
				"script-initd.sh"
)

install(FILES ${CMAKE_BINARY_DIR}/resources/script-initd.sh
		DESTINATION ${INITD_DIR}
		RENAME ${PROJECT_NAME}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
             		GROUP_READ GROUP_EXECUTE
             		WORLD_READ WORLD_EXECUTE
)