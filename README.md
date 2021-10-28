# COMP350 - Project B
# Jarrod LeComte

Step 1: 
Used interrupt 0x10 to print "Hello World" through a printString(char*) function, passing through each letter until '\0' is reached.

Step 2:
Used interrupt 0x16 to read in input from the keyboard and printed them to the screen with 0x10. Handles backspace by overwriting the previous letter with a space and resetting the index to just before the space. Handles enter by ending the ability to enter text and echoing back the user-input text.

Step 3: 
Used interrupt 0x13 to read a file from a specific sector on the disk. By setting the parameters (ax, bx, cx, dx) into the interrupt, the text within a specific file (placed within sector 30 manually) would be printed to screen.

Step 4:
Used provided assembly code to create a handleInterrupt21(ax, bx, cx, dx) function that uses the parameters to call interrupt 0x21 to print a message to screen through printString.

Step 5:
Used the interrupt 0x21 handler provided to make printString, readString, and readSector function through the handleInterrupt21 function. Based on the ax parameter, it will decide on which function it will perform using bx as the passed in variable. 

Testing:
If a message is displayed when the file is run, the readSector is functioning. You are then able to enter and delete text. Upon pressing enter, it will echo back the typed message. 
