add_library(Platform.Equality.Library INTERFACE)

target_include_directories(Platform.Equality.Library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Platform.Equality.Library PROPERTIES CXX_STANDARD 20)
