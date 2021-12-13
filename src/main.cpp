#include "main.h"
#include <sys/ipc.h>
#include <sys/shm.h>

#define REMOVE false

typedef struct datas
{
    int count;
    char str[20];
} datas;

int main()
{
    int shmid;
    datas *d;
    key_t key = 987654;
    void *memory_segment = NULL;

    if ((shmid = shmget(key, sizeof(datas), IPC_CREAT | 0666)) == -1)
    {
        printf("shmget failed\n");
        exit(0);
    }
    #if REMOVE 
    if (-1 == shmctl(shmid, IPC_RMID, 0))
    {
        printf("공유 메모리 제거 실패\n");
        return -1;
    }
    else
    {
        printf("공유 메모리 제거 성공\n");
    }
    #endif
    
    if ((memory_segment = shmat(shmid, NULL, 0)) == (void *)-1)
    {
        printf("shmat failed\n");
        exit(0);
    }

    d = (struct datas *)memory_segment;
    (*d).count++;
    char text[20] = "Hello World";
    snprintf((*d).str,sizeof((*d).str), text);

    std::cout << "sended" << std::endl;
    
    return 0;
}