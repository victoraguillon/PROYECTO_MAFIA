#ifndef MAFIA_TREE_H
#define MAFIA_TREE_H
#include <string> 
// ESTRUCTURAS DE DATOS

struct TreeNode {
    int id;
    std::string name;
    std::string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;

    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode();

}; 

struct ListNode {
    TreeNode* tree_node;
    ListNode* next;

    ListNode(TreeNode* node);
};


class CustomList {
    public:
        ListNode* head;
        CustomList();
        ~CustomList();
    void push_back(TreeNode* node);
};

// CLASE DEL ARBOL DE LA MAFIA

class MafiaTree{
    private: TreeNode* root;
     TreeNode* search_node (TreeNode* current, int id);
     TreeNode* find_valid_candidate_in_subtree(TreeNode* current, bool allow_jailed);
     TreeNode* get_next_boss (TreeNode* dead_boss, bool allow_jailed);
     void print_alive_lineage (TreeNode* node, int level);
        TreeNode* find_boss_recursive (TreeNode* node);

    public:
     MafiaTree();
     void load_from_csv (std::string filename);
     void show_alive_succession ();
     TreeNode* get_current_boss();
     void check_and_update_boss();
     void edit_node_data (int id);
};

#endif // MAFIA_TREE_H