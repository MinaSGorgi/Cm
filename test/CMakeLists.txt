SET(TestIncludeFiles test.hpp)

ADD_EXECUTABLE(testIf testIf.cpp ${TestIncludeFiles})
ADD_EXECUTABLE(testIfElse testIfElse.cpp ${TestIncludeFiles})

TARGET_LINK_LIBRARIES(testIf CmLib)
TARGET_LINK_LIBRARIES(testIfElse CmLib)

ADD_TEST(NAME testIf COMMAND testIf COMMENT "Running testIf")
ADD_TEST(NAME testIfElse COMMAND testIfElse COMMENT "Running testIfElse")