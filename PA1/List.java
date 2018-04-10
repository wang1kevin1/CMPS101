//-----------------------------------------------------------------------------
//  Kevin Wang
//  kwang43@ucsc.edu
//  PA_1
//
//  List.java
//  List ADT
//-----------------------------------------------------------------------------


public class List {
	private class Node {
		int data;
		Node prev;
		Node next;

		// Constructor
		public Node(int data) {
			this.data = data;
			prev = null;
			next = null;
		}
	}

	// List Data
	private Node front;
	private Node back;
	private Node cursor;
	private int length = 0;
	private int index;

	// Constructor
	public List() {
		front = null;
		back = null;
		cursor = null;
		length = 0;
		index = -1;
	}

	// ACCESS FUNCTIONS

	// Returns the number of elements in this List.
	int length() {
		return length;
	}

	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index() {
		if (index > length - 1 || index < -1) {
			index = -1;
		}
		return index;
	}

	// Returns front element. Pre: length()>0
	int front() {
		Node N = front;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call front() on empty List");
		} else {
			return N.data;
		}
	}

	// Returns back element. Pre: length()>0
	int back() {
		Node N = back;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call back() on empty List");
		} else {
			return N.data;
		}
	}

	// Returns cursor element. Pre: length()>0, index()>=0
	int get() {
		Node N = cursor;
		if (length <= 0) {
			throw new RuntimeException(
					"List Error: Cannot call get() on empty List");
		} else if (index < 0) {
			throw new RuntimeException("List Error: Cursor index undefined");
		} else {
			return N.data;
		}
	}

	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	boolean equals(List L) {
		boolean value = true;
		Node N = this.front;
		Node P = L.front;
		if (this.length == L.length) {
			while (value && N != null) {
				if (N.data != P.data) {
					value = false;
				}
				N = N.next;
				P = P.next;
			}
		}
		return value;
	}

	// MANIPULATION PROCEDURES

	// Resets this List to its original empty state.
	void clear() {
		front = null;
		back = null;
		cursor = null;
		length = 0;
	}

	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront() {
		if (length <= 0) {
			throw new RuntimeException(
					"List Error: Cannot call moveFront() on empty List");
		}
		cursor = front;
		index = 0;
	}

	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack() {
		if (length <= 0) {
			throw new RuntimeException(
					"List Error: Cannot call moveBack() on empty List");
		}
		cursor = back;
		index = length - 1;
	}

	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev() {
		Node N;
		if (index == 0 || index == -1) {
			cursor = null;
			index = -1;
		} else {
			N = cursor;
			cursor = N.prev;
		}
	}

	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext() {
		Node N;
		if (index == length - 1 || index == -1) {
			cursor = null;
			index = -1;
		} else {
			N = cursor;
			cursor = N.next;
		}
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data) {
		Node N;
		if (front == null) {
			front = new Node(data);
			back = front;
			cursor = front;
		} else {
			N = front;
			N.prev = new Node(data);
			front = N.prev;
			front.next = N;
		}
		length++;
		index++;
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data) {
		Node N;
		if (back == null) {
			back = new Node(data);
			front = back;
			cursor = back;
			index++;
		} else {
			N = back;
			N.next = new Node(data);
			back = N.next;
			back.prev = N;
		}
		length++;
	}

	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(int data) {
		Node N = cursor;
		Node P, Q;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call insertBefore() on empty List");
		}
		if (index == -1) {
			throw new RuntimeException(
					"List Error: Cannot call insertBefore() on undefined cursor");
		}
		if (N.data == front.data) {
			N.prev = new Node(data);
			front = N.prev;
			front.next = N;
		} else {
			P = new Node(data);
			Q = N.prev;
			N.prev = P;
			Q.next = P;
			P.next = N;
			P.prev = Q;
		}
		length++;
		index++;
	}

	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data) {
		Node N = cursor;
		Node P, Q;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call insertAfter() on empty List");
		}
		if (index == -1) {
			throw new RuntimeException(
					"List Error: Cannot call insertAfter() on undefined cursor");
		}
		if (N.data == back.data) {
			N.next = new Node(data);
			back = N.next;
			back.prev = N;
		} else {
			Q = new Node(data);
			P = N.next;
			N.next = Q;
			P.prev = Q;
			Q.prev = N;
			Q.next = P;
		}
		length++;
	}

	// Deletes the front element. Pre: length()>0
	void deleteFront() {
		Node N = front;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call deleteFront() on empty List");
		} else {
			front = N.next;
			front.prev = null;
			N.next = null;
		}
		length--;
		if (index != -1) {
			index--;
		}
	}

	// Deletes the back element. Pre: length()>0
	void deleteBack() {
		Node N = back;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call deleteBack() on empty List");
		} else {
			back = N.prev;
			back.next = null;
			N.prev = null;
		}
		length--;
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete() {
		Node N, P;
		if (length == 0) {
			throw new RuntimeException(
					"List Error: Cannot call delete() on empty List");
		}
		if (index == -1) {
			throw new RuntimeException(
					"List Error: Cannot call delete() on undefined cursor");
		}
		if (cursor.data == front.data) {
			N = front;
			front = N.next;
			front.prev = null;
			N.next = null;
			cursor = null;
		} else if (cursor.data == back.data) {
			N = back;
			back = N.prev;
			back.next = null;
			N.prev = null;
			cursor = null;
		} else {
			N = cursor.prev;
			P = cursor.next;
			N.next = P;
			P.prev = N;
			cursor = null;
		}
		length--;
		index = -1;
	}

	// OTHER METHODS

	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString() {
		Node N = front;
		String str = "";
		while (N != null) {
			str += N.data + " ";
			N = N.next;
		}
		return str;
	}

	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	public List copy() {
		Node N = back;
		List M = new List();
		while (N != null) {
			M.prepend(N.data);
			N = N.prev;
		}
		return M;
	}

	// Returns a new List which is the concatenation of
	// this list followed by L. The cursor in the new List
	// is undefined, regardless of the states of the cursors
	// in this List and L. The states of this List and L are
	// unchanged.
	public List concat(List L) {
		Node N = back;
		List M = new List();
		while (N != null) {
			M.prepend(N.data);
			N = N.prev;
		}
		return M;
	}

}
