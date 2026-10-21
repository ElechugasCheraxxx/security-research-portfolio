int __fastcall main(int argc, const char **argv, const char **envp)
{
  const CHAR *v3; // rax
  HANDLE FileA; // rax
  void *v5; // rsi
  DWORD FileSize; // eax
  SIZE_T v7; // r14
  HANDLE ProcessHeap; // rax
  int *v10; // rax
  int *v11; // rdi
  int v12; // ebx
  __int64 v13; // rcx
  __int64 Rbp_high; // rax
  __int64 v15; // rcx
  DWORD64 Rdx; // rax
  int v17; // esi
  int v18; // eax
  _BOOL8 v19; // rbx
  char *v20; // rbx
  char *v21; // rax
  char *v22; // r15
  int v23; // esi
  __int64 v24; // r14
  int v25; // eax
  LPVOID *v26; // rsi
  char *v27; // r15
  int v28; // ebx
  __int64 v29; // r14
  HANDLE v30; // rax
  HANDLE v31; // rax
  HANDLE v32; // rax
  HANDLE v33; // rax
  struct _PROCESS_INFORMATION ProcessInformation; // [rsp+60h] [rbp-A8h] BYREF
  __int64 v35; // [rsp+78h] [rbp-90h]
  __int128 Buffer; // [rsp+88h] [rbp-80h] BYREF
  __int128 v37; // [rsp+98h] [rbp-70h] BYREF
  CONTEXT Context; // [rsp+A8h] [rbp-60h] BYREF
  CONTEXT v39; // [rsp+578h] [rbp+470h] BYREF
  WINBOOL Wow64Process; // [rsp+A48h] [rbp+940h] BYREF
  unsigned __int8 OldValue[12]; // [rsp+A4Ch] [rbp+944h] BYREF
  struct _STARTUPINFOA StartupInfo; // [rsp+A58h] [rbp+950h] BYREF

  if ( argc != 3 )
  {
    RtlAdjustPrivilege(0x13u, 1u, 0, OldValue);
    NtRaiseHardError(-1073740768, 0, 0, 0LL, 6u, (PULONG)&Buffer);
    return -1;
  }
  v3 = argv[2];
  qword_14000E768 = (__int64)argv[1];
  lpApplicationName = v3;
  FileA = CreateFileA((LPCSTR)qword_14000E768, 0x80000000, 0, 0LL, 3u, 0, 0LL);
  v5 = FileA;
  if ( FileA == (HANDLE)-1LL )
  {
LABEL_7:
    CloseHandle((HANDLE)0xFFFFFFFFFFFFFFFFLL);
    return -1;
  }
  FileSize = GetFileSize(FileA, 0LL);
  v7 = FileSize;
  if ( FileSize == -1 )
  {
    CloseHandle(v5);
    return -1;
  }
  ProcessHeap = GetProcessHeap();
  v10 = (int *)HeapAlloc(ProcessHeap, 0, v7);
  v11 = v10;
  if ( v10 == (int *)-1LL )
  {
    CloseHandle(v5);
    goto LABEL_7;
  }
  if ( !ReadFile(v5, v10, v7, 0LL, 0LL) )
  {
    CloseHandle(v5);
    if ( v11 )
    {
      CloseHandle(v11);
      return -1;
    }
    return -1;
  }
  CloseHandle(v5);
  if ( !v11 )
    return -1;
  if ( *(int *)((char *)v11 + v11[15]) != 17744 )
  {
    v33 = GetProcessHeap();
    HeapFree(v33, 0, v11);
    return -1;
  }
  StartupInfo.cb = 104;
  v12 = 1;
  v35 = 0LL;
  memset(&StartupInfo.cb + 1, 0, 100);
  *(_OWORD *)&ProcessInformation.hThread = 0LL;
  if ( !CreateProcessA(
          lpApplicationName,
          0LL,
          0LL,
          0LL,
          1,
          4u,
          0LL,
          0LL,
          &StartupInfo,
          (LPPROCESS_INFORMATION)&ProcessInformation.hThread) )
    goto LABEL_72;
  IsWow64Process(ProcessInformation.hThread, &Wow64Process);
  if ( Wow64Process )
  {
    *(_QWORD *)&Buffer = 0LL;
    memset((char *)&Context.P1Home + 4, 0, 0x2C8uLL);
    LODWORD(Context.P1Home) = 1048587;
    Wow64GetThreadContext(*(HANDLE *)&ProcessInformation.dwProcessId, (PWOW64_CONTEXT)&Context);
    if ( ReadProcessMemory(
           ProcessInformation.hThread,
           (LPCVOID)(unsigned int)(HIDWORD(Context.Rbp) + 8),
           &Buffer,
           4uLL,
           0LL) )
    {
      Rbp_high = HIDWORD(Context.Rbp);
      v13 = Buffer;
      *(_QWORD *)&v37 = HIDWORD(Context.Rbp);
      *((_QWORD *)&v37 + 1) = Buffer;
    }
    else
    {
      v37 = 0LL;
      v13 = 0LL;
      Rbp_high = 0LL;
    }
    if ( !v13 || !Rbp_high )
      goto LABEL_72;
  }
  else
  {
    *(_QWORD *)&v37 = 0LL;
    memset(&v39, 0, sizeof(v39));
    v39.ContextFlags = 1048587;
    GetThreadContext(*(HANDLE *)&ProcessInformation.dwProcessId, &v39);
    if ( ReadProcessMemory(ProcessInformation.hThread, (LPCVOID)(v39.Rdx + 16), &v37, 8uLL, 0LL) )
    {
      Rdx = v39.Rdx;
      v15 = v37;
      *(_QWORD *)&Buffer = v39.Rdx;
      *((_QWORD *)&Buffer + 1) = v37;
    }
    else
    {
      Buffer = 0LL;
      v15 = 0LL;
      Rdx = 0LL;
    }
    if ( !v15 || !Rdx )
    {
LABEL_72:
      v32 = GetProcessHeap();
      HeapFree(v32, 0, v11);
      if ( *(_QWORD *)&ProcessInformation.dwProcessId )
        CloseHandle(*(HANDLE *)&ProcessInformation.dwProcessId);
      if ( ProcessInformation.hThread )
      {
        TerminateProcess(ProcessInformation.hThread, 0xFFFFFFFF);
        CloseHandle(ProcessInformation.hThread);
        return -1;
      }
      return -1;
    }
  }
  if ( *(_WORD *)((char *)v11 + v11[15] + 24) == 267 )
  {
    sub_140001050((char *)Format);
    sub_140001050((char *)Format);
    if ( !Wow64Process )
    {
LABEL_28:
      sub_140001050((char *)Format);
      return -1;
    }
  }
  else
  {
    v12 = 0;
    sub_140001050((char *)Format);
    sub_140001050((char *)Format);
    if ( Wow64Process )
      goto LABEL_28;
  }
  sub_140001050((char *)Format);
  v17 = *(unsigned __int16 *)((char *)v11 + v11[15] + 92);
  if ( Wow64Process )
    v18 = sub_1400010B0(ProcessInformation.hThread);
  else
    v18 = sub_1400011F0(ProcessInformation.hThread);
  if ( v18 == -1 )
    goto LABEL_72;
  if ( v17 != v18 )
  {
    sub_140001050((char *)Format);
    goto LABEL_72;
  }
  sub_140001050((char *)Format);
  if ( v12 )
  {
    v19 = *(int *)((char *)v11 + v11[15] + 160) != 0;
    sub_140001050((char *)Format);
    if ( !v19 )
    {
      v20 = (char *)v11 + v11[15];
      v21 = (char *)VirtualAllocEx(
                      ProcessInformation.hThread,
                      (LPVOID)*((unsigned int *)v20 + 13),
                      *((unsigned int *)v20 + 20),
                      0x3000u,
                      0x40u);
      v22 = v21;
      if ( v21 && WriteProcessMemory(ProcessInformation.hThread, v21, v11, *((unsigned int *)v20 + 21), 0LL) )
      {
        v23 = 0;
        if ( *((_WORD *)v20 + 3) )
        {
          v24 = 0LL;
          while ( WriteProcessMemory(
                    ProcessInformation.hThread,
                    &v22[*(unsigned int *)&v20[v24 + 36 + *((unsigned __int16 *)v20 + 10)]],
                    (char *)v11 + *(unsigned int *)&v20[v24 + 44 + *((unsigned __int16 *)v20 + 10)],
                    *(unsigned int *)&v20[v24 + 40 + *((unsigned __int16 *)v20 + 10)],
                    0LL) )
          {
            ++v23;
            v24 += 40LL;
            if ( v23 >= *((unsigned __int16 *)v20 + 3) )
              goto LABEL_43;
          }
          goto LABEL_66;
        }
LABEL_43:
        memset((char *)&Context.P1Home + 4, 0, 0x2C8uLL);
        LODWORD(Context.P1Home) = 1048587;
        if ( Wow64GetThreadContext(*(HANDLE *)&ProcessInformation.dwProcessId, (PWOW64_CONTEXT)&Context) )
        {
          if ( WriteProcessMemory(ProcessInformation.hThread, (LPVOID)(HIDWORD(Context.Rbp) + 8LL), v20 + 52, 4uLL, 0LL) )
          {
            LODWORD(Context.Rdi) = (_DWORD)v22 + *((_DWORD *)v20 + 10);
            if ( Wow64SetThreadContext(*(HANDLE *)&ProcessInformation.dwProcessId, (const WOW64_CONTEXT *)&Context) )
              goto LABEL_46;
          }
        }
      }
      goto LABEL_66;
    }
    v25 = sub_140001340(&ProcessInformation.hThread, v11);
LABEL_60:
    if ( v25 )
      goto LABEL_61;
    goto LABEL_66;
  }
  if ( *(int *)((char *)v11 + v11[15] + 176) )
  {
    sub_140001050((char *)Format);
    v25 = sub_140001640(&ProcessInformation.hThread, v11);
    goto LABEL_60;
  }
  sub_140001050((char *)Format);
  v26 = (LPVOID *)((char *)v11 + v11[15]);
  v27 = (char *)VirtualAllocEx(ProcessInformation.hThread, v26[6], *((unsigned int *)v26 + 20), 0x3000u, 0x40u);
  if ( v27 && WriteProcessMemory(ProcessInformation.hThread, v27, v11, *((unsigned int *)v26 + 21), 0LL) )
  {
    v28 = 0;
    if ( *((_WORD *)v26 + 3) )
    {
      v29 = 0LL;
      while ( WriteProcessMemory(
                ProcessInformation.hThread,
                &v27[*(unsigned int *)((char *)&v26[v29 + 4] + *((unsigned __int16 *)v26 + 10) + 4)],
                (char *)v11 + *(unsigned int *)((char *)&v26[v29 + 5] + *((unsigned __int16 *)v26 + 10) + 4),
                *(unsigned int *)((char *)&v26[v29 + 5] + *((unsigned __int16 *)v26 + 10)),
                0LL) )
      {
        ++v28;
        v29 += 5LL;
        if ( v28 >= *((unsigned __int16 *)v26 + 3) )
          goto LABEL_56;
      }
      goto LABEL_66;
    }
LABEL_56:
    memset(&Context, 0, sizeof(Context));
    Context.ContextFlags = 1048587;
    if ( GetThreadContext(*(HANDLE *)&ProcessInformation.dwProcessId, &Context) )
    {
      if ( WriteProcessMemory(ProcessInformation.hThread, (LPVOID)(Context.Rdx + 16), v26 + 6, 8uLL, 0LL) )
      {
        Context.Rcx = (DWORD64)&v27[*((unsigned int *)v26 + 10)];
        if ( SetThreadContext(*(HANDLE *)&ProcessInformation.dwProcessId, &Context) )
        {
LABEL_46:
          ResumeThread(*(HANDLE *)&ProcessInformation.dwProcessId);
LABEL_61:
          v30 = GetProcessHeap();
          HeapFree(v30, 0, v11);
          if ( *(_QWORD *)&ProcessInformation.dwProcessId )
            CloseHandle(*(HANDLE *)&ProcessInformation.dwProcessId);
          if ( ProcessInformation.hThread )
            CloseHandle(ProcessInformation.hThread);
          return 0;
        }
      }
    }
  }
LABEL_66:
  v31 = GetProcessHeap();
  HeapFree(v31, 0, v11);
  if ( *(_QWORD *)&ProcessInformation.dwProcessId )
    CloseHandle(*(HANDLE *)&ProcessInformation.dwProcessId);
  if ( ProcessInformation.hThread )
  {
    TerminateProcess(ProcessInformation.hThread, 0xFFFFFFFF);
    CloseHandle(ProcessInformation.hThread);
  }
  return -1;
}