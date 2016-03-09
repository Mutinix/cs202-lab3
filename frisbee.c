#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "thread.h"

typedef struct arg_struct
{
  int *number_of_passes;
  struct lock_t *lk;
} fris_struct;

void *pass_frisbee(void *arg)
{
  fris_struct *n_arg = (fris_struct *) arg;

  int i;
  for(i = 0; i < *n_arg->number_of_passes; i++)
  {
    lock_acquire(n_arg->lk);
    printf(2, "Fly!\n");
    lock_release(n_arg->lk);
  }

  return 0;
}

int
main(int argc, char *argv[])
{
  if(argc != 3)
  {
    printf(2, "usage: frisbee <numberofthreads> <numberofpasses>\n");
    exit();
  }

  int number_of_threads = atoi(argv[1]);
  int number_of_passes = atoi(argv[2]);

  struct lock_t lk;
  lock_init(&lk);

  fris_struct arg;
  arg.number_of_passes = &number_of_passes;
  arg.lk = &lk;

  void *args = (void *) &arg;
  int i;
  for(i = 0; i < number_of_threads; i++)
  {
    thread_create(pass_frisbee, args);
  }

  for(i = 0; i < number_of_threads; i++)
  {
    thread_join();
  }
  exit();
}