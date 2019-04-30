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
|:------:|:------------------------------------------------------------------------------------:|
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