## error

Analysis failed

## code

provider_timeout

## category

timeout

## message

Analysis took too long. Try a smaller request, then run `rea doctor` if it continues.

## retryable

true

## remediation

| Key    | Value                                                                                 |
|--------|---------------------------------------------------------------------------------------|
| action | Analysis took too long. Try a smaller request, then run `rea doctor` if it continues. |

## details.operation

list_documents

## details.timeout_ms

330000

## details.diagnostics.target_path

/root/mrgarabato_analysis/run/stage3/wine_unpacked.exe

## details.diagnostics.target_sha256

6b2dec3888fff5b70f200e2663faba05689db9c13bbe4efbb890e33292aee879

## details.diagnostics.transport

unix-socket

## details.diagnostics.provider_version

12.1.2

## details.diagnostics.profile_digest

c9d1b8b5fece7826116befe30d99989217a2a975af7b8b94086fe87ab12668d1

## details.diagnostics.run_id

93f7345a-31b0-4475-9f04-97224a051095

## details.diagnostics.runtime_root

/tmp/rea-ghidra-SCOuv4

## details.diagnostics.endpoint_path

/tmp/rea-ghidra-SCOuv4/bridge.sock

## details.diagnostics.project_root

/tmp/rea-ghidra-SCOuv4/project

## details.diagnostics.ghidra_log_path

/tmp/rea-ghidra-SCOuv4/ghidra.log

## details.diagnostics.script_log_path

/tmp/rea-ghidra-SCOuv4/script.log

## details.diagnostics.process_id

87757

## details.diagnostics.launch_support

| mode     | stderr                                                                                      | stderr_bytes | stderr_truncated |
|----------|---------------------------------------------------------------------------------------------|--------------|------------------|
| -envvars | NOTE: Picked up JDK_JAVA_OPTIONS: 
Picked up JAVA_TOOL_OPTIONS: 
Picked up _JAVA_OPTIONS: 
 | 91           | false            |
| -vmargs  | NOTE: Picked up JDK_JAVA_OPTIONS: 
Picked up JAVA_TOOL_OPTIONS: 
Picked up _JAVA_OPTIONS: 
 | 91           | false            |

## details.diagnostics.exit_code

null

## details.diagnostics.exit_signal

null

## details.diagnostics.diagnostic_truncated

false

## details.diagnostics.stdout

| Key            | Value                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
|----------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| text           | INFO  Using log config file: jar:file:/opt/ghidra/Ghidra/Framework/Generic/lib/Generic.jar!/generic.log4j.xml (LoggingInitialization)  
INFO  Using log file: /tmp/rea-ghidra-SCOuv4/ghidra.log (LoggingInitialization)  
INFO  Loading user preferences: /tmp/rea-ghidra-SCOuv4/config/root-ghidra/ghidra_12.1.2_DEV/preferences (Preferences)  
INFO  Searching for classes... (ClassSearcher)  
INFO  Class search complete (8883 ms) (ClassSearcher)  
INFO  Initializing SSL Context (DefaultSSLContextInitializer)  
INFO  Initializing Random Number Generator... (SecureRandomFactory)  
INFO  Random Number Generator initialization complete: NativePRNGNonBlocking (SecureRandomFactory)  
INFO  Trust manager disabled, cacerts have not been set (DefaultTrustManagerFactory)  
INFO  Starting cache cleanup: /tmp/rea-ghidra-SCOuv4/cache/root-ghidra/fscache2 (FileCacheMaintenanceDaemon)  
INFO  Finished cache cleanup, estimated storage used: 0 (FileCacheMaintenanceDaemon)  
INFO  Headless startup complete (23674 ms) (AnalyzeHeadless)  
INFO  Class searcher loaded 59 extension points (20 false positives) (ClassSearcher)  
INFO  HEADLESS Script Paths:
    /opt/ghidra/Ghidra/Features/SystemEmulation/ghidra_scripts
    /root/mrgarabato_analysis/run/rea/rea/bridge/ghidra
    /opt/ghidra/Ghidra/Features/GnuDemangler/ghidra_scripts
    /opt/ghidra/Ghidra/Features/WildcardAssembler/ghidra_scripts
    /opt/ghidra/Ghidra/Processors/DATA/ghidra_scripts
    /opt/ghidra/Ghidra/Features/DecompilerDependent/ghidra_scripts
    /opt/ghidra/Ghidra/Processors/JVM/ghidra_scripts
    /opt/ghidra/Ghidra/Debug/Debugger-rmi-trace/ghidra_scripts
    /opt/ghidra/Ghidra/Features/MicrosoftCodeAnalyzer/ghidra_scripts
    /opt/ghidra/Ghidra/Features/VersionTracking/ghidra_scripts
    /opt/ghidra/Ghidra/Features/PyGhidra/ghidra_scripts
    /opt/ghidra/Ghidra/Features/SwiftDemangler/ghidra_scripts
    /opt/ghidra/Ghidra/Features/Base/ghidra_scripts
    /opt/ghidra/Ghidra/Processors/Atmel/ghidra_scripts
    /opt/ghidra/Ghidra/Debug/Debugger/ghidra_scripts
    /opt/ghidra/Ghidra/Features/Decompiler/ghidra_scripts
    /opt/ghidra/Ghidra/Features/FunctionID/ghidra_scripts
    /opt/ghidra/Ghidra/Features/PDB/ghidra_scripts
    /opt/ghidra/Ghidra/Processors/8051/ghidra_scripts
    /opt/ghidra/Ghidra/Processors/PIC/ghidra_scripts
    /opt/ghidra/Ghidra/Features/FileFormats/ghidra_scripts
    /opt/ghidra/Ghidra/Features/BSim/ghidra_scripts
    /opt/ghidra/Ghidra/Features/BytePatterns/ghidra_scripts (HeadlessAnalyzer)  
INFO  HEADLESS: execution starts (HeadlessAnalyzer)  
INFO  Creating temporary project: /tmp/rea-ghidra-SCOuv4/project/rea-project (HeadlessAnalyzer)  
INFO  Creating project: /tmp/rea-ghidra-SCOuv4/project/rea-project (DefaultProject)  
INFO  REPORT: Processing input files:  (HeadlessAnalyzer)  
INFO       project: /tmp/rea-ghidra-SCOuv4/project/rea-project (HeadlessAnalyzer)  
INFO  IMPORTING: file:///tmp/rea-ghidra-SCOuv4/target-6b2dec3888ff.exe (HeadlessAnalyzer)  
INFO  Using Loader: Portable Executable (PE) (ProgramLoader)  
INFO  Using Language/Compiler: x86:LE:64:default:windows (ProgramLoader)  
INFO  Using Library Search Path: [., /bin, /lib, /lib64, /lib/x86_64-linux-gnu, /lib/aarch64-linux-gnu, /usr/bin, /usr/lib, /usr/X11R6/bin, /usr/X11R6/lib, /usr/java/packages/lib, /usr/lib64] (ProgramLoader)  
INFO  Additional info:
Loading file:///tmp/rea-ghidra-SCOuv4/target-6b2dec3888ff.exe?MD5=be8441a023b2c5f7e4fc7b70be68fc75...
------------------------------------------------

 (ProgramLoader)  
INFO  IMPORTING: Loaded 0 additional files (HeadlessAnalyzer)  
INFO  ANALYZING all memory and code: file:///tmp/rea-ghidra-SCOuv4/target-6b2dec3888ff.exe (HeadlessAnalyzer)  
WARN  Ignoring leading '_' chars on no-return name '___raise_securityfailure' specified in file: /opt/ghidra/Ghidra/Features/Base/data/PEFunctionsThatDoNotReturn (NoReturnFunctionAnalyzer)  
WARN  Ignoring leading '_' chars on no-return name '___report_rangecheckfailure' specified in file: /opt/ghidra/Ghidra/Features/Base/data/PEFunctionsThatDoNotReturn (NoReturnFunctionAnalyzer)  
INFO  Skipping PDB processing: missing PDB information in program metadata (PdbUniversalAnalyzer)  
WARN  More than 100 address segments have been created! (AddressMapDB)  
WARN  WARNING! Repairing body of function at 14086d305 (ClearFlowAndRepairCmd)  
ERROR ... function body repair failed due to overlap with another function: 14086d305 (ClearFlowAndRepairCmd)  
 |
| bytes          | 4442                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| retained_bytes | 4442                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |

## details.diagnostics.stderr

| Key            | Value                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
|----------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| text           | NOTE: Picked up JDK_JAVA_OPTIONS: 
Picked up JAVA_TOOL_OPTIONS: 
Picked up _JAVA_OPTIONS: 
openjdk version "27" 2026-09-15
OpenJDK Runtime Environment (build 27)
OpenJDK 64-Bit Server VM (build 27, mixed mode)
WARNING: Final field name in class ghidra.util.charset.CharsetInfo has been mutated reflectively by class com.google.gson.internal.bind.ReflectiveTypeAdapterFactory$2 in unnamed module @58695725 (file:/opt/ghidra/Ghidra/Framework/Generic/lib/gson-2.13.2.jar)
WARNING: Use --enable-final-field-mutation=ALL-UNNAMED to avoid a warning
WARNING: Mutating final fields will be blocked in a future release unless final field mutation is enabled
WARNING: A terminally deprecated method in sun.misc.Unsafe has been called
WARNING: sun.misc.Unsafe::staticFieldOffset has been called by org.apache.felix.framework.util.SecureAction (file:/opt/ghidra/Ghidra/Features/Base/lib/org.apache.felix.framework-7.0.5.jar)
WARNING: Please consider reporting this to the maintainers of class org.apache.felix.framework.util.SecureAction
WARNING: sun.misc.Unsafe::staticFieldOffset will be removed in a future release
 |
| bytes          | 1106                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| retained_bytes | 1106                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |

## details.diagnostics.failure_kind

timeout

## details.diagnostics.failure_message

Ghidra startup deadline elapsed
