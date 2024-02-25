#include <Node.hpp>
#include "VariantNode.hpp"
#include <iostream>
#include <vector>

class TestNode1 : public Node<TestNode1>{};

class TestNode2 : public Node<TestNode2>{};

class TestNode3 : public Node<TestNode3>{};

class TestVisitor
{
public:
    void visit(std::shared_ptr<INode> node)
    {
        std::cout << "TestVisitor::visit unknown type" << std::endl;
    }

    void visit(std::shared_ptr<TestNode1> node)
    {
        std::cout << "TestVisitor::visit TestNode1" << std::endl;
    }

    void visit(std::shared_ptr<TestNode2> node)
    {
        std::cout << "TestVisitor::visit TestNode2" << std::endl;
    }   
};

/// VariantNode
struct TestVariantNode1 : public VariantNode<TestVariantNode1>{};

struct TestVariantNode2 : public VariantNode<TestVariantNode2>{};

struct TestVariantNode3 : public VariantNode<TestVariantNode3>{};

using VariantNodeVariant = std::variant<std::shared_ptr<IVariantNode>, std::shared_ptr<TestVariantNode2>, std::shared_ptr<TestVariantNode3>>;

struct VariantTestHandler{
    void handle(VariantNodeVariant vNode){
        std::visit(*this, vNode);
    }
    
    void operator() (std::shared_ptr<IVariantNode> node){
        std::cout <<  "IVariant NODE." << std::endl;
    }
    
    void operator() (std::shared_ptr<TestVariantNode2> node){
        std::cout <<  "TestVariantNode2." << std::endl;
    }

    void operator() (std::shared_ptr<TestVariantNode3> node){
        std::cout <<  "TestVariantNode3." << std::endl;
    }
};

int main()
{
    auto node1 = TestNode1::create();
    auto node2 = TestNode2::create();
    auto node3 = TestNode3::create();
    TestVisitor visitor;

    std::vector<std::shared_ptr<INode>> nodes;
    nodes.push_back(node1);
    nodes.push_back(node2);
    nodes.push_back(node3);

    //impossible to use this kind of visitor
    std::cout << "\r\nTestVisitor on vector of INode" << std::endl;
    for(auto n: nodes)
    {   
        n->dispatch(visitor);
    }  

    std::cout << "\r\nTestVisitor on concrete INode" << std::endl;
    node1->dispatch(visitor);
    node2->dispatch(visitor);
    node3->dispatch(visitor);

    
    //VariantNode
    
    std::vector<VariantNodeVariant> variantNodes;
    variantNodes.push_back(IVariantNode::create<TestVariantNode1>());
    variantNodes.push_back(IVariantNode::create<TestVariantNode2>());
    variantNodes.push_back(IVariantNode::create<TestVariantNode3>());

    VariantTestHandler variantHandler;
    std::cout << "\r\nDispatch on VariantNode Vector" << std::endl;
    for(auto& n: variantNodes)
    {
        variantHandler.handle(n);
    }
}