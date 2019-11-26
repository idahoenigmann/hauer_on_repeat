cmake_minimum_required(VERSION 3.9)
project(hello_java_jar LANGUAGES Java)
# begin_of_changes: change as appropriate!
set(TARGET_NAME "dbwriter") # name used for naming the jar-file and the executable
set(TARGET_MAIN_CLASS "DBWriter") # name used for naming the main class
# platform: windows32, windows64, linux32, linux64, or mac
set(PLATFORM "linux32")
# will be used to create the directory "bin"
set(JDK_HOME "/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt")
find_package(Java 1.8 REQUIRED COMPONENTS Development)
include(UseJava)
file(GLOB EXTERN_JARS "extern/*.jar")
# find packr jar: https://github.com/libgdx/packr
find_jar(PACKR_JAR packrjar "packr" PATHS "tools")
# end_of_changes
#############################################################
# don't touch the following part unless you're really brave #
#############################################################
file(GLOB SOURCES "src/*.java")
# build jar for the application
add_jar(${TARGET_NAME}
SOURCES ${SOURCES}
INCLUDE_JARS ${EXTERN_JARS}
ENTRY_POINT ${TARGET_MAIN_CLASS})
get_target_property(TARGET_JAR_FILE ${TARGET_NAME} JAR_FILE)
# build packed application to directory "bin"
add_custom_command(
OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/bin/${TARGET_NAME}"
COMMAND ${CMAKE_COMMAND} -E remove_directory bin
COMMAND java -jar ${PACKR_JAR} --platform ${PLATFORM} --jdk ${JDK_HOME}
--executable ${TARGET_NAME} --classpath ${TARGET_NAME}.jar
${EXTERN_JARS} --mainclass ${TARGET_MAIN_CLASS} --output bin
DEPENDS "${TARGET_JAR_FILE}"
)
add_custom_target(
${TARGET_NAME}_bin
ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/bin/${TARGET_NAME}"
)
#
