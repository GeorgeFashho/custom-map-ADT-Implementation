/*mymap.h  - Custom implemntation of #include <map> header filer. 
             Implemented using a threaded balanced binary tree.

            written by: [George Fashho] on [15/11/2022] for [CS 251 FA22]
 */


#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename keyType, typename valueType>

class mymap {
 private:

    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };

    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap 


/*-----------------------------------------------------
    Helper function to make a copy of one map into another.
    Uses PreOrder traversal to traverse through the list 
    and copy elements into the other. 

    @param node: pointer to the root node

*/
    void copyRecursive(NODE *node){ 

        if(node == nullptr){ //checking if map is empty
            return;
        }
        else{

            this->put(node->key,node->value); //inserting new node into new BST
 
            copyRecursive(node->left); //going to the left

            if(node->isThreaded){ //checking if current node is threaded or not
                copyRecursive(nullptr); //if threaded then return
            }else{
                copyRecursive(node->right); //going right if node is not threaded
            }
        }
    }


/*-----------------------------------------------------
        Helper function to fill vector with nodes that need
        rebalancing using in-order traversal

        @param balanceNodes: vector to store nodes in
        @param violator: node violator
*/
void fillViolaterVector(vector<NODE*> &balanceNodes, NODE* violator){
    
    if(violator == nullptr){   
        return;
    }

    fillViolaterVector(balanceNodes,violator->left); //moving left

    balanceNodes.push_back(violator); //pushing values into vector

    if(violator->isThreaded){
        fillViolaterVector(balanceNodes,nullptr); //returning if threaded
    }else{

        fillViolaterVector(balanceNodes,violator->right); //going right
    }
}


/*-----------------------------------------------------
        Helper function to balance tree

        @param unbalancedNodes: vector of nodes to rebalance
        @param parent: parent node of violator
        @param left: starting point
        @param right: ending point
*/
 NODE* balanceTree(vector<NODE*>&unbalancedNodes, NODE* parent , int left, int right){

    if(right == -1){ //if vector empty
        return nullptr;
    }

    int mid = (left+right) / 2; //calculating mid
    NODE *newRoot = unbalancedNodes.at(mid); 

    if( unbalancedNodes.size() > 1 ){ //if vector only has more than one element
    //citation geeksforgeek for inspiration
        newRoot->left = balanceTree(unbalancedNodes, parent, left, mid-1);    //balancing left side
        newRoot->right = balanceTree(unbalancedNodes, parent, mid+1, right); //balancing right side

        newRoot->nL = 0;
        newRoot->nR = 0; 
        newRoot->isThreaded = true; 
        newRoot->right = parent ;
        return newRoot;
        
    }
     else if(unbalancedNodes.size() == 0){ //case for when there is only one element in the vector

        newRoot->nL = 0;
        newRoot->nR = 0; 
        newRoot->isThreaded = true; 
        newRoot->right = parent ;
        return newRoot;
    }
 
}
 

/*-----------------------------------------------------
        Helper function to print out every keyNode, number 
        of left leafs and number of right leafs in pre-order. 

        @param node: pointer to root node 
        @param output: output stream user chooses 
*/
    void checkBalanceRecursive(NODE* node, ostream& output){ 

        if(node == nullptr){  //checking if map is empty
            return;
        }

        output<< "key: "<< node->key <<", nL: "<< node->nL << ", nR: "<<node->nR << "\n"; //outputting node info

        checkBalanceRecursive(node->left, output); //going to left node

        if(node->isThreaded){ //checking if node is threaded
            checkBalanceRecursive(nullptr, output);

        }else{
            checkBalanceRecursive(node->right,output); //if not threaded then go right
        }

    }


/*-----------------------------------------------------
        Helper function to convert every element in the 
        BST and insert it into a vector with value type 
        being a pair of key and value. Uses in-order traversal

        @param node: pointer to root node 
        @param  vector<pair<keyType, valueType>>: vector with
        type, pair<key,value> 
*/
    void toVectorRecursive(NODE*current, vector<pair<keyType, valueType>> &vectorContainer){

        if(current == nullptr){ //checking if tree is empty
            return;
        }

        if(current->left != nullptr){ //going left first
 
            toVectorRecursive(current->left,vectorContainer);

        }
        pair<keyType,valueType> tempPair;
        tempPair.first = current->key;
        tempPair.second = current->value;
        vectorContainer.push_back(tempPair); //adding elements to vector

        if(current->isThreaded){

            toVectorRecursive(nullptr,vectorContainer); //returning if node is threaded

        }
        else{

            toVectorRecursive(current->right,vectorContainer); //going right 
        }

    }



/*-----------------------------------------------------
        Helper function to check if a node is a violator 
        or not. Uses the following equation to check and
        returns true or false; 

        if (max(current->nL,current->nR ))<= 2*(min(current->nL,current->nR)+ 1){
            return true;
        }

        @param current: pointer to current node in traversal 
*/
    bool checkViolator(NODE *current){
        return ((max(current->nL,current->nR ))<= 2*(min(current->nL,current->nR)+ 1)); 
    }


/*-----------------------------------------------------
        Helper function to delete every node in the BST
        in-order

        @param rootNode: pointer to root node 
*/
    void clearRecursive(NODE *rootNode){

        if(rootNode == nullptr){ //checking if bst is empty 
            return;
        }
        
        clearRecursive(rootNode->left); //going left recursively
        
        if(rootNode->isThreaded){ //if threaded then return
            clearRecursive(nullptr);

        }
        else{
            clearRecursive(rootNode->right); //going right
        }

/*         cout<<"Deleted node: "<<rootNode->key<<endl;
 */     delete rootNode; 
        size--;
    }

    

/*-----------------------------------------------------
        Helper function that traverses throught the 
        BST in-order to check if a key exists or 
        not. If key exists then change value of 
        the the key and return true.

        @param node: Pointer to root node
        @param key: node key
        @param value: value of key 
*/
    bool searchRecrsive(NODE *node, keyType key, valueType &value){

        if(node == nullptr){ //checking if BST is empty
            return false;
        }

        else if(node->key == key){   //if key already exists in BST then change
            value = node->value ;   // value and return true. 
            return true;
        }

        else if( node->key > key){  //going left
            return searchRecrsive(node->left, key,value);
        }
        else{
            if(node->isThreaded){ //checking if node is threaded

                return searchRecrsive(nullptr, key,value);

            }
            else{ //going right
                return searchRecrsive(node->right, key,value);
            }
        }
    }



/*-----------------------------------------------------
        Helper function to convert every element in the 
        BST and insert it into a vector with value type 
        being a pair of key and value. Uses in-order traversal

        @param node: pointer to root node 
        @param  vector<pair<keyType, valueType>>: vector with
        type, pair<key,value> 
*/
     void  toStringRecursive(NODE* node, ostream& output){ // Proj-4 code

        if(node == nullptr){
            return;
        }

        if(node->left !=nullptr){ //In-Order BST Recurssive Traversal
            toStringRecursive(node->left,output); //going left
        }

        output<< "key: "<< node->key <<" value: "<< node->value << "\n"; //output
        
        if(node->right != nullptr){ 

            if(node->isThreaded){
                toStringRecursive(nullptr,output) ; 
            }
            else{
                toStringRecursive(node->right,output); //going right
            }
        }
    }
    

/*-----------------------------------------------------
    iterator:
    his iterator is used so that mymap will work with a foreach loop.

*/
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end
         
        void leftMostNode(){ //function that moves curr to the leftmost node

            NODE *temp = curr;

            while(temp->left !=nullptr){
                temp = temp->left;
            }
            curr = temp ;
    }
    

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator == (const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }


/*-----------------------------------------------------
    operator++:
    his function should advance curr to the next in-order node.   
    O(logN)
*/
        iterator operator++() {

            if(curr == nullptr){
                return iterator(nullptr);  // checking if the BST is empty
            }
 
            if(!(curr->isThreaded)){ 
                
                if(curr->right != nullptr){
                    curr = curr->right;
                }
                if(curr->left != nullptr){ //moving curr to the leftmost node
                    leftMostNode();
                }
            }

            else{
                curr = curr->right;
            }
            return iterator(curr); //returning new curr
        }
    };

 public:
/*-----------------------------------------------------
        default constructor:
            Creates an empty mymap.
            Time complexity: O(1)
*/
    mymap() {
        root = nullptr;
        size = 0 ;

    }


/*-----------------------------------------------------
    Copy constructor:
        Constructs a new mymap which is a copy of the "other" mymap.
        Sets all member variables appropriately.
        Time complexity: O(nlogn), where n is total number of nodes in threaded,
        self-balancing BST.
        
        @param other: map we are copying from
*/
    mymap(const mymap& other) {

/*         myMap<keyType,valueType>tempMap; 
 */
        root = new NODE();
        root->value = other.root->value;
        root->key = other.root->key;

        copyRecursive(other.root); //copying recursively

        size = other.size;
    }


/*-----------------------------------------------------
    operator=:
        Clears "this" mymap and then makes a copy of the "other" mymap.
        Sets all member variables appropriately.
        Time complexity: O(nlogn), where n is total number of nodes in threaded,
        self-balancing BST.

        @param other: map we are copying from
*/
    mymap& operator=(const mymap& other) {

        NODE *temp = other.root;

         if(this == &other){  //edge case: if the two maps are already equal
            return *this;   //then do nothing
        } 

        this->clear(); //clearing the old map

        if(&other.root == nullptr){ //if the map we are copying from is already empty
            return *this;          // return the empty map
        } 

        copyRecursive(temp); //copying to this map from other map using recurssion
 
        return *this; 
    }


/*-----------------------------------------------------
    Clear:

        Frees the memory associated with the mymap; can be used for testing.
        Time complexity: O(n), where n is total number of nodes in threaded,
        self-balancing BST.
*/
    void clear() {
        
        if(root == nullptr){ //edge case if root does not exist
            return;
        }
        else{
            clearRecursive(root);   //call to recursive clear funciton
            root = nullptr;  
        }    
    }

    
/*-----------------------------------------------------
    destructor:

        Frees the memory associated with the mymap.
        Time complexity: O(n), where n is total number of nodes in threaded,
        self-balancing BST.
*/
    ~mymap() {
        clear(); 
    }


/*-----------------------------------------------------
    put:
        Inserts the key/value into the threaded, self-balancing BST based on
        the key.
        Time complexity: O(logn + mlogm), where n is total number of nodes in the
        threaded, self-balancing BST and m is the number of nodes in the
        sub-tree that needs to be re-balanced.
        Space complexity: O(1)

        @param key: node key with correct valueType
        @param value: node value with correct valueType
*/
    void put(keyType key, valueType value) {

        NODE *current = root; //root node
        NODE *newNode = new NODE(); //new node
        NODE *prev = nullptr; //prev pointer

        NODE *violator = nullptr; 
        NODE *parentV = prev;
        NODE *subRoot = nullptr; //root of the subTree

        vector<NODE*>imbalancedNodes; //vector to hold violator to reblance tree

        newNode->key = key;
        newNode->value = value; 
        newNode->left = nullptr;
        newNode->right = nullptr; //initialzing variabels
        newNode->isThreaded = false;
        newNode->nL = 0;
        newNode->nR = 0;

        if(current != nullptr){ //traversing through the list if root is != nullptr

            while(current != nullptr){ //keep going through list until correct location is found

                if(current->key < key){

                    current->nR++; //incremenign number of nodes to right

                    if(checkViolator(current)){ //checking for a violator
                        violator = current;
                        parentV = prev ;
                    }
                    
                    prev = current; //setting parent node

                    if(current->isThreaded){ //if threaded then end loop
                        current = nullptr;
                    }
                    else{
                        current = current->right; //going right
                    }
                }
                
                else if(current->key > key){
                    current->nL++;  //incremening number of nodes to the left

                    if(checkViolator(current)){
                        violator = current;
                        parentV = prev ;

                    }
                    prev = current;
                    current = current->left;
                }

                else if(current->key == key){ //if key already exists in the tree
                    current->value = value; //change the value of the key
                    return;
                }
            }

            if(prev->key < key){ //adding new node to right 

                newNode->right = prev->right;
                prev->right = newNode;
                prev->isThreaded = false;
                newNode->isThreaded = true;
            }
            else {  //adding new node to left
                prev->left = newNode;           
                newNode->right = prev;
                newNode->isThreaded = true;
            }
            size++;
            return;
        
        }
        else{ //if root does not exist intialize root
            root = newNode;
            size++;
            return;
        }


//  BALANCING CODE SEMI-FUNCTUNAL UNCOMMENT TO TEST (PASSES SOME TEST CASES BUT NOT OTHERS) //
        /* if(violator != nullptr){

            fillViolaterVector(imbalancedNodes,violator); //if violator exists then fill vector

            int left = 0 ;      //start point
            int right = imbalancedNodes.size() - 1 ; //calculating end point
            int mid = (left+right)/2 ; 

            subRoot = balanceTree(imbalancedNodes, parentV , left, right); //getting the new root of the sub tree

            if(subRoot != nullptr && parentV ==nullptr){    //edge case if there was only one node

                root = subRoot;

            }
            else{   //finding where the new root goes left or right

                if(subRoot->key > parentV->key){
                    parentV->right = subRoot;
                }
                else{
                    parentV->left = subRoot;
                }
            }
        } */
    }

    
/*-----------------------------------------------------
    contains:
        Returns true if the key is in mymap, return false if not.
        Time complexity: O(logn), where n is total number of nodes in the
        threaded, self-balancing BST
    */
    bool contains(keyType key) {
        valueType value ;
        return searchRecrsive(root,key,value);  //returning t/f is key is found or not
    }


/*-----------------------------------------------------
    get:
        Returns the value for the given key; if the key is not found, the
        default value, valueType(), is returned (but not added to mymap).
        Time complexity: O(logn), where n is total number of nodes in the
        Threaded, self-balancing BST
*/
    valueType get(keyType key) {

        valueType value ;
        if(searchRecrsive(root,key,value)){ //searching recursively
            return value;
        }

        return valueType();  //if not found return default value
    }


/*-----------------------------------------------------
    operator[]:
    
        Returns the value for the given key; if the key is not found,
        the default value, valueType(), is returned (and the resulting new
        key/value pair is inserted into the map).
        Time complexity: O(logn + mlogm), where n is total number of nodes in the
        threaded, self-balancing BST and m is the number of nodes in the
        sub-trees that need to be re-balanced.
        Space complexity: O(1)
*/
    valueType operator[](keyType key) {

        valueType value ;
        if(searchRecrsive(root,key,value)){
            return value; //if found return value
        }

        put(key,valueType()); //if not found insert new key with value as default
        return valueType();  //return default value
    }


/*-----------------------------------------------------
    Size:
        Returns the # of key/value pairs in the mymap, 0 if empty.
        O(1)
    */
    int Size() {
        return size; 
    }


/*-----------------------------------------------------
    begin:
    
        returns an iterator to the first in order NODE.
        Time complexity: O(logn), where n is total number of nodes in the
        threaded, self-balancing BST
    */
    iterator begin() {

        NODE *temp = root; //pointer to current root

        if(temp == nullptr){
            return iterator(nullptr); //if tree empty 
        }

        while(temp->left != nullptr){ //going to the leftmost node
            temp = temp->left;
        }
        
        return iterator(temp); 
    }


/*-----------------------------------------------------
  end:
    
    returns an iterator to the last in order NODE.
    this function is given to you.
    Time Complexity: O(1)
*/
    iterator end() {
        return iterator(nullptr);
    }


/*-----------------------------------------------------
  toString:
    
    Returns a string of the entire mymap, in order.
    Format for 8/80, 15/150, 20/200:
    "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    Time complexity: O(n), where n is total number of nodes in the
    threaded, self-balancing BST
*/
    string toString() {
        
        stringstream s;

        if(root == nullptr){ //if no BST return empty string
            return "";
        }

        toStringRecursive(root,s); //recurssive call to toString

        return s.str();
    }


/*-----------------------------------------------------
  toVector:

    Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    {{8, 80}, {15, 150}, {20, 200}}
    Time complexity: O(n), where n is total number of nodes in the
    threaded, self-balancing BST
    */
    vector<pair<keyType, valueType> > toVector() {

        vector<pair<keyType, valueType>> vectorContainer ; //vector to hold nodes in
        NODE*temp = root;

        toVectorRecursive(temp,vectorContainer);   //recurssive function to fill vector

        return vectorContainer;  
    }


/*-----------------------------------------------------
  checkBalance:
    
    Returns a string of mymap that verifies that the tree is properly
    balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    function should return a string in this format (in pre-order):
    "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    Time complexity: O(n), where n is total number of nodes in the
    threaded, self-balancing BST
    */
    string checkBalance() {

        NODE*temp = root;  //pointer to current root
        stringstream s;
        if(temp == nullptr){ //if no BST return empty string
            return "";
        }

        checkBalanceRecursive(temp,s) ; //function call to recurssive checkBalance
        
        
        return s.str();
    }
};
