//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;

public class DumpDecomp extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outdir = args.length > 0 ? args[0] : "/tmp/ghidra_out";
        long lo = args.length > 1 ? Long.parseLong(args[1], 16) : 0x140001000L;
        long hi = args.length > 2 ? Long.parseLong(args[2], 16) : 0x140021000L;
        new File(outdir).mkdirs();
        DecompInterface di = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        di.setOptions(opts);
        di.toggleCCode(true);
        di.toggleSyntaxTree(true);
        di.setSimplificationStyle("decompile");
        if (!di.openProgram(currentProgram)) {
            println("[DumpDecomp] no se pudo abrir el programa");
            return;
        }
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        int n = 0, bad = 0;
        PrintWriter idx = new PrintWriter(new FileWriter(outdir + "/_index.txt"));
        while (it.hasNext()) {
            Function f = it.next();
            long a = f.getEntryPoint().getOffset();
            if (a < lo || a >= hi) continue;
            DecompileResults res = di.decompileFunction(f, 120, monitor);
            String c = null;
            if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                c = res.getDecompiledFunction().getC();
            }
            String rva = Long.toHexString(a - currentProgram.getImageBase());
            if (c == null || c.isEmpty()) { bad++; c = "/* decompilacion fallida */\n"; }
            String fn = outdir + "/g_" + rva + ".c";
            PrintWriter w = new PrintWriter(new FileWriter(fn));
            w.println("/* RVA 0x" + rva + "  " + f.getBody().getNumAddresses() + " B  " + f.getName() + " */");
            w.println(c);
            w.close();
            idx.println("0x" + rva + "\t" + f.getBody().getNumAddresses() + "\t" + f.getName() + "\t" + c.length());
            n++;
        }
        idx.close();
        di.dispose();
        println("[DumpDecomp] " + n + " funciones decompiladas, " + bad + " fallidas -> " + outdir);
    }
}