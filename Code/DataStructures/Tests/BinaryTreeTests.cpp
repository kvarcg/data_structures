// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "BinaryTree.h"
#include <vector>
#include <string>

namespace DS {

    void createBasicTree(BinaryTree<GenericTestObject>& tree) {
        auto *root = tree.addLeft(nullptr, GenericTestObject(0));
        auto* rleft = tree.addLeft(root, GenericTestObject(1));
        tree.addLeft(rleft, GenericTestObject(2));
        tree.addRight(rleft, GenericTestObject(3));
        auto* rright = tree.addRight(root, GenericTestObject(4));
        tree.addLeft(rright, GenericTestObject(5));
        tree.addRight(rright, GenericTestObject(6));
    }

    template <typename T>
    void testTreeBase() {
        X_ASSERT_IF_FALSE(std::is_default_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_constructible<T>() == true);
        X_ASSERT_IF_FALSE(std::is_copy_assignable<T>() == true);
        //X_ASSERT_IF_FALSE(std::is_move_constructible<T>() == false);
        //X_ASSERT_IF_FALSE(std::is_move_assignable<T>() == false);
    }

    void testBasicTree() {
        BinaryTree<GenericTestObject> tree;
        createBasicTree(tree);
        const auto *root = tree.root();
        X_ASSERT_IF_FALSE(root->data()->val == 0);
        X_ASSERT_IF_FALSE(root->left()->data()->val == 1);
        X_ASSERT_IF_FALSE(root->left()->left()->data()->val == 2);
        X_ASSERT_IF_FALSE(root->left()->right()->data()->val == 3);
        X_ASSERT_IF_FALSE(root->right()->data()->val == 4);
        X_ASSERT_IF_FALSE(root->right()->left()->data()->val == 5);
        X_ASSERT_IF_FALSE(root->right()->right()->data()->val == 6);
        tree.print();

        // test copy
        BinaryTree<GenericTestObject> tree2(tree);
        root = tree2.root();
        X_ASSERT_IF_FALSE(root->data()->val == 0);
        X_ASSERT_IF_FALSE(root->left()->data()->val == 1);
        X_ASSERT_IF_FALSE(root->left()->left()->data()->val == 2);
        X_ASSERT_IF_FALSE(root->left()->right()->data()->val == 3);
        X_ASSERT_IF_FALSE(root->right()->data()->val == 4);
        X_ASSERT_IF_FALSE(root->right()->left()->data()->val == 5);
        X_ASSERT_IF_FALSE(root->right()->right()->data()->val == 6);
        tree2.print();

        // test assignment
        BinaryTree<GenericTestObject> tree3;
        tree3 = tree;
        root = tree3.root();
        X_ASSERT_IF_FALSE(root->data()->val == 0);
        X_ASSERT_IF_FALSE(root->left()->data()->val == 1);
        X_ASSERT_IF_FALSE(root->left()->left()->data()->val == 2);
        X_ASSERT_IF_FALSE(root->left()->right()->data()->val == 3);
        X_ASSERT_IF_FALSE(root->right()->data()->val == 4);
        X_ASSERT_IF_FALSE(root->right()->left()->data()->val == 5);
        X_ASSERT_IF_FALSE(root->right()->right()->data()->val == 6);
        tree3.print();
    }

    void testTraversal() {
        BinaryTree<GenericTestObject> tree;
        createBasicTree(tree);
        auto *root = tree.root();
        root->data()->val = 1;
        root->left()->data()->val = 2;
        root->right()->data()->val = 3;
        root->left()->left()->data()->val = 4;
        root->left()->right()->data()->val = 5;
        root->right()->left()->data()->val = 6;
        root->right()->right()->data()->val = 7;

        // test height
        auto height = tree.height(tree.root());
        X_ASSERT_IF_FALSE(height == 3);

#ifdef DS_DEBUG_LOG
        std::string preorder;
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 2 4 5 3 6 7 ") == 0);
        std::string postorder;
        tree.printNodePostorder(tree.root(), postorder);
        X_ASSERT_IF_FALSE(postorder.compare("4 5 2 6 7 3 1 ") == 0);
        std::string inorder;
        tree.printNodeInorder(tree.root(), inorder);
        X_ASSERT_IF_FALSE(inorder.compare("4 2 5 1 6 3 7 ") == 0);
        std::string levelorder1;
        tree.printNodeLevelorder(tree.root(), 0, levelorder1);
        X_ASSERT_IF_FALSE(levelorder1.compare("1 ") == 0);
        std::string levelorder2;
        tree.printNodeLevelorder(tree.root(), 1, levelorder2);
        X_ASSERT_IF_FALSE(levelorder2.compare("2 3 ") == 0);
        std::string levelorder3;
        tree.printNodeLevelorder(tree.root(), 2, levelorder3);
        X_ASSERT_IF_FALSE(levelorder3.compare("4 5 6 7 ") == 0);
#endif // DS_DEBUG_LOG

        // test search
        X_ASSERT_IF_FALSE(tree.searchPreorder(root, *root->data())->data() == root->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(root, *root->left()->data())->data() == root->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(root, *root->right()->data())->data() == root->right()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(root, *root->left()->left()->data())->data() == root->left()->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(root, *root->left()->right()->data())->data() == root->left()->right()->data());
        GenericTestObject testobj(-10);
        X_ASSERT_IF_FALSE(tree.searchPreorder(root, *root->right()->data())->data() != &testobj);

        tree.print();
        // test delete
         // delete leftmost leaf (4)
        tree.deletePreorder(tree.root(), *tree.root()->left()->left()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 2 5 3 6 7 ") == 0);
        // delete right node (3)
        tree.deletePreorder(tree.root(), *tree.root()->right()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 2 5 6 7 ") == 0);
        // delete right node (now 6)
        tree.deletePreorder(tree.root(), *tree.root()->right()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 2 5 7 ") == 0);
        // delete one leaf (5)
        tree.deletePreorder(tree.root(), *tree.root()->left()->right()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 2 7 ") == 0);

        // delete leftmost leaf (now 7)
        tree.deletePreorder(tree.root(), *tree.root()->left()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 7 ") == 0);

        // delete root leaf (1)
        tree.deletePreorder(tree.root(), *tree.root()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("7 ") == 0);

        // delete last leaf (7)
        tree.deletePreorder(tree.root(), *tree.root()->data());
        tree.print();
        preorder.clear();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("") == 0);

#ifdef DS_DEBUG_LOG
        // validate
        createBasicTree(tree);
        root = tree.root();
        root->data()->val = 1;
        root->left()->data()->val = 2;
        root->right()->data()->val = 3;
        root->left()->left()->data()->val = 4;
        root->left()->right()->data()->val = 5;
        root->right()->left()->data()->val = 6;
        root->right()->right()->data()->val = 7;
        preorder.clear();
        tree.print();
        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare("1 2 4 5 3 6 7 ") == 0);
#endif
    }

    namespace TESTS {
        void testBinaryTrees() {
            X_DEBUG_COMMENT("Started %s", __func__);
            testTreeBase<BinaryTree<GenericTestObject>>();
            testBasicTree();
            testTraversal();
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testBinaryTrees();
    return 0;
}


