/*This is a function problem.You only need to complete the function given below*/
/*Complete the function below
Node is as follows
struct Node{
	int data;
	Node *left, *right;
};
*/

const int INF = 1000;

int maxDown(struct Node *root, int &answer){
    if(root == NULL) return 0;
    int l = maxDown(root->left, answer);
    int r = maxDown(root->right, answer);
    if(root->left != NULL and root->right != NULL)
        answer = max(answer, l + r + root->data);
    return max(l, r) + root->data;
}

int maxPathSum(struct Node *root){
    int answer = -INF;
    maxDown(root, answer);
    return answer;
}
