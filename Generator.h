#pragma once

namespace miit::algebra
{
    class Generator
    {
    public:
        virtual ~Generator() = default;
        virtual int generate() const = 0;
    };
}
