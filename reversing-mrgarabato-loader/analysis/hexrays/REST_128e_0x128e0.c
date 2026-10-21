void __fastcall sub_128E0(const void *a1)
{
  __int64 *v1; // rax
  __int64 v2; // rdx
  __int64 v3; // rbx
  __int64 v4; // rcx

  if ( a1 )
  {
    v1 = qword_17150;
    v2 = 0LL;
    while ( 1 )
    {
      _mm_prefetch((const char *)v1 + 960, 1);
      if ( a1 == (const void *)*v1 )
        break;
      v2 = (unsigned int)(v2 + 1);
      v1 += 10;
      if ( (unsigned int)v2 >= 0xC350 )
      {
        sub_11F30(
          "_NalFreeMemoryNonPagedEx: Memory entry 0x%p is not entered into the table. Not freeing anything.\n",
          a1);
        return;
      }
    }
    v3 = 10LL * (unsigned int)v2;
    v4 = *((_QWORD *)&unk_17140 + 10 * (unsigned int)v2 + 1);
    if ( v4 )
      MmFreeContiguousMemory(v4, v2);
    *((_QWORD *)&unk_17140 + v3 + 3) = 0LL;
    *((_QWORD *)&unk_17140 + v3 + 2) = 0LL;
    *((_DWORD *)&unk_17140 + 2 * v3 + 10) = 0;
    *((_DWORD *)&unk_17140 + 2 * v3 + 11) = 0;
    *((_QWORD *)&unk_17140 + v3 + 4) = 0LL;
    *((_QWORD *)&unk_17140 + v3 + 1) = 0LL;
    *((_QWORD *)&unk_17140 + v3 + 6) = 0LL;
    *((_QWORD *)&unk_17140 + v3 + 7) = 0LL;
    *((_QWORD *)&unk_17140 + v3 + 8) = 0LL;
    *((_QWORD *)&unk_17140 + v3 + 9) = 0LL;
    _InterlockedCompareExchange((volatile signed __int32 *)&unk_17140 + 2 * v3, 0, 1);
  }
}