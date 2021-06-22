#pragma once
#include <iostream>
#include <functional>


template<typename TData,typename _Compare = std :: less<TData>>
class AvlTree{
    typedef AvlTree<TData,_Compare> _AvlTree;
    _AvlTree* _left = nullptr;
    _AvlTree* _right = nullptr;
    TData data;
    void LL_rotate();
    void RR_rotate();
    void LR_rotate();
    void RL_rotate();
    void balance();
    void add(TData* data);
    public:
    //get count of childrens elements
    int get_count();
    //get height of the current node
    int get_height();
    //get balance factor
    inline int get_balance_factor() const noexcept ;
    AvlTree(_AvlTree && t);
    AvlTree(TData && data);
    void Add(TData && data);
    //recursively pass every children of current node to f function 
    void Iterate(std::function<void(_AvlTree*)> && f);
    //get left child
    _AvlTree* Left(){return _left;};
    //get right child
    _AvlTree* Right(){return _right;};
    //get current data
    TData Data(){return data;};
    ~AvlTree();
};
