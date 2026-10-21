__int64 __fastcall sub_5E2010(_QWORD *a1)
{
  __int64 v1; // rdi
  _BYTE *v3; // rax
  __int64 v4; // rdx
  _QWORD *v5; // rcx
  __int64 v6; // rdx
  _DWORD *v7; // rax
  int v8; // eax
  int v9; // eax
  __int64 v10; // rax
  __int64 *v11; // rbx
  char v13; // [rsp+28h] [rbp-40h]
  struct _UNICODE_STRING DestinationString; // [rsp+40h] [rbp-28h] BYREF
  struct _UNICODE_STRING v15; // [rsp+50h] [rbp-18h] BYREF
  __int64 v16; // [rsp+70h] [rbp+8h] BYREF
  __int64 v17; // [rsp+88h] [rbp+20h]

  v17 = v1;
  sub_11F30("\nNal Windows Driver Loaded -- Compiled %s %s\n", aNov142013, a072240);
  v3 = byte_5CFEC0;
  dword_17120 = 0;
  v4 = 256LL;
  do
  {
    v3[264] = 0;
    *(_QWORD *)v3 = 0LL;
    v3 += 272;
    --v4;
  }
  while ( v4 );
  v5 = &unk_3E7A50;
  v6 = 50000LL;
  a1[14] = sub_11090;
  a1[16] = sub_110F0;
  a1[28] = sub_11150;
  a1[13] = sub_11010;
  v7 = &unk_17148;
  do
  {
    *(v7 - 2) = 0;
    *(_QWORD *)v7 = 0LL;
    *((_QWORD *)v7 + 2) = 0LL;
    *((_QWORD *)v7 + 1) = 0LL;
    v7[8] = 0;
    v7[9] = 0;
    *((_QWORD *)v7 + 3) = 0LL;
    *((_QWORD *)v7 + 5) = 0LL;
    *((_QWORD *)v7 + 6) = 0LL;
    *((_QWORD *)v7 + 7) = 0LL;
    *((_QWORD *)v7 + 8) = 0LL;
    v5[1] = 0LL;
    *v5 = 0LL;
    *(v5 - 2) = 0LL;
    *(v5 - 1) = 0LL;
    v5[2] = 0LL;
    v7 += 20;
    v5 += 5;
    --v6;
  }
  while ( v6 );
  sub_11F30("Nal Windows DriverAddDevice: entered\n");
  RtlInitUnicodeString(&DestinationString, L"\\Device\\Nal");
  v13 = 0;
  v8 = IoCreateDevice(a1, 24LL, &DestinationString, 32902LL, 0, v13, &v16);
  if ( v8 >= 0 )
  {
    v10 = v16;
    a1[1] = v16;
    v11 = *(__int64 **)(v10 + 64);
    *v11 = v10;
    RtlInitUnicodeString(&v15, L"\\DosDevices\\Nal");
    v9 = IoCreateSymbolicLink(&v15, &DestinationString);
    if ( v9 >= 0 )
    {
      *(_DWORD *)(v16 + 48) |= 4u;
      *(_DWORD *)(v16 + 48) &= ~0x80u;
      v11[1] = v16;
      goto LABEL_10;
    }
  }
  else
  {
    sub_11F30("Nal Windows DriverIoCreateDevice failed.  Status = 0x%0x\n", (unsigned int)v8);
    v9 = -1073741823;
  }
  sub_11F30("Nal Windows DriverIoCreateSymbolicLink failed.  Status = 0x%x\n", (unsigned int)v9);
  IoDeleteDevice(v16);
LABEL_10:
  sub_11F30("Nal Windows DriverAddDevice: done\n");
  sub_11F30(aNalWindowsDriv_12);
  return 0LL;
}