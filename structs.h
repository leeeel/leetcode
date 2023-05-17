struct ListNode {
    [[maybe_unused]] int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    [[maybe_unused]] explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Node {
public:
    [[maybe_unused]] int val;
    Node *left;
    Node *right;
    [[maybe_unused]] Node *next;

    explicit Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    explicit Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    explicit Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};