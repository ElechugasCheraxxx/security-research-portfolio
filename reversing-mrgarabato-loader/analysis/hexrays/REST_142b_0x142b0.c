void *__cdecl memmove(void *Dst, const void *Src, size_t MaxCount)
{
  void *v3; // r11
  bool v4; // zf
  bool v5; // cc
  unsigned __int64 v6; // rdx
  size_t v7; // r9
  size_t v8; // r9
  __int64 v10; // rax
  __int64 v11; // r10
  __int64 v12; // r10
  int v13; // eax
  int v14; // eax
  __int64 v15; // r10
  __int64 v16; // r10
  __int64 v17; // r9
  __int64 v18; // r10
  __int64 v19; // r10
  int *v20; // rcx
  size_t v21; // r9
  size_t v22; // r9
  __int64 v23; // rax
  __int64 v24; // r10
  __int64 v25; // r10
  int v26; // eax
  int v27; // eax
  __int64 v28; // r10
  __int64 v29; // r10
  __int64 v30; // r9
  __int64 v31; // r10
  __int64 v32; // r10
  void *retaddr; // [rsp+0h] [rbp+0h] BYREF

  v3 = Dst;
  v4 = Src == Dst;
  v5 = Src <= Dst;
  v6 = (_BYTE *)Src - (_BYTE *)Dst;
  if ( v5 )
  {
    if ( v4 )
      return v3;
    v20 = (int *)((char *)Dst + MaxCount);
    if ( MaxCount >= 8 )
    {
      if ( ((unsigned __int8)v20 & 7) != 0 )
      {
        if ( ((unsigned __int8)v20 & 1) != 0 )
        {
          v20 = (int *)((char *)v20 - 1);
          --MaxCount;
          *(_BYTE *)v20 = *((_BYTE *)v20 + v6);
        }
        if ( ((unsigned __int8)v20 & 2) != 0 )
        {
          v20 = (int *)((char *)v20 - 2);
          MaxCount -= 2LL;
          *(_WORD *)v20 = *(_WORD *)((char *)v20 + v6);
        }
        if ( ((unsigned __int8)v20 & 4) != 0 )
        {
          --v20;
          MaxCount -= 4LL;
          *v20 = *(int *)((char *)v20 + v6);
        }
      }
      while ( 1 )
      {
        v21 = MaxCount >> 5;
        if ( !(MaxCount >> 5) )
          break;
        if ( v21 < 0x800 || v6 > 0xFFFFFFFFFFFFF000uLL )
        {
          do
          {
            v23 = *(_QWORD *)((char *)v20 + v6 - 8);
            v24 = *(_QWORD *)((char *)v20 + v6 - 16);
            v20 -= 8;
            *((_QWORD *)v20 + 3) = v23;
            *((_QWORD *)v20 + 2) = v24;
            v25 = *(_QWORD *)((char *)v20 + v6);
            --v21;
            *((_QWORD *)v20 + 1) = *(_QWORD *)((char *)v20 + v6 + 8);
            *(_QWORD *)v20 = v25;
          }
          while ( v21 );
          MaxCount &= 0x1Fu;
          break;
        }
        do
        {
          v26 = 32;
          do
          {
            v20 -= 32;
            _mm_prefetch((const char *)v20 + v6, 0);
            _mm_prefetch((const char *)v20 + v6 + 64, 0);
            --v26;
          }
          while ( v26 );
          v20 += 1024;
          v27 = 64;
          do
          {
            v28 = *(_QWORD *)((char *)v20 + v6 - 16);
            _mm_stream_si32(v20 - 2, *(_QWORD *)((char *)v20 + v6 - 8));
            _mm_stream_si32(v20 - 4, v28);
            v29 = *(_QWORD *)((char *)v20 + v6 - 32);
            _mm_stream_si32(v20 - 6, *(_QWORD *)((char *)v20 + v6 - 24));
            _mm_stream_si32(v20 - 8, v29);
            v30 = *(_QWORD *)((char *)v20 + v6 - 40);
            v31 = *(_QWORD *)((char *)v20 + v6 - 48);
            v20 -= 16;
            _mm_stream_si32(v20 + 6, v30);
            _mm_stream_si32(v20 + 4, v31);
            v32 = *(_QWORD *)((char *)v20 + v6);
            --v27;
            _mm_stream_si32(v20 + 2, *(_QWORD *)((char *)v20 + v6 + 8));
            _mm_stream_si32(v20, v32);
          }
          while ( v27 );
          MaxCount -= 4096LL;
        }
        while ( MaxCount >= 0x1000 );
        _InterlockedOr8((volatile signed __int8 *)&retaddr, 0);
      }
      v22 = MaxCount >> 3;
      if ( MaxCount >> 3 )
      {
        do
        {
          v20 -= 2;
          --v22;
          *(_QWORD *)v20 = *(_QWORD *)((char *)v20 + v6);
        }
        while ( v22 );
        MaxCount &= 7u;
      }
    }
    if ( MaxCount )
    {
      do
      {
        v20 = (int *)((char *)v20 - 1);
        --MaxCount;
        *(_BYTE *)v20 = *((_BYTE *)v20 + v6);
      }
      while ( MaxCount );
      return v3;
    }
    else
    {
      return v3;
    }
  }
  else
  {
    if ( MaxCount >= 8 )
    {
      if ( ((unsigned __int8)Dst & 7) != 0 )
      {
        if ( ((unsigned __int8)Dst & 1) != 0 )
        {
          --MaxCount;
          *(_BYTE *)Dst = *((_BYTE *)Dst + v6);
          Dst = (char *)Dst + 1;
        }
        if ( ((unsigned __int8)Dst & 2) != 0 )
        {
          MaxCount -= 2LL;
          *(_WORD *)Dst = *(_WORD *)((char *)Dst + v6);
          Dst = (char *)Dst + 2;
        }
        if ( ((unsigned __int8)Dst & 4) != 0 )
        {
          MaxCount -= 4LL;
          *(_DWORD *)Dst = *(_DWORD *)((char *)Dst + v6);
          Dst = (char *)Dst + 4;
        }
      }
      while ( 1 )
      {
        v7 = MaxCount >> 5;
        if ( !(MaxCount >> 5) )
          break;
        if ( v7 < 0x800 || v6 < 0x1000 )
        {
          do
          {
            v10 = *(_QWORD *)((char *)Dst + v6);
            v11 = *(_QWORD *)((char *)Dst + v6 + 8);
            Dst = (char *)Dst + 32;
            *((_QWORD *)Dst - 4) = v10;
            *((_QWORD *)Dst - 3) = v11;
            v12 = *(_QWORD *)((char *)Dst + v6 - 8);
            --v7;
            *((_QWORD *)Dst - 2) = *(_QWORD *)((char *)Dst + v6 - 16);
            *((_QWORD *)Dst - 1) = v12;
          }
          while ( v7 );
          MaxCount &= 0x1Fu;
          break;
        }
        do
        {
          v13 = 32;
          do
          {
            _mm_prefetch((const char *)Dst + v6, 0);
            _mm_prefetch((const char *)Dst + v6 + 64, 0);
            Dst = (char *)Dst + 128;
            --v13;
          }
          while ( v13 );
          Dst = (char *)Dst - 4096;
          v14 = 64;
          do
          {
            v15 = *(_QWORD *)((char *)Dst + v6 + 8);
            _mm_stream_si32((int *)Dst, *(_QWORD *)((char *)Dst + v6));
            _mm_stream_si32((int *)Dst + 2, v15);
            v16 = *(_QWORD *)((char *)Dst + v6 + 24);
            _mm_stream_si32((int *)Dst + 4, *(_QWORD *)((char *)Dst + v6 + 16));
            _mm_stream_si32((int *)Dst + 6, v16);
            v17 = *(_QWORD *)((char *)Dst + v6 + 32);
            v18 = *(_QWORD *)((char *)Dst + v6 + 40);
            Dst = (char *)Dst + 64;
            _mm_stream_si32((int *)Dst - 8, v17);
            _mm_stream_si32((int *)Dst - 6, v18);
            v19 = *(_QWORD *)((char *)Dst + v6 - 8);
            --v14;
            _mm_stream_si32((int *)Dst - 4, *(_QWORD *)((char *)Dst + v6 - 16));
            _mm_stream_si32((int *)Dst - 2, v19);
          }
          while ( v14 );
          MaxCount -= 4096LL;
        }
        while ( MaxCount >= 0x1000 );
        _InterlockedOr8((volatile signed __int8 *)&retaddr, 0);
      }
      v8 = MaxCount >> 3;
      if ( MaxCount >> 3 )
      {
        do
        {
          *(_QWORD *)Dst = *(_QWORD *)((char *)Dst + v6);
          Dst = (char *)Dst + 8;
          --v8;
        }
        while ( v8 );
        MaxCount &= 7u;
      }
    }
    if ( MaxCount )
    {
      do
      {
        *(_BYTE *)Dst = *((_BYTE *)Dst + v6);
        Dst = (char *)Dst + 1;
        --MaxCount;
      }
      while ( MaxCount );
      return v3;
    }
    else
    {
      return v3;
    }
  }
}