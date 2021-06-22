#pragma once
#include "_avl_tree.hpp"

template<typename TData,typename _Compare>
AvlTree<TData,_Compare>::AvlTree(_AvlTree && t){
    this->_left = t._left;
    this->_right = t._right;
    this->data = t.data;
}
template<typename TData,typename _Compare>
AvlTree<TData,_Compare> AvlTree<TData,_Compare>::operator=(const AvlTree<int>& t){
    this->_left = t._left;
    this->_right = t._right;
    this->data = t.data;
}
template<typename TData,typename _Compare>
AvlTree<TData,_Compare>::AvlTree(TData && data)
{
    this->data = data;
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::add_node(_AvlTree* node){
    if(node->data<this->data){
        if(this->_left==nullptr)
        {
            this->_left = node;
            return;
        }
        this->_left->add_node(node);
    }
    else{
        if(this->_right==nullptr)
        { 
            this->_right = node;
            return;
        }
        this->_right->add_node(node);
    }
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::add(TData* data, three_circular_buffer* buf) 
{   
    if(*data<this->data)
        if(_left!=nullptr)
            _left->add(data,buf);
        else
            _left = new AvlTree{std::move(*data)};
    else
        if(_right!=nullptr)
            _right->add(data,buf);
        else
            _right = new AvlTree{std::move(*data)};
    this->balance();
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::Add(TData && data) 
{
    three_circular_buffer buf{};
    this->add(&data,&buf);
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::Iterate(std::function<void(_AvlTree*)> && f) 
{
    f(this);
    if(_left!=nullptr)
        _left->Iterate(std::move(f));
    if(_right!=nullptr)
        _right->Iterate(std::move(f));
}

template<typename TData,typename _Compare>
AvlTree<TData,_Compare>::~AvlTree() 
{   
    if(this == nullptr) return;

    if(this->_left!=nullptr)
    _left->~AvlTree();
    
    if(this->_right!=nullptr)
    _right->~AvlTree();
    if(_left!=nullptr)
        delete _left;
    if(_right!=nullptr)
        delete _right;    
    _left = nullptr;
    _right = nullptr;
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::LL_rotate() 
{
    _AvlTree* A = this;
    _AvlTree* B = this->_left;
    _AvlTree* C = this->_left->_left;
    _AvlTree* Ar = A->_right;
    _AvlTree* Br = B->_right;

    B->_right = new _AvlTree(std::forward<TData>(A->data));
    B->_right->_right = Ar;
    B->_right->_left = Br;
    //std::swap(*this,*B);
    this->_left = B->_left;
    this->_right = B->_right;
    this->data = B->data;
    B->_left = nullptr;
    B->_right = nullptr;
    B->data = TData{};
    delete B;
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::LR_rotate() 
{
    _AvlTree* A = this;
    _AvlTree* B = this->_left;
    _AvlTree* C = B->_right;
    _AvlTree* Cl = C->_left;
    _AvlTree* Cr = C->_right;
    _AvlTree* Ar = A->_right;
    B->_right = Cl;
    A->_right = new _AvlTree{std::forward<TData>(A->data)};
    A->_right->_right = Ar;
    A->_right->_left = Cr;
    A->data = C->data;
    C->_left = nullptr;
    C->_right = nullptr;
    C->data = TData{};
    delete C;
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::RR_rotate() 
{
    _AvlTree* A = this;
    _AvlTree* B = this->_right;
    _AvlTree* C = this->_right->_right;
    _AvlTree* Ar = A->_left;
    _AvlTree* Br = B->_left;

    B->_left = new _AvlTree(std::forward<TData>(A->data));
    B->_left->_left = Ar;
    B->_left->_right = Br;
    //std::swap(*this,*B);
    this->_left = B->_left;
    this->_right = B->_right;
    this->data = B->data;
    B->_left = nullptr;
    B->_right = nullptr;
    B->data = TData{};
    delete B;
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::RL_rotate() 
{
    _AvlTree* A = this;
    _AvlTree* B = this->_right;
    _AvlTree* C = B->_left;
    _AvlTree* Cl = C->_right;
    _AvlTree* Cr = C->_left;
    _AvlTree* Ar = A->_left;
    B->_left = Cl;
    A->_left = new _AvlTree{std::forward<TData>(A->data)};
    A->_left->_left = Ar;
    A->_left->_right = Cr;
    A->data = C->data;
    C->_left = nullptr;
    C->_right = nullptr;
    C->data = TData{};
    delete C;
}

template<typename TData,typename _Compare>
void AvlTree<TData,_Compare>::balance() 
{
    int balance = this->get_balance_factor();
    
    if(abs(balance)<=1) return;
    switch (balance)
    {
    case -2:
        switch(this->_right->get_balance_factor()){
            case -1:
                this->RR_rotate();
                break;
            case 1:
                this->RL_rotate();
                break;
            default:
                break;
        }
        break;
    case 2:
        switch(this->_left->get_balance_factor()){
            case 1:
                this->LL_rotate();
                break;
            case -1:
                this->LR_rotate();
                break;
            default:
                break;
        }
    default:
        break;
    }
}

template<typename TData,typename _Compare>
inline int AvlTree<TData,_Compare>::get_balance_factor() const noexcept 
{
    return
    (this->_left!=nullptr ? this->_left->get_height() : 0 )
    - 
    (this->_right!=nullptr ? this->_right->get_height() : 0);
}

template<typename TData,typename _Compare>
int AvlTree<TData,_Compare>::get_count() 
{
    _AvlTree* left = this->_left;
    _AvlTree* right = this->_right;
    return 
    (left!=nullptr ? left->get_count() : 0) + 
    (right!=nullptr ? right->get_count() : 0)
    +1;
}

template<typename TData,typename _Compare>
int AvlTree<TData,_Compare>::get_height() {
    _AvlTree* left = this->_left;
    _AvlTree* right = this->_right;

    int left_height = _left!=nullptr ? _left->get_height() : 0;
    int right_height = right ? right->get_height() : 0;

    return std::max(left_height,right_height) + 1;
}
