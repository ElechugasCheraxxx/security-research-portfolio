void *__fastcall sub_11EA0(void *a1, const void *a2, size_t a3)
{
  if ( KeGetCurrentIrql() <= 2u )
    memmove(a1, a2, a3);
  return a1;
}