void __fastcall sub_12770(const void *a1, __int64 a2)
{
  const void *v3; // rdx
  __int64 *v4; // r8
  __int64 v5; // rax
  const char *v6; // rcx
  __int64 v7; // rbx

  v3 = a1;
  if ( a1 )
  {
    if ( a2 )
    {
      v6 = (const char *)&unk_17188;
      v5 = 0LL;
      while ( 1 )
      {
        _mm_prefetch(v6 + 960, 1);
        if ( a2 == *(_QWORD *)v6 && v3 == *((const void **)v6 - 1) )
          break;
        v5 = (unsigned int)(v5 + 1);
        v6 += 80;
        if ( (unsigned int)v5 >= 0xC350 )
        {
LABEL_6:
          sub_11F30(
            "_NalFreeMemoryNonPagedEx: Memory entry 0x%p is not entered into the table. Not freeing anything.\n",
            v3);
          return;
        }
      }
    }
    else
    {
      v4 = qword_17150;
      v5 = 0LL;
      while ( 1 )
      {
        _mm_prefetch((const char *)v4 + 960, 1);
        if ( a1 == (const void *)*v4 )
          break;
        v5 = (unsigned int)(v5 + 1);
        v4 += 10;
        if ( (unsigned int)v5 >= 0xC350 )
          goto LABEL_6;
      }
    }
    v7 = 10 * v5;
    if ( *((_QWORD *)&unk_17140 + 10 * v5 + 1) )
    {
      if ( a2 )
      {
        v3 = (const void *)*((_QWORD *)&unk_17140 + 10 * v5 + 6);
        if ( v3 )
        {
          MmUnmapLockedPages(*((_QWORD *)&unk_17140 + 10 * v5 + 7));
          IoFreeMdl(*((_QWORD *)&unk_17140 + v7 + 6));
        }
      }
      MmFreeContiguousMemory(*((_QWORD *)&unk_17140 + v7 + 1), v3);
    }
    *((_QWORD *)&unk_17140 + v7 + 3) = 0LL;
    *((_QWORD *)&unk_17140 + v7 + 2) = 0LL;
    *((_DWORD *)&unk_17140 + 2 * v7 + 10) = 0;
    *((_DWORD *)&unk_17140 + 2 * v7 + 11) = 0;
    *((_QWORD *)&unk_17140 + v7 + 4) = 0LL;
    *((_QWORD *)&unk_17140 + v7 + 1) = 0LL;
    *((_QWORD *)&unk_17140 + v7 + 6) = 0LL;
    *((_QWORD *)&unk_17140 + v7 + 7) = 0LL;
    *((_QWORD *)&unk_17140 + v7 + 8) = 0LL;
    *((_QWORD *)&unk_17140 + v7 + 9) = 0LL;
    _InterlockedCompareExchange((volatile signed __int32 *)&unk_17140 + 2 * v7, 0, 1);
  }
}