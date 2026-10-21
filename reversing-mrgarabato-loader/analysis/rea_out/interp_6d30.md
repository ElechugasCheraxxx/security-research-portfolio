## evidence_id

ev_a20e9a5a987db6995a20901160f6decf9a19bae9e56a2ef5c352ec97d67fe8fd

## subject.name

loader_solo_text.exe

## subject.digest

| Key    | Value                                                            |
|--------|------------------------------------------------------------------|
| sha256 | d532f3ccf89d23968f3a39b15e7c710563e3c0529eafa814b994c6d1a473fbd1 |

## subject.local_path

/root/mrgarabato_analysis/run/loader_solo_text.exe

## subject.format

pe

## subject.architecture

x86_64

## provider

| Key     | Value  |
|---------|--------|
| id      | ghidra |
| name    | Ghidra |
| version | 12.1.2 |

## analysis_profile.provider

| Key     | Value  |
|---------|--------|
| id      | ghidra |
| name    | Ghidra |
| version | 12.1.2 |

## analysis_profile.parameters.target_kind

executable

## analysis_profile.parameters.target_format

pe

## analysis_profile.parameters.executable_role

application

## analysis_profile.parameters.managed

false

## analysis_profile.parameters.native_aot_metadata

| Key                  | Value                       |
|----------------------|-----------------------------|
| contract_revision    | rtr-9.1-x64-pe-read-only-v3 |
| source_bytes         | 134217728                   |
| work_units           | 67108864                    |
| working_memory_bytes | 67108864                    |
| report_bytes         | 4194304                     |

## analysis_profile.parameters.architecture

x86_64

## analysis_profile.parameters.available_architectures

x86_64

## analysis_profile.parameters.import_mode

ephemeral-source-immutable

## analysis_profile.parameters.pdb_observations

program-info-v5

## analysis_profile.parameters.annotation_policy

atomic-function-entry-metadata-v1

## analysis_profile.parameters.load_image_observations

source-mappings-entry-context-v2

## analysis_profile.parameters.function_body_evidence

complete-inclusive-ranges-v1

## analysis_profile.parameters.function_references

complete-body-and-entry-reference-manager-v2

## analysis_profile.parameters.call_relationship_coverage

function-body-call-coverage-v5

## analysis_profile.parameters.function_dossier_coverage

observed-facets-and-call-relationships-v1

## analysis_profile.parameters.string_inventory_evidence

defined-data-coverage-v1

## analysis_profile.parameters.location_resolution

explicit-address-exact-entry-symbol-first-v3

## analysis_profile.parameters.procedure_file_offset_resolution

address-first-unique-target-source-mapping-v2

## analysis_profile.parameters.instruction_flow_evidence

decoded-return-pcode-v1

## analysis_profile.parameters.instruction_references

exact-address-incoming-without-synthetic-entry-v2

## analysis_profile.parameters.function_boundary_observations

ghidra-function-boundary-limitations-v4

## analysis_profile.parameters.no_return_repair

returning-imports-decoded-return-v2

## analysis_profile.parameters.process_launch

inspected-jvm-launch-support-v1

## analysis_profile.parameters.jump_table_evidence

typed-case-default-blocks-v1

## analysis_profile.parameters.decompiler_jump_loads

true

## analysis_profile.parameters.loader

auto-from-header

## analysis_profile.parameters.language_id

auto-from-header

## analysis_profile.parameters.compiler_spec_id

auto-default

## analysis_profile.parameters.analyzer_preset

ghidra-default

## analysis_profile.digest

c9d1b8b5fece7826116befe30d99989217a2a975af7b8b94086fe87ab12668d1

## predicate_type

rea.analysis

## operation

procedure_pseudo_code

## parameters

| Key       | Value       |
|-----------|-------------|
| procedure | 0x140006d30 |

## raw_result.value


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * FUN_140006d30(char *param_1,ulonglong *param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  char *pcVar4;
  undefined8 ****ppppuVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined8 *****pppppuVar8;
  ulonglong *puVar9;
  undefined8 *****pppppuVar10;
  undefined1 auStack_b8 [32];
  char local_98 [8];
  undefined8 ****local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  ulonglong uStack_78;
  undefined4 local_70;
  char *local_68;
  undefined8 ****local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  ulonglong uStack_48;
  ulonglong local_40 [5];
  
  local_40[4] = DAT_14002f500 ^ (ulonglong)auStack_b8;
  local_70 = 0;
  local_68 = param_1;
  FUN_140003790(param_1);
  local_70 = 1;
  local_98[0] = '\0';
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,&DAT_1400229f0,2);
  uVar2 = FUN_140005890((longlong *)param_2,(longlong)&local_60,local_98);
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  if ((char)uVar2 != '\0') {
    *param_1 = local_98[0];
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"message",7);
  FUN_140006180(param_2,(longlong)&local_60,(undefined8 *****)(param_1 + 8));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"token",5);
  FUN_140006180(param_2,(longlong)&local_60,(undefined8 *****)(param_1 + 0x28));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"subscription",0xc);
  pppppuVar8 = (undefined8 *****)(param_1 + 0x48);
  FUN_140006180(param_2,(longlong)&local_60,pppppuVar8);
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"subscription_level",0x12);
  FUN_140005b70((longlong *)param_2,(longlong)&local_60,(int *)(param_1 + 0x68));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"update_url",10);
  FUN_140006180(param_2,(longlong)&local_60,(undefined8 *****)(param_1 + 0x198));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_40[1] = 0;
  local_40[2] = 0;
  local_40[3] = 0xf;
  local_40[0] = 0;
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,&DAT_140022b44,4);
  uVar6 = FUN_140005e40((longlong *)param_2,(longlong)&local_60,(longlong *)local_40);
  if (uStack_48 < 0x10) {
LAB_1400070c2:
    if ((char)uVar6 == '\0') {
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"username",8);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0x70));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar7);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"email",5);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0x90));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar7);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"expiry_date",0xb);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0xd0));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar7);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"status",6);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0xf8));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        goto LAB_14000786a;
      }
    }
    else {
      param_1[0x6c] = '\x01';
      uVar6 = *(ulonglong *)(param_1 + 0x58);
      pppppuVar10 = pppppuVar8;
      if (0xf < *(ulonglong *)(param_1 + 0x60)) {
        pppppuVar10 = (undefined8 *****)*pppppuVar8;
      }
      if (uVar6 == 0) {
LAB_14000713b:
        FUN_140002f00((ulonglong *)&local_60,(ulonglong *)pppppuVar8);
        local_70 = 3;
      }
      else {
        lVar3 = FUN_14001b7ec();
        if ((lVar3 == 0) || (uVar7 = lVar3 - (longlong)pppppuVar10, uVar7 == 0xffffffffffffffff))
        goto LAB_14000713b;
        local_60 = (undefined8 ****)0x0;
        uStack_58 = 0;
        local_50 = 0;
        uStack_48 = 0;
        if (uVar6 < uVar7) {
          uVar7 = uVar6;
        }
        if (0xf < *(ulonglong *)(param_1 + 0x60)) {
          pppppuVar8 = (undefined8 *****)*pppppuVar8;
        }
        FUN_140001bc0((ulonglong *)&local_60,pppppuVar8,uVar7);
        local_70 = 7;
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"username",8);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x70));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"email",5);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x90));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"discordid",9);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0xb0));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"subscription",0xc);
      FUN_140006180(local_40,(longlong)&local_90,&local_60);
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"expiry_date",0xb);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0xd0));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"hwid_affected",0xd);
      FUN_140005890((longlong *)local_40,(longlong)&local_90,param_1 + 0xf0);
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"status",6);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0xf8));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"created_at",10);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x118));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"last_login",10);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x138));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,&DAT_140022a84,2);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x158));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,&DAT_140022a88,4);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x178));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5))) {
LAB_14000764d:
            func_0x0001400c6239();
            pcVar1 = (code *)swi(3);
            pcVar4 = (char *)(*pcVar1)();
            return pcVar4;
          }
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      if (0xf < uStack_48) {
        uVar7 = uStack_48 + 1;
        ppppuVar5 = local_60;
        if (0xfff < uVar7) {
          uVar7 = uStack_48 + 0x28;
          ppppuVar5 = (undefined8 ****)local_60[-1];
          if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) {
            func_0x00014059f0a1();
            pcVar1 = (code *)swi(3);
            pcVar4 = (char *)(*pcVar1)();
            return pcVar4;
          }
        }
        goto LAB_14000786a;
      }
    }
  }
  else {
    uVar7 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (uVar7 < 0x1000) {
LAB_1400070bd:
      thunk_FUN_14001b822(ppppuVar5,uVar7);
      goto LAB_1400070c2;
    }
    uVar7 = uStack_48 + 0x28;
    ppppuVar5 = (undefined8 ****)local_60[-1];
    if ((ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5)) < 0x20) goto LAB_1400070bd;
LAB_140007863:
    func_0x00014055d56a();
LAB_14000786a:
    thunk_FUN_14001b822(ppppuVar5,uVar7);
  }
  if ((*param_1 == '\0') && (*(longlong *)(param_1 + 0x18) == 0)) {
    puVar9 = (ulonglong *)(param_1 + 8);
    if (*(ulonglong *)(param_1 + 0x20) < 0xe) {
      FUN_140002210(puVar9,0xe);
    }
    else {
      if (0xf < *(ulonglong *)(param_1 + 0x20)) {
        puVar9 = (ulonglong *)*puVar9;
      }
      param_1[0x18] = '\x0e';
      param_1[0x19] = '\0';
      param_1[0x1a] = '\0';
      param_1[0x1b] = '\0';
      param_1[0x1c] = '\0';
      param_1[0x1d] = '\0';
      param_1[0x1e] = '\0';
      param_1[0x1f] = '\0';
      FUN_14001b7fe();
      *(undefined1 *)((longlong)puVar9 + 0xe) = 0;
    }
  }
  if (0xf < local_40[3]) {
    uVar7 = local_40[3] + 1;
    uVar6 = local_40[0];
    if (0xfff < uVar7) {
      uVar7 = local_40[3] + 0x28;
      uVar6 = *(ulonglong *)(local_40[0] - 8);
      if (0x1f < (local_40[0] - uVar6) - 8) {
LAB_1400078fe:
        func_0x0001404a249f();
        pcVar1 = (code *)swi(3);
        pcVar4 = (char *)(*pcVar1)();
        return pcVar4;
      }
    }
    thunk_FUN_14001b822(uVar6,uVar7);
  }
  return param_1;
}



## raw_result.limitations

Ghidra Listing reports a terminal call at 0x140007653 with no resolved callee; its no-return basis is unknown.,Ghidra Listing reports a terminal call at 0x14000769e with no resolved callee; its no-return basis is unknown.,Ghidra Listing reports a terminal call at 0x140007904 with no resolved callee; its no-return basis is unknown.

## normalized_result


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * FUN_140006d30(char *param_1,ulonglong *param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  char *pcVar4;
  undefined8 ****ppppuVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined8 *****pppppuVar8;
  ulonglong *puVar9;
  undefined8 *****pppppuVar10;
  undefined1 auStack_b8 [32];
  char local_98 [8];
  undefined8 ****local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  ulonglong uStack_78;
  undefined4 local_70;
  char *local_68;
  undefined8 ****local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  ulonglong uStack_48;
  ulonglong local_40 [5];
  
  local_40[4] = DAT_14002f500 ^ (ulonglong)auStack_b8;
  local_70 = 0;
  local_68 = param_1;
  FUN_140003790(param_1);
  local_70 = 1;
  local_98[0] = '\0';
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,&DAT_1400229f0,2);
  uVar2 = FUN_140005890((longlong *)param_2,(longlong)&local_60,local_98);
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  if ((char)uVar2 != '\0') {
    *param_1 = local_98[0];
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"message",7);
  FUN_140006180(param_2,(longlong)&local_60,(undefined8 *****)(param_1 + 8));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"token",5);
  FUN_140006180(param_2,(longlong)&local_60,(undefined8 *****)(param_1 + 0x28));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"subscription",0xc);
  pppppuVar8 = (undefined8 *****)(param_1 + 0x48);
  FUN_140006180(param_2,(longlong)&local_60,pppppuVar8);
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"subscription_level",0x12);
  FUN_140005b70((longlong *)param_2,(longlong)&local_60,(int *)(param_1 + 0x68));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,"update_url",10);
  FUN_140006180(param_2,(longlong)&local_60,(undefined8 *****)(param_1 + 0x198));
  if (0xf < uStack_48) {
    uVar6 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (0xfff < uVar6) {
      uVar6 = uStack_48 + 0x28;
      ppppuVar5 = (undefined8 ****)local_60[-1];
      if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) goto LAB_1400078fe;
    }
    thunk_FUN_14001b822(ppppuVar5,uVar6);
  }
  local_40[1] = 0;
  local_40[2] = 0;
  local_40[3] = 0xf;
  local_40[0] = 0;
  local_60 = (undefined8 ****)0x0;
  uStack_58 = 0;
  local_50 = 0;
  uStack_48 = 0;
  FUN_140001bc0((ulonglong *)&local_60,&DAT_140022b44,4);
  uVar6 = FUN_140005e40((longlong *)param_2,(longlong)&local_60,(longlong *)local_40);
  if (uStack_48 < 0x10) {
LAB_1400070c2:
    if ((char)uVar6 == '\0') {
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"username",8);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0x70));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar7);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"email",5);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0x90));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar7);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"expiry_date",0xb);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0xd0));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar7);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"status",6);
      FUN_140006180(param_2,(longlong)&local_90,(undefined8 *****)(param_1 + 0xf8));
      if (0xf < uStack_78) {
        uVar7 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar7) {
          uVar7 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_140007863;
        }
        goto LAB_14000786a;
      }
    }
    else {
      param_1[0x6c] = '\x01';
      uVar6 = *(ulonglong *)(param_1 + 0x58);
      pppppuVar10 = pppppuVar8;
      if (0xf < *(ulonglong *)(param_1 + 0x60)) {
        pppppuVar10 = (undefined8 *****)*pppppuVar8;
      }
      if (uVar6 == 0) {
LAB_14000713b:
        FUN_140002f00((ulonglong *)&local_60,(ulonglong *)pppppuVar8);
        local_70 = 3;
      }
      else {
        lVar3 = FUN_14001b7ec();
        if ((lVar3 == 0) || (uVar7 = lVar3 - (longlong)pppppuVar10, uVar7 == 0xffffffffffffffff))
        goto LAB_14000713b;
        local_60 = (undefined8 ****)0x0;
        uStack_58 = 0;
        local_50 = 0;
        uStack_48 = 0;
        if (uVar6 < uVar7) {
          uVar7 = uVar6;
        }
        if (0xf < *(ulonglong *)(param_1 + 0x60)) {
          pppppuVar8 = (undefined8 *****)*pppppuVar8;
        }
        FUN_140001bc0((ulonglong *)&local_60,pppppuVar8,uVar7);
        local_70 = 7;
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"username",8);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x70));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"email",5);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x90));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"discordid",9);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0xb0));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"subscription",0xc);
      FUN_140006180(local_40,(longlong)&local_90,&local_60);
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"expiry_date",0xb);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0xd0));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"hwid_affected",0xd);
      FUN_140005890((longlong *)local_40,(longlong)&local_90,param_1 + 0xf0);
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"status",6);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0xf8));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"created_at",10);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x118));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,"last_login",10);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x138));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,&DAT_140022a84,2);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x158));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5)))
          goto LAB_14000764d;
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      local_90 = (undefined8 ****)0x0;
      uStack_88 = 0;
      local_80 = 0;
      uStack_78 = 0;
      FUN_140001bc0((ulonglong *)&local_90,&DAT_140022a88,4);
      FUN_140006180(local_40,(longlong)&local_90,(undefined8 *****)(param_1 + 0x178));
      if (0xf < uStack_78) {
        uVar6 = uStack_78 + 1;
        ppppuVar5 = local_90;
        if (0xfff < uVar6) {
          uVar6 = uStack_78 + 0x28;
          ppppuVar5 = (undefined8 ****)local_90[-1];
          if (0x1f < (ulonglong)((longlong)local_90 + (-8 - (longlong)ppppuVar5))) {
LAB_14000764d:
            func_0x0001400c6239();
            pcVar1 = (code *)swi(3);
            pcVar4 = (char *)(*pcVar1)();
            return pcVar4;
          }
        }
        thunk_FUN_14001b822(ppppuVar5,uVar6);
      }
      if (0xf < uStack_48) {
        uVar7 = uStack_48 + 1;
        ppppuVar5 = local_60;
        if (0xfff < uVar7) {
          uVar7 = uStack_48 + 0x28;
          ppppuVar5 = (undefined8 ****)local_60[-1];
          if (0x1f < (ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5))) {
            func_0x00014059f0a1();
            pcVar1 = (code *)swi(3);
            pcVar4 = (char *)(*pcVar1)();
            return pcVar4;
          }
        }
        goto LAB_14000786a;
      }
    }
  }
  else {
    uVar7 = uStack_48 + 1;
    ppppuVar5 = local_60;
    if (uVar7 < 0x1000) {
LAB_1400070bd:
      thunk_FUN_14001b822(ppppuVar5,uVar7);
      goto LAB_1400070c2;
    }
    uVar7 = uStack_48 + 0x28;
    ppppuVar5 = (undefined8 ****)local_60[-1];
    if ((ulonglong)((longlong)local_60 + (-8 - (longlong)ppppuVar5)) < 0x20) goto LAB_1400070bd;
LAB_140007863:
    func_0x00014055d56a();
LAB_14000786a:
    thunk_FUN_14001b822(ppppuVar5,uVar7);
  }
  if ((*param_1 == '\0') && (*(longlong *)(param_1 + 0x18) == 0)) {
    puVar9 = (ulonglong *)(param_1 + 8);
    if (*(ulonglong *)(param_1 + 0x20) < 0xe) {
      FUN_140002210(puVar9,0xe);
    }
    else {
      if (0xf < *(ulonglong *)(param_1 + 0x20)) {
        puVar9 = (ulonglong *)*puVar9;
      }
      param_1[0x18] = '\x0e';
      param_1[0x19] = '\0';
      param_1[0x1a] = '\0';
      param_1[0x1b] = '\0';
      param_1[0x1c] = '\0';
      param_1[0x1d] = '\0';
      param_1[0x1e] = '\0';
      param_1[0x1f] = '\0';
      FUN_14001b7fe();
      *(undefined1 *)((longlong)puVar9 + 0xe) = 0;
    }
  }
  if (0xf < local_40[3]) {
    uVar7 = local_40[3] + 1;
    uVar6 = local_40[0];
    if (0xfff < uVar7) {
      uVar7 = local_40[3] + 0x28;
      uVar6 = *(ulonglong *)(local_40[0] - 8);
      if (0x1f < (local_40[0] - uVar6) - 8) {
LAB_1400078fe:
        func_0x0001404a249f();
        pcVar1 = (code *)swi(3);
        pcVar4 = (char *)(*pcVar1)();
        return pcVar4;
      }
    }
    thunk_FUN_14001b822(uVar6,uVar7);
  }
  return param_1;
}



## confidence

observed

## authority

shipped-artifact

## environment

null

## limitations

The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.,The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.,Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.,Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.,Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.,External functions and functions without an analyzable body return null; other decompiler failures remain explicit.,Ghidra Listing reports a terminal call at 0x140007653 with no resolved callee; its no-return basis is unknown.,Ghidra Listing reports a terminal call at 0x14000769e with no resolved callee; its no-return basis is unknown.,Ghidra Listing reports a terminal call at 0x140007904 with no resolved callee; its no-return basis is unknown.,This session uses Ghidra 12.1.2. The bridge is verified against 12.1.4; other 12.1.x builds are accepted and the observed version is reported.

## relationship_coverage

null

## locations



## evidence_links

