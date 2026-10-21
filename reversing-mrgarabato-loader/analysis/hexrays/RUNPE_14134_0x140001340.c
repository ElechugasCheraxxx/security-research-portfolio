__int64 __fastcall sub_140001340(HANDLE *a1, int *a2)
{
  char *v3; // r15
  void *v5; // rax
  SIZE_T v6; // r9
  int v7; // ecx
  __int64 v8; // rbx
  __int64 v9; // rbx
  char *v10; // rbp
  int v11; // esi
  __int64 i; // rdi
  char *v13; // rdx
  __int64 v14; // r10
  unsigned int v15; // r9d
  int v16; // r15d
  __int64 v17; // r12
  unsigned int *v18; // r12
  unsigned __int64 v19; // rax
  unsigned int v20; // edx
  __int64 v21; // rsi
  __int64 v22; // rcx
  char *v23; // rdi
  HANDLE v24; // rcx
  HANDLE v25; // rcx
  char *v27; // [rsp+38h] [rbp-330h]
  void *lpBaseAddress[2]; // [rsp+40h] [rbp-328h] BYREF
  struct _WOW64_CONTEXT Context; // [rsp+50h] [rbp-318h] BYREF
  int Buffer; // [rsp+320h] [rbp-48h] BYREF

  v3 = (char *)a2 + a2[15];
  v27 = v3;
  v5 = VirtualAllocEx(*a1, 0LL, *((unsigned int *)v3 + 20), 0x3000u, 0x40u);
  lpBaseAddress[0] = v5;
  if ( v5 )
  {
    v6 = *((unsigned int *)v3 + 21);
    v7 = (_DWORD)v5 - *((_DWORD *)v3 + 13);
    *((_DWORD *)v3 + 13) = (_DWORD)v5;
    Buffer = v7;
    if ( WriteProcessMemory(*a1, lpBaseAddress[0], a2, v6, 0LL) )
    {
      v8 = a2[15];
      v9 = *(int *)((char *)a2 + v8 + 160) ? *(_QWORD *)((char *)a2 + v8 + 160) : 0LL;
      v10 = 0LL;
      v11 = 0;
      if ( *((_WORD *)v3 + 3) )
      {
        for ( i = 0LL; ; i += 40LL )
        {
          v13 = &v3[i + 24 + *((unsigned __int16 *)v3 + 10)];
          v14 = *((unsigned int *)v13 + 3);
          if ( (unsigned int)v9 >= (unsigned int)v14 && (unsigned int)v9 < (int)v14 + *((_DWORD *)v13 + 2) )
            v10 = &v3[i + 24 + *((unsigned __int16 *)v3 + 10)];
          if ( !WriteProcessMemory(
                  *a1,
                  (char *)lpBaseAddress[0] + v14,
                  (char *)a2 + *((unsigned int *)v13 + 5),
                  *((unsigned int *)v13 + 4),
                  0LL) )
            break;
          if ( ++v11 >= *((unsigned __int16 *)v3 + 3) )
          {
            if ( v10 )
            {
              LODWORD(v9) = 0;
              if ( HIDWORD(v9) )
              {
                v15 = *((_DWORD *)v10 + 5);
                v16 = Buffer;
                do
                {
                  v17 = (unsigned int)v9;
                  LODWORD(v9) = v9 + 8;
                  v18 = (unsigned int *)((char *)a2 + v15 + v17);
                  v19 = ((unsigned __int64)v18[1] - 8) >> 1;
                  if ( (_DWORD)v19 )
                  {
                    v20 = v15;
                    v21 = (unsigned int)v19;
                    do
                    {
                      v22 = (unsigned int)v9;
                      LODWORD(v9) = v9 + 2;
                      if ( *(_WORD *)((char *)a2 + v20 + v22) >= 0x1000u )
                      {
                        v23 = (char *)lpBaseAddress[0] + (*(_WORD *)((_BYTE *)a2 + v20 + v22) & 0xFFF) + *v18;
                        Buffer = 0;
                        ReadProcessMemory(*a1, v23, &Buffer, 4uLL, 0LL);
                        v24 = *a1;
                        Buffer += v16;
                        WriteProcessMemory(v24, v23, &Buffer, 4uLL, 0LL);
                        v15 = *((_DWORD *)v10 + 5);
                        v20 = v15;
                      }
                      --v21;
                    }
                    while ( v21 );
                  }
                }
                while ( (unsigned int)v9 < HIDWORD(v9) );
                v3 = v27;
              }
              memset(&Context.Dr0, 0, 0x2C8uLL);
              v25 = a1[1];
              Context.ContextFlags = 1048587;
              if ( Wow64GetThreadContext(v25, &Context) )
              {
                if ( WriteProcessMemory(*a1, (LPVOID)(Context.Ebx + 8LL), lpBaseAddress, 4uLL, 0LL) )
                {
                  Context.Eax = LODWORD(lpBaseAddress[0]) + *((_DWORD *)v3 + 10);
                  if ( Wow64SetThreadContext(a1[1], &Context) )
                  {
                    ResumeThread(a1[1]);
                    return 1LL;
                  }
                }
              }
            }
            return 0LL;
          }
        }
      }
    }
  }
  return 0LL;
}