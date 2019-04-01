# Cm

C minor(Cm) is a mini version of the C programming language using Flex and Bison compiler generating package.

## Data Types

|Type    |Size   |Description                                                                           |
|:------:|:-----:|--------------------------------------------------------------------------------------|
|`char`  |1 byte |An integer type ranging from 0 to 255                                                 |
|`int`   |4 bytes|An integer type ranging from -2,147,483,648 to 2,147,483,647                          |
|`double`|8 bytes|A floating-point type of 15 decimal places precision ranging from 2.3E-308 to 1.7E+308|
|`void`  |-      |A no-value data type used for functions return and arguments                          |

## Operators

### Mathematical

|Operator|Description                                                |
|:------:|-----------------------------------------------------------|
|`+`     |Adds two operands                                          |
|`-`     |Subtracts second operand from the first                    |
|`*`     |Multiplies both operands                                   |
|`/`     |Divides numerator by de-numerator                          |
|`%`     |Modulus Operator and remainder of after an integer division|

### Relational

|Operator|Description                                                                            |
|:------:|---------------------------------------------------------------------------------------|
|`==`    |Checks if the values of two operands are equal                                         |
|`!=`    |Checks if the values of two operands are not equal                                     |
|`>`     |Checks if the value of left operand is greater than the value of right operand         |
|`<`     |Checks if the value of left operand is less than the value of right operand            |
|`>=`    |Checks if the value of left operand is greater than or equal the value of right operand|
|`<=`    |Checks if the value of left operand is less than or equal the value of right operand   |

### Logical

|Operator|Description         |
|:------:|--------------------|
|`&&`    |Logical AND operator|
|`\|\|`  |Logical OR operator |
|`!`     |Logical NOT operator|

### Assignment

|Operator|Description                                                 |
|:------:|------------------------------------------------------------|
|`=`     |Assigns values from right side operands to left side operand|

## Operators Precedence

|Operator   |Associativity|
|:---------:|-------------|
|`!`        |Right to left|
|`* / %`    |Left to right|
|`+ -`      |Left to right|
|`< <= > >=`|Left to right|
|`== !=`    |Left to right|
|`&&`       |Left to right|
|`\|\|`     |Left to right|
|`=`        |Right to left|

## Assembly Quadruples

|Quadruple          |Description              |
|-------------------|-------------------------|
|`OR  $1, $2, $3`   |$3 = $1 \|\| $2          |
|`NOT $1, $2`       |$2 = !$1                 |
|`AND $1, $2, $3`   |$3 = $1 && $2            |
|`ADD $1, $2, $3`   |$3 = $1 + $2             |
|`SUB $1, $2, $3`   |$3 = $1 - $2             |
|`MUL $1, $2, $3`   |$3 = $1 * $2             |
|`DIV $1, $2, $3`   |$3 = $1 / $2             |
|`MOD $1, $2, $3`   |$3 = $1 % $2             |
|`MOV $1, $2`       |$2 = $1                  |
|`JE  $1, $2, label`|Jump to label if $1 == $2|
|`JG  $1, $2, label`|Jump to label if $1 > $2 |
|`JL  $1, $2, label`|Jump to label if $1 < $2 |
|`JNE $1, $2, label`|Jump to label if $1 != $2|
|`JGE $1, $2, label`|Jump to label if $1 >= $2|
|`JLE $1, $2, label`|Jump to label if $1 <= $2|