SET(TestIncludeFiles test.hpp)

ADD_EXECUTABLE(testIf testIf.cpp ${TestIncludeFiles})

TARGET_LINK_LIBRARIES(testIf CmLib)

ADD_TEST(NAME testIf COMMAND testIf COMMENT "Running testIf")