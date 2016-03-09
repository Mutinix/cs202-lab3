int thread_create(void *(*start_routine)(void*), void *arg);

// Mutual exclusion lock.
struct lock_t {
  uint locked;       // Is the lock held?
};

void lock_init(struct lock_t *lk);
void lock_acquire(struct lock_t *lk);
void lock_release(struct lock_t *lk);
void thread_join();