# Cm

C minor(Cm) is a mini version of the C programming language using Flex and Bison compiler generating package.

## AST

```markdown
                                            Node
                ┌────────────────────────────┼─────────────────────────────┐
            NStatement                    NBlock                      NExpression
    ┌────────────────┼─────┐                           ┌─────────┬────────┼─────────┬──────────┐
NExpressionStatement │ NVarDeclStatement            NInteger   NDouble   NVariable  │    NAssignment
          NControlFlowStatement                                             NBinaryOperation
        ┌────────────┴────────────┐
NWhileStatement           NIfStatement
```

## Data Types

|Type    |Description                                                                           |
|:------:|--------------------------------------------------------------------------------------|
|`int`   |An integer type ranging from -2,147,483,648 to 2,147,483,647                          |
|`double`|A floating-point type of 15 decimal places precision ranging from 2.3E-308 to 1.7E+308|

## Operators

### Mathematical

|Operator|Description                                                |
|:------:|-----------------------------------------------------------|
|`+`     |Adds two operands                                          |
|`-`     |Subtracts second operand from the first                    |
|`*`     |Multiplies both operands                                   |
|`/`     |Divides numerator by de-numerator                          |

### Relational

|Operator|Description                                                                            |
|:------:|---------------------------------------------------------------------------------------|
|`==`    |Checks if the values of two operands are equal                                         |
|`!=`    |Checks if the values of two operands are not equal                                     |
|`>`     |Checks if the value of left operand is greater than the value of right operand         |
|`<`     |Checks if the value of left operand is less than the value of right operand            |
|`>=`    |Checks if the value of left operand is greater than or equal the value of right operand|
|`<=`    |Checks if the value of left operand is less than or equal the value of right operand   |

### Assignment

|Operator|Description                                                 |
|:------:|------------------------------------------------------------|
|`=`     |Assigns values from right side operands to left side operand|

## Operators Precedence

|Operator   |Associativity|
|:---------:|-------------|
|`* /`      |Left to right|
|`+ -`      |Left to right|
|`< <= > >=`|Left to right|
|`== !=`    |Left to right|
|`=`        |Right to left|

## Assembly Quadruples

|Quadruple          |Description                                      |
|-------------------|-------------------------------------------------|
|`LOADi $1`         |Reserve memory for integer variable $1           |
|`LOADd $1`         |Reserve memory for double variable $1            |
|`ADD $1, $2, $3`   |$3 = $1 + $2                                     |
|`SUB $1, $2, $3`   |$3 = $1 - $2                                     |
|`MUL $1, $2, $3`   |$3 = $1 * $2                                     |
|`DIV $1, $2, $3`   |$3 = $1 / $2                                     |
|`MOV $1, $2`       |$2 = $1                                          |
|`CLT $1, $2`       |Evaluates to One if $1 < $2 else zero            |
|`CGT $1, $2`       |Evaluates to One if $1 > $2 else zero            |
|`CGE $1, $2`       |Evaluates to One if $1 >= $2 else zero           |
|`CLE $1, $2`       |Evaluates to One if $1 <= $2 else zero           |
|`CEQ $1, $2`       |Evaluates to One if $1 == $2 else zero           |
|`CNE $1, $2`       |Evaluates to One if $1 != $2 else zero           |
|`JZ  label`        |Jump to label if last quadruple evaluated to Zero|
|`JNZ label`        |Jump to label if last quadruple evaluated to One |
|`JMP label`        |Unconditional jump to label                      |
