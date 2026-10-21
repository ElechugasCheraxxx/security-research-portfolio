char __fastcall _scrt_initialize_onexit_tables(unsigned int a1)
{
  if ( !byte_14000E121 )
  {
    if ( a1 > 1 )
    {
      _scrt_fastfail(5u);
      JUMPOUT(0x1400024AALL);
    }
    if ( !(unsigned int)_scrt_is_ucrt_dll_in_use() || a1 )
    {
      *(__m128i *)&Table._first = _mm_load_si128((const __m128i *)&xmmword_140004490);
      Table._end = (_PVFV *)-1LL;
      *(_OWORD *)&stru_14000E140._first = *(_OWORD *)&Table._first;
      stru_14000E140._end = (_PVFV *)-1LL;
    }
    else if ( initialize_onexit_table(&Table) || initialize_onexit_table(&stru_14000E140) )
    {
      return 0;
    }
    byte_14000E121 = 1;
  }
  return 1;
}