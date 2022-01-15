# Corewar


https://www.section.io/engineering-education/what-is-little-endian-and-big-endian/ 

Your numerical value of 1000 is the first 4 bytes: e8 03 00 00.

Intel CPUs being little-endian, the bytes (not the nybbles) have to be reordered to read them in normal left-right order, so the value becomes 00 00 03 e8. Dropping the leading zeros leaves you 3e8 in hex, which is, indeed, 1000 in decimal.

 Writing the bytes from variable, which is a 32-bit integer, to the file character-by-character in memory order. 
 
 If you want it to be human-readable as a number, you will have to convert it to a string representation using the function of your choice.