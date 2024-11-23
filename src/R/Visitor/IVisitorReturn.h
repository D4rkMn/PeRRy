#ifndef R_IVISITORRETURN_H
#define R_IVISITORRETURN_H

#include "R/Namespace.h"

class R::IVisitorReturn {
public:
    
    enum Type {
        TYPE_RETURN,
        VARIANT_RETURN,
        REDUCE_RETURN,
        COMPILETIME_RETURN
    };

    virtual ~IVisitorReturn() = default;
    virtual Type getType() const = 0;
};

#endif