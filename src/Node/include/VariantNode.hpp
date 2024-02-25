#pragma once

#include <variant>

class IVariantNode : public std::enable_shared_from_this<IVariantNode>
{
public:
    virtual ~IVariantNode() = default;

    template <typename Derived> //TODO: check if Derived is raly derived from IVariantNode
    static std::shared_ptr<Derived> create(){
        return Derived::create();
    };

protected:
    IVariantNode() = default;
};

template <typename Derived>
class VariantNode : public IVariantNode
{
public:
    static std::shared_ptr<Derived> create()
    {
        return std::make_shared<Derived>();
    }

protected:
    VariantNode() = default;
};
