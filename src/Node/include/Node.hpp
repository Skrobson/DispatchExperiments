#pragma once

#include <memory>

// class Visitor
// {
// public:

//     virtual void visit(std::shared_ptr<INode> node) = 0;
// };

class INode : public std::enable_shared_from_this<INode>
{
public:
    virtual ~INode() = default;

    template <typename Visitor>
    void dispatch(Visitor &visitor)
    {
        visitor.visit(this->shared_from_this());
    }

protected:
    INode() = default;
};

template <typename Derived>
class Node : public INode
{
public:
    static std::shared_ptr<Derived> create()
    {
        return std::make_shared<Derived>();
    }

    template <typename Visitor>
    void dispatch(Visitor &visitor)
    {
        auto ptr = std::static_pointer_cast<Derived>(this->shared_from_this());
        visitor.visit(ptr);

        // visitor.visit(this->shared_from_this());
    }

protected:
    Node() = default;
};
