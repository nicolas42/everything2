/*
g++ make_primes.cpp -Iinclude -Ofast && ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>



struct u64_array { uint64_t* data; int length; int allocated; }; 
typedef struct u64_array u64_array;

u64_array u64_array_make()
{
    u64_array arr;
    arr.length = 0;
    arr.allocated = 1000;
    arr.data = (uint64_t*)malloc( arr.allocated * sizeof(uint64_t) );
    return arr;
}

void u64_array_add(u64_array *arr, uint64_t item)
{
    if ( arr->length == arr->allocated ) {
      arr->allocated *= 2;
      arr->data = (uint64_t*)realloc( arr->data, arr->allocated * sizeof(uint64_t) );
    }
    arr->data[arr->length] = item;
    arr->length += 1;
}




int is_prime( uint64_t candidate, u64_array primes )
{
    // prime sieve:  divides the candidate number by the already known prime numbers
    // if one of them divides it equally then it's not prime.

    for (uint64_t i=0; i<primes.length; i++){
        if ( candidate % primes.data[i] == 0 ) return 0;
    }
    return 1;
}


u64_array make_primes( int num_to_make )
{
    u64_array primes = u64_array_make();
    u64_array_add( &primes, 2 );
    uint64_t i;

	for ( i=3; i < num_to_make; i+=2){
		if ( is_prime(i, primes) ) {
            u64_array_add( &primes, i );
        }
    }
    for(i=0;i<primes.length;++i) printf("%llu ", primes.data[i]);

    return primes;

}




static sig_atomic_t sigint_flag = 0;

void signal_handler(int signal)
{
    if (signal == SIGINT){
        printf("\nYou handled the SIGINT!\n");
        sigint_flag = 1;
    }
}


u64_array make_primes_with_file(const char *filename)
{
    // register signal handler
    if ( signal(SIGINT, signal_handler) == SIG_ERR ) { 
        printf("\nERROR %s %d registering signal handler\n",__FILE__,__LINE__); 
    }

    u64_array primes = u64_array_make();
    int i;

    // if file exists then read the numbers from it,
    // otherwise create a new file and add 2 and 3 to start off.

    // 2 and 3 are needed since the program starts from the last
    // prime in the list and jumps in twos to the next candidate number.

    FILE *file = fopen(filename, "r");
    if (file){

        fseek(file, 0, SEEK_END); // seek to end of file
        int size = ftell(file);   // get current file pointer
        fseek(file, 0, SEEK_SET); // seek back to beginning of file
        char *str = (char*)malloc(size * sizeof(char));
        fread(str, size, 1, file);
        fclose(file);

        char *pos1 = str;
        char *pos2;
        long ret;

        while (1){
            ret = strtol(pos1, &pos2, 10);
            if (!ret) break;
            pos1 = pos2;
            // printf("The number(unsigned long integer) is %ld\n", ret);
            u64_array_add( &primes, (uint64_t)ret );
        }

    } else {
        u64_array_add( &primes, 2 );
        u64_array_add( &primes, 3 );
        file = fopen(filename, "a");
        fprintf(file, "%llu %llu ", (uint64_t)(2), (uint64_t)(3));
        fclose(file);

    }



    printf("Prime numbers\n");
    printf("----------------\n");
    printf("Outputting results to %s\n", filename);
    printf("\rlast prime generated: %llu", (uint64_t)(primes.data[primes.length-1]));
    fflush(stdout);

    time_t t0 = clock();

    uint64_t limit = (uint64_t)primes.data[primes.length-1] + 1000*1000;
    file = fopen(filename, "a");

	for (uint64_t j = (uint64_t)(primes.data[primes.length-1]); j < limit; j += 2 ) {
        if (sigint_flag) { 
            sigint_flag = 0; 
            return primes; 
        }
		if ( is_prime(j, primes) ) {
            u64_array_add( &primes, j );

            fprintf(file, "%llu ", j);
		}
        // every second print the last prime that was found.
        float time_elapsed = ( clock() - t0 ) / CLOCKS_PER_SEC;
        if ( time_elapsed >= 1.0 ){
			t0 = clock();
		    printf("\rlast prime generated: %llu", (uint64_t)(primes.data[primes.length-1]));
            fflush(stdout);
        }
	}
    return primes;
}







int main()
{
    time_t t0 = clock();

    make_primes(100*1000);
    // make_primes_with_file("primes_gitignore.txt");

    printf("\n\nduration: %f\n", ((double)( clock() - t0 )) / (double)CLOCKS_PER_SEC );

    return 0;
}


