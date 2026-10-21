## error

Analysis failed

## code

execution_failure

## category

execution_failure

## message

Analysis could not complete. Run `rea doctor` and review the reported details; repeating the unchanged request is not expected to succeed.

## retryable

false

## remediation

| Key    | Value                                                                                                                                      |
|--------|--------------------------------------------------------------------------------------------------------------------------------------------|
| action | Analysis could not complete. Run `rea doctor` and review the reported details; repeating the unchanged request is not expected to succeed. |

## details.provider_id

ida

## details.operation

procedure_pseudo_code

## details.diagnostics

| Key      | Value                                                                                         |
|----------|-----------------------------------------------------------------------------------------------|
| reason   | fetch failed                                                                                  |
| recovery | Check the configured upstream MCP registration and selected target; see docs/ida-provider.md. |
