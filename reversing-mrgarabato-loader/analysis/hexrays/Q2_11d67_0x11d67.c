__int64 __fastcall sub_11D50(unsigned int a1)
{
  unsigned int v1; // ebx
  __int64 result; // rax
  __int64 v3; // rdi

  v1 = a1;
  result = 1374389535 * a1;
  if ( a1 / 0x32 )
  {
    v3 = a1 / 0x32;
    do
    {
      result = KeStallExecutionProcessor(50LL);
      v1 -= 50;
      --v3;
    }
    while ( v3 );
  }
  if ( v1 )
    return KeStallExecutionProcessor(v1);
  return result;
}