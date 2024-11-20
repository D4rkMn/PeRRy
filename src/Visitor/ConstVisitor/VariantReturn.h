#ifndef VARIANTRETURN_H
#define VARIANTRETURN_H

#include "Visitor/IVisitorReturn.h"
#include <variant>

class VariantReturn : public IVisitorReturn {
public:
    std::variant<int32_t, int64_t, uint32_t, uint64_t, bool> value;
    VariantReturn(int32_t v) { value = int32_t(v); }
    VariantReturn(int64_t v) { value = int64_t(v); }
    VariantReturn(uint32_t v) { value = uint32_t(v); }
    VariantReturn(uint64_t v) { value = uint64_t(v); }
    VariantReturn(bool v) { value = bool(v); }
    ~VariantReturn() = default;
    Type getType() const override { return VARIANT_RETURN; }
};

#endif