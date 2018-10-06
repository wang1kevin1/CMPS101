/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_3
 *
 * Matrix.java
 */

/**
 * A matrix as an array of Lists of Entry Objects, maintained in column sorted
 * order. The user of this interface can access elements by their integer
 * indices (column and row) and edit them. The programs allow the performance of
 * a variety of Matrix operations taking advantage of their "sparseness". A
 * matrix can be defined as "sparse" if the number of non-zero entries (NNZs) is
 * small compared to the total number of entries, n*n.
 * 
 * @author Kevin Wang
 * @since 5.8.2018
 */
public class Matrix {

	/**
	 * A private class which encapsulates the column and value information
	 * corresponding to a matrix entry. Entry has two fields that store types 'int'
	 * and 'double', respectively.
	 */
	private class Entry {

		/* Entry Fields */
		int column;
		double value;

		/* Entry Constructor */
		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}

		/*
		 * Overrides Object equals() method. Returns true if and only if this Entry and
		 * x are of the same class and have the same field values.
		 */
		public boolean equals(Object x) {
			boolean equivalent = true;
			if (x == null || !(this.getClass() == x.getClass())) { // check Object
				equivalent = false;
			} else { // check Entry
				Entry E = (Entry) x;

				if (!(this.column == E.column) || !(this.value == E.value)) { // check Entry fields
					equivalent = false;
				}
			}
			return equivalent;
		}

		/* Overrides Object toString() method. */
		public String toString() {
			return "(" + column + ", " + value + ")";
		}
	}

	/* Matrix Fields */
	private List[] rowArray;
	private int n;
	private int NNZ;

	/* Matrix Constructor - Makes a new n x n zero Matrix. Pre: n>=1 */
	Matrix(int n) {
		if (n < 1) {
			throw new RuntimeException("Matrix Error: invalid size of matrix.");
		}

		rowArray = new List[n];
		for (int i = 0; i < n; i++) {
			rowArray[i] = new List();
		}
		this.n = n;
		NNZ = 0;
	}

	/**
	 * ------------------------------------------------------------------------
	 * --------------------------- ACCESS FUNCTIONS ---------------------------
	 * ------------------------------------------------------------------------
	 */

	/* Returns n, the number of rows and columns of this Matrix. */
	public int getSize() {
		if (n < 1) {
			throw new RuntimeException("Matrix Error: size of matrix cannot be smaller than 1x1.");
		}
		return n;
	}

	/* Returns the number of non-zero entries in this Matrix. */
	public int getNNZ() {
		if (NNZ < 0) {
			throw new RuntimeException("Matrix Error: matrix cannot have less than 0 NNZ's.");
		}
		return NNZ;
	}

	/*
	 * Overrides Object equals() method. Returns true if and only if this Matrix and
	 * x are of the same class and have the same List sequence.
	 */
	public boolean equals(Object x) {
		boolean equivalent = true;
		if (x == null || !(this.getClass() == x.getClass())) { // check Object
			equivalent = false;
		} else { // check Matrix
			Matrix M = (Matrix) x;

			if (!(this.getSize() == M.getSize()) || !(this.getNNZ() == M.getNNZ())) { // check Matrix fields
				equivalent = false;
			} else { // check List
				int i = 0;
				while (equivalent && (i < this.getSize())) { // check List Size
					List A = this.rowArray[i];
					List B = M.rowArray[i];
					if (!(A.length() == B.length())) {
						equivalent = false;
					} else if (!(A.length() == 0) && (B.length() == 0)) {
						equivalent = false;
					} else if ((A.length() == 0) && !(B.length() == 0)) {
						equivalent = false;
					} else if ((A.length() == 0) && !(B.length() == 0)) {
						continue;
					} else { // check Entry
						A.moveFront();
						B.moveFront();

						while (equivalent && !(A.index() == -1)) {
							Entry a = (Entry) A.get();
							Entry b = (Entry) B.get();

							if (!a.equals(b)) { // check List
								equivalent = false;
							}
							A.moveNext();
							B.moveNext();
						}
					}
					i++;
				}
			}
		}
		return equivalent;
	}

	/**
	 * ------------------------------------------------------------------------
	 * ------------------------ MANIPULATION PROCEDURES -----------------------
	 * ------------------------------------------------------------------------
	 */

	/* Resets this Matrix to its original zero state. Size 'n' stays constant */
	void makeZero() {
		for (int i = 0; i < this.getSize(); i++) {
			List L = rowArray[i];
			if (!(L.length() == 0)) {
				L.clear(); // clear each row
			} // else do nothing
		}
		NNZ = 0;
	}

	/* Returns a new Matrix having the same entries as this Matrix. */
	Matrix copy() {
		Matrix M = new Matrix(this.getSize());
		M.NNZ = this.getNNZ();

		for (int i = 0; i < this.getSize(); i++) { // search through Lists
			List L = rowArray[i];
			if (!(L.length() == 0)) { // if List is non-empty...
				L.moveFront();

				while ((L.index() == -1)) { // search through Entries
					Entry E = (Entry) L.get();
					M.changeEntry(i + 1, E.column, E.value);
					L.moveNext();
				}
			}
		}
		return M;
	}

	/*
	 * Changes the Entry value field at i-th row, j-th column of this Matrix to x.
	 */
	void changeEntry(int i, int j, double x) {
		if (i < 1 || i > this.getSize()) {
			throw new RuntimeException("Matrix Error: Cannot call changeEntry() on Matrix with invalid i-th row");
		}
		if (j < 1 || j > this.getSize()) {
			throw new RuntimeException("Matrix Error: Cannot call changeEntry() on Matrix with invalid j-th column");
		}

		Entry E = new Entry(j, x); // new Entry for editing
		List L = rowArray[i - 1]; // access target List

		if ((L.length() == 0) && !(x == 0.0)) { // CASE 1: empty List, non-zero value ---> append
			L.append(E);
			NNZ++;
			return;
		} else if (!(L.length() == 0) && !(x == 0.0)) { // CASE 2: non-empty List, non-zero value
			L.moveFront();
			while (!(L.index() == -1)) { // search through Entries
				Entry N = (Entry) L.get();
				if (N.column < j) { // keep searching
					L.moveNext();
				} else if (N.column == j) { // if column is occupied ---> replace
					L.insertBefore(E);
					L.delete();
					// NNZ stays constant
					return;
				} else if (N.column > j) { // if column is unoccupied ---> insert
					L.insertBefore(E);
					NNZ++;
					return;
				}
			}
			L.append(E); // if new Entry has highest column index of NNZ
			NNZ++;
			return;
		} else if (!(L.length() == 0) && (x == 0.0)) { // CASE 3: non-empty List, zero value ---> delete
			L.moveFront();
			while (!(L.index() == -1)) { // search through Entries
				Entry N = (Entry) L.get();
				if (N.column < j) { // keep searching
					L.moveNext();
				} else if (N.column == j) { // if column is occupied ---> delete
					L.delete();
					NNZ--;
					return;
				} else if (N.column > j) { // if no more possible column matches, do nothing
					return;
				}
			}
			return; // if reached end of List, do nothing
		} else if ((L.length() == 0) && (x == 0.0)) { // CASE 4: empty List, zero value ---> do nothing
			return;
		}
	}

	/*
	 * Returns a new Matrix that is the scalar product of this Matrix with double x.
	 */
	Matrix scalarMult(double x) {
		Matrix M = new Matrix(this.getSize());

		if (x == 0.0) { // if scalar multiplying by zero
			return M;
		}

		for (int i = 0; i < this.getSize(); i++) { // scalar multiplication by double
			List A = this.rowArray[i];
			if (!(A.length() == 0)) { // if row is not empty
				List L = scalarMultRow(A, x);
				M.rowArray[i] = L;
			}
		}
		M.NNZ = this.getNNZ();
		return M;
	}

	/*
	 * Returns a new List that is the scalar product of List A and double 'x'.
	 */
	private List scalarMultRow(List A, double x) {
		List L = new List();

		A.moveFront();

		while (!(A.index() == -1)) { // append scaled entries to a new List
			Entry a = (Entry) A.get();
			double scalarProduct = x * a.value;
			if (!(scalarProduct == 0.0)) { // only keep NNZs
				L.append(new Entry(a.column, scalarProduct));
			}
			A.moveNext();
		}
		return L;
	}

	/*
	 * Returns a new Matrix that is the combined sum of this Matrix with Matrix M.
	 */
	Matrix add(Matrix M) {
		if (!(this.getSize() == M.getSize())) {
			throw new RuntimeException("Matrix Error: Cannot call add() on matrices of different sizes");
		}
		Matrix X = new Matrix(this.getSize());

		if (this.equals(M)) { // if adding two equal Matrices
			X = this.scalarMult(2);
			return X;
		}

		for (int i = 0; i < this.getSize(); i++) { // adding two Matrices
			List A = this.rowArray[i];
			List B = M.rowArray[i];
			if (!(A.length() == 0) || !(B.length() == 0)) { // if working with a non-empty List
				List L = new List();
				if (A.length() == 0) { // adding to empty List
					L = B;
				} else if (B.length() == 0) { // adding an empty List
					L = A;
				} else { // adding two non-empty Lists
					L = addRow(A, B);
				}
				X.rowArray[i] = L;
				X.NNZ += L.length();
			}
		}
		return X;
	}

	/*
	 * Returns a new List that is the combined sum of List A and List B
	 */
	private List addRow(List A, List B) {
		List L = new List();

		A.moveFront();
		B.moveFront();

		while (!(A.index() == -1) || !(B.index() == -1)) { // append added entries to a new List by column order
			if (A.index() == -1) {
				Entry b = (Entry) B.get();
				L.append(new Entry(b.column, b.value));
				B.moveNext();
			} else if (B.index() == -1) {
				Entry a = (Entry) A.get();
				L.append(new Entry(a.column, a.value));
				A.moveNext();
			} else {
				Entry a = (Entry) A.get();
				Entry b = (Entry) B.get();
				if (a.column < b.column) {
					L.append(new Entry(a.column, a.value));
					A.moveNext();
				} else if (a.column > b.column) {
					L.append(new Entry(b.column, b.value));
					B.moveNext();
				} else if (a.column == b.column) {
					double sum = a.value + b.value;
					if (!(sum == 0.0)) { // only keep NNZs
						L.append(new Entry(a.column, sum));
					}
					A.moveNext();
					B.moveNext();
				}
			}
		}
		return L;
	}

	/*
	 * Returns a new Matrix that is the difference of this Matrix with Matrix M.
	 */
	Matrix sub(Matrix M) {
		if (!(this.getSize() == M.getSize())) {
			throw new RuntimeException("Matrix Error: Cannot call sub() on matrices of different sizes");
		}
		Matrix X = new Matrix(this.getSize());

		if (this.equals(M)) { // if subtracting two equal Matrices
			return X;
		}

		for (int i = 0; i < this.getSize(); i++) { // subtracting two Matrices
			List A = this.rowArray[i];
			List B = M.rowArray[i];
			if (!(A.length() == 0) || !(B.length() == 0)) { // if working with a non-empty List
				List L = new List();

				if (A.length() == 0) { // subtracting from empty List
					L = scalarMultRow(B, -1.0);
				} else if (B.length() == 0) { // subtracting an empty List
					L = A;
				} else { // subtracting two non-empty Lists
					L = subRow(A, B);
				}
				X.rowArray[i] = L;
				X.NNZ += L.length();
			}
		}
		return X;
	}

	/*
	 * Returns a new List that is equivalent to List A minus List B
	 */
	private List subRow(List A, List B) {
		List L = new List();

		A.moveFront();
		B.moveFront();

		while (!(A.index() == -1) || !(B.index() == -1)) { // append subtracted entries to a new List by column order
			if (A.index() == -1) {
				Entry b = (Entry) B.get();
				L.append(new Entry(b.column, 0 - b.value));
				B.moveNext();
			} else if (B.index() == -1) {
				Entry a = (Entry) A.get();
				L.append(new Entry(a.column, a.value));
				A.moveNext();
			} else {
				Entry a = (Entry) A.get();
				Entry b = (Entry) B.get();

				if (a.column < b.column) {
					L.append(new Entry(a.column, a.value));
					A.moveNext();
				} else if (a.column > b.column) {
					L.append(new Entry(b.column, 0 - b.value));
					B.moveNext();
				} else if (a.column == b.column) {
					double difference = a.value - b.value;
					if (!(difference == 0.0)) { // only keep NNZs
						L.append(new Entry(a.column, difference));
					}
					A.moveNext();
					B.moveNext();
				}
			}
		}
		return L;
	}

	/*
	 * Returns a new Matrix that is the transpose of this Matrix.
	 */
	Matrix transpose() {
		Matrix M = new Matrix(this.getSize());

		for (int i = 0; i < this.getSize(); i++) { // transpose by row
			List A = this.rowArray[i];

			if (!(A.length() == 0)) { // if row is not empty
				A.moveFront();
				while (!(A.index() == -1)) { // swap row and column indexes
					Entry a = (Entry) A.get();
					M.changeEntry(a.column, i + 1, a.value);
					A.moveNext();
				}
			}
		}
		M.NNZ = this.getNNZ();
		return M;
	}

	/*
	 * Returns a new Matrix that is the product of this Matrix with Matrix M.
	 */
	Matrix mult(Matrix M) {
		if (getSize() != M.getSize()) {
			throw new RuntimeException("\"Matrix Error: Cannot call mult() on matrices of different sizes\"");
		}
		Matrix X = new Matrix(getSize());
		Matrix TransM = M.transpose();

		for (int i = 0; i < this.getSize(); i++) { // multiplying two matrices
			List A = this.rowArray[i];

			List L = new List();
			for (int j = 0; j < this.getSize(); j++) {
				List B = TransM.rowArray[j];

				if (!(A.length() == 0) && !(B.length() == 0)) { // if neither List is empty
					double product = dotProduct(A, B);

					if (!(product == 0.0)) { // if the product is non-zero
						L.append(new Entry(j + 1, product));
					}
				}
			}
			X.rowArray[i] = L;
			X.NNZ += L.length();
		}
		return X;
	}

	/*
	 * Returns a the dot product of List A and List B
	 */
	private double dotProduct(List A, List B) {
		double dotproduct = 0.0;

		A.moveFront();
		B.moveFront();

		while (!(A.index() == -1) || !(B.index() == -1)) { // calculate dotproduct
			if (B.index() == -1) {
				A.moveNext();
			} else if (A.index() == -1) {
				B.moveNext();
			} else {
				Entry a = (Entry) A.get();
				Entry b = (Entry) B.get();
				if (a.column < b.column) {
					A.moveNext();
				} else if (a.column > b.column) {
					B.moveNext();
				} else if (a.column == b.column) {
					dotproduct += (a.value * b.value);

					A.moveNext();
					B.moveNext();
				}
			}
		}
		return dotproduct;
	}

	/**
	 * ------------------------------------------------------------------------
	 * --------------------------- ACCESS FUNCTIONS ---------------------------
	 * ------------------------------------------------------------------------
	 */

	/*
	 * Overrides Object's toString method. Returns a String representation of this
	 * Matrix.
	 */
	public String toString() {
		String str = "";
		for (int i = 1; i <= n; i++) {
			if (rowArray[i - 1].length() > 0) {
				str = str + i + ":" + rowArray[i - 1].toString();
				str += "\n";
			}
		}
		return str;
	}
}