__int64 __fastcall sub_11EF0(volatile signed __int32 *a1)
{
  if ( a1 )
    return (unsigned int)_InterlockedDecrement(a1);
  else
    return 0LL;
}