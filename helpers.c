// Helper functions for music
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int n = (atoi(&fraction[0]));
    int d = (atoi(&fraction[2]));

    return (((float)n/d) * 8);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //Assign octave and letter note to variables.
    char noteC = note[0];
    bool sharpFlat = (note[1] < 48 || note[1] > 57) ? true : false; //Bool checking if note is sharp or flat.
    int octave = atoi(&note[strlen(note) - 1]);

    const char scale[] = "CCDDEFFGGAAB";                            //Basic scale for calculating where the note is located. (12 steps per octave)
    const char *p = strchr(scale,noteC);                            //char pointer finding the location of the letter note.

    int noteDif = sharpFlat ? note[1] == '#' ? 12 - (p - scale + 2) : 12 - (p - scale) : 12 - (p - scale + 1);  //Calculates the note difference. Basically, where the note is located.
                                                                                                                //Since one octave is 12 steps, it calculates it in reverse. Instead of counting "10 steps into the 3rd octave" it counts
                                                                                                                //"2 steps before octave 4" which is why it's 12 - (location)
                                                                                                                //If sharp, adds one step. If flat removes one step.
    double location = ((octave * 12) - noteDif) - 46;               //octave * 12 is due to 12 steps per octave. You then remove the note difference, and remove 46 (The step location of A4)
                                                                    //This gives you a number which is equal to how many steps forwards, or backwards from A4 the note is.

    return (round(440 * (pow(2, (location / 12))))) ;               //Uses location to calculate the frequency of the note.
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return (strcmp(s,"") == 0) ? true : false;          //Returns true/false depending on if the string is ""
}

/*
int main(void)
{

    if(is_rest(get_string("Enter string\n")))
    {
        printf("Rest.\n");
    }
    else
    {
        printf("Not rest\n");
    }

    printf("A4 note location: %i\n", frequency("A4"));
    printf("G8 note location: %i\n", frequency("G8"));
    printf("Eb5 note location: %i\n", frequency("Eb5"));
    printf("E5 note location: %i\n", frequency("E5"));
    printf("A3 note location: %i\n", frequency("A3"));
    printf("Ab3 note (208 expected): %i\n", frequency("Ab3"));
    printf("C3 note (131 expected): %i\n", frequency("C3"));
    printf("F#2 note location: %i\n\n", frequency("F#2"));
    printf("Duration 1/8 %i\n", duration("1/8"));
    printf("Duration 1/4 %i\n", duration("1/4"));
    printf("Duration 3/8 %i\n", duration("3/8"));
    printf("Duration 1/2 %i\n", duration("1/2"));
    return 0;
}
*/