#pragma once
#include <iostream>
#include <functional>
struct three_circular_buffer{
    void* f1 = nullptr;
    void* f2 = nullptr;
    void add(void* t){ f2 = f1; f1 = t;}
};

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
    void add(TData* data, three_circular_buffer* buff);
    void add_node(_AvlTree* node);
    public:
    int get_count();
    int get_height();
    inline int get_balance_factor() const noexcept ;
    AvlTree(_AvlTree && t);
    AvlTree(TData && data);
    _AvlTree operator=(const AvlTree<int>& t);
    void Add(TData && data);
    void Iterate(std::function<void(_AvlTree*)> && f);
    _AvlTree* Left(){return _left;};
    _AvlTree* Right(){return _right;};
    TData Data(){return data;};
    ~AvlTree();
};
