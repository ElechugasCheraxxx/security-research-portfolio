__int64 __fastcall sub_11F10(volatile signed __int32 *a1, signed __int32 a2, signed __int32 a3)
{
  if ( a1 )
    return (unsigned int)_InterlockedCompareExchange(a1, a3, a2);
  else
    return 0LL;
}