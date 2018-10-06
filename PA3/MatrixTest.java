/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_3
 *
 * MatrixTest.java - Taken and slightly modified from...
 * https://github.com/legendddhgf/cmps101-pt.s18.grading/blob/master/pa3/ModelMatrixTest.java
 */

public class MatrixTest {
	public static void main(String[] args) {

		Matrix A;
		Matrix B;
		Matrix C;

		// Empty_GetSize Test
		A = new Matrix(3);
		if (A.getSize() != 3) {
			System.out.println("Failed Empty_GetSize");
		}
		// NonEmpty_GetSize Test
		A = new Matrix(3);
		A.changeEntry(1, 1, 4);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 0);
		A.changeEntry(2, 1, 2);
		A.changeEntry(3, 1, 0);
		A.changeEntry(2, 2, 2);
		A.changeEntry(3, 3, 0);
		if (A.getSize() != 3) {
			System.out.println("Failed NonEmpty_GetSize");
		}
		// Empty_GetNNZ Test
		A = new Matrix(3);
		if (A.getNNZ() != 0) {
			System.out.println("Failed Empty_GetNNZ");
		}
		// MakeZero_GetNNZ Test
		A = new Matrix(3);
		A.changeEntry(1, 1, 4);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 0);
		A.changeEntry(2, 1, 2);
		A.changeEntry(3, 1, 0);
		A.changeEntry(2, 2, 2);
		A.changeEntry(3, 3, 0);
		A.makeZero();
		if (A.getNNZ() != 0) {
			System.out.println("Failed MakeZero_GetNNZ");
		}
		// ChangeEntry_GetNNZ Test
		A = new Matrix(10);
		A.changeEntry(2, 1, 2);
		A.changeEntry(3, 1, 5);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 5);
		A.changeEntry(1, 1, 4);
		A.changeEntry(2, 2, 2);
		A.changeEntry(2, 5, 0);
		A.changeEntry(2, 3, 0);
		A.changeEntry(3, 3, 5);
		if (A.getNNZ() != 7) {
			System.out.println("Failed ChangeEntry_GetNNZ 1");
		}
		A.changeEntry(1, 3, 0);
		A.changeEntry(3, 1, 0);
		A.changeEntry(3, 3, 0);
		if (A.getNNZ() != 4) {
			System.out.println("Failed ChangeEntry_GetNNZ 2");
		}
		A.changeEntry(7, 6, 42);
		A.changeEntry(10, 1, 24);
		if (A.getNNZ() != 6) {
			System.out.println("Failed ChangeEntry_GetNNZ 3");
		}
		A.changeEntry(7, 6, 0);
		if (A.getNNZ() != 5) {
			System.out.println("Failed ChangeEntry_GetNNZ 4");
		}
		A.makeZero();
		A.changeEntry(5, 5, 5);
		if (A.getNNZ() != 1) {
			System.out.println("Failed ChangeEntry_GetNNZ 5");
		}
		// Copy_GetNNZ Test
		A = new Matrix(10);
		B = A.copy();
		if (B.getNNZ() != 0) {
			System.out.println("Failed Copy_GetNNZ 1");
		}
		A.changeEntry(1, 1, 1);
		B = A.copy();
		if (B.getNNZ() != 1) {
			System.out.println("Failed Copy_GetNNZ 2");
		}
		// Transpose_GetNNZ Test
		A = new Matrix(3);
		B = A.transpose();
		if (B.getNNZ() != 0) {
			System.out.println("Failed Transpose_GetNNZ 1");
		}
		A.changeEntry(1, 1, 4);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 0);
		A.changeEntry(2, 1, 2);
		A.changeEntry(3, 1, 0);
		A.changeEntry(2, 2, 2);
		A.changeEntry(3, 3, 0);
		B = A.transpose();
		if (B.getNNZ() != 4) {
			System.out.println("Failed Transpose_GetNNZ 2");
		}
		// Add_GetNNZ Test
		A = new Matrix(10);
		B = new Matrix(10);
		A.changeEntry(1, 1, 4);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 0);
		A.changeEntry(2, 1, 2);
		A.changeEntry(3, 1, 0);
		A.changeEntry(2, 2, 2);
		A.changeEntry(3, 3, 0);
		C = A.add(A);
		if (C.getNNZ() != 4 || A.getNNZ() != 4) {
			System.out.println("Failed Add_GetNNZ 1");
		}
		B.changeEntry(1, 1, -4);
		B.changeEntry(1, 2, 0);
		B.changeEntry(2, 1, 0);
		B.changeEntry(2, 2, -2);
		B.changeEntry(2, 4, 2);
		B.changeEntry(3, 1, 0);
		B.changeEntry(3, 2, 2);
		B.changeEntry(7, 8, 5);
		C = A.add(B);
		if (C.getNNZ() != 5) {
			System.out.println("Failed Add_GetNNZ 2");
		}
		// Sub_GetNNZ Test
		A = new Matrix(10);
		B = new Matrix(10);
		A.changeEntry(1, 1, -4);
		A.changeEntry(1, 2, -2);
		A.changeEntry(1, 3, 0);
		A.changeEntry(2, 5, 4);
		A.changeEntry(2, 1, -2);
		A.changeEntry(3, 1, 2);
		A.changeEntry(2, 2, -2);
		A.changeEntry(3, 3, 0);
		C = A.sub(A);
		if (C.getNNZ() != 0 || A.getNNZ() != 6) {
			System.out.println("Failed Sub_GetNNZ 1");
		}
		B.changeEntry(1, 1, -4);
		B.changeEntry(1, 2, 0);
		B.changeEntry(2, 1, 0);
		B.changeEntry(2, 2, -2);
		B.changeEntry(2, 4, 2);
		B.changeEntry(3, 1, 2);
		B.changeEntry(3, 2, 2);
		B.changeEntry(7, 8, 5);
		C = A.sub(B);
		if (C.getNNZ() != 6) {
			System.out.println("Failed Sub_GetNNZ 2");
		}
		// ScalarMult_GetNNZ Test
		A = new Matrix(10);
		A.changeEntry(1, 1, 4);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 0);
		A.changeEntry(2, 1, 2);
		A.changeEntry(3, 1, 0);
		A.changeEntry(2, 2, 2);
		A.changeEntry(3, 3, 0);
		B = A.scalarMult(-20);
		if (B.getNNZ() != 4) {
			System.out.println("Failed ScalarMult_GetNNZ 1");
		}
		// Mult_GetNNZ Test
		A = new Matrix(10);
		B = new Matrix(10);
		A.changeEntry(1, 1, 1);
		A.changeEntry(2, 2, 1);
		A.changeEntry(3, 3, 1);
		C = A.mult(A);
		if (C.getNNZ() != 3) {
			System.out.println("Failed Mult_GetNNZ 1");
		}
		A.changeEntry(1, 1, 1);
		A.changeEntry(1, 2, 2);
		A.changeEntry(1, 3, 3);
		A.changeEntry(2, 1, 4);
		A.changeEntry(2, 2, 5);
		A.changeEntry(2, 3, 6);
		A.changeEntry(3, 1, 7);
		A.changeEntry(3, 2, 8);
		A.changeEntry(3, 3, 9);
		B.changeEntry(1, 1, 1);
		B.changeEntry(2, 2, 1);
		C = A.mult(B);
		if (C.getNNZ() != 6) {
			System.out.println("Failed Mult_GetNNZ 2");
		}
		// Empty_Equals Test
		A = new Matrix(10);
		B = new Matrix(15);
		if (A.equals(B)) {
			System.out.println("Failed Empty_Equals 1");
		}
		B = new Matrix(10);
		if (!A.equals(B)) {
			System.out.println("Failed Empty_Equals 2");
		}
		A.changeEntry(5, 5, 5);
		B.changeEntry(5, 5, 5);
		A.makeZero();
		B.makeZero();
		if (!A.equals(B)) {
			System.out.println("Failed Empty_Equals 3");
		}
		// NonEmpty_Equals Test
		A = new Matrix(10);
		B = new Matrix(15);
		A.changeEntry(1, 1, 1);
		B.changeEntry(1, 1, 1);
		if (A.equals(B)) {
			System.out.println("Failed NonEmpty_Equals 1");
		}
		B = new Matrix(10);
		A.changeEntry(1, 1, 1);
		A.changeEntry(1, 3, 1);
		B.changeEntry(1, 1, 1);
		B.changeEntry(1, 3, 1);
		if (!A.equals(B)) {
			System.out.println("Failed NonEmpty_Equals 2");
		}
		A.changeEntry(1, 3, 0);
		if (A.equals(B)) {
			System.out.println("Failed NonEmpty_Equals 3");
		}
		A.changeEntry(1, 1, 0);
		B.makeZero();
		A.changeEntry(10, 10, 10);
		B.changeEntry(10, 10, 10);
		if (!A.equals(B)) {
			System.out.println("Failed NonEmpty_Equals 4");
		}
		A = new Matrix(100);
		B = new Matrix(100);
		int valcount = 1;
		for (int j = 1; j <= 100; j++) {
			for (int k = 1; k <= 100; k++) {
				// hint: this is 1-10000 left-to-right row-by-row
				A.changeEntry(j, k, valcount++);
			}
			B.changeEntry(j, j, 1); // hint: this is the identity matrix
		}
		C = A.scalarMult(2);
		if (!C.equals(A.add(A))) {
			System.out.println("Failed NonEmpty_Equals 1");
		}
		C = A.scalarMult(-2);
		if (!C.equals(A.sub(A).sub(A).sub(A))) {
			System.out.println("Failed NonEmpty_Equals 2");
		}
		C = A.mult(B);
		if (!C.equals(A)) {
			System.out.println("Failed NonEmpty_Equals 3");
		}
	}
}
