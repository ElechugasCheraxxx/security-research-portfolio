__int64 __fastcall sub_13FA0(_QWORD *a1)
{
  unsigned int v2; // ebx
  __int64 *v3; // rdi
  __int64 v4; // rbx
  _QWORD *v5; // rdi
  _QWORD *v6; // rdi
  char v7; // r11
  __int64 v8; // rdx
  __int64 v9; // rax
  _DWORD *v10; // rdi
  _BYTE *v11; // rdi
  _BYTE *v12; // rdi
  char Dst[272]; // [rsp+20h] [rbp-4D8h] BYREF
  __int64 v15; // [rsp+130h] [rbp-3C8h] BYREF
  char v16[264]; // [rsp+138h] [rbp-3C0h] BYREF
  __int64 v17; // [rsp+240h] [rbp-2B8h]
  __int64 v18; // [rsp+248h] [rbp-2B0h]
  __int64 v19; // [rsp+250h] [rbp-2A8h]
  char v20; // [rsp+258h] [rbp-2A0h]
  __int64 v21; // [rsp+4E0h] [rbp-18h]

  v21 = qword_17108;
  v2 = 1;
  if ( a1 )
  {
    sub_11F30("NalOsSpecificIoctl: FunctionId = %d\n");
    switch ( *a1 )
    {
      case 1LL:
        v3 = a1 + 2;
        if ( v3 )
        {
          memmove(Dst, v3 + 1, 0x108uLL);
          v4 = *v3;
          sub_13640(Dst, *v3 + 344);
          ++*(_DWORD *)(v4 + 936);
          v2 = 0;
        }
        else
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_GET_PDO_POINTER_FUNCID FunctionData is NULL\n");
        }
        break;
      case 2LL:
        if ( a1 == (_QWORD *)-16LL )
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_GET_SYMBOLIC_NAME_FUNCID FunctionData is NULL\n");
        }
        else
        {
          sub_13EF0(a1[2], a1 + 3);
          v2 = 0;
        }
        break;
      case 3LL:
        v5 = a1 + 2;
        if ( v5 )
        {
          v2 = 0;
          *v5 = sub_13E60();
        }
        else
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_ALLOC_DEV_CONTEXT_FUNCID FunctionData is NULL\n");
        }
        break;
      case 4LL:
        if ( a1 == (_QWORD *)-16LL )
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_FREE_DEV_CONTEXT_FUNCID FunctionData is NULL\n");
        }
        else
        {
          sub_13EA0(a1[2]);
          v2 = 0;
        }
        break;
      case 5LL:
        v6 = a1 + 2;
        if ( v6 )
        {
          memmove(v16, v6 + 1, 0x108uLL);
          v7 = *((_BYTE *)v6 + 296);
          v8 = v6[38];
          v15 = *v6;
          v17 = v6[34];
          v19 = v6[36];
          v9 = v6[35];
          v20 = v7;
          v18 = v9;
          v2 = 0;
          *((_DWORD *)v6 + 78) = sub_13D00(&v15, v8);
        }
        else
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_OS_DEVICE_FUNCID FunctionData is NULL\n");
        }
        break;
      case 6LL:
        v10 = a1 + 2;
        if ( v10 )
        {
          v2 = 0;
          *v10 = sub_11210();
        }
        else
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_DRIVER_GET_REF_COUNT_FUNCID FunctionData is NULL\n");
        }
        break;
      case 7LL:
        v11 = a1 + 2;
        if ( v11 )
        {
          memmove(Dst, v11, 0x108uLL);
          v2 = 0;
          v11[264] = sub_11220(Dst, (unsigned __int8)v11[265]);
        }
        else
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_ADAPTER_IN_USE_FUNCID FunctionData is NULL\n");
        }
        break;
      case 8LL:
        v12 = a1 + 2;
        if ( v12 )
        {
          memmove(Dst, v12, 0x108uLL);
          v2 = 0;
          v12[264] = sub_112F0(Dst);
        }
        else
        {
          sub_11F30("NalResolveOsSpecificIoctl: NAL_WIN_IS_ADAPTER_IN_USE_FUNCID FunctionData is NULL\n");
        }
        break;
      default:
        sub_11F30("NalResolveOsSpecificIoctl: FuctionId = %d\n");
        v2 = -932569064;
        break;
    }
  }
  return v2;
}