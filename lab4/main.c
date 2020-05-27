#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct int_vector{
	int a, b, c, d;
}int_vector;

int_vector vector1;
int_vector vector2;

int_vector randomVector(int_vector *v) {
	v -> a = rand() % 1000 + 1;
	v -> b = rand() % 1000 + 1;
	v -> c = rand() % 1000 + 1;
	v -> d = rand() % 1000 + 1;
	return *v;
}

double SIMDAdd(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++) {
		randomVector(&vector1);
        for(int j = 0; j < noNumbers; j++) {
            randomVector(&vector2);
            begin = clock();
	            asm(
		            "movups %1, %%xmm0\n"
				    "movups %2, %%xmm1\n"
				    "addps  %%xmm1, %%xmm0\n"
				    "movups %%xmm0, %0\n"
				    :"=g"(vector1)
				    :"g"(vector1),"g"(vector2)
			    );
            end = clock();
		    time = (double)(end - begin) / CLOCKS_PER_SEC;
		    totalTime += time;
		}
	}
	avgTime = totalTime / 10;
	return avgTime;
}

double SIMDSub(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++) {
	    randomVector(&vector1);
        for(int j = 0; j < noNumbers; j++){
            randomVector(&vector2);
            begin = clock();
                asm(
                    "movups %1, %%xmm0\n"
                    "movups %2, %%xmm1\n"
                    "subps  %%xmm1, %%xmm0\n"
                    "movups %%xmm0, %0\n"
                    :"=g"(vector1)
                    :"g"(vector1),"g"(vector2)
                );
            end = clock();
            time = (double)(end - begin) / CLOCKS_PER_SEC;
            totalTime += time;
        }
	}
	avgTime = totalTime / 10;
	return avgTime;
}

double SIMDMul(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        randomVector(&vector1);
        for(int j = 0; j < noNumbers; j++){
            begin = clock();
            randomVector(&vector2);
            asm(
                "movups %1, %%xmm0\n"
				"movups %2, %%xmm1\n"
				"mulps  %%xmm1, %%xmm0\n"
				"movups %%xmm0, %0\n"
				:"=g"(vector1)
				:"g"(vector1),"g"(vector2)
            );
		    end = clock();
		    time = (double)(end - begin) / CLOCKS_PER_SEC;
		    totalTime += time;
        }
    }
    avgTime = totalTime / 10;
    return avgTime;
}

double SIMDDiv(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++) {
        randomVector(&vector1);
        for(int j = 0; j < noNumbers; j++) {
            randomVector(&vector2);
            begin = clock();
            asm(
                "movups %1, %%xmm0\n"
				"movups %2, %%xmm1\n"
				"divps  %%xmm1, %%xmm0\n"
				"movups %%xmm0, %0\n"
				:"=g"(vector1)
				:"g"(vector1),"g"(vector2)
            );
		    end = clock();
		    time = (double)(end - begin) / CLOCKS_PER_SEC;
		    totalTime += time;
        }
    }
    avgTime = totalTime / 10;
    return avgTime;
}


double SISDAdd(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	int x = 0;
	int y = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++) {
        x = rand() % 1000 + 1;
        for(int j = 0; j < noNumbers * 4; j++) {
            y = rand() % 1000 + 1;
            begin = clock();
		    asm(
                "movl %1, %%eax\n"
                "movl %2, %%ebx\n"
                "addl %%ebx, %%eax\n"
                "movl %%ebx, %0\n"
                :"=g"(x)
                :"g"(x),"g"(y)
            );
            end = clock();
		    time = (double)(end - begin) / CLOCKS_PER_SEC;
		    totalTime += time;
        }
    }
    avgTime = totalTime / 10;
    return avgTime;
}

double SISDSub(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	int x = 0;
	int y = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++) {
        x = rand() % 1000 + 1;
            for(int j = 0; j < noNumbers * 4; j++) {
                y = rand()%1000+1;
                begin = clock();
		        asm(
                    "movl %1, %%eax\n"
                    "movl %2, %%ebx\n"
                    "sbbl %%ebx, %%eax\n"
                    "movl %%ebx, %0\n"
                    :"=g"(x)
                    :"g"(x),"g"(y)
                );
		        end = clock();
		        time = (double)(end - begin) / CLOCKS_PER_SEC;
		        totalTime += time;
            }
        }
    avgTime = totalTime / 10;
    return avgTime;
}

double SISDMul(int noNumbers){
    double totalTime = 0;
    double avgTime = 0;
	int x = 0;
	int y = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        x = rand() % 1000 + 1;
            for(int j = 0; j < noNumbers * 4; j++){
                y = rand() % 1000 + 1;
                begin = clock();
				asm(
                    "movl %1, %%eax\n"
                    "movl %2, %%ebx\n"
                    "mull %%ebx\n"
                    "movl %%eax, %0\n"
                    :"=g"(x)
                    :"g"(x),"g"(y)
               );
		        end = clock();
		        time = (double)(end - begin) / CLOCKS_PER_SEC;
		        totalTime += time;
            }
        }
    avgTime = totalTime / 10;
    return avgTime;
 }

double SISDDiv(int noNumbers) {
    double totalTime = 0;
    double avgTime = 0;
	int x = 0;
	int y = 0;

	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++) {
        x = rand() % 1000 + 1;
            for(int j = 0; j < noNumbers * 4; j++) {
                y = rand() % 1000 + 1;
                begin = clock();
				asm(
                    "movl %1, %%eax\n"
					"movl %2, %%ebx\n"
                    "xor %%edx, %%edx\n"
					"divl %%ebx\n"
                    "movl %%eax, %0\n"
                                    :"=g"(x)
                                    :"g"(x),"g"(y)
                );
		        end = clock();
		        time = (double)(end - begin) / CLOCKS_PER_SEC;
		        totalTime += time;
            }
        }

    avgTime = totalTime / 10;
    return avgTime;
}


int main(){
	srand (time(NULL));
    FILE *fp; 
    if ((fp=fopen("results.txt", "w"))==NULL) {
     printf ("Err");
     exit(1);
     }

	fprintf(fp, "Typ obliczen: SIMD\nIlosc liczb: 2048\nSredni czas [s]:\n");
	fprintf(fp, "+ %f\n",SIMDAdd(2048));
	fprintf(fp, "- %f\n",SIMDSub(2048));
	fprintf(fp, "* %f\n",SIMDMul(2048));
	fprintf(fp, "/ %f\n",SIMDDiv(2048));
	fprintf(fp, "\n");

    fprintf(fp, "Typ obliczen: SISD\nIlosc liczb: 2048\nSredni czas [s]:\n");
	fprintf(fp, "+ %f\n",SISDAdd(2048));
    fprintf(fp, "- %f\n",SISDSub(2048));
    fprintf(fp, "* %f\n",SISDMul(2048));
  	fprintf(fp, "/ %f\n",SISDDiv(2048));
    fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SIMD\nIlosc liczb: 4096\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",SIMDAdd(4096));
    fprintf(fp, "- %f\n",SIMDSub(4096));
    fprintf(fp, "* %f\n",SIMDMul(4096));
    fprintf(fp, "/ %f\n",SIMDDiv(4096));
	fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SISD\nIlosc liczb: 4096\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",SISDAdd(4096));
    fprintf(fp, "- %f\n",SISDSub(4096));
    fprintf(fp, "* %f\n",SISDMul(4096));
    fprintf(fp, "/ %f\n",SISDDiv(4096));
    fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SIMD\nIlosc liczb: 8192\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",SIMDAdd(8192));
    fprintf(fp, "- %f\n",SIMDSub(8192));
    fprintf(fp, "* %f\n",SIMDMul(8192));
    fprintf(fp, "/ %f\n",SIMDDiv(8192));
	fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SISD\nIlosc liczb: 8192\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",SISDAdd(8192));
    fprintf(fp, "- %f\n",SISDSub(8192));
    fprintf(fp, "* %f\n",SISDMul(8192));
    fprintf(fp, "/ %f\n",SISDDiv(8192));

    fclose (fp);

    printf("Results saved.\n");

	return 0;

}
