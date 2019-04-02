// global includes    //////////////////////////////
#include "Global.h"

#include "DataStructureTests.h"
#include "BinarySearchTree.h"
#include <vector>
#include <string>

namespace DS {

    constexpr int64_t BST_ROOT                = 100;
    constexpr int64_t BST_LEFT                = 50;
    constexpr int64_t BST_RIGHT                = 150;
    constexpr int64_t BST_LEFT_LEFT            = 25;
    constexpr int64_t BST_LEFT_RIGHT        = 75;
    constexpr int64_t BST_RIGHT_LEFT        = 125;
    constexpr int64_t BST_RIGHT_RIGHT        = 175;

    void createBasicTree(BinarySearchTree<GenericTestObject>& tree) {
        auto *root = tree.insertPreOrder(tree.root(), GenericTestObject(BST_ROOT));
        tree.insertPreOrder(tree.root(), GenericTestObject(BST_LEFT));
        tree.insertPreOrder(tree.root(), GenericTestObject(BST_LEFT_LEFT));
        tree.insertPreOrder(tree.root(), GenericTestObject(BST_LEFT_RIGHT));
        tree.insertPreOrder(tree.root(), GenericTestObject(BST_RIGHT));
        tree.insertPreOrder(tree.root(), GenericTestObject(BST_RIGHT_LEFT));
        tree.insertPreOrder(tree.root(), GenericTestObject(BST_RIGHT_RIGHT));
        tree.print();
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
        BinarySearchTree<GenericTestObject> tree;
        createBasicTree(tree);
        const auto *root = tree.root();
        X_ASSERT_IF_FALSE(root->data()->val == BST_ROOT);
        X_ASSERT_IF_FALSE(root->left()->data()->val == BST_LEFT);
        X_ASSERT_IF_FALSE(root->left()->left()->data()->val == BST_LEFT_LEFT);
        X_ASSERT_IF_FALSE(root->left()->right()->data()->val == BST_LEFT_RIGHT);
        X_ASSERT_IF_FALSE(root->right()->data()->val == BST_RIGHT);
        X_ASSERT_IF_FALSE(root->right()->left()->data()->val == BST_RIGHT_LEFT);
        X_ASSERT_IF_FALSE(root->right()->right()->data()->val == BST_RIGHT_RIGHT);
        tree.print();

        // test copy
        BinarySearchTree<GenericTestObject> tree2(tree);
        root = tree2.root();
        X_ASSERT_IF_FALSE(root->data()->val == BST_ROOT);
        X_ASSERT_IF_FALSE(root->left()->data()->val == BST_LEFT);
        X_ASSERT_IF_FALSE(root->left()->left()->data()->val == BST_LEFT_LEFT);
        X_ASSERT_IF_FALSE(root->left()->right()->data()->val == BST_LEFT_RIGHT);
        X_ASSERT_IF_FALSE(root->right()->data()->val == BST_RIGHT);
        X_ASSERT_IF_FALSE(root->right()->left()->data()->val == BST_RIGHT_LEFT);
        X_ASSERT_IF_FALSE(root->right()->right()->data()->val == BST_RIGHT_RIGHT);
        tree2.print();

        // test assignment
        BinarySearchTree<GenericTestObject> tree3;
        tree3 = tree;
        root = tree3.root();
        X_ASSERT_IF_FALSE(root->data()->val == BST_ROOT);
        X_ASSERT_IF_FALSE(root->left()->data()->val == BST_LEFT);
        X_ASSERT_IF_FALSE(root->left()->left()->data()->val == BST_LEFT_LEFT);
        X_ASSERT_IF_FALSE(root->left()->right()->data()->val == BST_LEFT_RIGHT);
        X_ASSERT_IF_FALSE(root->right()->data()->val == BST_RIGHT);
        X_ASSERT_IF_FALSE(root->right()->left()->data()->val == BST_RIGHT_LEFT);
        X_ASSERT_IF_FALSE(root->right()->right()->data()->val == BST_RIGHT_RIGHT);
        tree3.print();
    }

    void testTraversal() {
        BinarySearchTree<GenericTestObject> tree;
        createBasicTree(tree);

        // test height
        auto height = tree.height(tree.root());
        X_ASSERT_IF_FALSE(height == 3);

#ifdef DS_DEBUG_LOG
        std::string preorder;
        std::string preorder_expected =
            std::to_string(BST_ROOT).append(" ")
            .append(std::to_string(BST_LEFT)).append(" ")
            .append(std::to_string(BST_LEFT_LEFT)).append(" ")
            .append(std::to_string(BST_LEFT_RIGHT)).append(" ")
            .append(std::to_string(BST_RIGHT)).append(" ")
            .append(std::to_string(BST_RIGHT_LEFT)).append(" ")
            .append(std::to_string(BST_RIGHT_RIGHT)).append(" ");

        std::string postorder;
        std::string postorder_expected =
            std::to_string(BST_LEFT_LEFT).append(" ")
            .append(std::to_string(BST_LEFT_RIGHT)).append(" ")
            .append(std::to_string(BST_LEFT)).append(" ")
            .append(std::to_string(BST_RIGHT_LEFT)).append(" ")
            .append(std::to_string(BST_RIGHT_RIGHT)).append(" ")
            .append(std::to_string(BST_RIGHT)).append(" ")
            .append(std::to_string(BST_ROOT)).append(" ");

        std::string inorder;
        std::string inorder_expected =
            std::to_string(BST_LEFT_LEFT).append(" ")
            .append(std::to_string(BST_LEFT)).append(" ")
            .append(std::to_string(BST_LEFT_RIGHT)).append(" ")
            .append(std::to_string(BST_ROOT)).append(" ")
            .append(std::to_string(BST_RIGHT_LEFT)).append(" ")
            .append(std::to_string(BST_RIGHT)).append(" ")
            .append(std::to_string(BST_RIGHT_RIGHT)).append(" ");

        std::string levelorder1;
        std::string level1_expected =
            std::to_string(BST_ROOT).append(" ");

        std::string levelorder2;
        std::string level2_expected =
            std::to_string(BST_LEFT).append(" ")
            .append(std::to_string(BST_RIGHT)).append(" ");

        std::string levelorder3;
        std::string level3_expected =
            std::to_string(BST_LEFT_LEFT).append(" ")
            .append(std::to_string(BST_LEFT_RIGHT)).append(" ")
            .append(std::to_string(BST_RIGHT_LEFT)).append(" ")
            .append(std::to_string(BST_RIGHT_RIGHT)).append(" ");

        tree.printNodePreorder(tree.root(), preorder);
        X_ASSERT_IF_FALSE(preorder.compare(preorder_expected) == 0);
        tree.printNodePostorder(tree.root(), postorder);
        X_ASSERT_IF_FALSE(postorder.compare(postorder_expected) == 0);
        tree.printNodeInorder(tree.root(), inorder);
        X_ASSERT_IF_FALSE(inorder.compare(inorder_expected) == 0);
        tree.printNodeLevelorder(tree.root(), 0, levelorder1);
        X_ASSERT_IF_FALSE(levelorder1.compare(level1_expected) == 0);
        tree.printNodeLevelorder(tree.root(), 1, levelorder2);
        X_ASSERT_IF_FALSE(levelorder2.compare(level2_expected) == 0);
        tree.printNodeLevelorder(tree.root(), 2, levelorder3);
        X_ASSERT_IF_FALSE(levelorder3.compare(level3_expected) == 0);
#endif // DS_DEBUG_LOG

        // test search
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), *tree.root()->data())->data() == tree.root()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), *tree.root()->left()->data())->data() == tree.root()->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), *tree.root()->right()->data())->data() == tree.root()->right()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), *tree.root()->left()->left()->data())->data() == tree.root()->left()->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), *tree.root()->left()->right()->data())->data() == tree.root()->left()->right()->data());
        GenericTestObject testobj(-10);
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), *tree.root()->right()->data())->data() != &testobj);

        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_ROOT))->data() == tree.root()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_LEFT))->data() == tree.root()->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_RIGHT))->data() == tree.root()->right()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_LEFT_LEFT))->data() == tree.root()->left()->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_LEFT_RIGHT))->data() == tree.root()->left()->right()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_RIGHT_LEFT))->data() == tree.root()->right()->left()->data());
        X_ASSERT_IF_FALSE(tree.searchPreorder(tree.root(), GenericTestObject(BST_RIGHT_RIGHT))->data() == tree.root()->right()->right()->data());

#ifdef DS_DEBUG_LOG
        {
            tree.print();
            // test delete
            std::string inorder;
            // delete leftmost leaf (25) (no children)
            tree.deletePreorder(tree.root(), GenericTestObject(BST_LEFT_LEFT));
            tree.print();
            std::string inorder_expected = std::to_string(BST_LEFT).append(" ").append(std::to_string(BST_LEFT_RIGHT)).append(" ").append(std::to_string(BST_ROOT)).append(" ")
                .append(std::to_string(BST_RIGHT_LEFT)).append(" ").append(std::to_string(BST_RIGHT)).append(" ").append(std::to_string(BST_RIGHT_RIGHT)).append(" ");
            tree.printNodeInorder(tree.root(), inorder);
            X_ASSERT_IF_FALSE(inorder.compare(inorder_expected) == 0);
            // delete left leaf (50) (one right child)
            tree.deletePreorder(tree.root(), GenericTestObject(BST_LEFT));
            inorder_expected = std::to_string(BST_LEFT_RIGHT).append(" ").append(std::to_string(BST_ROOT)).append(" ")
                .append(std::to_string(BST_RIGHT_LEFT)).append(" ").append(std::to_string(BST_RIGHT)).append(" ").append(std::to_string(BST_RIGHT_RIGHT)).append(" ");
            inorder.clear();
            tree.print();
            tree.printNodeInorder(tree.root(), inorder);
            X_ASSERT_IF_FALSE(inorder.compare(inorder_expected) == 0);
            // add a leftmost right
            tree.insertPreOrder(tree.root(), BST_LEFT_LEFT);
            tree.print();
            // delete left leaf (75) (one left child)
            tree.deletePreorder(tree.root(), GenericTestObject(BST_LEFT_RIGHT));
            inorder_expected = std::to_string(BST_LEFT_LEFT).append(" ").append(std::to_string(BST_ROOT)).append(" ")
                .append(std::to_string(BST_RIGHT_LEFT)).append(" ").append(std::to_string(BST_RIGHT)).append(" ").append(std::to_string(BST_RIGHT_RIGHT)).append(" ");
            inorder.clear();
            tree.print();
            tree.printNodeInorder(tree.root(), inorder);
            X_ASSERT_IF_FALSE(inorder.compare(inorder_expected) == 0);
            // delete root leaf (100) (two children)
            tree.deletePreorder(tree.root(), GenericTestObject(BST_ROOT));
            inorder_expected = std::to_string(BST_LEFT_LEFT).append(" ")
                .append(std::to_string(BST_RIGHT_LEFT)).append(" ").append(std::to_string(BST_RIGHT)).append(" ").append(std::to_string(BST_RIGHT_RIGHT)).append(" ");
            inorder.clear();
            tree.print();
            tree.printNodeInorder(tree.root(), inorder);
            X_ASSERT_IF_FALSE(inorder.compare(inorder_expected) == 0);

            // delete the remaining leaves
            while (tree.root() != nullptr) {
                tree.deletePreorder(tree.root(), *(tree.root()->data()));
                tree.print();
            }
            inorder.clear();
            tree.printNodeInorder(tree.root(), inorder);
            X_ASSERT_IF_FALSE(inorder.compare("") == 0);
        }
#endif // DS_DEBUG_LOG

#ifdef DS_DEBUG_LOG
        // validate
        createBasicTree(tree);
        auto *root = tree.root();
        inorder.clear();
        tree.print();
        tree.printNodeInorder(tree.root(), inorder);
        inorder_expected =
            std::to_string(BST_LEFT_LEFT).append(" ")
            .append(std::to_string(BST_LEFT)).append(" ")
            .append(std::to_string(BST_LEFT_RIGHT)).append(" ")
            .append(std::to_string(BST_ROOT)).append(" ")
            .append(std::to_string(BST_RIGHT_LEFT)).append(" ")
            .append(std::to_string(BST_RIGHT)).append(" ")
            .append(std::to_string(BST_RIGHT_RIGHT)).append(" ");
        X_ASSERT_IF_FALSE(inorder.compare(inorder_expected) == 0);
#endif
    }

    namespace TESTS {
        void testBinarySearchTrees() {
            X_DEBUG_COMMENT("Started %s", __func__);
            testTreeBase<BinarySearchTree<GenericTestObject>>();
            testBasicTree();
            testTraversal();
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }
}

int main() {
    DS::TESTS::testBinarySearchTrees();
    return 0;
}


