package com.univ.lab3;

/**
 * Implementation of Strassen algorithm
 * Two types provided: simple and parallel
 *
 * Input matrices must have equal power
 */
public class StrassenMultiply {

    private static final int CUTOFF = 32;

    /**
     * Perform multiplication between two matrices
     */
    public static Matrix<Integer> multiply(Matrix<Integer> matrix1, Matrix<Integer> matrix2){
        if(matrix1.getPower() != matrix2.getPower()){
            throw new IllegalArgumentException();
        }

        Matrix<Integer> res = new Matrix<>(matrix1.getPower());

        int temp_value = 0;
        for(int i = 0; i < matrix1.getPower(); i++){
            for(int j = 0; j < matrix1.getPower(); j++){
                for(int k = 0; k < matrix1.getPower(); k++) {
                    temp_value += matrix1.rows[i][k] * matrix2.rows[k][j];


                }
                res.rows[i][j] = temp_value;
                temp_value = 0;
            }
        }

        return res;
    }

    /**
     * Perform addition between two matrices
     */
    private static Matrix<Integer> add(Matrix<Integer> matrix1, Matrix<Integer> matrix2){
        if(matrix1.getPower() != matrix2.getPower()){
            throw new IllegalArgumentException();
        }

        Matrix<Integer> res = new Matrix<>(matrix1.getPower());

        for(int i = 0; i < matrix1.getPower(); i++){
            for(int j = 0; j < matrix1.getPower(); j++){
                res.rows[i][j]  = matrix1.rows[i][j] + matrix2.rows[i][j] ;
            }
        }
        
        return  res;
    }

    /**
     * Perform subtraction between two matrices
     */
    private static Matrix<Integer> sub(Matrix<Integer> matrix1, Matrix<Integer> matrix2){
        if(matrix1.getPower() != matrix2.getPower()){
            throw new IllegalArgumentException();
        }

        Matrix<Integer> res = new Matrix<>(matrix1.getPower());

        for(int i = 0; i < matrix1.getPower(); i++){
            for(int j = 0; j < matrix1.getPower(); j++){
                res.rows[i][j]  = matrix1.rows[i][j] - matrix2.rows[i][j] ;
            }
        }
        
        return res;
    }

    /**
     * Shell of Strassen algorithm
     * Responsible for resizing matrices to acceptable power
     * And resizing result to input power
     */
    public static Matrix<Integer> strassenMultiplication(Matrix<Integer> matrix1, Matrix<Integer> matrix2){
        if(matrix1.getPower() != matrix2.getPower()){
            throw new IllegalArgumentException();
        }

        Matrix<Integer> matrix1Resized = resize(matrix1);
        Matrix<Integer> matrix2Resized = resize(matrix2);

        Matrix<Integer> res = new Matrix<>(matrix1.getPower());

        Matrix<Integer> resizedResult = strassen(matrix1Resized, matrix2Resized);

        for(int i = 0; i < resizedResult.getPower(); i++){
            for(int j = 0; j < resizedResult.getPower(); j++){
                if(i < res.getPower() && j < res.getPower()) {
                    res.rows[i][j] = resizedResult.rows[i][j];
                }
            }
        }

        return res;
    }

    /**
     * Resize matrix to its copy with 2^n power
     * Which makes strassen algorithm possible to use
     */
    private static Matrix<Integer> resize(Matrix<Integer> matrix){
        int k = 1;
        while(matrix.getPower() > k){
            k *= 2;
        }

        Matrix<Integer> resized = new Matrix<>(k);

        for(int i = 0; i < k; i++){
            for(int j = 0; j < k; j++) {
                if (i >= matrix.getPower() || j >= matrix.getPower()) {
                    resized.rows[i][j] = 0;
                } else {
                    resized.rows[i][j] = matrix.rows[i][j];
                }
            }
        }

        return resized;
    }


    private static Matrix<Integer> strassen(Matrix<Integer> matrix1, Matrix<Integer> matrix2){
        if(matrix1.getPower() != matrix2.getPower()){
            throw new IllegalArgumentException();
        }
        
        Matrix<Integer> res = new Matrix<>(matrix1.getPower());
        
        if (res.getPower() < CUTOFF) {

            // Returning the simple multiplication
            return multiply(matrix1, matrix2);

            // Matrix
        } else {

            
            // Step 2: Dividing matrix1 into 4 halves
            Matrix<Integer> A11 = split(matrix1, 1);
            Matrix<Integer> A12 = split(matrix1, 2);
            Matrix<Integer> A21 = split(matrix1, 3);
            Matrix<Integer> A22 = split(matrix1, 4);

            // Step 2: Dividing matrix2 into 4 halves
            Matrix<Integer> B11 = split(matrix2, 1);
            Matrix<Integer> B12 = split(matrix2, 2);
            Matrix<Integer> B21 = split(matrix2, 3);
            Matrix<Integer> B22 = split(matrix2, 4);

            // Using Formulas as described in algorithm

            // M1:=(A1+A3)×(B1+B2)
            Matrix<Integer> M1
                    = multiply(add(A11, A22), add(B11, B22));

            // M2:=(A2+A4)×(B3+B4)
            Matrix<Integer> M2 = multiply(add(A21, A22), B11);

            // M3:=(A1−A4)×(B1+A4)
            Matrix<Integer> M3 = multiply(A11, sub(B12, B22));

            // M4:=A1×(B2−B4)
            Matrix<Integer> M4 = multiply(A22, sub(B21, B11));

            // M5:=(A3+A4)×(B1)
            Matrix<Integer> M5 = multiply(add(A11, A12), B22);

            // M6:=(A1+A2)×(B4)
            Matrix<Integer> M6
                    = multiply(sub(A21, A11), add(B11, B12));

            // M7:=A4×(B3−B1)
            Matrix<Integer> M7
                    = multiply(sub(A12, A22), add(B21, B22));

            // P:=M2+M3−M6−M7
            Matrix<Integer> C11 = add(sub(add(M1, M4), M5), M7);

            // Q:=M4+M6
            Matrix<Integer> C12 = add(M3, M5);

            // R:=M5+M7
            Matrix<Integer> C21 = add(M2, M4);

            // S:=M1−M3−M4−M5
            Matrix<Integer> C22 = add(sub(add(M1, M3), M2), M6);

            // Step 3: Join 4 halves into one result matrix
            join(C11, res, 1);
            join(C12, res, 2);
            join(C21, res, 3);
            join(C22, res, 4);
        }

        // Step 4: Return result
        return res;
    }

    private static Matrix<Integer> split(Matrix<Integer> toSplit, int quarter){
        if(quarter > 4){
            throw new IllegalArgumentException();
        }

        Matrix<Integer> res = new Matrix<>(toSplit.getPower() / 2);
        int iM = quarter > 2 ? res.getPower() : 0;
        int jM = quarter % 2 == 0 ? res.getPower() : 0;


        for (int i1 = 0, i2 = iM; i1 < res.getPower(); i1++, i2++) {

            // Inner loop for columns
            for (int j1 = 0, j2 = jM; j1 < res.getPower(); j1++, j2++) {

                res.rows[i1][j1] = toSplit.rows[i2][j2];
            }
        }

        return res;
    }

    private static void join(Matrix<Integer> toJoin, Matrix<Integer> destination, int quarter){
        if(quarter > 4 || toJoin.getPower() * 2 != destination.getPower()) {
            throw new IllegalArgumentException();
        }

        int iM = quarter > 2 ? toJoin.getPower() : 0;
        int jM = quarter % 2 == 0 ? toJoin.getPower() : 0;


        for (int i1 = 0, i2 = iM; i1 < toJoin.getPower(); i1++, i2++) {

            // Inner loop for columns
            for (int j1 = 0, j2 = jM; j1 < toJoin.getPower(); j1++, j2++) {

                destination.rows[i2][j2] = toJoin.rows[i1][j1];
            }
        }
    }

}

