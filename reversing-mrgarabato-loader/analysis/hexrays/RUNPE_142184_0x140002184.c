__int64 __fastcall sub_140002184(__int64 a1)
{
  signed int LastError; // eax
  signed int v3; // ecx

  memset((void *)(a1 + 40), 0, 0x28uLL);
  *(_QWORD *)(a1 + 80) = 0LL;
  *(_DWORD *)(a1 + 88) = 0;
  *(_DWORD *)(a1 + 92) = 0;
  *(_QWORD *)(a1 + 16) = 0x140000000uLL;
  *(_QWORD *)(a1 + 8) = 0x140000000uLL;
  *(_QWORD *)(a1 + 32) = &unk_140004340;
  *(_DWORD *)a1 = 96;
  *(_DWORD *)(a1 + 24) = 3584;
  if ( !InitializeCriticalSectionEx((LPCRITICAL_SECTION)(a1 + 40), 0, 0) )
  {
    LastError = GetLastError();
    v3 = (unsigned __int16)LastError | 0x80070000;
    if ( LastError <= 0 )
      v3 = LastError;
    if ( v3 < 0 )
    {
      if ( IsDebuggerPresent() )
        OutputDebugStringW(L"ERROR : Unable to initialize critical section in CAtlBaseModule\n");
      byte_14000E6F8 = 1;
    }
  }
  return a1;
}