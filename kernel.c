// OS Kernel
// Jarrod LeComte

void printString(char*);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int, int, int, int);

void main(){

	int startVidMem = 0xb800;
	int vidMemOffset = 0x0;
	int white = 0x7;
	char* letters = "Hello World\0";
    char line[80];
    char buffer[512];


    interrupt(0x21,0,0,0,0);

	while(*letters != 0x0){
		//Sets message
		putInMemory(startVidMem, vidMemOffset, *letters);
		vidMemOffset++;
		//Sets text color
		putInMemory(startVidMem, vidMemOffset, white);
		vidMemOffset++;

		//Moves pointer
		letters++;
	}

    readSector(buffer, 30);
    printString(buffer);
    makeInterrupt21();
    interrupt(0x21,0,"Type Something: ",0,0);
    interrupt(0x21,1,line,0,0);

	//interrupt(0x21,1,line,0,0);
    interrupt(0x21,0,line,0,0);


	//printString("Enter a line: ");
	//readString(line);
	//printString(line);
    //Printstring doesn't work with line, but works with other strings?'

	while(1);

}

void printString(char* chars){
    
    //Loops until \0 is reached. Uses 0x10 interrupt for each input character
    int i = 0;
    while(chars[i] != '\0'){
        int charvalue = chars[i];
        interrupt(0x10, 0xe*256+charvalue, 0, 0, 0);
        i++;
    }
}

void readString(char* line){

    //Values of keys
    int enter = 0xd;
    int backspace = 0x8;

    int i = 0;

    while(1){

        int asciivalue = interrupt(0x16, 0, 0, 0, 0);

        if(asciivalue == enter){
	        line[i] = 0xd;
            interrupt(0x10, 0xe*256+0xd, 0, 0, 0);
			i++;
			line[i] = 0xa;
            interrupt(0x10, 0xe*256+0xa, 0, 0, 0);
			i++;
			line[i] = 0x0;
            interrupt(0x10, 0xe*256+0x0, 0, 0, 0);
			break;
        }
        else if(asciivalue == backspace){
            if(i>0){
                line[i] = 0x0;
                i--;
                interrupt(0x10, 0xe*256+0x8, 0, 0, 0);
				i++;
				interrupt(0x10, 0xe*256+0x0, 0, 0, 0);
				i--;
				interrupt(0x10, 0xe*256+0x8, 0, 0, 0);
            }
        }
        else{
            line[i] = asciivalue;
            interrupt(0x10, 0xe*256+asciivalue, 0, 0, 0);
            i++;
        }

    }//end of while loop
}

void readSector(char* buffer, int sector){

	int ah = 2; // 2 is read
	int al = 1; // Number of sectors to read
	int bx = buffer; // Data storage address
	int ch = 0; // Track number
	int cl = sector + 1; //Relative sector number (sector + 1)
	int dh = 0; // Head number
	int dl = 0x80; //Device number (0x80 for hard disk)

	int ax = ah*256+al;
	int cx = ch*256+cl;
	int dx = dh*256+dl;

	interrupt(0x13, ax, bx, cx, dx);

}

void handleInterrupt21(int ax, int bx, int cx, int dx){
	if (ax == 0){
	    printString(bx);
    }
	else if (ax == 1){
		readString(bx);
	}
	else if (ax == 2){
		readSector(bx, 30);
	}
	else if (ax > 2){
		printString("Error\0");
	}
}
