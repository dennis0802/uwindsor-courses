/*
* Student Name: Dennis Dao
* Student Number: 110010116
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Define a structure of type Point
 */
typedef struct Point {
	int x;
        int y;
} Point;

/*
 * Define a structure of type Line
 */
typedef struct Line {
	Point start;
    	Point end;
    	char color[15];
} Line;

/*
 * setPoint is of type Point - allows user to set coordinates of a point.
 * Set x coordinate of p.
 * Set y coordinate of p.
 * Return point p.
 */
Point setPoint(int x, int y) {
 	Point p;
    	p.x = x;
    	p.y = y;
    	return p;
}

/*
 * setLine is of type Line - allows user to set points and colour of line
 * s and e are of type Point
 * Set colour of line.
 */
Line setLine(Point s, Point e, char lineColor[]) {
    	Line l;
    	l.start = s;
    	l.end = e;
    	strcpy(l.color, lineColor);
    	return l;
}

/*
 * Print the point of a Point structure
 * given a Point p.
 */
void PrintPoint(Point p) {
	printf("(%d, %d)  \n", p.x, p.y);
}

/*
 * Print the line of a Line structure
 * given a Line l.
 */
void PrintLine(Line l) {
    	printf("start at: ");
    	PrintPoint(l.start);
    	printf("end at: ");
    	PrintPoint(l.end);
    	printf("color is: %s \n", l.color);
}

/*
 * Allow user to edit properties of the line
 * given the pointer to the line.
 */
void EditLine(Line *l) {
	// Prompt user for line properties.
    	printf("Please enter the new start point (x, y): ");
    	scanf("%d %d", &l->start.x, &l->start.y);

    	printf("Please enter the new end point (x, y): ");
    	scanf("%d %d", &l->end.x, &l->end.y);

    	printf("Please enter the line color: ");
    	scanf(" %[^\n]s", (*l).color);
}

/*
 * Reverse properties of the line. (sX is now eX, sY is now eY, etc.)
 * given the pointer to the line.
 */
void ReverseLine(Line *l) {
    	Point temp;

    	temp.x = (*l).start.x;
    	temp.y = (*l).start.y;

    	(*l).start.x = (*l).end.x;
    	(*l).start.y = (*l).end.y;

    	(*l).end.x = temp.x;
    	(*l).end.y = temp.y;
}

/*
 * Pointer to make the point list is of type Point - make pointers of type
 * point during program execution.
 * @param size
 * @return ptr
 */
Point *CreatePointList(int size) {
    	Point *ptr = (Point *) malloc(size * sizeof(Point));
    	return ptr;
}

/*
 * Intialize the list of points
 * @param list
 * @param size
 */
void InitializePointsList(Point *list, int size) {
    	int x;
    	int y;

    	for (int i = 0; i < size; i++) {
        	printf("enter data for point # %d: ", i);
        	scanf("%d %d", &x, &y);
        	*(list + i) = setPoint(x, y);
    	}
}

/*
 * Print the list of points.
 * @param list
 * @param size
 */
void PrintPointList(Point *list, int size) {
    	printf("\nHere are the points stored in the list: \n");
    	for (int i = 0; i < size; i++) {
	        PrintPoint(*(list + i));
    	}
}

// Sort the list of points given the pointer to the list and the size.
void SortPointList(Point *list, int size){
     	Point temp;
	char coordinate;

	while(coordinate != 'X' && coordinate != 'x' && coordinate != 'Y' && coordinate != 'y'){
		// Prompt user for coordinate until they enter a valid input (X, x, Y, or y)
		printf("\nSort coordinates by x-coordinate or y-coordinate?\n");
		scanf(" %c", &coordinate);

		// Sort by x-coordinate
		if(coordinate == 'X' || coordinate == 'x'){
     			for(int i =0; i< size-1; i++){
         			for(int j = i+1; j <size; j++){
             				if( (*(list+i)).x  > (*(list+j)).x ){
	              				temp = setPoint((*(list+i)).x, (*(list+i)).y);
		                		*(list+i) = setPoint((*(list+j)).x, (*(list+j)).y);
		                		*(list+j) = setPoint(temp.x, temp.y);
		        		}
         			}
     			}
		}

		// Sort by y-coordinate
                if(coordinate == 'Y' || coordinate == 'y'){
                        for(int i =0; i< size-1; i++){
                                for(int j = i+1; j <size; j++){
                                        if( (*(list+i)).y  > (*(list+j)).y ){
                                                temp = setPoint((*(list+i)).x, (*(list+i)).y);
                                                *(list+i) = setPoint((*(list+j)).x, (*(list+j)).y);
                                                *(list+j) = setPoint(temp.x, temp.y);
                                        }
                                }
                        }
                }

	}
}

int main(){
    	// Declare variable start of type Point and use the function setPoint(x,y) to set the x coordinate
    	// and y coordinate of the point start
    	Point start = setPoint(5, 7);

    	// Declare initial variable end of type point and set the x and y coordinate
    	Point end = setPoint(3, 9);

    	// Declare variable aline of type line and use the function setLine(start, end, color) to set the start point , end
    	// point, and the color of the line
    	Line aline = setLine(start, end, "red");

    	// Call the function PrintLine(Line) that print the information of any variable of type Line
    	printf("\nHere is the current Line data: \n");
    	PrintLine(aline);

    	// Call the function EditLine(Line) which allow the user to change the information of any variable of type Line
    	EditLine(&aline);

    	// Call the function PrintLine(Line) that print the information of any variable of type Line
    	// Note: after calling EditLine(aline) it is expected that PrintLine will display the new data of aLine
    	printf("\nHere is the new Line data: \n");
    	PrintLine(aline);

    	// Call the function ReverseLine(Line) this function will reverse the start and the end points on any given Line
    	// variable (swap the start and end points)
    	printf("\nAfter reversing the start and end points of the line: \n");
    	ReverseLine(&aline);

    	// Call the function PrintLine(Line) that print the information of any variable of type Line
    	// Note: after calling EditLine(aline) it is expected that PrintLine will display the new data of aLine
    	PrintLine(aline);

    	int num;

    	printf("\nPlease enter the total number of points you want to create: ");
    	scanf("%d", &num);

    	// Call the function CreatePointList(num) which allocate enough memory to store n number of points in an an array of
    	// Point structures
    	Point *pointlist = CreatePointList(num);

    	// Call the function InitializePointsList(pointList, num) which allow the user to enter the data for each point in
    	// the list of points
    	InitializePointsList(pointlist, num);

   	// Call the function PrintPointList(pointList,num) which will print all the points in the list.
    	PrintPointList(pointlist, num);

    	// Call SortPointList(pointList, num) that sort the list of points based on x or y
    	SortPointList(pointlist, num);

    	// Print the sorted point list
    	PrintPointList(pointlist,num);
}
