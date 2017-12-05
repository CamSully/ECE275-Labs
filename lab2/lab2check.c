/* Written by Dr. Richard Eason, UMaine. 
* Used by Cameron Sullivan for ECE 275 lab.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTATES 6

// Adjust the following if MAXSTATES changes
char states[MAXSTATES][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
int numstates = 0;

int addstate(const char* buff);
int getoutput(const char* buff);

int main(int argc, char** argv) {

	int i;
	int ps[MAXSTATES];
	int ns[MAXSTATES][2];
	int z[MAXSTATES][2];
        int reverse[MAXSTATES];         // Reverse lookup to find row for a given state
        
        int numinputs = 17;
        int inputsequence[]  = {0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1};
        int outputsequence[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
        char error;
        int state;
        
        if (argc > 1) {
            FILE * fp;
            if ((fp = fopen(argv[1], "r")) == 0) {
                printf("Could not open %s for input\n\n", argv[1]);
                exit(0);
            }
            for (i=0; i<MAXSTATES; i++) {
                    char buff[1024];		// only expect 3 characters at most...
//                    printf("Row %d: ", i+1);
                    fscanf(fp, "%s", buff);
                    ps[i] = addstate(buff);
                    fscanf(fp, "%s", buff);
                    ns[i][0] = addstate(buff);
                    fscanf(fp, "%s", buff);
                    ns[i][1] = addstate(buff);
                    fscanf(fp, "%s", buff);
                    z[i][0] = getoutput(buff);	
                    fscanf(fp, "%s", buff);
                    z[i][1] = getoutput(buff);
            }
            fclose(fp);
                    
        }
            
        else {
            printf("\n\nEnter the rows of your state table as: PS NS(X=0) NS(X=1) Z(X=0) Z(X=1)\n ");
            printf("For example:\n");
            printf("    S0 S1 S4 0 0 \n");
            printf("States may use one or two characters. Separate items by spaces or tabs\n");
            printf("The first row should be for your reset state\n");
            printf("\n");
            
            for (i=0; i<MAXSTATES; i++) {
                    char buff[1024];		// only expect 3 characters at most...
                    printf("Row %d: ", i+1);
                    scanf("%s", buff);
                    ps[i] = addstate(buff);
                    scanf("%s", buff);
                    ns[i][0] = addstate(buff);
                    scanf("%s", buff);
                    ns[i][1] = addstate(buff);
                    scanf("%s", buff);
                    z[i][0] = getoutput(buff);	
                    scanf("%s", buff);
                    z[i][1] = getoutput(buff);
                    
            }
        }
        
        
        printf("\n\n");
	printf("Your state table is: \n");
            printf("         |    NS      |    Z\n");
            printf("     PS  | X=0   X=1  | X=0 X=1\n");
            printf("   ______|____________|________\n");
        for (i=0; i< MAXSTATES; i++) {
            printf("    %3s  | %3s   %3s  |  %d   %d\n", states[ps[i]], states[ns[i][0]], states[ns[i][1]], z[i][0], z[i][1]);
        }
        printf("\n\n");
	
        if (numstates != MAXSTATES) {
            printf("You will need %d states for this problem\n\n", MAXSTATES);
            exit(0);
        }
        for (i=1; i<MAXSTATES; i++) {
            int j;
            for (j=0; j<i; j++) {
                if (ps[i] == ps[j]) {
                    printf("You list state %s as a present state more than once\n\n", states[ps[i]]);
                    exit(0);
                }
            }
        }
        
        for (i=0; i<MAXSTATES; i++) reverse[ps[i]] = i;         // generate reverse lookup
	
        error = 0;
        state = 0;
        for (i=0; i<numinputs; i++) {
            int row = reverse[state];
            if (z[row][inputsequence[i]] != outputsequence[i]) error = 1;
            state = ns[row][inputsequence[i]];
 	}
	
        printf("For input sequence: 0 1 0 1 1 1 0 0 1 1 0 1 0 0 1 0 1\n");
        printf("You output:         ");
        state = 0;
        for (i=0; i<numinputs; i++) {
            int row = reverse[state];
            printf("%d ", z[row][inputsequence[i]]);
            state = ns[row][inputsequence[i]];
        }
        printf("\n");
	if (error) {
            printf("Rather than:        0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1\n\n");
        }
        else {
            printf("which is correct\n\n");
        }

        state = 0;
        printf("Your sequence of states was: %s ", states[state]);
        for (i=0; i<numinputs; i++) {
            int row = reverse[state];
            state = ns[row][inputsequence[i]];
            printf("%s ", states[state]);
	}
	printf("\n\n");

}


int addstate(const char* buff) {
	int i;
        char mybuff[4] = {0, 0, 0, 0};     // last character is NULL

	if (strlen(buff) > 3) {
		printf("\n\nStates may have at most 3 characters\n");
		exit(0);
	}
	for (i=0; i<3; i++) mybuff[i] = buff[i]>='a' && buff[i]<='z' ? buff[i] - ('a' - 'A') : buff[i]; // toupper

	for (i=0; i < numstates; i++) {
		if (strcmp(mybuff, states[i]) == 0) return i;
	}

	if (i>=MAXSTATES) {
		printf("\n\nYou may have at most %d states\n", MAXSTATES);
		exit(0);
	}

	strcpy(states[i], mybuff);
	
	return numstates++;
}

int getoutput(const char* buff) {
	
	if (strlen(buff) > 1) {
		printf("\n\nOutputs must be a single character (0 or 1). Separate outputs by spaces or tabs.\n");
		exit(0);
	}

	if (buff[0] =='0') return 0;
	if (buff[0] =='1') return 1;

	printf("\n\nOutputs may only be 0 or 1\n");
	exit(0);
}

