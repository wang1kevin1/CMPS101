/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_3
 *
 * List.java
 */

/**
 * A bi-directional queue in the form of a doubly linked list. The user of this
 * interface has precise control over where in the list each element is
 * inserted. The user can access elements by their integer index (position in
 * the list), and search for elements in the list. A list has two ends referred
 * to as "front" and "back" respectively. It pair will be used by the client to
 * traverse the list in either direction. Each list element is associated with
 * an index ranging from 0 (front) to n-1 (back), where n is the length of the
 * list.
 * 
 * Note that it is a valid state for this ADT to have no distinguished element
 * (i.e. the cursor index may be undefined or "off the list") which is in fact
 * its default state. Thus the set of "mathematical structures" for this ADT
 * consists of all finite sequences of Objects in which at most one element is
 * underscored.
 * 
 * @author Kevin Wang
 * @since 5.8.2018
 */
public class List {

	/**
	 * A private doubly linked list class which itself contains fields for an Object
	 * (the data), and two Node references (the previous and next Nodes,
	 * respectively) which may be null.
	 */
	private class Node {

		/* Node Fields. */
		Object data;
		Node prev;
		Node next;

		/* Node Constructor. */
		Node(Object data) {
			this.data = data;
			prev = null;
			next = null;
		}

		/* Overrides Object toString() method. */
		public String toString() {
			return String.valueOf(data);
		}
	}

	/* List Fields */
	private Node front;
	private Node back;
	private Node cursor;
	private int index;
	private int length;

	/* List Constructor */
	List() {
		front = null;
		back = null;
		cursor = null;
		index = -1;
		length = 0;
	}

	/**
	 * ------------------------------------------------------------------------
	 * --------------------------- ACCESS FUNCTIONS ---------------------------
	 * ------------------------------------------------------------------------
	 */

	/* Returns the number of elements in this List. */
	int length() {
		if (length < 0) {
			throw new RuntimeException("List Error: length of List cannot be less than 0");
		}
		return length;
	}

	/*
	 * If cursor is defined, returns the index of the cursor element, otherwise
	 * returns -1.
	 */
	int index() {
		if (index < -1) {
			throw new RuntimeException("List Error: index of cursor cannot be less than -1");
		}
		return index;
	}

	/* Returns front element. Pre: length()>0 */
	Object front() {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call front() on empty List");
		}
		return front.data;
	}

	/* Returns back element. Pre: length()>0 */
	Object back() {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call back() on empty List");
		}
		return back.data;
	}

	/* Returns cursor element. Pre: length()>0, index()>=0 */
	Object get() {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call get() on empty List");
		}
		if (this.index() == -1) {
			throw new RuntimeException("List Error: Cannot call get() on undefined index");
		}
		return cursor.data;
	}

	/*
	 * Overrides Object equals() method. Returns true if and only if this List and L
	 * are the same integer sequence. The states of the cursors in the two Lists are
	 * not used in determining equality.
	 */
	public boolean equals(Object x) {
		boolean equivalent = true;
		if ((x == null) || !(this.getClass() == x.getClass())) { // check Object
			equivalent = false;
		} else { // check List
			List L = (List) x;

			if (!(this.length() == L.length())) {
				equivalent = false;
			} else { // check Node
				Node A = this.front;
				Node B = L.front;

				while (equivalent && !(A == null)) {
					if (!(A.data == B.data)) {
						equivalent = false;
					}
					A = A.next;
					B = B.next;
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

	/* Resets this List to its original empty state. */
	void clear() {
		front = null;
		back = null;
		cursor = null;
		index = -1;
		length = 0;
	}

	/*
	 * If List is non-empty, places the cursor under the front element, otherwise
	 * does nothing.
	 */
	void moveFront() {
		if (this.length() > 0) { // if List is non-empty...
			cursor = front;
			index = 0;
		}
	}

	/*
	 * If List is non-empty, places the cursor under the back element, otherwise
	 * does nothing.
	 */
	void moveBack() {
		if (this.length() > 0) { // if List is non-empty...
			cursor = back;
			index = this.length() - 1;
		}
	}

	/*
	 * If cursor is defined and not at front, moves cursor one step toward front of
	 * this List, if cursor is defined and at front, cursor becomes undefined, if
	 * cursor is undefined does nothing.
	 */
	void movePrev() {
		if (!(cursor == null) && (this.index() > 0)) { // if cursor is defined and not at front...
			cursor = cursor.prev;
			index--;
		} else if (!(cursor == null) && (this.index() == 0)) { // if cursor is defined and at front...
			cursor = null;
			index = -1;
		}
	}

	/*
	 * If cursor is defined and not at back, moves cursor one step toward back of
	 * this List, if cursor is defined and at back, cursor becomes undefined, if
	 * cursor is undefined does nothing.
	 */
	void moveNext() {
		if (!(cursor == null) && (this.index() < this.length() - 1)) { // if cursor is defined and not at back...
			cursor = cursor.next;
			index++;
		} else if (!(cursor == null) && (this.index() == this.length() - 1)) { // if cursor is defined and at back...
			cursor = null;
			index = -1;
		}
	}

	/*
	 * Insert new element into this List. If List is non-empty, insertion takes
	 * place before front element.
	 */
	void prepend(Object data) {
		if (this.length() == 0) { // if List is empty...
			front = new Node(data);
			back = front;
		} else { // if List is non-empty...
			Node N = new Node(data);

			N.next = front;
			front.prev = N;
			front = N;

			index++;
		}
		length++;
	}

	/*
	 * Insert new element into this List. If List is non-empty, insertion takes
	 * place after back element.
	 */
	void append(Object data) {
		if (this.length() == 0) { // if List is empty...
			back = new Node(data);
			front = back;
		} else { // if List is non-empty...
			Node N = new Node(data);

			N.prev = back;
			back.next = N;
			back = N;
		}
		length++;
	}

	/*
	 * Insert new element before cursor. Pre: length()>0, index()>=0
	 */
	void insertBefore(Object data) {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call insertBefore() on empty List");
		}
		if (this.index() == -1) {
			throw new RuntimeException("List Error: Cannot call insertBefore() on undefined cursor");
		}

		if (this.index() == 0) { // if cursor is at front...
			Node N = new Node(data);

			N.next = cursor;
			cursor.prev = N;
			front = N;
		} else { // cursor is not at front...
			Node N = new Node(data);
			Node prefix = cursor.prev;

			N.prev = prefix;
			N.next = cursor;
			prefix.next = N;
			cursor.prev = N;
		}
		index++;
		length++;
	}

	/*
	 * Inserts new element after cursor. Pre: length()>0, index()>=0
	 */
	void insertAfter(Object data) {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call insertAfter() on empty List");
		}
		if (this.index() == -1) {
			throw new RuntimeException("List Error: Cannot call insertAfter() on undefined cursor");
		}

		if (this.index() == this.length() - 1) { // if cursor is at back...
			Node N = new Node(data);

			N.prev = cursor;
			cursor.next = N;
			back = N;
		} else { // cursor is not at back...
			Node N = new Node(data);
			Node suffix = cursor.next;

			N.next = suffix;
			N.prev = cursor;
			suffix.prev = N;
			cursor.next = N;
		}
		length++;
	}

	/* Deletes the front element. Pre: length()>0 */
	void deleteFront() {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call deleteFront() on empty List");
		}
		if (this.length() == 1) {
			this.clear();
		} else {
			front = front.next;
			front.prev = null;

			if (this.index() == 0) { // if index is defined and at front...
				cursor = null;
				index = -1;
			} else if (this.index() > 0) { // if index is defined and not at front...
				index--;
			} // if index is undefined, do nothing
			length--;
		}
	}

	/* Deletes the back element. Pre: length()>0 */
	void deleteBack() {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call deleteBack() on empty List");
		}
		if (this.length() == 1) {
			this.clear();
		} else {
			back = back.prev;
			back.next = null;

			if (this.index() == this.length() - 1) { // if index is defined and at back...
				cursor = null;
				index = -1;
			} // if index is undefined, do nothing
			length--;
		}

	}

	/*
	 * Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
	 */
	void delete() {
		if (this.length() == 0) {
			throw new RuntimeException("List Error: Cannot call delete() on empty List");
		}
		if (this.index() == -1) {
			throw new RuntimeException("List Error: Cannot call delete() on undefined cursor");
		}
		if (this.length() == 1) {
			this.clear();
		} else {
			if (this.index() == 0) { // if index is defined and at front...
				front = front.next;
				front.prev = null;
			} else if (this.index() == this.length() - 1) { // if index is defined and at back...
				back = back.prev;
				back.next = null;
			} else {
				Node prefix = cursor.prev;
				Node suffix = cursor.next;

				prefix.next = suffix;
				suffix.prev = prefix;
			}
			cursor = null;
			index = -1;
			length--;
		}
	}

	/**
	 * ------------------------------------------------------------------------
	 * --------------------------- ACCESS FUNCTIONS ---------------------------
	 * ------------------------------------------------------------------------
	 */

	/*
	 * Overrides Object's toString method. Returns a String representation of this
	 * List consisting of a space separated sequence of integers, with front on
	 * left.
	 */
	public String toString() {
		Node N = front;
		String str = "";
		while (!(N == null)) {
			str += N.data + " ";
			N = N.next;
		}
		return str;
	}
}
