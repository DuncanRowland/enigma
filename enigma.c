//Author: Duncan Rowland 13/April/2015

#include <stdio.h>
#include <stdlib.h>

#define NUMROTORS 3
#define NUMCHARS 26 /* Capitals only. A..Z -> 0..25 */

const char ROTORS[NUMROTORS+1][NUMCHARS] = {
   "ABCDEFGHIJKLMNOPQRSTUVWXYZ", //Rotor 1   (by default, f(A)->A, f(B)->B, ...)
   "ABCDEFGHIJKLMNOPQRSTUVWXYZ", //Rotor 2
   "ABCDEFGHIJKLMNOPQRSTUVWXYZ", //Rotor 3
   "ZYXWVUTSRQPONMLKJIHGFEDCBA"  //Reflector (additional, f(f(x))=x and f(x)!=x)
};

int rotors[2*NUMROTORS+1][NUMCHARS];

int main(int argc, char** argv)
{
   char* rotorPosition = argv[1];
   char* inCharacter = argv[2];

   while(*inCharacter!='\0') { //Loop over all characters in the input
      // Copy the rotor values and add the rotor position offset (mapping A->0, B->1, ...)
      for(int r=0;r<NUMROTORS;r++) {
         for(int c=0;c<NUMCHARS;c++)
            rotors[r][c]=ROTORS[r][(c+rotorPosition[r]-'A')%NUMCHARS]-'A';
      }
      // Copy and map the reflector values (these do not have the rotor offset applied)
      for(int c=0;c<NUMCHARS;c++)
         rotors[NUMROTORS][c]=ROTORS[NUMROTORS][c]-'A';

      // Generate the reverse paths
      for(int r=0;r<NUMROTORS;r++)
         for(int c=0;c<NUMCHARS;c++)
            rotors[2*NUMROTORS-r][rotors[r][c]]=c;

      // Map current character and apply all rotor substitutions (forwards, reflector and reverse)
      int v = (int)*inCharacter-'A';
      for(int r=0;r<=2*NUMROTORS;r++)
         v=rotors[r][v];

      // Increment the rotor position, character pointer and output the character
      rotorPosition[0]++;
      if(rotorPosition[0]>'Z') {
         rotorPosition[0]='A';
         rotorPosition[1]++;
         if(rotorPosition[1]>'Z') {
            rotorPosition[1]='A';
            rotorPosition[2]++;
               if(rotorPosition[2]>'Z') {
               rotorPosition[2]='A';
            }
         }
      }
      inCharacter++;
      printf("%c",(char)v+'A');
   }

   printf("\n");
   return 0;
}

