#ifndef CONTEXT_H
#define CONTEXT_H

class Context {
    private:
        int lablesIndex;
    
    public:
        Context(): lablesIndex(0) { }
        int createLabel() { return lablesIndex++; }
};

#endif /* CONTEXT_H */