#ifndef R_VARIANTRETURN_H
#define R_VARIANTRETURN_H

#include "R/Visitor/IVisitorReturn.h"
#include <variant>

namespace R {
    using ConstVariant = std::variant<int32_t, int64_t, uint32_t, uint64_t, bool>;
}

class R::VariantReturn : public IVisitorReturn {
public:
    ConstVariant value;
    VariantReturn(int32_t v) { value = int32_t(v); }
    VariantReturn(int64_t v) { value = int64_t(v); }
    VariantReturn(uint32_t v) { value = uint32_t(v); }
    VariantReturn(uint64_t v) { value = uint64_t(v); }
    VariantReturn(bool v) { value = bool(v); }
    VariantReturn(const ConstVariant& v) { value = v; }
    ~VariantReturn() = default;
    Type getType() const override { return VARIANT_RETURN; }
};

#endif