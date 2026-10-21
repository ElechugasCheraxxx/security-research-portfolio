// DumpFuncs.java - postScript de Ghidra headless: exporta funciones y strings
//@category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;

public class DumpFuncs extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String out = args.length > 0 ? args[0] : "/tmp/ghidra_funcs.txt";
        PrintWriter w = new PrintWriter(new FileWriter(out));
        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        int n = 0;
        while (it.hasNext()) {
            Function f = it.next();
            w.println(f.getEntryPoint() + "\t" + f.getBody().getNumAddresses() + "\t" + f.getName());
            n++;
        }
        w.println("# TOTAL_FUNCS " + n);
        w.close();
        println("[DumpFuncs] " + n + " funciones -> " + out);
    }
}