#ifndef ASM_H
#define ASM_h

#include <iostream>
#include <string>
#include <vector>


typedef std::vector<std::string> Operands;

enum InstrTwo {
    NOT, MOV
};

enum InstrThree {
    OR, AND, ADD, SUB, MUL, DIV, MOD,
    JE, JG, JL, JNE, JGE, JLE
};

class Quadruple {
public:
    std::string instrcution;
    Operands operands;
    Quadruple(InstrTwo instrcution, std::string first, std::string second) :
        instrcution(enumToString(instrcution)), operands({first, second}) {}
    Quadruple(InstrThree instrcution, std::string first, std::string second, std::string third) :
        instrcution(enumToString(instrcution)), operands({first, second, third}) {}
    void print() {
        std::cout<<instrcution;
        for (std::string operand : operands) {
            std::cout<<" "<<operand;
        }
        std::cout<<std::endl;
    }
private:
    static std::string enumToString(InstrTwo enumInstr) {
        switch (enumInstr)
        {
            case NOT:
                return "NOT";
            case MOV:
                return "MOV";
        }
    }
    static std::string enumToString(InstrThree enumInstr) {
        switch (enumInstr)
        {
            case OR:
                return "OR";
            case AND:
                return "AND";
            case ADD:
                return "ADD";
            case SUB:
                return "SUB";
            case MUL:
                return "MUL";
            case DIV:
                return "DIV";
            case MOD:
                return "MOD";
            case JE:
                return "JE";
            case JG:
                return "JG";
            case JL:
                return "JL";
            case JNE:
                return "JNE";
            case JGE:
                return "JGE";
            case JLE:
                return "JLE";
        }
    }
};

#endif /* ASM_H */