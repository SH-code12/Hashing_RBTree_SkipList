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

    void rightRotate(Node *&node){
        Node *leftchild = node->left;
        node->left = leftchild->right;

        if (leftchild->right != nil){
            leftchild->right->parent = node;
        }
        leftchild->parent = node->parent;

        if (node->parent == nullptr){
            root = leftchild;
        }else if (node == node->parent->left){
            node->parent->left = leftchild;
        }else{
            node->parent->right = leftchild;
        }
        leftchild->right = node;
        node->parent = leftchild;
    }

    void lefttRotate(Node *&node){
        Node *rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nil){
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;

        if (node->parent == nullptr){
            root = rightChild;
        }else if (node == node->parent->left){
            node->parent->left = rightChild;
        }else{
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }
    // function handle cases of insertion
    void handelInsertion(Node *&node){
        Node *parent , *grandParent , *uncle = nullptr;
        // handle until this condition fail
        while (node != root && node->color == true && node->parent->color == true){
            parent = node->parent;
            grandParent = node->parent->parent;
            // parent = red then grandParent = black
            if (parent == grandParent->left){
                uncle = grandParent->right;
                // uncle red and in right location
                if ( uncle->color == true){
                    // recolor
                    grandParent->color = true;
                    parent->color = false;
                    uncle->color = false;

                    node = grandParent;
                }
                    // uncle black and in right location
                else{
                    if (node == parent->right){
                        lefttRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rightRotate(grandParent);
                    swap(parent->color , grandParent->color);
                    node = parent;
                }
            } else{
                uncle = grandParent->left;
                // uncle red and in left location
                if (uncle->color == true){
                    // recolor
                    grandParent->color = true;
                    parent->color = false;
                    uncle->color = false;

                    node = grandParent;
                }
                    // uncle black and in left location
                else{
                    if (node == parent->left){
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    lefttRotate(grandParent);
                    swap(parent->color , grandParent->color);
                    node = parent;
                }
            }
        }
        root->color = false;
    }

    // Function to traverse tree elements
    void printTree(Node *node){
        cout<< node->key <<", "<<((node->color )? "Red" : "Black")<<endl;

        if (node->left != nil){
            printTree(node->left);
        }
        if (node->right != nil){
            printTree(node->right);
        }
        return;
    }
    // function to handle deletion cases
    void handleDeletion(Node *&node){
        Node *sibling = nullptr;
        // handle until this condition fail
        while (node != root && node->color == false){
            // node in left location
            if (node == node->parent->left){
                sibling = node->parent->right;
                // if sibling red
                if (sibling->color == true){
                    sibling->color = false;
                    node->parent->color = true;
                    lefttRotate(node->parent);
                    sibling = node->parent->right;
                }
                // its children black : both black
                if (sibling->left->color == false && sibling->right->color == false){
                    // recolor sibling and double black to parent
                    sibling->color = true;
                    node = node->parent;
                } else{
                    // sibling right child black : near is red
                    if (sibling->right->color == false){
                        // recolor sibling and double black to parent
                        sibling->left->color = false;
                        sibling->color = true;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }
                    // sibling right child red : far is red
                    sibling->color = node->parent->color;
                    node->parent->color = false;
                    sibling->right->color = false;
                    lefttRotate(node->parent);
                    node = root;
                }
            }
            else{
                // node in right location
                sibling = node->parent->left;
                // if sibling red
                if (sibling->color == true){
                    sibling->color = false;
                    node->parent->color = true;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }
                // its children black
                if (sibling->left->color == false && sibling->right->color == false){
                    // recolor sibling and double black to parent
                    sibling->color = true;
                    node = node->parent;
                } else{
                    // sibling left child black : near is red
                    if (sibling->left->color == false){
                        // recolor sibling and double black to parent
                        sibling->right->color = false;
                        sibling->color = true;
                        lefttRotate(sibling);
                        sibling = node->parent->left;
                    }
                    // sibling left child red : far is red
                    sibling->color = node->parent->color;
                    node->parent->color = false;
                    sibling->left->color = false;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = false;
    }
    // function to find successor : minimum in left subtree
    Node* findSuccessor(Node *node){
        while (node->left != nil){
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
        n2->parent = n1->parent;
    }

public:
    RedBlackTree (){
        nil = new Node(0);
        nil->color = false;
        root = nil;
    }
    // insertion Function
    void insert(int key){
        Node *newnode = new Node(key) , *parent = nullptr , *current = root;

        newnode->left = nil;
        newnode->right = nil;

        while (current != nil){
            parent = current;
            if (newnode->key < current->key){
                current = current->left;
            } else{
                current = current->right;}
        }
        newnode->parent = parent;
        if (parent == nullptr){
            root = newnode;
        } else if (newnode->key < parent->key){
            parent->left = newnode;
        } else{
            parent->right = newnode;
        }
        handelInsertion(newnode);
    }

    void Print(){
        printTree(root);
        cout<<"\n";
    }


    // function to search about node to delete it

    void remove(int key){
        Node *temp = root;
        while (temp != nil){
            if (temp->key == key){
                break;
            } else if (key < temp->key){
                temp = temp->left;
            } else{
                temp = temp->right;
            }
        }
        if (temp == nil){
            cout<<"Key not found,try another key\n";
            return;
        }
        Node *targetNode = temp;
        // save color of node
        bool originalColor = targetNode->color;
        Node *successorChild;
        // node has one child in right side
        if (temp->left == nil){
            successorChild = temp->right;
            replaceNode(temp, temp->right);
        }
            // node has one child in left side
        else if (temp->right == nullptr){
            successorChild = targetNode->left;
            replaceNode(temp, temp->left);
        }
            // has two children
        else{
            targetNode = findSuccessor(temp->right);
            originalColor = targetNode->color;
            successorChild = targetNode->right;
            if ( targetNode->parent == temp){
                successorChild->parent = targetNode;

            } else{
                replaceNode(targetNode,targetNode->right);
                targetNode->right = temp->right;
                targetNode->right->parent = targetNode;
            }
            replaceNode(temp,targetNode);
            targetNode->left = temp->left;
            targetNode->left->parent = targetNode;
            targetNode->color = temp->color;
        }
        delete temp;
        if (originalColor == false){
            handleDeletion(successorChild);
        }
    }

};

int main(){
    RedBlackTree RBT;
    cout<<"Tree: \n";
    RBT.insert(10);
    RBT.insert(20);
    RBT.insert(30);
    RBT.insert(25);
    RBT.Print();
    cout<<"Tree After Deletion: \n";
    RBT.remove(10);
    RBT.Print();
    return 0;
}