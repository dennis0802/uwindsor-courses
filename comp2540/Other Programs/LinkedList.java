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

    // Insert an element based on smallest to largest order
    public LinkedList<E> insertOrder(LinkedList <E> list, E data){
        Node newNode = new Node(data);

        if(list.head == null || (Integer)newNode.data < (Integer)list.head.data){
            newNode.next = list.head;
            list.head = newNode;
        }
        else{
            Node curr = list.head;

            while(curr.next != null && (Integer)curr.next.data < (Integer)newNode.data){
                curr = curr.next;
            }
            newNode.next = curr.next;
            curr.next = newNode;
        }

        
        return list;
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

    public int findUnsorted(LinkedList<E> list, E data){
        int nodeNum = 1;
        Node current = list.head;

        while(current != null && current.data != data){
            nodeNum++;
            current = current.next;
        }

        if(current == null){
            return -1;
        }
        else if(current.data == data){
            return nodeNum;
        }
        return -1;
    }

    public int findSorted(LinkedList<E> list, E data){
        int nodeNum = 1;
        Node current = list.head;

        while(current != null && (Integer)current.data < (Integer)data){
            current = current.next;
            nodeNum++;
        }
        if(current.data == data){
            return nodeNum;
        }
        return -1;
    }

    public LinkedList<E> deleteUnsortedElement(LinkedList<E> list, E data){
        if(list.head != null){
            if(list.head.data == data){
                list.head = list.head.next;
            }
            else{
                Node current = list.head;
                while(current.next != null && current.next.data != data){
                    current = current.next;
                }
                if(current.next != null && current.next.data == data){
                    current.next = current.next.next;
                }
            }
        }
        return list;
    }

    public LinkedList<E> deleteSortedElement(LinkedList<E> list, E data){
        if(list.head != null){
            if(list.head.data == data){
                list.head = list.head.next;
            }
            else{
                Node current = list.head;
                while(current.next != null && (Integer)current.next.data < (Integer)data){
                    current = current.next;
                }
                if(current.next != null && current.next.data == data){
                    current.next = current.next.next;
                }
            }
        }
        return list;      
          
    }
}
