/**
 * Developer: Dennis Dao
 * Date: Mar 10, 2021
 * version 1.0
 */

// This tests the preorder, inorder, and postorder methods
public class TreeDemo {

    public static void main(String args[]){
        /**
         * Expected tree:
         *                        ------------- 0 --------------
         *                       /                              \
         *               ------ 1 -------                 ------ 2 -----
         *              /                \               /               \
         *           - 3 -                4              5                6 
         *          /     \              /
         *         7       8            9
         */
        int[] tree = {0,1,2,3,4,5,6,7,8,9};
        Tree myTree = new Tree(tree);

        System.out.println("Preorder traversal:");
        System.out.println(myTree.preorder(0));
        myTree.clearTraversal();
        System.out.println("\nPostorder traversal:");
        System.out.println(myTree.postorder(0));
        myTree.clearTraversal();
        System.out.println("\nInorder traversal:");
        System.out.println(myTree.inorder(0));
        myTree.clearTraversal();
    }
}
