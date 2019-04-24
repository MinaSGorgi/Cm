CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(Cm)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/build/parser.c)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BisonOutput}
      COMMAND ${BISON_EXECUTABLE}
              --defines=${CMAKE_SOURCE_DIR}/build/parser.h
              --output=${BisonOutput}
              ${CMAKE_SOURCE_DIR}/src/parser.y
      COMMENT "Generating parser.cpp"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/build/scanner.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
              --outfile=${FlexOutput}
              ${CMAKE_SOURCE_DIR}/src/scanner.l
      COMMENT "Generating scanner.cpp"
    )
ENDIF()

SET(IncludeDir ${CMAKE_SOURCE_DIR}/include)
SET(SrcDir ${CMAKE_SOURCE_DIR}/src)

SET(IncludeFiles ${IncludeDir}/calc3.h)
SET(SrcFiles ${BisonOutput} ${FlexOutput} ${SrcDir}/compiler.c)

ADD_EXECUTABLE(Cm ${IncludeFiles} ${SrcFiles})