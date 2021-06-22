#include "header.hpp"
#include "avl_tree.hpp"

void test1(AvlTree<int>* t);

int main(){
    using namespace std;
    AvlTree<int> tree{30};
    for(int i = 0;i<200;i++)
        tree.Add(rand()%250);
    
    cout<<tree.get_count()<<endl;
    cout<<tree.get_height()<<endl;
    cout<<tree.get_balance_factor()<<endl;
    
    test1(&tree);
}

void test1(AvlTree<int>* tree){
    using namespace std;
    tree->Iterate(move([](AvlTree<int>* node){
        if(node->Left()!=nullptr)
        if(node->Left()->Data()>node->Data())
            throw runtime_error("Wrong shit " 
                                + to_string(node->Left()->Data()) 
                                + " > " 
                                + to_string(node->Data()));
        if(node->Right()!=nullptr)
        if(node->Right()->Data()<node->Data())
            throw runtime_error("Wrong shit " 
                                + to_string(node->Right()->Data()) 
                                + " < " 
                                + to_string(node->Data()));
        if(abs(node->get_balance_factor())>1)
            throw runtime_error("Wrong shit "
                                + to_string(node->Data())
                                + " have bad balance factor!");
    }));
}