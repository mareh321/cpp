#include "RegularSolid.h"

namespace geometry {
    std::ostream& operator<<(std::ostream& os, const RegularSolid& solid) {
        os << solid.ToString();
        return os;
    }

    std::istream& operator>>(std::istream& is, RegularSolid& solid) {
        solid.read(is);
        return is;
    }

    std::string RegularSolid::ToString(const RegularSolid& solid) {
        return solid.ToString();
    }

    RegularSolid* RegularSolid::readFromStream(std::istream& is) {
        return nullptr;
    }
}
