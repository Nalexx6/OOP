package com.univ.lab3;

public class Matrix<T> {

    private final int power;
    public T[][] rows;

    public Matrix(int power){
        this.power = power;
        this.rows = (T[][]) new Integer[power][power];
        for(int i = 0; i < power; i++){
            for(int j = 0; j < power; j++){
                rows[i][j] = (T) new Integer(0);
            }
        }

    }

    public int getPower() {
        return power;
    }

    public void print(){
        for(int i = 0; i < power; i++){
            for(int j = 0; j < power; j++){
                System.out.print(rows[i][j] + "\t");

            }
            System.out.println();
        }
    }

    @Override
    public boolean equals(Object o){
        if(o == this){
            return true;
        }

        if(!(o instanceof Matrix )){
            return false;
        }

        Matrix<T> matrix = (Matrix<T>) o;

        if(power != matrix.getPower()){
            return false;
        }

        for(int i = 0; i < power; i++){
            for(int j = 0; j < power; j++){
                if(!rows[i][j].equals(matrix.rows[i][j])){
                    return false;
                }

            }
        }

        return true;
    }

}
