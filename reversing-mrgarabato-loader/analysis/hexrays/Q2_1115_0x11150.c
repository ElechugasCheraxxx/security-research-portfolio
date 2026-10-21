__int64 __fastcall sub_11150(__int64 a1, __int64 a2)
{
  __int64 v2; // rax
  _QWORD *v3; // rcx
  __int64 v5; // rdx
  unsigned int v6; // ebx

  v2 = *(_QWORD *)(a2 + 184);
  v3 = *(_QWORD **)(v2 + 32);
  v5 = *(unsigned int *)(v2 + 24);
  if ( v3 )
  {
    switch ( (_DWORD)v5 )
    {
      case 0x80862007:
        v6 = sub_113C0((__int64)v3);
        break;
      case 0x8086200B:
        v6 = sub_11A60((__int64)v3);
        break;
      case 0x8086200F:
        v6 = sub_11330((__int64)v3);
        break;
      case 0x80862013:
        v6 = sub_13FA0(v3);
        break;
      default:
        v6 = -1073741811;
        sub_11F30("Nal Windows DriverDeviceControl: Invalid IOCTL code 0x%0x\n", v5);
        break;
    }
  }
  else
  {
    sub_11F30("NalDeviceControl: InputBuffer was NULL\n", v5);
    v6 = -1073741811;
  }
  *(_QWORD *)(a2 + 56) = 0LL;
  *(_DWORD *)(a2 + 48) = v6;
  IofCompleteRequest(a2, 0LL);
  return v6;
}