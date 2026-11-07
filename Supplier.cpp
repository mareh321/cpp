#include "Supplier.h"

miit::bakery::Supplier::Supplier(const std::string& name, const std::string& address)
    : name(requireText(name)), address(requireText(address)) {}
const std::string& miit::bakery::Supplier::getName() const noexcept { return name; }
const std::string& miit::bakery::Supplier::getAddress() const noexcept { return address; }
