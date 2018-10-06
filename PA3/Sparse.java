
/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_3
 *
 * Sparse.java
 */

import java.io.*;
import java.util.*;

/**
 * This program takes two command line arguments giving the names of an input
 * file and an output file. The input contains the Matrix and Entry information.
 * Sparse.java reads the input file, initializes and builds the Array of Lists
 * representation of the matrices A and B, then calculates and prints the
 * following matrices to the output file: 
 * A, B, (1.5)A, A + B, A + A, B - A, A - A, Transpose of A, A * B, B * B.
 * 
 * @author Kevin Wang
 * @since 5.8.2018
 */
public class Sparse {
	public static void main(String[] args) throws IOException {
		if (!(args.length == 2)) {
			throw new RuntimeException("Usage: Sparse input_file ouput_file");
		}

		// Initialize IO
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		String line;
		String[] tokens;

		// Initialize Matrix information
		int n; // Matrix size
		int a; // number of NNZs in Matrix A
		int b; // number of NNZs in Matrix B

		// Initialize Entry information
		int row; // Entry row
		int col; // Entry row
		double val; // Entry value

		// Get Matrix Information.
		line = in.nextLine();
		tokens = line.split(" ");
		n = Integer.parseInt(tokens[0]);
		a = Integer.parseInt(tokens[1]);
		b = Integer.parseInt(tokens[2]);

		// Skip buffer line
		line = in.nextLine();

		// Initialize Matrices
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		// Get Matrix A Entry Information
		int i = 0;
		while (i < a) {
			line = in.nextLine();
			tokens = line.split(" ");

			row = Integer.parseInt(tokens[0]);
			col = Integer.parseInt(tokens[1]);
			val = Double.parseDouble(tokens[2]);
			A.changeEntry(row, col, val);

			i++;
		}

		// Skip buffer line
		line = in.nextLine();

		// Get Matrix B Entry Information
		int j = 0;
		while (j < b) {
			line = in.nextLine();
			tokens = line.split(" ");

			row = Integer.parseInt(tokens[0]);
			col = Integer.parseInt(tokens[1]);
			val = Double.parseDouble(tokens[2]);
			B.changeEntry(row, col, val);

			j++;
		}

		// Print to outfile
		out.println("A has " + a + " non-zero entries: ");
		out.println(A);

		out.println("B has " + b + " non-zero entries: ");
		out.println(B);

		out.println("(1.5)*A = ");
		out.println(A.scalarMult(1.5));

		out.println("A+B = ");
		out.println(A.add(B));

		out.println("A+A = ");
		out.println(A.add(A));

		out.println("B-A = ");
		out.println(B.sub(A));

		out.println("A-A = ");
		out.println(A.sub(A));

		out.println("Transpose(A) = ");
		out.println(A.transpose());

		out.println("A*B = ");
		out.println(A.mult(B));

		out.println("B*B = ");
		out.println(B.mult(B));

		// Close IO Streams
		in.close();
		out.close();
	}
}
