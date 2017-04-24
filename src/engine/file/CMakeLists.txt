add_library(file SHARED file.cc)
export(TARGETS file FILE ${PROJECT_NAME}-exports.cmake)