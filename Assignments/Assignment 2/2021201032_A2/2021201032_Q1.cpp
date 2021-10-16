#include<iostream>
#include<string>
#include<utility>

using namespace std;

template <class T>
class Node {
   public:
    T value;
    Node *left, *right;
    // Height of that node
    int height;
    // Count no.of times an element occur in AVL tree
    int frequency;
    // No.of nodes in the left subtree (along with the root)
    int leftSubtreeCount;

    Node(T val);
};

template <class T>
Node<T>::Node(T val) {
    value = val;
    left = right = NULL;
    height = 0;
    frequency = 0;
    leftSubtreeCount = 0;
}

// class Rectangle{
// public:
// 	int l,b;
// 	Rectangle(){
// 		l = 10;
// 		b = 20;
// 	}
// 	Rectangle(int length,int breadth){
// 		l = length;
// 		b = breadth;
// 	}
// 	bool operator <(Rectangle obj){
// 		if(l < obj.l)
// 			return true;
//         else if(l == obj.l && b < obj.b)
//             return true;
//         else
//             return false;
// 	}
// 	bool operator >(Rectangle obj){
// 		if(l > obj.l )
// 			return true;
//         else if(l == obj.l && b > obj.b)
//             return true;
//         else
//             return false;
// 	}
// 	bool operator ==(Rectangle obj){
// 		return (l == obj.l && b == obj.b);
// 	}
//     int operator -(Rectangle obj){
//         return l - obj.l;
//     }
// };

class Square{
public:
	int s;
	Square(){
        s = 10;
	}
	Square(int length){
        s = length;
	}
	bool operator <(Square obj){
		if(s < obj.s)
			return true;
        else
            return false;
	}
	bool operator >(Square obj){
		if(s > obj.s)
			return true;
        else
            return false;
	}
	bool operator ==(Square obj){
		return s == obj.s;
	}
    int operator -(Square obj){
        return s - obj.s;
    }
};

template <class T>
class AVL {
   public:

    Node<T> *root;
    bool small = false, large = false;
    T smallest, largest;

    int size;
    // Constructor
    AVL();

    // Helper functions
    int height(Node<T> *root);
    int balanceFactor(Node<T> *root);
    Node<T> *leftRotate(Node<T> *root);
    Node<T> *rightRotate(Node<T> *root);
    void inorderTraversal(Node<T> *root);

    // Insert
    void insert(T val);
    Node<T> *insertHelper(Node<T> *root, T val);

    // Delete
    void deleteNode(T val);
    Node<T> *deleteHelper(Node<T> *root, T val);
    Node<T> *smallestNode(Node<T> *root);

    // Search
    Node<T> *search(T val);
    Node<T> *searchHelper(Node<T> *root, T val);

    // Count no.of elements
    int count(T val);
    int countHelper(Node<T> *root, T val);

    // lower_bound
    void lowerBound(T val);
    // void lowerBoundHelper(Node<T> *root, T val, T &ans);
    void lowerBoundHelper(Node<T> *root, T val, Node<T>* &lb);

    // upper_bound
    void upperBound(T val);
    // void upperBoundHelper(Node<T> *root, T val, T &ans);
    void upperBoundHelper(Node<T> *root, T val, Node<T>* &ub);

    // Closest value
    T closestValue(T val);
    void closestValueHelper(Node<T> *root, T val, T &ans, int &minAns, bool &ansFound);

    // KthLargest
    T KthLargest(int k);
    void KthLargestHelper(Node<T> *root, int k, int &treeSize, int &count, Node<T> * &KthLargestNode);

    // No.of values in the range
    int range(T a, T b);
    // Find left Interval
    void leftInterval(Node<T> *root, T a, int &leftIntervalCount);
    // Find right Interval
    void rightInterval(Node<T> *root, T b, int &rightIntervalCount);
};

template <class T>
AVL<T>::AVL() {
    root = NULL;
    size = 0;
}

template <class T>
int AVL<T>::height(Node<T> *root) {
    if (root == NULL) {
        return -1;
    }
    return root->height;
}

template <class T>
int AVL<T>::balanceFactor(Node<T> *root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

template <class T>
void AVL<T>::inorderTraversal(Node<T> *root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    for (int i = 0; i < root->frequency; i++) {
        cout << "(" << root->value << "," << root->frequency << ","
             << root->height << ", LSCt: " << root->leftSubtreeCount << "), ";
        // cout << "(" << root->value.s << "," << root->frequency << ","
        //      << root->height << ", LSCt: " << root->leftSubtreeCount << "), ";
        // cout << "(" << root->value.l <<" "<< root->value.b << "," << root->frequency << ","
        //      << root->height << ", LSCt: " << root->leftSubtreeCount << "), ";

    }
    inorderTraversal(root->right);
}

template <class T>
Node<T> *AVL<T>::leftRotate(Node<T> *root) {
    // cout << "Left rotation" << endl;
    Node<T> *tempRoot = root->right;
    Node<T> *tempChild = tempRoot->left;

    // Updating the leftSubtreeCount value of the new root
    tempRoot->leftSubtreeCount += root->leftSubtreeCount;

    // Changing the links
    tempRoot->left = root;
    root->right = tempChild;

    // Updating heights
    root->height = max(height(root->left), height(root->right)) + 1;
    tempRoot->height = max(height(tempRoot->left), height(tempRoot->right)) + 1;
    return tempRoot;
}

template <class T>
Node<T> *AVL<T>::rightRotate(Node<T> *root) {
    // cout << "Right rotation" << endl;
    // Storing the nodes in temporary nodes
    Node<T> *tempRoot = root->left;
    Node<T> *tempChild = tempRoot->right;

    // Updating the leftSubtreeCount value of the root
    root->leftSubtreeCount -= tempRoot->leftSubtreeCount;

    // Changing the links
    tempRoot->right = root;
    root->left = tempChild;

    // Updating heights
    root->height = max(height(root->left), height(root->right)) + 1;
    tempRoot->height = max(height(tempRoot->left), height(tempRoot->right)) + 1;
    return tempRoot;
}

template <class T>
void AVL<T>::insert(T val) {
    size += 1;
    root = insertHelper(root, val);
}

template <class T>
Node<T> *AVL<T>::insertHelper(Node<T> *root, T val) {
    // Empty
    if (root == NULL) {
        Node<T> *temp = new Node<T>(val);
        temp->frequency += 1;
        temp->leftSubtreeCount += 1;
        return temp;
    } else if (val == root->value) {
        root->frequency += 1;
        root->leftSubtreeCount += 1;
        return root;
    }
    // Add to left subtree
    else if (val < root->value) {
        root->leftSubtreeCount += 1;
        root->left = insertHelper(root->left, val);
    }
    // Add to right subtree
    else
        root->right = insertHelper(root->right, val);

    // Updating Height of the node
    root->height = max(height(root->left), height(root->right)) + 1;
    // Finding the balance factor of a node
    int balance = balanceFactor(root);

    // LL case: Perform right rotation
    if (balance > 1 && val < root->left->value) {
        // cout << "LL" << endl;
        return rightRotate(root);
    }
    // LR case:
    if (balance > 1 && val > root->left->value) {
        // cout << "LR" << endl;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR case: Perform left rotation
    if (balance < -1 && val > root->right->value) {
        // cout << "RR" << endl;
        return leftRotate(root);
    }
    // RL case:
    if (balance < -1 && val < root->right->value) {
        // cout << "RL" << endl;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

template <class T>
void AVL<T>::deleteNode(T val) {
    root = deleteHelper(root, val);
}

template <class T>
Node<T> *AVL<T>::deleteHelper(Node<T> *root, T val) {
    // Not found
    if (root == NULL) {
        return root;
    }
    if (val < root->value) {
        root->left = deleteHelper(root->left, val);
        root->leftSubtreeCount -= 1;
    } else if (val > root->value) {
        root->right = deleteHelper(root->right, val);
    }
    // Value found
    else {
        size -= 1;
        if (root->frequency > 1) {
            root->frequency -= 1;
            root->leftSubtreeCount -= 1;
        } else {
            // Leaf node
            if (root->left == NULL && root->right == NULL) {
                root = NULL;
            }
            // Node with one child
            else if (root->left == NULL) {
                root = root->right;
            }
            // Node with one child
            else if (root->right == NULL) {
                root = root->left;
            }
            // Node with two children: Finding the smallest node in the right
            // subtree
            else {
                // TODO: Check leftsubtreecount
                Node<T> *smallest = smallestNode(root->right);
                root->value = smallest->value;
                root->frequency = smallest->frequency;
                root->right = deleteHelper(root->right, smallest->value);
                free(smallest);
            }
        }
    }

    // After deleting, tree empy
    if (root == NULL) return root;

    // Updating height of the root node
    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = balanceFactor(root);
    // LL case: Perform right rotation
    if (balance > 1 && val < root->left->value) {
        cout << "LL" << endl;
        return rightRotate(root);
    }
    // LR case:
    if (balance > 1 && val > root->left->value) {
        cout << "LR" << endl;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR case: Perform left rotation
    if (balance < -1 && val > root->right->value) {
        cout << "RR" << endl;
        return leftRotate(root);
    }
    // RL case:
    if (balance < -1 && val < root->right->value) {
        cout << "RL" << endl;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

template <class T>
Node<T> *AVL<T>::smallestNode(Node<T> *root) {
    Node<T> *smallest = root;
    while (smallest->left != NULL) {
        smallest = smallest->left;
    }
    return smallest;
}

template <class T>
Node<T> *AVL<T>::search(T val) {
    return searchHelper(root, val);
}

template <class T>
Node<T> *AVL<T>::searchHelper(Node<T> *root, T val) {
    if (root == NULL) {
        cout << "Not found" << endl;
        static T defaultValue;
        return new Node<T>(defaultValue);
    }
    if (root->value == val)
        return root;
    else if (val < root->value)
        return searchHelper(root->left, val);
    else
        return searchHelper(root->right, val);
}

template <class T>
int AVL<T>::count(T val) {
    return countHelper(root, val);
}

template <class T>
int AVL<T>::countHelper(Node<T> *root, T val) {
    if (root == NULL) {
        // cout << "Not found" << endl;
        return 0;
    }
    if (root->value == val)
        return root->frequency;
    else if (val < root->value)
        return countHelper(root->left, val);
    else
        return countHelper(root->right, val);
}


template <class T>
void AVL<T>::lowerBound(T val) {
    Node<T> *lb = NULL;
    lowerBoundHelper(root, val, lb);
    if(lb != NULL){
        cout<<lb->value<<endl;
        return ;
    }
    cout<<"NOT FOUND"<<endl;
}

template <class T>
void AVL<T>::lowerBoundHelper(Node<T> *root, T val, Node<T>* &lb) {
    if (root == NULL) return;
    if (root->value > val) {
        lb = root;
        lowerBoundHelper(root->left, val, lb);
    } else if(root->value < val)
        lowerBoundHelper(root->right, val, lb);
    else{
        lb = root;
        lowerBoundHelper(root->left, val, lb);
    }
}

template <class T>
void AVL<T>::upperBound(T val) {
    Node<T> *ub = NULL;
    upperBoundHelper(root, val, ub);
    if(ub != NULL){
        cout<<ub->value<<endl;
        return ;
    }
    cout<<"NOT FOUND"<<endl;
}

template <class T>
void AVL<T>::upperBoundHelper(Node<T> *root, T val, Node<T>* &ub) {
    if (root == NULL) return;
    if (root->value > val) {
        ub = root;
        upperBoundHelper(root->left, val, ub);
    } else if (root->value < val) {
        upperBoundHelper(root->right, val, ub);
    }
    else{
        upperBoundHelper(root->right, val, ub);
    }
}

template <class T>
T AVL<T>::closestValue(T val) {
    // Tree empty
    static T ans;
    if (root == NULL){
        cout<<"NOT found"<<endl;
        return ans;
    }
    // T ans;
    int minAns;
    bool ansFound = false;
    closestValueHelper(root, val, ans, minAns, ansFound);
    return ans;
}

template <class T>
void AVL<T>::closestValueHelper(Node<T> *root, T val, T &ans, int &minAns, bool &ansFound) {
    if (root == NULL) {
        return;
    }

    int temp;

    if (val > root->value)
        temp = val - root->value;
    else
        temp = root->value - val;

    if (!ansFound || temp < minAns) {
        ans = root->value;
        minAns = temp;
        ansFound = true;
    }
    if (val == root->value)
        return;
    else if (val < root->value) {
        closestValueHelper(root->left, val, ans, minAns, ansFound);
    } else {
        closestValueHelper(root->right, val, ans, minAns, ansFound);
    }
}

template <class T>
T AVL<T>::KthLargest(int k) {
    if (k > size) {
        cout << "No Kth largest" << endl;
        static T defaultValue;
        return defaultValue;
    }
    int leftElements = 0;
    int treeSize = size;
    Node<T> *KthLargestNode = NULL;
    KthLargestHelper(root, k, treeSize, leftElements, KthLargestNode);
    if(KthLargestNode == NULL){
        cout << "No Kth Largest"<<endl;
        static T defaultValue;
        return defaultValue;
    }
    return KthLargestNode->value;
}

template <class T>
void AVL<T>::KthLargestHelper(Node<T> *root, int k, int &treeSize, int &leftElements, Node<T>* &KthLargestNode) {
    if(root == NULL)
        return ;

    int rightSubtreeCount = treeSize - root->leftSubtreeCount - leftElements;
    if (rightSubtreeCount + 1 == k) {
        KthLargestNode = root;
        return ;
    }
    // There are K elements in the right subtree then 1 to Kth largest elements
    // will be in right subtree only
    if (rightSubtreeCount >= k) {
        leftElements += root->leftSubtreeCount;
        KthLargestHelper(root->right, k, treeSize, leftElements, KthLargestNode);
    } else {
        treeSize = treeSize - rightSubtreeCount - root->frequency;
        k = k- rightSubtreeCount - 1;
        KthLargestHelper(root->left, k, treeSize, leftElements, KthLargestNode);
    }
}

template <class T>
int AVL<T>::range(T a, T b) {
    int leftIntervalCount = 0;
    int rightIntervalCount = 0;
    leftInterval(root, a, leftIntervalCount);
    rightInterval(root, b, rightIntervalCount);
    return rightIntervalCount - leftIntervalCount;
}

template <class T>
void AVL<T>::leftInterval(Node<T> *root, T val, int &leftIntervalCount) {
    if (root == NULL) return;
    if (root->value == val) {
        // ans = root->value;
        leftIntervalCount += (root->leftSubtreeCount - root->frequency);
    } else if (val < root->value) {
        if (root->left == NULL)
            leftIntervalCount += root->leftSubtreeCount - root->frequency;
        else
            leftInterval(root->left, val, leftIntervalCount);
    } else {
        leftIntervalCount += root->leftSubtreeCount;
        leftInterval(root->right, val, leftIntervalCount);
    }
}

template <class T>
void AVL<T>::rightInterval(Node<T> *root, T val, int &rightIntervalCount) {
    if (root == NULL) 
        return;
    if (root->value == val) {
        // ans = root->value;
        rightIntervalCount += (root->leftSubtreeCount);
    }
    else if (val < root->value) {
        if (root->left == NULL)
            return;
        else
            rightInterval(root->left, val, rightIntervalCount);
    } 
    else {
        rightIntervalCount += root->leftSubtreeCount;
        rightInterval(root->right, val, rightIntervalCount);
    }
}

// ============================================== Driver Code: main()
// ===============================================================================

int main() {
    AVL<int> tree;
    int option;
    int k;
    int val, a, b;
    cout << "================================================================" << endl;
    cout << "Available options:" << endl;
    cout << "1.Insert" << endl;
    cout << "2.Delete" << endl;
    cout << "3.Search" << endl;
    cout << "4.Count" << endl;
    cout << "5.Lower bound" << endl;
    cout << "6.Upper bound" << endl;
    cout << "7.Closest element" << endl;
    cout << "8.Kth largest" << endl;
    cout << "9.Range" << endl;
    cout << "10.Inorder traversal" << endl;
    cout << "================================================================" << endl; 
    while (true) {
        // cout << "Enter option: ";
        cin >> option;
        if (option == 1) {
            cin >> val;
            tree.insert(val);
        } else if (option == 2) {
            cin >> val;
            tree.deleteNode(val);
        } else if (option == 3) {
            cin >> val;
            cout << tree.search(val)->value << endl;
        } else if (option == 4) {
            cin >> val;
            cout << "Count: " << tree.count(val) << endl;
        } else if (option == 5) {
            cin >> val;
            cout << "LowerBound: ";
            tree.lowerBound(val);
        } else if (option == 6) {
            cin >> val;
            cout << "UpperBound: ";
            tree.upperBound(val);
        } else if (option == 7) {
            cin >> val;
            cout << "Closest value: " << tree.closestValue(val);
        } else if (option == 8) {
            cin >> k;
            // cout<<"KTH largest"<<endl;
            cout << tree.KthLargest(k) << endl;
        } else if (option == 9) {
            cin >> a >> b;
            cout << "Range: " << tree.range(a, b) << endl;
        } else if (option == 10) {
            tree.inorderTraversal(tree.root);
            cout << endl;
        } else
            break;
        cout << endl;
    }
    return 0;
}

// =========================================== Driver Code: comparator =================================================

// int main() {
//     // AVL<Rectangle> tree;
//     // Rectangle val;
//     // int l,b;
//     AVL<Square> tree;
//     Square val;
//     int s;
//     int option;
//     int k;
//     cout << "================================================================" << endl;
//     cout << "Available options:" << endl;
//     cout << "1.Insert" << endl;
//     cout << "2.Delete" << endl;
//     cout << "3.Search" << endl;
//     cout << "4.Count" << endl;
//     cout << "5.Lower bound" << endl;
//     cout << "6.Upper bound" << endl;
//     cout << "7.Closest element" << endl;
//     cout << "8.Kth largest" << endl;
//     cout << "9.Range" << endl;
//     cout << "10.Inorder traversal" << endl;
//     cout << "================================================================" << endl;
//     while (true) {
//         // cout << "Enter option: ";
//         cin >> option;
//         if (option == 1) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             tree.insert(val);
//         } else if (option == 2) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             tree.deleteNode(val);
//         } else if (option == 3) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             // Rectangle ans = tree.search(val)->value;
//             // cout << ans.l<<" "<<ans.b << endl;
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             Square ans = tree.search(val)->value;
//             cout<<ans.s<<endl;
//         } else if (option == 4) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             cout << "Count: " << tree.count(val) << endl;
//         } else if (option == 5) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             // Rectangle ans = tree.lowerBound(val);
//             // cout << "LowerBound: " << ans.l<<" "<<ans.b << endl;
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             tree.lowerBound(val);
//         } else if (option == 6) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             // Rectangle ans = tree.upperBound(val);
//             // cout << "UpperBound: " << ans.l<<" "<<ans.b << endl;
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             tree.upperBound(val);
//         } else if (option == 7) {
//             // cout<<"Enter l,b: "; cin >>l>>b;
//             // Rectangle val(l,b);
//             // Rectangle ans = tree.closestValue(val);
//             // cout << "Closest value: " << ans.l<<" "<<ans.b << endl;
//             cout<<"Enter s:"; cin>>s;
//             Square val(s);
//             Square ans = tree.closestValue(val);
//             cout<<ans.s<<endl;
//         } else if (option == 8) {
//             // cin >> k;
//             // Rectangle ans = tree.KthLargest(k);
//             // cout << "Kth largest: " << ans.b<<" "<<ans.b << endl;
//             Square ans = tree.KthLargest(k);
//             cout<<ans.s<<endl;
//         } else if (option == 9) {
//             // cin>>l>>b;
//             // int l2,b2; 
//             // cin>>l2>>b2;
//             // Rectangle left(l,b);
//             // Rectangle right(l2,b2);
//             int s1;
//             cin>>s>>s1;
//             Square left(s);
//             Square right(s1);
//             cout << "Range: " << tree.range(left, right) << endl;
//         } else if (option == 10) {
//             tree.inorderTraversal(tree.root);
//             cout << endl;
//         } else
//             break;
//         cout << endl;
//     }
//     return 0;
// }
