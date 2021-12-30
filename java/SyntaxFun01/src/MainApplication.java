import com.adrianpoplesanu.function01.FunctionPointerTest;
import com.adrianpoplesanu.function01.PredicatePointerTest;
import com.adrianpoplesanu.function01.SupplierPointerTest;
import com.adrianpoplesanu.process_execution.ProcessExecutor;
import com.adrianpoplesanu.process_execution.ProcessExecutor2;
import com.adrianpoplesanu.process_execution.ProcessExecutor3;

import java.io.IOException;

public class MainApplication {
    public static void main(String[] args) {
        System.out.println("running all syntax fun snippets...");
        /*FunctionPointerTest functionPointerTest = new FunctionPointerTest();
        functionPointerTest.testFunctionMethod();

        PredicatePointerTest predicatePointerTest = new PredicatePointerTest();
        predicatePointerTest.testPredicatePointer();
        predicatePointerTest.testPredicatePointer2();

        SupplierPointerTest supplierPointerTest = new SupplierPointerTest();
        supplierPointerTest.testSupplierPointer();
        supplierPointerTest.testSupplierPointer();*/

        /*try {
            ProcessExecutor.testProcessExecution();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }*/

        /*try {
            ProcessExecutor.test2();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }*/

        /*try {
            ProcessExecutor2.test();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }*/

        ProcessExecutor3.testWorker();
    }
}
