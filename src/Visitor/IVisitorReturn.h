#ifndef IVISITORRETURN_H
#define IVISITORRETURN_H

class IVisitorReturn {
public:
    
    enum Type {
        TYPE_RETURN,
        VARIANT_RETURN,
        REDUCE_RETURN
    };

    virtual ~IVisitorReturn() = default;
    virtual Type getType() const = 0;
};

#endif