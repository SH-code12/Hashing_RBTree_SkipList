#include <iostream>
using namespace std;

class Node{
public:
    int key;
    Node* right, *left, *parent;
    // true ---> Red , false ---> Black
    bool color ;

    Node(int key){
        this->key = key;
        color = true;
        left = right = parent = nullptr;
    }

};

class RedBlackTree{
private:
    Node *root;
    Node *nil;

    void rightRotate(Node *&root , Node *&A){
        Node *B = A->left;
        A->left = B->right;

        if (B->right != nullptr){
            B->right->parent = A;
        }
        B->parent = A->parent;

        if (A->parent == nullptr){
            root = B;
        }else if (A == A->parent->left){
            A->parent->left = B;
        }else{
            A->parent->right = B;
        }
        B->right = A;
        A->parent = B;
    }

    void lefttRotate(Node *&root , Node *&A){
        Node *B = A->right;
        A->right = B->left;

        if (B->left != nullptr){
            B->left->parent = A;
        }
        B->parent = A->parent;

        if (A->parent == nullptr){
            root = B;
        }else if (A == A->parent->left){
            A->parent->left = B;
        }else{
            A->parent->right = B;
        }
        B->left = A;
        A->parent = B;
    }
    // function handle cases of insertion
    void handelInsertion(Node *&root , Node *&node){
        Node *parent , *grandParent , *uncle = nullptr;
        // handle until this condition fail
        while (node != root && node->color == true && node->parent->color == true){
            parent = node->parent;
            grandParent = node->parent->parent;
            // parent = red then grandParent = black
            if (parent == grandParent->left){
                uncle = grandParent->right;
                // uncle red and in right location
                if (uncle != nullptr && uncle->color == true){
                    // recolor
                    grandParent->color = true;
                    parent->color = false;
                    uncle->color = false;

                    node = grandParent;
                }
                // uncle black and in right location
                else{
                    if (node == parent->right){
                        lefttRotate(root , parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotate(root , grandParent);
                    swap(parent->color , grandParent->color);
                    node = parent;
                }
            } else{
                uncle = grandParent->left;
                // uncle red and in left location
                if (uncle != nullptr && uncle->color == true){
                    // recolor
                    grandParent->color = true;
                    parent->color = false;
                    uncle->color = false;

                    node = grandParent;
                }
                // uncle black and in left location
                else{
                    if (node == parent->left){
                        rightRotate(root , parent);
                        node = parent;
                        parent = node->parent;
                    }
                    lefttRotate(root , grandParent);
                    swap(parent->color , grandParent->color);
                    node = parent;
                }
            }
        }
        root->color = false;
    }

    // Function to traverse tree elements
    void printTree(Node *node){
        if (node == nullptr){
            return;
        }
        printTree(node->left);
        if (node->color == true){
            cout<<node->key <<", Red\n";
        } else{
            cout<<node->key <<", Black\n";
        }
        printTree(node->right);
    }
    // function to handle deletion cases
    void handleDeletion(Node *&node){
        Node *sibling = nullptr;
        // handle until this condition fail
        while (node != root && (node == nullptr || node->color == false)){
            // node in left location
            if (node == node->parent->left){
                sibling = node->parent->right;
                // if sibling red
                if (sibling->color == true){
                    sibling->color = false;
                    node->parent->color = true;
                    lefttRotate(root,node->parent);
                    sibling = node->parent->right;
                }
                // its children black : both black
                if ((sibling == nullptr) || (sibling->left == nullptr || sibling->left->color == false)
                    && (sibling->right == nullptr || sibling->right->color == false)){
                    // recolor sibling and double black to parent
                    if (sibling != nullptr) {sibling->color = true;}
                    node = node->parent;
                } else{
                    // sibling right child black : near is red
                    if (sibling->right == nullptr || sibling->right->color == false){
                        // recolor sibling and double black to parent
                        if (sibling->left != nullptr){
                            sibling->left->color = false;
                        }
                        sibling->color = true;
                        rightRotate(root,sibling);
                        sibling = node->parent->right;
                    }
                    // sibling right child red : far is red
                    sibling->color = node->parent->color;
                    node->parent->color = false;
                    if (sibling->right != nullptr){
                         sibling->right->color = false;
                    }
                    lefttRotate(root,node->parent);
                    node = root;
                }
            }
            else{
                // node in right location
                sibling = node->parent->left;
                // if sibling red
                if (sibling != nullptr && sibling->color == true){
                    sibling->color = false;
                    node->parent->color = true;
                    rightRotate(root,node->parent);
                    sibling = node->parent->left;
                }
                // its children black
                if ((sibling == nullptr) || (sibling->left == nullptr || sibling->left->color == false)
                    && (sibling->right == nullptr || sibling->right->color == false)){
                    // recolor sibling and double black to parent
                    if (sibling != nullptr) {sibling->color = true;}
                    node = node->parent;
                } else{
                    // sibling left child black : near is red
                    if (sibling->left == nullptr || sibling->left->color == false){
                        // recolor sibling and double black to parent
                        if (sibling->right != nullptr){
                            sibling->right->color = false;
                        }
                        sibling->color = true;
                        lefttRotate(root,sibling);
                        sibling = node->parent->left;
                    }
                    // sibling left child red : far is red
                    sibling->color = node->parent->color;
                    node->parent->color = false;
                    if (sibling->left != nullptr){
                        sibling->left->color = false;
                    }
                    rightRotate(root,node->parent);
                    node = root;
                }
            }
        }
        if (node != nullptr){
            node->color = false;
        }
    }
    // function to find successor : minimum in left subtree
    Node* findSuccessor(Node *node){
        while (node->left != nullptr){
            node = node->left;
        }
        return node;
    }
    // function to replace two nodes replace n1 with n2
    void replaceNode(Node *n1, Node *n2){
        // n1 is root
        if (n1->parent == nullptr){
            root = n2;
        }
            // n1 in left location
        else if (n1 == n1->parent->left){
            n1->parent->left = n2;
        }
            // n1 in right location
        else{
            n1->parent->right = n2;
        }
        if (n2 != nullptr){
            n2->parent = n1->parent;}
    }

    // function to search about node to delete it
    Node* search(Node* node , int key){
        while (node != nullptr){
            if (node->key == key){
                return node;
            }
            if (node->key <= key){
                node = node->right;
            } else{
                node = node->left;
            }
        }
        return nullptr;
    }

    void removeNode(Node *node, int key){
        Node *targetNode = search(node,key);
        if (targetNode == nullptr){
            cout<<"Key not found,try another key\n";
            return;
        }
        Node *successorChild ,*tempNode = targetNode;
        // save color of node
        bool tempColor = tempNode->color;
        // node has one child in right side
        if (targetNode->left == nullptr){
            successorChild = targetNode->right;
            replaceNode(targetNode, successorChild);
        }
        // node has one child in left side
        else if (targetNode->right == nullptr){
            successorChild = targetNode->left;
            replaceNode(targetNode, successorChild);
        }
        // has two children
        else{
            tempNode = findSuccessor(tempNode->right);
            tempColor = tempNode->color;
            successorChild = tempNode->right;
            if ( tempNode->parent == targetNode){
                if (successorChild != nullptr){
                    successorChild->parent = tempNode;
                }
            } else{
                replaceNode(tempNode,targetNode->right);
                tempNode->right = targetNode->right;
                tempNode->right->parent = tempNode;
            }
            replaceNode(targetNode,tempNode);
            tempNode->left = targetNode->left;
            tempNode->left->parent = tempNode;
            tempNode->color = targetNode->color;
        }
        delete targetNode;
        if (tempColor == false){
            handleDeletion(successorChild);
        }
    }

public:
    RedBlackTree (){
        root = nullptr;
    }
    // insertion Function
    void insert(int key){
        Node *node = new Node(key);

        if (root == nullptr){
            node->color = false;
            root = node;
        }
        else{
            Node *node2 = root;
            Node *parent = nullptr;

            while (node2 != nullptr){
                parent = node2;
                if (node->key < node2->key){
                    node2 = node2->left;
                } else{
                    node2 = node2->right;
                }
            }
            node->parent = parent;
            if (node->key < parent->key){
                parent->left = node;
            }
            else{
                parent->right = node;
            }
            handelInsertion(root,node);

        }
    }

    void Print(){
        printTree(root);
        cout<<"\n";
    }

    void remove(int key){
        removeNode(root,key);
    }

};

int main(){
    RedBlackTree RBT;
    cout<<"Tree: \n";
    RBT.insert(10);
    RBT.insert(20);
    RBT.insert(30);
    RBT.insert(15);
    RBT.insert(25);
    RBT.Print();
    cout<<"Tree: \n";
    RBT.remove(30);
    RBT.Print();
    return 0;
}
