void __fastcall sub_13EF0(__int64 a1, __int64 a2)
{
  NTSTATUS v3; // eax
  PCHAR Buffer; // rcx
  PCHAR v5; // rdx
  __int64 v6; // rbx
  CHAR v7; // al
  struct _STRING v8; // [rsp+20h] [rbp-28h] BYREF
  struct _UNICODE_STRING DestinationString; // [rsp+30h] [rbp-18h] BYREF

  if ( a1 )
  {
    RtlInitUnicodeString(&DestinationString, (PCWSTR)(a1 + 408));
    v8.Length = 260;
    v8.MaximumLength = 260;
    v8.Buffer = (PCHAR)ExAllocatePoolWithTag(1LL, 260LL, 543908932LL);
    if ( v8.Buffer )
    {
      v3 = RtlUnicodeStringToAnsiString(&v8, &DestinationString, 0);
      Buffer = v8.Buffer;
      if ( v3 >= 0 )
      {
        v5 = v8.Buffer;
        v6 = a2 - (unsigned __int64)v8.Buffer;
        do
        {
          v7 = *v5++;
          v5[v6 - 1] = v7;
        }
        while ( v7 );
      }
      ExFreePoolWithTag(Buffer, 0LL);
    }
  }
}