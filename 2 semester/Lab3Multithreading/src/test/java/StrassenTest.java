import com.univ.lab3.Matrix;
import com.univ.lab3.StrassenMultiply;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.security.SecureRandom;


public class StrassenTest {

    private static final SecureRandom RANDOM = new SecureRandom();
    @Test
    public void multiplyingTest(){
        Matrix<Integer> matrix1 = new Matrix<>(200);
        fillRandom(matrix1, 10);
//        matrix1.print();

        long start = System.nanoTime();
//        Matrix<Integer> simpleRes = StrassenMultiply.multiply(matrix1, matrix1);
        long end = System.nanoTime();
//        simpleRes.print();
//        System.out.println("Simple: " + (end - start) / 1000000 + " ms");
        start = System.nanoTime();
        Matrix<Integer> strassenRes = StrassenMultiply.strassenMultiplication(matrix1, matrix1, false);
        end = System.nanoTime();
        System.out.println("Strassen: " + (end - start) / 1000000 + " ms");
        start = System.nanoTime();
        Matrix<Integer> strassenMultiRes = StrassenMultiply.strassenMultiplication(matrix1, matrix1, true);
        end = System.nanoTime();
        System.out.println("Strassen Multithreaded: " + (end - start) / 1000000 + " ms");
//        strassenRes.print();

//        assertEquals(simpleRes, strassenRes);
        assertEquals(strassenRes, strassenMultiRes);
    }

    public void fillRandom(Matrix<Integer> matrix, int bound){

        for(int i = 0; i < matrix.getPower(); i++){
            for(int j = 0; j < matrix.getPower(); j++){
                matrix.rows[i][j] = RANDOM.nextInt(bound);
            }
        }
    }
}
