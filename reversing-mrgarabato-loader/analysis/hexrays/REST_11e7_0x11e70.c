void *__fastcall sub_11E70(void *a1, unsigned __int8 a2, size_t a3)
{
  if ( KeGetCurrentIrql() <= 2u )
    memset(a1, a2, a3);
  return a1;
}