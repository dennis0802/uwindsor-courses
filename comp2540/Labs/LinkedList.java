/**
 * Developer: Dennis Dao
 * Date: Feb 4, 2021
 * version 1.0
 */

/**
 * Make a LinkedList class
 */
public class LinkedList<E>{
    Node head;

    class Node{
        E data;
        Node next;

        Node(E d){
            data = d;
        }
    }

    // Insert an element
    public LinkedList<E> insert(LinkedList<E> list, E data){
        // Initialize new node
        Node newNode = new Node(data);
        newNode.next = null;

        // If the list is empty, the new node is the head
        if(list.head == null){
            list.head = newNode;
        }
        // Find the last node and make the new node the last node
        else{
            Node last = list.head;
            while(last.next != null){
                last = last.next;
            }
            last.next = newNode;
        }
        return list;
    }

    // Delete an element at the end
    public LinkedList<E> deleteAtEnd(LinkedList<E> list){
        Node node = list.head;
        while(node.next != null && node.next.next != null){
            node = node.next;
        }
        node.next = null;
        return list;
    }   
    
    // Delete an element at the head of the list
    // * Strictly to be used when the stack contains one element!
    public LinkedList<E> deleteAtHead(LinkedList<E> list){
        if(list.head == null){
            return list;
        }
        list.head = list.head.next;
        return list;
    }
    
    // Delete an element at the end
    public E getLastElement(LinkedList<E> list){
        Node node = list.head;
        if(node == null){
            return null;
        }
        while(node.next != null){
            node = node.next;
        }
        return node.data;
    }

    // Get number of elements in the list
    public int getNumElements(LinkedList<E> list){
        int count = 1;
        Node node = list.head;
        if(node == null){
            return 0;
        }
        while(node.next != null){
            node = node.next;
            count++;
        }
        return count;
    }

    // Get the elements of the list
    public String getElements(LinkedList<E> list){
        String message = "";
        Node node = list.head;
        if(node == null){
            return message;
        }
        message += node.data;
        while(node.next != null){
            node = node.next;
            message += " -> " + node.data;
        }
        return message;
    }
}
