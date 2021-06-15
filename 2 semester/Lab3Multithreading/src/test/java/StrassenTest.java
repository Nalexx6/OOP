import com.univ.lab3.Matrix;
import com.univ.lab3.StrassenMultiply;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.security.SecureRandom;


public class StrassenTest {

    private static final SecureRandom RANDOM = new SecureRandom();

    @Test
    public void multiplyingTest(){
        Matrix<Integer> matrix1 = new Matrix<>(1000);
        fillRandom(matrix1, 10);
//        matrix1.print();


        Matrix<Integer> simpleRes = StrassenMultiply.multiply(matrix1, matrix1);
//        simpleRes.print();
        Matrix<Integer> strassenRes = StrassenMultiply.strassenMultiplication(matrix1, matrix1);
//        strassenRes.print();

        assertEquals(simpleRes, strassenRes);
    }

    public void fillRandom(Matrix<Integer> matrix, int bound){

        for(int i = 0; i < matrix.getPower(); i++){
            for(int j = 0; j < matrix.getPower(); j++){
                matrix.rows[i][j] = RANDOM.nextInt(bound);
            }
        }
    }
}
