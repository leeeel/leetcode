struct ListNode {
    [[maybe_unused]] int val;
    [[maybe_unused]] ListNode *next;

    [[maybe_unused]] explicit ListNode() : val(0), next(nullptr) {}

    [[maybe_unused]] explicit ListNode(int x) : val(x), next(nullptr) {}

    [[maybe_unused]] explicit ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    [[maybe_unused]] int val;
    [[maybe_unused]] TreeNode *left;
    [[maybe_unused]] TreeNode *right;

    [[maybe_unused]] explicit TreeNode() : val(0), left(nullptr), right(nullptr) {}

    [[maybe_unused]] explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    [[maybe_unused]] explicit TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Node {
public:
    [[maybe_unused]] int val;
    [[maybe_unused]] Node *left;
    [[maybe_unused]] Node *right;
    [[maybe_unused]] Node *next;

    [[maybe_unused]] explicit Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    [[maybe_unused]] explicit Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    [[maybe_unused]] explicit Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

struct GraphNode {
public:
    [[maybe_unused]] int val;
    [[maybe_unused]] std::vector<GraphNode *> neighbors;

    [[maybe_unused]] explicit GraphNode() {
        val = 0;
        neighbors = std::vector<GraphNode *>();
    }

    [[maybe_unused]] explicit GraphNode(int _val) {
        val = _val;
        neighbors = std::vector<GraphNode *>();
    }

    [[maybe_unused]] explicit GraphNode(int _val, std::vector<GraphNode *> _neighbors) {
        val = _val;
        neighbors = std::move(_neighbors);
    }
};