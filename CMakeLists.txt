CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
SET(CMAKE_CXX_STANDARD 11)
PROJECT(Cm)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/build/parser.cpp)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BisonOutput}
      COMMAND ${BISON_EXECUTABLE}
              --defines=${CMAKE_SOURCE_DIR}/build/parser.hpp
              --output=${BisonOutput}
              ${CMAKE_SOURCE_DIR}/src/parser.y
      COMMENT "Generating parser.cpp"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/build/scanner.cpp)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
              --outfile=${FlexOutput}
              ${CMAKE_SOURCE_DIR}/src/scanner.l
      COMMENT "Generating scanner.cpp"
    )
ENDIF()

ADD_EXECUTABLE(Cm ${BisonOutput} ${FlexOutput})