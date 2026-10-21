__int64 __fastcall sub_11ED0(volatile signed __int32 *a1)
{
  if ( a1 )
    return (unsigned int)_InterlockedIncrement(a1);
  else
    return 0LL;
}