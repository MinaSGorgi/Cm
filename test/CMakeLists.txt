SET(TestIncludeFiles test.hpp)

ADD_EXECUTABLE(CmTest test.cpp ${TestIncludeFiles})
ADD_EXECUTABLE(testIf testIf.cpp ${TestIncludeFiles})

TARGET_LINK_LIBRARIES(CmTest CmLib)
TARGET_LINK_LIBRARIES(testIf CmLib)

ADD_TEST(NAME Test1 COMMAND CmTest COMMENT "Running test")
ADD_TEST(NAME testIf COMMAND testIf COMMENT "Running testIf")