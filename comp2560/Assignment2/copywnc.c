/**
 * Copy with No Comments
 * Developer: Dennis Dao
 * Date: January 31, 2021
 * version 1.0
 */

// This program copys a c file without the comments

#include <stdio.h>

// Function prototypes
int copyfile(const char *f1, const char *f2);

int main(int argc, char *argv[]){
	// Usage
	if(argc != 3){
		puts("Usage: copywnc target-file new-file");
		return -1;
	}
	copyfile(argv[1], argv[2]);
	puts("Copying successful.");
}

// Function defintions
// Copy the contents of file1 to file2
int copyfile(const char *f1, const char *f2){
	// Variable defintions
	FILE *inf, *outf;
	int c;

	// Problems opening the first file for reading
	if((inf = fopen(f1, "r")) == NULL){
		return -1;
	}

	// Problems opening the second file for writing
	if((outf = fopen(f2, "w")) == NULL){
		fclose(inf);
		return -2;
	}

	// Read from the file
	while((c = getc(inf)) != EOF){
		// / found
		if(c == '/'){
			c = getc(inf);
			// Single line comment found
			if(c == '/'){
				// Ignore all characters until \n found
				while((c = getc(inf)) != EOF){
					if(c == '\n'){
						putc(c, outf);
						break;
					}
				}
			}
			// Beginning of a block comment found
			else if(c == '*'){
				// Ignore all characters until */ found
				while((c = getc(inf)) != EOF){
					if(c == '*'){
						c = getc(inf);
						if(c == '/'){
							break;
						}
						// If not /, then puts the char back to the infile for the while loop.
						else{
							ungetc(c, inf);
						}
					}
				}
			}
			// Typical C code
			else{
				putc(c, outf);
			}
		}
		// Typical C code
		else{
			putc(c, outf);
		}
	}
	fclose(inf);
	fclose(outf);
	return 0;
}
