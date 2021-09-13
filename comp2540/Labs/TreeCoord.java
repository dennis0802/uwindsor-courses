/**
 * Developer: Dennis Dao
 * Date: Mar 10, 2021
 * version 1.0
 */

// This implements a coordinate system for a binary tree
// Uses the LinkedTree (Part D) structure, implemntation details for coordinate setup is in the implementation file
public class TreeCoord {
    public static void main(String args[]){
        /**
         * Expected tree:
         *                        --------------- 0 --------------
         *                       /                                \
         *               ------ 1 -------                    ------ 2 -----
         *              /               \                  /               \
         *        ---- 3 -          --- 4 --             - 5 -            -- 6 --
         *       /        \        /        \         /      \           /       \
         *      7         8       9          10     11        12        13       14
         *     /
         *    15
         */
        int[] tree = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        LinkedTree myTree = new LinkedTree(tree);

        // Go through the tree inorder, setting up coordinate values
        System.out.println("The tree traversed inorder is: " + myTree.inorder(myTree.getRoot()));
        System.out.println("Binary tree where node v has an x and y coordinate");
        System.out.println("x(v) is the number of nodes trabelled before reaching node v");
        System.out.println("y(v) is the depth of node v\n");
        myTree.inorderSet(myTree.getRoot());

        System.out.println(myTree.getCoordinates(myTree.getRoot()));
    }
}
