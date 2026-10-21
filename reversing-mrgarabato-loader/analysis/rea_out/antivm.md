## evidence_id

ev_460681d7b6c06656cec00291718a1662966d106a8e025cc2bb7f607b08edae52

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
| procedure | 0x14001a9a0 |

## raw_result.value


longlong FUN_14001a984(int param_1)

{
  char cVar1;
  uint7 extraout_var;
  uint7 uVar2;
  undefined7 extraout_var_00;
  uint7 extraout_var_01;
  
  if (param_1 == 0) {
    DAT_14002fa88 = 1;
  }
  FUN_14001ad54();
  cVar1 = FUN_14001b628();
  uVar2 = extraout_var;
  if (cVar1 != '\0') {
    cVar1 = FUN_14001b628();
    if (cVar1 != '\0') {
      return CONCAT71(extraout_var_00,1);
    }
    FUN_14001b628();
    uVar2 = extraout_var_01;
  }
  return (ulonglong)uVar2 << 8;
}



## raw_result.limitations



## normalized_result


longlong FUN_14001a984(int param_1)

{
  char cVar1;
  uint7 extraout_var;
  uint7 uVar2;
  undefined7 extraout_var_00;
  uint7 extraout_var_01;
  
  if (param_1 == 0) {
    DAT_14002fa88 = 1;
  }
  FUN_14001ad54();
  cVar1 = FUN_14001b628();
  uVar2 = extraout_var;
  if (cVar1 != '\0') {
    cVar1 = FUN_14001b628();
    if (cVar1 != '\0') {
      return CONCAT71(extraout_var_00,1);
    }
    FUN_14001b628();
    uVar2 = extraout_var_01;
  }
  return (ulonglong)uVar2 << 8;
}



## confidence

observed

## authority

shipped-artifact

## environment

null

## limitations

The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.,The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.,Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.,Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.,Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.,External functions and functions without an analyzable body return null; other decompiler failures remain explicit.,This session uses Ghidra 12.1.2. The bridge is verified against 12.1.4; other 12.1.x builds are accepted and the observed version is reported.

## relationship_coverage

null

## locations



## evidence_links

