project(DeapLearning)
file(GLOB SRC_FILES *.c *.h)
add_executable(DeepLearning ${SRC_FILES})
target_link_libraries(DeepLearning -lm)
