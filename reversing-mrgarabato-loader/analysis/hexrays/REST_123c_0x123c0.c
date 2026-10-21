__int64 __fastcall sub_123C0(unsigned int a1)
{
  __int64 v2; // rsi
  __int64 result; // rax
  unsigned int v4; // ebp
  unsigned int v5; // ebx
  __int64 v6; // rdi

  v2 = 1000LL;
  result = 1374389535 * a1;
  v4 = a1 / 0x32;
  do
  {
    v5 = a1;
    if ( v4 )
    {
      v6 = v4;
      do
      {
        result = KeStallExecutionProcessor(50LL);
        v5 -= 50;
        --v6;
      }
      while ( v6 );
    }
    if ( v5 )
      result = KeStallExecutionProcessor(v5);
    --v2;
  }
  while ( v2 );
  return result;
}