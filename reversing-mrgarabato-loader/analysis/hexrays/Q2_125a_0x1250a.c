__int64 sub_12450()
{
  __int64 result; // rax
  __int64 v1; // rsi
  __int64 PerformanceCounter; // rbp
  unsigned int v3; // ebx
  __int64 v4; // rdi

  result = qword_17130;
  if ( !qword_17130 )
  {
    KeQueryPerformanceCounter(0LL);
    v1 = 1000LL;
    PerformanceCounter = KeQueryPerformanceCounter(0LL);
    do
    {
      v3 = 100;
      v4 = 2LL;
      do
      {
        KeStallExecutionProcessor(50LL);
        v3 -= 50;
        --v4;
      }
      while ( v4 );
      if ( v3 )
        KeStallExecutionProcessor(v3);
      --v1;
    }
    while ( v1 );
    qword_17130 = (KeQueryPerformanceCounter(0LL) - PerformanceCounter) / 0x186A0uLL;
    return qword_17130;
  }
  return result;
}