__int64 __fastcall sub_132B0(__int64 *a1)
{
  __int64 result; // rax
  const WCHAR *v3; // rbx
  USHORT Length; // r11
  unsigned __int16 v5; // cx
  __int64 v6; // rbp
  __int64 v7; // rdi
  __int64 v8; // r12
  __int64 v9; // rax
  __int64 PoolWithTag; // rsi
  _QWORD *i; // rax
  __int64 v12; // [rsp+20h] [rbp-68h] BYREF
  PCWSTR SourceString; // [rsp+28h] [rbp-60h] BYREF
  __int64 v14; // [rsp+30h] [rbp-58h] BYREF
  struct _UNICODE_STRING DestinationString; // [rsp+38h] [rbp-50h] BYREF
  int v16; // [rsp+48h] [rbp-40h] BYREF
  __int16 v17; // [rsp+4Ch] [rbp-3Ch]
  __int16 v18; // [rsp+4Eh] [rbp-3Ah]
  char v19; // [rsp+50h] [rbp-38h]
  char v20; // [rsp+51h] [rbp-37h]
  char v21; // [rsp+52h] [rbp-36h]
  char v22; // [rsp+53h] [rbp-35h]
  char v23; // [rsp+54h] [rbp-34h]
  char v24; // [rsp+55h] [rbp-33h]
  char v25; // [rsp+56h] [rbp-32h]
  char v26; // [rsp+57h] [rbp-31h]
  __int64 v27; // [rsp+58h] [rbp-30h]

  v27 = qword_17108;
  v16 = -1387689660;
  v17 = 30255;
  v18 = 4560;
  v19 = -115;
  v20 = -53;
  v21 = 0;
  v22 = -64;
  v23 = 79;
  v24 = -61;
  v25 = 53;
  v26 = -116;
  v12 = 0LL;
  v14 = 0LL;
  SourceString = 0LL;
  result = IoGetDeviceInterfaces(&v16, 0LL, 1LL, &SourceString);
  if ( (int)result >= 0 )
  {
    v3 = SourceString;
    RtlInitUnicodeString(&DestinationString, SourceString);
    Length = DestinationString.Length;
    if ( DestinationString.Length )
    {
      while ( 1 )
      {
        if ( Length > 4u )
        {
          v5 = 0;
          if ( Length - 4 > 0 )
            break;
        }
LABEL_22:
        v3 += (unsigned __int64)DestinationString.MaximumLength >> 1;
        RtlInitUnicodeString(&DestinationString, v3);
        Length = DestinationString.Length;
        if ( !DestinationString.Length )
          return ExFreePoolWithTag(SourceString, 0LL);
      }
      while ( 1 )
      {
        if ( v5 >= 0x14u )
          goto LABEL_22;
        if ( v3[v5] == 86 && v3[v5 + 1] == 69 && v3[v5 + 2] == 78 && v3[v5 + 3] == 95 )
          break;
        if ( ++v5 >= Length - 4 )
          goto LABEL_22;
      }
      if ( (int)IoGetDeviceObjectPointer(&DestinationString, &unk_1F01FF, &v12, &v14) >= 0 )
      {
        v6 = v12;
        v7 = *a1;
        v8 = *(_QWORD *)(v12 + 8);
        if ( *a1 )
        {
          PoolWithTag = ExAllocatePoolWithTag(0LL, 592LL, 543908932LL);
          for ( i = (_QWORD *)(v7 + 584); *i; i = (_QWORD *)(*i + 584LL) )
            v7 = *i;
          *(_QWORD *)(v7 + 584) = PoolWithTag;
          goto LABEL_19;
        }
        v9 = ExAllocatePoolWithTag(0LL, 592LL, 543908932LL);
        PoolWithTag = v9;
        if ( v9 )
        {
          *a1 = v9;
LABEL_19:
          if ( PoolWithTag )
          {
            *(_QWORD *)(PoolWithTag + 56) = v8;
            *(_QWORD *)(PoolWithTag + 48) = v6;
            *(_QWORD *)(PoolWithTag + 584) = 0LL;
            sub_13110(PoolWithTag);
            ++*((_DWORD *)a1 + 2);
            sub_12D70(PoolWithTag);
            wcsncpy((wchar_t *)(PoolWithTag + 64), v3, 0x103uLL);
          }
        }
      }
      v12 = 0LL;
      v14 = 0LL;
      goto LABEL_22;
    }
    return ExFreePoolWithTag(SourceString, 0LL);
  }
  return result;
}