__int64 __fastcall sub_113C0(__int64 a1)
{
  unsigned int v2; // ebx
  __int64 result; // rax
  __int64 v4; // rcx
  __int64 v5; // rcx
  __int64 v6; // rdx

  v2 = 1;
  if ( !a1 )
    return v2;
  switch ( *(_QWORD *)a1 )
  {
    case 1LL:
      *(_BYTE *)(a1 + 16) = sub_11C20(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 2LL:
      *(_WORD *)(a1 + 16) = sub_11C30(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 3LL:
      *(_DWORD *)(a1 + 16) = sub_11C40(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 7LL:
      *(_BYTE *)(a1 + 16) = sub_11C50(*(_QWORD *)(a1 + 24), *(_BYTE *)(a1 + 32));
      return 0LL;
    case 8LL:
      *(_BYTE *)(a1 + 16) = sub_11C60(*(_QWORD *)(a1 + 24), *(_WORD *)(a1 + 32));
      return 0LL;
    case 9LL:
      *(_BYTE *)(a1 + 16) = sub_11C80(*(_QWORD *)(a1 + 24), *(_DWORD *)(a1 + 32));
      return 0LL;
    case 0xDLL:
      *(_BYTE *)(a1 + 16) = sub_11C90(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 0xELL:
      *(_WORD *)(a1 + 16) = sub_11CB0(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 0xFLL:
      *(_DWORD *)(a1 + 16) = sub_11CD0(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 0x13LL:
      *(_BYTE *)(a1 + 16) = sub_11CF0(*(_QWORD *)(a1 + 24), *(unsigned __int8 *)(a1 + 32));
      return 0LL;
    case 0x14LL:
      *(_BYTE *)(a1 + 16) = sub_11D10(*(_QWORD *)(a1 + 24), *(unsigned __int16 *)(a1 + 32));
      return 0LL;
    case 0x15LL:
      *(_BYTE *)(a1 + 16) = sub_11D30(*(_QWORD *)(a1 + 24), *(unsigned int *)(a1 + 32));
      return 0LL;
    case 0x19LL:
      *(_DWORD *)(a1 + 16) = sub_12AC0((_QWORD *)(a1 + 24), *(_QWORD *)(a1 + 32), (unsigned int *)(a1 + 40));
      return 0LL;
    case 0x1ALL:
      *(_DWORD *)(a1 + 16) = sub_121C0(*(const void **)(a1 + 24), *(_QWORD *)(a1 + 32), *(_DWORD *)(a1 + 40));
      return 0LL;
    case 0x1BLL:
      *(_QWORD *)(a1 + 16) = sub_11DB0();
      return 0LL;
    case 0x1CLL:
      *(_QWORD *)(a1 + 16) = sub_12450();
      return 0LL;
    case 0x23LL:
      sub_123C0(*(unsigned int *)(a1 + 16));
      return 0LL;
    case 0x24LL:
      sub_11D50(*(unsigned int *)(a1 + 16));
      return 0LL;
    case 0x25LL:
      *(_QWORD *)(a1 + 16) = sub_12010(*(_QWORD *)(a1 + 24));
      return 0LL;
    case 0x26LL:
      *(_QWORD *)(a1 + 16) = sub_128B0(*(_DWORD *)(a1 + 24), *(_DWORD *)(a1 + 28), (int)a1 + 32, 0, 0);
      return 0LL;
    case 0x27LL:
      sub_128E0(*(_QWORD *)(a1 + 16), 0LL, 0LL);
      return 0LL;
    case 0x28LL:
      *(_DWORD *)(a1 + 16) = sub_11ED0(*(volatile signed __int32 **)(a1 + 24));
      return 0LL;
    case 0x29LL:
      *(_DWORD *)(a1 + 16) = sub_11EF0(*(volatile signed __int32 **)(a1 + 24));
      return 0LL;
    case 0x2ALL:
      *(_DWORD *)(a1 + 16) = sub_11F10(*(_QWORD *)(a1 + 24), *(unsigned int *)(a1 + 32), *(unsigned int *)(a1 + 36));
      return 0LL;
    case 0x2FLL:
      if ( a1 == -16 )
        goto LABEL_42;
      *(_DWORD *)(a1 + 16) = sub_11F30((char *)(a1 + 20));
      result = 0LL;
      break;
    case 0x30LL:
      v4 = *(_QWORD *)(a1 + 24);
      if ( v4 )
      {
        sub_11E70(v4, *(unsigned int *)(a1 + 16), *(_QWORD *)(a1 + 32));
        return 0LL;
      }
      else
      {
        sub_11F30("NAL_KMEMSET_FUNCID: One of the buffers was NULL\n");
        return 1LL;
      }
    case 0x31LL:
      v5 = *(_QWORD *)(a1 + 24);
      if ( v5 )
      {
        v6 = *(_QWORD *)(a1 + 16);
        if ( v6 )
          goto LABEL_29;
      }
      sub_11F30("NAL_KUMEMCPY_FUNCID: One of the buffers was NULL\n");
      result = 1LL;
      break;
    case 0x32LL:
      v5 = *(_QWORD *)(a1 + 24);
      if ( v5 && (v6 = *(_QWORD *)(a1 + 16)) != 0 )
      {
LABEL_29:
        sub_11EA0(v5, v6, *(_QWORD *)(a1 + 32));
        result = 0LL;
      }
      else
      {
        sub_11F30("NAL_KKMEMCPY_FUNCID: One of the buffers was NULL\n");
        result = 1LL;
      }
      break;
    case 0x33LL:
      sub_11EA0(*(_QWORD *)(a1 + 24), *(_QWORD *)(a1 + 16), *(_QWORD *)(a1 + 32));
      result = 0LL;
      break;
    case 0x36LL:
      if ( a1 == -16 )
      {
LABEL_42:
        sub_11F30("NAL_ENABLE_DEBUG_PRINT_FUNCID: FunctionData is NULL\n");
        result = 1LL;
      }
      else
      {
        sub_12000(*(unsigned __int8 *)(a1 + 16));
        result = 0LL;
      }
      break;
    case 0x37LL:
      *(_QWORD *)(a1 + 16) = sub_12520(
                               *(_DWORD *)(a1 + 24),
                               *(_DWORD *)(a1 + 28),
                               *(_QWORD *)(a1 + 40),
                               (unsigned __int64 *)(a1 + 32));
      result = 0LL;
      break;
    case 0x38LL:
      sub_12770(*(const void **)(a1 + 16), *(_QWORD *)(a1 + 24));
      result = 0LL;
      break;
    case 0x39LL:
      *(_DWORD *)(a1 + 16) = sub_129C0(
                               (_QWORD *)(a1 + 24),
                               *(_QWORD *)(a1 + 32),
                               (unsigned int *)(a1 + 40),
                               *(_QWORD *)(a1 + 48));
      result = 0LL;
      break;
    case 0x3ALL:
      *(_DWORD *)(a1 + 16) = sub_12220(
                               *(const void **)(a1 + 24),
                               *(_QWORD *)(a1 + 32),
                               *(_DWORD *)(a1 + 40),
                               *(const void **)(a1 + 48));
      result = 0LL;
      break;
    case 0x3BLL:
      *(_QWORD *)(a1 + 16) = sub_11DE0(*(_QWORD *)(a1 + 24), *(_QWORD *)(a1 + 32));
      result = 0LL;
      break;
    default:
      return (unsigned int)-932569064;
  }
  return result;
}