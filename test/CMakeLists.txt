SET(TestIncludeFiles test.hpp)

ADD_EXECUTABLE(testIf testIf.cpp ${TestIncludeFiles})
ADD_EXECUTABLE(testIfElse testIfElse.cpp ${TestIncludeFiles})
ADD_EXECUTABLE(testWhile testWhile.cpp ${TestIncludeFiles})

TARGET_LINK_LIBRARIES(testIf CmLib)
TARGET_LINK_LIBRARIES(testIfElse CmLib)
TARGET_LINK_LIBRARIES(testWhile CmLib)

ADD_TEST(NAME testIf COMMAND testIf COMMENT "Running testIf")
ADD_TEST(NAME testIfElse COMMAND testIfElse COMMENT "Running testIfElse")
ADD_TEST(NAME testWhile COMMAND testWhile COMMENT "Running testWhile")