set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "C:/Users/testy/Desktop/UNI-Stuff/Visual computing/OpenGL_Praktikum_Linux_MacOS_fix_cmake_3.5/OpenGL_Praktikum/libs/glm-master")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
