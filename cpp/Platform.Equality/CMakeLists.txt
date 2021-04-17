add_library(Platform.Equality.Library INTERFACE)

target_include_directories(Platform.Equality.Library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(Platform.Equality.Library INTERFACE cxx_std_20)