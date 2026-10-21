__int64 __fastcall sub_12D70(__int64 a1)
{
  __int64 v1; // rdi
  char v3; // bp
  ULONG v4; // r12d
  __int64 v5; // rax
  __int64 v6; // rdx
  NTSTATUS v7; // r13d
  char v8; // di
  __int64 PoolWithTag; // rsi
  __int64 v10; // r8
  __int64 v11; // rcx
  __int64 v12; // rdx
  char v13; // al
  unsigned int v14; // edx
  __int64 v15; // rcx
  __int64 v16; // rax
  ULONG ResultLength; // [rsp+40h] [rbp-1D8h] BYREF
  void *KeyHandle; // [rsp+48h] [rbp-1D0h] BYREF
  struct _STRING AnsiString; // [rsp+50h] [rbp-1C8h] BYREF
  struct _OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+60h] [rbp-1B8h] BYREF
  UNICODE_STRING SourceString; // [rsp+90h] [rbp-188h] BYREF
  char v23[24]; // [rsp+A0h] [rbp-178h] BYREF
  struct _UNICODE_STRING DestinationString; // [rsp+B8h] [rbp-160h] BYREF
  char v25; // [rsp+E0h] [rbp-138h] BYREF
  int v26; // [rsp+F0h] [rbp-128h]
  __int64 v27; // [rsp+1E0h] [rbp-38h]

  v27 = qword_17108;
  v1 = *(_QWORD *)(a1 + 56);
  v3 = 0;
  v4 = 0;
  v26 = 0;
  KeInitializeEvent(v23, 0LL, 0LL);
  v5 = IoBuildSynchronousFsdRequest(27LL, v1, 0LL);
  if ( v5 )
  {
    v6 = *(_QWORD *)(v5 + 184) - 72LL;
    if ( *(_QWORD *)(v5 + 184) != 72LL )
    {
      *(_DWORD *)(v5 + 48) = -1073741637;
      *(_BYTE *)v6 = 27;
      *(_QWORD *)(v6 + 16) = &v25;
      *(_BYTE *)(v6 + 1) = 15;
      *(_DWORD *)(v6 + 32) = 64;
      *(_DWORD *)(v6 + 8) = 0;
      *(_DWORD *)(v6 + 24) = 0;
      if ( (unsigned int)IofCallDriver(v1, v5) == 259 )
        KeWaitForSingleObject(v23, 0LL, 0LL, 0LL, 0LL);
    }
  }
  RtlInitUnicodeString(&DestinationString, L"\\REGISTRY\\MACHINE\\HARDWARE\\RESOURCEMAP\\PnP Manager\\PnpManager");
  ObjectAttributes.ObjectName = &DestinationString;
  ObjectAttributes.Length = 48;
  ObjectAttributes.RootDirectory = 0LL;
  ObjectAttributes.Attributes = 64;
  ObjectAttributes.SecurityDescriptor = 0LL;
  ObjectAttributes.SecurityQualityOfService = 0LL;
  v7 = ZwOpenKey(&KeyHandle, (ACCESS_MASK)&unk_20019, &ObjectAttributes);
  if ( v7 >= 0 )
  {
    do
    {
      v8 = 0;
      ZwEnumerateValueKey(KeyHandle, v4, KeyValueFullInformation, 0LL, 0, &ResultLength);
      PoolWithTag = ExAllocatePoolWithTag(1LL, ResultLength + 8LL, 543908932LL);
      v7 = ZwEnumerateValueKey(KeyHandle, v4, KeyValueFullInformation, (PVOID)PoolWithTag, ResultLength, &ResultLength);
      if ( v7 >= 0 )
      {
        if ( *(_DWORD *)(PoolWithTag + 4) == 8 )
        {
          RtlInitUnicodeString(&SourceString, (PCWSTR)(PoolWithTag + 20));
          RtlUnicodeStringToAnsiString(&AnsiString, &SourceString, 1u);
          if ( strstr(AnsiString.Buffer, "Translated") )
          {
            if ( strstr(AnsiString.Buffer, "NTPNP") )
            {
              v10 = PoolWithTag + *(unsigned int *)(PoolWithTag + 8);
              if ( *(_DWORD *)(v10 + 4) == 5 )
              {
                if ( *(_DWORD *)(v10 + 16) )
                {
                  v11 = v10 + 20;
                  v12 = *(unsigned int *)(v10 + 16);
                  do
                  {
                    if ( *(_BYTE *)v11 == 3 && *(_DWORD *)(v11 + 4) == v26 )
                    {
                      v13 = v8;
                      if ( !v8 )
                        v13 = 1;
                      v8 = v13;
                    }
                    v11 += 20LL;
                    --v12;
                  }
                  while ( v12 );
                  if ( v8 == 1 )
                  {
                    v14 = 0;
                    v15 = v10 + 24;
                    do
                    {
                      if ( *(_BYTE *)(v15 - 4) == 2 )
                      {
                        *(_DWORD *)(a1 + 12) = *(_DWORD *)(v15 + 4);
                        *(_BYTE *)(a1 + 8) = *(_BYTE *)v15;
                        v16 = *(_QWORD *)(v15 + 8);
                        *(_DWORD *)(a1 + 24) = 0;
                        *(_QWORD *)(a1 + 16) = v16;
                      }
                      ++v14;
                      v15 += 20LL;
                    }
                    while ( v14 < *(_DWORD *)(v10 + 16) );
                    v3 = 1;
                  }
                }
              }
            }
          }
          RtlFreeAnsiString(&AnsiString);
          ++v4;
        }
      }
      else
      {
        v3 = 1;
      }
      if ( PoolWithTag )
        ExFreePoolWithTag(PoolWithTag);
    }
    while ( !v3 );
  }
  if ( KeyHandle )
    ZwClose(KeyHandle);
  return (unsigned int)v7;
}