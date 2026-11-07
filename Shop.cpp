#include "Shop.h"

miit::bakery::Shop::Shop(const std::string& name, const std::string& address)
    : name(requireText(name)), address(requireText(address)) {}
const std::string& miit::bakery::Shop::getName() const noexcept { return name; }
const std::string& miit::bakery::Shop::getAddress() const noexcept { return address; }
