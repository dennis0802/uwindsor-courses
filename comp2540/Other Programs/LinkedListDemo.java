public class LinkedListDemo {
    public static void main(String args[]){
        LinkedList<Integer> list = new LinkedList<Integer>();
        LinkedList<Integer> sorted = new LinkedList<Integer>();
        list.insert(list, 10);
        list.insert(list, 1);
        list.insert(list, 2);
        list.insert(list, 3);
        sorted.insertOrder(sorted, 4);
        sorted.insertOrder(sorted, 11);
        sorted.insertOrder(sorted, 3);
        sorted.insertOrder(sorted, 6);
        sorted.insertOrder(sorted, 8);
        System.out.println(list.getElements(list));
        System.out.println(sorted.getElements(sorted) + "\n");
        
        int findFourUnsorted = list.findUnsorted(list, 4);
        if(findFourUnsorted == -1){
            System.out.println("4 was not in the list");
        }
        else{
            System.out.println("4 was in node " + findFourUnsorted);
        }

        int findFourSorted = sorted.findSorted(sorted, 4);
        if(findFourSorted == -1){
            System.out.println("4 was not in the list");
        }
        else{
            System.out.println("4 was in node " + findFourSorted);
        }

        list.deleteUnsortedElement(list, 10);
        list.deleteUnsortedElement(list, 2);
        sorted.deleteSortedElement(sorted, 3);
        sorted.deleteSortedElement(sorted, 8);
        sorted.deleteSortedElement(sorted, 11);
        System.out.println();
        System.out.println(list.getElements(list));
        System.out.println(sorted.getElements(sorted) + "\n");
    }
}
