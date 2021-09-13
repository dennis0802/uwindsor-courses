public class DoublyLinkedList<E> {
    class Node{
        E data;
        
        Node next;
        Node previous;

        Node(E d){
            data = d;
        }
    }
    Node head;
    Node tail;
    
    /**
     * Set up header and trailer nodes
     */
    public DoublyLinkedList(){
        head = new Node(null);
        tail = new Node(null);

        head.next = tail;
        tail.previous = head;
    }

    // Insert an element
    public DoublyLinkedList<E> insert(DoublyLinkedList<E> list, E data){
        // Initialize new node
        Node newNode = new Node(data);
        newNode.next = list.head.next;
        newNode.previous = list.head;
        list.head.next.previous = newNode;
        list.head.next = newNode;
        return list;
    }

    public DoublyLinkedList<E> insertSorted(DoublyLinkedList<E> list, E data){
        // Initialize new node
        Node newNode = new Node(data);
        Node current = list.head.next;

        while(current != list.tail && (Integer)current.data < (Integer)data){
            current = current.next;
        }

        newNode.next = current;
        newNode.previous = current.previous;
        current.previous.next = newNode;
        current.previous = newNode;

        return list;
    }

    // Get the elements of the list
    public String getElements(DoublyLinkedList<E> list){
        String message = "";
        Node node = list.head;
        if(node == null){
            return message;
        }
        message += node.data;
        while(node != list.tail){
            node = node.next;
            message += " <-> " + node.data;
        }
        return message;
    }

    public int findUnsorted(DoublyLinkedList<E> list, E data){
        Node current = list.head.next;
        int nodeNum = 0;

        while(current != list.tail && current.data != data){
            current = current.next;
            nodeNum++;
        }

        if(current.data == data){
            return nodeNum;
        }
        return -1;
    }

    public int findSorted(DoublyLinkedList<E> list, E data){
        Node current = list.head.next;
        int nodeNum = 0;

        while(current != list.tail && current.data != data){
            current = current.next;
            nodeNum++;
        }

        if(current.data == data){
            return nodeNum;
        }
        return -1;
    }

    public void deleteUnsorted(DoublyLinkedList<E> list, E data){
        Node current = list.head.next;

        while(current != list.tail && current.data != data){
            current = current.next;
        }

        if(current != tail && current.data == data){
            current.previous.next = current.next;
            current.next.previous = current.previous;
            current.previous = current.next = null;
        }
    }

    public void deleteUnsortedStartingEnd(DoublyLinkedList<E> list, E data){
        Node current = list.tail.previous;

        while(current != list.head && current.data != data){
            current = current.previous;
        }

        if(current != tail && current.data == data){
            current.previous.next = current.next;
            current.next.previous = current.previous;
            current.previous = current.next = null;
        }
    }

    public void deleteSorted(DoublyLinkedList<E> list, E data){
        Node current = list.head.next;

        while(current != list.tail && (Integer)current.data < (Integer)data){
            current = current.next;
        }

        if(current != list.tail && current.data == data){
            current.previous.next = current.next;
            current.next.previous = current.previous;
            current.previous = current.next = null;
        }
    }

    public void deleteSortedStartingEnd(DoublyLinkedList<E> list, E data){
        Node current = list.tail.previous;

        while(current != list.head && (Integer)current.data > (Integer) data){
            current = current.previous;
        }

        if(current != list.head && current.data == data){
            current.previous.next = current.next;
            current.next.previous = current.previous;
            current.next = current.previous = null;
        }
    }
}
