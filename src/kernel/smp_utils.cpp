#include <smp_utils>
#include <smp>

void smp_spinlock::lock()
{
  while (!__sync_bool_compare_and_swap(&m_value, 0, 1)) {
	while (m_value) _mm_pause();
  }
}
void smp_spinlock::unlock()
{
  __sync_lock_release(&m_value, 0);
}

void smp_barrier::spin_wait(int max) noexcept
{
  __sync_synchronize();
  while (this->val < max) {
	_mm_pause();
  }
}
