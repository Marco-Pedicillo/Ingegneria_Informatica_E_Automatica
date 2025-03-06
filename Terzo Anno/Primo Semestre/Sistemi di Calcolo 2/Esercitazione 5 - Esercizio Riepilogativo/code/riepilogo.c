#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

// macros for error handling
#include "common.h"

#define N 100   // child process count
#define M 10    // thread per child process count
#define T 3     // time to sleep for main process

#define SHM_NAME "/shmem_notification"
#define MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME "/main_waits_for_children"
#define CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME "/children_wait_for_main"
#define CRITICAL_SECTION "/critical_section"

#define FILENAME	"accesses.log"

/*
 * data structure required by threads
 */
typedef struct thread_args_s {
    unsigned int child_id;
    unsigned int thread_id;
} thread_args_t;

/*
 * parameters can be set also via command-line arguments
 */
int n = N, m = M, t = T;

/* TODO: declare as many semaphores as needed to implement
 * the intended semantics, and choose unique identifiers for
 * them (e.g., "/mysem_critical_section") */

sem_t *main_waits_for_children = NULL;
sem_t *children_wait_for_main = NULL;
sem_t *critical_section = NULL;

/* TODO: declare a shared memory and the data type to be placed 
 * in the shared memory, and choose a unique identifier for
 * the memory (e.g., "/myshm") 
 * Declare any global variable (file descriptor, memory 
 * pointers, etc.) needed for its management
 */

int shm_fd;
int *data;


/*
 * Ensures that an empty file with given name exists.
 */
void init_file(const char *filename) {
    printf("[Main] Initializing file %s...", FILENAME);
    fflush(stdout);
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd<0) handle_error("error while initializing file");
    close(fd);
    printf("closed...file correctly initialized!!!\n");
}

/*
 * Create a named semaphore with a given name, mode and initial value.
 * Also, tries to remove any pre-existing semaphore with the same name.
 */
sem_t *create_named_semaphore(const char *name, mode_t mode, unsigned int value) {
    printf("[Main] Creating named semaphore %s...", name);
    fflush(stdout);
    
    // TODO

    sem_unlink(name);
    sem_t* sem = sem_open(name, O_CREAT | O_EXCL, mode, value);
    if(sem = SEM_FAILED) handle_error("errore creazione semaforo named");

    printf("done!!!\n");
    return NULL;
}



void parseOutput() {
    // identify the child that accessed the file most times
    int* access_stats = calloc(n, sizeof(int)); // initialized with zeros
    printf("[Main] Opening file %s in read-only mode...", FILENAME);
	fflush(stdout);
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) handle_error("error while opening output file");
    printf("ok, reading it and updating access stats...");
	fflush(stdout);

    size_t read_bytes;
    int index;
    do {
        read_bytes = read(fd, &index, sizeof(int));
        if (read_bytes > 0)
            access_stats[index]++;
    } while(read_bytes > 0);
    printf("ok, closing it...");
	fflush(stdout);

    close(fd);
    printf("closed!!!\n");

    int max_child_id = -1, max_accesses = -1;
    for (i = 0; i < n; i++) {
        printf("[Main] Child %d accessed file %s %d times\n", i, FILENAME, access_stats[i]);
        if (access_stats[i] > max_accesses) {
            max_accesses = access_stats[i];
            max_child_id = i;
        }
    }
    printf("[Main] ===> The process that accessed the file most often is %d (%d accesses)\n", max_child_id, max_accesses);
    free(access_stats);
}

void* thread_function(void* x) {
    thread_args_t *args = (thread_args_t*)x;

    /* TODO: protect the critical section using semaphore(s) as needed */

    int ret = sem_wait(critical_section);
    if(ret) handle_error("sem_wait fallita");
    printf("[Child#%d-Thread#%d] Entered into critical section!!!\n", args->child_id, args->thread_id);

    // open file, write child identity and close file
    int fd = open(FILENAME, O_WRONLY | O_APPEND);
    if (fd < 0) handle_error("error while opening file");
    printf("[Child#%d-Thread#%d] File %s opened in append mode!!!\n", args->child_id, args->thread_id, FILENAME);	

    write(fd, &(args->child_id), sizeof(int));
    printf("[Child#%d-Thread#%d] %d appended to file %s opened in append mode!!!\n", args->child_id, args->thread_id, args->child_id, FILENAME);	

    close(fd);
    printf("[Child#%d-Thread#%d] File %s closed!!!\n", args->child_id, args->thread_id, FILENAME);

    ret = sem_post(critical_section);
    if(ret) handle_error("sem_post fallita");

    printf("[Child#%d-Thread#%d] Exited from critical section!!!\n", args->child_id, args->thread_id);

    printf("[Child#%d-Thread#%d] Completed!!!\n", args->child_id, args->thread_id);
    free(args);

    free(args);
    pthread_exit(NULL);
}

void mainProcess() {
    /* TODO: the main process waits for all the children to start,
     * it notifies them to start their activities, and sleeps
     * for some time t. Once it wakes up, it notifies the children
     * to end their activities, and waits for their termination.
     * Finally, it calls the parseOutput() method and releases
     * any shared resources. */

    int i, ret;
    
    printf("%d figli creati, aspetto che tutti i figli siano pronti\n", n);
    for(i=0; i<n; i++){
        ret = sem_wait(main_waits_for_children);
        if(ret) handle_error("errore wait main_waits_for_children");
    }
    printf("tutti i figli sono pronti\n");

    printf("notifica l'avvio di ogni figlio\n");
    for(i=0; i<n; i++){
        ret = sem_post(children_wait_for_main);
        if(ret) handle_error("errore post children_wait_for_main");
    }
    printf("tutti i figli hanno notificato il loro avvio\n");

    printf("[Main] Sleeping for %d seconds...\n", t);
    sleep(t);
    printf("[Main] Woke up after having slept for %d seconds!!!\n", t);

    printf("[Main] Notifying children to end their activities...\n");
    *data = 1;
	printf("[Main] Children have been notified to end their activities!!!\n");

    printf("[Main] Waiting for all the children to terminate...\n");
    int child_status;
    for(i=0; i<n; i++){
        ret = wait(&child_status);
        if(ret == -1) handle_error("wait fallita");
        if(WEXITSTATUS(child_status)){
            fprintf(stderr, "errore figlio morto con codice %d\n", WEXITSTATUS(child_status));
            exit(EXIT_FAILURE);
        }
    }
    printf("[Main] All the children have terminated!!!\n");

    parseOutput();


   ret = close(shm_fd);
	  if (ret == -1)
        handle_error("main: cannot close the shared memory");

    if (munmap(data, sizeof(int))==-1)
        handle_error("main unmap");

    shm_unlink(SHM_NAME);

    ret = sem_close(main_waits_for_children);
	if(ret) {
	    handle_error("sem_close failed");
    }

    ret = sem_unlink(MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME);
	if(ret) {
	    handle_error("sem_unlink failed");
    }

    ret = sem_close(children_wait_for_main);
	if(ret) {
	    handle_error("sem_close failed");
    }

    ret = sem_unlink(CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME);
	if(ret) {
	    handle_error("sem_unlink failed");
	}

    ret = sem_close(critical_section);
	if(ret) {
	    handle_error("sem_close failed");
    }
    ret = sem_unlink(CRITICAL_SECTION);
	if(ret) {
	    handle_error("sem_unlink failed");
	}

}

void childProcess(int child_id) {
    /* TODO: each child process notifies the main process that it
     * is ready, then waits to be notified from the main in order
     * to start. As long as the main process does not notify a
     * termination event [hint: use sem_getvalue() here], the child
     * process repeatedly creates m threads that execute function
     * thread_function() and waits for their completion. When a
     * notification has arrived, the child process notifies the main
     * process that it is about to terminate, and releases any
     * shared resources before exiting. */

    int ret;

    printf("processo figlio %d inizializzato\n", child_id);
    ret = sem_post(main_waits_for_children);
    if(ret) handle_error("errore post main_waits_for_children");
    printf("[Child#%d] Main process notified that I am ready!!!\n", child_id);

    ret = sem_wait(children_wait_for_main);
    if(ret) handle_error("sem_wait failed");
    printf("[Child#%d] Notification to begin received!!!\n", child_id);

    unsigned int thread_id = 0;
    pthread_t* thread_handlers = malloc(m * sizeof(pthread_t));

    do{
        int j;

        memset(thread_handlers, 0, m * sizeof(pthread_t));

        printf("[Child#%d] Creating %d threads...\n", child_id, m);
        for(j=0; j<m; j++){
            thread_args_s *t_args = (thread_args_t *)malloc(sizeof(thread_args_t));
             t_args ->  child_id = child_id;
             t_args -> thread_id = thread_id++;
             ret = pthread_create(&thread_handlers[j], NULL, thread_function, t_args);
             if(ret) handle_error_en(ret, "pthread_create fallita");
        }
        printf("[Child#%d] %d threads created!!!\n", child_id, m);

        printf("[Child#%d] Waiting for the end of the %d threads...\n", child_id, m);
        for(j=0; j<m; j++){
            ret = pthread_join(thread_handlers[j], NULL);
            if(ret) handle_error_en(ret, "pthread_join fallita");
        }
        printf("[Child#%d] %d threads completed!!!\n", child_id, m);

        printf("[Child#%d] Checking for end activities notification...\n", child_id);

        if (*data) break;

        printf("[Child#%d] Go on with activities!!!\n", child_id);
    }while(1);

    free(thread_handlers);
    
    printf("[Child#%d] Activities completed!!!\n", child_id);


    if (munmap(data, sizeof(int))==-1)
        handle_error("main unmap");
     ret = close(shm_fd);
    
    if (ret == -1)
        handle_error("main: cannot close the shared memory");

    ret = sem_close(main_waits_for_children);
	if(ret) {
	    handle_error("sem_close failed");
    }

    ret = sem_close(children_wait_for_main);
	if(ret) {
	    handle_error("sem_close failed");
    }

    ret = sem_close(critical_section);
	if(ret){
	    handle_error("sem_close failed");
	}
}

int main(int argc, char **argv) {
    // arguments
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) m = atoi(argv[2]);
    if (argc > 3) t = atoi(argv[3]);

    int i;

    shm_unlink(SHM_NAME);

    if((shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666)) == -1)
        handle_error("errore shm_open");
    if(ftruncate(shm_fd, sizeof(int)) == -1)
        handle_error("errore ftruncate");
    if((data = (int*) mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
        handle_error("errore mmap");
    *data = 0;

    main_waits_for_children = create_named_semaphore(MAIN_WAITS_FOR_CHILDREN_SEMAPHORE_NAME, 0600, 0);
    children_wait_for_main = create_named_semaphore(CHILDREN_WAIT_FOR_MAIN_SEMAPHORE_NAME, 0600, 0);
    critical_section = create_named_semaphore(CRITICAL_SECTION, 0600, 1);

    // initialize the file
    init_file(FILENAME);

    /* TODO: initialize any semaphore needed in the implementation, and
     * create N children where the i-th child calls childProcess(i); 
     * initialize the shared memory (create it, set its size and map it in the 
     * memory), then the main process executes function mainProcess() once 
     * all the children have been created */

    for(i=0; i<n; i++){
        pid_t pid = fork();
        if(pid == -1){
            printf("errore creazione processo figlio n%d: %s\n", i, strerror(errno));
            exit(EXIT_FAILURE);
        }else if(pid == 0){
            printf("processo figlio n%d creato con pid: %d\n", i, getpid());
            childProcess(i);
            exit(EXIT_FAILURE);
        }
    }

    mainProcess();

    exit(EXIT_SUCCESS);
}