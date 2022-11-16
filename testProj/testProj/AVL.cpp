#include "AVL.h"
#include <vector>
#include <iostream>

AVL::AVL()
{
    root = nullptr;
}

void AVL::clear()
{
    std::vector< Node* > stack;

    stack.push_back(root);

    while (!stack.empty())
    {
        Node* tmp = stack.back();
        stack.pop_back();

        if (!tmp) continue;
        stack.push_back(tmp->left);
        stack.push_back(tmp->right);

        delete tmp;
    }

    root = nullptr;
}

void AVL::directPrint()
{
    std::vector< Node* > stack;
    stack.push_back(root);

    while (!stack.empty())
    {
        Node* tmp = stack.back();
        stack.pop_back();

        if (!tmp) continue;

        std::cout << tmp->key << " " << tmp->data << "\n";

        stack.push_back(tmp->right);
        stack.push_back(tmp->left);
    }
}

void AVL::reversePrint()
{
    std::vector< std::pair<Node*, std::pair<bool, bool> > > stack;
    stack.push_back({ root, {false, false} });

    while (!stack.empty())
    {
        std::pair<Node*, std::pair<bool, bool> > tmp = stack.back();

        if (!tmp.first)
        {
            stack.pop_back();
            continue;
        }

        if (!tmp.second.first)
        {
            stack.back().second.first = true;
            stack.push_back({ tmp.first->left, {false, false} });
            continue;
        }

        if (!tmp.second.second)
        {
            stack.back().second.second = true;
            stack.push_back({ tmp.first->right, {false, false} });
            continue;
        }

        std::cout << tmp.first->key << " " << tmp.first->data << "\n";
        stack.pop_back();
    }
}

void AVL::keySortedPrint()
{
    std::vector< std::pair<Node*, bool> > stack;
    stack.push_back({ root, false });

    int k = 0;

    while (!stack.empty())
    {
        std::pair<Node*, bool> tmp = stack.back();

        if (!tmp.first)
        {
            stack.pop_back();
            continue;
        }

        if (tmp.second)
        {
            std::cout << tmp.first->key << " " << tmp.first->data << "\n";
            k++;
            stack.pop_back();
            stack.push_back({ tmp.first->right, false });
        }
        else
        {
            stack.back().second = true;
            stack.push_back({ tmp.first->left, false });
        }
    }
}

AVL::~AVL()
{
    clear();
}

//
std::string& AVL::operator[](ll key)
{

    if (root == nullptr || root->find(root, key) == nullptr)
        add(key, "");

    return root->find(root, key)->data;
}


void AVL::add(ll key, str value)
{
    if (root == nullptr) {

        root = new Node(key, value);

        return;
    }

    root = root->insert(root, key, value);
}

void AVL::remove(ll key)
{
    if (root == nullptr)
        return;

    root = root->deleteNode(root, key);
}

std::string AVL::findValueWithKey(ll key)
{
    if (root == nullptr || root->find(root, key) == nullptr)
        throw std::exception();

    return root->find(root, key)->data;
}

bool AVL::contains(ll key)
{
    return root != nullptr && root->find(root, key) != nullptr;
}

AVL::Node::Node(ll nKey, str nValue)
{
    left = right = nullptr;
    data = nValue;
    key = nKey;
    height = 1;
}

AVL::Node::Node()
{
    left = right = nullptr;
    data = "";
    key = 0;
    height = 1;
}


//Create new node and return it.
AVL::Node* AVL::Node::newNode(ll nKey, str nValue)
{
    Node* node = new Node();
    node->key = nKey;
    node->data = nValue;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; 

    return(node);
}

int AVL::Node::getHeight(Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int AVL::Node::max(int a, int b)
{
    return (a > b) ? a : b;
}

AVL::Node* AVL::Node::rightRotate(Node* node)
{
    Node* x = node->left;
    Node* T2 = x->right;

    // Perform rotation 
    x->right = node;
    node->left = T2;

    // Update heights 
    node->height = max(getHeight(node->left),
        getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left),
        getHeight(x->right)) + 1;

    // Return new root 
    return x;
}

AVL::Node* AVL::Node::leftRotate(Node* node)
{
    Node* y = node->right;
    Node* T2 = y->left;

    // Perform rotation 
    y->left = node;
    node->right = T2;

    // Update heights 
    node->height = max(getHeight(node->left),
        getHeight(node->right)) + 1;
    y->height = max(getHeight(y->left),
        getHeight(y->right)) + 1;

    // Return new root 
    return y;
}

int AVL::Node::getBalance(Node* node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) -
        getHeight(node->right);
}

AVL::Node* AVL::Node::insert(Node* node, int key, str value)
{
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key, value));

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else // Equal keys not allowed 
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(getHeight(node->left),
        getHeight(node->right));

    /* 3. Get the balance factor of this
        ancestor node to check whether
        this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced,
    // then there are 4 cases 

    // Left Left Case 
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case 
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case 
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case 
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

AVL::Node* AVL::Node::minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

AVL::Node* AVL::Node::deleteNode(Node* root, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE 
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller 
    // than the root's key, then it lies
    // in left subtree 
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater 
    // than the root's key, then it lies 
    // in right subtree 
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then 
    // This is the node to be deleted 
    else
    {
        // node with only one child or no child 
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node* temp = root->left ?
                root->left :
                root->right;

            // No child case 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case 
                *root = *temp; // Copy the contents of 
            // the non-empty child 
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's 
            // data to this node 
            root->key = temp->key;

            // Delete the inorder successor 
            root->right = deleteNode(root->right,
                temp->key);
        }
    }

    // If the tree had only one node
    // then return 
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(getHeight(root->left),
        getHeight(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF 
    // THIS NODE (to check whether this 
    // node became unbalanced) 
    int balance = getBalance(root);

    // If this node becomes unbalanced, 
    // then there are 4 cases 

    // Left Left Case 
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case 
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case 
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case 
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVL::Node* AVL::Node::find(Node *node, ll key)
{
    if (!node)
        return nullptr;

    if (node->key > key)
        return find(node->left, key);
    else if (node->key < key)
        return find(node->right, key);
    else
        return node;
}
