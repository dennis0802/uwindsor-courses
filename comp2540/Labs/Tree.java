/**
 * Developer: Dennis Dao
 * Date: Mar 10, 2021
 * version 1.0
 */

 // This implements the Tree data structure

 public class Tree{
     // Instance variables
     private int[] tree;
     private String traversal = "";

    public Tree(int[] tree){
        this.tree = tree;
        this.traversal = "";
    }

    /**
     * Traverse the tree in preorder
     * @param nodeNum Starting node, the root
     * @return The traversal as a string
     */
    public String preorder(int nodeNum){
        traversal += Integer.toString(nodeNum) + ", ";
        if(2*nodeNum+1 <= tree.length-1){
            preorder(2*nodeNum+1);
        }

        if(2*nodeNum+2 < tree.length-1){
            preorder(2*nodeNum+2);
        }
        return traversal;
    }

    /**
     * Traverse the tree in postorder
     * @param Starting node, the root
     * @return The traversal as a string
     */
    public String postorder(int nodeNum){
        if(2*nodeNum+1 <= tree.length-1){
            postorder(2*nodeNum+1);
        }
        if(2*nodeNum+2 < tree.length-1){
            postorder(2*nodeNum+2);
        }
        traversal += Integer.toString(nodeNum) + ", ";
        return traversal;
    }

    /**
     * Traverse the tree in inorder
     * @param Starting node, the root
     * @return The traversal as a string
     */
    public String inorder(int nodeNum){
        if(2*nodeNum+1 <= tree.length-1){
            inorder(2*nodeNum+1);
        }
        traversal += Integer.toString(nodeNum) + ", ";
        if(2*nodeNum+2 < tree.length-1){
            inorder(2*nodeNum+2);
        }
        return traversal;
    }

    /**
     * Clear the traversal variable of the tree
     */
    public void clearTraversal(){
        this.traversal = "";
    }
 }