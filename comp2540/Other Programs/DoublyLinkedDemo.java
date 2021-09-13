public class DoublyLinkedDemo {
    public static void main(String args[]){
        DoublyLinkedList<Integer> list = new DoublyLinkedList<Integer>();
        DoublyLinkedList<Integer> sorted = new DoublyLinkedList<Integer>();

        list.insert(list, 1);
        list.insert(list, 2);
        list.insert(list, 4);
        list.insert(list, 0);
        sorted.insertSorted(sorted, 10);
        sorted.insertSorted(sorted, 9);
        sorted.insertSorted(sorted, 8);
        sorted.insertSorted(sorted, 7);
        sorted.insertSorted(sorted, 4);
        System.out.println(list.getElements(list));
        System.out.println(sorted.getElements(sorted));

        int findUnsorted = list.findUnsorted(list, 4);
        int findSorted = list.findSorted(sorted, 10);

        if(findUnsorted == -1){
            System.out.println("4 was not in the list");
        }
        else{
            System.out.println("4 was at node " + findUnsorted);
        }
        if(findSorted == -1){
            System.out.println("10 was not in the list");
        }
        else{
            System.out.println("10 was at node " + findSorted);
        }

        list.deleteUnsorted(list, 0);
        sorted.deleteSorted(sorted, 10);
        System.out.println(list.getElements(list));
        System.out.println(sorted.getElements(sorted));

        list.deleteUnsortedStartingEnd(list, 4);
        sorted.deleteSortedStartingEnd(sorted, 8);
        System.out.println(list.getElements(list));
        System.out.println(sorted.getElements(sorted));

        sorted.deleteSortedStartingEnd(sorted, 7);
        sorted.deleteSortedStartingEnd(sorted, 9);
        sorted.deleteSortedStartingEnd(sorted, 4);
        System.out.println(sorted.getElements(sorted));
        sorted.insertSorted(sorted, 10);
        System.out.println(sorted.getElements(sorted));
    }
}
