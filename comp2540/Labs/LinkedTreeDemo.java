
/**
 * Developer: Dennis Dao
 * Date: Mar 14, 2021
 * version 1.0
 */

// This tests the LinkedTree implementation with insert, search, and successor
public class LinkedTreeDemo {
    class Node{
        // Instance variables
        int data, xCoord, yCoord;
        Node left, right, parent;

        /**
         * Default constructor
         * @param data Data in the node of the tree
         */
        public Node(int data){
            this.data = data;
            left = right = parent = null;
        }
    }
    public static void main(String args[]) throws Exception{
        LinkedTree myLinkedTree = new LinkedTree();

        // Insert
        myLinkedTree.insert(myLinkedTree.getRoot(), 16);
        myLinkedTree.insert(myLinkedTree.getRoot(), 5);
        myLinkedTree.insert(myLinkedTree.getRoot(), 18);
        myLinkedTree.insert(myLinkedTree.getRoot(), 2);
        myLinkedTree.insert(myLinkedTree.getRoot(), 15);
        myLinkedTree.insert(myLinkedTree.getRoot(), 17);
        myLinkedTree.insert(myLinkedTree.getRoot(), 19);
        myLinkedTree.insert(myLinkedTree.getRoot(), 1);
        myLinkedTree.insert(myLinkedTree.getRoot(), 3);
        myLinkedTree.insert(myLinkedTree.getRoot(), 13);
        myLinkedTree.insert(myLinkedTree.getRoot(), 12);
        myLinkedTree.insert(myLinkedTree.getRoot(), 14);

        /**
         * Expected tree:
         *                  ------- 16 ------
         *                 /                 \
         *                5                  18 
         *             /     \             /     \
         *           2        15          17      19
         *         /   \     /   
         *        1     3   13
         *                 /  \
         *                12   14
         */
        
        System.out.println("Inorder traversal of tree: ");
        System.out.println(myLinkedTree.inorder(myLinkedTree.getRoot()));

        // TreeSearch test
        for(int i = 1; i <= 20; i++){
            if(myLinkedTree.treeSearch(myLinkedTree.getRoot(), i) == null){
                System.out.println("False. " + i + " is NOT in the tree");
            }
            else{
                System.out.println("True. " + i + " is in the tree");
                if(myLinkedTree.treeSearch(myLinkedTree.getRoot(), i).parent == null){
                    System.out.println("This is the root of the tree");
                }
                else{
                    System.out.println("Their parent is " + (myLinkedTree.treeSearch(myLinkedTree.getRoot(), i).parent.data));
                }
            }
        }
        System.out.println();

        // Successor test
        for(int i = 1; i <= 20; i++){
            if(myLinkedTree.treeSearch(myLinkedTree.getRoot(),i) == null){
                continue;
            }
            else{
                if(myLinkedTree.successor(myLinkedTree.treeSearch(myLinkedTree.getRoot(),i)) == null){
                    continue;
                }
                System.out.println("The successor of " + i + " is " + myLinkedTree.successor(myLinkedTree.treeSearch(myLinkedTree.getRoot(),i)).data);
            }
        }
    }
}
