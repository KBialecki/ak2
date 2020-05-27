#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct int_vector{
	int a, b, c, d;
}int_vector;

int_vector vec1;
int_vector vec2;

int_vector randVec(int_vector *v){
	v->a = rand()%1000+1;
	v->b = rand()%1000+1;
	v->c = rand()%1000+1;
	v->d = rand()%1000+1;
	return *v;
}

double add_SIMD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
		randVec(&vec1);
        int j = 0;
        for(; j < numberOfNumbers; j++){
            randVec(&vec2);
            begin = clock();
	            asm(
		            "movups %1, %%xmm0\n"       //vecA do xmm0
				    "movups %2, %%xmm1\n"       //vecb do xmm1
				    "addps  %%xmm1, %%xmm0\n"
				    "movups %%xmm0, %0\n"
				    :"=g"(vec1)                 //output
				    :"g"(vec1),"g"(vec2)        //input
			    );
            end = clock();
		    time = (double)(end - begin)/CLOCKS_PER_SEC;
		    total_time += time;
		}
	}
	average_time = total_time/10;
	return average_time;
}

double sub_SIMD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
	    randVec(&vec1);
            for(int j = 0; j < numberOfNumbers; j++){
		        randVec(&vec2);
                begin = clock();
			        asm(
				        "movups %1, %%xmm0\n"
				        "movups %2, %%xmm1\n"
				        "subps  %%xmm1, %%xmm0\n"
				        "movups %%xmm0, %0\n"
				        :"=g"(vec1)
				        :"g"(vec1),"g"(vec2)
			        );
                end = clock();
		        time = (double)(end - begin)/CLOCKS_PER_SEC;
		        total_time += time;
		    }
	}
	average_time = total_time/10;
	return average_time;
}

double mul_SIMD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        randVec(&vec1);
        for(int j = 0; j < numberOfNumbers; j++){
            begin = clock();
            randVec(&vec2);
            asm(
                "movups %1, %%xmm0\n"
				"movups %2, %%xmm1\n"
				"mulps  %%xmm1, %%xmm0\n"
				"movups %%xmm0, %0\n"
				:"=g"(vec1)
				:"g"(vec1),"g"(vec2)
            );
		    end = clock();
		    time = (double)(end - begin)/CLOCKS_PER_SEC;
		    total_time += time;
        }

        }
    average_time = total_time/10;
    return average_time;
}

double div_SIMD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        randVec(&vec1);
        int j = 0;
        for(; j < numberOfNumbers; j++){
            randVec(&vec2);
            begin = clock();
            asm(
                "movups %1, %%xmm0\n"
				"movups %2, %%xmm1\n"
				"divps  %%xmm1, %%xmm0\n"
				"movups %%xmm0, %0\n"
				:"=g"(vec1)
				:"g"(vec1),"g"(vec2)
            );
		    end = clock();
		    time = (double)(end - begin)/CLOCKS_PER_SEC;
		    total_time += time;
        }
        }
    average_time = total_time/10;
    return average_time;
}


double add_SISD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	int x = 0;
	int y = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        x = rand()%1000+1;
        for(int j = 0; j < numberOfNumbers*4; j++){
            y = rand()%1000+1;
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
		    time = (double)(end - begin)/CLOCKS_PER_SEC;
		    total_time += time;
        }

    }
    average_time = total_time/10;
    return average_time;
}

double sub_SISD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	int x = 0;
	int y = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        x = rand()%1000+1;
            for(int j = 0; j < numberOfNumbers*4; j++){
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
		        time = (double)(end - begin)/CLOCKS_PER_SEC;
		        total_time += time;
            }
        }
    average_time = total_time/10;
    return average_time;
}

double mul_SISD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	int x = 0;
	int y = 0;
	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        x = rand()%1000+1;
            for(int j = 0; j < numberOfNumbers*4; j++){
                y = rand()%1000+1;
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
		        time = (double)(end - begin)/CLOCKS_PER_SEC;
		        total_time += time;
            }
        }
    average_time = total_time/10;
    return average_time;
 }

double div_SISD(int numberOfNumbers){
    double total_time = 0;
    double average_time = 0;
	int x = 0;
	int y = 0;

	clock_t begin;
	clock_t end;
	double time;

    for(int i = 0; i < 10; i++){
        x = rand()%1000+1;
            for(int j = 0; j < numberOfNumbers*4; j++){
                y = rand()%1000+1;
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
		        time = (double)(end - begin)/CLOCKS_PER_SEC;
		        total_time += time;
            }
        }

    average_time = total_time/10;
    return average_time;
}


int main(){
	srand (time(NULL));
    FILE *fp; 
    if ((fp=fopen("wyniki.txt", "w"))==NULL) {
     printf ("Nie mogę otworzyć pliku test.txt do zapisu!\n");
     exit(1);
     }

	fprintf(fp, "Typ obliczen: SIMD\nIlosc liczb: 2048\nSredni czas [s]:\n");
	fprintf(fp, "+ %f\n",add_SIMD(2048));
	fprintf(fp, "- %f\n",sub_SIMD(2048));
	fprintf(fp, "* %f\n",mul_SIMD(2048));
	fprintf(fp, "/ %f\n",div_SIMD(2048));
	fprintf(fp, "\n");

    fprintf(fp, "Typ obliczen: SISD\nIlosc liczb: 2048\nSredni czas [s]:\n");
	fprintf(fp, "+ %f\n",add_SISD(2048));
    fprintf(fp, "- %f\n",sub_SISD(2048));
    fprintf(fp, "* %f\n",mul_SISD(2048));
  	fprintf(fp, "/ %f\n",div_SISD(2048));
    fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SIMD\nIlosc liczb: 4096\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",add_SIMD(4096));
    fprintf(fp, "- %f\n",sub_SIMD(4096));
    fprintf(fp, "* %f\n",mul_SIMD(4096));
    fprintf(fp, "/ %f\n",div_SIMD(4096));
	fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SISD\nIlosc liczb: 4096\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",add_SISD(4096));
    fprintf(fp, "- %f\n",sub_SISD(4096));
    fprintf(fp, "* %f\n",mul_SISD(4096));
    fprintf(fp, "/ %f\n",div_SISD(4096));
    fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SIMD\nIlosc liczb: 8192\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",add_SIMD(8192));
    fprintf(fp, "- %f\n",sub_SIMD(8192));
    fprintf(fp, "* %f\n",mul_SIMD(8192));
    fprintf(fp, "/ %f\n",div_SIMD(8192));
	fprintf(fp, "\n");

	fprintf(fp, "Typ obliczen: SISD\nIlosc liczb: 8192\nSredni czas [s]:\n");
    fprintf(fp, "+ %f\n",add_SISD(8192));
    fprintf(fp, "- %f\n",sub_SISD(8192));
    fprintf(fp, "* %f\n",mul_SISD(8192));
    fprintf(fp, "/ %f\n",div_SISD(8192));

    fclose (fp);

    printf("Wyniki pomiarow zapisano do pliku wyniki.txt.\n");

	return 0;

}

