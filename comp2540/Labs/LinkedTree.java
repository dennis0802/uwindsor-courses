/**
 * Developer: Dennis Dao
 * Date: Mar 10, 2021
 * version 1.0
 */

// This implements the Linked Tree data structure
public class LinkedTree {
    // Instance variables
    private int[] tree;
    private Node root;
    private static int nodesTravelled;
    private static int depth;
    private String outputCoords = "";
    private String transversal = "";

    /**
     * Node class for the tree
     */
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

    /**
     * Default constructor
     */
    public LinkedTree(){
        root = null;
    }

    /**
     * Second constructor
     * @param tree An tree, or array of values
     */
    public LinkedTree(int[] tree){
        this.tree = tree;
        root = new Node(tree[0]);
        setValues(root, 0);
    }

    /**
     * Traverse the tree inorder and set coordinate values (x = num nodes visited before reaching node n, y = height/depth)
     * For Part C (mapping tree coordinates)
     * @param node The root of the tree
     */
    public void inorderSet(Node node){
        // Left branch
        if(node.left != null){
            depth++;
            inorderSet(node.left);
            depth--;
        }

        node.xCoord = nodesTravelled;
        node.yCoord = depth;
        nodesTravelled++;

        // Right branch
        if(node.right != null){
            depth++;
            node.right.parent = node;
            inorderSet(node.right);
            depth--;
        }
    }

    /**
     * Traverse the tree inorder
     * @param node The root of the tree
     */
    public String inorder(Node node){
        // Left branch
        if(node.left != null){
            inorder(node.left);
        }

        transversal += node.data + " -> ";

        // Right branch
        if(node.right != null){
            inorder(node.right);
        }
        return transversal + "\n";
    }

    /**
     * Set the values of the tree
     * @param node The node to add values to the left or right to
     * @param num The position of the root node
     */
    public void setValues(Node node, int num){
        // Left branch
        if(2*num+1 <= tree.length-1){
            Node current = new Node(tree[2*num+1]);
            current.parent = node;
            node.left = current;
            setValues(node.left, 2*num+1);
        }
        // Right branch
        if(2*num+2 <= tree.length-1){
            Node current = new Node(tree[2*num+2]);
            current.parent = node;
            node.right = current;
            setValues(node.right, 2*num+2);
        }
    }

    /**
     * Get the coordinates of each node in the tree using inorder traversal
     * For Part C (mapping tree coordinates)
     * @param node The root of the tree
     * @return The traversal of coordinates as a string
     */
    public String getCoordinates(Node node){
        // Left branch
        if(node.left != null){
            getCoordinates(node.left);
        }
        
        outputCoords += node.data + ": (" + node.xCoord + ", " + node.yCoord  + ")\n";

        // Right branch
        if(node.right != null){
            getCoordinates(node.right);
        }
        return outputCoords;
    }

    /**
     * Get the root of the tree
     * @return The root of the tree
     */
    public Node getRoot(){
        return this.root;
    }
    
    /**
     * Get the height of the tree
     * @param root The root of the tree
     * @return The height of the tree
     */
    public int height(Node root){
        if(root == null){
            return -1;
        }
        else{
            return 1 + Math.max(height(root.left), height(root.right));
        }
    }

    /**
     * Get the size of the tree
     * @param root The root of the tree
     * @return The size of the tree
     */
    public int size(Node root){
        if(root == null){
            return 0;
        }
        else{
            return 1 + size(root.left) + size(root.right);
        }
    }

    /**
     * Clear the output coordinate string
     */
    public void clearOutputCoord(){
        this.outputCoords = "";
    }

    /**
     * Clear the transversal string
     */
    public void clearTransversal(){
        this.transversal = "";
    }

    // Beyond this point is lecture slide material
    /**
     * Search the tree for a node containing a value (assume a sorted tree)
     * @param start The starting node
     * @param key The key to search for
     * @return The node containing the key
     */
    public Node treeSearch(Node start, int key){
        if(start == null || key == start.data){
            return start;
        }
        else if(key < start.data){
            return treeSearch(start.left, key);
        }
        else{
            return treeSearch(start.right, key);
        }
    }

    /**
     * Find the min value (assume a sorted tree)
     * @param start The node to start the search
     * @return The node with the min value
     */
    public Node minTree(Node start){
        while(start.left != null){
            start = start.left;
        }
        return start;
    }

    /**
     * Find the min value (assume a sorted tree)
     * @param start The node to start the search
     * @return The node with the min value
     */
    public Node maxTree(Node start){
        while(start.right != null){
            start = start.right;
        }
        return start;
    }

    /**
     * Find the successor of a node (the node with the smallest key greater than the value in start)
     * @param start The node to start the search
     * @return The successor node
     */
    public Node successor(Node start){
        if(start.right != null){
            return minTree(start.right);
        }
        else{
            Node par = start.parent;
            while(par != null && start == par.right){
                start = par;
                par = start.parent;
            }
            return par;
        }
    }

    /**
     * Find the predecessor of a node (the node with the largest key less than the value in start)
     * @param start The node to start the search
     * @return The predecessor node
     */
    public Node predecessor(Node start){
        if(start.right != null){
            return maxTree(start.left);
        }
        else{
            Node par = start.parent;
            while(par != null && start == par.left){
                start = par;
                par = start.parent;
            }
            return par;
        }
    }

    /**
     * Insert an element
     * @param newNode The starting node, the root
     * @param data The data of the node
     * @return The node that was added
     * @throws Exception If the key already exists
     */
    public Node insert(Node newNode, int data) throws Exception{
        Node t = null;
        if(newNode == null){
            t = new Node(data);
            if(root == null){
                root = t;
            }
            return t;
        }
        else if(data < newNode.data){
            newNode.left = insert(newNode.left, data);
            newNode.left.parent = newNode;
        }
        else if(data > newNode.data){
            newNode.right = insert(newNode.right, data);
            newNode.right.parent = newNode;
        }
        else{
            throw new Exception("Key exists!");
        }
        return newNode;

    }

    public Node LLRotation(Node left){
        Node node = left.left;
        if(left.parent.left == left){
            left.parent.left = node;
        }
        else{
            left.parent.right = node;
        }
        left.left = node.right;
        node.right = left;
        return node;
    }

    public Node RRRotation(Node right){
        Node node = right.right;
        if(right.parent.left == right){
            right.parent.left = node;
        }
        else{
            node.parent.right = node;
        }
        right.right = node.left;
        node.left = right;
        return node;
    }

    public Node LRRotationLeft(Node node){
        node.left = LRRotationRight(node.left);
        return node.left;
    }

    public Node LRRotationRight(Node node){
        node.right = LRRotationLeft(node.right); 
        return node.right;
    }
}
