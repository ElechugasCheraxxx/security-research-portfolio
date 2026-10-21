## evidence_id

ev_426e5475d8db971a1dc08e3a6a875695eddca2c7789a268d4e8255bca845eef5

## subject.name

chunk0.exe

## subject.digest

| Key    | Value                                                            |
|--------|------------------------------------------------------------------|
| sha256 | fca6ee8910f7a850629c2a34e2c1145373a7c3726c43a97e6ba71e767e8365e2 |

## subject.local_path

/root/mrgarabato_analysis/run/stage3/chunk0.exe

## subject.format

pe

## subject.architecture

x86_64

## provider

| Key     | Value                               |
|---------|-------------------------------------|
| id      | rea-workflow                        |
| name    | REA composed investigation workflow |
| version | 1                                   |

## analysis_profile.provider

| Key     | Value                               |
|---------|-------------------------------------|
| id      | rea-workflow                        |
| name    | REA composed investigation workflow |
| version | 1                                   |

## analysis_profile.parameters.upstream_analysis_profile.provider

| Key     | Value  |
|---------|--------|
| id      | ghidra |
| name    | Ghidra |
| version | 12.1.2 |

## analysis_profile.parameters.upstream_analysis_profile.parameters.target_kind

executable

## analysis_profile.parameters.upstream_analysis_profile.parameters.target_format

pe

## analysis_profile.parameters.upstream_analysis_profile.parameters.executable_role

application

## analysis_profile.parameters.upstream_analysis_profile.parameters.managed

false

## analysis_profile.parameters.upstream_analysis_profile.parameters.native_aot_metadata

| Key                  | Value                       |
|----------------------|-----------------------------|
| contract_revision    | rtr-9.1-x64-pe-read-only-v3 |
| source_bytes         | 134217728                   |
| work_units           | 67108864                    |
| working_memory_bytes | 67108864                    |
| report_bytes         | 4194304                     |

## analysis_profile.parameters.upstream_analysis_profile.parameters.architecture

x86_64

## analysis_profile.parameters.upstream_analysis_profile.parameters.available_architectures

x86_64

## analysis_profile.parameters.upstream_analysis_profile.parameters.import_mode

ephemeral-source-immutable

## analysis_profile.parameters.upstream_analysis_profile.parameters.pdb_observations

program-info-v5

## analysis_profile.parameters.upstream_analysis_profile.parameters.annotation_policy

atomic-function-entry-metadata-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.load_image_observations

source-mappings-entry-context-v2

## analysis_profile.parameters.upstream_analysis_profile.parameters.function_body_evidence

complete-inclusive-ranges-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.function_references

complete-body-and-entry-reference-manager-v2

## analysis_profile.parameters.upstream_analysis_profile.parameters.call_relationship_coverage

function-body-call-coverage-v5

## analysis_profile.parameters.upstream_analysis_profile.parameters.function_dossier_coverage

observed-facets-and-call-relationships-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.string_inventory_evidence

defined-data-coverage-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.location_resolution

explicit-address-exact-entry-symbol-first-v3

## analysis_profile.parameters.upstream_analysis_profile.parameters.procedure_file_offset_resolution

address-first-unique-target-source-mapping-v2

## analysis_profile.parameters.upstream_analysis_profile.parameters.instruction_flow_evidence

decoded-return-pcode-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.instruction_references

exact-address-incoming-without-synthetic-entry-v2

## analysis_profile.parameters.upstream_analysis_profile.parameters.function_boundary_observations

ghidra-function-boundary-limitations-v4

## analysis_profile.parameters.upstream_analysis_profile.parameters.no_return_repair

returning-imports-decoded-return-v2

## analysis_profile.parameters.upstream_analysis_profile.parameters.process_launch

inspected-jvm-launch-support-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.jump_table_evidence

typed-case-default-blocks-v1

## analysis_profile.parameters.upstream_analysis_profile.parameters.decompiler_jump_loads

true

## analysis_profile.parameters.upstream_analysis_profile.parameters.loader

auto-from-header

## analysis_profile.parameters.upstream_analysis_profile.parameters.language_id

auto-from-header

## analysis_profile.parameters.upstream_analysis_profile.parameters.compiler_spec_id

auto-default

## analysis_profile.parameters.upstream_analysis_profile.parameters.analyzer_preset

ghidra-default

## analysis_profile.parameters.upstream_analysis_profile.digest

c9d1b8b5fece7826116befe30d99989217a2a975af7b8b94086fe87ab12668d1

## analysis_profile.parameters.source_limitations

provider-operation-caveats-v1

## analysis_profile.parameters.workflow_revision

4

## analysis_profile.digest

fb576f6ab50b01c1bd8f6798fa0adbe730bfe81818b074478d2a713acb6d9a07

## predicate_type

rea.analysis

## operation

binary_overview

## parameters

| Key | Value |
|-----|-------|


## raw_result

null

## normalized_result.document

target-fca6ee8910f7.exe

## normalized_result.image_base

0x140000000

## normalized_result.segments

| name    | start       | end         | length | image_base  | address_space |
|---------|-------------|-------------|--------|-------------|---------------|
| Headers | 0x140000000 | 0x140000200 | 512    | 0x140000000 | ram           |
| .text   | 0x140825000 | 0x1408a5000 | 524288 | 0x140000000 | ram           |

## normalized_result.segment_count

2

## normalized_result.procedure_count

629

## normalized_result.string_count

273

## confidence

derived

## authority

shipped-artifact

## environment

null

## limitations

Derived by an REA composed workflow.,Ghidra (ghidra 12.1.2) list_documents, list_procedures, list_segments, list_strings: Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.,Ghidra (ghidra 12.1.2) list_documents, list_procedures, list_segments, list_strings: Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.,Ghidra (ghidra 12.1.2) list_documents, list_procedures, list_segments, list_strings: The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.,Ghidra (ghidra 12.1.2) list_documents, list_procedures, list_segments, list_strings: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.,Ghidra (ghidra 12.1.2) list_documents, list_procedures, list_segments, list_strings: This session uses Ghidra 12.1.2. The bridge is verified against 12.1.4; other 12.1.x builds are accepted and the observed version is reported.,Ghidra (ghidra 12.1.2) list_documents: A headless Ghidra session contains exactly one imported Program, unlike Hopper's multi-document GUI session.,Ghidra (ghidra 12.1.2) list_procedures: External functions and local thunks are distinct; procedure metadata identifies both and preserves a thunk target when Ghidra resolves one.,Ghidra (ghidra 12.1.2) list_segments: Memory-block end addresses are exclusive; permissions come from Ghidra MemoryBlock flags rather than inference from section names.,Ghidra (ghidra 12.1.2) list_strings: Charset is reported, while a non-missing terminator cannot distinguish a present terminator from a fixed or Pascal layout.,Ghidra (ghidra 12.1.2) list_strings: Only Ghidra-defined string Data is observed; packed or undefined string bytes may be absent. Completeness applies to that inventory, and an empty search does not establish that text is absent from the artifact. If an address is known, use read_bytes and xrefs to inspect bytes and references.

## relationship_coverage

null

## locations



## evidence_links

