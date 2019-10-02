/*This is a function problem.You only need to complete the function given below*/
/* A binary tree node has data, pointer to left child
   and a pointer to right child  
struct Node {
    int data;
    Node* right;
    Node* left;
    
    Node(int x){
        data = x;
        right = NULL;
        left = NULL;
    }
}; */
bool isBST(Node* root, int low, int high){
    if(root == NULL) return true;
    if(root->data < low) return false;
    if(root->data > high) return false;
    return isBST(root->right, root->data, high) and isBST(root->left, low, root->data);
}

const int INF  = 1001;
bool isBST(Node* root) {
    return isBST(root, -INF, INF);
}
