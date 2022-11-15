#include <iostream>


#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <bits/stdc++.h>
using namespace std;


template<typename T>
class Stack : public stack<T> {

public:
    T pop() {
        T tmp =  stack<T>::top();
        stack<T>::pop();
        return tmp;
    }


};

template<typename T>
class Queue : public queue<T>{

public:
    T dequeue() {
        T tmp = queue<T>::front();
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const T& el) {
        queue<T>::push(el);
    }

    /*
    std::list<T> pool;
    //int size_c = 0;
    Queue() {
    }
    void clear() {
        pool.clear();
    }
    bool isEmpty() const {
        return pool.empty();
    }
    T& topEl() {
        return pool.back();
    }
    T dequeue() {
        T el = pool.front();
        pool.pop_front();
        return el;
    }
    void enqueue(const T& el) {
        pool.push_back(el);
    }
    int size(){
        return pool.size();
    }
     */


};




template<class T> class BST;

template<class T>
class BSTNode {
public:
    BSTNode() {
        left = right = 0;
    }
    explicit BSTNode(const T& e, BSTNode<T> *l = nullptr, BSTNode<T> *r = nullptr) {
        el = e; left = l; right = r;
    }
    T el;
    BSTNode<T> *left, *right;
};

template<class T>
class BST {
public:
    BST() {
        root = nullptr;
    }
    ~BST() {
        clear();
    }
    void clear() {
        clear(root);
        root = nullptr;
    }
    bool isEmpty() const {
        return root == 0;
    }
    void preorder() {
        preorder(root);
    }
    void inorder() {
        inorder(root);
    }
    void postorder() {
        postorder(root);
    }
    void insert(const T&);
    void recursiveInsert(const T& el) {
        recursiveInsert(root,el);
    }
    T* search(const T& el) const {
        return search(root,el);
    }
    T* recursiveSearch(const T& el) const {
        return recursiveSearch(root,el);
    }
    void deleteByCopying(BSTNode<T>*&);
    void findAndDeleteByCopying(const T&);
    void deleteByMerging(BSTNode<T>*&);
    void findAndDeleteByMerging(const T&);
    void iterativePreorder();
    void iterativeInorder();
    void iterativePostorder();
    void breadthFirst();
    void MorrisPreorder();
    void MorrisInorder();
    void MorrisPostorder();
    void balance(T*,int,int);
protected:
    BSTNode<T>* root;
    void clear(BSTNode<T>*);
    void recursiveInsert(BSTNode<T>*&, const T&);
    T* search(BSTNode<T>*, const T&) const;
    T* recursiveSearch(BSTNode<T>*, const T&) const;
    void preorder(BSTNode<T>*);
    void inorder(BSTNode<T>*);
    void postorder(BSTNode<T>*);
    virtual void visit(BSTNode<T>* p) {
        cout << p->el << ' ';
    }
};


template<class T>
void BST<T>::clear(BSTNode<T> *p) {
    if (p != nullptr) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}



template<class T>
void BST<T>::insert(const T& el) {
    BSTNode<T> *p = root, *prev = nullptr;
    while (p != nullptr) {  // find a place for inserting new node;
        prev = p;
        if (el < p->el)
            p = p->left;
        else p = p->right;
    }
    if (root == nullptr)    // tree is empty;
        root = new BSTNode<T>(el);
    else if (el < prev->el)
        prev->left  = new BSTNode<T>(el);
    else prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::recursiveInsert(BSTNode<T>*& p, const T& el) {
    if (p == 0)
        p = new BSTNode<T>(el);
    else if (el < p->el)
        recursiveInsert(p->left, el);
    else recursiveInsert(p->right,el);
}

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const {
    while (p != nullptr)
        if (el == p->el)
            return &p->el;
        else if (el < p->el)
            p = p->left;
        else p = p->right;
    return nullptr;
}

template<class T>
T* BST<T>::recursiveSearch(BSTNode<T>* p, const T& el) const {
    if (p != 0)
        if (el == p->el)
            return &p->el;
        else if (el < p->el)
            return recursiveSearch(p->left,el);
        else return recursiveSearch(p->right,el);
    else return 0;
}


template<class T>
void BST<T>::iterativePreorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p = root;
    if (p != nullptr) {
        travStack.push(p);
        while (!travStack.empty()) {
            p = travStack.pop();
            visit(p);
            if (p->right != nullptr)
                travStack.push(p->right);
            if (p->left != nullptr)             // left child pushed after right
                travStack.push(p->left); // to be on the top of the stack;
        }
    }
}

template<class T>
void BST<T>::iterativeInorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p = root;
    while (p != nullptr) {
        while (p != nullptr) {                 // stack the right child (if any)
            if (p->right)                // and the node itself when going
                travStack.push(p->right); // to the left;
            travStack.push(p);
            p = p->left;
        }
        p = travStack.pop();             // pop a node with no left child
        while (!travStack.empty() && p->right == nullptr) { // visit it and all nodes
            visit(p);                                 // with no right child;
            p = travStack.pop();
        }
        visit(p);                        // visit also the first node with
        if (!travStack.empty())          // a right child (if any);
            p = travStack.pop();
        else p = nullptr;
    }
}

template<class T>
void BST<T>::iterativePostorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T>* p = root, *q = root;
    while (p != nullptr) {
        for ( ; p->left != nullptr; p = p->left)
            travStack.push(p);
        while (p->right == nullptr || p->right == q) {
            visit(p);
            q = p;
            if (travStack.empty())
                return;
            p = travStack.pop();
        }
        travStack.push(p);
        p = p->right;
    }
}



template<class T>
void BST<T>::breadthFirst() {
    Queue<BSTNode<T>*> queue;
    BSTNode<T> *p = root;
    if (p != nullptr) {
        queue.enqueue(p);
        while (!queue.empty()) {
            p = queue.dequeue();
            visit(p);
            if (p->left != nullptr)
                queue.enqueue(p->left);
            if (p->right != nullptr)
                queue.enqueue(p->right);
        }
    }
}


template<class T>
void BST<T>::balance (T data[], int first, int last) {
    if (first <= last) {
        int middle = (first + last)/2;
        insert(data[middle]);
        balance(data,first,middle-1);
        balance(data,middle+1,last);
    }
}

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>*& node) {
    BSTNode<T> *previous, *tmp = node;
    if (node->right == 0)                  // node has no right child;
        node = node->left;
    else if (node->left == 0)              // node has no left child;
        node = node->right;
    else {
        tmp = node->left;                  // node has both children;
        previous = node;                  // 1.
        while (tmp->right != 0) {         // 2.
            previous = tmp;
            tmp = tmp->right;
        }
        node->el = tmp->el;               // 3.
        if (previous == node)
            previous->left  = tmp->left;
        else previous->right = tmp->left; // 4.
    }
    delete tmp;                            // 5.
}


template<class T>
void BST<T>::findAndDeleteByCopying(const T& el) {
    BSTNode<T> *p = root, *prev = 0;
    while (p != 0 && !(p->el == el)) {
        prev = p;
        if (el < p->el)
            p = p->left;
        else p = p->right;
    }
    if (p != 0 && p->el == el)
        if (p == root)
            deleteByCopying(root);
        else if (prev->left == p)
            deleteByCopying(prev->left);
        else deleteByCopying(prev->right);
    else if (root != 0)
        cout << "el " << el << " is not in the tree\n";
    else cout << "the tree is empty\n";
}



void menu(){
    std::cout.width(20);
    std::cout<<"MENU"<<std::endl<<std::endl<<"Create (0), Search (1), Breadth-First Traversal (2) \nDepth-First Traversal: preorder (3), inorder (4), postorder (5)\nDelete Node (6)"<<std::endl;
    std::cout<<"Exit Program (7)"<<std::endl<<"Choose?";

}




BST<int> Binary_Tree;
// make a disposition based on input
std::string decision(const std::string& user_input){
    std::string key = "null";

    std::string del = " ";//parameter to use
    std::stringstream ss(user_input);
    std::string word;
    std::vector<std::string> wordlist{};//command vector
/*
while (!ss.eof()) {
    getline(ss, word, del);
    std::cout << word << std::endl;
}
*/

    while (ss >> word) {//splits string by space
        //std::cout << word << std::endl;

        wordlist.push_back(word);//puts the individual strings into a vector
        if(wordlist.size()>50){//if there is are 3 detected inputs then return error
            std::cout<<"Input has too many parameters. Please try again."<<std::endl;
            //wordlist.empty();
            return key;
            //break;
        }
    }
    //checks if the first input matches the command number and is a valid input
    if((wordlist.at(0) == ("1")||wordlist.at(0)=="6")&&
       wordlist.size()!=2){
        std::cout<<"No input parameter"<<std::endl;
        return key;
    }

    else if ((wordlist.at(0) == ("2")||
              wordlist.at(0) == ("3")||
              wordlist.at(0) == ("4")||
              wordlist.at(0) == ("5"))
              &&wordlist.size()!=1){
        std::cout<<"too many inputs"<<std::endl;
        return key;
    }

    //check valid input or if the input value is 0
    if(wordlist.size() == 2){
        for(char i : wordlist.at(1)) {
            if (!std::isdigit(i)) {
                std::cout << "input is not a int or is negative" << std::endl;
                return key;
            }
        }

    }


    if(wordlist.at(0) == "0"){
        for(int k=1; k<wordlist.size();k++)
            Binary_Tree.insert(stoi(wordlist.at(k)));


    }

    else if(wordlist.at(0) == "1"){
        if(Binary_Tree.search(stoi(wordlist.at(1)))){
            cout<<"Found Number"<<endl;
        }
        else{
            cout<<"There is no such node in the tree!"<<endl;
        }

    }

    else if(wordlist.at(0) == "2"){
        Binary_Tree.breadthFirst();



    }
    else if(wordlist.at(0) == "3"){
        Binary_Tree.iterativePreorder();



    }
    else if(wordlist.at(0) == "4"){
        Binary_Tree.iterativeInorder();



    }
    else if(wordlist.at(0) == "5"){
        Binary_Tree.iterativePostorder();



    }
    else if(wordlist.at(0) == "6"){
        Binary_Tree.findAndDeleteByCopying(stoi(wordlist.at(1)));



    }
    else if(wordlist.at(0) == "7"){
        key = "exit"; //pass exit code
    }

    return key;
}





int main() {

    std::string exit = "go";
    //vector<vector<int>> map;
    while(exit != "exit") {

        menu();
        std::string u_input;
        getline(std::cin,u_input);




        exit = decision(u_input);//decide on output checks if it should exit

    }
    std::cout<<"Program finished have a nice day!"<<std::endl;//a friendly message
    return 0;
}
