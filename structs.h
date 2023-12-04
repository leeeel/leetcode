struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    explicit ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    explicit Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    explicit Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    explicit Node(int _val, Node *_left, Node *_right, Node *_next) : val(_val), left(_left), right(_right), next(_next) {}
};

struct GraphNode {
public:
    int val;
    std::vector<GraphNode *> neighbors;

    explicit GraphNode() {
        val = 0;
        neighbors = std::vector<GraphNode *>();
    }

    explicit GraphNode(int _val) {
        val = _val;
        neighbors = std::vector<GraphNode *>();
    }

    explicit GraphNode(int _val, std::vector<GraphNode *> _neighbors) {
        val = _val;
        neighbors = std::move(_neighbors);
    }
};