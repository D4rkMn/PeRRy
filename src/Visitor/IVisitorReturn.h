#ifndef IVISITORRETURN_H
#define IVISITORRETURN_H

class IVisitorReturn {
public:
    
    enum Type {
        
    };

    virtual ~IVisitorReturn() = default;
    virtual Type getType() const = 0;
};

#endif